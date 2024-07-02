/*
 * systemStates.c
 *
 * Created: 19.05.2024 14:31:08
 *  Author: marc
 */ 

#include "systemStates.h"
#include "gpio.h"
#include "adc.h"
#include "eeprom.h"
#include "powerMgr.h"
#include "uart.h"
#include "display.h"
#include "measure.h"
#include "timer.h"
#include "exti.h"
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#define IS_USB_POWERED (1)

#define SPEED_OF_SOUND_MM_PER_MILLI_SEC (343)
#define PARAMETRIZATION_REQUEST_SIZE (6) /*1 start character, 1 read write close connection indicator, 2 address bytes, 2 value bytes*/
#define PARAMETRIZATION_RESPONSE_SIZE (6) /*1 start character, 1 response code (read write positive, negative), 2 address bytes(echo), 2 value bytes*/

#define MIN(x,y) ((x)<(y)?(x):(y))
#define HIGHBYTE_OF(x) (((x)&0xFF00)>>8)
#define LOWBYTE_OF(x) (((x)&0x00FF))
						
volatile bool hasInterruptTriggered = false;
volatile systemState_t systemState = systemState_boot;
volatile systemState_t oldState = systemState_boot;


void Appl_systemStateMachine_execute(void)
{
	// actions to perfom in current state
	switch(systemState)
	{
		case systemState_boot:
		{
			// state action for boot state 
			PWR_disableAllPeripherals();
			PWR_enableUsedPeripherals();
			PWR_setNormalClockSpeed();
			wdt_disable();
			GPIO_init();
			EEPROM_init();
			GPIO_setVBatMeasEn_to(true);
			GPIO_setDispEn_to(false);
			USART_Init();
			USART_Transmit(":e",2);
			ADC_init();
			if(
				  (Meas_BatVoltage() <= 7000)
				&&(IS_USB_POWERED == 0)
			  )
			{
				// on low battery voltage switch to low battery voltage stage where essentially everything is turned off and forbidden.
				systemState = systemState_batLowFault;
			}
			else if(GPIO_getPin(Wakeup) == false)
			{
				// just booted and button is pressed .. transition into parametrization mode. 
				systemState = systemState_parametrization;
			}
			else
			{
				systemState = systemState_measure;
				//systemState = systemState_parametrization; // test only
			}

			// if else logic ensures that the boot state will only be traversed once
		}
		break;
		case systemState_measure:
		{
			// state action for the measure state --> the measure state likely is been reached because the system got woken up (less likely because of transition from boot state)
			// check the battery voltage before taking any fluid level measurement or doing any display business
			// if we just transitioned here from the boot state then the voltage measurement is redundant but will not harm too much
			PWR_enableUsedPeripherals(); // technically redundant when coming from boot state but absolutely required when entering via button press b/c timer and ADC are disabled and would not be enabled otherwise. causing the program to hang here after wakeup indefinitely
			ADC_init();
			uint16_t measuredBatVoltage = 0;

			#if IS_USB_POWERED == 0
				measuredBatVoltage = Meas_BatVoltage();
			#else
				measuredBatVoltage = 7543; // dummy value for testing
			#endif

			if(measuredBatVoltage <= 7000)
			{
				systemState = systemState_batLowFault;
			}
			else
			{
				// measurements are allowed --> perform them here
				ADC_disable(); // disable the ADC since the ADC is only needed for the battery voltage measurement and that has been performed already
				GPIO_setVBatMeasEn_to(false); // battery measurement already performed and voltage deemed sufficent for the measurement to be allowable... --> no need for measurement circuitry to be enabled anymore
				/*
				DDRA &= ~(1<<pins[SensEcho].pinnumber);
				*/
				/**
				PORTA |= (1<<pins[SensEcho].pinnumber); // input pullup 
				*/
				GPIO_setSensSupM_to(false); // negative supply to low aka gnd
				GPIO_setSensSupP_to(true); // positive supply to high aka vcc -> effectively provide power to the sensors
				_delay_ms(100); // allow the range finder to power up
				volatile uint32_t distanceAvg = 0;
				#define SENSOR 1
				#if SENSOR == 1
				for(uint8_t i=0;i<EEPROM_averagingSampleCnt;i++)
				{
					volatile uint32_t durationInTicks = 0;
					switch(EEPROM_sensorType)
					{
						case sensorType_triggerEcho:
						{
							GPIO_setSensTrig_to(false); // generate the edge pattern needed for the trigger pin; timing taken from the arduino example for the hc-sr04 board; busy wait used since timing intervals are really short and do not really require timer based generation.
							_delay_us(2);
							GPIO_setSensTrig_to(true);
							_delay_us(50);
							GPIO_setSensTrig_to(false);
							while(GPIO_getPin(SensEcho) == false); // wait for the echo pin to go high because a falling edge means the echo has been received
							while(GPIO_getPin(SensEcho)==true)
							{
								durationInTicks++;
							}
							//measurement taken convert to distance next
						}
						break;
						case sensorType_grove:
						{
							pins[SensSig].isOutput = true; // initially used as trigger pin
							GPIO_SensSigPinReinit();
							GPIO_setSensSig_to(false); // generate the edge pattern needed for the trigger on the sig pin that serves double duty in the grove boards
							_delay_us(2);
							GPIO_setSensSig_to(true);
							_delay_us(10);
							GPIO_setSensSig_to(false);
							pins[SensSig].isOutput = false;
							GPIO_SensSigPinReinit();
							while(GPIO_getPin(SensSig) == false); // wait for the echo pin to go high because a falling edge means the echo has been received
							while(GPIO_getPin(SensSig)==true)
							{
								durationInTicks++;
							}
							//measurement taken convert to distance next
						}
						break;
						default:
						{
							// no such sensor;
							// nothing to do; maybe display warning in display
						}
						break;
					}
					_delay_ms(20); // to ensure the maximum sample rate of the module is never surpassed (50hz)
					volatile uint32_t durationInMicroseconds = durationInTicks * 104/10; // 8mhz internal rc osc means that one instruction takes 1/8 of a us... so conversion factor is >=8 value has been experimentally determined...
					volatile const uint32_t distanceCm = durationInMicroseconds * SPEED_OF_SOUND_MM_PER_MILLI_SEC / 2 / 10000;
					distanceAvg += distanceCm;
				}
				#endif
				
				distanceAvg /= EEPROM_averagingSampleCnt; // divide the summed up distance samples to actually get the average distance to be displayed

				uint16_t distanceHigherThanEmpty = EEPROM_tankempty_cm > distanceAvg ? EEPROM_tankempty_cm - distanceAvg : 0; // empty tank should always be less than the measured distance otherwise the tank is "more than empty" so show an empty tank instead...
				uint16_t litersInTank = 0;

				if(
					  (EEPROM_numOfTanks != 0)// calculation of volume in liters is possible b/c atleast one tank is defined as present
					&&(EEPROM_areaEntriesUsed != 0) // calculation of volume in liters is possible b/c atleast one area is defined so the volume can be approximated with cuboids 
					&&(distanceHigherThanEmpty > 0) // only attempt calculating the liters in the tank when there is acually anything in the tank, otherwise; an empty tank by definition has zerl liters inside of it.
				  )
				{
					for(uint8_t j=0;j<EEPROM_areaEntriesUsed;j++)
					{
						if(EEPROM_areaEntrySpacing * (j+1) <= distanceHigherThanEmpty)
						{
							// areaentry must be taken into account calculating the volume in liters b/c current fill is at higher level than the location of the currently iterated over area value
							litersInTank += EEPROM_areaEntries[j] * EEPROM_areaEntrySpacing;
						}
						else
						{
							// area entry was measured at lower height than currently measured -- thus the current entry can not be used completely but instead the height that goes over the height where the area was measured at must be taken for the volume calculation
							litersInTank += EEPROM_areaEntries[j] * (EEPROM_areaEntrySpacing-((EEPROM_areaEntrySpacing * (j+1)) - distanceHigherThanEmpty)); 
							break;// leave the loop since all the area entries that would actually yield any valid liter-age of fluid have now been considered and accounted for.
						}
					}
					litersInTank *= EEPROM_numOfTanks; // area is only for one tank in tank array thus total fluid amount is times number of individual tanks. assuming all tanks are equally full which is ensured by design ("communicating tubes")
				}
				else
				{
					// do not calculate the volume in liters b/c neccessary geometry data of tank array is not present or because tank is literally just empty
					litersInTank = 0;
				}

				const uint16_t maxDifferenceFluidLevel = EEPROM_tankempty_cm - EEPROM_tankfull_cm;
				uint16_t percentage = (uint16_t)(((uint32_t)distanceHigherThanEmpty * (uint32_t)maxDifferenceFluidLevel)/100);
				percentage = MIN(100, percentage); // clamp to 100% in case the percentage ever gets calculated to more than 100% (maybe measurement was not exact?!)
				// all possible calculations performed --> now build up display content
				
				/*
					 0123456789ABCDEF
					------------------
					|xxxcm   XXXXXLtr| 
					|XXX %   X.XX V  |
					------------------
					assumes that the maximum distance will fit in 3 digits ie 999cm (should suffice)
					assumes that the maximum amount of liters will fit in 5 digits ie 99999 L (hundred thousand Litres) --> will suffice
					assumes that percentage fits in 3 digits (max is 100 so will suffice)
					assumes that voltage fits in 1 digit + 2 decimal places given that a 9V primary cell is used that will suffice
				*/

				char distanceToBeDisplayed[10]; 
				char litersToBeDisplayed[10];
				char percentageToBeDisplayed[10];
				char voltageToBeDisplayed[10];

				ultoa(distanceHigherThanEmpty, &distanceToBeDisplayed[0], 10); // base 10
				ultoa(litersInTank, &litersToBeDisplayed[0], 10);
				ultoa(percentage, &percentageToBeDisplayed[0],10);
				ultoa(measuredBatVoltage, &voltageToBeDisplayed[0],10);
				
				const char * cm = "cm   ";
				const char * l = "Ltr";
				const char * percentSignAndSpaces = " %   ";

				const char vtg[] = {
										voltageToBeDisplayed[0],
										'.',
										voltageToBeDisplayed[1],
										voltageToBeDisplayed[2],
										 ' ',
										 'V'
									};

				Disp_init();
				Disp_printStringRightAligned(distanceToBeDisplayed,3);
				Disp_printString(cm, 5);
				Disp_printStringRightAligned(litersToBeDisplayed, 5);
				Disp_printString(l,3);

				Disp_sendInstruction(DisplayInstruction_setDDRAMAddress,0x40); // 0x40 is start of 2nd line

				Disp_printStringRightAligned(percentageToBeDisplayed, 3);
				Disp_printString(percentSignAndSpaces, 5);

				Disp_printString(vtg, 6);

				// disable everything used for measurement
				// then goto low sleep state until timer interrupt triggers for transition to sleepdisplayoff
				ADC_disable();
				GPIO_setVBatMeasEn_to(false);
				GPIO_setSensSupP_to(false); 
				GPIO_setSensSupM_to(false);

				PWR_setSlowestClockSpeed(); // switch to lowest speed ie 32khz
				Timer_init();
				sei();

				systemState = systemState_sleepDisplayOn; // everything has been done already and is sent to the display -- there is no reason for the mcu to remain active anymore. but keep display on for reading the output
			}
		}
		break;
		case systemState_sleepDisplayOn:
		{
			set_sleep_mode(SLEEP_MODE_IDLE); // wakeup by timer2
			sleep_enable();
			sleep_cpu();
			sleep_disable();
			// we only get here by getting woken up by timer2 to denote that the display on time has elapsed
			// leaving the sleep with display on state so the display should be disabled too
			// disable all used peripherals, disable the display and go to deep sleep state until woken up by button press
			GPIO_setDPins_to(0);
			DDRB = 0; // all datalines to input before turning off the display
			DDRD &= ~((1<<4)|(1<<5)); // rw and en also to input before turning off the display
			DDRA &= ~(1<<1); // rs to input before turning off the display
			//GPIO_setDispEn_to(false);
			DDRD |= 1<<6;
			PORTD &= ~(1<<6);
			PWR_disableUsedPeripherals();
			Exti_init(); // only initialize the interrupt for the wakeup button if the next step is not the parametrization state (but rather the display off state since otherwise the interupt is not needed)
			Timer_deinit();
			sei(); // should technically be redundant
			systemState = systemState_sleepDisplayOff;
		}
		break;
		case systemState_sleepDisplayOff:
		{
			set_sleep_mode(SLEEP_MODE_PWR_DOWN);
			sleep_enable();
			sleep_cpu();
			sleep_disable(); 

			// once we get here we were woken up by the button being pressed...
			// thus transition to measure state is needed
			// leaving the sleep state ie the button has been pressed
			// enable all used peripherals, enable the measurement circuitries
			Exti_deinit();
			PWR_setNormalClockSpeed(); // once the mcu gets woken up again a new measurement and display cycle starts and requires the full 8mhz
			GPIO_init(); // full reinit of all pins to their default configuration to ensure that the display pins are also set to correct configuration because they need to be inputs before the display can be turned off...
			PWR_enableUsedPeripherals();
			GPIO_setVBatMeasEn_to(true); 
			ADC_init(); // initialize the ADC to ensure the bat voltage can be measured before any fluid level measurement is taken
			systemState = systemState_measure; 
		}
		break;
		case systemState_batLowFault:
		{
			cli();
			wdt_disable();
			GPIO_setVBatMeasEn_to(false);
			GPIO_setDispEn_to(false); 
			GPIO_setSensSupM_to(false);
			GPIO_setSensSupP_to(false); // effectively short the supply pins for the external sensor together causing the thing to be not powered
			ADC_disable(); // disable the adc before the ADC peripheral clock is disabled to ensure that the ADC analog part does not draw power from the analog supply pin. 
			PWR_disableAllPeripherals();
			PWR_setSlowestClockSpeed();
			sleep_enable();
			set_sleep_mode(SLEEP_MODE_PWR_DOWN);// deepest sleep mode that can only be left by interrupt, wdt, or power on reset
			// wdt is disabled by fuse, interrupts are disabled so only power on remains
			sleep_cpu(); // get stuck in powerdown sleep mode because battery voltage is low
			sleep_disable(); // should not be reachable
		}
		break;
		case systemState_parametrization:
		{
			if(uart0Handle.readByteIndexReceiveBuffer != uart0Handle.freeByteIndexReceiveBuffer)
			{
				// unprocessed data from parametrization tool / PC
				if(USART_getReceivableBytes() >= PARAMETRIZATION_REQUEST_SIZE - 1)
				{
					uint8_t requestBuffer[PARAMETRIZATION_REQUEST_SIZE] = {0};
					bool receiveRequestResult = true;
					for(uint8_t i=0;i<PARAMETRIZATION_REQUEST_SIZE;i++)
					{
						usartReceiveResult_t result = USART_Receive();
						if(result.wasSuccessful == true)
						{
							requestBuffer[i] = result.dataByte;
						}
						else
						{
							// should not have happened by design... 
							receiveRequestResult = false;
						}
					}
					if(receiveRequestResult == true)
					{
						// receive successful --> check if ill formed --> interpret if not
						if(
								(requestBuffer[0] != ':') // bad start character
							  ||(
									  (requestBuffer[1] != 'w') // not a write indicator
									&&(requestBuffer[1] != 'q') // not a quit indicator
									&&(requestBuffer[1] != 'r') // not a read indicator either --> bad indicator
								)
							  ||(
									  (requestBuffer[1] == 'r')
									&&(requestBuffer[4] != 0x00)
									&&(requestBuffer[5] != 0x00) // read request but data field not padded.
							    )
							  ||(
									  (requestBuffer[1] == 'q')
								    &&(requestBuffer[2] != 0x00)
								    &&(requestBuffer[3] != 0x00)
								    &&(requestBuffer[4] != 0x00)
								    &&(requestBuffer[5] != 0x00) // quit request but address and data field not padded. strictly not needed but prevents to access unwritten buffer contents because the num of bytes read from the buffer is static
								)
							// ^^^  vim user confirmed ^^ 
						  )
					  {
						  //  ill-formed --> ignore
					  }
					  else
					  {
						  // well formed --> interpret
						  // get address and data fields first
						  uint16_t address = (((uint16_t)requestBuffer[2]) << 8) | (requestBuffer[3]); // msb first
						  //uint16_t datafield = (((uint16_t)requestBuffer[4]) << 8) | (requestBuffer[5]); // msb first -- but not needed as variable
						  char responseBuffer[PARAMETRIZATION_RESPONSE_SIZE+1] = {0};

						  switch(requestBuffer[1]) // what command type?
						  {
							  case 'q': 
							  {
								  // request to end the parametrization session, write the values to the eeprom and then leave the session --> go to boot state next since the statechain is best tested from there
								  EEPROM_syncToEEPROM();
								  systemState = systemState_boot;
							  } 
							  break;

							  case 'w':
							  {
								  responseBuffer[0] = ':'; // same start character as in request
								  responseBuffer[1] = 'W'; // uppercase W for positive response to write
								  switch(address)
								  {
										case ADDR_TANKFULL_CM:
										{
											responseBuffer[2] = HIGHBYTE_OF(ADDR_TANKFULL_CM);
											responseBuffer[3] = LOWBYTE_OF(ADDR_TANKFULL_CM);
											EEPROM_tankfull_cm = 0; // preclear
											EEPROM_tankfull_cm |= (((uint16_t)requestBuffer[4]) << 8);
											EEPROM_tankfull_cm |= (((uint16_t)requestBuffer[5]) << 0);
										}
										break;
										case ADDR_TANKEMPTY_CM:
										{
											responseBuffer[2] = HIGHBYTE_OF(ADDR_TANKEMPTY_CM);
											responseBuffer[3] = LOWBYTE_OF(ADDR_TANKEMPTY_CM);
											EEPROM_tankempty_cm = 0;
											EEPROM_tankempty_cm |= (((uint16_t)requestBuffer[4]) << 8);
											EEPROM_tankempty_cm |= (((uint16_t)requestBuffer[5]) << 0);
										}
										break;
										case ADDR_NUM_OF_TANKS_IN_PARALELL:
										{
											responseBuffer[2] = HIGHBYTE_OF(ADDR_NUM_OF_TANKS_IN_PARALELL);
											responseBuffer[3] = LOWBYTE_OF(ADDR_NUM_OF_TANKS_IN_PARALELL);
											EEPROM_numOfTanks = requestBuffer[5]; // only lsb b/c 8bit value
										}
										break;
										case ADDR_AREA_ENTRIES_USED:
										{
											responseBuffer[2] = HIGHBYTE_OF(ADDR_AREA_ENTRIES_USED);
											responseBuffer[3] = LOWBYTE_OF(ADDR_AREA_ENTRIES_USED);
											EEPROM_areaEntriesUsed =  requestBuffer[5]; // only lsb b/c 8bit value
										}
										break;
										case ADDR_AREA_ENTRY_SPACING_CM:
										{
											responseBuffer[2] = HIGHBYTE_OF(ADDR_AREA_ENTRY_SPACING_CM);
											responseBuffer[3] = LOWBYTE_OF(ADDR_AREA_ENTRY_SPACING_CM);
											EEPROM_areaEntrySpacing = requestBuffer[5]; // only lsb b/c 8bit value
										}
										break;
										case ADDR_AVERAGING_SAMPLE_CNT:
										{
											responseBuffer[2] = HIGHBYTE_OF(ADDR_AVERAGING_SAMPLE_CNT);
											responseBuffer[3] = LOWBYTE_OF(ADDR_AVERAGING_SAMPLE_CNT);
											EEPROM_averagingSampleCnt = requestBuffer[5]; // only lsb b/c 8bit value
										}
										break;
										case ADDR_SENSOR_TYPE:
										{
											responseBuffer[2] = HIGHBYTE_OF(ADDR_SENSOR_TYPE);
											responseBuffer[3] = LOWBYTE_OF(ADDR_SENSOR_TYPE);
											EEPROM_sensorType = requestBuffer[5] & 0x01; // only ls-bit of lsb b/c 8bit variable and only 2 types defined
										}
										break;
										default:
										{
											// none of the fixed addresses, either entry in the area entry array or out of bounds
											if(
												  (address <= ADDR_AREA_ENTRY_0 + (EEPROM_areaEntriesUsed * AREA_ENTRY_SIZE))
												&&(
													  (ADDR_AREA_ENTRY_0 - address == 0) // first entry
													||(((ADDR_AREA_ENTRY_0 - address) % 2) == 0) // subsequent entry and correctly aligned
												  )
											  )
											{
												// in range and correctly aligned, get index in area entries array 
												uint8_t index = (ADDR_AREA_ENTRY_0 - address) / 2;

												responseBuffer[2] = HIGHBYTE_OF(address);
												responseBuffer[3] = LOWBYTE_OF(address);
												EEPROM_areaEntries[index] = 0;
												EEPROM_areaEntries[index] |= ((uint16_t)requestBuffer[4]) << 8;
												EEPROM_areaEntries[index] |= ((uint16_t)requestBuffer[5]) << 0;

											}
											else
											{
												for(uint8_t i=1;i<PARAMETRIZATION_RESPONSE_SIZE;i++)
												{
													responseBuffer[i] = 0xFF; // set the response type address and data to invalid value
												}
											}
										}
										break;
								  }
							  }
							  break;
							  case 'r':
							  {
								  responseBuffer[0] = ':'; // same start character as in request
								  responseBuffer[1] = 'R'; // uppercase R for positive response to read
								  switch(address)
								  {
										case ADDR_TANKFULL_CM:
										{
											responseBuffer[2] = HIGHBYTE_OF(ADDR_TANKFULL_CM);
											responseBuffer[3] = LOWBYTE_OF(ADDR_TANKFULL_CM);
											responseBuffer[4] = HIGHBYTE_OF(EEPROM_tankfull_cm);
											responseBuffer[5] = LOWBYTE_OF(EEPROM_tankfull_cm);
										}
										break;
										case ADDR_TANKEMPTY_CM:
										{
											responseBuffer[2] = HIGHBYTE_OF(ADDR_TANKEMPTY_CM);
											responseBuffer[3] = LOWBYTE_OF(ADDR_TANKEMPTY_CM);
											responseBuffer[4] = HIGHBYTE_OF(EEPROM_tankempty_cm);
											responseBuffer[5] = LOWBYTE_OF(EEPROM_tankempty_cm);
										}
										break;
										case ADDR_NUM_OF_TANKS_IN_PARALELL:
										{
											responseBuffer[2] = HIGHBYTE_OF(ADDR_NUM_OF_TANKS_IN_PARALELL);
											responseBuffer[3] = LOWBYTE_OF(ADDR_NUM_OF_TANKS_IN_PARALELL);
											responseBuffer[4] = 0; // 8bit value
											responseBuffer[5] = EEPROM_numOfTanks;
										}
										break;
										case ADDR_AREA_ENTRIES_USED:
										{
											responseBuffer[2] = HIGHBYTE_OF(ADDR_AREA_ENTRIES_USED);
											responseBuffer[3] = LOWBYTE_OF(ADDR_AREA_ENTRIES_USED);
											responseBuffer[4] = 0; // 8bit value
											responseBuffer[5] = EEPROM_areaEntriesUsed;
										}
										break;
										case ADDR_AREA_ENTRY_SPACING_CM:
										{
											responseBuffer[2] = HIGHBYTE_OF(ADDR_AREA_ENTRY_SPACING_CM);
											responseBuffer[3] = LOWBYTE_OF(ADDR_AREA_ENTRY_SPACING_CM);
											responseBuffer[4] = 0; // 8bit value
											responseBuffer[5] = EEPROM_areaEntrySpacing;
										}
										break;
										case ADDR_AVERAGING_SAMPLE_CNT:
										{
											responseBuffer[2] = HIGHBYTE_OF(ADDR_AVERAGING_SAMPLE_CNT);
											responseBuffer[3] = LOWBYTE_OF(ADDR_AVERAGING_SAMPLE_CNT);
											responseBuffer[4] = 0; // 8bit value
											responseBuffer[5] = EEPROM_averagingSampleCnt;
										}
										break;
										case ADDR_SENSOR_TYPE:
										{
											responseBuffer[2] = HIGHBYTE_OF(ADDR_SENSOR_TYPE);
											responseBuffer[3] = LOWBYTE_OF(ADDR_SENSOR_TYPE);
											responseBuffer[4] = 0; // 8bit value
											responseBuffer[5] = EEPROM_sensorType;
										}
										break;
										default:
										{
											// none of the fixed addresses, either entry in the area entry array or out of bounds
											if(
												  (address <= ADDR_AREA_ENTRY_0 + (EEPROM_areaEntriesUsed * AREA_ENTRY_SIZE))
												&&(
													  (ADDR_AREA_ENTRY_0 - address == 0) // first entry
													||(((ADDR_AREA_ENTRY_0 - address) % 2) == 0) // subsequent entry and correctly aligned
												  )
											  )
											{
												// in range and correctly aligned, get index in area entries array 
												uint8_t index = (ADDR_AREA_ENTRY_0 - address) / 2;

												responseBuffer[2] = HIGHBYTE_OF(address);
												responseBuffer[3] = LOWBYTE_OF(address);
												responseBuffer[4] = HIGHBYTE_OF(EEPROM_areaEntries[index]);
												responseBuffer[5] = LOWBYTE_OF(EEPROM_areaEntries[index]);
											}
											else
											{
												for(uint8_t i=1;i<PARAMETRIZATION_RESPONSE_SIZE;i++)
												{
													responseBuffer[i] = 0xFF; // set the response type address and data to invalid value
												}
											}
											
										}
										break;
										
								  }
							  }
							  break;
						  }
						  // command interpreted, action taken and response prepared --> send out response
					      while(uart0Handle.freeByteIndexTransmitBuffer != uart0Handle.readByteIndexTransmitBuffer)
						  {
							  // do not attempt to overrun the tx buffer but also do not ommit the prepared response --> wait for the tx buffer to free
						  }
						  responseBuffer[PARAMETRIZATION_RESPONSE_SIZE] = 0xff;
						  USART_Transmit(responseBuffer, PARAMETRIZATION_RESPONSE_SIZE+1);
					  }
					}
				}
			}
			else 
			{
				// nothing received yet or not received an entire request --> do not react on any received data yet
			}
		}
		break;
	}
}
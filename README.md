# README

##Intended Usecase
Waterlevel display in multitank battey of tanks. Tanks are located in basement, sense device will be mounted on top of tanks far enough away from filling port. 
Thus no watertightness or waterresistance is implemented for any of the components.

## Design Features
Multiple Sensorboards "supported" by design (read Mistakes#J5 for more).
Elaborate Liter-age estimation algorithm by approximation of tank geometry with multiple boxes of varying area, spacing of estimation-box-area-entries parametrizable (1 global value)
Remaining Tankgeometry (Distance when full, distance when empty, number of tanks) parametrizable. 
Measurement sample averaging with parametrizable sample count for general stability, reproducability and compensation of effects of surface-waves while filling (effectiveness not proven)
Sleep modes for powersaving: between user interactions (deepest possible sleep mode), for time that display is supposed to be on (deepest sleep mode that can be left by timer)
Parametrization via UART with ready made tool (Open protocol)

## Operating instructions
Connect battery without pressing the front panel button --> normal startup procedure; system will perform one measurement cycle and show the results on the display
Connect battery with pressed front panel button --> boot into parametrization mode; leave via UART command or powercycle

## Basic-most Troubleshooting 
### "Display stays dark on button press"
Disassembly of sense device, check battery voltage -- system will not attempt any measurements below 7V
When Battery Voltage >7V attempt powercycle (battery disconnect-reconnect)

## Parametrization protocol
### UART Specifics
9600Baud, 8bits, 1 stop bit, no parity
### Leaving the parametrization session
send ":q" (without quotes)
### write a memory location 
send ":wXXYY" where XX is the address in MSB first and YY is the value in MSB first (both 16bit); device will respond with ":WXX00" where XX is that same address and 00 is padding data.
### read a memory location
analogous to write except ":r" is to be used instead of ":w"; data will be in last two response bytes in 16bit MSBFirst
### Memory Map
TankFullCM         | 0x0000 | 2bytes
TankEmptyCM        | 0x0002 | 2bytes
NumTanks           | 0x0004 | 1byte
AreaEntryCount     | 0x0005 | 1byte
AreaEntrySpacingCm | 0x0006 | 1byte
AveragingCount     | 0x0007 | 1byte
SensorType         | 0x0008 | 1byte (0: HC-SR04, 1:Grove)
AreaEntrySpaceStart| 0x000A | 2bytes per entry

## Power Figures
To be powered from a 9V Block Battery. Active current (w/ Display on, sensor not attached) is ~15mA. 
The MCU will be in sleep just about the entire time. The current transient for the MCU being active is assumed to be neglegdable.
The current transient by the sensor has not been determined. But the sensor is powered from IO Pins and normally unpowered thus not adding to the Iq.
The current consumption in sleep (Display off, sensor disconnected, MCU sleep) was in the noise of the multimeter (readings are typical at ~1mV across 10R shunt experimentally put in place instead of regulator; ~100uA)

## Hacking features
Default values for liter estimation algorithm when activated by define but not configured in EEPROM.
Define for circumventing the Battery voltage measurement evaluation -- effectively rendering the BatteryLowFault State inoperable/unreachable.

## Mistakes 
### Q5
Reverse voltage Protection "Diode" Transistor (Q5) did not work in my testing.
Circumvent by placing a ordinary diode between pins 1 and 2 of the footprint.

### U2
Was not available to me at the time of building and pinning is unlike 117 or 78xx series regulator thus the device may be a bad pick when a generic jellybean part would be wanted. 
There is no special reason to use this one. 
Circumvent by either buying appropriate part or replace with 7805 mounted in reverse (smaller footprint one will work as current consumption of MCU and display when active is ~15mA in my measurement thus anysize regulator will likely be enough)

### J1
/tRST is connected to MCU but /sRST would be the one to use with standard AVR JTAG pinout. 
Circumvent by either using SPI which is available on the Display header or by shorting the /tRST and /sRST pins together.

### U1
ATmega1284P was initially designed in as it happened to be in my junkbox... later replaced with ATmega324PB as a cheaper more than plenty replacement.
The ATmega324PB is not exactly pin compatible as the two (1284P) supply pins on the bottom edge (17, 18) are IO pins on the 324PB.
Circumvent: none
Fix: new layout or stick with original design MCU. 
Impact: none as long as the SW does not configure the two pins as outputs (which it should not -- by design)

### V0
V0 had been planned to be connected to resistor divider for contrast setting (that is switch-off-able). But fixed 1k pull down would be enough.
Circumvent by not placing R13, R14, R11, Q3 and instead placing R12 as ~500R and placing another ~500R between pins 2 and 3 of Q3 (slight cant).
alternatively only place R12 as 1k and bridge pins 2 and 3 of Q3

### J5 
Pinning of header for Grove Ultrasonic rangefinder module is completely messed up w/ regard to the module. 
Circumvent: use a crossover wireharnes and / or change the pinning in as far as possible (supply pins). Possibly bridge pin 3 and 4 on J5 to fix switched signal and NC pin. 
alternatively stick with HC-SR04 board instead. 
Firmware side of things has not been verified for Grove module at all thus it may require some hacking to get working. 

### Q4 
Technically working how ever not sufficent for turning off the display. The display module will get its power also over the data and control lines if not powered thus setting all data and control lines to input-no-pullup before turning off the display is required.
Circumvent: not needed -- already accounted for in Firmware. 

## Issues
### Parametrization tool communication (General)
Send commands multiple times until a) the display lights up [stop session command] or b) message counter in log window in bottom updates
### Parametrization tool connection
Start the sense device in parametrization mode.
Send the stop command from the tool until successfully left the session. 
Keep the Tool running and connected to the UART to USB adapter.
Restart the sense device in parametrization mode. 
The communciation should now work -- signs of a non working communication are UI buttons not changing their animated state.
### Parametrization best practices
Send a value
set a different value
Read back value --> the UI element for setting doubles for display and should change value to before set value.

Always leave the parametrization session by stop command when values have been changed in order for the write to peristant memory to happen. 
# RC-Car-SelfDriving

Project for turning a regular RC car into a computer vision driven self driving one. 

Goals: 

1. Control car with arduino remotely 
2. Have car detect environment and parse it 
3. Avoid obstacles and navigate to a location 
4. Battle other cars? 

Maisto R/C Rock Crawler:
- Power: 6AA battery powered
- Transmittion: PS3 Controller (USB) -> (Keyes) USB Host Shield 2.0 -> Ardunio UNO (Processor) -> DK Electrics Motor Shield V1
- Control: DK Electrics Motor Shield V1 -> Two Motor (Driving) One Motor (Turning)

Ardunio Pin Usage (Digital 2-13):
- USB Host Shield 2.0 (8-13)
- DK Electric Motor Shield:  
      All 6 analog input pins are available. They can also be used as digital pins (pins #14 thru 19)  
      Digital pin 2, and 13 are not used.  
      The following pins are in use only if the DC/Stepper noted is in use:  
      Digital pin 11: DC Motor #1 / Stepper #1 (activation/speed control)  
      Digital pin 3: DC Motor #2 / Stepper #1 (activation/speed control)  
      Digital pin 5: DC Motor #3 / Stepper #2 (activation/speed control)  
      Digital pin 6: DC Motor #4 / Stepper #2 (activation/speed control)  
      The following pins are in use if any DC/steppers are used  
      Digital pin 4, 7, 8 and 12 are used to drive the DC/Stepper motors via the 74HC595 serial-to-parallel latch  
      The following pins are used only if that particular servo is in use:  
      Digitals pin 9: Servo #1 control  
      Digital pin 10: Servo #2 control  

DK Electric Motor Shield Controls (6 Motors Total):
- 2 Stepper Motors
- 4 Regular Motors

Legacy RC Power Config: 
-Lower Voltage -> Controller to power Radio & Logic, Turning Motor
-Higher Voltage -> 2 Driving Motors
-Controller uses Hbridge, accepts logic voltages regardless of battery voltage
-Transmition: 27 MHz Radio controlled -> Controller


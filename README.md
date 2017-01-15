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
- DK Electric Motor Shield ()

DK Electric Motor Shield Controls (6 Motors Total):
- 2 Stepper Motors
- 4 Regular Motors

Legacy RC Power Config: 
-Lower Voltage -> Controller to power Radio & Logic, Turning Motor
-Higher Voltage -> 2 Driving Motors
-Controller uses Hbridge, accepts logic voltages regardless of battery voltage
-Transmition: 27 MHz Radio controlled -> Controller

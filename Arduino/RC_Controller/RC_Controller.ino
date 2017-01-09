/*
 Example sketch for the PS3 USB library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <PS3USB.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
/* You can create the instance of the class in two ways */
PS3USB PS3(&Usb); // This will just create the instance
//PS3USB PS3(&Usb,0x00,0x15,0x83,0x3D,0x0A,0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printAngle;
uint8_t state = 0;

// Clockwise and counter-clockwise definitions
#define CW  0
#define CCW 1
 
// Motor definition
#define MOT_A 0
 
const byte PWMA = 11;
const byte DIRA = 13;
 
 
void setup()
{
  // All pins should be setup as outputs
  pinMode(PWMA, OUTPUT);
  pinMode(DIRA, OUTPUT); 
  // Initialize all pins as low
  digitalWrite(PWMA, LOW);
  digitalWrite(DIRA, LOW);

    Serial.begin(115200);
#if !defined(__MIPSEL__)
    while (!Serial)
        ; // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
    if (Usb.Init() == -1) {
        Serial.print(F("\r\nOSC did not start"));
        while (1)
            ; //halt
    }
    Serial.print(F("\r\nPS3 USB Library Started"));


}
void loop()
{
  // Drive motor A at various speeds, then stop.
//  moveMotor(MOT_A, CCW, 255);
//  delay(1000);
//  moveMotor(MOT_A, CW, 127);
  //delay(1000);
  stopMotor(MOT_A);
//  moveMotor(MOT_A, CW, 255);
//  delay(1000);
//  moveMotor(MOT_A, CCW, 127);
  
  Usb.Task();

    if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
      if (PS3.getAnalogButton(R2)) {
        Serial.print(F("\r\nR2: "));
        Serial.print(PS3.getAnalogButton(R2));
        moveMotor(MOT_A, CW, PS3.getAnalogButton(R2));

      }
    }
}

// moveMotor drives motor
void moveMotor(byte motor, byte dir, byte spd)
{
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
}
 
//stop motor
void stopMotor(byte motor)
{
  moveMotor(motor, 0, 0);
}


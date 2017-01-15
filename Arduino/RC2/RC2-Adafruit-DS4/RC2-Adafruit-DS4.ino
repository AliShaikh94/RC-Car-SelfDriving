// #include <PS4USB.h>
#include <PS4BT.h>
#include <AFMotor.h>
#include <usbhub.h>
// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like 

//PS4USB PS4(&Usb);
PS4BT PS4(&Btd);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;


// Motors 2,3, 4 work completely 
// Motor 1 has interference and only works with full power

// DC motors 2 and 3 blocks are connected to the forward and backwards motors 
AF_DCMotor DCMotor_2(2); 
AF_DCMotor DCMotor_3(3); 
AF_DCMotor DCMotor_4(4); 

void setup()
{

  //   Serial.begin(115200);
  // #if !defined(__MIPSEL__)
  //   while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  // #endif
  //   if (Usb.Init() == -1) {
  //     Serial.print(F("\r\nOSC did not start"));
  //     while (1); // Halt
  //   }
  //   Serial.print(F("\r\nPS4 USB Library Started"));
    Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));
  

}
void loop()
{

    Usb.Task();

    if (PS4.connected()) {

      if (PS4.getAnalogHat(RightHatX) > 137 || PS4.getAnalogHat(RightHatX) < 117) {
          int RightHatX_Value = PS4.getAnalogHat(RightHatX);
          Serial.print(F("\tRightHatX: "));
          Serial.print(PS4.getAnalogHat(RightHatX_Value));

          if(PS4.getAnalogHat(RightHatX) > 137) {
            DCMotor_4.run(BACKWARD);
            DCMotor_4.setSpeed(RightHatX_Value);
          }
          if(PS4.getAnalogHat(RightHatX) < 117) {
            DCMotor_4.run(FORWARD);
            DCMotor_4.setSpeed(255-RightHatX_Value);
          }
      }
      else {
        DCMotor_4.run(RELEASE);
      }
      // if (PS4.getButtonClick(RIGHT)) {
      //   Serial.print(F("\r\nRight"));
      //   PS4.setLed(Blue);

      //   DCMotor_4.run(FORWARD);
      //   DCMotor_4.setSpeed(200);

      // }
      // else if (PS4.getButtonClick(LEFT)) {
      //   Serial.print(F("\r\nLeft"));
      //   PS4.setLed(Green);

      //   DCMotor_4.run(BACKWARD);
      //   DCMotor_4.setSpeed(200);

      // }
      //  else {
      //   DCMotor_4.run(RELEASE);
      // }

      if (PS4.getAnalogButton(R2)) {   
        int R2_Value = PS4.getAnalogButton(R2);
        Serial.print(F("\r\nR2: "));
        Serial.print(R2_Value);

        DCMotor_2.run(BACKWARD);
        DCMotor_2.setSpeed(R2_Value);
        DCMotor_3.run(BACKWARD);
        DCMotor_3.setSpeed(R2_Value);
      }
      else if (PS4.getAnalogButton(L2)) {
        int L2_Value = PS4.getAnalogButton(L2);
        Serial.print(F("\r\nL2: "));
        Serial.print(L2_Value);
        DCMotor_2.run(FORWARD);
        DCMotor_2.setSpeed(L2_Value);  
        DCMotor_3.run(FORWARD);
        DCMotor_3.setSpeed(L2_Value);  
      }
      else {
        DCMotor_2.run(RELEASE);
        DCMotor_3.run(RELEASE);
      }
    }
}

#include <PS4USB.h>
#include <AFMotor.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
PS4USB PS4(&Usb);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;


AF_DCMotor DCMotor_2(2); 

void setup()
{

    Serial.begin(115200);

    

  #if !defined(__MIPSEL__)
    while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  #endif
    if (Usb.Init() == -1) {
      Serial.print(F("\r\nOSC did not start"));
      while (1); // Halt
    }
    Serial.print(F("\r\nPS4 USB Library Started"));

}
void loop()
{

    Usb.Task();

    if (PS4.connected()) {
      if (PS4.getAnalogButton(R2)) {   
        int R2_Value = PS4.getAnalogButton(R2);
        Serial.print(F("\r\nR2: "));
        Serial.print(R2_Value);

        DCMotor_2.run(FORWARD);
        DCMotor_2.setSpeed(R2_Value);  
      }
      else if (PS4.getAnalogButton(L2)) {
        int L2_Value = PS4.getAnalogButton(L2);
        Serial.print(F("\r\nL2: "));
        Serial.print(L2_Value);
        DCMotor_2.run(BACKWARD);
        DCMotor_2.setSpeed(L2_Value);  
        
      }
      else {
        DCMotor_2.run(RELEASE);
      }
    }
}

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
int pwm_a = 13; //PWM control for motor outputs 1 and 2 is on digital pin 3
int pwm_b = 4; //PWM control for motor outputs 3 and 4 is on digital pin 11
int dir_a = 12; //direction control for motor outputs 1 and 2 is on digital pin 12
int dir_b = 3; //direction control for motor outputs 3 and 4 is on digital pin 13
int val = 0; //value for fade

void setup()
{

  
    pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
    pinMode(pwm_b, OUTPUT);
    pinMode(dir_a, OUTPUT);
    pinMode(dir_b, OUTPUT);
    
    //analogWrite(pwm_a, 100);  //set both motors to run at (100/255 = 39)% duty cycle (slow)
    //analogWrite(pwm_b, 100);
  
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
 
//     forw();         //Set Motors to go forward Note : No pwm is defined with the for function, so that fade in and out works
    // fadein();       //fade in from 0-255
    // delay(1000);
//     forward();      //continue full speed forward
    // delay(1000);
    // fadeout();      //Fade out from 255-0
    // delay(1000);    //Wait one second

    // stopped();      // stop for 2 seconds
      //bstop();
    // delay(2000);

//     back();         //Set motors to revers. Note : No pwm is defined with the back function, so that fade in and out works
    // fadein();       //fade in from 0-255
    // delay(1000);
//     backward();     //full speed backward
    // delay(1000);
    // fadeout();      //Fade out from 255-0
    // delay(1000);
    Usb.Task();

    if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
      if (PS3.getAnalogButton(R2)) {
        Serial.print(F("\r\nR2: "));
        Serial.print(PS3.getAnalogButton(R2));
        digitalWrite(dir_b, HIGH); //Reverse motor direction, 1 high, 2 low
        analogWrite(pwm_b, PS3.getAnalogButton(R2));
      }
      else if (PS3.getAnalogButton(L2)) {
        Serial.print(F("\r\nL2: "));
        Serial.print(PS3.getAnalogButton(L2));
        digitalWrite(dir_b, LOW); //Reverse motor direction, 1 high, 2 low
        analogWrite(pwm_b, PS3.getAnalogButton(L2));
      }
      else {
        stopped();
      }
    }
}

/* Let's take a moment to talk about these functions. The forw and back functions are simply designating the direction the motors will turn once they are fed a PWM signal.
If you only call the forw, or back functions, you will not see the motors turn. On a similar note the fade in and out functions will only change PWM, so you need to consider
the direction you were last set to. In the code above, you might have noticed that I called forw and fade in the same grouping. You will want to call a new direction, and then
declare your pwm fade. There is also a stop function. 
*/

void forw() // no pwm defined
{ 
  digitalWrite(dir_a, HIGH);  //Reverse motor direction, 1 high, 2 low
  digitalWrite(dir_b, HIGH);  //Reverse motor direction, 3 low, 4 high  
}

void back() // no pwm defined
{
  digitalWrite(dir_a, LOW);  //Set motor direction, 1 low, 2 high
  digitalWrite(dir_b, LOW);  //Set motor direction, 3 high, 4 low
}

void forward() //full speed forward
{ 
  digitalWrite(dir_a, HIGH);  //Reverse motor direction, 1 high, 2 low
  digitalWrite(dir_b, HIGH);  //Reverse motor direction, 3 low, 4 high  
  analogWrite(pwm_a, 255);    //set both motors to run at (100/255 = 39)% duty cycle
  analogWrite(pwm_b, 255);
}

void backward() //full speed backward
{
  digitalWrite(dir_a, LOW);  //Set motor direction, 1 low, 2 high
  digitalWrite(dir_b, LOW);  //Set motor direction, 3 high, 4 low
  analogWrite(pwm_a, 255);   //set both motors to run at 100% duty cycle (fast)
  analogWrite(pwm_b, 255);
}

void stopped() //stop
{ 
  Serial.print(F("\r\nStopped"));
  digitalWrite(dir_a, LOW); //Set motor direction, 1 low, 2 high
  digitalWrite(dir_b, LOW); //Set motor direction, 3 high, 4 low
  analogWrite(pwm_a, 0);    //set both motors to run at 100% duty cycle (fast)
  analogWrite(pwm_b, 0); 
}

void fadein()
{ 
  // fade in from min to max in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) 
  { 
     // sets the value (range from 0 to 255):
    analogWrite(pwm_a, fadeValue);   
    analogWrite(pwm_b, fadeValue);    
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 
}

void fadeout()
{ 
  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) 
  { 
    // sets the value (range from 0 to 255):
    analogWrite(pwm_a, fadeValue);
    analogWrite(pwm_b, fadeValue);
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);  
}
}

void astop()                   //stop motor A
{
  analogWrite(pwm_a, 0);    //set both motors to run at 100% duty cycle (fast)
}

void bstop()                   //stop motor B
{ 
  analogWrite(pwm_b, 0);    //set both motors to run at 100% duty cycle (fast)
}



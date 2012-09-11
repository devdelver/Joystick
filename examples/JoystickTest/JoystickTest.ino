#include <Joystick.h>
#include <PushButton.h>
#include <Metro.h>

/*
  Test for Joystick module. 

  INSTRUCTIONS:
  1. Don't touch the joystick at start of running. The program will read the CENTER position at first update() method call.
  2. When the LED of Arduino board lights up, move the Joystick in all directions. This procedure
  is necessary for calibrate the joystick module.
  
= HARDWARE SETUP =
  Connect the follow pins:
  Arduino        Joystick
    A0   <------->  VRx
    A1   <------->  VRy
    D2   <------->  SW

 Tested in Arduino Nano V3.0 AVR ATmega328.  
 
= CHANGE LOG =
 version 1.0 - Initial release.
 
= CREDIT = 
 created by Sergio M C Figueiredo / September 2012.
 site: http://devdelver.com/blog/Category/arduino
 e-mail: sfigueiredo@devdelver.com

*/
  
int LED = 13;

Joystick joy(A0,A1,2);

Metro intervalo(1000,true);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  Serial.println("* Inicio *");
  
  pinMode(LED, OUTPUT);
  
  // Calibrate joystick procedure
  digitalWrite(LED, LOW);
  // The next call of update() method will get center value of axis. Don't touch the joystick.
  joy.update();
  digitalWrite(LED, HIGH);
  // LED13 lights to indicate time for calibration.
  // Is expected that the user move the joystick in all directions
  while (millis()<10000) {
    joy.update();
  }
  digitalWrite(LED, LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  joy.update(); // updates joysticks states

  int event=joy.getButtonEvent();
  if (event==PushButton::EV_PRESSED) {
    Serial.println("PRESSED");
  } else 
  if (event==PushButton::EV_LONG_PRESSED) {
     Serial.println("LONG PRESSED");
  }
  
  if (intervalo.check()) {
      Serial.print("\nX=");
      Serial.print(joy.X().value());
      if (joy.X().isAtCenter()) {
        Serial.print("[CENTER]");
      }
      Serial.print("\nY=");
      Serial.print(joy.Y().value());
      if (joy.Y().isAtCenter()) {
        Serial.print("[CENTER]");
      }
  }

}  



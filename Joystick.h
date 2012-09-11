/*
 * Header of Joystick Library for Arduino.
 *  
 * version 1.0
 *  
 * created by Sergio M C Figueiredo - September 2012
 * 
 * site: http://blog.devdelver.com/category/arduino
 * 
 * e-mail: sfigueiredo@devdelver.com
 * 
 */
#ifndef Joystick_h
#define Joystick_h

#include "PushButton.h"

/*
  JoyAxis class
*/

class JoyAxis {
  private:
     Metro interval;
     
	 int VRpin;
     int rawMin;
     int rawMax;
     int rawCentro;
     
  protected:
     int jvalue;
     int jmin;
     int jmax;
     int jcenter;

     JoyAxis(int VR_PIN);      
	 void update();
     void print();
     
     friend class Joystick;

  public:
       static const int CENTER_TOLERANCE=5;
    
	   int value();
	   int centerValue();
	   bool isAtCenter();
};

/*
  Joystick Module interface.
*/

class Joystick {
private:
	int ax;
	
protected:
	JoyAxis Xaxis, Yaxis;
	PushButton S;
  
public:
	Joystick(int VRx_PIN, int VRy_PIN, int switch_PIN); 
	
	void update();
	void print();
	   
	int getButtonEvent();
	JoyAxis X();
	JoyAxis Y();
};

#endif
/*
 * Implementation of Joystick Library for Arduino.
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
#include "Arduino.h"
#include "Joystick.h"

/*
 * Constructor of Joystick.
 * 
 * VRx_PIN - Analog pin
 * VRy_PIN - Analog pin
 * switch_PIN - Digital pin with PULLUP RESISTOR.
 * 
 */
Joystick::Joystick(int VRx_PIN, int VRy_PIN, int switch_PIN): Xaxis(VRx_PIN),Yaxis(VRy_PIN),S(switch_PIN) {
}

/*
 * Reads analog and switch pins and update the object state.
 */
void Joystick::update() {
  /*
   * Fazer duas leituras analogicas 
   * em curto espaco de tempo não é 
   * recomendado.
   * Por isso, a cada update(), leio
   * um eixo do joystick de cada vez. 
   */
  if (ax==0) {
	  Xaxis.update();
	  ax=1;
  } else {
	  Yaxis.update();
	  ax=0;
  }
  S.update();
}

/*
 * Print useful information at serial port (for debugging proporses)
 */
void Joystick::print() {
  Xaxis.print();
  Yaxis.print();
  S.print();
}

/*
 * Get and clears the last button event detected.
 * Use PushButtons constants to compare the returned value:
 * PushButton::EV_NONE  - No new events since last call;
 * PushButton::EV_PRESSED - The button was pressed with a short time;
 * PushButton::EV_LONG_PRESSED - The button was pressed for a long time (>1s);
 * 
 */
int Joystick::getButtonEvent() {
	return S.getEvent();
}

JoyAxis Joystick::X() {
	return Xaxis;
}

JoyAxis Joystick::Y() {
	return Yaxis;
}

JoyAxis::JoyAxis(int VR_PIN): interval(97,true) {
  VRpin=VR_PIN;
  rawCentro=0; // indica que o centro precisa ser estabelecido na primeira leitura.
}

/*
  Le os valores do Joystick, calibrando-o on-the-fly.
*/
void JoyAxis::update() {
	if (!interval.check()) {
	  return;
	}
	
	int rawValue = analogRead(VRpin);
	interval.reset();
	
	if (rawCentro==0) { // ainda não estabeleceu o valor do centro?
		rawCentro=rawValue; 
		rawMax=rawCentro+100;
		rawMin=rawCentro-100;
	}
	
    // record the maximum sensor value
    if (rawValue > rawMax) {
      rawMax = rawValue;
      jmax = map(rawMax,0,1023,0,255);
      jcenter = map(rawCentro, rawMin, rawMax, 0, 255);
    }

    // record the minimum sensor value
    if (rawValue < rawMin) {
      rawMin = rawValue;
      jmin = map(rawMin,0,1023,0,255);
      jcenter = map(rawCentro, rawMin, rawMax, 0, 255);
    }
	
  // apply the calibration to the sensor reading
  jvalue = map(rawValue, rawMin, rawMax, 0, 255);
  // in case the sensor value is outside the range seen during calibration
  jvalue = constrain(jvalue, 0, 255);
  
 }
 
void JoyAxis::print() {
  Serial.print("Joy[PIN]=");
  Serial.println(VRpin);  
  
  Serial.print("Joy[RAW_MIN]=");
  Serial.println(rawMin);  
  Serial.print("Joy[RAW_MAX]=");
  Serial.println(rawMax);  
  Serial.print("Joy[RAW_CENTRO]=");
  Serial.println(rawCentro);  

  Serial.print("Joy[MIN]=");
  Serial.println(jmin);  
  Serial.print("Joy[MAX]=");
  Serial.println(jmax);  
  Serial.print("Joy[CENTRO]=");
  Serial.println(jcenter);  
	
  Serial.print("Joy[VALUE]=");
  Serial.println(jvalue);    
}

/*
 * returns the value of  
 */
int JoyAxis::value() {
	return jvalue;
}

/*
 * Returns true if the Joystick is at center.  
 */
bool JoyAxis::isAtCenter() {
	return (jvalue>=(jcenter-CENTER_TOLERANCE)) && (jvalue<=jcenter+CENTER_TOLERANCE);
}
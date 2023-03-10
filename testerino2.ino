/* Encoder Library - TwoKnobs Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */
//#define ENCODER_USE_INTERRUPTS
#include <Encoder.h>

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder knobtrig(16, 17);
Encoder knobtime(18, 19);
Encoder knobvolt(20, 21);
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(9600);
//  attachInterrupt(16, isrTrigger, CHANGE);
//  attachInterrupt(18, isrTime, CHANGE);
//  attachInterrupt(20, isrVolt, CHANGE);
  
}

long positiontrig  = 5;
long positiontime = 5;
long positionvolt = 5;
long newTrig = 5;
long newTime = 5;
long newVolt = 5;


void loop() {
  //long newTrig, newTime, newVolt;
  cli();
  if (knobtrig.read() < 0){
    knobtrig.write(0);
  }
  if (knobtrig.read() > 9){
    knobtrig.write(9);
  }
  newTrig = knobtrig.read();
  
  if (knobtime.read() < 0){
    knobtime.write(0);
  }
  if (knobtime.read() > 9){
    knobtime.write(9);
  }
  newTime = knobtime.read();

  if (knobvolt.read() > 9){
    knobvolt.write(9);
  }
  if (knobvolt.read() < 0){
    knobvolt.write(0);
  }
  newVolt = knobvolt.read();

//  sei();
  if (newTrig != positiontrig || newTime != positiontime || newVolt != positionvolt) {
    if (newTrig == -1){
      newTrig = 0;
    }
    if (newTrig == 10){
      newTrig = 9;
    }
    if (newTime == -1){
      newTime = 0;
    }
    if (newTime == 10){
      newTime = 9;
    }
    if (newVolt == -1){
      newVolt = 0;
    }
    if (newVolt == 10){
      newVolt = 9;
    }
    Serial.print("trig = ");
    Serial.print(newTrig);
    Serial.print(", time = ");
    Serial.print(newTime);
    Serial.print(", volt = ");
    Serial.print(newVolt);
    Serial.println();
    positionvolt = newVolt;
    positiontime = newTime;
    positiontrig = newTrig;
  }
  sei();
}

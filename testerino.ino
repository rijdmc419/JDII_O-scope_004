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
}

long positiontrig  = 5;
long positiontime = 5;
long positionvolt = 5;

void loop() {
  long newTrig = 5;
  long newTime = 5;
  long newVolt = 5;
  //long newTrig, newTime, newVolt;
  //if (knobtrig.read() > 0 && knobtrig.read() < 9){
  newTrig = knobtrig.read();
  //}
  //if (newTime <= 9 && newTime >=0){
  newTime = knobtime.read();
  //}
  //if (positionvolt < 9 && positionvolt >0){
  newVolt = knobvolt.read();
  //}
  if (newTrig != positiontrig || newTime != positiontime || newVolt != positionvolt) {
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
}
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  /*
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    knobtrig.write(0);
    knobtime.write(0);
    knobvolt.write(0);
  }
} */

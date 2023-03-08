/* Rotary encoder with attachInterrupt
Counts pulses from an incremental encoder and put the result in variable counter. 
Taking also into account the direction and counts down when the rotor rotates in 
the other direction.
This code is used attachInterrupt 0 and 1 which are pins 2 and 3 moust Arduino.
For more information about attachInterrupt see:
http://arduino.cc/en/Reference/AttachInterrupt
 
created 2014
by Ben-Tommy Eriksen
https://github.com/BenTommyE/BenRotaryEncoder
 
*/

// Encoder connect to digitalpin 2 and 3 on the Arduino.

int encAState;
int encALastState;
int encBState;
int encBLastState;

int encA1State;
int encA1LastState;
int encB1State;
int encB1LastState;

volatile unsigned int countertime = 0;  //This variable will increase or decrease depending on the rotation of encoder
volatile unsigned int countervolt = 0;  //This variable will increase or decrease depending on the rotation of encoder
volatile unsigned int counter = 0;

void setup() {
  Serial.begin (9600);
 
  pinMode(2, INPUT);           // set pin to input
  pinMode(3, INPUT);           // set pin to input
  pinMode(4, INPUT);           // set pin to input
  pinMode(5, INPUT);           // set pin to input
  
  digitalWrite(2, HIGH);      
  digitalWrite(3, HIGH);  
  digitalWrite(4, HIGH);      
  digitalWrite(5, HIGH);

//reads initial state
  encALastState = digitalRead(2);
  encBLastState = digitalRead(5);
  encA1LastState = digitalRead(3);
  encB1LastState = digitalRead(4);
 
 
  //Setting up interrupt
  //A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
  //attachInterrupt(0, ai0, CHANGE);
  attachInterrupt(0, ai2, CHANGE);
  attachInterrupt(1, ai3, CHANGE);
  
  //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  //attachInterrupt(1, ai1, CHANGE);
}

void loop() {
  // Send the value of counter
  Serial.print ("timescale: ");
  Serial.print (countertime);
  Serial.print (" voltscale: ");
  Serial.println(countervolt);  
}

void ai0() {
  encAState = digitalRead(2);
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if(encAState != encALastState && encAState == 1){
    if(digitalRead(3) != encAState){
      counter++;
    }
  }
}

void ai1() {
  encBState = digitalRead(3);
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if(encBState != encBLastState && encBState == 0){
    if(digitalRead(2) != encBState){
      counter--;
    }
  }
}

void ai2(){
  cli();
  encAState = digitalRead(2);
  encBState = digitalRead(5);
  if (encAState != encALastState){
    if (encBState != encAState){
      if (countertime < 9){
      countertime ++;
      encALastState = encAState;
      }      
      sei();
    }
    else{
      if (countertime > 0){
      countertime --;
      encALastState = encAState;
      sei();
      }
    }    
  }  
}
void ai3(){
  cli();
  encA1State = digitalRead(3);
  encB1State = digitalRead(4);
  if (encA1State != encA1LastState){
    if (encB1State != encA1State){
      if (countervolt < 9){
      countervolt ++;
      encA1LastState = encA1State;
      }      
      sei();
    }
    else{
      if (countervolt > 0){
      countervolt --;
      encA1LastState = encA1State;
      sei();
      }
    }    
  }  
}
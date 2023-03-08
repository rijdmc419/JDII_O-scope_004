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

int encA2State;
int encA2LastState;
int encB2State;
int encB2LastState;

volatile unsigned int countertrig = 0;  //This variable will increase or decrease depending on the rotation of encoder
volatile unsigned int countertime = 0;  //This variable will increase or decrease depending on the rotation of encoder
volatile unsigned int countervolt = 0;  //This variable will increase or decrease depending on the rotation of encoder
volatile unsigned int counter = 0;

void setup() {
  Serial.begin (9600);
 
  pinMode(16, INPUT);           // set pin to input
  pinMode(17, INPUT);           // set pin to input
  pinMode(18, INPUT);           // set pin to input
  pinMode(19, INPUT);           // set pin to input
  pinMode(20, INPUT);           // set pin to input
  pinMode(21, INPUT);           // set pin to input
  
  digitalWrite(16, HIGH);      
  digitalWrite(17, HIGH);  
  digitalWrite(18, HIGH);      
  digitalWrite(19, HIGH);
  digitalWrite(20, HIGH);      
  digitalWrite(21, HIGH);

//reads initial state
  encALastState = digitalRead(17);
  encBLastState = digitalRead(16);
  encA1LastState = digitalRead(19);
  encB1LastState = digitalRead(18);
  encA2LastState = digitalRead(21);
  encB2LastState = digitalRead(20);
  

 
 
  //Setting up interrupt
  //A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
  //attachInterrupt(0, ai0, CHANGE);
  attachInterrupt(17, ai2, CHANGE);
  attachInterrupt(19, ai3, CHANGE);
  attachInterrupt(21, ai4, CHANGE);
  
  //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  //attachInterrupt(1, ai1, CHANGE);
}

void loop() {
  // Send the value of counter
  Serial.print ("triggerval: ");
  Serial.print (countertrig);
  Serial.print (" timescale: ");
  Serial.print (countertime);
  Serial.print (" voltscale: ");
  Serial.println(countervolt);  
}

void ai2(){
  cli();
  encAState = digitalRead(17);
  encBState = digitalRead(16);
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
  encA1State = digitalRead(19);
  encB1State = digitalRead(18);
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
void ai4(){
  cli();
  encA2State = digitalRead(21);
  encB2State = digitalRead(20);
  if (encA2State != encA2LastState){
    if (encB2State != encA2State){
      if (countertrig < 9){
      countertrig ++;
      encA2LastState = encA2State;
      }      
      sei();
    }
    else{
      if (countertrig > 0){
      countertrig --;
      encA2LastState = encA2State;
      sei();
      }
    }    
  }  
}
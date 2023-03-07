/* Based on Oleg Mazurov's code for rotary encoder interrupt service routines for AVR micros
   here https://chome.nerpa.tech/mcu/reading-rotary-encoder-on-arduino/
   and using interrupts https://chome.nerpa.tech/mcu/rotary-encoder-interrupt-service-routine-for-avr-micros/

   This example does not use the port read method. Tested with Nano and ESP32
   both encoder A and B pins must be connected to interrupt enabled pins, see here for more info:
   https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
*/

// Define rotary encoder pins
//#define ENC_A 3
//#define ENC_B 4
 #define outputA1 6
 #define outputB1 7
 #define outputA2 2
 #define outputB2 5
 #define outputA3 3
 #define outputB3 4

unsigned long _lastIncReadTime1 = micros(); 
unsigned long _lastDecReadTime1 = micros(); 
unsigned long _lastIncReadTime2 = micros(); 
unsigned long _lastDecReadTime2 = micros(); 
unsigned long _lastIncReadTime3 = micros(); 
unsigned long _lastDecReadTime3 = micros(); 
int _pauseLength = 25000;
int _fastIncrement = 10;
int lastCountertime = 0;
int lastCountervolt = 0;
int lastCountertrig = 0;

volatile int countertime = 0;
volatile int countervolt = 0;
volatile int countertrig = 0;


void setup() {

  // Set encoder pins and attach interrupts
  pinMode(outputA3, INPUT);
  pinMode(outputB3, INPUT);
  pinMode(outputA2, INPUT);
  pinMode(outputB2, INPUT);
  pinMode(outputA1, INPUT);
  pinMode(outputB1, INPUT);
  //attachInterrupt(digitalPinToInterrupt(ENC_A), read_encoder, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(ENC_B), read_encoder, CHANGE);

  // Start the serial monitor to show output
  Serial.begin(115200);
  Serial.println("start");
}

void loop(){
  read_encodertime();  
  read_encodervolt();
  read_encodertrig();
  

}

void read_encodertime() {
  // Encoder interrupt routine for both pins. Updates counter
  // if they are valid and have rotated a full indent
 
  static uint8_t old_AB1 = 3;  // Lookup table index
  static int8_t encval1 = 0;   // Encoder value  
  static const int8_t enc_states1[]  = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0}; // Lookup table

  old_AB1 <<=2;  // Remember previous state

  if (digitalRead(outputA3)) old_AB1 |= 0x02; // Add current state of pin A
  if (digitalRead(outputB3)) old_AB1 |= 0x01; // Add current state of pin B
  
  encval1 += enc_states1[( old_AB1 & 0x0f )];

  // Update counter if encoder has rotated a full indent, that is at least 4 steps
  if( encval1 > 3 ) {        // Four steps forward
    int changevalue = 1;
    //if((micros() - _lastIncReadTime1) < _pauseLength) {
    //  changevalue = _fastIncrement * changevalue; 
    //}
    _lastIncReadTime1 = micros();
    if (countertime < 9){
    countertime = countertime + changevalue;              // Update counter
    }
    encval1 = 0;
    
  }
  else if( encval1 < -3 ) {        // Four steps backward
    int changevalue = -1;
    //if((micros() - _lastDecReadTime1) < _pauseLength) {
    //  changevalue = _fastIncrement * changevalue; 
    //}
    _lastDecReadTime1 = micros();
    if (countertime > 0){
    countertime = countertime + changevalue;              // Update counter
    }
    encval1 = 0;
    
  }
  if (countertime != lastCountertime){
    Serial.print("timescale: ");
    Serial.println(countertime);
  }
  lastCountertime = countertime;   
} 

void read_encodervolt() {
  // Encoder interrupt routine for both pins. Updates counter
  // if they are valid and have rotated a full indent
 
  static uint8_t old_AB2 = 3;  // Lookup table index
  static int8_t encval2 = 0;   // Encoder value  
  static const int8_t enc_states2[]  = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0}; // Lookup table

  old_AB2 <<=2;  // Remember previous state

  if (digitalRead(outputA2)) old_AB2 |= 0x02; // Add current state of pin A
  if (digitalRead(outputB2)) old_AB2 |= 0x01; // Add current state of pin B
  
  encval2 += enc_states2[( old_AB2 & 0x0f )];

  // Update counter if encoder has rotated a full indent, that is at least 4 steps
  if( encval2 > 3 ) {        // Four steps forward
    int changevalue = 1;
    //if((micros() - _lastIncReadTime2) < _pauseLength) {
    //  changevalue = _fastIncrement * changevalue; 
    //}
    _lastIncReadTime2 = micros();
    countervolt = countervolt + changevalue;              // Update counter
    encval2 = 0;
  }
  else if( encval2 < -3 ) {        // Four steps backward
    int changevalue = -1;
    //if((micros() - _lastDecReadTime2) < _pauseLength) {
    //  changevalue = _fastIncrement * changevalue; 
    //}
    _lastDecReadTime2 = micros();
    countervolt = countervolt + changevalue;              // Update counter
    encval2 = 0;
  }
  if (countervolt != lastCountervolt){
    Serial.print("voltscale: ");
    Serial.println(countervolt);
  }
  lastCountervolt = countervolt;
} 

void read_encodertrig() {
  // Encoder interrupt routine for both pins. Updates counter
  // if they are valid and have rotated a full indent
 
  static uint8_t old_AB3 = 3;  // Lookup table index
  static int8_t encval3 = 0;   // Encoder value  
  static const int8_t enc_states3[]  = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0}; // Lookup table

  old_AB3 <<=2;  // Remember previous state

  if (digitalRead(outputA1)) old_AB3 |= 0x02; // Add current state of pin A
  if (digitalRead(outputB1)) old_AB3 |= 0x01; // Add current state of pin B
  
  encval3 += enc_states3[( old_AB3 & 0x0f )];

  // Update counter if encoder has rotated a full indent, that is at least 4 steps
  if( encval3 > 3 ) {        // Four steps forward
    int changevalue = 1;
    //if((micros() - _lastIncReadTime3) < _pauseLength) {
    //  changevalue = _fastIncrement * changevalue; 
    //}
    _lastIncReadTime3 = micros();
    countertrig = countertrig + changevalue;              // Update counter
    encval3 = 0;
  }
  else if( encval3 < -3 ) {        // Four steps backward
    int changevalue = -1;
    //if((micros() - _lastDecReadTime3) < _pauseLength) {
    //  changevalue = _fastIncrement * changevalue; 
    //}
    _lastDecReadTime3 = micros();
    countertrig = countertrig + changevalue;              // Update counter
    encval3 = 0;
  }
  if (countertrig != lastCountertrig){
    Serial.print("trig: ");
    Serial.println(countertrig);
  }
  lastCountertrig = countertrig;
} 

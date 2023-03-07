#include <ADC.h>
#include <ADC_util.h>
#include <stdlib.h>

//create timer object
IntervalTimer myTimer;
//create adc object
ADC *adc = new ADC();

void setup() {
  //configure adc0 for maximum sampling speed
  adc->adc0->setAveraging(0);
  adc->adc0->setResolution(8);
  adc->adc0->setConversionSpeed(ADC_CONVERSION_SPEED::HIGH_SPEED);
  adc->adc0->setSamplingSpeed(ADC_SAMPLING_SPEED::VERY_HIGH_SPEED);

  //configure adc1 for maximum sampling speed
  adc->adc1->setAveraging(0);
  adc->adc1->setResolution(8);
  adc->adc1->setConversionSpeed(ADC_CONVERSION_SPEED::HIGH_SPEED);
  adc->adc1->setSamplingSpeed(ADC_SAMPLING_SPEED::VERY_HIGH_SPEED);

  //start continiously sampling A0 and A1
  adc->startSynchronizedContinuous(A0, A1);
  //wait 100 microseconds to avoid possible errors with initial analog values
  delay(100);

  //start timer interrupt to call sendValues function every 1 microsecond
  myTimer.begin(sendValues, 1);

}
//declare variables
ADC::Sync_result result;
int voltage0, voltage1;
int prevVoltage0, prevVoltage1;
int trigger = 0;
int triggerVoltage = 0;
char valueArray[512];
int curIndex = 0;
int timeVal = 0;
int unsigned long prevTimeVal = 0;
int unsigned long curTimeVal = 0;

//variables for future encoder code
int voltScale = 3;
int timeScale = 6;
int triggerScale = 4;

//loop doing nothing
void loop() {

}

void sendValues(){
  //measures the time elapsed in microseconds since the last data sample
  curTimeVal = micros();
  timeVal = curTimeVal - prevTimeVal;
  prevTimeVal = curTimeVal;
  
  //reads both adc values
  result = adc->readSynchronizedContinuous();
  //stores current values to previous value variables, then overwrites current values to the new adc values
  prevVoltage0 = voltage0;
  prevVoltage1 = voltage1;
  voltage0 = result.result_adc0;
  voltage1 = result.result_adc1;

  //calculates the voltage value of the trigger line on the graph
  triggerVoltage = 3.3 * ((float)voltScale / 9) * ((float)triggerScale / 9);

  //determines if trigger has been set
  if((triggerVoltage <= voltage1) && (triggerVoltage > prevVoltage1)){
    trigger = 2;
  }else{
    trigger = 0;
  }

  //outputs the triggeer value to the front of the current data line in the array
  itoa(trigger, valueArray + curIndex * 12, 10);

  //places a space character after trigger in the array
  valueArray[curIndex * 12 + 1] = ' ';

  //loads voltage0 into the 512 byte value array, adding leading zeros if necessary
  if(voltage0 < 10){
    valueArray[curIndex * 12 + 2] = '0';
    valueArray[curIndex * 12 + 3] = '0';
    itoa(voltage0, valueArray + curIndex * 12 + 4, 10);
  }else if(voltage0 < 100){
    valueArray[curIndex * 12 + 2] = '0';
    itoa(voltage0, valueArray + curIndex * 12 + 3, 10);
  }else{
    itoa(voltage0, valueArray + curIndex * 12 + 2, 10);
  }

  //places a space character after voltage0 in the array
  valueArray[curIndex * 12 + 5] = ' ';

  //loads voltage1 into the 512 byte value array after the space, adding leading zeros if necessary
  if(voltage1 < 10){
    valueArray[curIndex * 12 + 6] = '0';
    valueArray[curIndex * 12 + 7] = '0';
    itoa(voltage1, valueArray + curIndex * 12 + 8, 10);
  }else if(voltage1 < 100){
    valueArray[curIndex * 12 + 6] = '0';
    itoa(voltage1, valueArray + curIndex * 12 + 7, 10);
  }else{
    itoa(voltage1, valueArray + curIndex * 12 + 6, 10);
  }

  //places a space character after voltage1 in the array
  valueArray[curIndex * 12 + 9] = ' ';

  //places timeVal into the value array after the second space
  itoa(timeVal, valueArray + curIndex * 12 + 10, 10);

  //ends the specific line in the array with a newline character
  valueArray[curIndex * 12 + 11] = '\n';

  //increments index
  curIndex = curIndex + 1;

  //sends the valueArray to the usb buffer and sets curIndex to 0 if the valueArray is full
  if(curIndex == 42){
      curIndex = 0;
      Serial.write(valueArray);
  }
}

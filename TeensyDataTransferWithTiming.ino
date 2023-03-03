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
char valueArray[512];
int curIndex = 0;
int timeVal = 0;

//currently unused variables
int voltScale = 3;
int timeScale = 6;
int triggerLevel = 4;

//loop doing nothing
void loop() {

}

void sendValues(){
  //measure the current time in microseconds
  timeVal = (micros() % 90) + 10;
  
  //reads both adc values
  result = adc->readSynchronizedContinuous();
  //stores both adc values
  voltage0 = result.result_adc0;
  voltage1 = result.result_adc1;

  //loads voltage0 into the 512 byte value array, adding leading zeros if necessary
  if(voltage0 < 10){
    valueArray[curIndex * 11] = '0';
    valueArray[curIndex * 11 + 1] = '0';
    itoa(voltage0, valueArray + curIndex * 11 + 2, 10);
  }else if(voltage0 < 100){
    valueArray[curIndex * 11] = '0';
    itoa(voltage0, valueArray + curIndex * 11 + 1, 10);
  }else{
    itoa(voltage0, valueArray + curIndex * 11, 10);
  }

  //places a space character after voltage0 in the array
  valueArray[curIndex * 11 + 3] = ' ';

  //loads voltage1 into the 512 byte value array after the space, adding leading zeros if necessary
  if(voltage1 < 10){
    valueArray[curIndex * 11 + 4] = '0';
    valueArray[curIndex * 11 + 5] = '0';
    itoa(voltage1, valueArray + curIndex * 11 + 6, 10);
  }else if(voltage1 < 100){
    valueArray[curIndex * 11 + 4] = '0';
    itoa(voltage1, valueArray + curIndex * 11 + 5, 10);
  }else{
    itoa(voltage1, valueArray + curIndex * 11 + 4, 10);
  }

  //places a space character after voltage1 in the array
  valueArray[curIndex * 11 + 7] = ' ';

  //places timeVal into the value array after the second space
  itoa(timeVal, valueArray + curIndex * 11 + 8, 10);

  //ends the specific line in the array with a newline character
  valueArray[curIndex * 11 + 10] = '\n';

  //increments index
  curIndex = curIndex + 1;

  //sends the valueArray to the usb buffer and sets curIndex to 0 if the valueArray is full
  if(curIndex == 46){
      curIndex = 0;
      Serial.write(valueArray);
  }
}

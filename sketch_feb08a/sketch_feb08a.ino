
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.println("Begin Printing");
  
}

void loop() {

  Serial.print("values: ");
  Serial.print(1);
  Serial.print(" ");
  Serial.print(1);
  Serial.print(" ");
  Serial.println(1);
  
  delay(5000);

  Serial.print("values: ");
  Serial.print(9);
  Serial.print(" ");
  Serial.print(9);
  Serial.print(" ");
  Serial.println(9);
  
  delay(5000);
  
  Serial.print("values: ");
  Serial.print(9);
  Serial.print(" ");
  Serial.print(9);
  Serial.print(" ");
  Serial.println(9);
}

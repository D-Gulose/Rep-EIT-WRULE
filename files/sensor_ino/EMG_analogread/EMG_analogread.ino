const  int  analogInPin = 26;//  analog  pin A0 , GPIO 26
int  sensorValue = 0;// value we want to plot

void  setup() {
  Serial.begin (9600);//    bits  per  second
  
}
  
void  loop() {
  
  sensorValue = analogRead(analogInPin);// read  the  analog  input
  Serial.println(sensorValue);// print  out the  value
  Serial.print(" ");
  delay (50);
}

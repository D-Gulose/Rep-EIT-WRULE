const int analogInPin1 = 25; // analog pin A1, GPIO 25
const int analogInPin2 = 34; // analog pin A2, GPIO 34
const int analogInPin3 = 39; // analog pin A3, GPIO 39
const int analogInPin4 = 36; // analog pin A4, GPIO 36
int sensorValue1 = 0; // value we want to plot
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;

void  setup() {
  Serial.begin (9600);//    bits  per  second
  
}
  
void loop() {
sensorValue1 = analogRead(analogInPin1); // read the analog input
sensorValue2 = analogRead(analogInPin2);
sensorValue3 = analogRead(analogInPin3);
sensorValue4 = analogRead(analogInPin4);
Serial.print(sensorValue1); // print out the value
Serial.print(",");
Serial.print(sensorValue2);
Serial.print(",");
Serial.print(sensorValue3);
Serial.print(",");
Serial.println(sensorValue4);
delay(50);
}

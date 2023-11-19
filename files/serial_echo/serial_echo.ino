int incomingByte = 0;    // for incoming serial data

void setup() {
    Serial.begin(9600);    // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
  
    // read the incoming byte:
    //incomingByte = Serial.read();
    String command = Serial.readStringUntil('\n'); // read string until newline character
  
    // say what you got:
    // Serial.print((char)incomingByte);
    Serial.println(command);
  }

  //Serial.println("sending");
  delay(100);
  
}
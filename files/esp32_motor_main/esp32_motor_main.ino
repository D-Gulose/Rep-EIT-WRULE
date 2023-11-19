/*
 * Brief description
 * 
 */

#include <ESP32Servo.h>

Servo myservo;

#define SERVO_PIN 12

double posServo = 0;
double posServo1 = 2100; //0


double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup()
{
  Serial.begin(512000);
  pinMode(SERVO_PIN, OUTPUT);
  myservo.attach(SERVO_PIN); // PWM pin
  delay(1000);
  
}

void loop()
{
  while(!Serial.available());
  posServo=Serial.readString().toInt(); 
  double angle = mapf(0.785398, 0.0,1.570796, posServo1, posServo); 
  myservo.writeMicroseconds(angle);
  Serial.print(posServo);
}
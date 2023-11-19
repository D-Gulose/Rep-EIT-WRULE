/*
 * Brief description
 * 
 */

#include <ESP32Servo.h>

Servo myservo;

#define SERVO_PIN 13

double posServo1 = 2100; //0
double posServo2 = 1160; //90

double toggle = true; 

double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup()
{
  pinMode(SERVO_PIN, OUTPUT);
  
  myservo.attach(SERVO_PIN); // PWM pin
  delay(1000);
  Serial.print("test setup..");
  
}

void loop()
{
  Serial.print("loop setup..");
  if(toggle){
    double angle = mapf(0.0, 0.0,1.570796, posServo1, posServo2);
    myservo.writeMicroseconds(angle);
    toggle = false;
  }
  else{
    double angle = mapf(0.785398, 0.0,1.570796, posServo1, posServo2); 
    myservo.writeMicroseconds(angle);
    toggle = true;
  }
  
  
  delay(1000);
}

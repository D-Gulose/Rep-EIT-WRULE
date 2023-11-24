/*
 * Brief description
 * 
 */

#include <ESP32Servo.h>

Servo myservo;

#define SERVO_PIN 12

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
}

void loop()
{ 
  if(toggle){
    double angle = mapf(0.0, 0.0, 3.141592, posServo1, posServo2);
    myservo.writeMicroseconds(angle*2);
    toggle = false;
  }
  else{
    double angle = mapf(1.5707, 0.0, 3.141592, posServo1, posServo2); 
    myservo.writeMicroseconds(angle*2);
    toggle = true;
  }
  delay(1000);
  
  
}

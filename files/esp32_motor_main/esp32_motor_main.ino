/*
 * Brief description
 * 
 */

#include <ESP32Servo.h>

Servo myservo;

#define SERVO_PIN 12

double posServo1 = 0; //0
double posServo2 = 1182; //90 (with gear transmission)
double x;
int arr;

int mn=30;
int mx=120;

double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double calibration(double x, double from_min, double from_max, double to_min, double to_max)
{
    return (to_max - to_min) / (from_max - from_min) * (x - from_min)+ to_min;
}


void setup()
{
  Serial.begin(512000);
  pinMode(SERVO_PIN, OUTPUT);
  // myservo.attach(SERVO_PIN); // PWM pin
  delay(1000);
  
}

void loop()
{
  while(!Serial.available());
  arr=Serial.readString().toInt();
  if ((arr < mn) || (arr > mx))
  {
    myservo.detach();
    Serial.print("Servo detached");
  }
  else
  {
    double arr_map=calibration(arr, mn, mx, 0, 180);
    myservo.attach(SERVO_PIN);
    x = arr_map * 3.1415926 / 180.0;
    double angle = mapf(x, 0.0,1.570796, posServo1, posServo2); 
    myservo.writeMicroseconds(angle); 
    Serial.print(x);
  }
  

}

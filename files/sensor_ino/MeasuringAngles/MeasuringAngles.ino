#include <Wire.h>
#include <ICM20948_WE.h>
#define ICM20948_ADDR 0x69

ICM20948_WE myIMU = ICM20948_WE(ICM20948_ADDR);

// I2C pins
#define I2C_SDA 23
#define I2C_SCL 22

void setup() {
  Wire.begin(I2C_SDA, I2C_SCL);
  Serial.begin(512000);
  myIMU.init();
  
  myIMU.setAccOffsets(-16330.0, 16450.0, -16600.0, 16180.0, -16520.0, 16690.0);
    
  Serial.println("Position your ICM20948 flat and don't move it - calibrating...");
  delay(1000);
  myIMU.autoOffsets();
  Serial.println("Done!"); 
  
  //enables or disables the acceleration sensor, dafault: enabled 
  myIMU.enableAcc(true);

  myIMU.setAccRange(ICM20948_ACC_RANGE_2G);
  
  myIMU.setAccDLPF(ICM20948_DLPF_6);    

  // divides the output of the accelerometer
  myIMU.setAccSampleRateDivider(10);
}

void loop() {
  myIMU.readSensor();
  xyzFloat gValue = myIMU.getGValues();
  xyzFloat angle = myIMU.getAngles();
  float pitch = myIMU.getPitch();
  float roll  = myIMU.getRoll();
 
  Serial.println("G values (x,y,z):");
  Serial.print(gValue.x);
  Serial.print("   ");
  Serial.print(gValue.y);
  Serial.print("   ");
  Serial.println(gValue.z);
  Serial.println("Angles (x,y,z):");
  Serial.print(angle.x);
  Serial.print("   ");
  Serial.print(angle.y);
  Serial.print("   ");
  Serial.println(angle.z);
  Serial.print("Orientation of the module: ");
  Serial.println(myIMU.getOrientationAsString());

  Serial.print("Pitch = "); 
  Serial.print(pitch); 
  Serial.print("  |  Roll = "); 
  Serial.println(roll); 
  
  Serial.println();
  Serial.println();

  delay(500);
}

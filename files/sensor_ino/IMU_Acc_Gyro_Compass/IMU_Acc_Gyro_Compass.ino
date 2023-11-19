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
  myIMU.setGyrOffsets(-115.0, 130.0, 105.0);
    
  Serial.println("Position your ICM20948 flat and don't move it - calibrating...");
  delay(1000);
  myIMU.autoOffsets();
  Serial.println("Done!"); 

  myIMU.enableAcc(true);

  myIMU.enableGyr(true);
  
  myIMU.setAccRange(ICM20948_ACC_RANGE_2G);
  
  myIMU.setAccDLPF(ICM20948_DLPF_6);    
  
  myIMU.setAccSampleRateDivider(10);
  
  myIMU.setGyrRange(ICM20948_GYRO_RANGE_250);
  
  myIMU.setGyrDLPF(ICM20948_DLPF_6);  

  myIMU.setGyrSampleRateDivider(10);

  myIMU.setMagOpMode(AK09916_CONT_MODE_20HZ);
}

void loop() {
  myIMU.readSensor();
  xyzFloat gValue = myIMU.getGValues();
  xyzFloat gyr = myIMU.getGyrValues();
  // returns magnetic flux ensity [µT]
  xyzFloat magValue = myIMU.getMagValues();
  float resultantG = myIMU.getResultantG(gValue);

  // For g-values the corrected raws are used
  Serial.println("Acceleration in g (x,y,z):");
  Serial.print(gValue.x);
  Serial.print("   ");
  Serial.print(gValue.y);
  Serial.print("   ");
  Serial.println(gValue.z);
  // The resulting acceleration from a g-value triple:
  // The absolute value of the sum of the three vectors
  Serial.print("Resultant g: ");
  Serial.println(resultantG);

  Serial.println("Gyroscope data in degrees/s: ");
  Serial.print(gyr.x);
  Serial.print("   ");
  Serial.print(gyr.y);
  Serial.print("   ");
  Serial.println(gyr.z);

  Serial.println("Magnetometer Data in µTesla: ");
  Serial.print(magValue.x);
  Serial.print("   ");
  Serial.print(magValue.y);
  Serial.print("   ");
  Serial.println(magValue.z);

  Serial.println("********************************************");

  delay(500);
}

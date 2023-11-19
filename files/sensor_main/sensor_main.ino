#include <Wire.h>
#include <ICM20948_WE.h>
#define ICM20948_ADDR 0x69

const int analogInPin0 = 26;//  EMG analog  pin A0 , GPIO 26
const int analogInPin1 = 25;//  EMG analog  pin A1 , GPIO 25

const int analogInPin2 = 34; // analog pin A2, GPIO 34
const int analogInPin3 = 39; // analog pin A3, GPIO 39
const int analogInPin4 = 36; // analog pin A4, GPIO 36
const int analogInPin5 = 4; // analog pin A5, GPIO 4

int sensorValue0 = 0;// EMG value we want to plot
int sensorValue1 = 0;// EMG value we want to plot

int sensorValue2 = 0; // FSR value 2 we want to plot
int sensorValue3 = 0; // FSR value 3 we want to plot
int sensorValue4 = 0; // FSR value 4 we want to plot
int sensorValue5 = 0; // FSR value 5 we want to plot

ICM20948_WE myIMU = ICM20948_WE(ICM20948_ADDR); // IMU object
// IMU Gyro&Angles I2C pins
#define I2C_SDA 23
#define I2C_SCL 22

void setup() {
  // IMU
  Wire.begin(I2C_SDA, I2C_SCL);
  Serial.begin(512000); // bits  per  second
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

  // to configure
  myIMU.setGyrRange(ICM20948_GYRO_RANGE_250);
  
  myIMU.setGyrDLPF(ICM20948_DLPF_6);  

  myIMU.setGyrSampleRateDivider(10);

  myIMU.setMagOpMode(AK09916_CONT_MODE_20HZ);
}

void loop() {
  sensorValue0 = analogRead(analogInPin0);// read the analog input for EMG Value
  Serial.print("emg_raw: ");
  Serial.print(sensorValue0);// print out the value
  Serial.print("   ");
  sensorValue1 = analogRead(analogInPin1);// read the analog input for EMG Value
  Serial.print("emg_envelop: ");
  Serial.println(sensorValue1);// print out the value
  
  sensorValue2 = analogRead(analogInPin2); // read the analog input for FSR Value 2
  sensorValue3 = analogRead(analogInPin3); // read the analog input for FSR Value 3
  sensorValue4 = analogRead(analogInPin4); // read the analog input for FSR Value 4
  sensorValue5 = analogRead(analogInPin5); // read the analog input for FSR Value 5
  
  Serial.print("FSR_black: ");
  Serial.print(sensorValue2); // print out the value
  Serial.print("   FSR_red: ");
  Serial.print(sensorValue3);
  Serial.print("   FSR_green: ");
  Serial.print(sensorValue4);
  Serial.print("   FSR_yellow: ");
  Serial.println(sensorValue5);
  delay(50);
  
  // IMU Gyro Compass
  myIMU.readSensor();
  xyzFloat gValue = myIMU.getGValues();
  xyzFloat gyr = myIMU.getGyrValues();
  xyzFloat angle = myIMU.getAngles();
  xyzFloat magValue = myIMU.getMagValues(); // returns magnetic flux density [µT]
  float resultantG = myIMU.getResultantG(gValue);
  float pitch = myIMU.getPitch();
  float roll  = myIMU.getRoll();
  
  // For g-values, the corrected raws are used
  Serial.println("Acceleration in g: ");
  Serial.print("   (");
  Serial.print(gValue.x);
  Serial.print(", ");
  Serial.print(gValue.y);
  Serial.print(", ");
  Serial.print(gValue.z);
  Serial.println(")");
  
  Serial.println("Angles: ");
  Serial.print("   (");
  Serial.print(angle.x);
  Serial.print(", ");
  Serial.print(angle.y);
  Serial.print(", ");
  Serial.print(angle.z);
  Serial.println(")");
  
  Serial.print("Orientation of the module: ");
  Serial.println(myIMU.getOrientationAsString());
  
  Serial.print("Pitch = "); 
  Serial.print(pitch); 
  Serial.print("  |  Roll = "); 
  Serial.println(roll); 
  
  // The resulting acceleration from a g-value triple:
  // The absolute value of the sum of the three vectors
  Serial.print("Resultant g: ");
  Serial.println(resultantG);
  
  Serial.println("Gyroscope data in degrees/s: ");
  Serial.print("   (");
  Serial.print(gyr.x);
  Serial.print(", ");
  Serial.print(gyr.y);
  Serial.print(", ");
  Serial.print(gyr.z);
  Serial.println(")");
  
  Serial.println("Magnetometer Data in µTesla: ");
  Serial.print("   (");
  Serial.print(magValue.x);
  Serial.print(", ");
  Serial.print(magValue.y);
  Serial.print(", ");
  Serial.print(magValue.z);
  Serial.println(")");
  
  Serial.println("********************************************");

  delay(500);
}

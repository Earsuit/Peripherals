#include "spdlog/spdlog.h"
#include <unistd.h>
#include <iostream>

//MPU9250
#define MPU9250_AD (uint8_t)0x69
#define FIFO_EN_AD (uint8_t)0x23
#define PWR_MGMT_1_AD (uint8_t)0x6B
#define ACCEL_XOUT_H_AD (uint8_t)0x3B
#define GYRO_XOUT_H_AD (uint8_t)0x43
#define EXT_SENS_DATA_00_AD (uint8_t)0x49
#define ACCEL_CONFIG_1_AD (uint8_t)0x1C
#define ACCEL_CONFIG_2_AD (uint8_t)0x1D
#define GYRO_CONFIG_AD (uint8_t)0x1B
#define CONFIG_AD (uint8_t)0x1A
#define I2C_MST_CTRL_AD (uint8_t)0x24
#define I2C_SLV0_ADDR_AD (uint8_t)0x25
#define I2C_SLV0_REG_AD (uint8_t)0x26
#define I2C_SLV0_CTRL_AD (uint8_t)0x27
#define INT_BYPASS_CONFIG_AD (uint8_t)0x37
#define USER_CTRL_AD (uint8_t)0x6A
#define ACCEL_SENS 8192.0f
#define GYRO_SENS 131.0f

//Magnetometer
#define MAG_AD 0xC
#define WIA_AD 0x00
#define INFO 0x01
#define STATUS_1_AD 0x02
#define HXL_AD 0x03    //X-axis measurement data lower 8bit
#define HXH_AD 0x04    //X-axis measurement data higher 8bit
#define HYL_AD 0x05    //Y-axis measurement data lower 8bit
#define HYH_AD 0x06    //Y-axis measurement data higher 8bit
#define HZL_AD 0x07    //Z-axis measurement data lower 8bit
#define HZH_AD 0x08    //Z-axis measurement data higher 8bit
#define STATUS_2_AD 0x09
#define CNTL1_AD 0x0A   //control 1
#define CNTL2_AD 0x0B   //control 2
#define ASTC_AD 0x0C    //Self-Test Control
#define TS1_AD 0x0D    //test 1
#define TS2_AD 0x0E   //test 2
#define I2CDIS_AD 0x0F    //I2C disable
#define ASAX_AD 0x10    //Magnetic sensor X-axis sensitivity adjustment value
#define ASAY_AD 0x11    //Magnetic sensor Y-axis sensitivity adjustment value
#define ASAZ_AD 0x12    //Magnetic sensor Z-axis sensitivity adjustment value
#define MAGNE_SENS 6.67f
#define SCALE 0.1499f  // 4912/32760 uT/tick
#define DATA_READY 0x01
#define MAGIC_OVERFLOW 0x8

// void MPU9250Setup();
// void readGyro();

// volatile float accelX,accelY,accelZ,gyroX,gyroY,gyroZ,magneX,magneY,magneZ,asax,asay,asaz;
// BSC i2c;
// using std::cout;
// using std::endl;

namespace spd = spdlog;
int main(int argc,char* argv[]){
    // i2c.I2Csetup(100);
    // auto console = spd::stdout_color_mt("console");
    console->info("Welcome to spdlog!");
    // MPU9250Setup();
    // cout<<"here"<<endl;
    // sleep(10);
    // readGyro();
    // cout<<accelX<<endl;
    return 0;
}

// void MPU9250Setup(){
//     {uint8_t data[2] = {PWR_MGMT_1_AD,0x01};
//     i2c.write(MPU9250_AD,2,data);}

//     {uint8_t data[2] = {ACCEL_CONFIG_1_AD,0x08};
//     i2c.write(MPU9250_AD,2,data);}

//     {uint8_t data[2] = {ACCEL_CONFIG_2_AD,0x05};
//     i2c.write(MPU9250_AD,2,data);}

//     {uint8_t data[2] = {GYRO_CONFIG_AD,0x08};
//     i2c.write(MPU9250_AD,2,data);}

//     {uint8_t data[2] = {CONFIG_AD,0x05};
//     i2c.write(MPU9250_AD,2,data);}
// }

// void readGyro(){
//     //read the accelerate
//     i2c.request(MPU9250_AD,ACCEL_XOUT_H_AD,6);

//     accelX = (i2c.readBuffer()<<8) | i2c.readBuffer();
//     accelY = (i2c.readBuffer()<<8) | i2c.readBuffer();
//     accelZ = (i2c.readBuffer()<<8) | i2c.readBuffer();

//     //read the gyro
//     i2c.request(MPU9250_AD,GYRO_XOUT_H_AD,6);
//     gyroX = (i2c.readBuffer()<<8) | i2c.readBuffer();
//     gyroY = (i2c.readBuffer()<<8) | i2c.readBuffer();
//     gyroZ = (i2c.readBuffer()<<8) | i2c.readBuffer();
// }

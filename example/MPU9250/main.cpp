#include <time.h>
#include <iostream>
#include "BSC.h"

//MPU9250
#define MPU9250_AD (uint8_t)0x68
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

void MPU9250Setup();
void readGyro();

volatile int16_t accelX,accelY,accelZ,gyroX,gyroY,gyroZ,magneX,magneY,magneZ,asax,asay,asaz;
BSC i2c;
using std::cout;
using std::endl;

int main(int argc,char* argv[]){
    i2c.I2Csetup(argv[0],400);
    MPU9250Setup();
    int milisec = 100; // length of time to sleep, in miliseconds
    struct timespec req = {0};
    req.tv_sec = 0;
    req.tv_nsec = milisec * 1000000L;
    while(1){
        readGyro();
        cout<<"Acc_x: "<<accelX/ACCEL_SENS;
        cout<<" Acc_y: "<<accelY/ACCEL_SENS;
        cout<<" Acc_z: "<<accelZ/ACCEL_SENS<<endl;
        cout<<"Gyro_x: "<<gyroX/GYRO_SENS;
        cout<<" Gyro_y: "<<gyroY/GYRO_SENS;
        cout<<" Gyro_z: "<<gyroZ/GYRO_SENS<<endl;
        nanosleep(&req,(struct timespec *)NULL);
    } 
    return 0;
}

void MPU9250Setup(){
    {uint8_t data[2] = {PWR_MGMT_1_AD,0x01};
    i2c.write(MPU9250_AD,2,data);}

    {uint8_t data[2] = {ACCEL_CONFIG_1_AD,0x08};
    i2c.write(MPU9250_AD,2,data);}

    {uint8_t data[2] = {ACCEL_CONFIG_2_AD,0x05};
    i2c.write(MPU9250_AD,2,data);}

    {uint8_t data[2] = {GYRO_CONFIG_AD,0x08};
    i2c.write(MPU9250_AD,2,data);}

    {uint8_t data[2] = {CONFIG_AD,0x05};
    i2c.write(MPU9250_AD,2,data);}
}

void readGyro(){
    //read the accelerate
    i2c.request(MPU9250_AD,ACCEL_XOUT_H_AD,6);
    accelX = (i2c.readBuffer()<<8) | i2c.readBuffer();
    accelY = (i2c.readBuffer()<<8) | i2c.readBuffer();
    accelZ = (i2c.readBuffer()<<8) | i2c.readBuffer();

    //read the gyro
    i2c.request(MPU9250_AD,GYRO_XOUT_H_AD,6);
    gyroX = (i2c.readBuffer()<<8) | i2c.readBuffer();
    gyroY = (i2c.readBuffer()<<8) | i2c.readBuffer();
    gyroZ = (i2c.readBuffer()<<8) | i2c.readBuffer();
}

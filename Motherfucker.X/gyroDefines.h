
#ifndef _GYRODEFINES_H    /* Guard against multiple inclusion */
#define _GYRODEFINES_H

/***************************************************
 * MPU6050 addresses
 **************************************************/
#define SlaveAddress0 0b1101000
#define SlaveAddress1 0b1101001

#define SlaveHex0 0x68
#define SlaveHex1 0x69

#define SlaveAddress0rev 0b0001011
#define SlaveAddress1rev 0b1001011
/***************************************************
 * MPU6050 registers
 **************************************************/
#define ACCEL_XOUT_H    0x3B
#define ACCEL_XOUT_L    0x3C
#define ACCEL_YOUT_H    0x3D
#define ACCEL_YOUT_L    0x3E
#define ACCEL_ZOUT_H    0x3F
#define ACCEL_ZOUT_L    0x40
#define TEMP_OUT_H      0x41
#define TEMP_OUT_L      0x42
#define GYRO_XOUT_H     0x43
#define GYRO_XOUT_L     0x44
#define GYRO_YOUT_H     0x45
#define GYRO_YOUT_L     0x46
#define GYRO_ZOUT_H     0x47
#define GYRO_ZOUT_L     0x48
#define WHO_AM_I        0x75
#define PWR_MGMT        0x6B

//u_char ACCEL_XOUT_H =    0x3B;
//u_char ACCEL_XOUT_L =    0x3C;
//u_char ACCEL_YOUT_H =    0x3D;
//u_char ACCEL_YOUT_L =    0x3E;
//u_char ACCEL_ZOUT_H =    0x3F;
//u_char ACCEL_ZOUT_L =    0x40;
//u_char TEMP_OUT_H   =    0x41;
//u_char TEMP_OUT_L   =    0x42;
//u_char GYRO_XOUT_H  =    0x43;
//u_char GYRO_XOUT_L  =    0x44;
//u_char GYRO_YOUT_H  =    0x45;
//u_char GYRO_YOUT_L  =    0x46;
//u_char GYRO_ZOUT_H  =    0x47;
//u_char GYRO_ZOUT_L  =    0x48;
//u_char WHO_AM_I     =    0x75;
//u_char PWR_MGMT     =    0x6B;

/***************************************************
 * Variables to hold 6-DOF values
 **************************************************/
    char accelXoutH;
    char accelXoutL;
    char accelYoutH;
    char accelYoutL;
    char accelZoutH;
    char accelZoutL;
    char tempOutH;
    char tempOutL;
    char gyroXoutH;
    char gyroXoutL;
    char gyroYoutH;
    char gyroYoutL;
    char gyroZoutH;
    char gyroZoutL;

    u_char ACCEL_XOUT;
    u_short ACCEL_YOUT;
    u_short ACCEL_ZOUT;
    u_short TEMP_OUT;
    u_short GYRO_XOUT;
    u_short GYRO_YOUT;
    u_short GYRO_ZOUT;
    
    u_char LetsTry;
    
    u_char testVar1 = 1;
    u_char testVar2 = 2;
    u_char testVar3 = 3;
    u_char testVar4 = 4;
    u_char comma = ',';



#endif /* _EXAMPLE_FILE_NAME_H */


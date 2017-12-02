
#ifndef _GYRODEFINES_H    /* Guard against multiple inclusion */
#define _GYRODEFINES_H

/***************************************************
 * MPU6050 addresses
 **************************************************/
#define SlaveAddress0 0b1101000
#define SlaveAddress1 0b1101001
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

/***************************************************
 * Variables to hold 6-DOF values
 **************************************************/
    u_char accelXoutH;
    u_char accelXoutL;
    u_char accelYoutH;
    u_char accelYoutL;
    u_char accelZoutH;
    u_char accelZoutL;
    u_char tempOutH;
    u_char tempOutL;
    u_char gyroXoutH;
    u_char gyroXoutL;
    u_char gyroYoutH;
    u_char gyroYoutL;
    u_char gyroZoutH;
    u_char gyroZoutL;

    u_short ACCEL_XOUT;
    u_short ACCEL_YOUT;
    u_short ACCEL_ZOUT;
    u_short TEMP_OUT;
    u_short GYRO_XOUT;
    u_short GYRO_YOUT;
    u_short GYRO_ZOUT;



#endif /* _EXAMPLE_FILE_NAME_H */


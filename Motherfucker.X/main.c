#include <stdio.h>
#include <stdlib.h>
#include "config.h"
//#include <xc.h>
#include "functions.h"
#include "gyroDefines.h"
#include "mebedelay.h"

    



int main(void){
    I2CInit();
    UARTInit();
    uint16_t Threshold = 40; //with the proper recalculation of the axes (-60 on one of them) about 40 thresh should be good 
    u_char stepcunt = 0;
    bool john = 0;
    double vector = 0;
    //UART1Init();
    //SmirfSetup();
//    WriteToSlave(SlaveAddress1, PWR_MGMT, 0); //turn on MPU add 1
    WriteToSlave(SlaveAddress0, PWR_MGMT, 0); //turn on MPU add 0
    while(1){

//        ReceiveFromSlaveTestPoint(SlaveAddress0, ACCEL_XOUT_H, &accelXoutH);
//        ReceiveFromSlaveTestPoint(SlaveAddress0, ACCEL_ZOUT_H, &accelZoutH);
//        ReceiveFromSlaveTestPoint(SlaveAddress0, ACCEL_YOUT_H, &accelYoutH);
//        ReceiveFromSlaveTestPoint(SlaveAddress1, ACCEL_YOUT_H, &accelYoutH);
//        ReceiveFromSlaveTestPoint(SlaveAddress0, ACCEL_XOUT_L, &accelXoutL);
//        ReceiveFromSlaveTestPoint(SlaveAddress0, GYRO_XOUT_H, &gyroXoutH);
        //ReceiveFromSlaveTest(SlaveAddress0, ACCEL_XOUT_L, accelXoutL);
//        charToShort(accelXoutH, accelXoutL, ACCEL_XOUT);
        
//        u_short TestOut = charAdd(accelXoutH, accelXoutL);
        
        //U2TXREG = ACCEL_XOUT; //transmit the value
        //UART_Write(accelXoutH);
        
//        ReceiveFromSlave(SlaveAddress0, ACCEL_YOUT_H, accelYoutH);
//        ReceiveFromSlave(SlaveAddress0, ACCEL_YOUT_L, accelYoutL);
//        charToShort(accelYoutH, accelYoutL, ACCEL_YOUT);
//        U2TXREG = ACCEL_YOUT; //transmit the value
        //if(U2STAbits.UTXBF == 1)
        //while(U2STAbits.UTXBF); 
//        UART_Write(accelXoutL); //the decimal number representing the char. 65=A. 77=M.
//        UART_Write(LetsTry);
//        UART_Write(accelXoutH);
        //UART_Write(65);
        //UART1_Write(accelXoutH);
        //UART1_Write(65);
//        u_char tempWord[] = {accelXoutH,comma,testVar1,comma,testVar2,comma,accelXoutL};
//        MakeWord(tempWord);
//        TestWrite(accelXoutH,accelYoutH);
        
        
        
        /* THIS IS FOR USING THE CUSTOM FRAME. WORKS WELL
        ShortDelay(500 * US_TO_CT_TICKS );
        ShortDelay(500 * US_TO_CT_TICKS );
        UART_Write(0x7E);
        UART_Write(accelYoutH);
        UART_Write(accelXoutH);
        UART_Write(accelYoutH);
        UART_Write(accelXoutH);
        ShortDelay(500 * US_TO_CT_TICKS );
        ShortDelay(500 * US_TO_CT_TICKS );
         * 
         */
        
 

        
//        if(VectorCalc()>Threshold){
//            UART_Write('A');
//            ShortDelay(500000 * US_TO_CT_TICKS );
//        }
        
        
//        ShortDelay(500 * US_TO_CT_TICKS );
//        ShortDelay(500 * US_TO_CT_TICKS );
//        UART_Write(VectorCalc());
//        ShortDelay(500 * US_TO_CT_TICKS );
//        ShortDelay(500 * US_TO_CT_TICKS );
        
        if (VectorCalc()>Threshold && john==0) //this block of code is pretty close to just counting up when a step is taken. but sometimes it counts too many.
        { 
            stepcunt+=1; 
            UART_Write(stepcunt);
            john=1; 
        } // if it crosses threshold increment step by one and raise the flag
        else if (VectorCalc()>Threshold && john==1) // if flag is raised and threshold is crossed , do nothing
        { 
            //do nothing
        }
        if (VectorCalc()<Threshold && john==1) // if flag is raised and threshold is not crossed , put that flag down.
        {
            john=0;
        }
        ShortDelay(100000 * US_TO_CT_TICKS );
//    UART_Write(stepcunt);
    }   
}


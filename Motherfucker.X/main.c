#include <stdio.h>
#include <stdlib.h>
#include "config.h"
//#include <xc.h>
#include "functions.h"
#include "gyroDefines.h"





int main(void){
    
    I2CInit();
    UARTInit();
    //SmirfSetup();
    while(1){
        
//        ReceiveFromSlave(SlaveAddress0, ACCEL_XOUT_H, accelXoutH);
//        ReceiveFromSlave(SlaveAddress0, ACCEL_XOUT_L, accelXoutL);
//        charToShort(accelXoutH, accelXoutL, ACCEL_XOUT);
//        U2TXREG = ACCEL_XOUT; //transmit the value
//        
//        ReceiveFromSlave(SlaveAddress0, ACCEL_YOUT_H, accelYoutH);
//        ReceiveFromSlave(SlaveAddress0, ACCEL_YOUT_L, accelYoutL);
//        charToShort(accelYoutH, accelYoutL, ACCEL_YOUT);
//        U2TXREG = ACCEL_YOUT; //transmit the value
        //if(U2STAbits.UTXBF == 1)
        //while(U2STAbits.UTXBF); 
        UART_Write(77); //the decimal number representing the char. 65=A. 77=M.
    }
    
    
    
}


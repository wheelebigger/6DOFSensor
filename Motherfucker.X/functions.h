#ifndef _FUNCTIONS_H /* Guard against multiple inclusion */
#define _FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>
#include "gyroDefines.h"
//making a fake bool, for having easier readable code.
typedef unsigned char bool;
#define true    1
#define false   0


//motherfucking prototypes 
void I2CInit(void);
bool ReceiveFromSlave(u_char slaveAdr, u_char regToRead, char recData); //used to send an address and register to the I2C bus, to receive data.
void I2CIdle(void);
bool I2CStart(void);
void I2CStop(void);
bool I2CSendByte(u_char data); //used to send a byte to the I2C bus, that BYTE can represent an address or register

void UARTInit(void);

char charToShort(char high, char low);

void SmirfSetup(void);

void UART_Write(char txdata);

bool ReceiveFromSlaveTest(u_char slaveAdr, u_char regToRead, char recData);
bool ReceiveFromSlaveTestPoint(u_char slaveAdr, u_char regToRead, char *recData);

bool WriteToSlave(u_char slaveAdr, u_char regToWrite, u_char TrDat);

void UART1Init(void);
void UART1_Write(char txdata);

void MakeWord(char data[]);

bool ReceiveFromSlaveTestPointInt(u_char slaveAdr, u_char regToRead, char *recData);



void I2CInit(void){
    uint8_t temp = 0;
    I2C1CON = 0; //resets the whole I2C
    
    I2C1CONbits.ON = 0; //disables I2C before setting it up
    I2C1BRG = 0x030;
    //I2C1CONbits.A10M = 0; //Sets up the I2C to use 7-bit address
    //I2C1CONbits.SIDL = 1; //if we decide to IDLE the device, the I2C-opearations will not continue even when idled.
    I2C1CONbits.SIDL = 0;
    I2C1CONbits.DISSLW = 0; //slew rate enabled, meaning that the I2C will be communicating at 400 kHz
    //I2C1STATbits.ACKSTAT = 1;
    I2C1CONbits.ON = 1; //Enables I2C. = Configures A4 and A5 to be I2C and not analog pins.
    I2C1STAT = 0; //resets the status register 
    temp = I2C1RCV; //empties the receiver
    
};

bool ReceiveFromSlave(u_char slaveAdr, u_char regToRead, char recData){
    uint8_t ackRec, i, j;
    ackRec = 0;
    I2CStart();
    I2CSendByte(slaveAdr << 1 | 0); //the address and the bit telling it's a write mode
    I2CIdle(); //idles the I2C module.
    for(i = 0; i < 100; i++){
        
        if (I2C1STATbits.ACKSTAT == 0) // Did we receive an ACK ?
        { 
        //TRISFbits.TRISF0 = 0; //used for debugging, enable if you wanna test whether ack was received.
        ackRec = 1;
        
            break;
        }

    }
    if(!ackRec) return false; //exits if no ACK was received. / there was a problem
    ackRec = 0; 
    I2CSendByte(regToRead); //this is the register which the master wants to read from the slave.
    if (I2C1STATbits.ACKSTAT != 0) // Did we receive an ACK ?
    {
        return false; // Exit if there was a problem
    }
    //now we've told the slave which register we need data from, so we can tell the slave we wanna read from it.
    for (j = 0; j < 100; j++) {
        //5.Issue a repeated start = a start cond without a prior stop
        I2CStart();
        //6. Set Slave in R mode
        I2CSendByte((slaveAdr << 1) | 1);
        //7. Check ACK
        if (I2C1STATbits.ACKSTAT == 0) // Did we receive an ACK ?
        {
            //TRISFbits.TRISF0 = 0; //used for debugging, enable if you wanna test whether ack was received.
            ackRec = 1;
            
            break;
        }
    }
    if(!ackRec) return false; //exits if no ACK was received. / there was a problem
    
    I2CIdle();
        // got the ack, processor is in read mode
        I2C1CONbits.RCEN = 1; // enable master read (receive enable bit)
        while (I2C1CONbits.RCEN); // wait for byte to be received !(I2CSTATbits.RBF)
        
        I2CIdle(); 
        I2C1STATbits.I2COV = 0; //checks if the RCV register is still holding a previous byte. 
        recData = I2C1RCV; //recData holds the data received which is given in the receive register.
        
        //Generate a NACK on last byte
        I2C1CONbits.ACKDT = 1; // send nack
        I2C1CONbits.ACKEN = 1;
        //Generate a stop
        I2CStop();
return true;    
};



bool ReceiveFromSlaveTest(u_char slaveAdr, u_char regToRead, char recData){
    uint8_t ackRec, i, j;
    ackRec = 0;
    for(i = 0; i < 100; i++){
    I2CStart();
    I2CSendByte((slaveAdr << 1) | 0); //the address and the bit telling it's a write mode
    I2CIdle(); //idles the I2C module.
    
        
        if (I2C1STATbits.ACKSTAT == 0) // Did we receive an ACK ?
        { 
        //TRISFbits.TRISF0 = 0; //used for debugging, enable if you wanna test whether ack was received.
        ackRec = 1;
        
            break;
        }
        
    }
    if(!ackRec) return false; //exits if no ACK was received. / there was a problem
    ackRec = 0; 
    I2CSendByte(regToRead); //this is the register which the master wants to read from the slave.
    if (I2C1STATbits.ACKSTAT != 0) // Did we receive an ACK ?
    {
        return false; // Exit if there was a problem
    }
    //now we've told the slave which register we need data from, so we can tell the slave we wanna read from it.
    for (j = 0; j < 100; j++) {
        //5.Issue a repeated start = a start cond without a prior stop
        I2CStart();
        //6. Set Slave in R mode
        I2CSendByte((slaveAdr << 1) | 1);
        //7. Check ACK
        if (I2C1STATbits.ACKSTAT == 0) // Did we receive an ACK ?
        {
            //TRISFbits.TRISF0 = 0; //used for debugging, enable if you wanna test whether ack was received.
            ackRec = 1;
            break;
        }
    }
    if(!ackRec) return false; //exits if no ACK was received. / there was a problem
    
    I2CIdle();
        // got the ack, processor is in read mode
        I2C1CONbits.RCEN = 1; // enable master read (receive enable bit)
        while (I2C1CONbits.RCEN); // wait for byte to be received !(I2CSTATbits.RBF)
        
        I2CIdle(); 
        I2C1STATbits.I2COV = 0; //checks if the RCV register is still holding a previous byte. 
        //I2C1STATbits.I2CPOV = 0; //TEST DEN HER VIRKER MÅSKE IKKE
        recData = I2C1RCV; //recData holds the data received which is given in the receive register.
        
        //Generate a NACK on last byte
        I2C1CONbits.ACKDT = 1; // send nack
        I2C1CONbits.ACKEN = 1;
        //Generate a stop
        I2CStop();
return true;    
};

bool ReceiveFromSlaveTestPoint(u_char slaveAdr, u_char regToRead, char *recData){
    uint8_t ackRec, i, j;
    ackRec = 0;
    for(i = 0; i < 100; i++){
    I2CStart();
    I2CSendByte((slaveAdr << 1) | 0); //the address and the bit telling it's a write mode
    I2CIdle(); //idles the I2C module.
    
        
        if (I2C1STATbits.ACKSTAT == 0) // Did we receive an ACK ?
        { 
        //TRISFbits.TRISF0 = 0; //used for debugging, enable if you wanna test whether ack was received.
        ackRec = 1;
        
            break;
        }
        
    }
    if(!ackRec) return false; //exits if no ACK was received. / there was a problem
    ackRec = 0; 
    I2CSendByte(regToRead); //this is the register which the master wants to read from the slave.
    if (I2C1STATbits.ACKSTAT != 0) // Did we receive an ACK ?
    {
        return false; // Exit if there was a problem
    }
    //now we've told the slave which register we need data from, so we can tell the slave we wanna read from it.
    for (j = 0; j < 100; j++) {
        //5.Issue a repeated start = a start cond without a prior stop
        I2CStart();
        //6. Set Slave in R mode
        I2CSendByte((slaveAdr << 1) | 1);
        //7. Check ACK
        if (I2C1STATbits.ACKSTAT == 0) // Did we receive an ACK ?
        {
            //TRISFbits.TRISF0 = 0; //used for debugging, enable if you wanna test whether ack was received.
            ackRec = 1;
            break;
        }
    }
    if(!ackRec) return false; //exits if no ACK was received. / there was a problem
    
    I2CIdle();
        // got the ack, processor is in read mode
        I2C1CONbits.RCEN = 1; // enable master read (receive enable bit)
        while (I2C1CONbits.RCEN); // wait for byte to be received !(I2CSTATbits.RBF)
        
        I2CIdle(); 
        I2C1STATbits.I2COV = 0; //checks if the RCV register is still holding a previous byte. 
        //I2C1STATbits.I2CPOV = 0; //TEST DEN HER VIRKER MÅSKE IKKE
        *recData = I2C1RCV; //recData holds the data received which is given in the receive register.
        
        //Generate a NACK on last byte
        I2C1CONbits.ACKDT = 1; // send nack
        I2C1CONbits.ACKEN = 1;
        //Generate a stop
        I2CStop();
return true;    
};

bool ReceiveFromSlaveTestPointInt(u_char slaveAdr, u_char regToRead, char *recData){
    uint8_t ackRec, i, j;
    ackRec = 0;
    for(i = 0; i < 100; i++){
    I2CStart();
    I2CSendByte((slaveAdr << 1) | 0); //the address and the bit telling it's a write mode
    I2CIdle(); //idles the I2C module.
    
        
        if (I2C1STATbits.ACKSTAT == 0) // Did we receive an ACK ?
        { 
        //TRISFbits.TRISF0 = 0; //used for debugging, enable if you wanna test whether ack was received.
        ackRec = 1;
        
            break;
        }
        
    }
    if(!ackRec) return false; //exits if no ACK was received. / there was a problem
    ackRec = 0; 
    I2CSendByte(regToRead); //this is the register which the master wants to read from the slave.
    if (I2C1STATbits.ACKSTAT != 0) // Did we receive an ACK ?
    {
        return false; // Exit if there was a problem
    }
    //now we've told the slave which register we need data from, so we can tell the slave we wanna read from it.
    for (j = 0; j < 100; j++) {
        //5.Issue a repeated start = a start cond without a prior stop
        I2CStart();
        //6. Set Slave in R mode
        I2CSendByte((slaveAdr << 1) | 1);
        //7. Check ACK
        if (I2C1STATbits.ACKSTAT == 0) // Did we receive an ACK ?
        {
            //TRISFbits.TRISF0 = 0; //used for debugging, enable if you wanna test whether ack was received.
            ackRec = 1;
            break;
        }
    }
    if(!ackRec) return false; //exits if no ACK was received. / there was a problem
    
    I2CIdle();
        // got the ack, processor is in read mode
        I2C1CONbits.RCEN = 1; // enable master read (receive enable bit)
        while (I2C1CONbits.RCEN); // wait for byte to be received !(I2CSTATbits.RBF)
        
        I2CIdle(); 
        I2C1STATbits.I2COV = 0; //checks if the RCV register is still holding a previous byte. 
        //I2C1STATbits.I2CPOV = 0; //TEST DEN HER VIRKER MÅSKE IKKE
        *recData = I2C1RCV; //recData holds the data received which is given in the receive register.
        
        //Generate a NACK on last byte
        I2C1CONbits.ACKDT = 1; // send nack
        I2C1CONbits.ACKEN = 1;
        //Generate a stop
        I2CStop();
return true;    
};


void I2CIdle(void) {
    uint8_t t = 1;
    /* Wait until I2C Bus is Inactive */
    while (I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN ||
            I2C1CONbits.RSEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT || t--);
}

bool I2CStart(void) {
    // wait for module idle
    I2CIdle();
    // Enable the Start condition
    I2C1CONbits.SEN = 1;
    // Check for collisions
    if (I2C1STATbits.BCL) {
        return (false);
    } else {
        // wait for module idle
        I2CIdle();
        return (true);
    }
}

void I2CStop(void) {
    int x = 0;
    // wait for module idle
    I2CIdle();
    //initiate stop bit
    I2C1CONbits.PEN = 1;
    //wait for hardware clear of stop bit
    while (I2C1CONbits.PEN) {
        if (x++ > 50) break;
    }
    I2C1CONbits.RCEN = 0;
    // IFS1bits.MI2C1IF = 0; // Clear Interrupt
    I2C1STATbits.IWCOL = 0;
    I2C1STATbits.BCL = 0;
    // wait for module idle
    I2CIdle();
}

bool I2CSendByte(u_char data) {
    while(I2C1STATbits.TBF); //Wait till data is transmitted.
    // Send the byte
    I2C1TRN = data;

    // Check for collisions
    if ((I2C1STATbits.IWCOL == 1)) {
        return (false);
    } else {
        while (I2C1STATbits.TRSTAT); // wait until write cycle is complete
        if ((I2C1STATbits.BCL == 1)) {
            return (false);
        } else {
            //TRISFbits.TRISF0 = 0; //used for debugging, enable if you wanna test whether ack was received.
            // wait for module idle
            I2CIdle();
            return (true);
        }
    }
}

bool WriteToSlave(u_char slaveAdr, u_char regToWrite, u_char TrDat){
    uint8_t i, ack, k;
    ack = 0;
    for(i = 0; i< 100; i++){
        I2CStart();
        I2CSendByte((slaveAdr << 1)| 0);
        I2CIdle();
        if(I2C1STATbits.ACKSTAT == 0) 
        {
            ack = 1;
            break;
        }
    }
    if(!ack) return (false);
    I2CSendByte(regToWrite);
    I2CIdle();
    if(I2C1STATbits.ACKSTAT == 0)
    {
        I2CSendByte(TrDat);
    } else {
        return false;
    }
    I2CStop();
    return true;
}

void UARTInit(void){
    U2STA = 0; //clearing the whole UART STA before setup
    U2MODE = 0;//clearing the whole UART MODE before setup
    
    U2BRG = 21; //baudrate of ~115200 if the PBCL i 40 MHz
    //U2BRG = 259; //daudrate of ~9600 if the PBCL is 40 MHz
    
    
    /* This is for PBCL of 80 MHz
    *U2BRG = 519;    // Sets the baud rate to  ~9600 (9615)
    *U2BRG = 42;     // Sets the baud rate to ~115200 (116279)
    */
    //U2MODEbits.BRGH = 1;
    
    U2MODEbits.ON = 0; //turn off the UART before setting it up
    //U2MODEbits.SIDL = 1; //stop operation on sleep
    U2MODEbits.SIDL = 0;
    //Do we need the RTSMD?
    U2MODEbits.PDSEL = 0b00;//8-bit data no parity
    U2MODEbits.STSEL = 0;   // 1 stop bit
        
    U2MODEbits.ON = 1;
    
    U2STAbits.URXEN = 1; //Enables receive module
    U2STAbits.UTXEN = 1; //Enables transmit module
}

void UART1Init(void){
    U1STA = 0;
    U2MODE = 0;
    U1BRG = 21;
    U1MODEbits.ON = 0;
    U1MODEbits.SIDL = 1;
    U1MODEbits.PDSEL = 0b00;
    U1MODEbits.STSEL = 0;
    U1MODEbits.ON = 1;
    U1STAbits.URXEN = 1;
    U1STAbits.UTXEN = 1;
}

char charToShort(char high, char low){
    char outUnite = ((high <<8) | low)/256;
    
    return outUnite;
    //this literally just removes the lowest bit. bitcalculation is fucking retarded. just use the high part of the register.
}

u_short charAdd(char high, char low) {
    u_short dickfuck = (high<<8)|low;
    return dickfuck;
}

void SmirfSetup(void){
    U2TXREG = '$';
    U2TXREG = '$';
    U2TXREG = '$';  
}

void UART_Write(char txdata)
{
  while(!U2STAbits.TRMT);
  if(txdata != 0){
      U2TXREG = txdata;
  }
  txdata = 0;
}

void UART_WriteShort(short txdata)
{
  while(!U2STAbits.TRMT);
  if(txdata != 0){
      U2TXREG = txdata;
  }
  txdata = 0;
}

void UART1_Write(char txdata)
{
  while(!U1STAbits.TRMT);
  U1TXREG = txdata;
}

void MakeWord(char data[]){
    int w = 0;
    while(data[w]){
        UART_Write(data[w]);
        w++;
    }
}

void TestComma(char data1, char data2){
    UART_Write(data1);
    UART_Write(',');
    UART_Write(data2);
    UART_Write(',');
}

void TestSpace(char data1, char data2){
    UART_Write('$');
    UART_Write(data1);
    UART_Write(' ');
    UART_Write(data2);
    UART_Write(';');
}

double VectorCalc(){
    ReceiveFromSlaveTestPoint(SlaveAddress0, ACCEL_XOUT_H, &accelXoutH);
    ReceiveFromSlaveTestPoint(SlaveAddress0, ACCEL_YOUT_H, &accelYoutH);
    ReceiveFromSlaveTestPoint(SlaveAddress0, ACCEL_ZOUT_H, &accelZoutH);
    accelYoutH = accelYoutH-60; //calculation needed, depending on how the chip will be turning, refer to the pictures.
    
    double result = sqrt(pow(accelXoutH, 2)+pow(accelYoutH, 2)+pow(accelZoutH, 2)); 
    
    return result;
            
}

void stepcountfunc(u_char stepcount, uint16_t threshold, bool flag){
    if (VectorCalc()>threshold && flag==0)
    { 
        stepcount+=1; 
        flag=1; 
    } // if it crosses threshold increment step by one and raise the flag
    else if (VectorCalc()>threshold && flag==1) // if flag is raised and threshold is crossed , do nothing
    { 
    //do nothing     
    }
    if (VectorCalc()<threshold && flag==1) // if flag is raised and threshold is not crossed , put that flag down.
    {
        flag=0;
    }
    UART_Write(stepcount);
}
#endif 

#ifndef _CONFIG_H    /* Guard against multiple inclusion */
#define _CONFIG_H


/***************************************************
 *Calculations for the system clock
 *The primary Oscillator of the chip is 8 mHz
 *The math is 8.000.000/2*20/1 = 80.000.000 (80 mHz)
 * /2 = FPLLIDIV. *20 = FPLLMUL. /1 = FPLLODIV
 ***************************************************/
#pragma config FPLLIDIV = DIV_2
#pragma config FPLLMUL = MUL_20
#pragma config FPLLODIV = DIV_1


#pragma config FNOSC = PRIPLL
#pragma config FSOSCEN = OFF
#pragma config IESO = ON
#pragma config POSCMOD = XT
#pragma config OSCIOFNC = OFF
#pragma config FPBDIV = DIV_2  //Peripheral Clock Division (PBCLK is SYSCLK/2) = 40 mHz
#pragma config FCKSM = CSDCMD
#pragma config WDTPS = PS1048576

#pragma config FWDTEN = OFF


#pragma config ICESEL = ICS_PGx1
#pragma config PWP = OFF
#pragma config BWP = OFF
#pragma config CP = OFF

#pragma config DEBUG = OFF

#endif 
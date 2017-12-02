/* 
 * File:   Delay.h
 * Author: IbHelmer
 *
 * Created on 14. februar 2016, 21:38
 */

#ifndef DELAY_H
#define	DELAY_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#define _SUPPRESS_PLIB_WARNING 1
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING 1  
#include <stdlib.h>
    
//  The following is used by the main application
#define SYS_FREQ		(80000000)

#define TICK_PER_MS     (SYS_FREQ/2/1000)
#define TICK_PER_US     (SYS_FREQ/2/1000000)    

#define DelayMs(X)  OpenCoreTimer(X*TICK_PER_MS);while (!mCTGetIntFlag()); mCTClearIntFlag();
#define DelayUs(X)  OpenCoreTimer(X*TICK_PER_US);while (!mCTGetIntFlag()); mCTClearIntFlag();


#ifdef	__cplusplus
}
#endif

#endif	/* DELAY_H */
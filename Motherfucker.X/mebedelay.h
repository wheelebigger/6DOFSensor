
#ifndef _MEBDEL_H    /* Guard against multiple inclusion */
#define _MEBDEL_H
#include <p32xxxx.h>
#define _CP0_GET_COUNT()       _mfc0 (_CP0_COUNT, _CP0_COUNT_SELECT) 


void ShortDelay(                       // Short Delay 
  uint32_t DelayCount)                   // Delay Time (CoreTimer Ticks) 
{ 
  uint32_t StartTime;                    // Start Time 
  StartTime = _CP0_GET_COUNT();         // Get CoreTimer value for StartTime 
  while ( (uint32_t)(_CP0_GET_COUNT() - StartTime) < DelayCount ) {}; 
} 


#define CPU_CLOCK_HZ             (80000000UL)    // CPU Clock Speed in Hz 
#define CPU_CT_HZ            (CPU_CLOCK_HZ/2)    // CPU CoreTimer   in Hz 
#define PERIPHERAL_CLOCK_HZ      (40000000UL)    // Peripheral Bus  in Hz 

#define US_TO_CT_TICKS  (CPU_CT_HZ/1000000UL)    // uS to CoreTimer Ticks 

 

     // Delay 50uS 

#endif /* _EXAMPLE_FILE_NAME_H */

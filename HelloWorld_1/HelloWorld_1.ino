//=============================================================================>
// 1. Project - start

// Author:    MagSem
// Fork:      Maxim Integrated Firmware
// Data:      20.11.2019
// Details:   Some Maxim Integrated EvKit examples for Arduino       
// uC board:  MAX32620FTHR

// 1. Project - finish
//=============================================================================<

/**
 * @file    
 * @brief   Hello World!
 * @details This example uses the UART to print to a terminal and flashes an LED.
 * @details Add string from MAX32625 EvKit and analog printf function
 */

//=============================================================================>
// 2. Includes - start

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include "tmr_utils.h"

#include "MAX32620FTHRM.h"              // MAX32620FTHRM  MagSem Lib

// 2. Includes - finish
//=============================================================================<

//=============================================================================>
// 3. Definitions - start

// 3. Definitions - finish
//=============================================================================<

//=============================================================================>
// 4. Globals - start

uint8_t LED_Status[] = {0, 0, 0, 0};

// 4. Globals - finish
//=============================================================================<

//=============================================================================>
// 5. Functions - start

/*
 * SerialPrintf
 * Implements printf functionality in Serial.print
 * Used for debug printing
 * Parameters like printf
 * Returns 
 *    0 - format error
 *    negative number - out of memory, the modulus of the number is equal to the requested memory
 *    positive number - the number of characters printed in Serial
 */
const size_t SerialPrintf (const char *szFormat, ...)
{
  va_list argptr;
  va_start(argptr, szFormat);
  char *szBuffer = 0;
  const size_t nBufferLength = vsnprintf(szBuffer, 0, szFormat, argptr) + 1;
  if (nBufferLength == 1) return 0;
  szBuffer = (char *) malloc(nBufferLength);
  if (! szBuffer) return - nBufferLength;
  vsnprintf(szBuffer, nBufferLength, szFormat, argptr);
  Serial.print(szBuffer);
  free(szBuffer);
  return nBufferLength - 1;
}

// 5. Functions - finish
//=============================================================================<

//=============================================================================>
// 6. SetUp - start

void setup(void)
{
  // Prepare the User LEDs
  pinMode(MAX32620FTHR_RLED, OUTPUT);
  pinMode(MAX32620FTHR_GLED, OUTPUT);
  pinMode(MAX32620FTHR_BLED, OUTPUT);

  // USB to Serial (PC to uC)
  Serial.begin(0);
  //while(!Serial.availableForWrite()); // 1.1.3
  //while (!Serial);                    // 1.1.5
  // 96 MHz very fast for first Serial print
  delay(500);
}

// 6. SetUp - finish
//=============================================================================<

//=============================================================================>
// 7. Loop - start

void loop(void)
{
  int count = 0;
  int led = 2;
  int timems = 1000;

  SerialPrintf("---Hello World!---\n");

  while(1)
  {
    SerialPrintf("%s Rev: %c%c\n", TARGET_NAME, ((TARGET_REV >> 8) & 0xFF), (TARGET_REV & 0xFF));

    LED_On(led);
    SerialPrintf("count = %d\n", count++);
    TMR_Delay(MXC_TMR0, MSEC(timems));
    LED_Off(led);
    TMR_Delay(MXC_TMR0, MSEC(timems));
  }
}

// 7. Loop - finish
//=============================================================================<

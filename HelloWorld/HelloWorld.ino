//=============================================================================>
// 1. Project - start

// Author:    MagSem
// Fork:      Maxim Integrated Firmware
// Data:      02.08.2019
// Details:   Some Maxim Integrated EvKit examples for Arduino       
// uC board:  MAX32620FTHR

// 1. Project - finish
//=============================================================================<

/**
 * @file    
 * @brief   Hello World!
 * @details This example uses the UART to print to a terminal and flashes an LED.
 */

//=============================================================================>
// 2. Includes - start

#include <stdio.h>
#include <stdint.h>
#include "mxc_config.h"
#include "mxc_sys.h"
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
  int led = 0;
  int timems = 1000;

  Serial.println(" ");
  Serial.println("---Hello World!---");
  Serial.println(" ");

  while(1)
  {
    LED_On(led);
      Serial.print("LED Number = ");
      Serial.println(led);
      Serial.print("LED_Status = ");
      Serial.println(LED_Status[led]);
      Serial.print("count = ");
      Serial.println(count);
    TMR_Delay(MXC_TMR0, MSEC(timems));
    LED_Off(led);
      Serial.print("LED_Status = ");
      Serial.println(LED_Status[led]);
      Serial.println(" ");
    TMR_Delay(MXC_TMR0, MSEC(timems));
    count++;
    if(led < 3) led++; else led = 0;
  }
}

// 7. Loop - finish
//=============================================================================<

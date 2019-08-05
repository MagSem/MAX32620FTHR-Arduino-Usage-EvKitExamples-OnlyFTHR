//=============================================================================>
// 1. Project - start

// Author:    MagSem
// Fork:      Maxim Integrated Firmware
// Data:      05.08.2019
// Details:   Some Maxim Integrated EvKit examples for Arduino       
// uC board:  MAX32620FTHR

// 1. Project - finish
//=============================================================================<

/**
 * @file    
 * @brief   GPIO callback demo
 * @details When GPIO Port 2 Pin 7 transitions from high to low,
 *          the LED transitions between Red and Green
 */

//=============================================================================>
// 2. Includes - start

#include <stdio.h>
#include <stdint.h>
#include "mxc_config.h"
#include "mxc_sys.h"
#include "gpio.h"

#include "MAX32620FTHRM.h"            // MAX32620FTHRM  MagSem Lib

// 2. Includes - finish
//=============================================================================<

//=============================================================================>
// 3. Definitions - start

// 3. Definitions - finish
//=============================================================================<

//=============================================================================>
// 4. Globals - start

uint8_t LED_Status[] = {0, 0, 0, 0};

const gpio_cfg_t pin = { PORT_2, PIN_7, GPIO_FUNC_GPIO, GPIO_PAD_INPUT_PULLUP };

// 4. Globals - finish
//=============================================================================<

//=============================================================================>
// 5. Functions - start

//----------------------------------------------------------------------------->
/* This function is called when the interrupt fires on the GPIO pin
 *
 * Remember to de-bounce the input to this pin, or the LEDs will toggle
 *  too fast to observe!
 *
 */
void pin_cb(void *cbdata)
{
  static unsigned int state = 0;

  if (state)
  {
    LED_On(2);
    LED_Off(1);
  }
  else
  {
    LED_Off(2);
    LED_On(1);
  }
  state ^= 0x01;
}
//-----------------------------------------------------------------------------<

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
  // Prepare the User PUSH BUTTON
  pinMode(MAX32620FTHR_PBUT, INPUT_PULLUP);

  // USB to Serial (PC to uC)
  Serial.begin(0);
  //while(!Serial.availableForWrite()); // 1.1.3
  //while (!Serial);                    // 1.1.5
  // 96 MHz very fast for first Serial print
  delay(500);
  
  /* Initial state of LEDs */
  LED_On(2);
  LED_Off(1);

  /* Configure port pin and callback */
  GPIO_Config(&pin);
  GPIO_RegisterCallback(&pin, pin_cb, NULL);
  GPIO_IntConfig(&pin, GPIO_INT_FALLING_EDGE);
  GPIO_IntEnable(&pin);
  NVIC_EnableIRQ(MXC_GPIO_GET_IRQ(pin.port));
}

// 6. SetUp - finish
//=============================================================================<

//=============================================================================>
// 7. Loop - start

void loop(void)
{
  /* Wait forever here, toggling LEDs on interrupts */
  while (1);
}

// 7. Loop - finish
//=============================================================================<

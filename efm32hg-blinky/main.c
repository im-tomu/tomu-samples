// Copyright 2016 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "capsense.h"
#include "retargetserial.h"

#include "em_chip.h"
#include "em_cmu.h"
#include "em_device.h"
#include "em_emu.h"
#include "em_gpio.h"

// The uptime of this application in milliseconds, maintained by the SysTick
// timer.
volatile uint32_t uptime_millis;

// This functions is injected into the Interrupt Vector Table, and will be
// called whenever the SysTick timer fires (whose interval is configured inside
// main() further below).
void SysTick_Handler() {
  uptime_millis++;
}

void SpinDelay(uint32_t millis) {
  // Calculate the time at which we need to finish "sleeping".
  uint32_t sleep_until = uptime_millis + millis;

  // Spin until the requested time has passed.
  while (uptime_millis < sleep_until);
}

int main() {
  // Runs the Silicon Labs chip initialisation stuff, that also deals with
  // errata (implements workarounds, etc).
  CHIP_Init();

  // Initialise the LEUART, and map output from printf() to it.
  RETARGET_SerialInit();
  RETARGET_SerialCrLf(1);

  // Switch on the clock for GPIO. Even though there's no immediately obvious
  // timing stuff going on beyond the SysTick below, it still needs to be
  // enabled for the GPIO to work.
  printf("Enabling GPIO clock\n");
  CMU_ClockEnable(cmuClock_GPIO, true);

  // Sets up and enable the `SysTick_Handler' interrupt to fire once every 1ms.
  // ref: http://community.silabs.com/t5/Official-Blog-of-Silicon-Labs/Chapter-5-MCU-Clocking-Part-2-The-SysTick-Interrupt/ba-p/145297
  printf("Starting systick timer\n");
  if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) {
    // Something went wrong.
    printf("ERROR WHILST INITIALISING SYSTICK TIMER! HALTING.\n");
    while (1);
  }

  // Set up two pins with the GPIO controller and configure them to be open
  // drain:
  //  - PA0 == green
  //  - PB7 == red
  printf("Setting up GPIO pins to be open-drain\n");
  GPIO_PinModeSet(gpioPortA, 0, gpioModeWiredAnd, 0);
  GPIO_PinModeSet(gpioPortB, 7, gpioModeWiredAnd, 0);

  // Enable the capacitive touch sensor. Remember, this consumes TIMER0 and
  // TIMER1, so those are off-limits to us.
  printf("Initialising the capacitive touch sensor\n");
  CAPSENSE_Init();

  // Blink infinitely.
  printf("Beginning application loop.\n");
  while (1) {
    printf("Hello world\n");

    // Clear the PA0 bit, allowing the FET to sink to ground and thus lighting
    // up the green LED.
    GPIO_PinOutClear(gpioPortA, 0);
    SpinDelay(100);

    // Set the PA0 bit, preventing the FET from sinking to ground and thus
    // switching the green LED off.
    GPIO_PinOutSet(gpioPortA, 0);
    SpinDelay(100);

    // Repeat for the red LED on port PB7, but do so twice so that those that
    // self-assemble their boards can be sure they've got the green and red LEDs
    // around the right way.
    GPIO_PinOutClear(gpioPortB, 7);
    SpinDelay(100);
    GPIO_PinOutSet(gpioPortB, 7);
    SpinDelay(100);
    GPIO_PinOutClear(gpioPortB, 7);
    SpinDelay(100);
    GPIO_PinOutSet(gpioPortB, 7);
    SpinDelay(100);

    SpinDelay(500);

    // Capture/sample the state of the capacitive touch sensors.
    CAPSENSE_Sense();

    // Analyse the sample, and if the touch-pads on the green LED side is
    // touched, rapid blink the green LED ten times.
    if (CAPSENSE_getPressed(BUTTON0_CHANNEL) &&
        !CAPSENSE_getPressed(BUTTON1_CHANNEL)) {
      printf("Detected touch near green LED\n");
      int i;
      for (i = 10; i > 0; i--) {
        GPIO_PinOutClear(gpioPortA, 0);
        SpinDelay(100);
        GPIO_PinOutSet(gpioPortA, 0);
        SpinDelay(100);
      }
    // Analyse the same sample, and if the touch-pads on the red LED side is
    // touched, rapid blink the red LED ten times.
    } else if (CAPSENSE_getPressed(BUTTON1_CHANNEL) &&
               !CAPSENSE_getPressed(BUTTON0_CHANNEL)) {
      printf("Detected touch near red LED\n");
      int i;
      for (i = 10; i > 0; i--) {
        GPIO_PinOutClear(gpioPortB, 7);
        SpinDelay(100);
        GPIO_PinOutSet(gpioPortB, 7);
        SpinDelay(100);
      }
    }

    SpinDelay(500);
  }
}

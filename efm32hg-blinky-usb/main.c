#include <stdint.h>
#include <stdbool.h>

#include "capsense.h"
#include "usbconfig.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_device.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_usb.h"
#include "em_wdog.h"

#include "callbacks.h"
#include "descriptors.h"

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

  // Disable the watchdog that the bootloader started.
  WDOG->CTRL = 0;

  // Switch on the clock for GPIO. Even though there's no immediately obvious
  // timing stuff going on beyond the SysTick below, it still needs to be
  // enabled for the GPIO to work.
  CMU_ClockEnable(cmuClock_GPIO, true);

  // Sets up and enable the `SysTick_Handler' interrupt to fire once every 1ms.
  // ref: http://community.silabs.com/t5/Official-Blog-of-Silicon-Labs/Chapter-5-MCU-Clocking-Part-2-The-SysTick-Interrupt/ba-p/145297
  if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) {
    // Something went wrong.
    while (1);
  }
  // Set up two pins with the GPIO controller and configure them to be open
  // drain:
  //  - PA0 == green
  //  - PB7 == red
  GPIO_PinModeSet(gpioPortA, 0, gpioModeWiredAnd, 0);
  GPIO_PinModeSet(gpioPortB, 7, gpioModeWiredAnd, 0);

  // Enable the capacitive touch sensor. Remember, this consumes TIMER0 and
  // TIMER1, so those are off-limits to us.
  CAPSENSE_Init();

  // Enable the USB controller. Remember, this consumes TIMER2 as per
  // -DUSB_TIMER=USB_TIMER2 in Makefile because TIMER0 and TIMER1 are already
  // taken by the capacitive touch sensors.
  USBD_Init(&initstruct);

  // Blink infinitely, in an aviation-like pattern.
  while (1) {
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


#include <stdint.h>
#include <stdbool.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_usb.h"

#include "callbacks.h"

#define BUFFERSIZE 256
STATIC_UBUF(receiveBuffer, BUFFERSIZE);


void stateChange(USBD_State_TypeDef oldState, USBD_State_TypeDef newState)
{
  (void)oldState;
  if (newState == USBD_STATE_CONFIGURED)
  {
    GPIO_PinOutClear(gpioPortA, 0);
    USBD_Read(EP_OUT, receiveBuffer, BUFFERSIZE, dataReceivedCallback);
  }
  else if ( newState == USBD_STATE_SUSPENDED )
  {
    GPIO_PinOutSet(gpioPortA, 0);
  }
}


int dataSentCallback(USB_Status_TypeDef status, uint32_t xferred, uint32_t remaining)
{
  /* Remove warnings for unused variables */
  (void)xferred;
  (void)remaining;
  
  return status;
}


int dataReceivedCallback(USB_Status_TypeDef status, uint32_t xferred, uint32_t remaining)
{
  /* Remove warnings for unused variables */
  (void)xferred;
  (void)remaining;

  if ( status != USB_STATUS_OK )
  {
     return status;
  }
  GPIO_PinOutClear(gpioPortB, 7);
  USBTIMER_DelayMs( 100 );
  GPIO_PinOutSet(gpioPortB, 7);
  if( xferred == 4 && receiveBuffer[0] == 'p' && receiveBuffer[1] == 'i' && receiveBuffer[2] == 'n' && receiveBuffer[3] == 'g' ) {
    receiveBuffer[1] = 'o';
  }
  USBD_Write(EP_IN, receiveBuffer, xferred, dataSentCallback);
  USBD_Read(EP_OUT, receiveBuffer, BUFFERSIZE, dataReceivedCallback);
  return USB_STATUS_OK;
}


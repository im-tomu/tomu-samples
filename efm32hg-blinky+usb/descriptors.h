/***************************************************************************//**
 * @file descriptors.h
 * @brief USB descriptors
 * @author Energy Micro AS
 * @version 1.01
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 * 4. The source and compiled code may only be used on Energy Micro "EFM32"
 *    microcontrollers and "EFR4" radios.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 *****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
  

/* Device Descriptor. Refer to the USB 2.0 Specification, chapter 9.6 */
SL_ALIGN(4)
static const USB_DeviceDescriptor_TypeDef deviceDesc SL_ATTRIBUTE_ALIGN(4) =
{
  .bLength            = USB_DEVICE_DESCSIZE,            /* Size of the Descriptor in Bytes */
  .bDescriptorType    = USB_DEVICE_DESCRIPTOR,          /* Device Descriptor type */
  .bcdUSB             = 0x0200,                         /* USB 2.0 compliant */
  .bDeviceClass       = 0xFF,                           /* Vendor unique device */
  .bDeviceSubClass    = 0,                              /* Ignored for vendor unique device */            
  .bDeviceProtocol    = 0,                              /* Ignored for vendor unique device */
  .bMaxPacketSize0    = USB_FS_CTRL_EP_MAXSIZE,                /* Max packet size for EP0 */
  .idVendor           = 0x10C4,                         /* Energy Micro VID */
  .idProduct          = 0x4711,                         /* PID */
  .bcdDevice          = 0x0100,                         /* Device Release number */
  .iManufacturer      = 1,                              /* Index of Manufacturer String Descriptor */
  .iProduct           = 2,                              /* Index of Product String Descriptor */
  .iSerialNumber      = 3,                              /* Index of Serial Number String Descriptor */
  .bNumConfigurations = 1                               /* Number of Possible Configurations */
};

/* This array contains the Configuration Descriptor and all
 * Interface and Endpoint Descriptors for the device.
 * Refer to the USB 2.0 Specification, chapter 9.6. */
SL_ALIGN(4)
static const uint8_t configDesc[] SL_ATTRIBUTE_ALIGN(4) =
{
  /*** Configuration descriptor ***/
  USB_CONFIG_DESCSIZE,                  /* bLength              */
  USB_CONFIG_DESCRIPTOR,                /* bDescriptorType      */

  USB_CONFIG_DESCSIZE +                 /* wTotalLength (LSB)   */
  USB_INTERFACE_DESCSIZE +
  (USB_ENDPOINT_DESCSIZE * NUM_EP_USED),

  (USB_CONFIG_DESCSIZE +                /* wTotalLength (MSB)   */
  USB_INTERFACE_DESCSIZE +
  (USB_ENDPOINT_DESCSIZE * NUM_EP_USED))>>8,

  1,                                    /* bNumInterfaces       */
  1,                                    /* bConfigurationValue  */
  0,                                    /* iConfiguration       */
  CONFIG_DESC_BM_RESERVED_D7,           /* bmAttrib             */
  CONFIG_DESC_MAXPOWER_mA( 100 ),       /* bMaxPower: 100 mA    */

  /*** Interface descriptor ***/
  USB_INTERFACE_DESCSIZE,               /* bLength              */
  USB_INTERFACE_DESCRIPTOR,             /* bDescriptorType      */
  0,                                    /* bInterfaceNumber     */
  0,                                    /* bAlternateSetting    */
  NUM_EP_USED,                          /* bNumEndpoints        */
  0xFF,                                 /* bInterfaceClass      */
  0,                                    /* bInterfaceSubClass   */
  0,                                    /* bInterfaceProtocol   */
  0,                                    /* iInterface           */
  
  /*** Bulk Endpoint Descriptor (IN) ***/
  USB_ENDPOINT_DESCSIZE,                /* bLength              */
  USB_ENDPOINT_DESCRIPTOR,              /* bDescriptorType      */
  EP_IN,                                /* bEndpointAddress     */
  USB_EPTYPE_BULK,                      /* bmAttributes         */
  USB_FS_BULK_EP_MAXSIZE,               /* wMaxPacketSize (LSB) */
  0,                                    /* wMaxPacketSize (MSB) */
  0,                                    /* bInterval            */    
  
  
  /*** Bulk Endpoint Descriptor (OUT) ***/
  USB_ENDPOINT_DESCSIZE,                /* bLength              */
  USB_ENDPOINT_DESCRIPTOR,              /* bDescriptorType      */
  EP_OUT,                               /* bEndpointAddress     */
  USB_EPTYPE_BULK,                      /* bmAttributes         */
  USB_FS_BULK_EP_MAXSIZE,               /* wMaxPacketSize (LSB) */
  0,                                    /* wMaxPacketSize (MSB) */
  0,                                    /* bInterval            */
   
};

/* Define the String Descriptor for the device. String must be properly
 * aligned and unicode encoded. The first element defines the language id. 
 * Here 0x04 = United States, 0x09 = English. 
 * Refer to the USB Language Identifiers documentation. */
STATIC_CONST_STRING_DESC_LANGID( langID, 0x04, 0x09 );
STATIC_CONST_STRING_DESC( iManufacturer, 'S','i','l','i','c','o','n',' ',
                                         'L', 'a', 'b', 's' );
STATIC_CONST_STRING_DESC( iProduct     , 'E','F','M','3','2',' ',
                                         'E','x','a','m','p','l','e',' ',
                                         'U','S','B',' ', 
                                         'D','e','v','i','c','e');
STATIC_CONST_STRING_DESC( iSerialNumber, '0','0','0','0','0','0',             
                                         '0','0','1','2','3','4' );


static const void * const strings[] =
{
  &langID,
  &iManufacturer,
  &iProduct,
  &iSerialNumber
};

/* Endpoint buffer sizes. Use 1 for Control/Interrupt
 * endpoints and 2 for Bulk endpoints. */
static const uint8_t bufferingMultiplier[ NUM_EP_USED + 1 ] = 
{ 
  1,  /* Control */
  2,  /* Bulk */
  2   /* Bulk */
};

/* Define callbacks that are called by the USB stack on different events. */
static const USBD_Callbacks_TypeDef callbacks =
{
  .usbReset        = NULL,              /* Called whenever USB reset signalling is detected on the USB port. */
  .usbStateChange  = stateChange,       /* Called whenever the device change state.  */
  .setupCmd        = NULL,              /* Called on each setup request received from host. */
  .isSelfPowered   = NULL,              /* Called whenever the device stack needs to query if the device is currently self- or bus-powered. */
  .sofInt          = NULL               /* Called at each SOF (Start of Frame) interrupt. If NULL, the device stack will not enable the SOF interrupt. */
};

/* Fill the init struct. This struct is passed to USBD_Init() in order 
 * to initialize the USB Stack */
static const USBD_Init_TypeDef initstruct =
{
  .deviceDescriptor    = &deviceDesc,
  .configDescriptor    = configDesc,
  .stringDescriptors   = strings,
  .numberOfStrings     = sizeof(strings)/sizeof(void*),
  .callbacks           = &callbacks,
  .bufferingMultiplier = bufferingMultiplier,
  .reserved            = 0
};

#ifdef __cplusplus
}
#endif


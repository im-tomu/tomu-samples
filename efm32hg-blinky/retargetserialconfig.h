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

// This file contains configuration/settings for the Gecko SDK-provided
// "retargetserial" driver at Gecko_SDK/kits/common/drivers/retargetserial.c.

#ifndef _RETARGETSERIALCONFIG_H
#define _RETARGETSERIALCONFIG_H

#define RETARGET_CLK      cmuClock_LEUART0
#define RETARGET_IRQ_NAME LEUART0_IRQHandler
#define RETARGET_IRQn     LEUART0_IRQn
#define RETARGET_LEUART   1
#define RETARGET_LOCATION LEUART_ROUTE_LOCATION_LOC1
#define RETARGET_PERIPHERAL_ENABLE()
#define RETARGET_RX       LEUART_Rx
#define RETARGET_RXPIN    14
#define RETARGET_RXPORT   gpioPortB
#define RETARGET_TX       LEUART_Tx
#define RETARGET_TXPIN    13
#define RETARGET_TXPORT   gpioPortB
#define RETARGET_UART     LEUART0

#endif /* _RETARGETSERIALCONFIG_H */

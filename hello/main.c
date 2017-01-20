/*
 * Copyright 2017 Peter Chubb
 * 
 *  Licensed under the Apache Licence, Version 2.0 (the "Licence");
 * you may not use this file except in compliance with the Licence.
 *  You may obtain a copy of the Licence at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the Licence is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the Licence for the specific language governing permissions and
 * limitations under the Licence.
 */

#include <stdint.h>
#include <stdbool.h>

#include <em_cmu.h>
#include <em_leuart.h>
#define baudrate 115200

static void
write_char(int c)
{
    while (!(LEUART0->STATUS & LEUART_STATUS_TXBL))
        ;
// Not implemented in Qemu yet
//    while (LEUART0->SYNCBUSY & LEUART_SYNCBUSY_TXDATA)
//        ;

    LEUART0->TXDATA = (uint32_t)c & 0xffUL;
}

int puts(const char *s)
{
    while (*s)
        write_char(*s++);
    write_char('\n');
    write_char('\r');
    return 0;
}

static void init_uart(void)
{
    int clkdiv;

    clkdiv  = 32 * CMU_ClockFreqGet(cmuClock_LEUART0) + baudrate/2;
    clkdiv /= baudrate;
    clkdiv -= 32;
    clkdiv *= 8;

    LEUART0->CLKDIV = clkdiv;
    LEUART0->ROUTE = LEUART_ROUTE_LOCATION_LOC3 | USART_ROUTE_RXPEN | USART_ROUTE_TXPEN;
    LEUART0->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX | USART_CMD_RXEN | USART_CMD_TXEN;
    LEUART0->CMD = leuartEnable;
}

int
main(void)
{
    init_uart();
    for (;;) {
        puts("Hello!");
    }
}

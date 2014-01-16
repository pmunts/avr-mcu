/* Basic UART polling serial console driver */

// $Id$

// $Id$

// Copyright (C)2013-2014, Philip Munts, President, Munts AM Corp.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include "cpu.h"
#include "uart.h"

#include <avr/interrupt.h>

// The following hodgepodge of macros are an attempt to make sense of the
// myriad variations of serial ports in the AVR family.

// Serial console is on FIRST serial port

#if defined(CONFIG_CONSOLE_UART0) || (!defined(CONFIG_CONSOLE_UART0) && !defined(CONFIG_CONSOLE_UART1))

#if defined(UDR)
#define zzUDR		UDR
#elif defined(UDR0)
#define zzUDR		UDR0
#elif defined(UDR1)
#define zzUDR		UDR1
#endif

#if defined(UBRRH)
#define zzUBRRH		UBRRH
#elif defined(UBRR0H)
#define zzUBRRH		UBRR0H
#elif defined(UBRR1H)
#define zzUBRRH		UBRR1H
#endif

#if defined(UBRRL)
#define zzUBRRL		UBRRL
#elif defined(UBRR0)
#define zzUBRRL		UBRR0
#elif defined(UBRR0L)
#define zzUBRRL		UBRR0L
#elif defined(UBRR1)
#define zzUBRRL		UBRR1
#elif defined(UBRR1L)
#define zzUBRRL		UBRR1L
#endif

#if defined(UCSRA)
#define zzUCSRA		UCSRA
#elif defined(UCSR0A)
#define zzUCSRA		UCSR0A
#elif defined(UCSR1A)
#define zzUCSRA		UCSR1A
#endif

#if defined(UCSRB)
#define zzUCSRB		UCSRB
#elif defined(UCSR0B)
#define zzUCSRB		UCSR0B
#elif defined(UCSR1B)
#define zzUCSRB		UCSR1B
#endif

#if defined(UCSRC)
#define zzUCSRC		UCSRC
#elif defined(UCSR0C)
#define zzUCSRC		UCSR0C
#elif defined(UCSR1C)
#define zzUCSRC		UCSR1C
#endif

#if defined(U2X)
#define zzU2X		U2X
#elif defined(U2X0)
#define zzU2X		U2X0
#elif defined(U2X1)
#define zzU2X		U2X1
#endif

#if defined(RXEN)
#define zzRXEN		RXEN
#elif defined(RXEN0)
#define zzRXEN		RXEN0
#elif defined(RXEN1)
#define zzRXEN		RXEN1
#endif

#if defined(TXEN)
#define zzTXEN		TXEN
#elif defined(TXEN0)
#define zzTXEN		TXEN0
#elif defined(TXEN1)
#define zzTXEN		TXEN1
#endif

#if defined(RXCIE)
#define zzRXCIE		RXCIE
#elif defined(RXCIE0)
#define zzRXCIE		RXCIE0
#elif defined(RXCIE1)
#define zzRXCIE		RXCIE1
#endif

#if defined(UDRE)
#define zzUDRE		UDRE
#elif defined(UDRE0)
#define zzUDRE		UDRE0
#elif defined(UDRE1)
#define zzUDRE		UDRE1
#endif

#if defined(UCSZ0)
#define zzUCSZ0		UCSZ0
#elif defined(UCSZ00)
#define zzUCSZ0		UCSZ00
#elif defined(UCSZ10)
#define zzUCSZ0		UCSZ10
#endif

#if defined(UCSZ1)
#define zzUCSZ1		UCSZ1
#elif defined(UCSZ01)
#define zzUCSZ1		UCSZ01
#elif defined(UCSZ11)
#define zzUCSZ1		UCSZ11
#endif

#if defined(URSEL)
#define zzURSEL		URSEL
#elif defined(URSEL0)
#define zzURSEL		URSEL0
#elif defined(URSEL1)
#define zzURSEL		URSEL1
#endif

#if defined(UART_RX_vect)
#define zzUART_RX_vect	UART_RX_vect
#elif defined(UART0_RX_vect)
#define zzUART_RX_vect	UART0_RX_vect
#elif defined(USART_RX_vect)
#define zzUART_RX_vect	USART_RX_vect
#elif defined(USART_RXC_vect)
#define zzUART_RX_vect	USART_RXC_vect
#elif defined(USARTRXC_vect)
#define zzUART_RX_vect	USARTRXC_vect
#elif defined(USART0_RX_vect)
#define zzUART_RX_vect	USART0_RX_vect
#elif defined(USART0_RXC_vect)
#define zzUART_RX_vect	USART0_RXC_vect
#elif defined(UART1_RX_vect)
#define zzUART_RX_vect	UART1_RX_vect
#elif defined(USART1_RX_vect)
#define zzUART_RX_vect	USART1_RX_vect
#elif defined(USART1_RXC_vect)
#define zzUART_RX_vect	USART1_RXC_vect
#endif

#endif

// Serial console is on SECOND serial port

#if defined(CONFIG_CONSOLE_UART1)

#if defined(UDR1)
#define zzUDR		UDR1
#else
#error Cannot find UDR
#endif

#if defined(UBRR1H)
#define zzUBRRH		UBRR1H
#elif defined(UBRRH)
#define zzUBRRH		UBRRH
#endif

#if defined(UBRR1)
#define zzUBRRL		UBRR1
#elif defined(UBRR1L)
#define zzUBRRL		UBRR1L
#endif

#if defined(UCSR1A)
#define zzUCSRA		UCSR1A
#endif

#if defined(UCSR1B)
#define zzUCSRB		UCSR1B
#endif

#if defined(UCSR1C)
#define zzUCSRC		UCSR1C
#endif

#if defined(U2X1)
#define zzU2X		U2X1
#elif defined(U2X)
#define zzU2X		U2X
#endif

#if defined(RXEN1)
#define zzRXEN		RXEN1
#elif defined(RXEN)
#define zzRXEN		RXEN
#endif

#if defined(TXEN1)
#define zzTXEN		TXEN1
#elif defined(TXEN)
#define zzTXEN		TXEN
#endif

#if defined(RXCIE1)
#define zzRXCIE		RXCIE1
#elif defined (RXCIE)
#define zzRXCIE		RXCIE
#endif

#if defined(UDRE1)
#define zzUDRE		UDRE1
#elif defined(UDRE)
#define zzUDRE		UDRE
#endif

#if defined(UCSZ10)
#define zzUCSZ0		UCSZ10
#endif

#if defined(UCSZ11)
#define zzUCSZ1		UCSZ11
#endif

#if defined(URSEL1)
#define zzURSEL		URSEL1
#endif

#if defined(UART1_RX_vect)
#define zzUART_RX_vect	UART1_RX_vect
#elif defined(USART1_RX_vect)
#define zzUART_RX_vect	USART1_RX_vect
#elif defined(USART1_RXC_vect)
#define zzUART_RX_vect	USART1_RXC_vect
#endif

#endif

#ifdef zzUDR
void uart_init(unsigned long int baudrate)
{
  unsigned int b;

  zzUDR = 0;

  b = F_CPU/8/baudrate - 1;
  zzUBRRH = b / 256;
  zzUBRRL = b % 256;
  zzUCSRA = _BV(zzU2X);
  zzUCSRB = _BV(zzTXEN) | _BV(zzRXEN) | _BV(zzRXCIE);
#ifdef zzUCSRC
#ifdef zzURSEL
  zzUCSRC = _BV(zzURSEL) | _BV(zzUCSZ1) | _BV(zzUCSZ0);
#else
  zzUCSRC = _BV(zzUCSZ1) | _BV(zzUCSZ0);
#endif
#endif

  sei();
}

int uart_putch(char c)
{
  while (bit_is_clear(zzUCSRA, zzUDRE))
    wdt_reset();

  zzUDR = c;
  return 0;
}

/* Serial port receive buffer */

#define RXBUFSIZE	64

volatile unsigned char UART_Rcv_head;
volatile unsigned char UART_Rcv_tail;
volatile unsigned int  UART_Rcv_count;
volatile unsigned char UART_Rcv_buf[RXBUFSIZE];

/* Serial port receive interrupt service routine */

ISR(zzUART_RX_vect)
{
  unsigned char c;

  c = zzUDR;

  if (UART_Rcv_count < RXBUFSIZE)
  {
    UART_Rcv_buf[UART_Rcv_tail] = c;
    UART_Rcv_count++;
    UART_Rcv_tail++;
    UART_Rcv_tail &= RXBUFSIZE-1;
  }
}

/* Serial port receive standard I/O driver routine */

int uart_getch(void)
{
  char c;

  if (UART_Rcv_count == 0)
    return -1;

  c = UART_Rcv_buf[UART_Rcv_head];

  UART_Rcv_count--;
  UART_Rcv_head++;
  UART_Rcv_head &= RXBUFSIZE-1;

  return c;
}

/* Serial port receive ready routine */

int uart_available(void)
{
  return UART_Rcv_count;
}
#endif

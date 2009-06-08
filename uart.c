/* Basic UART polling serial console driver */

// $Id$

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <stdio.h>

#include "uart.h"

// Define compatibility macros

#ifndef UDR0
#define UDR0	UDR
#endif

#ifndef UBRR0H
#define UBRR0H	UBRRH
#endif

#ifndef UBRR0L
#define UBRR0L	UBRRL
#endif

#ifndef UCSR0A
#define UCSR0A	UCSRA
#endif

#ifndef UCSR0B
#define UCSR0B	UCSRB
#endif

#ifndef UCSR0C
#define UCSR0C	UCSRC
#endif

#ifndef U2X0
#define U2X0	U2X
#endif

#ifndef UCSZ00
#define UCSZ00	UCSZ0
#endif

#ifndef UCSZ01
#define UCSZ01	UCSZ1
#endif

#ifndef UDRE0
#define UDRE0	UDRE
#endif

#ifndef RXC0
#define RXC0	RXC
#endif

#ifndef RXEN0
#define RXEN0	RXEN
#endif

#ifndef TXEN0
#define TXEN0	TXEN
#endif

#ifndef RXCIE0
#define RXCIE0	RXCIE
#endif

#ifndef UART0_RX_vect
#ifdef UART_RX_vect
#define UART0_RX_vect UART_RX_vect
#endif
#ifdef USART0_RXC_vect
#define UART0_RX_vect USART0_RXC_vect
#endif
#ifdef USART0_RX_vect
#define UART0_RX_vect USART0_RX_vect
#endif
#ifdef USART_RXC_vect
#define UART0_RX_vect USART_RXC_vect
#endif
#ifdef USART_RX_vect
#define UART0_RX_vect USART_RX_vect
#endif
#endif

#ifndef UART0_TX_vect
#ifdef UART_TX_vect
#define UART0_TX_vect UART_TX_vect
#endif
#ifdef USART0_TXC_vect
#define UART0_TX_vect USART0_TXC_vect
#endif
#ifdef USART0_TX_vect
#define UART0_TX_vect USART0_TX_vect
#endif
#ifdef USART_TXC_vect
#define UART0_TX_vect USART_TXC_vect
#endif
#ifdef USART_TX_vect
#define UART0_TX_vect USART_TX_vect
#endif
#endif

unsigned long int CPUFREQ = 16000000L;

void uart_init(unsigned long int baudrate)
{
  unsigned int b;

  UDR0 = 0;

  b = CPUFREQ/8/baudrate - 1;
  UBRR0H = b / 256;
  UBRR0L = b % 256;
  UCSR0A = _BV(U2X0);
  UCSR0B = _BV(TXEN0) | _BV(RXEN0) | _BV(RXCIE0);
#ifdef URSEL
  UCSR0C = _BV(URSEL) | _BV(UCSZ01) | _BV(UCSZ00);
#else
  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
#endif

  sei();
}

int uart_putch(char c, FILE *f)
{
  if (c == '\n') uart_putch('\r', f);

#ifdef CTS_ASSERTED
  while (!CTS_ASSERTED)
    wdt_reset();
#endif

  while (bit_is_clear(UCSR0A, UDRE0))
    wdt_reset();

  UDR0 = c;
  return 0;
}

/* Serial port 0 receive buffer */

#define RXBUFSIZE	64

volatile unsigned char UART0_Rcv_head;
volatile unsigned char UART0_Rcv_tail;
volatile unsigned int  UART0_Rcv_count;
volatile unsigned char UART0_Rcv_buf[RXBUFSIZE];

/* Serial port 0 receive interrupt service routine */

ISR(UART0_RX_vect)
{
  unsigned char c;

  c = UDR0;

#ifdef DEASSERT_RTS
  if (UART0_Rcv_count > RXBUFSIZE - 10)
    DEASSERT_RTS;
#endif

#ifdef ASSERT_RTS
  if (UART0_Rcv_count < RXBUFSIZE - 20)
    ASSERT_RTS;
#endif

  if (UART0_Rcv_count < RXBUFSIZE)
  {
    UART0_Rcv_buf[UART0_Rcv_tail] = c;
    UART0_Rcv_count++;
    UART0_Rcv_tail++;
    UART0_Rcv_tail &= RXBUFSIZE-1;
  }
}

/* Serial port 0 receive standard I/O driver routine */

int uart_getch(FILE *f)
{
  char c;

  if (UART0_Rcv_count == 0)
    return _FDEV_ERR;

  c = UART0_Rcv_buf[UART0_Rcv_head];

  UART0_Rcv_count--;
  UART0_Rcv_head++;
  UART0_Rcv_head &= RXBUFSIZE-1;

  return c;
}

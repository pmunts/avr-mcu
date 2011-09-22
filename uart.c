/* Basic UART polling serial console driver */

// $Id$

#include "cpu.h"
#include "uart.h"

#include <avr/interrupt.h>

// The following parts only have USART1

#ifdef __AVR_AT90USB1286__
#define CONFIG_UART1
#endif

// Catch-all: default to U(S)ART0

#if !defined(UDR) && !defined(CONFIG_UART0) && !defined(CONFIG_UART1)
#define CONFIG_UART0
#endif

// Define compatibility macros

#ifdef CONFIG_UART0
#define UDR UDR0
#define UBRRH UBRR0H
#define UBRRL UBRR0L
#define UCSRA UCSR0A
#define UCSRB UCSR0B
#define UCSRC UCSR0C
#ifndef U2X
#define U2X U2X0
#endif
#ifndef RXEN
#define RXEN RXEN0
#endif
#ifndef TXEN
#define TXEN TXEN0
#endif
#ifndef RXCIE
#define RXCIE RXCIE0
#endif
#ifndef UDRE
#define UDRE UDRE0
#endif
#ifndef UCSZ0
#define UCSZ0 UCSZ00
#endif
#ifndef UCSZ1
#define UCSZ1 UCSZ01
#endif
#ifdef URSEL0
#define URSEL URSEL0
#endif
#ifdef UART0_RX_vect
#define USART_RX_vect UART0_RX_vect
#endif
#ifdef USART0_RX_vect
#define USART_RX_vect USART0_RX_vect
#endif
#ifdef USART0_RXC_vect
#define USART_RX_vect USART0_RXC_vect
#endif
#endif

#ifdef CONFIG_UART1
#define UDR UDR1
#define UBRRH UBRR1H
#define UBRRL UBRR1L
#define UCSRA UCSR1A
#define UCSRB UCSR1B
#define UCSRC UCSR1C
#ifndef U2X
#define U2X U2X1
#endif
#ifndef RXEN
#define RXEN RXEN1
#endif
#ifndef TXEN
#define TXEN TXEN1
#endif
#ifndef RXCIE
#define RXCIE RXCIE1
#endif
#ifndef UDRE
#define UDRE UDRE1
#endif
#ifndef UCSZ0
#define UCSZ0 UCSZ10
#endif
#ifndef UCSZ1
#define UCSZ1 UCSZ11
#endif
#ifdef URSEL1
#define URSEL URSEL1
#endif
#ifdef UART1_RX_vect
#define USART_RX_vect UART1_RX_vect
#endif
#ifdef USART1_RX_vect
#define USART_RX_vect USART1_RX_vect
#endif
#ifdef USART0_RXC_vect
#define USART_RX_vect USART0_RXC_vect
#endif
#endif

// For older parts with UART instead of USART

#if !defined(USART_RX_vect) && defined(UART_RX_vect)
#define USART_RX_vect UART_RX_vect
#endif

// For ATmega32 and possibly others

#if !defined(USART_RX_vect) && defined(USART_RXC_vect)
#define USART_RX_vect USART_RXC_vect
#endif

#ifdef UDR
void uart_init(unsigned long int baudrate)
{
  unsigned int b;

  UDR = 0;

  b = F_CPU/8/baudrate - 1;
  UBRRH = b / 256;
  UBRRL = b % 256;
  UCSRA = _BV(U2X);
  UCSRB = _BV(TXEN) | _BV(RXEN) | _BV(RXCIE);
#ifdef URSEL
  UCSRC = _BV(URSEL) | _BV(UCSZ1) | _BV(UCSZ0);
#else
  UCSRC = _BV(UCSZ1) | _BV(UCSZ0);
#endif

  sei();
}

int uart_putch(char c)
{
#ifdef CTS_ASSERTED
  while (!CTS_ASSERTED)
    wdt_reset();
#endif

  while (bit_is_clear(UCSRA, UDRE))
    wdt_reset();

  UDR = c;
  return 0;
}

/* Serial port receive buffer */

#define RXBUFSIZE	64

volatile unsigned char UART_Rcv_head;
volatile unsigned char UART_Rcv_tail;
volatile unsigned int  UART_Rcv_count;
volatile unsigned char UART_Rcv_buf[RXBUFSIZE];

/* Serial port receive interrupt service routine */

ISR(USART_RX_vect)
{
  unsigned char c;

  c = UDR;

#ifdef DEASSERT_RTS
  if (UART_Rcv_count > RXBUFSIZE - 10)
    DEASSERT_RTS;
#endif

#ifdef ASSERT_RTS
  if (UART_Rcv_count < RXBUFSIZE - 20)
    ASSERT_RTS;
#endif

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

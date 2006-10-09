/* Basic UART polling serial console driver */

// $Id: uart.c,v 1.5 2006-10-09 04:31:31 cvs Exp $

#include <avr/io.h>
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

unsigned long int CPUFREQ = 16000000L;

void uart_init(unsigned long int baudrate)
{
  unsigned int b;

  UDR0 = 0;

  b = CPUFREQ/8/baudrate - 1;
  UBRR0H = b / 256;
  UBRR0L = b % 256;
  UCSR0A = _BV(U2X);
  UCSR0B = _BV(TXEN0) | _BV(RXEN0);
#ifdef URSEL
  UCSR0C = _BV(URSEL) | _BV(UCSZ01) | _BV(UCSZ00);
#else
  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
#endif
}

int uart_putch(char c, FILE *f)
{
  if (c == '\n') uart_putch('\r', f);
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;
  return 0;
}

int uart_getch(FILE *f)
{
  loop_until_bit_is_set(UCSR0A, RXC0);
  return UDR0;
}

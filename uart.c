/* Basic UART polling serial console driver */

// $Id: uart.c,v 1.4 2006-10-06 14:42:54 cvs Exp $

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

unsigned long int CPUFREQ = 16000000;

void uart_init(unsigned long int baudrate)
{
  unsigned int b;

  UDR0 = 0;

  b = CPUFREQ/(16L*baudrate) - 1;
  UBRR0H = b / 256;
  UBRR0L = b % 256;
  UCSR0A = 0x00;
  UCSR0B = _BV(TXEN0) | _BV(RXEN0);
  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
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

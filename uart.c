/* Basic UART polling serial console driver */

// $Id: uart.c,v 1.2 2006-07-12 17:17:11 cvs Exp $

#include <avr/io.h>
#include <stdio.h>

#include "uart.h"

unsigned long int CPUFREQ = 16000000;

void uart_init(unsigned long int baudrate)
{
  unsigned int b;

  UDR0 = 0;

  b = CPUFREQ/(16L*baudrate) - 1;
  UBRR0H = b / 256;
  UBRR0L = b % 256;
  UCSR0A = 0x00;
  UCSR0B = _BV(TXEN) | _BV(RXEN);
  UCSR0C = _BV(UCSZ1) | _BV(UCSZ0);
}

int uart_putch(char c, FILE *f)
{
  if (c == '\n') uart_putch('\r', f);
  loop_until_bit_is_set(UCSR0A, UDRE);
  UDR0 = c;
  return 0;
}

int uart_getch(FILE *f)
{
  loop_until_bit_is_set(UCSR0A, RXC);
  return UDR0;
}

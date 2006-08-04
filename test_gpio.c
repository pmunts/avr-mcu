/* Simple bit twiddler test program */

// $Id: test_gpio.c,v 1.2 2006-08-04 15:53:13 cvs Exp $

#include <avr/io.h>
#include <avr/wdt.h>

int main(void)
{
  unsigned char a;

  wdt_disable();

#ifndef __AVR_ATmega168__
  DDRA = 0xFF;
#endif
  DDRB = 0xFF;
  DDRC = 0xFF;
  DDRD = 0xFF;
#ifdef __AVR_ATmega128__
  DDRE = 0xFF;
  DDRF = 0xFF;
  DDRG = 0xFF;
#endif

  for (a = 0;; a++)
  {
#ifndef __AVR_ATmega168__
    PORTA = a;
#endif
    PORTB = a;
    PORTC = a;
    PORTD = a;
#ifdef __AVR_ATmega128__
    PORTE = a;
    PORTF = a;
    PORTG = a;
#endif
  }
}

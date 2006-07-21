/* Simple bit twiddler test program */

// $Id: test_gpio.c,v 1.1 2006-07-21 20:19:31 cvs Exp $

#include <avr/io.h>
#include <avr/wdt.h>

int main(void)
{
  unsigned char a;

  wdt_disable();

  DDRA = 0xFF;
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
    PORTA = a;
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

/* Simple bit twiddler test program */

// $Id$

#include "cpu.h"

int main(void)
{
  unsigned char a;

  wdt_disable();

#ifdef DDRA
  DDRA = 0xFF;
#endif
#ifdef DDRB
  DDRB = 0xFF;
#endif
#ifdef DDRC
  DDRC = 0xFF;
#endif
#ifdef DDRD
  DDRD = 0xFF;
#endif
#ifdef DDRE
  DDRE = 0xFF;
#endif
#ifdef DDRF
  DDRF = 0xFF;
#endif
#ifdef DDRG
  DDRG = 0xFF;
#endif

  for (a = 0;; a++)
  {
#ifdef PORTA
    PORTA = a;
#endif
#ifdef PORTB
    PORTB = a;
#endif
#ifdef PORTC
    PORTC = a;
#endif
#ifdef PORTD
    PORTD = a;
#endif
#ifdef PORTE
    PORTE = a;
#endif
#ifdef PORTF
    PORTF = a;
#endif
#ifdef PORTG
    PORTG = a;
#endif
  }
}

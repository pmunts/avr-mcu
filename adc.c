/* Basic polling Analog to Digital driver */

// $Id$

#include "cpu.h"

#ifdef ADEN
unsigned short int ReadADC(unsigned char channel)
{
  unsigned short int result;

  ADCSRA = _BV(ADEN) + _BV(ADIF) + 7;			// Turn ADC on

  ADMUX = _BV(REFS0) + _BV(ADLAR) + channel;		// Select channel

  ADCSRA = _BV(ADEN) + _BV(ADSC) + 7;			// Start conversion

  loop_until_bit_is_set(ADCSRA, ADIF);			// Wait until done

  result = ADCL;					// Calculate result
  result += ADCH << 8;

  ADCSRA = 0x00;					// Turn ADC off

  return result;					// Return result
}
#endif

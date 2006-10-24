/* Basic polling Analog to Digital driver */

// $Id: adc.c,v 1.1 2006-10-24 18:13:52 cvs Exp $

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "adc.h"

unsigned short int ReadADC(unsigned char channel)
{
#ifdef ADEN
  unsigned short int result;

  ADCSRA = _BV(ADEN) + _BV(ADIF) + 7;			// Turn ADC on

  ADMUX = _BV(REFS0) + _BV(ADLAR) + channel;		// Select channel

  ADCSRA = _BV(ADEN) + _BV(ADSC) + 7;			// Start conversion

  loop_until_bit_is_set(ADCSRA, ADIF);			// Wait until done

  result = ADCL;					// Calculate result
  result += ADCH << 8;

  ADCSRA = 0x00;					// Turn ADC off

  return result;					// Return result
#else
  return 0;
#endif
}

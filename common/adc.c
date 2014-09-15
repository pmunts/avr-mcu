/* Basic polling Analog to Digital driver */

// $Id$

// Copyright (C)2013-2014, Philip Munts, President, Munts AM Corp.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

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

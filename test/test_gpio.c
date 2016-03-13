/* Simple bit twiddler test program */

// $Id: test_gpio.c 9918 2016-02-09 07:53:15Z svn $

// Copyright (C)2013-2016, Philip Munts, President, Munts AM Corp.
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

/* CPU dependent definitions */

// $Id$

#ifndef F_CPU
#define F_CPU 16000000L
#endif

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>

#include <util/delay.h>

#include "adc.h"
#include "conio.h"

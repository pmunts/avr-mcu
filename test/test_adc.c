/* Simple A/D test program */

// $Id$

static const char revision[] = "$Id$";

#include <stdio.h>

#include "cpu.h"

#ifndef BAUDRATE
#define BAUDRATE 115200
#endif

int main(void)
{
  int channel;

  wdt_disable();

  conio_init(BAUDRATE);

  puts("\033[H\033[2JAtmel AVR Analog to Digital Converter Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s\n\n", F_CPU, __VERSION__);

  for (;;)
  {
    for (channel = 0; channel < 4; channel++)
      printf("Channel %d is %04d ", channel, ReadADC(channel));

    putchar('\r');
  }
}

/* Simple standard I/O test program */

// $Id: test_conio.c,v 1.2 2007-02-12 20:59:07 cvs Exp $

#include <avr/wdt.h>

#include <stdio.h>
#include <string.h>

#include "conio.h"

#ifndef BAUDRATE
#define BAUDRATE 115200
#endif

int main(void)
{
  char buf[32];

  wdt_disable();

  conio_init(BAUDRATE);

  puts("\033[H\033[2JAtmel AVR Console I/O Test\n");

  for (;;)
  {
    printf("Enter a string: ");
    fgets(buf, sizeof(buf), stdin);
    if (strlen(buf)) if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0;
    printf("You entered %d bytes, '%s'\n", strlen(buf), buf);
  }
}

/* Simple serial console services */

// $Id: conio.c,v 1.3 2006-07-12 17:01:17 cvs Exp $

#include <stdio.h>
#include <string.h>

#include "conio.h"
#include "uart.h"

/* Initialize UART and bind it to stdin, stdout, and stderr */

void conio_init(unsigned long int baudrate)
{
  uart_init(baudrate);

  fdevopen(uart_putch, uart_getch);
}

/* Put a string without trailing newline */

void cputs(char *s)
{
  while (*s) putchar(*s++);
}

/* Override fgets() with a version that does line editing */

char *fgets(char *s, int bufsize, FILE *f)
{
  char *p;
  int c;

  memset(s, 0, bufsize);

  p = s;

  for (p = s; p < s + bufsize-1;)
  {
    c = getchar();
    switch (c)
    {
      case '\r' :
      case '\n' :
        putchar('\r');
        putchar('\n');
        *p = '\n';
        return s;

      case '\b' :
        if (p > s)
        {
          *p-- = 0;
          putchar('\b');
          putchar(' ');
          putchar('\b');
        }
        break;

      default :
        putchar(c);
        *p++ = c;
        break;
    }
  }

  return s;
}

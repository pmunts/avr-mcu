/* Simple serial console services */

// $Id: conio.c,v 1.1 2006-07-12 00:02:06 cvs Exp $

#include <stdio.h>

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

/* Override gets() with a version that does line editing */

char *gets(char *s)
{
  char *p;
  int c;

  p = s;

  for (;;)
  {
    c = getchar();
    switch (c)
    {
      case '\r' :
      case '\n' :
        putchar('\r');
        putchar('\n');
        *p = 0;
        return s;

      case '\b' :
        if (p > s)
        {
          p--;
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
}

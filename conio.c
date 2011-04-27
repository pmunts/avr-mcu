/* Simple serial console services */

// $Id$

#include <stdio.h>
#include <string.h>

#include "conio.h"
#include "uart.h"

extern void usbserial_conio_init(void);
extern int usbserial_getch(FILE *f);

/* Initialize UART and bind it to stdin, stdout, and stderr */

void conio_init(unsigned long int baudrate)
{
#ifdef CONSOLE_USB
  usbserial_conio_init();
  usbserial_getch(stdin);
#else
  uart_init(baudrate);
  fdevopen(uart_putch, uart_getch);
#endif
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
      case EOF :
        break;

      case '\r' :
      case '\n' :
        putchar('\r');
        putchar('\n');
        *p = '\n';
        return s;

      case '\b' :
      case 127 :
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

/* Simple serial console services */

// $Id$

#include <stdio.h>
#include <string.h>

#include "cpu.h"
#include "conio.h"
#include "uart.h"
#include "usb_serial.h"

static FILE mystdout = FDEV_SETUP_STREAM(conio_putch, NULL, _FDEV_SETUP_WRITE);
static FILE mystdin = FDEV_SETUP_STREAM(NULL, conio_getch, _FDEV_SETUP_READ);

static char linebuffer[255];
static char *lineptr = linebuffer;
static unsigned char linecount = 0;

void conio_init(unsigned long int baudrate)
{
#ifdef CONSOLE_USB
  usb_init();
  getch();
#else
  uart_init(baudrate);
#endif

// Bind standard streams to console I/O subsystem

  stdin = &mystdin;
  stdout = &mystdout;
  stderr = &mystdout;
}

// AVR-libc standard I/O library device driver output function

int conio_putch(char c, FILE *f)
{
  putch(c);
  return 0;
}

// AVR-libc standard I/O library device driver input function

int conio_getch(FILE *f)
{
  char c;

// Get a line if we have no data available

  if (linecount == 0)
    linecount = cgets(linebuffer, sizeof(linebuffer));

// Return byte from the current line

  c = *lineptr++;

  if (--linecount == 0)
    lineptr = linebuffer;

  return c;
}

// Send 1 character to console device

void putch(char c)
{
  if (c == '\n') putch('\r');

#ifdef CONSOLE_USB
  while (usb_serial_putchar(c) < 0)
    wdt_reset();
#else
  uart_putch(c);
#endif
}

// Send a string to console device

void cputs(char *s)
{
  while (*s) putch(*s++);
}

// Check for data available from console device

int keypressed(void)
{
#ifdef CONSOLE_USB
  return usb_serial_available();
#else
  return uart_available();
#endif
}

// Receive 1 character from console device

int getch(void)
{
  int c;

#ifdef CONSOLE_USB
  while ((c = usb_serial_getchar()) < 0)
    wdt_reset();

  return c;
#else
  return uart_getch();
#endif
}

// Receive a line from console device

int cgets(char *s, int size)
{
  char *p = s;
  char c;

  memset(s, 0, size);

  for (;;)
  {
    c = getch();

    switch (c)
    {
      case '\r' :
      case '\n' :
        cputs("\r\n");
        *p++ = '\n';
        return p - s;
        break;

      case '\b' :
      case 127 :
        if (p > s)
        {
          *p-- = 0;
          cputs("\b \b");
        }
        break;

      default :
        putch(c);
        *p++ = c;
        if ((p - s) >= size)
          return size;
        break;
    }
  }
}

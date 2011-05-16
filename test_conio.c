/* Simple serial console I/O test program */

// $Id$

static const char revision[] = "$Id$";

#define __ASSERT_USE_STDERR

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "conio.h"

#ifndef BAUDRATE
#define BAUDRATE 115200
#endif

int main(void)
{
  int i;
  char buf[256];
  int x, y;
  const char spinner[] = "|/-\\";
  wdt_disable();

  conio_init(BAUDRATE);

  puts("\033[H\033[2JAtmel AVR Console I/O Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s\n\n", F_CPU, __VERSION__);

// Test putch()

  for (i = 'A'; i < 'Z'; i++)
    putch(i);

  putch('\n');
  putch('\n');

// Test cputs()

  for (i = 0; i < 10; i++)
  {
    sprintf(buf, "The value of the variable i is currently, now, until the next iteration, %d\n", i);
    cputs(buf);
  }

// Test keypressed() and getch()

  cputs("\nPress ^C to continue: ");

  for (i = 0;;)
  {
    putch(spinner[i]);
    putch('\b');
    if (++i == sizeof(spinner)-1) i = 0;

    if (keypressed())
    {
      if (getch() == 3)
        break;
      else
        putch('.');
    }

    _delay_ms(75.0);
  }

  putch('\n');
  putch('\n');

// Test cputs() and cgets()

  for (;;)
  {
    cputs("[cgets] Enter a string: ");
    cgets(buf, sizeof(buf));
    if (strlen(buf)) if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0;
    if (!strcasecmp(buf, "next")) break;
    printf("[cgets] You entered %d bytes, '%s'\n\n", strlen(buf), buf);
  }

// Test putchar()

  putchar('\n');

  for (i = 'a'; i < 'z'; i++)
    putchar(i);

  putchar('\n');
  putchar('\n');

// Test printf() and fgets()

  for (;;)
  {
    printf("[fgets] Enter a string: ");
    fflush(stdout);
    fgets(buf, sizeof(buf), stdin);
    if (strlen(buf)) if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0;
    if (!strcasecmp(buf, "next")) break;
    printf("[fgets] You entered %d bytes, '%s'\n\n", strlen(buf), buf);
  }

  putchar('\n');

// Test scanf()

  for (;;)
  {
    printf("Enter two numbers: ");
    fflush(stdout);

    fflush(stdin);
    scanf("%d %d", &x, &y);
    printf("You entered %d and %d\n", x, y);

    if ((x == 0) && (y == 0)) break;
  }

  assert(0);
}

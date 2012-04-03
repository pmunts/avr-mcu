/* Simple serial console services */

// $Id$

#include <stdio.h>

void conio_init(unsigned long int baudrate);

int conio_putch(char c, FILE *f);

int conio_getch(FILE *f);

// The following low level unbuffered I/O functions are vaguely
// inspired by Turbo Pascal and Turbo C console I/O services

void putch(char c);

void cputs(char *s);

int keypressed(void);

int getch(void);

int cgets(char *s, int size);

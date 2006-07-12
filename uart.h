/* Basic UART polling serial console driver */

// $Id: uart.h,v 1.1 2006-07-12 00:02:06 cvs Exp $

#include <stdio.h>

void uart_init(unsigned long int baudrate);
int uart_putch(char c, FILE *f);
int uart_getch(FILE *f);

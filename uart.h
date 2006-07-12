/* Basic UART polling serial console driver */

// $Id: uart.h,v 1.2 2006-07-12 17:17:11 cvs Exp $

#include <stdio.h>

extern unsigned long int CPUFREQ;

void uart_init(unsigned long int baudrate);

int uart_putch(char c, FILE *f);

int uart_getch(FILE *f);

/* Basic UART polling serial console driver */

// $Id$

#include <stdio.h>

extern unsigned long int CPUFREQ;

void uart_init(unsigned long int baudrate);

int uart_putch(char c, FILE *f);

int uart_getch(FILE *f);

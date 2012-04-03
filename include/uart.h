/* Basic serial port driver */

// $Id$

void uart_init(unsigned long int baudrate);

int uart_putch(char c);

int uart_getch(void);

int uart_available(void);

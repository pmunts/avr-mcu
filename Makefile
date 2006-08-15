# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id: Makefile,v 1.14 2006-08-15 19:22:00 cvs Exp $

include AVR.mk

libmunts.a: conio.o uart.o
	$(AR) -r libmunts.a $?

ATmega168_USB:
	$(MAKE) MCU=atmega128 ATmega168_USB.download

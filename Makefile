# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id: Makefile,v 1.15 2006-08-17 19:12:29 cvs Exp $

include AVR.mk

libmunts.a: conio.o uart.o
	$(AR) -r libmunts.a $?

ATmega168_USB:
	$(MAKE) MCU=atmega168 ATmega168_USB.download

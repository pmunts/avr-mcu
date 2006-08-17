# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id: Makefile,v 1.16 2006-08-17 19:35:37 cvs Exp $

include AVR.mk

ATmega168_USB:
	$(MAKE) MCU=atmega168 ATmega168_USB.download

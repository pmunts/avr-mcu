# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id: Makefile,v 1.17 2006-08-17 19:52:19 cvs Exp $

include AVR.mk

ATmega168_USB.hex:
	$(MAKE) -f AVR.mk ATmega168_USB.hex MCU=atmega168

ATmega168_USB.download:
	$(MAKE) -f AVR.mk ATmega168_USB.download MCU=atmega168

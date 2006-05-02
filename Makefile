# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id: Makefile,v 1.7 2006-05-02 23:08:51 cvs Exp $

.include <AVR.mk>

MCU		= atmega8515

# Define default rule placeholder

default:
	@echo You must specify an explicit target!

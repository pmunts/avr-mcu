# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id: Makefile,v 1.13 2006-07-12 23:40:07 cvs Exp $

include AVR.mk

libmunts.a: conio.o uart.o
	$(AR) -r libmunts.a $?

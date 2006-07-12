# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id: Makefile,v 1.12 2006-07-12 00:02:06 cvs Exp $

include AVR.mk

libmunts.a: conio.o uart.o
	ar -r libmunts.a $?

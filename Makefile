# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id: Makefile,v 1.2 2006-04-27 16:44:22 cvs Exp $

AVRBIN		= /usr/local/atmel/bin
CC		= $(AVRBIN)/avr-gcc
LD		= $(AVRBIN)/avr-ld
STRIP		= $(AVRBIN)/avr-strip
OBJCOPY		= $(AVRBIN)/avr-objcopy
OBJDUMP		= $(AVRBIN)/avr-objdump

MCU		= atmega8515
CFLAGS		= -g -O -Wall -mmcu=$(MCU)

# Define suffix rules

.SUFFIXES: .asm .bin .hex .o

.bin.asm:
	$(OBJDUMP) -S -d $< >$@

.c.bin:
	$(CC) $(CFLAGS) -o $@ $<

.o.bin:
	$(CC) $(CFLAGS) -o $@ $<

.bin.hex:
	$(OBJCOPY) -O ihex $< $@

# Define default rule placeholder

default:
	@echo You must specify an explicit target!

# Update from CVS repository

update:
	cvs -q update -I ! 2>&1 | grep -v CVS

# Clean out working files

clean:
	rm -f *.o *.bin *.hex 

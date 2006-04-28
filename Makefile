# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id: Makefile,v 1.3 2006-04-28 15:53:11 cvs Exp $

AVRBIN		= /export/software/Linux/atmel/bin
CC		= $(AVRBIN)/avr-gcc
LD		= $(AVRBIN)/avr-ld
STRIP		= $(AVRBIN)/avr-strip
OBJCOPY		= $(AVRBIN)/avr-objcopy
OBJDUMP		= $(AVRBIN)/avr-objdump

MCU		= atmega8515
CFLAGS		= -g -O -Wall -mmcu=$(MCU)

# Define suffix rules

.SUFFIXES: .asm .bin .hex .o

.c.bin:
	$(CC) $(CFLAGS) -o $@ $<

.o.bin:
	$(CC) $(CFLAGS) -o $@ $<

.bin.asm:
	$(OBJDUMP) -S -d $< >$@

.bin.hex:
	$(OBJCOPY) -O ihex $< $@

.S.o:
	$(CC) $(CFLAGS) -o $@ -c $<

# Define default rule placeholder

default:
	@echo You must specify an explicit target!

# Update from CVS repository

update:
	cvs -q update -I ! 2>&1 | grep -v CVS

# Clean out working files

clean:
	rm -f *.asm *.bin *.hex *.o

# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id: Makefile,v 1.6 2006-04-28 16:19:23 cvs Exp $

AVRBIN		= /export/software/Linux/atmel/bin
CC		= $(AVRBIN)/avr-gcc
LD		= $(AVRBIN)/avr-ld
STRIP		= $(AVRBIN)/avr-strip
OBJCOPY		= $(AVRBIN)/avr-objcopy
OBJDUMP		= $(AVRBIN)/avr-objdump

MCU		= atmega8515
CFLAGS		= -g -O -Wall -mmcu=$(MCU) -DMCU=$(MCU) $(EXTRAFLAGS)

# Define suffix rules

.SUFFIXES: .asm .elf .hex .o

.c.elf:
	$(CC) $(CFLAGS) -o $@ $< $(EXTRAOBJS)

.o.elf:
	$(CC) $(CFLAGS) -o $@ $< $(EXTRAOBJS)

.elf.asm:
	$(OBJDUMP) -S -d $< >$@

.elf.hex:
	$(OBJCOPY) -S -O ihex $< $@

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
	rm -f *.asm *.elf *.hex *.o

# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id: AVR.mk,v 1.10 2006-07-06 15:45:13 cvs Exp $

AVRTOOLS	?= /usr/local/avr-tools
CC		= $(AVRTOOLS)/bin/avr-gcc
LD		= $(AVRTOOLS)/bin/avr-ld
STRIP		= $(AVRTOOLS)/bin/avr-strip
OBJCOPY		= $(AVRTOOLS)/bin/avr-objcopy
OBJDUMP		= $(AVRTOOLS)/bin/avr-objdump

MCU		= atmega128

CFLAGS		= -g -O -Wall -mmcu=$(MCU) -DMCU_$(MCU) $(EXTRAFLAGS)

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

# Define default target placeholder

default:
	@echo You must explicitly specify the target

# Update from CVS repository

update:
	@-cvs -q update -I ! 2>&1 | grep -v CVS

# Clean out working files

clean:
	rm -f *.asm *.elf *.hex *.o

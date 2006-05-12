# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id: AVR.mk,v 1.4 2006-05-12 22:26:01 cvs Exp $

AVR		?= /usr/local/avr
AVRBIN		= $(AVR)/bin
CC		= $(AVRBIN)/avr-gcc
LD		= $(AVRBIN)/avr-ld
STRIP		= $(AVRBIN)/avr-strip
OBJCOPY		= $(AVRBIN)/avr-objcopy
OBJDUMP		= $(AVRBIN)/avr-objdump

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

# Define default target placeholder

default:
	@echo You must explicitly specify the target

# Update from CVS repository

update:
	@-cvs -q update -I ! 2>&1 | grep -v CVS

# Clean out working files

clean:
	rm -f *.asm *.elf *.hex *.o

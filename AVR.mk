# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id: AVR.mk,v 1.14 2006-07-12 16:55:30 cvs Exp $

AVRTOOLS	?= /usr/local/avr-tools
CC		= $(AVRTOOLS)/bin/avr-gcc
LD		= $(AVRTOOLS)/bin/avr-ld
AR		= $(AVRTOOLS)/bin/avr-ar
STRIP		= $(AVRTOOLS)/bin/avr-strip
OBJCOPY		= $(AVRTOOLS)/bin/avr-objcopy
OBJDUMP		= $(AVRTOOLS)/bin/avr-objdump

AVRPROGRAM	?= /c/PROGRA~1/Atmel/AVRTOO~1/STK500/STK500.exe -cUSB -d$(MCU) -e -pf -vf -if

MCU		= atmega128
FREQ		= 16000000L

CFLAGS		= -g -O -Wall -mmcu=$(MCU) -DMCU_$(MCU) -DFREQ=$(FREQ) -L . $(EXTRAFLAGS)

# Define default target placeholder

default:
	@echo You must explicitly specify the target

# These are the target suffixes

.SUFFIXES: .asm .elf .hex .o .download

# Don't delete intermediate files

.SECONDARY:

# Now define some suffix rules

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.o.elf:
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $< -lmunts $(EXTRAOBJS)

.elf.asm:
	$(OBJDUMP) -S -d $< >$@

.elf.hex:
	$(OBJCOPY) -S -O ihex $< $@

.hex.download:
	$(AVRPROGRAM)$<

.S.o:
	$(CC) $(CFLAGS) -o $@ -c $<

# Update from CVS repository

update:
	@-cvs -q update -I ! 2>&1 | grep -v CVS

# Clean out working files

clean:
	rm -f *.asm *.elf *.hex *.o

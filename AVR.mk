# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id: AVR.mk,v 1.30 2008-02-27 08:27:07 cvs Exp $

AVRTOOLS	?= /usr/local/avr-tools
CC		= $(AVRTOOLS)/bin/avr-gcc
LD		= $(AVRTOOLS)/bin/avr-ld
AR		= $(AVRTOOLS)/bin/avr-ar
STRIP		= $(AVRTOOLS)/bin/avr-strip
OBJCOPY		= $(AVRTOOLS)/bin/avr-objcopy
OBJDUMP		= $(AVRTOOLS)/bin/avr-objdump

MCU		?= UNDEFINED
AVRPROGRAM	?= $(AVRDUDE)avrdude -p $(MCU) -c avrispmkII -P usb -v -U flash:w:
AVRSRC		?= .

CFLAGS		= -g -O -Wall -I$(AVRSRC) -mmcu=$(MCU) $(DEBUG) $(EXTRAFLAGS)
LDFLAGS		= -L $(AVRSRC)

# Define default target placeholder

default_catch:
	@echo ERROR: You must explicitly specify the target
	@exit 1

# These targets are not files

.PHONY: default_catch update clean

# These are the target suffixes

.SUFFIXES: .asm .elf .hex .o .program

# Don't delete intermediate files

.SECONDARY:

# Now define some suffix rules

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.o.elf:
	cd $(AVRSRC) && $(MAKE) lib$(MCU).a MCU=$(MCU)
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $< -l$(MCU) $(EXTRAOBJS)

.elf.asm:
	$(OBJDUMP) -S -d $< >$@

.elf.hex:
	$(OBJCOPY) -S -O ihex $< $@

.hex.program:
	$(AVRPROGRAM)$<

.s.o:
	$(CC) $(CFLAGS) -o $@ -c $<

.S.o:
	$(CC) $(CFLAGS) -o $@ -c $<

# Update from CVS repository

update:
	@-cvs -q update -I ! 2>&1 | grep -v CVS

# Clean out working files

clean:
	rm -f *.asm *.elf *.hex *.o *.a
	@if [ "$(AVRSRC)" != "$(PWD)" ]; then cd $(AVRSRC); rm -f *.asm *.elf *.hex *.o *.a ; fi

# Build processor dependent libraries

lib$(MCU).a: conio.o uart.o adc.o
	$(AR) -r lib$(MCU).a $?

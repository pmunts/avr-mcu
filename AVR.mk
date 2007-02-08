# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id: AVR.mk,v 1.25 2007-02-08 23:52:16 cvs Exp $

AVRTOOLS	?= /usr/local/avr-tools
CC		= $(AVRTOOLS)/bin/avr-gcc
LD		= $(AVRTOOLS)/bin/avr-ld
AR		= $(AVRTOOLS)/bin/avr-ar
STRIP		= $(AVRTOOLS)/bin/avr-strip
OBJCOPY		= $(AVRTOOLS)/bin/avr-objcopy
OBJDUMP		= $(AVRTOOLS)/bin/avr-objdump

MCU		?= UNDEFINED
AVRPROGRAM	?= /c/PROGRA~1/Atmel/AVRTOO~1/STK500/Stk500 -cUSB -d$(MCU) -e -pf -vf -if
AVRSRC		?= .

CFLAGS		= -g -O -Wall -I$(AVRSRC) -mmcu=$(MCU) $(EXTRAFLAGS) $(DEBUG)
LDFLAGS		= -L $(AVRSRC)

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
	cd $(AVRSRC) && $(MAKE) libmunts-$(MCU).a MCU=$(MCU)
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $< -lmunts-$(MCU) $(EXTRAOBJS)

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
	rm -f *.asm *.elf *.hex *.o *.a
	@if [ "$(AVRSRC)" != "$(PWD)" ]; then cd $(AVRSRC); rm -f *.asm *.elf *.hex *.o *.a ; fi

# Build processor dependent libraries

libmunts-$(MCU).a: conio.o uart.o adc.o
	$(AR) -r libmunts-$(MCU).a $?

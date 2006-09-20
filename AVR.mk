# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id: AVR.mk,v 1.19 2006-09-20 05:37:27 cvs Exp $

AVRTOOLS	?= /usr/local/avr-tools
CC		= $(AVRTOOLS)/bin/avr-gcc
LD		= $(AVRTOOLS)/bin/avr-ld
AR		= $(AVRTOOLS)/bin/avr-ar
STRIP		= $(AVRTOOLS)/bin/avr-strip
OBJCOPY		= $(AVRTOOLS)/bin/avr-objcopy
OBJDUMP		= $(AVRTOOLS)/bin/avr-objdump

MCU		?= UNDEFINED
AVRPROGRAM	?= /c/PROGRA~1/Atmel/AVRTOO~1/STK500/STK500.exe -cUSB -d$(MCU) -e -pf -vf -if
AVRSRC		?= .

CFLAGS		= -g -O -Wall -I$(AVRSRC) -mmcu=$(MCU) $(EXTRAFLAGS)
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

libmunts-$(MCU).a: conio.o uart.o
	$(AR) -r libmunts-$(MCU).a $?

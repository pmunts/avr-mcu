# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id: AVR.mk,v 1.16 2006-08-17 19:35:37 cvs Exp $

AVRTOOLS	?= /usr/local/avr-tools
CC		= $(AVRTOOLS)/bin/avr-gcc
LD		= $(AVRTOOLS)/bin/avr-ld
AR		= $(AVRTOOLS)/bin/avr-ar
STRIP		= $(AVRTOOLS)/bin/avr-strip
OBJCOPY		= $(AVRTOOLS)/bin/avr-objcopy
OBJDUMP		= $(AVRTOOLS)/bin/avr-objdump

AVRPROGRAM	?= /c/PROGRA~1/Atmel/AVRTOO~1/STK500/STK500.exe -cUSB -d$(MCU) -e -pf -vf -if

MCU		= atmega128
CFLAGS		= -g -O -Wall -mmcu=$(MCU) $(EXTRAFLAGS)
LDFLAGS		= -L .

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
	$(MAKE) libmunts-$(MCU).a MCU=$(MCU)
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
	rm -f *.asm *.elf *.hex *.o

reallyclean: clean
	rm -f *.a

# Build processor dependent libraries

libmunts-$(MCU).a: conio.o uart.o
	$(AR) -r libmunts-$(MCU).a $?

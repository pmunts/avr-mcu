# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id: AVR.mk,v 1.34 2008-10-06 23:13:11 cvs Exp $

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
LDFLAGS		= -L$(AVRSRC) -l$(MCU) -Wl,-Map,$*.map,--cref $(EXTRAOBJS)

# These targets are not files

.PHONY: default_catch update clean

# These are the target suffixes

.SUFFIXES: .asm .bin .elf .hex .o .program

# Don't delete intermediate files

.SECONDARY:

# Define default target placeholder

default_catch:
	@echo ERROR: You must explicitly specify a make target
	@exit 1

# Now define some suffix rules

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.o.elf:
	cd $(AVRSRC) && $(MAKE) lib$(MCU).a MCU=$(MCU)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

.elf.asm:
	$(OBJDUMP) -S -d $< >$@

.elf.bin:
	$(OBJCOPY) -S -O binary --gap-fill=0 $< $@

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
	rm -f *.a *.asm *.bin *.elf *.hex *.map *.o $(AVRSRC)/*.a $(AVRSRC)/*.o

# Build processor dependent libraries

lib$(MCU).a: conio.o uart.o adc.o
	$(AR) -r lib$(MCU).a $?

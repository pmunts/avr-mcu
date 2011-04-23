# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id$

AVRSRC		?= .

AVRTOOLS	?= /usr/local/avr-tools
CROSS_COMPILE	?= $(AVRTOOLS)/bin/avr-

CC		= $(CROSS_COMPILE)gcc
LD		= $(CROSS_COMPILE)ld
AR		= $(CROSS_COMPILE)ar
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump

MCU		?= UNDEFINED

AVRPROGRAM	?= avrdude -p $(MCU) -c avrispmkII -P usb -v -U flash:w:
TEENSY		?= /usr/local/bin/teensy_loader_cli

CFLAGS		= -g -O -Wall -I$(AVRSRC) -mmcu=$(MCU) $(DEBUG) $(EXTRAFLAGS)
LDFLAGS		= -L$(AVRSRC) -l$(MCU) -Wl,-Map,$*.map,--cref $(EXTRAOBJS)

# These targets are not files

.PHONY: default_catch update clean

# These are the target suffixes

.SUFFIXES: .asm .bin .elf .hex .o .program .teensy

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

.hex.teensy:
	$(TEENSY) -mmcu=$(MCU) -w -v $<

.s.o:
	$(CC) $(CFLAGS) -o $@ -c $<

.S.o:
	$(CC) $(CFLAGS) -o $@ -c $<

# Update from source code repository

update:
	svn status
	svn update

# Clean out working files

clean:
	rm -f *.a *.asm *.bin *.elf *.hex *.map *.o $(AVRSRC)/*.a $(AVRSRC)/*.o

# Build processor dependent libraries

lib$(MCU).a: conio.o uart.o adc.o
	$(AR) -r lib$(MCU).a $?

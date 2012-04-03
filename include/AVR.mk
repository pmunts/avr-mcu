# Generic Makefile for compiling Atmel AVR microcontroller firmware

# $Id$

AVRSRC		?= ..

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

CPUFLAGS	+= -mmcu=$(MCU)
CONFIGFLAGS	?=
DEBUGFLAGS	?= -g
OPTFLAGS	?= -O0
IOFLAGS		?=
EXTRAFLAGS	?=
CFLAGS		+= -Wall
CFLAGS		+= -I$(AVRSRC)/include -I.
CFLAGS		+= $(CPUFLAGS) $(OPTFLAGS) $(CONFIGFLAGS) $(IOFLAGS) $(DEBUGFLAGS) $(EXTRAFLAGS)
LDFLAGS		= -L. -l$(MCU) -Wl,-Map,$*.map,--cref $(EXTRAOBJS)

# These targets are not files

.PHONY: default_catch lib update clean

# These are the target suffixes

.SUFFIXES: .asm .c .bin .elf .hex .o .program .teensy .s .S

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
	$(MAKE) lib$(MCU).a MCU=$(MCU)
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

# Support for common library functions

COMMON_DIR	= $(AVRSRC)/common
include $(COMMON_DIR)/common.mk

# Build processor dependent libraries

lib$(MCU).a: common_lib

lib: lib$(MCU).a

# Update from source code repository

update:
	svn status --no-ignore
	svn update

# Clean out working files

clean:
	rm -f *.a *.asm *.bin *.elf *.hex *.map *.o
	$(MAKE) common_clean

# Generic Makefile for compiling Atmel AVR microcontroller firmware

# Copyright (C)2013-2018, Philip Munts, President, Munts AM Corp.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the following disclaimer.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

AVRTOOLS	?= /usr/local/avr-mcu-tools
CROSS_COMPILE	?= $(AVRTOOLS)/bin/avr-

CC		= $(CROSS_COMPILE)gcc
LD		= $(CROSS_COMPILE)ld
AR		= $(CROSS_COMPILE)ar
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump

MCU		?= UNDEFINED

CPUFLAGS	+= -mmcu=$(MCU)
CONFIGFLAGS	?=
DEBUGFLAGS	?= -g
OPTFLAGS	?= -O0
IOFLAGS		?=
EXTRAFLAGS	?=
CFLAGS		+= -Wall
CFLAGS		+= -I$(AVRSRC)/gcc/include -I.
CFLAGS		+= $(CPUFLAGS) $(OPTFLAGS) $(CONFIGFLAGS) $(IOFLAGS) $(DEBUGFLAGS) $(EXTRAFLAGS)
LDFLAGS		= -L. -l$(MCU) -Wl,-Map,$*.map,--cref $(EXTRAOBJS)

# These targets are not files

.PHONY: AVR_mk_default AVR_mk_clean lib

# These are the target suffixes

.SUFFIXES: .asm .c .bin .elf .hex .o .program .teensy .s .S

# Don't delete intermediate files

.SECONDARY:

# Define default target placeholder

AVR_mk_default:
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

.s.o:
	$(CC) $(CFLAGS) -o $@ -c $<

.S.o:
	$(CC) $(CFLAGS) -o $@ -c $<

# Support for common library functions

COMMON_DIR	= $(AVRSRC)/gcc/common
include $(COMMON_DIR)/common.mk

# Build processor dependent libraries

lib$(MCU).a: common_lib

lib: lib$(MCU).a

# Clean out working files

AVR_mk_clean:
	rm -f *.a *.asm *.bin *.elf *.hex *.map *.o
	$(MAKE) common_clean

# Include subordinate makefiles

include $(AVRSRC)/include/avrdude.mk
include $(AVRSRC)/include/teensy.mk

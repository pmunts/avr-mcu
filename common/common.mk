# Common library make definitions

# $Id$

COMMON_DIR	?= $(AVRSRC)/common
CFLAGS		+= -I$(COMMON_DIR)

.PHONY: common_lib common_clean

COMMON_OBJS	= $(COMMON_DIR)/adc.o $(COMMON_DIR)/conio.o		\
		  $(COMMON_DIR)/uart.o $(COMMON_DIR)/usb_serial.o

# Add common object files to the MCU library

common_lib: $(COMMON_OBJS)
	$(AR) crs lib$(MCU).a $(COMMON_OBJS)

# Remove common object files

common_clean:
	rm -f $(COMMON_OBJS)

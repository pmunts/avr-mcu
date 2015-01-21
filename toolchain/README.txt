                      AVR Microcontroller Toolchain Notes

   This toolchain includes binutils, gcc, and [1]avr-libc. It may be built
   for Linux, OpenBSD, and Windows (using Cygwin). The Linux, OpenBSD and
   Windows releases are virtually identical in every respect. (This is the
   reason I created my own toolchain: I routinely flip back and forth
   among Linux, OpenBSD, and Windows development environments.)

   I use the [2]Atmel AVRISP mkII and [3]avrdude for in system
   programming. Since avrdude is rather OS dependent, and native binaries
   are available for all of the environments I am interested in, I do not
   include it in my toolchain.
     __________________________________________________________________

   Questions or comments to [4]phil@munts.net

   $Id$

References

   1. http://www.nongnu.org/avr-libc
   2. http://www.atmel.com/dyn/products/tools_card.asp?tool_id=3808
   3. http://www.nongnu.org/avrdude
   4. mailto:phil@munts.net

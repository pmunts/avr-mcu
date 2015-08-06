                      AVR Microcontroller Toolchain Notes

   This toolchain includes binutils, gcc, and avr-libc. It may be built
   for Linux, MacOS (using [1]Fink), OpenBSD, and Windows (using
   [2]Cygwin) development hosts. The toolchains produce identical results
   on every host operating system: This is the reason I created my own
   toolchain; I routinely flip back and forth among Linux, MacOS, OpenBSD,
   and Windows development environments. It is even possible to build the
   toolchain as a [3]Canadian Cross to run on a small Linux system such as
   the [4]Raspberry Pi. See [5]Makefile.rpi for an example.

   I use the [6]Atmel AVRISP mkII and [7]avrdude for in system
   programming. Since avrdude is rather OS dependent, and native binaries
   are available for all of the environments I am interested in, I do not
   include it in my toolchain.
     __________________________________________________________________

   Questions or comments to [8]phil@munts.net

   $Id$

References

   1. http://www.finkproject.org/
   2. http://www.cygwin.com/
   3. http://en.wikipedia.org/wiki/Cross_compiler#Canadian_Cross
   4. http://www.raspberrypi.org/
   5. http://tech.munts.com/MCU/Frameworks/AVR/toolchain/Makefile.rpi
   6. http://www.atmel.com/dyn/products/tools_card.asp?tool_id=3808
   7. http://www.nongnu.org/avrdude
   8. mailto:phil@munts.net

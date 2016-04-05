                      AVR Microcontroller Toolchain Notes

   This toolchain includes binutils, gcc, and avr-libc. It may be built
   for Linux, MacOS (using [1]Fink or [2]MacPorts), OpenBSD, and Windows
   (using [3]Cygwin) development hosts. The toolchains produce identical
   results on every host operating system: This is the reason I created my
   own toolchain; I routinely flip back and forth among Linux, MacOS,
   OpenBSD, and Windows development environments. It is even possible to
   build the toolchain as a [4]Canadian Cross to run on a small Linux
   system such as the [5]Raspberry Pi or the [6]BeagleBone. See
   [7]Makefile.cross for details.

   I use the [8]Atmel AVRISP mkII and [9]avrdude for in system
   programming. Since avrdude is rather OS dependent, and native binaries
   are available for all of the environments I am interested in, I do not
   include it in my toolchain.

   Prebuilt toolchain packages are available at:
   [10]http://repo.munts.com.
   _______________________________________________________________________

   Questions or comments to [11]phil@munts.net

   I am available for custom system development (hardware and software) of
   products using AVR or other microcontrollers.

References

   1. http://www.finkproject.org/
   2. http://www.macports.org/
   3. http://www.cygwin.com/
   4. http://en.wikipedia.org/wiki/Cross_compiler#Canadian_Cross
   5. http://www.raspberrypi.org/
   6. http://beagleboard.org/bone
   7. http://tech.munts.com/MCU/Frameworks/AVR/toolchain/Makefile.cross
   8. http://www.atmel.com/dyn/products/tools_card.asp?tool_id=3808
   9. http://www.nongnu.org/avrdude
  10. http://repo.munts.com/
  11. mailto:phil@munts.net

# Download and build GNU toolchain for Atmel AVR microcontrollers

# $Id$

PKGNAME		= avr-tools
INSTBASE	= $(shell pwd)/$(PKGNAME)

TEMP		= /tmp

BINUTILVER	= 2.19.1
BINUTILSERVER	= ftp://ftp.gnu.org/pub/gnu/binutils
BINUTILDIST	= $(TEMP)/binutils-$(BINUTILVER).tar.gz
BINUTILURL	= $(BINUTILSERVER)/`basename $(BINUTILDIST)`
BINUTILSRC	= binutils-$(BINUTILVER)

GCCVER		= 4.4.0
GCCSERVER	= ftp://ftp.gnu.org/pub/gnu/gcc/gcc-$(GCCVER)
GCCDIST		= $(TEMP)/gcc-$(GCCVER).tar.bz2
GCCURL		= $(GCCSERVER)/`basename $(GCCDIST)`
GCCSRC		= gcc-$(GCCVER)
GCCOBJ		= gcc-$(GCCVER).obj

AVRLIBCVER	= 1.6.7
AVRLIBCSERVER	= http://download.savannah.gnu.org/releases/avr-libc
AVRLIBCDIST	= $(TEMP)/avr-libc-$(AVRLIBCVER).tar.bz2
AVRLIBCURL	= $(AVRLIBCSERVER)/`basename $(AVRLIBCDIST)`
AVRLIBCSRC	= avr-libc-$(AVRLIBCVER)

AVRLIBCMPDIST	= $(TEMP)/avr-libc-manpages-$(AVRLIBCVER).tar.bz2
AVRLIBCMPURL	= $(AVRLIBCSERVER)/`basename $(AVRLIBCMPDIST)`

AVRLIBCUMDIST	= $(TEMP)/avr-libc-user-manual-$(AVRLIBCVER).tar.bz2
AVRLIBCUMURL	= $(AVRLIBCSERVER)/`basename $(AVRLIBCUMDIST)`

ifeq ($(shell uname), CYGWIN_NT-5.1)
TARBALL		= $(PKGNAME)-cygwin.tgz
else
TARBALL		= $(PKGNAME)-$(shell uname -s)-$(shell uname -i).tgz
endif

default: $(TARBALL)

################################################################################

# Download binutils

$(BINUTILDIST):
	wget -P $(TEMP) $(BINUTILURL)

# Compile binutils

binutils.done: $(BINUTILDIST)
	rm -rf $(BINUTILSRC)
	tar xzf $(BINUTILDIST)
	cd $(BINUTILSRC) && ./configure --prefix=$(INSTBASE) --target=avr
	$(MAKE) -C $(BINUTILSRC)
ifeq ($(shell uname), Linux)
# Force static linking
	rm $(BINUTILSRC)/binutils/ar
	rm $(BINUTILSRC)/binutils/addr2line
	rm $(BINUTILSRC)/binutils/cxxfilt
	rm $(BINUTILSRC)/binutils/nm-new
	rm $(BINUTILSRC)/binutils/objcopy
	rm $(BINUTILSRC)/binutils/objdump
	rm $(BINUTILSRC)/binutils/ranlib
	rm $(BINUTILSRC)/binutils/readelf
	rm $(BINUTILSRC)/binutils/size
	rm $(BINUTILSRC)/binutils/strings
	rm $(BINUTILSRC)/binutils/strip-new
	rm $(BINUTILSRC)/gas/as-new
	rm $(BINUTILSRC)/gprof/gprof
	rm $(BINUTILSRC)/ld/ld-new
	$(MAKE) -C $(BINUTILSRC) LDFLAGS=-all-static
endif
	$(MAKE) -C $(BINUTILSRC) install
	touch binutils.done

################################################################################

# Download gcc

$(GCCDIST):
	wget -P $(TEMP) $(GCCURL)

# Compile gcc

# CentOS 4 needs GCCEXTRACONFIG=--with-mpfr=/usr/local

gcc.done: binutils.done $(GCCDIST)
	rm -rf $(GCCSRC)
	rm -rf $(GCCOBJ)
	tar xjf $(GCCDIST)
	mkdir -p $(GCCOBJ)
	cd $(GCCOBJ) && ../$(GCCSRC)/configure --prefix=$(INSTBASE) --target=avr --enable-languages=c --disable-libssp --disable-libgomp --disable-nls --disable-shared $(GCCEXTRACONFIG)
ifeq ($(shell uname), Linux)
# Force static linking
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(GCCOBJ) LDFLAGS=-static
else
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(GCCOBJ)
endif
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(GCCOBJ) install
	touch gcc.done

################################################################################

# Download avr-libc

$(AVRLIBCDIST):
	wget -P $(TEMP) $(AVRLIBCURL)
	wget -P $(TEMP) $(AVRLIBCMPURL)
	wget -P $(TEMP) $(AVRLIBCUMURL)

# Compile avr-libc

avr-libc.done: binutils.done gcc.done $(AVRLIBCDIST) $(AVRLIBCMPDIST) $(AVRLIBCUMDIST)
	rm -rf $(AVRLIBCSRC)
	tar xjf $(AVRLIBCDIST)
	export PATH=$$PATH':'$(INSTBASE)/bin && cd $(AVRLIBCSRC) && ./configure --prefix=$(INSTBASE) --host=avr
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(AVRLIBCSRC)
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(AVRLIBCSRC) install
	tar xjf $(AVRLIBCMPDIST) --directory=$(INSTBASE)
	tar xjf $(AVRLIBCUMDIST) --directory=$(INSTBASE)/share
	touch avr-libc.done

################################################################################

# Create installation tarball

$(TARBALL): binutils.done gcc.done avr-libc.done
	echo "GNU AVR microcontroller toolchain"	>$(INSTBASE)/README.txt
	echo " "					>>$(INSTBASE)/README.txt
	echo "Built on `date` from:"			>>$(INSTBASE)/README.txt
	echo " "					>>$(INSTBASE)/README.txt
	echo "$(BINUTILSRC)"				>>$(INSTBASE)/README.txt
	echo "$(GCCSRC)"				>>$(INSTBASE)/README.txt
	echo "$(AVRLIBCSRC)"				>>$(INSTBASE)/README.txt
	unix2dos $(INSTBASE)/README.txt
	chmod -R ugo-w $(INSTBASE)
ifeq ($(shell uname), Linux)
	sudo chown -R 0.0 $(INSTBASE)
endif
	tar czf $(TARBALL) `basename $(INSTBASE)`
ifeq ($(shell uname), Linux)
	sudo chown -R $(shell id -u).$(shell id -g) $(INSTBASE)
endif
	chmod -R u+w $(INSTBASE)

# Store tarball to repository

store: $(TARBALL)
	scp $(TARBALL) root@munts.net:/export/software/MCU

# Install tarball to /usr/local

install: $(TARBALL)
	tar xzf $(TARBALL) --directory=/usr/local

# Uninstall

uninstall:
	rm -rf /usr/local/$(PKGNAME)

# Clean out working files

clean:
	-rm *.done
	-rm $(PKGNAME)*.tgz
	rm -rf $(INSTBASE)
	rm -rf $(BINUTILSRC)
	rm -rf $(GCCSRC)
	rm -rf $(GCCOBJ)
	rm -rf $(AVRLIBCSRC)

distclean: clean
	-rm *.tgz *.tar.gz *.tar.bz2

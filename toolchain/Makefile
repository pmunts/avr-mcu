# Download and build GNU toolchain for Atmel AVR microcontrollers

# $Id: Makefile,v 1.1 2007-10-10 02:23:48 cvs Exp $

PKGNAME		= avr-tools
INSTBASE	= $(shell pwd)/$(PKGNAME)

TEMP		= /tmp

BINUTILVER	= 2.18
BINUTILSERVER	= ftp://ftp.gnu.org/pub/gnu/binutils
BINUTILDIST	= $(TEMP)/binutils-$(BINUTILVER).tar.gz
BINUTILURL	= $(BINUTILSERVER)/`basename $(BINUTILDIST)`
BINUTILSRC	= binutils-$(BINUTILVER)

GCCVER		= 4.2.1
GCCSERVER	= ftp://ftp.gnu.org/pub/gnu/gcc/gcc-$(GCCVER)
GCCDIST		= $(TEMP)/gcc-$(GCCVER).tar.bz2
GCCURL		= $(GCCSERVER)/`basename $(GCCDIST)`
GCCSRC		= gcc-$(GCCVER)

AVRLIBCVER	= 1.4.6
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
	$(MAKE) -C $(BINUTILSRC) install
	touch binutils.done

################################################################################

# Download gcc

$(GCCDIST):
	wget -P $(TEMP) $(GCCURL)

# Compile gcc

gcc.done: binutils.done $(GCCDIST)
	rm -rf $(GCCSRC)
	tar xjf $(GCCDIST)
	cd $(GCCSRC) && ./configure --prefix=$(INSTBASE) --target=avr --enable-languages=c --disable-libssp --disable-libgomp
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(GCCSRC)
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(GCCSRC) install
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
	echo "GNU AVR microcontroller toolchain"	>$(INSTBASE)/README
	echo " "					>>$(INSTBASE)/README
	echo "Built on `date` from:"			>>$(INSTBASE)/README
	echo " "					>>$(INSTBASE)/README
	echo "$(BINUTILSRC)"				>>$(INSTBASE)/README
	echo "$(GCCSRC)"				>>$(INSTBASE)/README
	echo "$(AVRLIBCSRC)"				>>$(INSTBASE)/README
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
	rm -rf $(AVRLIBCSRC)

distclean: clean
	-rm *.tgz *.tar.gz *.tar.bz2

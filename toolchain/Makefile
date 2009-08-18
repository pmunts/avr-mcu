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

GCCVER		= 4.4.1
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

VERSION		= $(BINUTILVER)_$(GCCVER)_$(AVRLIBCVER)
RELEASE		= 1

ifeq ($(shell uname), CYGWIN_NT-5.1)
TARBALL		= $(PKGNAME)-cygwin.tgz
else
TARBALL		= $(PKGNAME)-$(shell uname -s)-$(shell uname -i).tgz
endif

.PHONY: default download clean distclean

default: $(TARBALL)

################################################################################

# Download source distributions:

download: $(BINUTILDIST) $(GCCDIST) $(AVRLIBCDIST)

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

# CentOS 4 needs GCCEXTRACONFIG=--with-mpfr=/usr/local

gcc.done: binutils.done $(GCCDIST)
	rm -rf $(GCCSRC)
	rm -rf $(GCCOBJ)
	tar xjf $(GCCDIST)
	mkdir -p $(GCCOBJ)
	cd $(GCCOBJ) && ../$(GCCSRC)/configure --prefix=$(INSTBASE) --target=avr --enable-languages=c --disable-libssp --disable-libgomp --disable-nls --disable-shared $(GCCEXTRACONFIG)
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(GCCOBJ)
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

readme.done: binutils.done gcc.done avr-libc.done
	echo "GNU AVR microcontroller toolchain"	>$(INSTBASE)/README.txt
	echo " "					>>$(INSTBASE)/README.txt
	echo "Built on `date` from:"			>>$(INSTBASE)/README.txt
	echo " "					>>$(INSTBASE)/README.txt
	echo "$(BINUTILSRC)"				>>$(INSTBASE)/README.txt
	echo "$(GCCSRC)"				>>$(INSTBASE)/README.txt
	echo "$(AVRLIBCSRC)"				>>$(INSTBASE)/README.txt
	unix2dos $(INSTBASE)/README.txt
	touch readme.done

################################################################################

# Create toolchain tarball

tarball: readme.done
	tar czf $(TARBALL) `basename $(INSTBASE)` --owner=root --group=root --mode=ugo-w

################################################################################

# Create toolchain RPM package

fakeroot: readme.done
	mkdir -p fakeroot/usr/local
	cp -R -p avr-tools fakeroot/usr/local
	chmod -R -w fakeroot

specfile: specfile.template fakeroot
	sed s/@@VERSION@@/$(VERSION)/g <specfile.template | sed s/@@RELEASE@@/$(RELEASE)/g >specfile
	find fakeroot/usr/local/avr-tools -type d | awk '{ printf("%%dir /%s\n", substr($$1, 10)); }' >>specfile
	find fakeroot/usr/local/avr-tools -type f | cut -c 9- >>specfile

rpm: specfile
	mkdir -p rpmbuild/RPMS/$(MACHTYPE)
	rpmbuild --buildroot=`pwd`/fakeroot --define="_topdir `pwd`/rpmbuild" -bb specfile
	cp rpmbuild/RPMS/$(MACHTYPE)/*.rpm .

################################################################################

# Clean out working files

clean:
	-rm *.done
	-rm $(PKGNAME)*.tgz
	rm -rf $(INSTBASE)
	rm -rf $(BINUTILSRC)
	rm -rf $(GCCSRC)
	rm -rf $(GCCOBJ)
	rm -rf $(AVRLIBCSRC)
	rm -rf fakeroot specfile rpmbuild *.rpm

distclean: clean

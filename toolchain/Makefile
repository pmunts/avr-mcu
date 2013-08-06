# Download and build GNU toolchain for Atmel AVR microcontrollers

# $Id$

# Copyright (C)2013, Philip Munts, President, Munts AM Corp.
# All rights reserved.
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

PKGNAME		= avr-mcu-tools
INSTBASE	= $(shell pwd)/$(PKGNAME)

FIND		= find
TAR		= tar
TEMP		= /tmp

BINUTILVER	= 2.23.2
BINUTILSERVER	= http://ftp.gnu.org/pub/gnu/binutils
BINUTILDIST	= $(TEMP)/binutils-$(BINUTILVER).tar.bz2
BINUTILURL	= $(BINUTILSERVER)/`basename $(BINUTILDIST)`
BINUTILSRC	= binutils-$(BINUTILVER)

GCCVER		= 4.8.1
GCCSERVER	= http://ftp.gnu.org/pub/gnu/gcc/gcc-$(GCCVER)
GCCDIST		= $(TEMP)/gcc-$(GCCVER).tar.bz2
GCCURL		= $(GCCSERVER)/`basename $(GCCDIST)`
GCCSRC		= gcc-$(GCCVER)
GCCOBJ		= gcc-$(GCCVER).obj

AVRLIBCVER	= 1.8.0
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

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
TARBALL		= $(PKGNAME)-$(VERSION)-cygwin.tgz
else
TARBALL		= $(PKGNAME)-$(VERSION)-$(shell uname -s)-$(shell uname -i).tgz
endif

ifeq ($(shell uname), OpenBSD)
GCCEXTRACONFIG	+= --with-gmp=/usr/local
GCCEXTRACONFIG	+= --with-mpc=/usr/local
GCCEXTRACONFIG	+= --with-mpfr=/usr/local
PACKAGENAME	= $(PKGNAME)-$(VERSION).tgz
TAR		= gtar
endif

default: readme.done

################################################################################

# Download source distributions:

download: $(BINUTILDIST) $(GCCDIST) $(AVRLIBCDIST)

################################################################################

# Download binutils

$(BINUTILDIST):
	wget -nv -P $(TEMP) $(BINUTILURL)

# Compile binutils

binutils.done: $(BINUTILDIST)
	rm -rf $(BINUTILSRC)
	$(TAR) xjf $(BINUTILDIST)
	cd $(BINUTILSRC) && ./configure --prefix=$(INSTBASE) --target=avr --disable-lto --disable-nls --disable-shared --disable-werror
	$(MAKE) -C $(BINUTILSRC)
	$(MAKE) -C $(BINUTILSRC) install
	touch binutils.done

################################################################################

# Download gcc

$(GCCDIST):
	wget -nv -P $(TEMP) $(GCCURL)

# Compile gcc

gcc.done: binutils.done $(GCCDIST)
	rm -rf $(GCCSRC)
	rm -rf $(GCCOBJ)
	$(TAR) xjf $(GCCDIST)
	mkdir -p $(GCCOBJ)
	cd $(GCCOBJ) && ../$(GCCSRC)/configure --prefix=$(INSTBASE) --target=avr --disable-lto --enable-languages=c --disable-libssp --disable-libgomp --disable-nls --disable-shared --disable-werror $(GCCEXTRACONFIG)
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(GCCOBJ)
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(GCCOBJ) install
	touch gcc.done

################################################################################

# Download avr-libc

$(AVRLIBCDIST):
	wget -nv -P $(TEMP) $(AVRLIBCURL)
	wget -nv -P $(TEMP) $(AVRLIBCMPURL)
	wget -nv -P $(TEMP) $(AVRLIBCUMURL)

# Compile avr-libc

avr-libc.done: binutils.done gcc.done $(AVRLIBCDIST) $(AVRLIBCMPDIST) $(AVRLIBCUMDIST)
	rm -rf $(AVRLIBCSRC)
	$(TAR) xjf $(AVRLIBCDIST)
	export PATH=$$PATH':'$(INSTBASE)/bin && cd $(AVRLIBCSRC) && ./configure --prefix=$(INSTBASE) --host=avr
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(AVRLIBCSRC)
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(AVRLIBCSRC) install
	$(TAR) xjf $(AVRLIBCMPDIST) --directory=$(INSTBASE)
	$(TAR) xjf $(AVRLIBCUMDIST) --directory=$(INSTBASE)/share
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
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
	$(TAR) czf $(TARBALL) `basename $(INSTBASE)` --mode=ugo-w
else
	$(TAR) czf $(TARBALL) `basename $(INSTBASE)` --owner=root --group=root --mode=ugo-w
endif

################################################################################

# Create Linux RPM package

ifeq ($(shell uname), Linux)
fakeroot: readme.done
	mkdir -p fakeroot/usr/local
	cp -R -p $(PKGNAME) fakeroot/usr/local

specfile: specfile.template fakeroot
	sed s/@@PKGNAME@@/$(PKGNAME)/g <specfile.template | sed s/@@VERSION@@/$(VERSION)/g | sed s/@@RELEASE@@/$(RELEASE)/g >specfile
	$(FIND) fakeroot/usr/local/$(PKGNAME) -type d | awk '{ printf("%%dir /%s\n", substr($$1, 10)); }' >>specfile
	$(FIND) fakeroot/usr/local/$(PKGNAME) -type f | cut -c 9- >>specfile
	$(FIND) fakeroot/usr/local/$(PKGNAME) -type l | cut -c 9- >>specfile

rpm: specfile
	rpmbuild --buildroot=`pwd`/fakeroot --define="_topdir `pwd`/rpmbuild" -bb specfile
	cp rpmbuild/RPMS/*/*.rpm .
endif

################################################################################

# Create OpenBSD package

ifeq ($(shell uname), OpenBSD)

fakeroot: readme.done
	mkdir -p fakeroot/usr/local
	cp -R -p $(PKGNAME) fakeroot/usr/local

CONTENTS: fakeroot
	echo "@owner root"				>CONTENTS
	echo "@group wheel"				>>CONTENTS
	echo "@mode -w"					>>CONTENTS
	echo "@cwd /usr/local"				>>CONTENTS
	find fakeroot/usr/local/$(PKGNAME) -type d | awk '{ printf("@dir %s\n", substr($$1, 20)); }' >>CONTENTS
	find fakeroot -type f | cut -c 20- | sort	>>CONTENTS
	find fakeroot -type l | awk '{ printf("echo %s `readlink %s`\n", $$1, $$1); }' | sh | \
	awk '{ printf("@exec ln -s %s %s\n", $$2, substr($$1,9)); }'            >>CONTENTS
	find fakeroot -type l | awk '{ printf("@unexec rm %s\n", substr($$1, 9)); }' >>CONTENTS

COMMENT:
	echo "AVR Microcontroller Toolchain"		>COMMENT

$(PACKAGENAME): CONTENTS COMMENT
	pkg_create -A `uname -m` -f CONTENTS -D COMMENT="`cat COMMENT`" -d COMMENT -p / -B fakeroot $(PACKAGENAME)
	@-rm CONTENTS
	@-rm COMMENT

package: $(PACKAGENAME)
endif

################################################################################

# Clean out working files

clean:
	rm -rf $(INSTBASE)
	rm -rf $(BINUTILSRC)
	rm -rf $(GCCSRC)
	rm -rf $(GCCOBJ)
	rm -rf $(AVRLIBCSRC)
	rm -rf fakeroot specfile rpmbuild *.done *.rpm *.tgz

distclean: clean

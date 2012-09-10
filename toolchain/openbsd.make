# Makefile for building AVR toolchain for OpenBSD

# $Id$

MAKE		= gmake
TAR		= gtar

BINUTILVER	!= awk '/BINUTILVER.*=/ { print $$3 }'	<Makefile
GCCVER		!= awk '/GCCVER.*=/     { print $$3 }'	<Makefile
AVRLIBCVER	!= awk '/AVRLIBCVER.*=/ { print $$3 }'	<Makefile
PACKAGENAME	:= avr-tools-$(BINUTILVER)_$(GCCVER)_$(AVRLIBCVER).tgz

default_openbsd: $(PACKAGENAME)

fakeroot:
	$(MAKE) fakeroot TAR=$(TAR) GCCEXTRACONFIG="--with-gmp=/usr/local --with-mpc=/usr/local --with-mpfr=/usr/local"

CONTENTS: fakeroot
	echo "@owner root"				>CONTENTS
	echo "@group wheel"				>>CONTENTS
	echo "@mode -w"					>>CONTENTS
	echo "@cwd /usr/local"				>>CONTENTS
	find fakeroot/usr/local/avr-tools -type d | awk '{ printf("@dir %s\n", substr($$1, 20)); }' >>CONTENTS
	find fakeroot -type f | cut -c 20- | sort	>>CONTENTS

COMMENT:
	echo "AVR Microcontroller Toolchain"		>COMMENT

$(PACKAGENAME): CONTENTS COMMENT
	pkg_create -A `uname -m` -f CONTENTS -D COMMENT="`cat COMMENT`" -d COMMENT -p / -B fakeroot $(PACKAGENAME)
	@-rm CONTENTS
	@-rm COMMENT

clean:
	$(MAKE) clean

distclean:
	$(MAKE) distclean

CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs

TARGETS=	libstringutils.a \
		libstringutils.so \
		translate.o \
		translate-dynamic\
		translate-static

all:		$(TARGETS)

# TODO: Add rules for libstringutils.a libstringutils.soi

stringutils.o:	stringutils.c
	$(CC) $(CFLAGS) -fPIC -c -o stringutils.o stringutils.c

libstringutils.a:	stringutils.o
	$(AR) $(ARFLAGS) libstringutils.a stringutils.o

libstringutils.so:	stringutils.o
	$(LD) $(LDFLAGS) -shared -o libstringutils.so stringutils.o

translate.o:	translate.c
	$(CC) $(CFLAGS) -c -o translate.o translate.c

translate-dynamic:	translate.o
	$(LD) $(LDFLAGS) -o translate-dynamic translate.o -lstringutils

translate-static:	translate.o
	$(LD) $(LDFLAGS) -static -o translate-static translate.o -lstringutils

test:			test-libstringutils \
				test-translate

test-libstringutils:	libstringutils.so test_stringutils.py
	./test_stringutils.py -v

test-translate:			test_translate.py
	./test_translate.py -v

clean:
	rm -f $(TARGETS) *.o

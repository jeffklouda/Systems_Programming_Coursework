CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs
TARGETS=	freq entry fnv map libmap link-freq measure

all:		$(TARGETS)

#-------------------------------------------------------------------------------

# TODO: Add rules for test_entry, test_fnv, test_map, freq, measure

#-------------------------------------------------------------------------------
measure:	measure.c
	@echo Compiling measure.o...
	@$(CC) measure.c $(CFLAGS) -c -o measure.o
	@echo Linking measure...
	@$(LD) $(LDFLAGS) -o measure measure.o libmap.a

test:		test_entry test_fnv test_map test_freq \
			test-entry test-fnv test-map test-freq

test_entry:	test_entry.c libmap.a
	$(CC) test_entry.c $(CFLAGS) -c -o test_entry.o
	$(LD) $(LDFLAGS) -o test_entry test_entry.o libmap.a

test-entry:	test_entry
	@echo Testing entry...
	@[ `valgrind --leak-check=full ./test_entry 2>&1 | tee test_entry.log | grep ERROR | awk '{print $$4}'` = 0 ] && ! grep -q 'failed' test_entry.log || cat test_entry.log

test_fnv:	test_fnv.c libmap.a
	$(CC) test_fnv.c $(CFLAGS) -c -o test_fnv.o
	$(LD) $(LDFLAGS) -o test_fnv test_fnv.o libmap.a

test-fnv:	test_fnv
	@echo Testing fnv...
	@[ `valgrind --leak-check=full ./test_fnv 2>&1 | tee test_fnv.log | grep ERROR | awk '{print $$4}'` = 0 ] && ! grep -q 'failed' test_fnv.log || cat test_fnv.log

test_map:	test_map.c libmap.a
	$(CC) test_map.c $(CFLAGS) -c -o test_map.o
	$(LD) $(LDFLAGS) -o test_map test_map.o libmap.a

test-map:	test_map
	@echo "Testing map..."
	@[ `valgrind --leak-check=full ./test_map 2>&1 | tee test_map.log | grep ERROR | awk '{print $$4}'` = 0 ] && ! grep -q 'failed' test_map.log || cat test_map.log

test-freq:	test_freq.sh freq
	@echo "Testing freq..."
	@./test_freq.sh 2>&1 | tee test_freq.log
	@[ `valgrind --leak-check=full ./freq < map.h 2>&1 | tee test_freq.log | grep ERROR | awk '{print $$4}'` = 0 ] && ! grep -q 'failed' test_freq.log || cat test_freq.log

benchmark:	measure freq benchmark.py
	@echo Benchmarking
	@./benchmark.py

entry:	entry.c
	@echo compiling entry.o...
	@$(CC) entry.c $(CLAGS) -c -o entry.o

freq:	freq.c
	@echo compiling freq.o...
	@$(CC) freq.c $(CFLAGS) -c -o freq.o

fnv:	fnv.c
	@echo compiling fnv.o...
	@$(CC) fnv.c $(CFLAGS) -c -o fnv.o

map:	map.c
	@echo compiling map.o...
	@$(CC) map.c $(CFLAGS) -c -o map.o

libmap:	entry.o fnv.o map.o
	@echo Linking libmap.a...
	@$(AR) $(ARFLAGS) libmap.a entry.o fnv.o map.o

link-freq:	freq.o libmap.a
	@echo Linking freq
	@$(LD) $(LDFLAGS) -o freq freq.o libmap.a

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) test_entry test_fnv test_map measure *.a *.o *.log *.input

.PHONY:		all test benchmark clean

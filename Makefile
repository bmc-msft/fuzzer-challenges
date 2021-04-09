CC=clang
CFLAGS=-g3 -fsanitize=fuzzer -fsanitize=address
SOURCES=$(wildcard *.c)
BINS=$(SOURCES:.c=.exe)

%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $^

all:	$(BINS)

clean:
	rm -rf $(TARGETS) core* *~ *.log HONGGFUZZ.REPORT.TXT SIG* afl++.dic *.exe *.pdb *.exp *.lib out-* in

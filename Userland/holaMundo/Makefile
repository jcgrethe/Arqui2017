include ../Makefile.inc

MODULE=holaMundo.bin
ASMSOURCES= $(wildcard asm/*.asm)
SOURCES=$(wildcard [^_]*.c)
ASMOBJECTS=$(ASMSOURCES:.asm=.o)
COBJECTS=$(SOURCES:.c=.o)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c _loader.c $(SOURCES) 

%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

all: $(USER)

$(USER): $(ASMOBJECTS) $(COBJECTS)
	$(LD) -T holaMundo.ld _loader.o $(COBJECTS) $(ASMOBJECTS) -o ../$(MODULE)

clean:
	rm -rf *.o

.PHONY: all clean
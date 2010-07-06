CC = ncc
FASM = fasm
CFLAGS = -Os -I.

all: start.o libc.a

%.o: %.s
	$(FASM) $^ $@
%.o: %.c
	$(CC) $(CFLAGS) $^
libc.a: syscall.o string.o malloc.o atoi.o
	$(AR) rcs $@ $^

clean:
	rm -f *.o *.a

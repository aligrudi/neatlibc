CC = ncc
FASM = fasm
CFLAGS = -Os

all: start.o libc.a

%.o: %.s
	$(FASM) $^ $@
%.o: %.c
	$(CC) $(CFLAGS) $^
libc.a: syscall.o string.o
	$(AR) rcs $@ $^

clean:
	rm -f *.o *.a

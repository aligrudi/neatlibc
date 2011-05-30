# for x86 build
ARCH = x86
CC = ncc
AS = fasm

# for arm build
#ARCH = arm
#CC = ncc
#AS = neatas

CFLAGS = -Os -I.

all: start.o libc.a

%.o: %.s
	$(AS) $^ >/dev/null
%.o: %.c
	$(CC) $(CFLAGS) $^

OBJS = $(patsubst %.c,%.o,$(wildcard *.c))
OBJS2 = $(patsubst %.s,%.o,$(wildcard $(ARCH)/*.s))

start.o: $(ARCH)/start.o
	cp $(ARCH)/start.o .
libc.a: $(OBJS) $(OBJS2)
	$(AR) rcs $@ $^

clean:
	rm -f *.o *.a x86/*.o arm/*.o

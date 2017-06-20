CC      = gcc
CFLAGS  = -Wall -Werror
CFLAGS += -g
LDFLAGS = -g -pthread -lpthread

BINS    = tri-rapide

all: ${BINS}

tri-rapide: pile.o tri.o rapide.o main.o
	${CC} ${LDFLAGS} -o $@ $^

%.o: %.c %.h
	${CC} ${CFLAGS} -c $<
%.o: %.c
	${CC} ${CFLAGS} -c $<

clean:
	rm *.o || true

realclean: clean
	rm ${BINS} || true

.PHONY: all clean realclean test


test: all
	./test.sh

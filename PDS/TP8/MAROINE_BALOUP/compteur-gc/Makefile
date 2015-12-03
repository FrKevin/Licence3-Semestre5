CC      = gcc
CFLAGS  = -Wall -Werror
CFLAGS += -g
LDFLAGS = -g -pthread -lpthread

BINS    = aleazard compteur-gc

all: ${BINS}

aleazard: aleazard.o
	${CC} ${LDFLAGS} -o $@ $^

compteur-gc: compteur-gc.o
	${CC} ${LDFLAGS} -o $@ $^

%.o: %.c %.h
	${CC} ${CFLAGS} -c $<
%.o: %.c
	${CC} ${CFLAGS} -c $<

clean:
	rm *.o || true

realclean: clean
	rm ${BINS} *.adn *.dat *.png || true

.PHONY: all clean realclean test


test: all
	./test.sh

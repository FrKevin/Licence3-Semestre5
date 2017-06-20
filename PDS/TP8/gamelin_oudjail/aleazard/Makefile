# variable pour l'archive
TP=8
NOM1=Gamelin
NOM2=Oudjail

# source du projets
VPATH = src
OBJ = ./obj

CC      = gcc
CFLAGS  = -Wall -Werror
CFLAGS += -g
LDFLAGS = -g -pthread
EXECS    = aleazard compteur-gc
OBJS = aleazard.o compteur-gc.o

all: ${EXECS}
	rm -rf $(OBJ)/ || true
	mkdir $(OBJ)
	mv -f $(OBJS) $(OBJ)

aleazard: aleazard.o
	${CC} ${LDFLAGS} -o $@ $^

compteur-gc: compteur-gc.o
	${CC} ${LDFLAGS} -o $@ $^


%.o: %.c %.h
	${CC} ${CFLAGS} -c $<
%.o: %.c
	${CC} ${CFLAGS} -c $<

clean:
	rm -rf $(OBJ) *~ || true
	rm *.o || true

realclean: clean
	rm ${EXECS} *.adn *.dat *.png || true

.PHONY: all clean realclean

test: all
	./src/test.sh

archive:
	zip -r TP${TP}_${NOM1}_${NOM2}.zip *

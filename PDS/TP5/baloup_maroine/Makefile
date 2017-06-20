# numéro de TP
TP=5
# nom du coéquipier 1
NOM1=Maroine
# nom du coéquipier 2
NOM2=Baloup




# =========== NE PAS TOUCHER ===========
CC      = gcc
CFLAGS  = -Wall -Werror -ansi -pedantic
CFLAGS += -D_XOPEN_SOURCE=500
CFLAGS += -g
LDFLAGS  = -g
# ======================================



# commande 'make' sans argument
# lister les exécutables à produire
all: multif race exo8

# lister en argument de 'rm' les noms de fichiers binaires exécutables
realclean: clean
	rm multif race exo8 || true

# lister les arguments make correspondant aux exécutables à tester
test: multif race exo8
	./test.sh




# =========== NE PAS TOUCHER ===========

# Compilation séparée
%.o: %.c %.h
	${CC} ${CFLAGS} -c $<

clean:
	rm *.o || true

archive: realclean
	zip -r ../TP${TP}_${NOM1}_${NOM2}.zip *

# Liste des pseudo-cibles utilisés dans ce fichier,
# qui ne sont pas des noms de fichier à produire
.PHONY: all clean realclean archive test

# ======================================




# ----- les exécutables à produire -----
multif: multif.o
	${CC} ${LDFLAGS} -o $@ $^
race: race.o
	${CC} ${LDFLAGS} -o $@ $^
exo8: exo8.o
	${CC} ${LDFLAGS} -o $@ $^

# --------------------------------------

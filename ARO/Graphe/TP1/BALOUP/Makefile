# numéro de TP
TP=1
# nom du coéquipier 1
NOM1=Baloup
# nom du coéquipier 2
NOM2=




# =========== NE PAS TOUCHER ===========
CC      = gcc
CFLAGS  = -Wall -std=c99
CFLAGS += -g
LDFLAGS  = -g
# ======================================



# commande 'make' sans argument
# lister les exécutables à produire
all: graph

# lister en argument de 'rm' les noms de fichiers binaires exécutables
realclean: clean
	rm do || true

# lister les arguments make correspondant aux exécutables à tester
test: do
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
graph: main.o graphe.o display.o
	${CC} ${LDFLAGS} -o $@ $^

# --------------------------------------

# numéro de TP
TP=3
# nom du coéquipier 1
NOM1=Baloup
# nom du coéquipier 2
NOM2=




# =========== NE PAS TOUCHER ===========
CC      = gcc
CFLAGS  = -Wall -Werror -ansi -pedantic
CFLAGS += -D_XOPEN_SOURCE=500
CFLAGS += -g
LDFLAGS  = -g
# ======================================



# commande 'make' sans argument
# lister les exécutables à produire
all: mtail mtail_stupide

# lister en argument de 'rm' les noms de fichiers binaires exécutables
realclean: clean
	rm mtail mtail_stupide || true

# lister les arguments make correspondant aux exécutables à tester
test: mtail mtail_stupide
	./test.sh




# =========== NE PAS TOUCHER ===========

# Compilation séparée
%.o: %.c %.h
	${CC} ${CFLAGS} -c $<

clean:
	rm *.o || true

archive: realclean
	rm -rf ../TP${TP}_${NOM1}_${NOM2}
	mkdir ../TP${TP}_${NOM1}_${NOM2}
	cp -r * ../TP${TP}_${NOM1}_${NOM2}
	cd .. ; zip -r TP${TP}_${NOM1}_${NOM2}.zip TP${TP}_${NOM1}_${NOM2}/*

# Liste des pseudo-cibles utilisés dans ce fichier,
# qui ne sont pas des noms de fichier à produire
.PHONY: all clean realclean archive test

# ======================================




# ----- les exécutables à produire -----
mtail: mtail.o
	${CC} ${LDFLAGS} -o $@ $^

mtail_stupide: mtail_stupide.o
	${CC} ${LDFLAGS} -o $@ $^

# --------------------------------------

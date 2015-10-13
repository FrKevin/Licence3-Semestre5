# numéro de TP
TP=4
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
all: mcat

# lister en argument de 'rm' les noms de fichiers binaires exécutables
realclean: clean
	rm mcat || true

# lister les arguments make correspondant aux exécutables à tester
test: mcat
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
mcat: mcat.o
	${CC} ${LDFLAGS} -o $@ $^

# --------------------------------------

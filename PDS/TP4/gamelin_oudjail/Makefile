###   DATA   ###
TP=4
NOM1=Gamelin
NOM2=Oudjail
### END DATA ###

## Compilateur C et éditeur de liens
CC      = gcc

## Options pour la compilation du C
CFLAGS  = -Wall -Werror -ansi -pedantic
#  Spécifie la version de la norme POSIX à respecter
CFLAGS += -D_XOPEN_SOURCE=500
#  Active les informations de débogage
CFLAGS += -g

## Options de l’édition de liens
LDFLAGS  = -g

#Liste des speudo-cibles utilisés dans ce fichier,
# quit ne sont pas des noms de fichier à produire
.PHONY: all clean realclean archive test

## Première cible
	#  « make » sans argument construit sa première cible
all: mcat

## Make avec argument
mcat: mcat.c
	${CC} ${CFLAGS} mcat.c -o mcat

test:
	./test.sh

clean:
	rm  mcat || true

realclean:
	rm mcat mcat.png || true

show:
	eog mcat.png

## Compilation séparée
#  Le .o doit être recompilé dès que le .c ou le .h (s'il existe) change
%.o: %.c %.h
	${CC} ${CFLAGS} -c $<


## Permet de creer une archive coforme pour le depot PDS
archive: clean
	rm -f mcat
	zip -r TP${TP}_${NOM1}_${NOM2}.zip *

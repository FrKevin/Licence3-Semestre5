###   DATA   ###
TP=5
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
all: multif race exo8

## Make avec argument
multif: multif.c
	${CC} ${CFLAGS} multif.c -o multif

race: race.c
	${CC} ${CFLAGS} race.c -o race

exo8: exo8.c
	${CC} ${CFLAGS} exo8.c -o exo8

test:
	./test.sh

clean:
	rm race multif exo8 || true


## Compilation séparée
#  Le .o doit être recompilé dès que le .c ou le .h (s'il existe) change
%.o: %.c %.h
	${CC} ${CFLAGS} -c $<


## Permet de creer une archive coforme pour le depot PDS
archive: clean
	rm -f multif race exo8
	zip -r TP${TP}_${NOM1}_${NOM2}.zip *

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

## Première cible
	#  « make » sans argument construit sa première cible
all: mcat

## Make avec argument
mcat: mcat.c
	${CC} ${CFLAGS} mcat.c -o mcat

## Compilation séparée
#  Le .o doit être recompilé dès que le .c ou le .h (s'il existe) change
%.o: %.c %.h
	${CC} ${CFLAGS} -c $<

test:
	bash mtailTest.sh

clean:
	rm  mcat || true

## Permet de creer une archive coforme pour le depot PDS
archive: clean
	rm -rf ../TP${TP}_${NOM1}_${NOM2}
	mkdir ../TP${TP}_${NOM1}_${NOM2}
	cp -r * ../TP${TP}_${NOM1}_${NOM2}
	cd .. ; zip -r TP${TP}_${NOM1}_${NOM2}.zip TP${TP}_${NOM1}_${NOM2}/*

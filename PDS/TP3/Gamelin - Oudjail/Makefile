### Modèle pour vos Makefile


TP=3

NOM1=Gamelin

NOM2=Oudjail


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
#  Indiquez en dépendance le ou les binaires à construire
all: mtail mtail_stupide


## Compilation séparée
#  Le .o doit être recompilé dès que le .c ou le .h (s'il existe) change
%.o: %.c %.h
	${CC} ${CFLAGS} -c $<

test:
	bash test.sh

clean:
	rm mtail || true

## Liste des pseudo-cibles
#  Ces cibles ne correspondent pas à des fichiers que l'on veut créer,
#  juste à des séquences que l'on veut pouvoir déclencher
.PHONY: all clean

mtail: mtail.c
	${CC} ${CFLAGS} mtail.c -o mtail

mtail_stupide: mtail_stupide.c
	${CC} ${CFLAGS} mtail_stupide.c -o mtail_stupide

## Permet de creer une archive coforme pour le depot PDS

archive: clean
	rm -rf ../TP${TP}_${NOM1}_${NOM2}
	mkdir ../TP${TP}_${NOM1}_${NOM2}
	cp -r * ../TP${TP}_${NOM1}_${NOM2}
	cd .. ; zip -r TP${TP}_${NOM1}_${NOM2}.zip TP${TP}_${NOM1}_${NOM2}/*

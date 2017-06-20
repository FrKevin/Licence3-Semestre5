## Compilateur C et éditeur de liens
CC      = gcc

## Options pour la compilation du C
CFLAGS  = -Wall -std=c99
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
all: parcoursLargeur

## Make avec argument

parcoursLargeur:
	${CC} ${CFLAGS} parcoursLargeur.c graphe_visu_color.c ../lib/graphe.c -o parcoursLargeur

test:
	./test.sh

clean:
	rm  parcoursLargeur || true


## Compilation séparée
#  Le .o doit être recompilé dès que le .c ou le .h (s'il existe) change
%.o: %.c %.h
	${CC}  -c $<

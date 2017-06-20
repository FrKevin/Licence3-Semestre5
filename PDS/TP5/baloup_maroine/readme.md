TP4 : multif, race et exo8 (processus)
=====


Par Maxime Maroine et Marc Baloup

Licence 3 Informatique, Université Lille 1

2015-2016



Exercice 8
-------

### Question 2

Quand on tue le processus père, les processus fils restent en exécution,
et leur sortie standard est toujours redirigé vers la console dans lequel
on a exécuté le père.

### Question 3

Le processus fils qui a été tué est devenu un zombie, car le processus père
n'a pas encore récupéré la valeur de sortie avec l'appel système wait.
Quand le père exécute la commande wait, il n'y a même pas d'attente
car il y a déjà un processus fils terminé (en zombie) suite à l'appel
système wait, le processus fils terminé n'existe plus.

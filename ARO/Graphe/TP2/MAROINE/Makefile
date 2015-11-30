all: testAnalyseur newTestAnalyseur

testAnalyseur: testAnalyseur.c
	gcc -Wall -g -std=c99 testAnalyseur.c include/graphe.c -o testAnalyseur

newTestAnalyseur: newTestAnalyseur.c include/graphe2visu.c include/parcoursLargeur.c
	gcc -Wall -g -std=c99 newTestAnalyseur.c include/graphe.c include/graphe2visu.c include/parcoursLargeur.c -o newTestAnalyseur

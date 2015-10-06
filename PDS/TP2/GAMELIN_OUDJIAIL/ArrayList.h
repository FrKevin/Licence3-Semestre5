#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#define DEFAULT_SIZE 2


struct ArrayList {
    int capacite;
    int size;
    char **data;
};

typedef struct ArrayList ArrayList;

ArrayList *constructArrayList();
ArrayList *constructArrayListWithCapacite(int capacite);

void destructArrayList(ArrayList *list);

int addElement(ArrayList **list, char *element);
int removeElement(ArrayList *list, int index);
int removeElementWithDecalage(ArrayList *list, int index);

int containsAList(ArrayList *list, char *element);


char *getElement(const ArrayList *list, int index);
char *getElementNS(const ArrayList *list, int index);
int setElement(const ArrayList *list, int index, char *newElement);
int setElementNS(const ArrayList *list, int index, char *newElement);


void printList(const ArrayList *list);


#endif

#include "ArrayList.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



ArrayList *constructArrayList()
{
  ArrayList *construct;

  construct = (ArrayList*)malloc(sizeof(ArrayList));
  construct->capacite = DEFAULT_SIZE;
  construct->size = 0;
  construct->data = (char**)malloc(DEFAULT_SIZE * sizeof(char*));

  return construct;
}

ArrayList *constructArrayListWithCapacite(int capacite)
{
  ArrayList *construct;

  construct = (ArrayList*)malloc(sizeof(ArrayList));
  construct->capacite = capacite;
  construct->size = 0;
  construct->data = (char**)malloc(capacite * sizeof(char*));


  return construct;
}

void destructArrayList(ArrayList* list)
{
  int i;
  for(i=0; i < list->size; ++i) {
    free(list->data[i]);
    list->data[i] = NULL;
  }
  free(list->data);
  list->data = NULL;
  free(list);

}

int addElement(ArrayList **list, char *element)
{
  ArrayList *newList;
  int i;
  if((*list)->size == (*list)->capacite) {
    newList = constructArrayListWithCapacite((*list)->capacite*2);
    for (i = 0; i < (*list)->size; ++i) {

      newList->data[i] = strdup((*list)->data[i]);
    }
    newList->size = (*list)->size;
    destructArrayList(*list);
    *list = newList;
  }
  (*list)->data[(*list)->size++] = strdup(element);
  return 1;
}





int removeElement(ArrayList *list, int index)
{
  if(index < 0 || index >= list->size) {
    return 0;
  }

  free(list->data[index]);
  list->data[index] = NULL;
  return 1;

}

int removeElementWithDecalage(ArrayList *list, int index)
{
  int i;
  if(!removeElement(list, index)) {
    return 0;
  }

  for(i=index; i < list->size -1; ++i) {
    list->data[i] = list->data[i+1];
  }

  list->size--;
  return 1;
}

char* getElement(const ArrayList *list, int index)
{
  if(index < 0 || index >= list->size) {
    return NULL;
  }

  return list->data[index];
}

int containsAList(ArrayList *list, char *element)
{
  int i;
  for(i=0; i < list->size; ++i) {
    if(strcmp(getElement(list,i), element) == 0) {
      return 1;
    }
  }
  return 0;
}


char *getElementNS(const ArrayList *list, int index)
{
  if(index < 0 || index >= list->capacite) {
    return NULL;
  }

  return list->data[index];
}


int setElement(const ArrayList *list, int index, char *newElement)
{
  if(index < 0 || index >= list->size) {
    return 0;
  }

  list->data[index] = newElement;

  return 1;
}

int setElementNS(const ArrayList *list, int index, char *newElement)
{
  if(index < 0 || index >= list->capacite) {
    return 0;
  }

  list->data[index] = newElement;

  return 1;
}


void printList(const ArrayList *list)
{
  int i;
  printf("[ ");
  for(i=0; i < list->size-1; ++i) {
    printf("%s, ", getElement(list, i));
  }
  printf("%s ]\n", getElement(list, list->size-1));
}

void printAllList(const ArrayList *list)
{
  int i;
  printf("[ ");
  for(i=0; i < list->capacite-1; ++i) {
    printf("%s, ", getElement(list, i));
  }
  printf("%s ]\n", getElement(list, list->capacite-1));
}

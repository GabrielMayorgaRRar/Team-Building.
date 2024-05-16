#ifndef ENTITY_H
#define ENTITY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAIN_HEADER_POSITION 0L
#define ENTITY_NAME_LENGTH 50

typedef struct DataEntity {
    long FileDirection;
    char Name[ENTITY_NAME_LENGTH];
} Entity;


void prinAtributteData(FILE *dataDicitonary, long currentHeaderPointer);
void reassignAtributtePointers(FILE *dataDicitonary, long currentHeaderPointer, const char *newEntityName, long newEntityDirection);
long getDataDictionaryHeader(FILE *dataDicitonary);
int appendAtributte(FILE *dataDicitonary, Entity *dataEntity);

#endif
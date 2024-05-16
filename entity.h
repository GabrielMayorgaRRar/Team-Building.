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


int appendEntity(FILE *dataDicitonary, Entity* dataEntity);
long getDataDictionaryHeader(FILE *dataDicitonary);
void reassignEntityPointers(FILE *dataDicitonary, long currentHeaderPointer, const char* newEntityName, long newEntityDirection);
void printEntityData(FILE *dataDicitonary, long currentHeaderPointer);

#endif
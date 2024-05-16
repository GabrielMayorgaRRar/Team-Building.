#include "entity.h"

int appendEntity(FILE *dataDicitonary, Entity* dataEntity) {
    int operationResult = EXIT_SUCCESS;
    long newEntityPosition = 0;
    const long nullPointer = -1L;
    
    fseek(dataDicitonary, MAIN_HEADER_POSITION, SEEK_END);

    newEntityPosition = ftell(dataDicitonary);
    dataEntity->FileDirection = newEntityPosition;

    // Add the entity name
    fwrite(dataEntity->Name, sizeof(char), sizeof(dataEntity->Name), dataDicitonary);
    // Data pointer
    fwrite(&nullPointer, sizeof(long), 1, dataDicitonary);
    // Attributes pointer
    fwrite(&nullPointer, sizeof(long), 1, dataDicitonary);
    // Next entity pointer
    fwrite(&nullPointer, sizeof(long), 1, dataDicitonary);

    printf("New entity \"%s\" added at position %ld\n", dataEntity->Name, dataEntity->FileDirection);

    return operationResult;
}

long getDataDictionaryHeader(FILE *dataDicitonary) {
    long header;

    fseek(dataDicitonary, MAIN_HEADER_POSITION, SEEK_SET);
    fread(&header, sizeof(header), 1, dataDicitonary);

    return header;
}

void reassignEntityPointers(FILE *dataDicitonary, long currentHeaderPointer, const char* newEntityName, long newEntityDirection) {
    long headerValue = -1;
    
    fseek(dataDicitonary, currentHeaderPointer, SEEK_SET);
    fread(&headerValue, sizeof(headerValue), 1, dataDicitonary);

    if(headerValue == -1L) {
        // No more entities to iterate. Set the current pointer to the new entity direction.
        fseek(dataDicitonary, currentHeaderPointer, SEEK_SET);
        fwrite(&newEntityDirection, sizeof(long), 1, dataDicitonary);
    }
    else {
        char currentEntityName[ENTITY_NAME_LENGTH];
        long nextEntityDirection;
        long nextHeaderPointer;

        // Go to the Entity location and read its data.
        fseek(dataDicitonary, headerValue, SEEK_SET);
        // Read the name for the entity at the current position.
        fread(&currentEntityName, sizeof(char), ENTITY_NAME_LENGTH, dataDicitonary); 
        nextHeaderPointer = ftell(dataDicitonary) + (sizeof(long) * 2);
        // Compare the Entity names to determine whether the current entity should be before the new one or not.
        if(strcmp(currentEntityName, newEntityName) < 0) {
            // Current entity is before the new one.
            reassignEntityPointers(dataDicitonary, nextHeaderPointer, newEntityName, newEntityDirection);
        }
        else {
            // Reassign first pointer.
            fseek(dataDicitonary, currentHeaderPointer, SEEK_SET);
            fwrite(&newEntityDirection, sizeof(long), 1, dataDicitonary);
            // Reassign new entity pointer.
            fseek(dataDicitonary, newEntityDirection + ENTITY_NAME_LENGTH + (sizeof(long) * 2), SEEK_SET);
            fwrite(&headerValue, sizeof(long), 1, dataDicitonary);
        }
    } 
}

void printEntityData(FILE *dataDicitonary, long currentHeaderPointer) {
    long headerValue = -1;
    
    fseek(dataDicitonary, currentHeaderPointer, SEEK_SET);
    fread(&headerValue, sizeof(headerValue), 1, dataDicitonary);

    if(headerValue == -1L) {
        return;
    }
    else {
        char currentEntityName[ENTITY_NAME_LENGTH];
        long nextHeaderPointer;

        // Go to the Entity location and read its data.
        fseek(dataDicitonary, headerValue, SEEK_SET);
        // Read the name for the entity at the current position.
        fread(&currentEntityName, sizeof(char), ENTITY_NAME_LENGTH, dataDicitonary); 

        printf("Entity: %s\n", currentEntityName);
        nextHeaderPointer = ftell(dataDicitonary) + (sizeof(long) * 2);
        printEntityData(dataDicitonary, nextHeaderPointer);
    } 
}

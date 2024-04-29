#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#define EXIT_SUCCESS 0

typedef enum DictionaryMenuOption DictionaryMenuOption;

void printMainMenu();
int readUserInput();
void processUserSelection(DictionaryMenuOption userSelection);

#endif
#include "main.h"

typedef enum DictionaryMenuOption
{
    NO_SELECTION,
    NEW_DICTIONARY,
    OPEN_DICTIONARY,
    CLOSE_PROGRAM,
} DictionaryMenuOption;

int main(int argc, char const *argv[])
{
    int currentUserSelection = NO_SELECTION;
    while (currentUserSelection != CLOSE_PROGRAM)
    {
        printMainMenu();
        currentUserSelection = readUserInput();
        processUserSelection(currentUserSelection);
    }
    return EXIT_SUCCESS;
}

void printMainMenu()
{
    printf("----Data Dictionary----\n");
    printf("%d) Create a new dictionary.\n", NEW_DICTIONARY);
    printf("%d) Open an existing dictionary.\n", OPEN_DICTIONARY);
    printf("%d) EXIT.\n", CLOSE_PROGRAM);
}

int readUserInput()
{
    int userSelection;
    printf("Please select an option: ");
    scanf("%d", &userSelection);
    return userSelection;
}

void processUserSelection(DictionaryMenuOption userSelection)
{
    switch (userSelection)
    {
    case NEW_DICTIONARY:
        printf("YAY! Create a new Data Dictionary.\n");
        break;
    case OPEN_DICTIONARY:
        printf("YAY! Open an existing Data Dictionary.\n");
        break;
    case CLOSE_PROGRAM:
        printf("Exiting program.\n");
        break;
    default:
        printf("Invalid option!\n");
        break;
    }
}

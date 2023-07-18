//Program created by: Brendan Lin

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//Error Codes
#define FILE_IO_READING_ERROR 1
#define EXPECTED_NUMBER_OF_ARGUMENTS_ERROR 2

//Constants
#define EXPECTED_NUMBER_OF_ARGUMENTS 2
#define SET_BOOL_VARIABLE false
#define SET_CHARACTER_COUNTER 0
#define SET_LINE_COUNTER 1
#define NEWLINE_CHAR '\n'
#define SET_WORD_TO_FIND_POINTER 0

void readRequestedFileAndFindWord(char *file, char *wordToFind);
void validateNumberOfArguments(int argc);
void printOutput(bool wordFound, int lineCounter, int characterCounter);
bool validateWord(char *wordToFind, char character, FILE *file);
int updateCharacterCounter(char *wordToFind, char character, FILE *file, int characterCounter,
                           int wordToFindPointer);

int main(int argc, char *argv[]) {

    validateNumberOfArguments(argc);
    readRequestedFileAndFindWord(argv[1], argv[2]);

    return 0;
}

void readRequestedFileAndFindWord(char *fileRequest, char *wordToFind) {
    FILE *file;
    bool wordFound = SET_BOOL_VARIABLE;
    int characterCounter = SET_CHARACTER_COUNTER;
    int lineCounter = SET_LINE_COUNTER;
    char character;

    file = fopen(fileRequest, "r");

    if (file == NULL) {
        perror("Could not open file for reading.");
        exit(FILE_IO_READING_ERROR);
    }

    while (wordFound == false && fscanf(file, "%c", &character) != EOF) {

        if (character == NEWLINE_CHAR) {
            lineCounter++;
            characterCounter = SET_CHARACTER_COUNTER;
        }

        if (validateWord(wordToFind, character, file) == true) {
            wordFound = true;
            rewind(file);
            characterCounter = updateCharacterCounter(wordToFind, character, file, characterCounter,
                                                      SET_WORD_TO_FIND_POINTER);
        }
    }

    //Subtract the final word except the first character and add 1 to get the accurate character location
    characterCounter = characterCounter - strlen(wordToFind) + 1;
    printOutput(wordFound, lineCounter, characterCounter);
    fclose(file);
}

void validateNumberOfArguments(int argc) {
    if (argc != EXPECTED_NUMBER_OF_ARGUMENTS + 1) {
        perror("Number of Arguments Passed is invalid");
        exit(EXPECTED_NUMBER_OF_ARGUMENTS_ERROR);
    }
}

bool validateWord(char *wordToFind, char character, FILE *file) {
    if (!*wordToFind) {
        return true;
    }

    if (*wordToFind != character) {
        return false;
    } else {

        fscanf(file, "%c", &character);

        return validateWord(wordToFind + 1, character, file);
    }
}

int updateCharacterCounter(char *wordToFind, char character, FILE *file, int characterCounter,
                           int wordToFindPointer) {
    if (!*wordToFind) {
        return characterCounter;
    }

    fscanf(file, "%c", &character);

    if (character == NEWLINE_CHAR) {
        return updateCharacterCounter(wordToFind - wordToFindPointer, character, file,
                                      SET_CHARACTER_COUNTER, SET_WORD_TO_FIND_POINTER);
    }

    if (*wordToFind != character) {
        return updateCharacterCounter(wordToFind - wordToFindPointer, character, file,
                                      characterCounter + 1, SET_WORD_TO_FIND_POINTER);
    } else {
        return updateCharacterCounter(wordToFind + 1, character, file,
                                      characterCounter + 1, wordToFindPointer + 1);
    }
}

void printOutput(bool wordFound, int lineCounter, int characterCounter) {

    if (wordFound == false) {
        printf("Not Found!");
    } else {
        printf("Line: %d, Character: %d", lineCounter, characterCounter);
    }
}
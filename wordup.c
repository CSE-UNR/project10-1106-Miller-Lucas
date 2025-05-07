// Lucas Miller
// 5/5/2025
// Project 10

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define WORD_LEN 6   
#define MAX_GUESSES 6

void loadWord(char mysteryWord[]);
void getGuess(char guess[]);
bool isValidGuess(char guess[]);
void toLowerCase(char word[]);
void compareWords(char guess[], char mysteryWord[], char result[], char hints[]);
void displayBoard(char guesses[MAX_GUESSES][WORD_LEN], char hints[MAX_GUESSES][WORD_LEN], int guessCount);

int main() {
    char mysteryWord[WORD_LEN];
    loadWord(mysteryWord);

    char guesses[MAX_GUESSES][WORD_LEN];
    char hints[MAX_GUESSES][WORD_LEN];
    int guessCount = 0;
    bool won = false;

    while (guessCount < MAX_GUESSES && !won) {
        char guess[WORD_LEN];
        getGuess(guess);

        while (!isValidGuess(guess)) {
            printf("Invalid guess. Must be 5 alphabetic letters.\n");
            getGuess(guess);
        }

        toLowerCase(guess);
        strcpy(guesses[guessCount], guess);
        compareWords(guess, mysteryWord, guesses[guessCount], hints[guessCount]);

        if (strcmp(guess, mysteryWord) == 0) {
            won = true;
        }

        displayBoard(guesses, hints, guessCount + 1);
        guessCount++;
    }

    if (won) {
        printf("Congratulations! You guessed the word '%s'!\n", mysteryWord);
    } else {
        printf("Game over! The correct word was '%s'.\n", mysteryWord);
    }

    return 0;
}

void loadWord(char mysteryWord[]) {
    FILE *file = fopen("word.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open word.txt\n");
        exit(1);
    }
    fscanf(file, "%5s", mysteryWord);
    fclose(file);
}

void getGuess(char guess[]) {
    printf("Enter your 5-letter guess: ");
    scanf("%5s", guess);
}

bool isValidGuess(char guess[]) {
    if (strlen(guess) != 5) return false;
    for (int i = 0; i < 5; i++) {
        if (!isalpha(guess[i])) return false;
    }
    return true;
}

void toLowerCase(char word[]) {
    for (int i = 0; i < 5; i++) {
        word[i] = tolower(word[i]);
    }
    word[5] = '\0';
}

void compareWords(char guess[], char mysteryWord[], char result[], char hints[]) {
    bool matched[5] = {false};

    for (int i = 0; i < 5; i++) {
        if (guess[i] == mysteryWord[i]) {
            result[i] = toupper(guess[i]);
            matched[i] = true;
        } else {
            result[i] = guess[i];
        }
        hints[i] = ' ';
    }
  
    for (int i = 0; i < 5; i++) {
        if (guess[i] != mysteryWord[i]) {
            for (int j = 0; j < 5; j++) {
                if (!matched[j] && guess[i] == mysteryWord[j]) {
                    hints[i] = '^';
                    matched[j] = true;
                    break;
                }
            }
        }
    }

    result[5] = '\0';
    hints[5] = '\0';
}

void displayBoard(char guesses[MAX_GUESSES][WORD_LEN], char hints[MAX_GUESSES][WORD_LEN], int guessCount) {
    printf("\n--- Your Guesses ---\n");
    for (int i = 0; i < guessCount; i++) {
        printf("%s\n", guesses[i]);
        printf("%s\n", hints[i]);
    }
    printf("--------------------\n\n");
}

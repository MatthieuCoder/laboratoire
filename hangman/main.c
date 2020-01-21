#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int ft_includes(char *str, char c) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == c)
            return (1);
    }
    return (0);
}

unsigned int ft_strlenUnique(char *str) {
    char str1[strlen(str)];
    int count = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (!ft_includes(str1, str[i])) {
            str1[i] = str[i];
            count++;
        }
    }
    return count;
}

char *ft_getRandomWord() {
    char *wordArray[] = {
            "library", "school", "javascript", "paris", "france", "development", "boss", "factory", "memory", "schedule",
            "awesome", "mouse", "keyboard", "battery", "brightness", "game", "music", "player", "single", "house", "hangman"
    };

    srand(time(NULL));
    int random = (int) floor((rand() % (sizeof(wordArray) / sizeof(wordArray[0]))));
    return (wordArray[random]);
}

void ft_showCurrent(char *word, char *letters, int retries) {
    char *currentWord = malloc((strlen(word) * 2) + 1);
    for (int i = 0; i < strlen(word); i++) {
        if (ft_includes(letters, word[i]))
            currentWord[i] = word[i];
        else
            currentWord[i] = '_';
    }
    currentWord[strlen(word)] = '\0';
    printf("--- WELCOME TO THE HANGMAN ---\n\n");
    printf("Word: %s\n", currentWord);
    printf("Retries: %d\n", retries);
    printf("\n\n");
    printf(">>> Press any letter <<<\n\n");
    free(currentWord);
}

int main(int argc, char *argv[]) {
    char answer[1];
    int is_win = 0;
    int retries = 5;

    char *word = ft_getRandomWord();
    char *lettersFound = malloc((strlen(word) * sizeof(char)) + 1);
    for (int i = 0; i < strlen(word); i++)
        lettersFound[i] = '_';
    lettersFound[strlen(word)] = '\0';

    printf("--- WELCOME TO THE HANGMAN ---\n\n");
    printf("Word: %s\n", lettersFound);
    printf("Retries: %d\n", retries);
    printf("\n\n");
    printf(">>> Press any letter <<<\n");

    int i = 0;
    while (retries > 0 && is_win == 0) {
        scanf("%c", &answer[0]);
        fflush(stdin);
        if ((answer[0] >= 'A' && answer[0] <= 'Z' ) || (answer[0] >= 'a' && answer[0] <= 'z' )) {
            if (ft_includes(word, answer[0])) {
                if (!ft_includes(lettersFound, answer[0])) {
                    lettersFound[i] = answer[0];
                    i++;
                }
            } else {
                retries--;
            }
            system("clear");
            ft_showCurrent(word, lettersFound, retries);
            if (i == ft_strlenUnique(word))
                is_win = 1;
        }
    }

    if (is_win == 1)
        printf("You win!\n");
    else
        printf("You lose! The right word was '%s'.\n", word);

    free(lettersFound);
    return 0;
}

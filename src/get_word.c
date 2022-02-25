/*
** EPITECH PROJECT, 2019
** B_PSU_402_LYN_4_1_strace_flavien_allix
** File description:
** Created by flavien,
*/

#include "strace.h"

char *append(char *str, char cara)
{
    size_t size;
    char *backup;

    if (!str)
        str = strdup("");
    size = strlen(str);
    backup = malloc(size + 2);
    strcpy(backup, str);
    backup[size] = cara;
    backup[size + 1] = '\0';
    free(str);
    return backup;
}

char *get_word(char *str, char seperator, int wich_word)
{
    int pos = 1;
    int is_space = 0;
    char *word = NULL;

    for (int x = 0 ; x < strlen(str) ; x++) {
        if (str[x] == seperator)
            if (pos == wich_word)
                return word;
            else {
                is_space = 1;
                continue;
            }
        if (is_space == 1) {
            pos += 1;
            is_space = 0;
        }
        if (pos == wich_word)
            word = append(word, str[x]);
    }
    return word;
}
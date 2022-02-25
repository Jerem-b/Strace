/*
** EPITECH PROJECT, 2020
** B-PSU-402-LYN-4-1-strace-flavien.allix
** File description:
** command_write.c
*/

#include "strace.h"

int command_write(int i, char **av, strace_t *strace)
{
    char *backup;

    if (strace->command) {
        backup = strdup(strace->command);
        free(strace->command);
        strace->command = (char *) malloc(1 + strlen(backup) + strlen(av[i]));
        strcpy(strace->command, backup);
        strcat(strace->command, " ");
        strcat(strace->command, av[i]);
        free(backup);
    } else
        strace->command = strdup(av[i]);
}
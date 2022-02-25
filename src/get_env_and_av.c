/*
** EPITECH PROJECT, 2020
** B-PSU-402-LYN-4-1-strace-flavien.allix
** File description:
** get_env.c
*/

#include "strace.h"

void get_env_and_av(strace_t *strace, char **env, char **av)
{
    int i = 0;
    int k = 0;

    for (; env[i] != NULL; i++);
    strace->env = malloc(sizeof(char *) * (i + 2));
    for (int j = 0; j < i; j++)
        strace->env[j] = strdup(env[j]);
    strace->env[i] = NULL;
    for (int k = 0; av[k] != NULL; k++);
    strace->av = malloc(sizeof(char *) * (k + 2));
    strace->av[0] = strdup(ret_only_cmd(strace->command));
    for (int l = 0; l < k; l++)
        strace->av[l] = strdup(av[l]);
    strace->av[k] = NULL;
}
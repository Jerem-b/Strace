/*
** EPITECH PROJECT, 2019
** B-PSU-402-LYN-4-1-strace-flavien.allix
** File description:
** Created by flavien,
*/

#include "strace.h"
#include "check_args.h"

void command_full_write(char *result, strace_t *strace)
{
    char *check_exist = get_word(strace->command, ' ', 1);
    char *backup = strdup(strace->command);

    if (strcmp(result, check_exist) == 0) {
        free(check_exist);
        free(backup);
        return;
    }
    result[strlen(result) - (strlen(check_exist))] = '\0';
    free(strace->command);
    strace->command = (char *) malloc(4 + strlen(backup) + strlen(result));
    strcpy(strace->command, result);
    strcat(strace->command, backup);
    free(backup);
    free(check_exist);
}

void help(void)
{
    puts("USAGE: ./strace [-s] [-p <pid>|<command>]");
    exit(0);
}

int error_cleaning(strace_t *strace)
{
    free(strace->command);
    free(strace);
    return 84;
}

int main(int ac, char **av, char **env)
{
    strace_t *strace = malloc(sizeof(strace_t));
    strace->command = NULL;
    strace->pid = 0;

    if (ac == 1)
        return error_cleaning(strace);
    if (ac == 2 && !strcmp("-h", av[1]))
        help();
    if (check_args(ac, av, strace) == 84)
        return error_cleaning(strace);
    if (strace->has_s) {
        get_env_and_av(strace, env, av);
        core_s(strace, av);
    }
    else if (strace->pid != 0)
        core_p(strace);
    free(strace->command);
    free(strace);
}
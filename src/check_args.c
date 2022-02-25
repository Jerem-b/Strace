/*
** EPITECH PROJECT, 2019
** B-PSU-402-LYN-4-1-strace-flavien.allix
** File description:
** Created by flavien,
*/

#include "strace.h"

int next_check_args(int i, char **av, strace_t *strace)
{
    int ati;

    if (strace->pid != 0 && i == (strace->pid)) {
        ati = atoi(av[i]);
        if (ati == 0 || kill(ati, 0)) {
            printf("strace: attach: ptrace(PTRACE_SEIZE, %d): No such process"
                "\n", ati);
            return 84;
        }
        strace->pid = ati;
        return 0;
    }
    if (strace->pid != 0 || (av[i][0] == '-' && !strace->command))
        return 84;
    command_write(i, av, strace);
    return 0;
}

char *test_path_command(int i, char *path, strace_t *strace)
{
    char *word = get_word(path, ':', i + 1);
    char *result;
    char *to_cpy = get_word(strace->command, ' ', 1);

    if (i != -1) {
        result = (char *) malloc(1 + strlen(to_cpy) + strlen(word) + 1);
        strcpy(result, word);
        strcat(result, "/");
        strcat(result, to_cpy);
    } else
        result = strdup(to_cpy);
    free(word);
    free(to_cpy);
    return result;
}

int check_command_exists(strace_t *strace)
{
    char *path = getenv("PATH");
    int pos = 0;
    struct stat sb;
    char *result;

    for (int i = 0; path[i] != '\0'; ++i)
        if (path[i] == ':')
            pos++;
    for (int i = -1; i < pos; ++i) {
        result = test_path_command(i, path, strace);
        if (stat(result, &sb) == 0 && sb.st_mode & S_IXUSR) {
            command_full_write(result, strace);
            free(result);
            return 0;
        }
        free(result);
    }
    printf("strace: Can't stat '%s': No such file or directory\n",
        get_word(strace->command, ' ', 1));
    return 84;
}

int last_check(int i, strace_t *strace)
{
    if (i == (strace->pid))
        return 84;
    if (strace->pid != 0)
        return 0;
    if (check_command_exists(strace) == 84)
        return 84;
    return 0;
}

int check_args(int ac, char **av, strace_t *strace)
{
    int i;

    for (i = 1; i < ac; ++i) {
        if (strcmp(av[i], "-s") == 0 && i != (strace->pid)) {
            strace->has_s = true;
            continue;
        }
        if (strcmp(av[i], "-p") == 0) {
            strace->pid = i + 1;
            continue;
        }
        if (next_check_args(i, av, strace) == 84)
            return 84;
    }
    return last_check(i, strace);
}
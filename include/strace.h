/*
** EPITECH PROJECT, 2019
** B_PSU_402_LYN_4_1_strace_flavien_allix
** File description:
** Created by flavien,
*/

#ifndef STRACE_H_
#define STRACE_H_

#include <stdio.h>
#include <sys/stat.h>
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include <sys/types.h>
#include <signal.h>
#include "unistd.h"
#include <sys/syscall.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/user.h>

#include <fcntl.h>
#include <errno.h>

typedef struct strace_s
{
    bool has_s;
    int pid;
    char *command;
    char **av;
    char **env;
    char *sysname_tab;
    struct user_regs_struct regs;
} strace_t;

int command_write(int i, char **av, strace_t *strace);
void command_full_write(char *result, strace_t *strace);
char *get_word(char *str, char seperator, int wich_word);
void get_env_and_av(strace_t *strace, char **env, char **av);
void core_s(strace_t *strace, char *av[]);
char *ret_only_cmd(char *cmd);
char *read_value(pid_t pid, unsigned long addr);
int get_sys_nbargs(long long int sysnb);
char *get_syscall_name(long long int sysnb);
void core_p(strace_t *strace);
void display_end(long long int retval);
void display(strace_t *strace, int nb_args, pid_t pid);
#endif
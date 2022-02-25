/*
** EPITECH PROJECT, 2020
** B-PSU-402-LYN-4-1-strace-flavien.allix
** File description:
** syscalls.c
*/

#include "strace.h"
#include "syscall_name.h"

char *get_syscall_name(long long int sysnb)
{
    return sysname_tab[sysnb];
}

int get_sys_nbargs(long long int sysnb)
{
    return sysargs_tab[sysnb];
}

char *read_value(pid_t pid, unsigned long addr)
{
    char *val;
    unsigned long long allocated = 4096;
    unsigned long long read, tmp;

    if ((val = malloc(allocated)) == NULL)
        return NULL;
    read = 0;
    while (1) {
        if (read + sizeof(tmp) > allocated)
            val = realloc(val, allocated *= 2);
        tmp = ptrace(PTRACE_PEEKDATA, pid, addr + read);
        if (errno != 0) {
            val[read] = 0;
            break;
        }
        memcpy(val + read, &tmp, sizeof(tmp));
        if (memchr(&tmp, 0, sizeof(tmp)) != NULL)
            break;
        read += sizeof(tmp);
    }
    return (val[0] == 0) ? "NULL" : val;
}
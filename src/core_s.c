/*
** EPITECH PROJECT, 2020
** B-PSU-402-LYN-4-1-strace-flavien.allix
** File description:
** core_s.c
*/

#include "strace.h"
#include "syscall_name.h"

char *ret_only_cmd(char *cmd)
{
    int i = 0;
    char *tmp;

    for (; cmd[i] != ' '; i++);
    tmp = malloc(sizeof(char) * (i + 1));
    for (int j = 0; j < i; j++)
        tmp[j] = cmd[j];
    tmp[i] = '\0';
    return tmp;
}

void display(strace_t *strace, int nb_args, pid_t pid)
{
    long long int regs[6] = {strace->regs.rdi, strace->regs.rsi,
        strace->regs.rdx, strace->regs.r10, strace->regs.r8, strace->regs.r9};

    printf("%s(", get_syscall_name(strace->regs.orig_rax));
    for (int i = 0; i < nb_args - 1; i++) {
        if (systype_tab[strace->regs.orig_rax][i] == "INT")
            printf("%lld, ", regs[i]);
        else if (systype_tab[strace->regs.orig_rax][i] == "STR")
            printf("\"%s\", ", read_value(pid, regs[i]));
        else if (systype_tab[strace->regs.orig_rax][i] == "PTR")
            printf("0x%llx, ", regs[i]);
    }
    if (systype_tab[strace->regs.orig_rax][nb_args - 1] == "INT")
        printf("%lld) = ", regs[nb_args - 1]);
    else if (systype_tab[strace->regs.orig_rax][nb_args - 1] == "STR")
        printf("\"%s\") = ", read_value(pid, regs[nb_args - 1]));
    else if (systype_tab[strace->regs.orig_rax][nb_args - 1] == "PTR")
        printf("0x%llx) = ", regs[nb_args - 1]);
    (sysret_tab[strace->regs.orig_rax] == 1) ? printf("?\n") : printf("%lld\n",
        strace->regs.rax);
}

void display_end(long long int retval)
{
    printf("exit_group(%lld) = ?\n", retval);
    printf("+++ exited with %lld +++\n", retval);
}

int exec_child(pid_t pid, char *tmp_cmd, char **av)
{
    int status;

    if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        kill(getpid(), SIGSTOP);
        execvp(tmp_cmd, av + 2);
    }
    waitpid(pid, &status, 0);
    return status;
}

void core_s(strace_t *strace, char **av)
{
    pid_t pid = fork();
    int status;
    char *tmp_cmd = ret_only_cmd(strace->command);
    unsigned short instr;

    status = exec_child(pid, tmp_cmd, av);
    while (status) {
        ptrace(PTRACE_GETREGS, pid, NULL, &strace->regs);
        instr = ptrace(PTRACE_PEEKTEXT, pid, strace->regs.rip, NULL);
        ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
        waitpid(pid, &status, 0);
        if (instr == 1295) {
            ptrace(PTRACE_GETREGS, pid, NULL, &strace->regs);
            if (strace->regs.orig_rax >= 0 && strace->regs.orig_rax <= 352)
                display(strace, get_sys_nbargs(strace->regs.orig_rax), pid);
        }
    }
    display_end(status);
}
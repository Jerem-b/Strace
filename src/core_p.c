/*
** EPITECH PROJECT, 2020
** B-PSU-402-LYN-4-1-strace-flavien.allix
** File description:
** core_p.c
*/

#include "strace.h"
#include "syscall_name.h"

int signal_handler(int status)
{
    return ((WSTOPSIG(status) == SIGTRAP || WSTOPSIG(status) == SIGSTOP) &&
    WIFSTOPPED(status));
}

void display_end_p(pid_t pid)
{
    printf("strace: Process %d detached\n", pid);
    printf("<detached ...>\n\n");
}

void core_p(strace_t *strace)
{
    int status;
    unsigned short instr;

    ptrace(PTRACE_ATTACH, strace->pid, NULL, NULL);
    printf("strace: Process %d attached\n", strace->pid);
    waitpid(strace->pid, &status, 0);
    while(signal_handler(status)) {
        ptrace(PTRACE_GETREGS, strace->pid, NULL, &strace->regs);
        instr = ptrace(PTRACE_PEEKTEXT, strace->pid, strace->regs.rip, NULL);
        ptrace(PTRACE_SINGLESTEP, strace->pid, 0, 0);
        waitpid(strace->pid, &status, 0);
        if (instr == 1295) {
            ptrace(PTRACE_GETREGS, strace->pid, NULL, &strace->regs);
            if (strace->regs.orig_rax >= 0 && strace->regs.orig_rax <= 352)
                display(strace, get_sys_nbargs(strace->regs.orig_rax),
                    strace->pid);
        }
    }
    display_end_p(strace->pid);
    ptrace(PTRACE_DETACH, strace->pid, NULL, NULL);
}
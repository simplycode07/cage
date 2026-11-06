#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../include/container.h"

#ifndef STACK_SIZE
#define STACK_SIZE (1024 * 1024)

#endif

static int child_func(void *arg) {
	printf("child pid: %d\n", getpid());
	Command *cmd = (Command *)arg;

	printf("cmd: %d, %s\n", cmd->argc, cmd->path);

	int status = execvp(cmd->path, cmd->args);
	if (status == -1)
		perror("could not execute command\n");

	return status;
}

int create_container(Command cmd) {
	printf("Container created!!\n");

	char *stack;
	char *stackTop;

	stack = mmap(NULL, STACK_SIZE, PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
	if (stack == MAP_FAILED)
		return -1;

	stackTop = stack + STACK_SIZE;  /* Assume stack grows downward */

	printf("parent pid: %d\n", getpid());
	int pid = clone(child_func, stackTop, CLONE_NEWPID | SIGCHLD, &cmd);

	if (pid == -1){
		printf("pid failed\n");
		munmap(stack, STACK_SIZE);
		return -1;
	}

	int status;

	if (waitpid(pid, &status, 0) == -1) {
		perror("waitpid");
		munmap(stack, STACK_SIZE);
		return -1;
	}

	printf("child terminated\n");

	munmap(stack, STACK_SIZE);

	if (WIFEXITED(status)) {
		int exit_code = WEXITSTATUS(status);
		// printf("child exited with: %d\n", exit_code);
		return exit_code;
	}

	if (WIFSIGNALED(status)){
		int exit_code = 128 + WTERMSIG(status);
		// printf("child terminated with: %d\n", exit_code);
		return exit_code;
	}

	return -1;
}

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define STACK_SIZE (1024 * 1024)

static int child_func(void *arg) {

	printf("child pid: %d\n", getpid());

	sleep(5);

	return 0;
}

int create_container(int args, char *cmd) {
	printf("Container created!!\n");

	char *stack;
	char *stackTop;

	stack = mmap(NULL, STACK_SIZE, PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
	if (stack == MAP_FAILED)
		return -1;

	stackTop = stack + STACK_SIZE;  /* Assume stack grows downward */

	int pid = clone(child_func, stackTop, CLONE_NEWPID | SIGCHLD, cmd);

	if (pid == -1){
		printf("pid failed\n");
		return -1;
	}
	
	sleep(1);

	printf("parent pid: %d\n", getpid());

	if (waitpid(pid, NULL, 0) == -1) {
		printf("exit failure of child process\n");
		return -1;
	}
	printf("child terminated successfully\n");
	

	return 0;
}

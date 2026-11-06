#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/container.h"

int main(int argc, char *argv[]) {
	int res = 0;

	if (argc <= 1) {
		printf("Usage: %s [options] [cmd]\n", argv[0]);
		res = 1;
	}

	else {
		if (!strcmp("run", argv[1])) {
			if (argc < 3) return -1;

			printf("calling func to create container...\n");

			// this copy of command will be passed onto the execv
			// the (argc - 2 + 1), +1 is because the execvp expects NULL terminated argument vector
			char **arg_cpy = malloc(sizeof(char*) * (argc - 1));

			for (int i=0; i < argc - 2; i++) {
				arg_cpy[i] = malloc(sizeof(char) * strlen(argv[i + 2]) + 1);
				strcpy(arg_cpy[i], argv[i+2]);
			}

			arg_cpy[argc - 2] = NULL;

			Command cmd = {
				argc - 2,
				arg_cpy[0],
				arg_cpy,
			};
			res = create_container(cmd);
			if (res == -1) {
				fprintf(stderr, "container runtime failed\n");
				return 1;
			}
		}
		else {
			res = -1;
		}
	}

	return res;

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/container.h"

int main(int argc, char *argv[]) {
	if (argc <= 1) {
		printf("Usage: %s [options] [cmd]\n", argv[0]);
	}

	else {
		if (!strcmp("run", argv[1])) {
			printf("calling func to create container...\n");

			// this copy of command will be passed onto the execv
			// the (argc - 2 + 1), +1 is because the execvp expects NULL terminated argument vector
			char **arg_cpy = malloc(sizeof(char*) * (argc - 1));
			if (argc > 2) {
				for (int i=0; i < argc - 2; i++) {
					arg_cpy[i] = malloc(sizeof(char) * strlen(argv[i + 2]) + 1);
					strcpy(arg_cpy[i], argv[i+2]);
				}

				arg_cpy[argc - 2] = NULL;
			}

			Command cmd = {
				argc - 2,
				arg_cpy[0],
				arg_cpy,
			};
			create_container(argc - 2, cmd);
		}
	}

	return 0;

}

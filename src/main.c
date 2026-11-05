#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/container.h"

int main(int argc, char *argv[]) {
	if (argc <= 1) {
		printf("Usage: %s <child-hostname>\n", argv[0]);
	}

	else {
		if (!strcmp("run", argv[1])) {
			printf("calling func to create container...\n");

			// this copy of command will be passed onto the container to execute ig?
			int length_cmd = 0;
			for (int i=0; i < argc - 2; i++) {
				length_cmd += strlen(argv[i + 2]);
			}
			char *cmd = malloc(length_cmd * sizeof(char) + 1);
			if (argc > 2) {
				int counter = 0;
				for (int i=0; i < argc - 2; i++) {
					int counter_arg = 0;
					while (argv[i + 2][counter_arg] != '\0'){
						cmd[counter] = argv[i+2][counter_arg];
						counter++;
						counter_arg++;
					}
					cmd[counter] = ' ';
					counter++;
				}
				cmd[counter] = '\0';
			}

			// debugging print statements
			// printf("cmd: %s\n", cmd);
			// int i = 0;
			// while (cmd[i] != '\0') {
			// 	printf("%c", cmd[i]);
			// 	i++;
			// }
			
			create_container(argc - 2, cmd);
		}
	}

	return 0;

}

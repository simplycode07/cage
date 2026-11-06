#define STACK_SIZE (1024 * 1024)

typedef struct {
	int argc;
	char *path;
	char **args;
} Command;

typedef struct {
	int box_id;
	char *stackTop;
	char *utsname;

} Box;

int create_container(Command cmd);

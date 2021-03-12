#include <stdio.h>
#include <unistd.h>

void call(char *name) {
	if (fork() == 0) {
		printf("%s Child\n", name);
	}
	else {
		printf("%s Parent\n", name);
	}
}

int main(int argsc, char **argv) {
	call(argv[1]);
	return 0;
}

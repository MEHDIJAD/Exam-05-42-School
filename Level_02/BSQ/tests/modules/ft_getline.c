#include <stdio.h>
#include <stdlib.h>


int main(void) {
	
	char *line = NULL;
	size_t len = 0;
	__ssize_t nread;

	while ((nread = getline(&line, &len, stdin)) != -1) {
		printf("Retrieved line of length %zu:\n", nread);
    	printf("%s", line);
	}
	free(line);
	
	return 0;
}
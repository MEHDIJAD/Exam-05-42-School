#include <stdio.h>


void ft_fscanf(FILE *stream) {
	int nb_rows;
    char empty, obstacle, full;

    int result = fscanf(stream, "%d %c %c %c", &nb_rows, &empty, &obstacle, &full);

    if (result == 4) {
        printf("Lines: %d\n", nb_rows);
        printf("Empty: '%c', Obstacle: '%c', Full: '%c'\n", empty, obstacle, full);
    } else {
        printf("Error: Found only %d items\n", result);
    }
}


int main(void)
{
	ft_fscanf(stdin);
	return 0;
}


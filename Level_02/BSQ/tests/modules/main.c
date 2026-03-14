#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"
#include <stdbool.h>

/*! @brief 
	I- READ: 
		1. The First Line
*/

typedef struct s_config {
	int		lines_count;
	char	empty;
	char	obstacle;
	char	full;
	int	map_width;
} t_config;


bool isprintable(char c) {
	return (c >= 32 && c <= 126);
}
void errorf() {
	fprintf(stderr, "%sERROR FILE%s\n", RED, RESET);
}


bool dupl(char empty, char obstacle, char full) {
	return (empty == obstacle || empty == full || obstacle == full);
}


void printgrid(int **g, int height, int width){
	for ( int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++){
			printf("[%d]", g[i][j]);
		}
		printf("\n");
	}	
}

int min(int a, int b, int c) {
	int m = a;
	if (b < m) m = b;
	if (c < m) m = c;
	return m;
}


void dptable(int **g, t_config cnfg, int max_size, int best_y, int best_x) {
	/*! @brief 
		
	*/

	for (int i = 1; i < cnfg.lines_count; i++) {
		for (int j = 1; j < cnfg.map_width; j++)
		{
			if (g[i][j] == 1) {
				g[i][j] = min(g[i-1][j], g[i][j-1], g[i-1][j-1]) + 1;
				if (g[i][j] > max_size) {
					max_size = g[i][j];
					best_y = i;
					best_x = j;
				}
			}
		}	
	}

	for (int i = 0; i < cnfg.lines_count; i++)
	{
		for (int j = 0; j < cnfg.map_width; j++)
		{
			int cell = g[i][j];
			int c;
			if (i > (best_y - max_size) && i <= best_y && j > (best_x - max_size) && j <= best_x) {
				c = cnfg.full;
			}
			else if (cell == 0){
				c = cnfg.obstacle;
			}
			else 
				c = cnfg.empty;
			fprintf(stdout, "%c", c);
		}
		fprintf(stdout, "\n");
		
	}
}

void process_map(FILE *stream) {
	char *line = NULL;
	int **grid = NULL;
	bool has_error = false;
	int rows_allocated = 0;
	size_t len = 0;
	t_config config = {0,0,0,0,0};
	int max_size = 0;
	int best_x = 0;
	int best_y = 0;


	if(fscanf(stream, "%d %c %c %c", /* ./bsq lines_count empty obstacle full */
		&config.lines_count, &config.empty, &config.obstacle, &config.full) != 4) {
		has_error = true; goto cleanup;
	}

	if (config.lines_count < 1) { // Rule: There's at least one line of at least one box.
		has_error = true; goto cleanup;
	}
	
	if (dupl(config.empty, config.obstacle, config.full)){ // Rule: map is invalid if two characters (of empty, full and obstacle) are identical.
		has_error = true; goto cleanup;
	}

	if (!isprintable(config.empty) || !isprintable(config.obstacle) || !isprintable(config.full)){ // Rule: characters can be any printable character.
		has_error = true; goto cleanup;
	}
	if (getline(&line, &len, stream) == -1) { // Purpose: swallow the '\n' left from fscanf to start reading map lines correctly.
		has_error = true; goto cleanup;
	}


	int current_line_count = 0;

	// Grid Allocation
	grid = malloc(sizeof(int *) * config.lines_count);
	if (!grid) {has_error = true; goto cleanup;}

	while (getline(&line, &len, stream) != -1) 
	{
		int current_len = 0;
		while (line[current_len] && line[current_len] != '\n') 
		{
			if (line[current_len] != config.empty && line[current_len] != config.obstacle) { // Rule: characters on the map can only be those introduced in the first line.
				has_error = true; goto cleanup;				
			}
			current_len++;
		}

		if (line[current_len] != '\n') { // Rule: at each end of line, there's a line break.
			has_error = true; goto cleanup;			
		}

		if(config.map_width == 0) { // Purpose: set reference width using the first line.
			config.map_width = current_len;
		}
		
		else if (current_len != config.map_width) { // Rule: all lines must have the same length.
			has_error = true; goto cleanup;			
		}

		grid[rows_allocated] = malloc(sizeof(int) * config.map_width);        
		if (!grid[rows_allocated]) {
			has_error = true; goto cleanup; 
		}
		for (int i = 0; i < current_len; i++){
			if (line[i] == config.empty) {
				grid[rows_allocated][i] = 1;
				if (max_size == 0) {
					max_size = 1;
					best_y = rows_allocated;
					best_x = i;
				}
			}
			else {
				grid[rows_allocated][i] = 0;
			}
		}		
		rows_allocated++;

		current_line_count++;	
		if (current_line_count > config.lines_count) { // Purpose: stop immediately if map exceeds the header's line count.
			has_error = true; goto cleanup;			
		}
	}

	if (current_line_count != config.lines_count) { // Rule: ensure total lines match the header's expected count.
		has_error = true; goto cleanup;		
	}
	printf("%sVALID MAP!%s\n", GREEN, RESET);
	dptable(grid, config, max_size, best_y, best_x);
	// printgrid(grid, rows_allocated, config.map_width);
	cleanup:
		if (has_error) {
		fprintf(stderr, "%sERROR MAP%s\n", RED, RESET);
		}
		if (line){free(line);}
		for (int i = 0; i < rows_allocated; i++){
			free(grid[i]);
			grid[i] = NULL;
		}
		free (grid);
}

int main(int ac, char *av[]) {
	
	if (ac == 1) {
		printf("%sstdin MODE%s\n", BLUE, RESET);
		process_map(stdin);
	}
	else if (ac > 1) {
		printf("%sFILES MODE%s\n", YELLOW, RESET);
		for (int i = 1; i < ac; i++)
		{
			FILE *file_pointer = fopen(av[i], "r");
			if (!file_pointer) {
				errorf();
				continue;
			}
			process_map(file_pointer);
			fclose(file_pointer);
			printf("\n");
		}
	}
	return EXIT_SUCCESS;
}

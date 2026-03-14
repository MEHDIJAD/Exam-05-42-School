#include <stdlib.h> // for malloc
#include <stdio.h> // for fprint, fputc, fputs

/*! @brief Structure to store map configuration (header data). */
typedef struct s_data {
	int line_count;  /*!< Number of lines in the map. */
	char empty;      /*!< Character representing an empty space. */
	char abstacle;   /*!< Character representing an obstacle. */
	char full;       /*!< Character representing the filled square. */
	int map_width;   /*!< Calculated width of the map. */
} t_d;

/*! @brief Structure to store the map grid and tracking data for the biggest square. */
typedef struct s_map {
	int **grid;          /*!< 2D array for the DP table. */
	int rows_allocated;  /*!< Count of successfully allocated rows. */
	int max_size;        /*!< Size of the largest square found. */
	int best_y;          /*!< Y-coordinate of the bottom-right corner of the best square. */
	int best_x;          /*!< X-coordinate of the bottom-right corner of the best square. */
} t_m;

/*! @brief Prints a standard map error message to stderr. */
void errorm() {
	fputs("map error\n", stderr);
}

/*! @brief Checks for duplicate characters in the map configuration. */
int dupl(char e, char ob, char f) {
	return (e == ob || e == f || ob == f);
}

/*! @brief Validates if a character is printable. */
int ft_isprint(char c) {
	return (c >= 32 && c <= 126);
}

/*! @brief Returns the minimum of three integers. */
int min(int a, int b, int c) {
	int m = a;
	if (b < m) m = b;
	if (c < m) m = c;
	return m;
}


#include "color.h"

/*! @brief Implements Dynamic Programming to find and print the biggest square.
    @param map The map structure containing the grid.
    @param data The configuration data. */
void dptable(t_m map , t_d data) {
	// Update the grid using the min logic
	for (int i = 1; i < data.line_count; i++) 
	{
		for(int j = 1; j < data.map_width; j++) 
		{
			if (map.grid[i][j] == 1) {
				map.grid[i][j] = min(map.grid[i-1][j], map.grid[i][j-1], map.grid[i-1][j-1]) + 1;
				if (map.grid[i][j] > map.max_size) {
					map.max_size = map.grid[i][j];
					map.best_y = i;
					map.best_x = j;
				}
			}
		}
	}
	// print the final map
	printf("\n%s=== BSQ Result ===%s\n", BLUE, RESET);
	for (int i = 0; i < data.line_count; i++)
	{
		for (int j = 0; j < data.map_width; j++)
		{
			if (i > map.best_y - map.max_size && i <= map.best_y
				&& j > map.best_x - map.max_size && j <= map.best_x){
					printf("%s%c%s", GREEN, data.full, RESET);
				}
				else if (map.grid[i][j] == 0) {
					printf("%s%c%s", RED, data.abstacle, RESET);
				}
				else {
					putchar(data.empty);
				}
		}
		putchar('\n');	
	}
}

/*! @brief Parses and processes a single map from a file stream.
    @param stream The input stream (file or stdin). */
void process_map(FILE *stream) {
	char *line = NULL;
	size_t len = 0;
	int has_error = 0;
	t_d data = {0,0,0,0,0};
	t_m map = {NULL,0,0,0,0};

	// 1. Read Input ./bsq empty abtacle full
	if (fscanf(stream, "%d %c %c %c", 
		&data.line_count, &data.empty, &data.abstacle, &data.full) != 4){
		has_error = 1; goto cleanup;
	}

	// 2. Rull: There's at least one line of at least one box.
	if (data.line_count < 1) {has_error = 1; goto cleanup;}

	// 3. Rull:  map is invalid if two characters (of empty, full and obstacle) are identical.
	if (dupl(data.empty, data.abstacle, data.full)){has_error = 1; goto cleanup;}

	// 4. is all chars are printable ?
	if (!ft_isprint(data.empty) || !ft_isprint(data.abstacle) || !ft_isprint(data.full)) {has_error = 1; goto cleanup;}

	// 5. swallow the '\n' left from fscanf
	if (getline(&line, &len, stream) == -1) {has_error = 1; goto cleanup;}

	// 6. allocate for grid height
	map.grid = malloc(sizeof(int *) * data.line_count);
	if (!map.grid) {has_error = 1; goto cleanup;}
	
	// 7. while we have lines
	int current_line_count = 0;
	while (getline(&line, &len, stream) != -1)
	{
		// Process line
		int current_len = 0;
		while (line[current_len] && line[current_len] != '\n')
		{
			if (line[current_len] != data.empty && line[current_len] != data.abstacle) {has_error = 1; goto cleanup;}
			current_len++;
		}
		if (line[current_len] != '\n'){has_error = 1; goto cleanup;}

		if (data.map_width == 0) {
			data.map_width = current_len;
			// if we have empty new line
			if (data.map_width == 0) { has_error = 1; goto cleanup;}
		}
		else if (current_len != data.map_width) {
			has_error = 1; goto cleanup;
		}

		// allocate for grid(width)
		map.grid[map.rows_allocated] = malloc(sizeof(int) * data.map_width);
		if (!map.grid[map.rows_allocated]){has_error = 1; goto cleanup;}

		// 8. fill grid
		for (int i = 0; i < data.map_width; i++){
			if (line[i] == data.empty) {
				map.grid[map.rows_allocated][i] = 1;
				if (map.max_size == 0) { // to not miss 1x1 square
					map.max_size = 1;
					map.best_y = map.rows_allocated;
					map.best_x = i;
				}
			}
			else {
				map.grid[map.rows_allocated][i] = 0;
			}
		}
		map.rows_allocated++;

		current_line_count++;
		// if we pass the line count in the data we stop immediately
		if (current_line_count > data.line_count) {has_error = 1; goto cleanup;}
	}
	// after we finish loop if we find line count != line count in data => error map
	if (current_line_count != data.line_count){has_error = 1; goto cleanup;}
	dptable(map, data); // DP table logic
	cleanup:
		if (has_error) {
			errorm();
		}
		if (line) {free(line);} // free line from getline 
		for (int i = 0; i < map.rows_allocated; i++){ // free frid intel number of rows allocated
			free(map.grid[i]);
			map.grid[i] = NULL;
		}
		free(map.grid);
}

/*! @brief Main entry point. Handles arguments and selects map source. */
int main(int ac, char *av[]) {
	if (ac == 1) {
		process_map(stdin);
	}
	else if (ac > 1) {
		for (int i = 1; i < ac; i++)
		{
			FILE *file_pointer = fopen(av[i], "r");
			if (!file_pointer){
				errorm();
				continue;
			}
			process_map(file_pointer);
			fclose(file_pointer); // close each file after finish
		}
	}
}

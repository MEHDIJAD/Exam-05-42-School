#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*! @brief 
	I- SETUP:
		./life width height iterations
		1. Store variables
		2. Creat grid
	II- INPUT:
		Read and store
	III- RULESOFLIFE:
*/

/*! @brief Structure to store simulation data and pen state. */
typedef struct s_data
{
	int x;              /*!< Width of the grid. */
	int y;              /*!< Height of the grid. */
	int iterations;     /*!< Number of generation cycles. */

	int pen_x;          /*!< Current X position of the drawing pen. */
	int pen_y;          /*!< Current Y position of the drawing pen. */
	int isup;           /*!< Pen state: 1 (up/not drawing), 0 (down/drawing). */
}	t_d;

/*! @brief Checks if a cell character represents an alive state ('0'). */
int isAlive(char cell) {
	return (cell == '0');
}

/*! @brief Checks if a cell character represents a dead state (' '). */
int isDead(char cell) {
	return (cell == ' ');
}

/*! @brief Prints the simulation grid to the standard output.
    @param g The 2D grid of characters.
    @param data The simulation configuration. */
void printgrid(char **g, t_d data) {
	for (int i = 0; i < data.y; i++) {
		for (int j = 0; j < data.x; j++) {
			putchar(g[i][j]);
		}
		putchar('\n');
	}
}

/*! @brief Dynamically allocates and initializes a 2D grid.
    @param data Configuration containing dimensions.
    @return Pointer to the allocated 2D grid. */
char  **creatgrid(t_d data) {
	char **g;
	int i, j;

	g = calloc(sizeof(char *), (data.y + 1));
	if (!g){return NULL;}
	for (int i = 0; i < data.y; i++) {
		g[i] = calloc(sizeof(char), (data.x + 1));
		if(!g[i]) {
			while (--i >= 0){free(g[i]);}
			free (g);
			return NULL;
		}
	}
	
	for (i = 0; i < data.y; i++) {
		for (j = 0; j < data.x; j++) {
			g[i][j] = ' ';
		}	
		g[i][j] = '\0';
	}
	g[i] = NULL;
	return g;
}

/*! @brief Applies the pen action to a specific cell if the pen is down. */
void pen(char *cell, t_d dt) {
	if (dt.isup == 0) {
		*cell = '0';
	}
}

/*! @brief Counts alive neighbors for a specific cell coordinate. */
int neighbers(char **g, int y, int x, t_d dt) {
	int count = 0;

	for (int i = -1; i <= 1; i++) { 
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) // skip the cell(x,y)
				continue;

			int ny = y + i;
			int nx = x + j;

			if (ny >= 0 && ny < dt.y && nx >= 0 && nx < dt.x) { // if in bound && alive = count++
				if (isAlive(g[ny][nx]))
					count++;
			}
		}
	}
	return count;
}

/*! @brief Frees all memory allocated for the 2D grid. */
void free_grid(char **g, t_d dt) {
    for (int i = 0; i < dt.y; i++) {
        free(g[i]);
    }
    free(g);
}

/*! @brief Main entry point. Initializes simulation and processes input commands. */
int main(int ac, char *av[])
{
	t_d data;
	char c;

	if (ac != 4) {
		fprintf(stderr, "Usage: %s width height iterations\n", av[0]);
		return (1);
	}
	
	// 1. get data from command line
	data.x = atoi(av[1]);
	data.y = atoi(av[2]);
	data.iterations = atoi(av[3]);
	data.pen_x = 0;
	data.pen_y = 0;
	data.isup = 1;
	
	// 2. creat grid
	char **g = creatgrid(data);
	if (!g)
		return (1);

	// 3. process moves
	while ((read(0, &c, 1) > 0)) {
		switch (c)
		{
		case 'w':
			if (data.pen_y > 0) {
				data.pen_y--;
				pen(&g[data.pen_y][data.pen_x], data);
			}
			break;
		case 'a':
			if (data.pen_x > 0) {
				data.pen_x--;
				pen(&g[data.pen_y][data.pen_x], data);	
			}
			break;
		case 's':
			if (data.pen_y < data.y - 1) {
				data.pen_y++;
				pen(&g[data.pen_y][data.pen_x], data);	
			}
			break;
		case 'd':
			if (data.pen_x < data.x - 1) {
				data.pen_x++;
				pen(&g[data.pen_y][data.pen_x], data);	
			}
			break;
		case 'x':
			data.isup = !data.isup;
			pen(&g[data.pen_y][data.pen_x], data);
			break;
		default:
			break;
		}
	}

	// 4. iteration + game of life
	char **newg = creatgrid(data);
	if (!newg){
		free_grid(g, data);
		return (1);
	}

	for (int k = 0; k < data.iterations; k++)
	{
		for (int i = 0; i < data.y; i++)
		{
			for (int j = 0; j < data.x; j++)
			{
				int neighbercnt = neighbers(g, i, j, data); 
				char cell = g[i][j];
				if (isAlive(cell) && neighbercnt < 2) {
					newg[i][j] = ' ';
				}
				else if (isAlive(cell) && (neighbercnt == 2 || neighbercnt == 3)){
					newg[i][j] = '0';
				}
				else if (isAlive(cell) && neighbercnt > 3){
					newg[i][j] = ' ';
				}
				else if (isDead(cell) && neighbercnt == 3) {
					newg[i][j] = '0';
				}
				else {
					newg[i][j] = g[i][j];
				}
			}
		}
		char **tmp = g;
		g = newg;
		newg = tmp;
	}
	
	// Final Output
	printf("\n=== Simulation Result (%d iterations) ===\n", data.iterations);
	printgrid(g, data);

	free_grid(newg, data);
	free_grid(g, data);
	
	return (0);
}

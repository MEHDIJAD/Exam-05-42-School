# BSQ - Biggest Square

| Name | Description | Include | Prototype |
| :--- | :--- | :--- | :--- |
| **malloc** | Allocates dynamic memory | `<stdlib.h>` | `void *malloc(size_t size);` |
| **calloc** | Allocates and zeros dynamic memory | `<stdlib.h>` | `void *calloc(size_t nmemb, size_t size);` |
| **realloc** | Resizes dynamic memory allocation | `<stdlib.h>` | `void *realloc(void *ptr, size_t size);` |
| **free** | Deallocates dynamic memory | `<stdlib.h>` | `void free(void *ptr);` |
| **fopen** | Opens a file stream | `<stdio.h>` | `FILE *fopen(const char *pathname, const char *mode);` |
| **fclose** | Closes a file stream | `<stdio.h>` | `int fclose(FILE *stream);` |
| **getline** | Reads an entire line from a stream | `<stdio.h>` | `ssize_t getline(char **lineptr, size_t *n, FILE *stream);` |
| **fscanf** | Reads formatted input from a stream | `<stdio.h>` | `int fscanf(FILE *stream, const char *format, ...);` |
| **fputs** | Writes a string to a stream | `<stdio.h>` | `int fputs(const char *s, FILE *stream);` |
| **fprintf** | Writes formatted output to a stream | `<stdio.h>` | `int fprintf(FILE *stream, const char *format, ...);` |
| **stderr** | Standard error output stream | `<stdio.h>` | `extern FILE *stderr;` |
| **stdout** | Standard output stream | `<stdio.h>` | `extern FILE *stdout;` |
| **stdin** | Standard input stream | `<stdio.h>` | `extern FILE *stdin;` |
| **errno** | Last error number | `<errno.h>` | `extern int errno;` |

---

### Description

The aim of this program is to find the biggest square on a map, avoiding obstacles.
A file containing the map will be provided. It'll have to be passed as an argument for your program.
The first line of the map contains information on how to read the map (space separated) :
 - The number of lines on the map;
 - The "empty" character;
 - The "obstacle" character;
 - The "full" character.

The map is made up of '"empty" characters', lines and '"obstacle" characters'.
The aim of the program is to replace '"empty" characters' by '"full" characters' in order to represent the biggest square possible.
In the case that more than one solution exists, we'll choose to represent the square that's closest to the top of the map, then the one that's most to the left.
When your program receives more than one map in argument, each solution or "map error" must be followed by a line break.
Should there be no passed arguments, your program must be able to read on the standard input.

### Definition of a valid map

 - **All lines must have the same length**: The map is a rectangle. Once you determine the width of the first line, every following line must match that exact count.
 - **There's at least one line of at least one box**: The map cannot be empty. It requires a minimum dimension of 1x1.
 - **At each end of line, there's a line break**: Every line, including the last one, must terminate with a `\n`.
 - **The characters on the map can only be those introduced in the first line**: The grid must strictly use the "empty" and "obstacle" characters defined in your header. Any other character (except the newline) makes the map invalid.
 - **The map is invalid if a character is missing from the first line, or if two characters (of empty, full and obstacle) are identical**: The header must provide all three symbols (empty, obstacle, full). If any two of these are the same (e.g., empty and obstacle are both `.`), it is a "map error".
 - **The characters can be any printable character, even numbers**: Do not assume the symbols will always be `.`, `o`, and `x`. They could be numbers, letters, or symbols.
 - **In case of an invalid map, your program should display "map error" on the error output followed by a line break**: Use `stderr` for the error message. After printing "map error" and a newline, your program must continue to the next map if multiple arguments were provided.

---

### Example

```bash
%>cat example_file
9 . o x
...........................
....o......................
............o..............
...........................
....o......................
...............o...........
...........................
......o..............o.....
..o.......o................
%>./bsq example_file
.....xxxxxxx...............
....oxxxxxxx...............
.....xxxxxxxo..............
.....xxxxxxx...............
....oxxxxxxx...............
.....xxxxxxx...o...........
.....xxxxxxx...............
......o..............o.....
..o.......o................
%>
```

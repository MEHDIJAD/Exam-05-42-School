<br>

<div align="center">

# 🟦 BSQ — Biggest Square

**Largest Square Finder via Dynamic Programming — 42 Exam Rank 05**

![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square)
![School](https://img.shields.io/badge/School-42%20%7C%201337-000000?style=flat-square)
![Level](https://img.shields.io/badge/Level-02-orange?style=flat-square)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen?style=flat-square)

</div>

---

## 📋 Subject

> Find the biggest square of empty cells in a 2D map, avoiding obstacles.  
> Input via file argument(s) or stdin if no arguments given.

**Map format:**
```
9 . o x          ← header: line_count  empty  obstacle  full
...........
....o......      ← map body (empty = '.', obstacle = 'o')
...........
```

**Output:** replace the empty cells of the biggest square with the `full` character (`x`).

---

## 🔄 Program Flow

```
main()
 ├── no args  →  process_map(stdin)
 └── args     →  for each file: fopen → process_map → fclose
                      │
                 process_map()
                  ├── 1. Parse header with fscanf
                  ├── 2. Validate (count, duplicates, printable)
                  ├── 3. Consume trailing \n (getline)
                  ├── 4. Allocate grid rows
                  ├── 5. Read + validate each line (getline)
                  ├── 6. Fill DP grid (1=empty, 0=obstacle)
                  ├── 7. dptable() → find best square
                  └── cleanup: (goto) free all memory, print error if needed
```

---

## 💡 Algorithm — Dynamic Programming

The DP table transforms the grid so that each cell stores **the size of the largest square whose bottom-right corner is at that cell**.

**Recurrence:**
```
if cell is empty:
    grid[i][j] = min(grid[i-1][j], grid[i][j-1], grid[i-1][j-1]) + 1
if cell is obstacle:
    grid[i][j] = 0
```

**Visual example:**
```
Input:          DP table:       Best square (size 3, corner at [3][4]):
. . . . .       1 1 1 1 1
. . o . .       1 1 0 1 1
. . . . .       1 1 1 1 2
. . . . .       1 1 1 2 3  ←  bottom-right corner
```

**Printing the square:** a cell `(i, j)` is inside the best square if:
```
i > best_y - max_size  AND  i <= best_y
j > best_x - max_size  AND  j <= best_x
```

---

## ⚙️ Function Breakdown

### `process_map(FILE *stream)`
Parses and processes one complete map.

> ⚠️ **Tricky — `fscanf` + `getline`:** After `fscanf` reads the header values, it leaves the `\n` in the stream. A throwaway `getline` call is needed to consume it before reading map lines.

> ⚠️ **Tricky — `goto cleanup`:** Every error path sets `has_error = 1` and jumps to the same `cleanup` label. This avoids copy-pasting `free()` calls at every exit point. Memory is freed proportionally using `rows_allocated`.

> ⚠️ **Tricky — `\n` at end of line:** `getline` includes `\n` in the returned string. The subject requires every line to end with `\n`. Check `line[current_len] != '\n'` — if true, the file is truncated → map error.

> ⚠️ **Tricky — line count validation:** Bail immediately when `current_line_count > line_count` (too many lines). After the loop, check `current_line_count != line_count` to catch too few lines.

---

### `dptable(t_m map, t_d data)`
Applies the DP recurrence and tracks `max_size`, `best_y`, `best_x`. Then prints the map, replacing cells inside the best square with the `full` character.

> ⚠️ **Tricky — 1×1 square:** During grid filling, if `max_size == 0` and an empty cell is found, set `max_size = 1` immediately — otherwise a map with no 2×2 opportunity would print no square at all.

---

## 🗺️ Map Validation Rules

| Rule | Error condition |
|---|---|
| Line count | Header says N lines but file has more or fewer |
| All same width | Any line shorter or longer than the first |
| `\n` at end of every line | Last char of each line read by `getline` must be `\n` |
| Valid characters only | Any char not equal to `empty` or `obstacle` |
| Distinct header chars | `empty == obstacle`, `empty == full`, or `obstacle == full` |
| At least 1 line, 1 column | `line_count < 1` or `map_width == 0` |

On error: print `"map error\n"` to `stderr`, continue to next map.

---

## 🧰 New Functions Reference

| Function | Signature | Description |
|---|---|---|
| `fscanf` | `fscanf(stream, fmt, &vars...)` | Read formatted input from a file stream |
| `getline` | `ssize_t getline(char **buf, size_t *n, FILE *s)` | Read a full line; allocates/resizes buffer; caller must `free(buf)` |
| `fputs` | `int fputs(const char *s, FILE *stream)` | Write a string to a stream (no formatting) |
| `fopen` | `FILE *fopen(const char *path, const char *mode)` | Open a file, returns `NULL` on failure |
| `fclose` | `int fclose(FILE *stream)` | Close a file stream |
| `malloc` | `void *malloc(size_t size)` | Allocate `size` bytes (uninitialized) |
| `free` | `void free(void *ptr)` | Deallocate heap memory |

---

## 🚀 Usage

```bash
cd Level_02/BSQ
make
./bsq map_file          # from file
./bsq map1 map2 map3    # multiple files
./bsq < map_file        # from stdin
```

---

> ⚠️ **Note:** Compiled with `gcc -Wall -Wextra -Werror`. No C++ — pure C only.

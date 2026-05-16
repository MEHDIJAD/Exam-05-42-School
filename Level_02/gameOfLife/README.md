<br>

<div align="center">

# 🧬 Game of Life

**Conway's Game of Life Simulation — 42 Exam Rank 05**

![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square)
![School](https://img.shields.io/badge/School-42%20%7C%201337-000000?style=flat-square)
![Level](https://img.shields.io/badge/Level-02-orange?style=flat-square)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen?style=flat-square)

</div>

---

## 📋 Subject

> Simulate Conway's Game of Life on a grid drawn interactively via stdin commands.

**Usage:**
```bash
./life width height iterations
```

**Input:** a stream of pen commands from stdin  
**Output:** the grid state after `iterations` generations

---

## 🔄 Program Flow

```
main()
 ├── 1. Parse args  (width, height, iterations)
 ├── 2. creatgrid() → allocate width × height char grid, fill with ' ' (dead)
 ├── 3. Read pen commands from stdin (read 1 byte at a time)
 │       w/a/s/d → move pen   |   x → toggle pen up/down
 ├── 4. Run N generation loops
 │       neighbers() → count alive neighbors for each cell
 │       apply Game of Life rules → write to newgrid
 │       swap grid pointers
 └── 5. printgrid() → output final state
```

---

## 💡 Algorithm — Conway's Rules

Applied to every cell each generation:

| Cell state | Alive neighbors | Next state |
|---|---|---|
| Alive | < 2 | Dies (underpopulation) |
| Alive | 2 or 3 | Survives |
| Alive | > 3 | Dies (overpopulation) |
| Dead | exactly 3 | Born |
| Dead | anything else | Stays dead |

**Cell encoding:** `'0'` = alive · `' '` (space) = dead

---

## ⚙️ Function Breakdown

### `creatgrid(t_d data)` — Grid Allocation
Allocates a `char**` grid using `calloc`, initializes every cell to `' '`, sets each row's last byte to `'\0'`, and sets the final row pointer to `NULL` (sentinel).

> ⚠️ **Tricky — cleanup on partial failure:** If any `calloc` fails mid-loop, the function frees all previously allocated rows before returning `NULL`. Without this, a failed allocation leaks every row created before it.

---

### Pen system (inside `main`)
Commands are read **one byte at a time** with `read(0, &c, 1)`.

| Key | Action |
|---|---|
| `w` | Move pen up |
| `s` | Move pen down |
| `a` | Move pen left |
| `d` | Move pen right |
| `x` | Toggle pen up / down |

> ⚠️ **Tricky — pen state:** Movement does **not** mark cells by itself. After every move, `pen(&cell, data)` is called — but it only writes `'0'` when `isup == 0` (pen is down). Toggling `x` uses `isup = !isup`.

---

### `neighbers(char **g, int y, int x, t_d dt)` — Count Live Neighbors
Loops the 3×3 neighborhood using offsets `i, j ∈ {-1, 0, 1}`, skips `(0,0)` (the cell itself), and **bounds-checks** each neighbor before reading.

```
for i in {-1, 0, 1}:
  for j in {-1, 0, 1}:
    if i==0 and j==0: skip
    ny = y + i,  nx = x + j
    if in bounds and g[ny][nx] == '0': count++
return count
```

---

### Generation Loop — Double Buffer
Two grids (`g` and `newg`) are used to avoid reading cells that were already updated in the current generation.

```
for each generation k:
    compute newg from g using Game of Life rules
    swap(g, newg)   ← pointer swap, no data copy
```

**Pointer swap:**
```c
char **tmp = g;
g = newg;
newg = tmp;
```

> ⚠️ **Tricky:** After the loop, `g` holds the **final state** and `newg` holds the stale previous state. Both must be freed. Freeing `newg` first (the stale one) then `g` is the safe order.

---

## 🧰 New Functions Reference

| Function | Signature | Description |
|---|---|---|
| `read` | `ssize_t read(int fd, void *buf, size_t n)` | Read `n` bytes from file descriptor (0 = stdin); no buffering |
| `calloc` | `void *calloc(size_t nmemb, size_t size)` | Allocate and **zero-initialize** `nmemb × size` bytes |
| `atoi` | `int atoi(const char *str)` | Convert a string argument to `int` |
| `putchar` | `int putchar(int c)` | Write a single character to stdout |

---

## 🚀 Usage

```bash
cd Level_02/gameOfLife
make

# Draw a pattern via stdin, then run 5 generations on a 10x10 grid:
printf "ssdddxssddwwx" | ./life 10 10 5
```

---

> ⚠️ **Note:** Compiled with `gcc -Wall -Wextra -Werror`. No C++ — pure C only.

<br>

<div align="center">

# 🧩 polyset

**Polymorphic Collection via Multiple Inheritance — 42 Exam Rank 05**

![Language](https://img.shields.io/badge/Language-C%2B%2B98-blue?style=flat-square)
![School](https://img.shields.io/badge/School-42%20%7C%201337-000000?style=flat-square)
![Level](https://img.shields.io/badge/Level-01-orange?style=flat-square)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen?style=flat-square)

</div>

---

## 📋 Subject

> Extend a provided class hierarchy to add searchable bags and a set wrapper.  
> Files to implement: `searchable_array_bag.{hpp,cpp}` · `searchable_tree_bag.{hpp,cpp}` · `set.{hpp,cpp}`

---

## 🏗️ Class Hierarchy

```
                    ┌─────────────┐
                    │     bag     │  (abstract)
                    │  insert()   │  insert(int)
                    │  print()    │  insert(int*, int)
                    │  clear()    │  print()
                    └──────┬──────┘  clear()
                           │
              ┌────────────┴────────────┐
              │                         │
     ┌────────┴────────┐     ┌──────────┴──────────┐
     │   array_bag     │     │   searchable_bag     │  (abstract)
     │ (array storage) │     │  + has(int) = 0      │
     └────────┬────────┘     └──────────┬───────────┘
              │    (diamond)            │
              └───────────┬────────────┘
                          │
             ┌────────────┴────────────┐
             │  searchable_array_bag   │  ← YOU IMPLEMENT
             │  + has(int)             │
             └─────────────────────────┘

   Same structure exists for tree_bag → searchable_tree_bag
```

```
   set  ──── wraps ────►  searchable_bag*  (pointer to any searchable bag)
```

---

## 💡 Core Idea

**Diamond problem:** `array_bag` and `searchable_bag` both inherit from `bag`. Without `virtual`, a `searchable_array_bag` would contain **two copies** of `bag`.

The fix: `searchable_bag` uses `virtual public bag` — this tells the compiler to share a **single `bag` sub-object** across the diamond.

```cpp
class searchable_bag : virtual public bag { ... };
//                     ^^^^^^^ KEY WORD
```

---

## ⚙️ Function Breakdown

### `searchable_array_bag::has(int val)` — Linear Search
Scans `this->data[0..size-1]` (inherited from `array_bag`) and returns `true` on first match.

```
for each element in data[0..size):
    if element == val → return true
return false
```

---

### `searchable_tree_bag::has(int val)` — BST Traversal

```
            [5]
           /   \
         [3]   [8]
         / \
       [1] [4]

has(4):  5 → go left (4 < 5) → 3 → go right (4 > 3) → 4 → found ✓
```

```
current = this->tree (root)
while current is not NULL:
    if val == current->value → return true
    if val > current->value  → go right
    else                     → go left
return false
```

> ⚠️ **Tricky:** This function is `const` — you cannot use `node **` (a pointer-to-pointer would allow modifying `this->tree`). Use a plain local `node *current` — moving `current` locally does **not** mutate the tree.

---

### `set::insert(int val)` — Uniqueness Enforcement
Only inserts if `has()` returns false.

```cpp
if (this->sb && !this->sb->has(val))
    this->sb->insert(val);
```

This is the **only difference** between a set and a bag.

---

### `set` constructor / destructor

```cpp
set::set(searchable_bag &sb) : sb(&sb) {}  // stores a pointer, does NOT own it
```

> ⚠️ **Tricky:** The destructor must **not** `delete` or `clear` the bag. `set` is a **wrapper/view** — it doesn't own the object. The bag is created and destroyed by whoever called `set(sb)` (i.e., `main`).

---

### OCF — Calling Parent `operator=`
When writing the assignment operator for `searchable_array_bag`, you must delegate to the parent to copy its private members:

```cpp
searchable_array_bag &operator=(const searchable_array_bag &other) {
    if (this != &other)
        array_bag::operator=(other);  // copies data[] and size
    return *this;
}
```

---

## 📦 Given vs. To Implement

| File | Status | Description |
|---|---|---|
| `bag.hpp` | ✅ Given | Abstract base — defines `insert`, `print`, `clear` |
| `searchable_bag.hpp` | ✅ Given | Abstract — adds `has()` interface |
| `array_bag.hpp / .cpp` | ✅ Given | Array-backed bag implementation |
| `tree_bag.hpp / .cpp` | ✅ Given | BST-backed bag implementation |
| `main.cpp` | ✅ Given | Test driver — do not modify |
| `searchable_array_bag.hpp / .cpp` | 🔨 Implement | Array bag + `has()` |
| `searchable_tree_bag.hpp / .cpp` | 🔨 Implement | Tree bag + `has()` |
| `set.hpp / .cpp` | 🔨 Implement | Set wrapper over any `searchable_bag*` |

---

## 🧰 Key Concepts Reference

| Concept | Detail |
|---|---|
| `virtual public bag` | Solves diamond — one shared `bag` sub-object |
| `const` restriction on `has()` | Cannot use `node**`; use local `node*` instead |
| Wrapper/view pattern | `set` holds a pointer but does not own the lifetime |
| `ParentClass::operator=` | Call explicitly to copy private inherited members |

---

## 🚀 Usage

```bash
cd Level_01/polyset
make
./polyset 1 7 9 0 23
```

---

> ⚠️ **Note:** All code must compile with `-std=c++98`. All classes must follow Orthodox Canonical Form.

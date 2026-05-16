<br>

<div align="center">

# 📐 vect2

**2D Integer Vector with Operator Overloading — 42 Exam Rank 05**

![Language](https://img.shields.io/badge/Language-C%2B%2B98-blue?style=flat-square)
![School](https://img.shields.io/badge/School-42%20%7C%201337-000000?style=flat-square)
![Level](https://img.shields.io/badge/Level-01-orange?style=flat-square)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen?style=flat-square)

</div>

---

## 📋 Subject

> Create a class `vect2` representing a 2D mathematical vector containing `int`s.  
> Files to implement: `vect2.hpp`, `vect2.cpp`

**Required operations:**

| Operation | Example |
|---|---|
| Addition | `v1 + v2` |
| Subtraction | `v1 - v2` |
| Scalar multiplication | `v * 2` and `2 * v` |
| Index access | `v[0]` (x), `v[1]` (y) |
| Print | `std::cout << v` → `{x, y}` |

---

## 💡 Core Idea

The class stores two `int` members (`x`, `y`). Every operation is **component-wise**: apply the operation independently to `x` and `y`.

```
vect2(2, 3) + vect2(1, 4)  →  vect2(3, 7)
vect2(2, 3) * 2             →  vect2(4, 6)
```

---

## ⚙️ Function Breakdown

### Orthodox Canonical Form
Default constructor initializes both to `0`. Parameterized constructor: `vect2(int x, int y)` using initializer list.

---

### `operator+` / `operator-` — Vector Arithmetic
Returns a **new `vect2` by value** (result is a temporary, not `*this`).

```cpp
vect2 result;
result.x = this->x + other.x;
result.y = this->y + other.y;
return result;
```

---

### `operator*(int scalar)` — Scalar Multiplication (member)
Handles `v * 2`: multiplies both components by the scalar.

> ⚠️ **Tricky:** `2 * v` (scalar on the **left**) **cannot** be a member function — the left operand is `int`, not `vect2`, so `int` would need to have the method.  
> Solution: a **free function** `operator*(int scalar, const vect2 &v)` that delegates to `v * scalar`.

```cpp
// Free function outside the class:
vect2 operator*(int scalar, const vect2 &v) {
    return v * scalar;  // calls the member version
}
```

---

### `operator[]` — Index Access (two overloads required)

| Version | Signature | Purpose |
|---|---|---|
| Read (const) | `const int& operator[](int) const` | Read from a `const` object |
| Write (non-const) | `int& operator[](int)` | Allows `v[0] = 5` |

Both return a reference to `x` when index is `0`, and `y` otherwise.

---

### `operator++` / `operator--` — Increment / Decrement

| Form | Signature | Behavior |
|---|---|---|
| Prefix `++v` | `vect2& operator++()` | Modify `*this`, return `*this` by reference |
| Postfix `v++` | `vect2 operator++(int)` | Save copy, increment, return **saved copy by value** |

> ⚠️ **Tricky:** The dummy `int` parameter in the postfix signature is what tells the compiler it's postfix — it has no name and is never used.

---

### `operator<<` — Stream Output (free function)
Must be a **free function** since the left operand is `std::ostream`, not `vect2`.  
Outputs: `{x, y}` using `getX()` / `getY()` since `x` and `y` are private.

---

## 🧰 Key Concepts Reference

| Concept | Detail |
|---|---|
| Free `operator*` | Required when built-in type is on the left (`2 * v`) |
| Dual `operator[]` | `const` overload for reading, non-const for writing |
| Postfix `(int)` | Dummy `int` parameter distinguishes postfix from prefix |
| Return by value vs reference | Arithmetic returns new value; `+=`, `++` return `*this` |

---

## 🚀 Usage

```bash
cd Level_01/vec2
make
./vect2
```

---

> ⚠️ **Note:** All code must compile with `-std=c++98`.

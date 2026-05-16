<br>

<div align="center">

# 🔢 bigint

**Arbitrary Precision Unsigned Integer — 42 Exam Rank 05**

![Language](https://img.shields.io/badge/Language-C%2B%2B98-blue?style=flat-square)
![School](https://img.shields.io/badge/School-42%20%7C%201337-000000?style=flat-square)
![Level](https://img.shields.io/badge/Level-01-orange?style=flat-square)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen?style=flat-square)

</div>

---

## 📋 Subject

> Create a class `bigint` that stores an **arbitrary precision unsigned integer**.  
> Files to implement: `bigint.hpp`, `bigint.cpp`

**Required operations:**

| Operation | Example |
|---|---|
| Addition | `a + b`, `a += b`, `++a`, `a++` |
| Comparison | `<` `>` `==` `!=` `<=` `>=` |
| Left digit-shift | `42 << 3` → `42000` |
| Right digit-shift | `1337 >> 2` → `13` |
| Print | `std::cout << bg` (no leading zeros) |

---

## 💡 Core Idea

Instead of using a fixed-size integer type (limited to ~18 digits), the number is stored as a **`std::string` of digit characters** — meaning it can grow as large as RAM allows.

```
bigint(1337)  →  _digits = "1337"
bigint(0)     →  _digits = "0"
```

---

## ⚙️ Function Breakdown

### `bigint(unsigned long n)` — Constructor
Converts the number to a string using `std::ostringstream` (c++98 replacement for `std::to_string`).

```cpp
std::ostringstream oss;
oss << n;
_digits = oss.str();
```

---

### `operator+` — Addition
Simulates grade-school addition **right to left** using two indices on each string.

```
  "9 9"
+ "  1"
———————
carry → "1 0 0"   →  reverse  →  "001"  →  "100"
```

```
i = last index of this->_digits
j = last index of other._digits

while (i >= 0 OR j >= 0 OR carry > 0):
    d1 = digit at i (or 0 if exhausted)
    d2 = digit at j (or 0 if exhausted)
    sum = d1 + d2 + carry
    append (sum % 10) to result
    carry = sum / 10

reverse result string
```

> ⚠️ **Tricky:** The loop must continue `while carry > 0` even after both strings are exhausted — otherwise `99 + 1` would give `"00"` instead of `"100"`.

---

### `operator<<=` — Left Digit-Shift (multiply by 10ⁿ)
Appends `n` zeroes to `_digits`.

```cpp
this->_digits.append(n, '0');   // "42" << 3  →  "42000"
```

> ⚠️ **Tricky:** `shift` is a `bigint`, not an `int`. Use `std::istringstream` to extract the value as a `size_t` from `shift.getDigits()`.

---

### `operator>>=` — Right Digit-Shift (divide by 10ⁿ)
Truncates `_digits` using `std::string::resize`.

```cpp
_digits.resize(_digits.length() - shift);  // "1337" >> 2  →  "13"
```

If shift ≥ number of digits → result is `"0"`.

---

### `operator<` — Comparison
1. If lengths differ → **longer string = bigger number** (no digit comparison needed)
2. If same length → `std::string::operator<` compares **character by character from left** — which works correctly for digit strings of equal length

---

### `operator<<` — Stream Output (free function)
Must be a **free function** (not a member) so `std::cout << bg` works. Just calls `os << bg.getDigits()`.

---

## 🧰 New Functions Reference

| Function | Header | Description |
|---|---|---|
| `std::ostringstream` | `<sstream>` | Write into a string buffer (like `cout` but into a `string`) |
| `std::istringstream` | `<sstream>` | Read from a string (like `cin` but from a `string`) |
| `oss.str()` | `<sstream>` | Extract the built string from an `ostringstream` |
| `string.append(n, c)` | `<string>` | Append character `c` exactly `n` times |
| `string.resize(n)` | `<string>` | Truncate or extend the string to length `n` |
| `std::reverse(b, e)` | `<algorithm>` | Reverse a range in-place |

---

## 🚀 Usage

```bash
cd Level_01/bigint
make
./bigint
```

---

> ⚠️ **Note:** All code must compile with `-std=c++98`. No `auto`, no `std::to_string`, no range-for.

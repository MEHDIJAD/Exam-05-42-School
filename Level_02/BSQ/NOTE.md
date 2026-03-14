# BSQ - Notes and Logic

### Missing Line Break (`\n`)

**Question**: Why must we check for a `\n` at the end of every line read by `getline`?

**Response**: The subject explicitly states: "At each end of line, there's a line break." `getline` can return a string that is terminated by `\0` (null) but lacks a `\n` if the file ends prematurely. 

### Test Suite Overview

| File | Scenario | Expected Output |
| :--- | :--- | :--- |
| `t_valid` | A perfect 3x3 map | `VALID MAP!` |
| `t_too_many` | Header says 2 lines, file has 3 | `map error` |
| `t_too_few` | Header says 5 lines, file has 2 | `map error` |
| `t_wrong_width` | Second line is shorter than the first | `map error` |
| `t_bad_char` | Contains a character not in the header | `map error` |
| `t_dup_header` | Header has two `.` characters | `map error` |
| `t_no_newline` | Last line is missing the `\n` | `map error` |
| `t_zero_lines` | Header specifies 0 lines | `map error` |

## 1. What does "Arbitrary Precision Unsigned Integer" mean?

* **Arbitrary Precision:** The number can have as many digits as your RAM allows (e.g., 1,000 digits), unlike standard types which are limited (e.g., int stops at ~2 billion).

* **Unsigned Integer:** It stores only non-negative whole numbers (0, 1, 2...), with no negative signs and no decimal points.

## 2. Why use **unsigned long long** in the constructor?

* Largest Standard Type: unsigned long long is the biggest integer C++ supports natively. We use it to initialize the class, but once the number is inside your std::string, it can grow infinitely larger than a long long.


## 3. stringstream - c++98 way to convert number to string

Think of stringstream (string stream) as a way to treat a String exactly like a Terminal.

**```std::cout``` writes data to your screen.**

**```std::ostringstream``` writes data into a std::string.**

**```std::cin``` reads data from your keyboard.**

**```std::istringstream``` reads data from a std::string.**

ℹ️ You need ```#include <sstream>``` to use them.

### 1. std::ostringstream (Output String Stream)

#### Goal: 

Convert a Number -> String (Replacement for std::to_string).

Think of this as a **"printer"** that prints into a string buffer instead of the console.

#### How it works:

1. Create the stream object.
2. Use the << operator (just like cout) to push numbers into it.
3. Call .str() to get the final string out.

#### CODE:

```cpp
#include <sstream> // Required

bigint::bigint(unsigned long long n) {
    std::ostringstream oss; // 1. Create the 'printer'
    
    oss << n;               // 2. Print 'n' into it (e.g., prints 42)
    
    this->_digits = oss.str(); // 3. Extract the result "42"
}
```

#### Example Usage of ostringstream

```cpp
#include <sstream>
#include <string>

unsigned long num = 123456789;

std::ostringstream oss; // Create an output string stream
oss << num; // Insert the number into the stream
std::string str = oss.str(); // Get the string representation
```

### std::istringstream (Input String Stream)

#### Goal:

Convert a String -> Number (Replacement for std::stoi).

Think of this as a fake **keyboard**. You feed it a string, and then you "read" variables from it using >>.

### How it works:

Create the stream object and give it the string (e.g., "1337").

Use the >> operator (just like cin) to extract the number.

#### CODE:

```cpp
#include <sstream>

bigint &bigint::operator<<=(const bigint &shift) {
    if (this->_digits == "0" || shift._digits == "0")
        return *this;

    // 1. Create the 'fake keyboard' with the string inside
    std::istringstream iss(shift.getDigits());
    
    unsigned long n;
    
    // 2. Read the number out (just like cin >> n)
    iss >> n; 

    this->_digits.append(n, '0');
    return *this;
}
```

#### Example Usage of istringstream

```cpp
#include <sstream>
#include <string>

std::string str = "123456789";
std::istringstream iss(str); // Create an input string stream
unsigned long num;

iss >> num; // Extract the number from the stream
```




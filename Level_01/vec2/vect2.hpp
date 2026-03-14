#ifndef VECT2_HPP
#define VECT2_HPP

/*! PSEUDOCODE:
	1. creat class
		- var: two int for 2 dimention vector
		- meth:
			1. OF: default/param/copy, assigment op=, ~des
			2. addition
			3.  subtraction
			4. multiplication by scaler 📌(vect2(2,2) * 2 == vect2(4,4)) is true)
			5. op[] (used to access the component of of your vector 💬)
				The "Writer" (Non-const):
				Signature: int& operator[](int index)
				Returns: A reference (int&).
				Purpose: Allows you to change the value (e.g., v[0] = 42;).

				The "Reader" (Const):
				Signature: int operator[](int index) const
				Returns: A copy (or const int&).
				Purpose: Allows you to read the value from a const object (e.g., std::cout << const_v[0];).
			6. op<< 
				std::cout << v << std::endl;
				SHOULD produce the same output as:
				s << { << v[0] << ,  << v[1] << } << std::endl;
			7. Getters func
			8. @note main must work
*/

#include <iostream>
	
/*! @brief Class representing a 2D vector for mathematical operations. */
class vect2 {
	private:
		int x; /*!< X-coordinate. */
		int y; /*!< Y-coordinate. */
	public:
		// 1. OF
		/*! @brief Default constructor. */
		vect2();
		/*! @brief Parameterized constructor. */
		vect2(int, int);
		/*! @brief Copy constructor. */
		vect2(const vect2&);
		/*! @brief Copy assignment operator. */
		vect2 &operator=(const vect2&);

		// 2. addition
		/*! @brief Vector addition. */
		vect2 operator+(const vect2&) const;
		/*! @brief Prefix increment. */
		vect2 &operator++(); // ++obj
		/*! @brief Postfix increment. */
		vect2 operator++(int); // obj++
		/*! @brief Compound addition. */
		vect2 &operator+=(const vect2&);

		// 3. sub
		/*! @brief Vector subtraction. */
		vect2 operator-(const vect2&) const;
		/*! @brief Unary negation. */
		vect2 operator-() const;
		/*! @brief Prefix decrement. */
		vect2 &operator--();
		/*! @brief Postfix decrement. */
		vect2 operator--(int);
		/*! @brief Compound subtraction. */
		vect2 &operator-=(const vect2&);

		// 4. mult by scaler
		/*! @brief Scalar multiplication. */
		vect2 operator*(int) const;
		/*! @brief Vector multiplication (component-wise). */
		vect2 operator*(const vect2&) const;
		/*! @brief Compound scalar multiplication. */
		vect2 &operator*=(int);

		// 5. op[]
		/*! @brief Subscript operator (read-only). */
		const int &operator[](int index) const;
		/*! @brief Subscript operator (read-write). */
		int &operator[](int index);

		// 7. Getters
		/*! @brief Returns X coordinate. */
		int getX() const;
		/*! @brief Returns Y coordinate. */
		int getY() const;

		// == && != 
		/*! @brief Equality check. */
		bool operator==(const vect2&) const;
		/*! @brief Inequality check. */
		bool operator!=(const vect2&) const;
};


// 6. op<< 
	//	std::cout << v << std::endl;
	//	SHOULD produce the same output as:
	//	s << { << v[0] << ,  << v[1] << } << std::endl;

/*! @brief Stream insertion operator. */
std::ostream &operator<<(std::ostream &os, const vect2& vec);

// 🚨 scaler * obj
// we need int.op(v)
// 2 * v => 2.op*(v)
/*! @brief Multiplies integer by vect2. */
vect2 operator*(int, const vect2 &);

#endif

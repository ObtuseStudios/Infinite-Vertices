//Copyright 2016, Cameron bell, All rights reserved

//Include Guards
#pragma once

#include <iostream>

namespace Penguin
{
	//Stores multiple values
	struct Vector
	{
		//Variables
		float x, y = 0;

		//Constructors sets all values, though x is optional
		Vector(float a = 0, float b = 0)
			: x(a), y(b) {}

		//Adds two vecs together
		Vector& add(const Vector& other)
		{
			//Add axis
			x += other.x;
			y += other.y;

			//Dereference
			return (*this);
		};

		//Gets the difference of two vectors
		Vector& subtract(const Vector& other)
		{
			//Subtract axis
			x -= other.x;
			y -= other.y;

			//Dereference
			return (*this);
		};

		//Multiplys two vecs together
		Vector& multiply(const Vector& other)
		{
			//Times axis
			x *= other.x;
			y *= other.y;

			//Dereference
			return (*this);
		};

		//Divides two vecs
		Vector& divide(const Vector& other)
		{
			//Divide axis
			x /= other.x;
			y /= other.y;

			//Dereference
			return (*this);
		};

		//Overload + operator
		friend Vector& operator+(Vector a, const Vector& b)
		{
			//Add using function in class
			return a.add(b);
		}

		//Overload - operator
		friend Vector& operator-(Vector a, const Vector& b)
		{
			//Minus using function in class
			return a.subtract(b);
		}

		//Overload * operator
		friend Vector& operator*(Vector a, const Vector& b)
		{
			//Times using function in class
			return a.multiply(b);
		}

		//Overload / operator
		friend Vector& operator/(Vector a, const Vector& b)
		{
			//Divide using function in class
			return a.divide(b);
		}

		//Overload + operator for other nums
		friend Vector& operator+(Vector a, float& b)
		{
			//Add using function in class
			return a.add(Vector(b, b));
		}

		//Overload - operator for other nums
		friend Vector& operator-(Vector a, float& b)
		{
			//Add using function in class
			return a.subtract(Vector(b, b));
		}

		//Overload * operator for other nums
		friend Vector& operator*(Vector a, float& b)
		{
			//Add using function in class
			return a.multiply(Vector(b, b));
		}

		//Overload / operator for other nums
		friend Vector& operator/(Vector a, float& b)
		{
			//Add using function in class
			return a.divide(Vector(b, b));
		}

		//Overload the += operator
		Vector& operator+=(const Vector& other)
		{
			//Add with self
			return add(other);
		}

		//Overload the -= operator
		Vector& operator-=(const Vector& other)
		{
			//Minus with self
			return subtract(other);
		}

		//Overload the *= operator
		Vector& operator*=(const Vector& other)
		{
			//Times with self
			return multiply(other);
		}

		//Overload the /= operator
		Vector& operator/=(const Vector& other)
		{
			//Divide with self
			return divide(other);
		}

		//Overload the comparison operator
		bool operator==(const Vector& other)
		{
			//Compare the x and y
			return other.x == x && other.y == y;
		}

		//Overload the comparison operator
		bool operator!=(const Vector& other)
		{
			//Compare the x and y
			return other.x != x && other.y != y;
		}

		//Overload cout for printing
		friend std::ostream& operator<<(std::ostream& stream, const Vector& vec)
		{
			//Print
			stream << "Vector: " << vec.x << ", " << vec.y;

			//Return
			return stream;
		};
	};

	/*
	class Vector
	{
	public:
		//The constuctor of a vector takes an x and a y
		Vector(float a = 0, float b = 0) { x = a; y = b; };

		//If the user wants to set the variable later they can.
		void Set(float a = 0, float b = 0) { x = a; y = b; };

		//The actual x and y.
		float y;
		float x;
	};
	*/
}
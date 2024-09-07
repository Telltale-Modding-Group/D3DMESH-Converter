	#pragma once
#ifndef VECTOR_3_H
#define VECTOR_3_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "../../BinarySerialization.h"
#include "../../BinaryDeserialization.h"
#include "../../Json.h"

//||||||||||||||||||||||||||||| VECTOR 3 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| VECTOR 3 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| VECTOR 3 |||||||||||||||||||||||||||||

/// <summary>
/// [12 BYTES] Vector with 3 float32 components (x, y, z)
/// </summary>
struct Vector3
{
	/// <summary>
	/// [4 BYTES] x (horizontal) component.
	/// </summary>
	float x;

	/// <summary>
	/// [4 BYTES] y (vertical) component.
	/// </summary>
	float y;

	/// <summary>
	/// [4 BYTES] z (depth) component.
	/// </summary>
	float z;

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

	Vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	};

	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	};

	Vector3(std::ifstream* inputFileStream)
	{
		x = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		y = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		z = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteFloat32ToBinary(outputFileStream, x); //[4 BYTES]
		WriteFloat32ToBinary(outputFileStream, y); //[4 BYTES]
		WriteFloat32ToBinary(outputFileStream, z); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| OPERATOR OVERLOADS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| OPERATOR OVERLOADS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| OPERATOR OVERLOADS |||||||||||||||||||||||||||||

	//Negative Vector3
	Vector3 operator-()
	{
		x = -x;
		y = -y;
		z = -z;
		return *this;
	};

	//Add Vector3
	Vector3 operator+(const Vector3& b)
	{
		x += b.x;
		y += b.y;
		z += b.z;
		return *this;
	};

	//Add Vector3
	Vector3 operator+=(const Vector3& b)
	{
		x += b.x;
		y += b.y;
		z += b.z;
		return *this;
	};

	//Subtract Vector3
	Vector3 operator-(const Vector3& b)
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;
		return *this;
	};

	//Subtract Vector3
	Vector3 operator-=(const Vector3& b)
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;
		return *this;
	};

	//Multiply Vector3
	Vector3 operator*(const Vector3& b)
	{
		x *= b.x;
		y *= b.y;
		z *= b.z;
		return *this;
	};

	//Multiply Vector3
	Vector3 operator*=(const Vector3& b)
	{
		x *= b.x;
		y *= b.y;
		z *= b.z;
		return *this;
	};

	//Divide Vector3
	Vector3 operator/(const Vector3& b)
	{
		x /= b.x;
		y /= b.y;
		z /= b.z;
		return *this;
	};

	//Divide Vector3
	Vector3 operator/=(const Vector3& b)
	{
		x /= b.x;
		y /= b.y;
		z /= b.z;
		return *this;
	};

	//Multiply float
	Vector3 operator*(const float& b)
	{
		x *= b;
		y *= b;
		z *= b;
		return *this;
	};

	//Multiply float
	Vector3 operator*=(const float& b)
	{
		x *= b;
		y *= b;
		z *= b;
		return *this;
	};

	//Divide float
	Vector3 operator/(const float& b)
	{
		x /= b;
		y /= b;
		z /= b;
		return *this;
	};

	//Divide float
	Vector3 operator/=(const float& b)
	{
		x /= b;
		y /= b;
		z /= b;
		return *this;
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		return "[Vector3] x:" + std::to_string(x) + " y: " + std::to_string(y) + " z: " + std::to_string(z);
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Vector3, x, y, z)
	
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//NOTE: Yes I'm aware that C++ has functionality/operators for returning the size of the object, however...
	//For some of these structs/classes the size C++ returns/gets is wrong and doesn't match what telltale would expect.
	//So for saftey I will just manually calculate the byte size of the object here to what telltale expects.
		
	/// <summary>
	/// [12 BYTES]
	/// </summary>
	/// <returns></returns>
	unsigned int GetByteSize()
	{
		unsigned int totalByteSize = 0;
		totalByteSize += 4; //[4 BYTES] x
		totalByteSize += 4; //[4 BYTES] y
		totalByteSize += 4; //[4 BYTES] z
		return totalByteSize;
	}
};

#endif
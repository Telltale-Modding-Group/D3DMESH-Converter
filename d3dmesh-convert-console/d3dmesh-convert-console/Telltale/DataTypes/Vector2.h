#pragma once
#ifndef VECTOR_2_H
#define VECTOR_2_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: GLM Library
#include <glm.hpp>

//Custom
#include "../../Binary/BinarySerialization.h"
#include "../../Binary/BinaryDeserialization.h"
#include "../../Helper/JsonHelper.h"

//||||||||||||||||||||||||||||| VECTOR 2 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| VECTOR 2 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| VECTOR 2 |||||||||||||||||||||||||||||

/// <summary>
/// [8 BYTES] Vector with 2 float32 components (x, y)
/// </summary>
struct Vector2
{
	/// <summary>
	/// [4 BYTES] x (horizontal) component.
	/// </summary>
	float x;

	/// <summary>
	/// [4 BYTES] y (vertical) component.
	/// </summary>
	float y;

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

	Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	};

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	};

	Vector2(std::ifstream* inputFileStream)
	{
		x = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		y = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
	};

	Vector2(glm::vec2 newVector)
	{
		x = newVector.x;
		y = newVector.y;
	};

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteFloat32ToBinary(outputFileStream, x); //[4 BYTES]
		WriteFloat32ToBinary(outputFileStream, y); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		return "[Vector2] x:" + std::to_string(x) + " y: " + std::to_string(y);
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Vector2, x, y)

	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//NOTE: Yes I'm aware that C++ has functionality/operators for returning the size of the object, however...
	//For some of these structs/classes the size C++ returns/gets is wrong and doesn't match what telltale would expect.
	//So for saftey I will just manually calculate the byte size of the object here to what telltale expects.

	/// <summary>
	/// [8 BYTES]
	/// </summary>
	/// <returns></returns>
	unsigned int GetByteSize() 
	{
		unsigned int totalByteSize = 0;
		totalByteSize += 4; //[4 BYTES] x
		totalByteSize += 4; //[4 BYTES] y
		return totalByteSize;
	}
};

#endif
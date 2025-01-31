#pragma once
#ifndef INTEGER_VECTOR_3_H
#define INTEGER_VECTOR_3_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: GLM Library
#include <glm.hpp>

//Custom
#include "../../Binary/BinarySerialization.h"
#include "../../Binary/BinaryDeserialization.h"
#include "../../Helper/JsonHelper.h"

//||||||||||||||||||||||||||||| INTEGER VECTOR 3 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INTEGER VECTOR 3 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INTEGER VECTOR 3 |||||||||||||||||||||||||||||
//NOTE: This is NOT an actual data structures serialized in a telltale file.
//However there are cases where the vector types do hold integer data per component.

/// <summary>
/// [12 BYTES] Vector with 3 int32 components (x, y, z)
/// </summary>
struct IntegerVector3
{
	/// <summary>
	/// [4 BYTES] x (horizontal) component.
	/// </summary>
	int x;

	/// <summary>
	/// [4 BYTES] y (vertical) component.
	/// </summary>
	int y;

	/// <summary>
	/// [4 BYTES] z (depth) component.
	/// </summary>
	int z;

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

	IntegerVector3()
	{
		x = 0;
		y = 0;
		z = 0;
	};

	IntegerVector3(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	};

	IntegerVector3(std::ifstream*& inputFileStream)
	{
		x = ReadInt32FromBinary(inputFileStream); //[4 BYTES]
		y = ReadInt32FromBinary(inputFileStream); //[4 BYTES]
		z = ReadInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	IntegerVector3(glm::ivec3& newVector)
	{
		x = newVector.x;
		y = newVector.y;
		z = newVector.z;
	};

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream*& outputFileStream)
	{
		WriteInt32ToBinary(outputFileStream, x); //[4 BYTES]
		WriteInt32ToBinary(outputFileStream, y); //[4 BYTES]
		WriteInt32ToBinary(outputFileStream, z); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		return "[IntegerVector3] x:" + std::to_string(x) + " y: " + std::to_string(y) + " z: " + std::to_string(z);
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(IntegerVector3, x, y, z)
};

#endif
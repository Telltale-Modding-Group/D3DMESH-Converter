#pragma once
#ifndef INTEGER_VECTOR_4_H
#define INTEGER_VECTOR_4_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: GLM Library
#include <glm.hpp>

//Custom
#include "../../Binary/BinarySerialization.h"
#include "../../Binary/BinaryDeserialization.h"
#include "../../Helper/JsonHelper.h"

//||||||||||||||||||||||||||||| INTEGER VECTOR 4 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INTEGER VECTOR 4 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INTEGER VECTOR 4 |||||||||||||||||||||||||||||
//NOTE: This is NOT an actual data structures serialized in a telltale file.
//However there are cases where the vector types do hold integer data per component.

/// <summary>
/// [16 BYTES] Vector with 4 int32 components (x, y, z, w)
/// </summary>
struct IntegerVector4
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

	/// <summary>
	/// [4 BYTES] w (scalar) component.
	/// </summary>
	int w;

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

	IntegerVector4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	};

	IntegerVector4(int x, int y, int z, int w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	};

	IntegerVector4(std::ifstream* inputFileStream)
	{
		x = ReadInt32FromBinary(inputFileStream); //[4 BYTES]
		y = ReadInt32FromBinary(inputFileStream); //[4 BYTES]
		z = ReadInt32FromBinary(inputFileStream); //[4 BYTES]
		w = ReadInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	IntegerVector4(glm::ivec4 newVector)
	{
		x = newVector.x;
		y = newVector.y;
		z = newVector.z;
		w = newVector.w;
	};

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteInt32ToBinary(outputFileStream, x); //[4 BYTES]
		WriteInt32ToBinary(outputFileStream, y); //[4 BYTES]
		WriteInt32ToBinary(outputFileStream, z); //[4 BYTES]
		WriteInt32ToBinary(outputFileStream, w); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		return "[IntegerVector4] x:" + std::to_string(x) + " y: " + std::to_string(y) + " z: " + std::to_string(z) + " w: " + std::to_string(w);
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(IntegerVector4, x, y, z, w)
};

#endif
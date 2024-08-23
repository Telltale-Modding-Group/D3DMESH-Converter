#pragma once
#ifndef INTEGER_VECTOR_4_H
#define INTEGER_VECTOR_4_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"

//||||||||||||||||||||||||||||| INTEGER VECTOR 4 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INTEGER VECTOR 4 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INTEGER VECTOR 4 |||||||||||||||||||||||||||||
//NOTE: This is NOT an actual data structures serialized in a telltale file.
//However there are cases where the vector types do hold integer data per component.

/// <summary>
/// [16 bytes] Vector with 4 int32 components (x, y, z, w)
/// </summary>
struct IntegerVector4
{
	/// <summary>
	/// [4 bytes] x (horizontal) component.
	/// </summary>
	int x;

	/// <summary>
	/// [4 bytes] y (vertical) component.
	/// </summary>
	int y;

	/// <summary>
	/// [4 bytes] z (depth) component.
	/// </summary>
	int z;

	/// <summary>
	/// [4 bytes] w (scalar) component.
	/// </summary>
	int w;

	IntegerVector4()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	};

	IntegerVector4(std::ifstream* inputFileStream)
	{
		this->x = ReadInt32FromBinary(inputFileStream); //[4 BYTES]
		this->y = ReadInt32FromBinary(inputFileStream); //[4 BYTES]
		this->z = ReadInt32FromBinary(inputFileStream); //[4 BYTES]
		this->w = ReadInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteInt32ToBinary(outputFileStream, this->x); //[4 BYTES]
		WriteInt32ToBinary(outputFileStream, this->y); //[4 BYTES]
		WriteInt32ToBinary(outputFileStream, this->z); //[4 BYTES]
		WriteInt32ToBinary(outputFileStream, this->w); //[4 BYTES]
	};
};

#endif
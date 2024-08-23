#pragma once
#ifndef INTEGER_VECTOR_3_H
#define INTEGER_VECTOR_3_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"

//||||||||||||||||||||||||||||| INTEGER VECTOR 3 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INTEGER VECTOR 3 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INTEGER VECTOR 3 |||||||||||||||||||||||||||||
//NOTE: This is NOT an actual data structures serialized in a telltale file.
//However there are cases where the vector types do hold integer data per component.

/// <summary>
/// [12 bytes] Vector with 3 int32 components (x, y, z)
/// </summary>
struct IntegerVector3
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

	IntegerVector3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	};

	IntegerVector3(std::ifstream* inputFileStream)
	{
		this->x = ReadInt32FromBinary(inputFileStream); //[4 BYTES]
		this->y = ReadInt32FromBinary(inputFileStream); //[4 BYTES]
		this->z = ReadInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteInt32ToBinary(outputFileStream, this->x); //[4 BYTES]
		WriteInt32ToBinary(outputFileStream, this->y); //[4 BYTES]
		WriteInt32ToBinary(outputFileStream, this->z); //[4 BYTES]
	};
};

#endif
#pragma once
#ifndef UNSIGNED_INTEGER_VECTOR_4_H
#define UNSIGNED_INTEGER_VECTOR_4_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"

//||||||||||||||||||||||||||||| UNSIGNED INTEGER VECTOR 4 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| UNSIGNED INTEGER VECTOR 4 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| UNSIGNED INTEGER VECTOR 4 |||||||||||||||||||||||||||||
//NOTE: This is NOT an actual data structures serialized in a telltale file.
//However there are cases where the vector types do hold integer data per component.

/// <summary>
/// [16 bytes] Vector with 4 uint32 components (x, y, z, w)
/// </summary>
struct UnsignedIntegerVector4
{
	/// <summary>
	/// [4 bytes] x (horizontal) component.
	/// </summary>
	unsigned int x;

	/// <summary>
	/// [4 bytes] y (vertical) component.
	/// </summary>
	unsigned int y;

	/// <summary>
	/// [4 bytes] z (depth) component.
	/// </summary>
	unsigned int z;

	/// <summary>
	/// [4 bytes] w (scalar) component.
	/// </summary>
	unsigned int w;

	UnsignedIntegerVector4()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	};

	UnsignedIntegerVector4(std::ifstream* inputFileStream)
	{
		this->x = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->y = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->z = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->w = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteUInt32ToBinary(outputFileStream, this->x); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->y); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->z); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->w); //[4 BYTES]
	};
};

#endif
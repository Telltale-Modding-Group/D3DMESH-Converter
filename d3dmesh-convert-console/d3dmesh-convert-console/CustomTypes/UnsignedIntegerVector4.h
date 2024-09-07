#pragma once
#ifndef UNSIGNED_INTEGER_VECTOR_4_H
#define UNSIGNED_INTEGER_VECTOR_4_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Json.h"

//||||||||||||||||||||||||||||| UNSIGNED INTEGER VECTOR 4 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| UNSIGNED INTEGER VECTOR 4 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| UNSIGNED INTEGER VECTOR 4 |||||||||||||||||||||||||||||
//NOTE: This is NOT an actual data structures serialized in a telltale file.
//However there are cases where the vector types do hold integer data per component.

/// <summary>
/// [16 BYTES] Vector with 4 uint32 components (x, y, z, w)
/// </summary>
struct UnsignedIntegerVector4
{
	/// <summary>
	/// [4 BYTES] x (horizontal) component.
	/// </summary>
	unsigned int x;

	/// <summary>
	/// [4 BYTES] y (vertical) component.
	/// </summary>
	unsigned int y;

	/// <summary>
	/// [4 BYTES] z (depth) component.
	/// </summary>
	unsigned int z;

	/// <summary>
	/// [4 BYTES] w (scalar) component.
	/// </summary>
	unsigned int w;

	UnsignedIntegerVector4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	};

	UnsignedIntegerVector4(unsigned int x, unsigned int y, unsigned int z, unsigned int w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	};

	UnsignedIntegerVector4(std::ifstream* inputFileStream)
	{
		x = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		y = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		z = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		w = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteUInt32ToBinary(outputFileStream, x); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, y); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, z); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, w); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		return "[UnsignedIntegerVector4] x:" + std::to_string(x) + " y: " + std::to_string(y) + " z: " + std::to_string(z) + " w: " + std::to_string(w);
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(UnsignedIntegerVector4, x, y, z, w)
};

#endif
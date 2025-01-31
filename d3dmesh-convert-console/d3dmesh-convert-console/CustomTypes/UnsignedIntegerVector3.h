#pragma once
#ifndef UNSIGNED_INTEGER_VECTOR_3_H
#define UNSIGNED_INTEGER_VECTOR_3_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: GLM Library
#include <glm.hpp>

//Custom
#include "../../Binary/BinarySerialization.h"
#include "../../Binary/BinaryDeserialization.h"
#include "../../Helper/JsonHelper.h"

//||||||||||||||||||||||||||||| UNSIGNED INTEGER VECTOR 3 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| UNSIGNED INTEGER VECTOR 3 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| UNSIGNED INTEGER VECTOR 3 |||||||||||||||||||||||||||||
//NOTE: This is NOT an actual data structures serialized in a telltale file.
//However there are cases where the vector types do hold integer data per component.

/// <summary>
/// [12 BYTES] Vector with 3 uint32 components (x, y, z)
/// </summary>
struct UnsignedIntegerVector3
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

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

	UnsignedIntegerVector3()
	{
		x = 0;
		y = 0;
		z = 0;
	};

	UnsignedIntegerVector3(unsigned int x, unsigned int y, unsigned int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	};

	UnsignedIntegerVector3(std::ifstream*& inputFileStream)
	{
		x = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		y = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		z = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	UnsignedIntegerVector3(glm::uvec3& newVector)
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
		WriteUInt32ToBinary(outputFileStream, x); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, y); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, z); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		return "[UnsignedIntegerVector3] x:" + std::to_string(x) + " y: " + std::to_string(y) + " z: " + std::to_string(z);
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(UnsignedIntegerVector3, x, y, z)
};

#endif
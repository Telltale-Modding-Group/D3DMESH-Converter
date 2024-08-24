#pragma once
#ifndef UNSIGNED_INTEGER_VECTOR_3_H
#define UNSIGNED_INTEGER_VECTOR_3_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"

//||||||||||||||||||||||||||||| UNSIGNED INTEGER VECTOR 3 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| UNSIGNED INTEGER VECTOR 3 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| UNSIGNED INTEGER VECTOR 3 |||||||||||||||||||||||||||||
//NOTE: This is NOT an actual data structures serialized in a telltale file.
//However there are cases where the vector types do hold integer data per component.

/// <summary>
/// [12 bytes] Vector with 3 uint32 components (x, y, z)
/// </summary>
struct UnsignedIntegerVector3
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

	UnsignedIntegerVector3(std::ifstream* inputFileStream)
	{
		x = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		y = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		z = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
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

	void to_json(nlohmann::json& json, const UnsignedIntegerVector3& value)
	{
		json = nlohmann::json
		{
			{ "x", value.x },
			{ "y", value.y },
			{ "z", value.z },
		};
	}

	void from_json(const nlohmann::json& json, UnsignedIntegerVector3& value)
	{
		json.at("x").get_to(value.x);
		json.at("y").get_to(value.y);
		json.at("z").get_to(value.z);
	}
};

#endif
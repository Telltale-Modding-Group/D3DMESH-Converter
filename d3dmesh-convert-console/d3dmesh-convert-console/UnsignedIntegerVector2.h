#pragma once
#ifndef UNSIGNED_INTEGER_VECTOR_2_H
#define UNSIGNED_INTEGER_VECTOR_2_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"

//||||||||||||||||||||||||||||| UNSIGNED INTEGER VECTOR 2 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| UNSIGNED INTEGER VECTOR 2 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| UNSIGNED INTEGER VECTOR 2 |||||||||||||||||||||||||||||
//NOTE: This is NOT an actual data structures serialized in a telltale file.
//However there are cases where the vector types do hold integer data per component.

/// <summary>
/// [8 bytes] Vector with 2 uint32 components (x, y)
/// </summary>
struct UnsignedIntegerVector2
{
	/// <summary>
	/// [4 bytes] x (horizontal) component.
	/// </summary>
	unsigned int x;

	/// <summary>
	/// [4 bytes] y (vertical) component.
	/// </summary>
	unsigned int y;

	UnsignedIntegerVector2()
	{
		x = 0;
		y = 0;
	};

	UnsignedIntegerVector2(unsigned int x, unsigned int y)
	{
		this->x = x;
		this->y = y;
	};

	UnsignedIntegerVector2(std::ifstream* inputFileStream)
	{
		x = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		y = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteUInt32ToBinary(outputFileStream, x); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, y); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		return "[UnsignedIntegerVector2] x:" + std::to_string(x) + " y: " + std::to_string(y);
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/

	void to_json(nlohmann::json& json, const UnsignedIntegerVector2& value)
	{
		json = nlohmann::json
		{
			{ "x", value.x },
			{ "y", value.y },
		};
	}

	void from_json(const nlohmann::json& json, UnsignedIntegerVector2& value)
	{
		json.at("x").get_to(value.x);
		json.at("y").get_to(value.y);
	}
};

#endif
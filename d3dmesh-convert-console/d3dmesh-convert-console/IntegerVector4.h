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
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	};

	IntegerVector4(std::ifstream* inputFileStream)
	{
		x = ReadInt32FromBinary(inputFileStream); //[4 BYTES]
		y = ReadInt32FromBinary(inputFileStream); //[4 BYTES]
		z = ReadInt32FromBinary(inputFileStream); //[4 BYTES]
		w = ReadInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteInt32ToBinary(outputFileStream, x); //[4 BYTES]
		WriteInt32ToBinary(outputFileStream, y); //[4 BYTES]
		WriteInt32ToBinary(outputFileStream, z); //[4 BYTES]
		WriteInt32ToBinary(outputFileStream, w); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/

	void to_json(nlohmann::json& json, const IntegerVector4& value)
	{
		json = nlohmann::json
		{
			{ "x", value.x },
			{ "y", value.y },
			{ "z", value.z },
			{ "w", value.w },
		};
	}

	void from_json(const nlohmann::json& json, IntegerVector4& value)
	{
		json.at("x").get_to(value.x);
		json.at("y").get_to(value.y);
		json.at("z").get_to(value.z);
		json.at("w").get_to(value.w);
	}
};

#endif
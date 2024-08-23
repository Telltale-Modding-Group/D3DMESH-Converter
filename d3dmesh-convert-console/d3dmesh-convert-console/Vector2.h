#pragma once
#ifndef VECTOR_2_H
#define VECTOR_2_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"

//||||||||||||||||||||||||||||| VECTOR 2 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| VECTOR 2 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| VECTOR 2 |||||||||||||||||||||||||||||

/// <summary>
/// [8 bytes] Vector with 2 float32 components (x, y)
/// </summary>
struct Vector2
{
	/// <summary>
	/// [4 bytes] x (horizontal) component.
	/// </summary>
	float x;

	/// <summary>
	/// [4 bytes] y (vertical) component.
	/// </summary>
	float y;

	Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	};

	Vector2(std::ifstream* inputFileStream)
	{
		x = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		y = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteFloat32ToBinary(outputFileStream, x); //[4 BYTES]
		WriteFloat32ToBinary(outputFileStream, y); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/

	void to_json(nlohmann::json& json, const Vector2& value)
	{
		json = nlohmann::json
		{ 
			{ "x", value.x },
			{ "y", value.y },
		};
	}

	void from_json(const nlohmann::json& json, Vector2& value)
	{
		json.at("x").get_to(value.x);
		json.at("y").get_to(value.y);
	}
};

#endif
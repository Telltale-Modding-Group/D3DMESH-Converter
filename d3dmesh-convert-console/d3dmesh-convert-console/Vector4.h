#pragma once
#ifndef VECTOR_4_H
#define VECTOR_4_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"

//||||||||||||||||||||||||||||| VECTOR 4 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| VECTOR 4 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| VECTOR 4 |||||||||||||||||||||||||||||

/// <summary>
/// [16 bytes] Vector with 4 float32 components (x, y, z, w)
/// </summary>
struct Vector4
{
	/// <summary>
	/// [4 bytes] x (horizontal) component.
	/// </summary>
	float x;

	/// <summary>
	/// [4 bytes] y (vertical) component.
	/// </summary>
	float y;

	/// <summary>
	/// [4 bytes] z (depth) component.
	/// </summary>
	float z;

	/// <summary>
	/// [4 bytes] w (scalar) component.
	/// </summary>
	float w;

	Vector4()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	};

	Vector4(std::ifstream* inputFileStream)
	{
		x = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		y = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		z = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		w = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteFloat32ToBinary(outputFileStream, x); //[4 BYTES]
		WriteFloat32ToBinary(outputFileStream, y); //[4 BYTES]
		WriteFloat32ToBinary(outputFileStream, z); //[4 BYTES]
		WriteFloat32ToBinary(outputFileStream, w); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/

	void to_json(nlohmann::json& json, const Vector4& value)
	{
		json = nlohmann::json
		{
			{ "x", value.x },
			{ "y", value.y },
			{ "z", value.z },
			{ "w", value.w },
		};
	}

	void from_json(const nlohmann::json& json, Vector4& value)
	{
		json.at("x").get_to(value.x);
		json.at("y").get_to(value.y);
		json.at("z").get_to(value.z);
		json.at("w").get_to(value.w);
	}
};

#endif
#pragma once
#ifndef QUATERNION_H
#define QUATERNION_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"

//||||||||||||||||||||||||||||| QUATERNION |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| QUATERNION |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| QUATERNION |||||||||||||||||||||||||||||

/// <summary>
/// [16 bytes] A vector-like data structure used to represent rotations
/// </summary>
struct Quaternion
{
	/// <summary>
	/// [4 bytes] x component used to help define the axis of rotation
	/// </summary>
	float x;

	/// <summary>
	/// [4 bytes] y component used to help define the axis of rotation
	/// </summary>
	float y;

	/// <summary>
	/// [4 bytes] z component used to help define the axis of rotation
	/// </summary>
	float z;

	/// <summary>
	/// [4 bytes] w component used to determine the angle of rotation around the rotation axis
	/// </summary>
	float w;

	Quaternion()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	};

	Quaternion(std::ifstream* inputFileStream)
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

	void to_json(nlohmann::json& json, const Quaternion& value)
	{
		json = nlohmann::json
		{
			{ "x", value.x },
			{ "y", value.y },
			{ "z", value.z },
			{ "w", value.w },
		};
	}

	void from_json(const nlohmann::json& json, Quaternion& value)
	{
		json.at("x").get_to(value.x);
		json.at("y").get_to(value.y);
		json.at("z").get_to(value.z);
		json.at("w").get_to(value.w);
	}
};

#endif
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
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->w = 0.0f;
	};

	Quaternion(std::ifstream* inputFileStream)
	{
		this->x = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		this->y = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		this->z = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		this->w = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteFloat32ToBinary(outputFileStream, this->x); //[4 BYTES]
		WriteFloat32ToBinary(outputFileStream, this->y); //[4 BYTES]
		WriteFloat32ToBinary(outputFileStream, this->z); //[4 BYTES]
		WriteFloat32ToBinary(outputFileStream, this->w); //[4 BYTES]
	};
};

#endif
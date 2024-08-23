#pragma once
#ifndef VECTOR_3_H
#define VECTOR_3_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"

//||||||||||||||||||||||||||||| VECTOR 3 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| VECTOR 3 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| VECTOR 3 |||||||||||||||||||||||||||||

/// <summary>
/// [12 bytes] Vector with 3 float32 components (x, y, z)
/// </summary>
struct Vector3
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

	Vector3()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	};

	Vector3(std::ifstream* inputFileStream)
	{
		this->x = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		this->y = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		this->z = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteFloat32ToBinary(outputFileStream, this->x); //[4 BYTES]
		WriteFloat32ToBinary(outputFileStream, this->y); //[4 BYTES]
		WriteFloat32ToBinary(outputFileStream, this->z); //[4 BYTES]
	};
};

#endif
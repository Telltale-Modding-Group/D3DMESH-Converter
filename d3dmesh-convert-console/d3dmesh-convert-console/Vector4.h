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
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->w = 0.0f;
	};

	Vector4(std::ifstream* inputFileStream)
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
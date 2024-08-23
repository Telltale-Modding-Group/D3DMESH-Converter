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
		this->x = 0.0f;
		this->y = 0.0f;
	};

	Vector2(std::ifstream* inputFileStream)
	{
		this->x = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		this->y = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
	};

	/*
	Vector2(nlohmann::json& json)
	{
		this->x = json.at("x").get_to(this->x);
		this->y = json.at("y").get_to(this->y);
	};

	void ToJson(nlohmann::json& json)
	{
		json.push_back(
			{
				{ "x", this->x },
				{ "y", this->y },
			}
			);
	};
	*/

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteFloat32ToBinary(outputFileStream, this->x); //[4 BYTES]
		WriteFloat32ToBinary(outputFileStream, this->y); //[4 BYTES]
	};
};

#endif
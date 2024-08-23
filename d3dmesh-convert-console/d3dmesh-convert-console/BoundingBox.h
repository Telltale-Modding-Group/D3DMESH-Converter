#pragma once
#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"

//||||||||||||||||||||||||||||| BOUNDING BOX |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| BOUNDING BOX |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| BOUNDING BOX |||||||||||||||||||||||||||||

/// <summary>
/// [24 bytes] A bounding box in three-dimensional space.
/// </summary>
struct BoundingBox
{
	/// <summary>
	/// [12 bytes] Represents the minimum coordinates of the bounding box in three-dimensional space.
	/// </summary>
	Vector3 mMin;

	/// <summary>
	/// [12 bytes] Represents the maximum coordinates of the bounding box in three-dimensional space.
	/// </summary>
	Vector3 mMax;

	BoundingBox()
	{
		mMin = {};
		mMax = {};
	};

	BoundingBox(std::ifstream* inputFileStream)
	{
		mMin = Vector3(inputFileStream); //[12 BYTES]
		mMax = Vector3(inputFileStream); //[12 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		mMin.BinarySerialize(outputFileStream); //[12 BYTES]
		mMax.BinarySerialize(outputFileStream); //[12 BYTES]
	};
};

#endif
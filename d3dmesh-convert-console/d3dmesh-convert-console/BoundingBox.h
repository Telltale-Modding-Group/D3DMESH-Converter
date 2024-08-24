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
/// [24 BYTES] A bounding box in three-dimensional space.
/// </summary>
struct BoundingBox
{
	/// <summary>
	/// [12 BYTES] Represents the minimum coordinates of the bounding box in three-dimensional space.
	/// </summary>
	Vector3 mMin;

	/// <summary>
	/// [12 BYTES] Represents the maximum coordinates of the bounding box in three-dimensional space.
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

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "\n";
		output += "[BoundingBox] mMin: " + mMin.ToString() + "\n";
		output += "[BoundingBox] mMax: " + mMax.ToString();
		return output;
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/

	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//NOTE: Yes I'm aware that C++ has functionality/operators for returning the size of the object, however...
	//For some of these structs/classes the size C++ returns/gets is wrong and doesn't match what telltale would expect.
	//So for saftey I will just manually calculate the byte size of the object here to what telltale expects.

	/// <summary>
	/// [24 BYTES]
	/// </summary>
	/// <returns></returns>
	unsigned int GetByteSize()
	{
		unsigned int totalByteSize = 0;
		totalByteSize += mMin.GetByteSize(); //[12 BYTES] mMin
		totalByteSize += mMax.GetByteSize(); //[12 BYTES] mMax
		return totalByteSize;
	}
};

#endif
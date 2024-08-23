#pragma once
#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"

//||||||||||||||||||||||||||||| BOUNDING SPHERE |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| BOUNDING SPHERE |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| BOUNDING SPHERE |||||||||||||||||||||||||||||

/// <summary>
/// [20 bytes] A bounding sphere in three-dimensional space.
/// </summary>
struct BoundingSphere
{
	/// <summary>
	/// [4 bytes] The size of the current data structure (this value should be 20)
	/// <para>(CALCULATION) to calculate block size... </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the block size variable itself. </para>
	/// <para> Add 12, as this is the size of a Vector3 that represents the mCenter variable. </para>
	/// <para> Add 4, as this is the size of a float32 that represents the mRadius variable. </para>
	/// </summary>
	unsigned int mBlockSize;

	/// <summary>
	/// [12 bytes] Center point of the bounding sphere in three-dimensional space.
	/// </summary>
	Vector3 mCenter;

	/// <summary>
	/// [4 bytes] Radius of the bounding sphere.
	/// </summary>
	float mRadius;

	BoundingSphere()
	{
		this->mBlockSize = 20;
		this->mCenter = {};
		this->mRadius = 0.0f;
	};

	BoundingSphere(std::ifstream* inputFileStream)
	{
		this->mBlockSize = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mCenter = Vector3(inputFileStream); //[12 BYTES]
		this->mRadius = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//update values
		mBlockSize = 4; //block size uint32 itself
		mBlockSize += sizeof(mCenter);
		mBlockSize += sizeof(mRadius);

		//begin serialization
		WriteUInt32ToBinary(outputFileStream, this->mBlockSize); //[4 BYTES]
		this->mCenter.BinarySerialize(outputFileStream); //[12 BYTES]
		WriteFloat32ToBinary(outputFileStream, this->mRadius); //[4 BYTES]
	};
};

#endif
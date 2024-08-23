#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Quaternion.h"
#include "Vector3.h"

//||||||||||||||||||||||||||||| TRANSFORM |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TRANSFORM |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TRANSFORM |||||||||||||||||||||||||||||

/// <summary>
/// [32 bytes] Defines a geometric rotation and position.
/// </summary>
struct Transform
{
	/// <summary>
	/// [4 bytes] The size of the current data structure (this value should be 32)
	/// <para>(CALCULATION) to calculate block size... </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the block size variable itself. </para>
	/// <para> Add 16, as this is the size of a Quaternion that represents the mRot variable. </para>
	/// <para> Add 12, as this is the size of a Vector3 that represents the mTrans variable. </para>
	/// </summary>
	unsigned int mBlockSize;

	/// <summary>
	/// [16 bytes] The rotation component of the transform.
	/// </summary>
	Quaternion mRot;

	/// <summary>
	/// [12 bytes] The position component of the transform.
	/// </summary>
	Vector3 mTrans;

	Transform()
	{
		this->mBlockSize = 12;
		this->mRot = {};
		this->mTrans = {};
	};

	Transform(std::ifstream* inputFileStream)
	{
		this->mBlockSize = ReadUInt32FromBinary(inputFileStream); //[4 BYTES] (value should always be 32)
		this->mRot = Quaternion(inputFileStream); //[16 BYTES]
		this->mTrans = Vector3(inputFileStream); //[12 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//update values
		mBlockSize = 4; //block size uint32 itself
		mBlockSize += sizeof(mRot);
		mBlockSize += sizeof(mTrans);

		//begin serialization
		WriteUInt32ToBinary(outputFileStream, this->mBlockSize); //[4 BYTES]
		this->mRot.BinarySerialize(outputFileStream); //[16 BYTES]
		this->mTrans.BinarySerialize(outputFileStream); //[12 BYTES]
	};
};

#endif
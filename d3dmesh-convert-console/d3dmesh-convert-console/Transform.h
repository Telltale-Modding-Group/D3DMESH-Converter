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
/// [32 BYTES] Defines a geometric rotation and position.
/// </summary>
struct Transform
{
	/// <summary>
	/// [4 BYTES] The size of the current data structure (this value should be 32)
	/// <para>(CALCULATION) to calculate block size... </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the block size variable itself. </para>
	/// <para> Add 16, as this is the size of a Quaternion that represents the mRot variable. </para>
	/// <para> Add 12, as this is the size of a Vector3 that represents the mTrans variable. </para>
	/// </summary>
	unsigned int mBlockSize;

	/// <summary>
	/// [16 BYTES] The rotation component of the transform.
	/// </summary>
	Quaternion mRot;

	/// <summary>
	/// [12 BYTES] The position component of the transform.
	/// </summary>
	Vector3 mTrans;

	Transform()
	{
		mBlockSize = 12;
		mRot = {};
		mTrans = {};
	};

	Transform(std::ifstream* inputFileStream)
	{
		mBlockSize = ReadUInt32FromBinary(inputFileStream); //[4 BYTES] (value should always be 32)
		mRot = Quaternion(inputFileStream); //[16 BYTES]
		mTrans = Vector3(inputFileStream); //[12 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//update values
		mBlockSize = 4; //block size uint32 itself
		mBlockSize += 16; //[16 BYTES] mRot
		mBlockSize += 12; //[12 BYTES] mTrans

		//begin serialization
		WriteUInt32ToBinary(outputFileStream, mBlockSize); //[4 BYTES]
		mRot.BinarySerialize(outputFileStream); //[16 BYTES]
		mTrans.BinarySerialize(outputFileStream); //[12 BYTES]
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "";
		output += "[Transform] mBlockSize:" + std::to_string(mBlockSize) + "\n";
		output += "[Transform] mRot: " + mRot.ToString() + "\n";
		output += "[Transform] mTrans: " + mTrans.ToString();
		return output;
	};

	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//NOTE: Yes I'm aware that C++ has functionality/operators for returning the size of the object, however...
	//For some of these structs/classes the size C++ returns/gets is wrong and doesn't match what telltale would expect.
	//So for saftey I will just manually calculate the byte size of the object here to what telltale expects.

	/// <summary>
	/// [32 BYTES]
	/// </summary>
	/// <returns></returns>
	unsigned int GetByteSize()
	{
		unsigned int totalByteSize = 0;
		totalByteSize += 4; //[4 BYTES] mBlockSize
		totalByteSize += mRot.GetByteSize(); //[16 BYTES] mRot
		totalByteSize += mTrans.GetByteSize(); //[12 BYTES] mTrans
		return totalByteSize;
	}
};

#endif
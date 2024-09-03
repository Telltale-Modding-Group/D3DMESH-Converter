#pragma once
#ifndef BONE_CONSTRAINTS_H
#define BONE_CONSTRAINTS_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Json.h"

#include "BoneType.h"
#include "TRangeFloat.h"

//||||||||||||||||||||||||||||| BONE CONSTRAINTS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| BONE CONSTRAINTS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| BONE CONSTRAINTS |||||||||||||||||||||||||||||

/// <summary>
/// [60 BYTES]
/// </summary>
class BoneConstraints
{
public:

	unsigned int mBlockSize_BoneContraints;
	BoneType mBoneType;
	Vector3 mHingeAxis;

	//StaticArray 3 Elements
	unsigned int mAxisRangeStaticArray_BlockSize; //28
	TRangeFloat mAxisRange0;
	TRangeFloat mAxisRange1;
	TRangeFloat mAxisRange2;

	BoneConstraints()
	{
		mBlockSize_BoneContraints = 0;
		mBoneType = BoneType::eBoneType_Hinge;
		mHingeAxis = {};
		mAxisRangeStaticArray_BlockSize = 0;
		mAxisRange0 = {};
		mAxisRange1 = {};
		mAxisRange2 = {};
	};

	BoneConstraints(std::ifstream* inputFileStream)
	{
		mBlockSize_BoneContraints = ReadUInt32FromBinary(inputFileStream);
		mBoneType = (BoneType)ReadInt32FromBinary(inputFileStream);
		mHingeAxis = Vector3(inputFileStream);

		//StaticArray 3 Elements
		mAxisRangeStaticArray_BlockSize = ReadUInt32FromBinary(inputFileStream); //28
		mAxisRange0 = TRangeFloat(inputFileStream);
		mAxisRange1 = TRangeFloat(inputFileStream);
		mAxisRange2 = TRangeFloat(inputFileStream);
	};

	void UpdateValues()
	{
		mBlockSize_BoneContraints = GetByteSize();
		mAxisRangeStaticArray_BlockSize = 4;
		mAxisRangeStaticArray_BlockSize += mAxisRange0.GetByteSize();
		mAxisRangeStaticArray_BlockSize += mAxisRange1.GetByteSize();
		mAxisRangeStaticArray_BlockSize += mAxisRange2.GetByteSize();
	}

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteUInt32ToBinary(outputFileStream, mBlockSize_BoneContraints);
		WriteUInt32ToBinary(outputFileStream, mBoneType);
		mHingeAxis.BinarySerialize(outputFileStream);
		WriteUInt32ToBinary(outputFileStream, mAxisRangeStaticArray_BlockSize);
		mAxisRange0.BinarySerialize(outputFileStream);
		mAxisRange1.BinarySerialize(outputFileStream);
		mAxisRange2.BinarySerialize(outputFileStream);
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "";
		output += "[BoneConstraints] mBlockSize_BoneContraints: " + std::to_string(mBlockSize_BoneContraints) + "\n";
		output += "[BoneConstraints] mBoneType: " + std::to_string(mBoneType) + " (" + GetBoneTypeName(mBoneType) + ") \n";
		output += "[BoneConstraints] mHingeAxis: " + mHingeAxis.ToString() + "\n";
		output += "[BoneConstraints] mAxisRangeStaticArray_BlockSize: " + std::to_string(mAxisRangeStaticArray_BlockSize) + "\n";
		output += "[BoneConstraints] mAxisRange0: " + mAxisRange0.ToString() + "\n";
		output += "[BoneConstraints] mAxisRange1: " + mAxisRange1.ToString() + "\n";
		output += "[BoneConstraints] mAxisRange2: " + mAxisRange2.ToString();
		return output;
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(BoneConstraints, 
		mBlockSize_BoneContraints, 
		mBoneType,
		mHingeAxis,
		mAxisRangeStaticArray_BlockSize,
		mAxisRange0,
		mAxisRange1,
		mAxisRange2)

	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//NOTE: Yes I'm aware that C++ has functionality/operators for returning the size of the object, however...
	//For some of these structs/classes the size C++ returns/gets is wrong and doesn't match what telltale would expect.
	//So for saftey I will just manually calculate the byte size of the object here to what telltale expects.

	/// <summary>
	/// [60 BYTES]
	/// </summary>
	/// <returns></returns>
	unsigned int GetByteSize()
	{
		unsigned int totalByteSize = 0;
		totalByteSize += 4; //[4 BYTES] mBlockSize_BoneContraints
		totalByteSize += 4; //[4 BYTES] mBoneType
		totalByteSize += mHingeAxis.GetByteSize(); //[12 BYTES] mHingeAxis
		totalByteSize += 4; //[4 BYTES] mAxisRangeStaticArray_BlockSize
		totalByteSize += mAxisRange0.GetByteSize(); //[12 BYTES] mAxisRange0
		totalByteSize += mAxisRange1.GetByteSize(); //[12 BYTES] mAxisRange1
		totalByteSize += mAxisRange2.GetByteSize(); //[12 BYTES] mAxisRange2
		return totalByteSize;
	}
};

#endif
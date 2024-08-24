#pragma once
#ifndef T3_MATERIAL_REQUIREMENTS_H
#define T3_MATERIAL_REQUIREMENTS_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Json.h"

//||||||||||||||||||||||||||||| T3 MATERIAL REQUIREMENTS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MATERIAL REQUIREMENTS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MATERIAL REQUIREMENTS |||||||||||||||||||||||||||||

/// <summary>
/// [40 BYTES]
/// </summary>
struct T3MaterialRequirements
{
	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mMaterialRequirements_BlockSize;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mPasses_BlockSize;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mPasses;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mChannels_BlockSize;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mChannels1;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mChannels2;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mInputs_BlockSize;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mInputs1;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mInputs2;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mInputs3;

	T3MaterialRequirements()
	{
		mMaterialRequirements_BlockSize = 0;
		mPasses_BlockSize = 0;
		mPasses = 0;
		mChannels_BlockSize = 0;
		mChannels1 = 0;
		mChannels2 = 0;
		mInputs_BlockSize = 0;
		mInputs1 = 0;
		mInputs2 = 0;
		mInputs3 = 0;
	};

	T3MaterialRequirements(std::ifstream* inputFileStream)
	{
		mMaterialRequirements_BlockSize = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mPasses_BlockSize = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mPasses = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mChannels_BlockSize = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mChannels1 = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mChannels2 = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mInputs_BlockSize = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mInputs1 = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mInputs2 = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mInputs3 = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//update values
		mMaterialRequirements_BlockSize = 40; //[40 BYTES] mMaterialRequirements_BlockSize
		mPasses_BlockSize = 4; //[4 BYTES] mPasses_BlockSize
		mPasses_BlockSize += 4; //[4 BYTES] mPasses
		mChannels_BlockSize = 4; //[4 BYTES] mChannels_BlockSize
		mChannels_BlockSize += 4; //[4 BYTES] mChannels1
		mChannels_BlockSize += 4; //[4 BYTES] mChannels2
		mInputs_BlockSize = 4; //[4 BYTES] mInputs_BlockSize
		mInputs_BlockSize += 4; //[4 BYTES] mInputs1
		mInputs_BlockSize += 4; //[4 BYTES] mInputs2
		mInputs_BlockSize += 4; //[4 BYTES] mInputs3

		//begin serialization
		WriteUInt32ToBinary(outputFileStream, mMaterialRequirements_BlockSize); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mPasses_BlockSize); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mPasses); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mChannels_BlockSize); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mChannels1); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mChannels2); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mInputs_BlockSize); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mInputs1); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mInputs2); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mInputs3); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "";
		output += "[T3MaterialRequirements] mMaterialRequirements_BlockSize: " + std::to_string(mMaterialRequirements_BlockSize) + "\n";
		output += "[T3MaterialRequirements] mPasses_BlockSize: " + std::to_string(mPasses_BlockSize) + "\n";
		output += "[T3MaterialRequirements] mPasses: " + std::to_string(mPasses) + "\n";
		output += "[T3MaterialRequirements] mChannels_BlockSize: " + std::to_string(mChannels_BlockSize) + "\n";
		output += "[T3MaterialRequirements] mChannels1: " + std::to_string(mChannels1) + "\n";
		output += "[T3MaterialRequirements] mChannels2: " + std::to_string(mChannels2) + "\n";
		output += "[T3MaterialRequirements] mInputs_BlockSize: " + std::to_string(mInputs_BlockSize) + "\n";
		output += "[T3MaterialRequirements] mInputs1: " + std::to_string(mInputs1) + "\n";
		output += "[T3MaterialRequirements] mInputs2: " + std::to_string(mInputs2) + "\n";
		output += "[T3MaterialRequirements] mInputs3: " + std::to_string(mInputs3);
		return output;
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE(...) //throws exceptions when there are missing values
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(
		T3MaterialRequirements, 
		mMaterialRequirements_BlockSize,
		mPasses_BlockSize,
		mPasses,
		mChannels_BlockSize,
		mChannels1,
		mChannels2,
		mInputs_BlockSize,
		mInputs1,
		mInputs2,
		mInputs3)

	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//NOTE: Yes I'm aware that C++ has functionality/operators for returning the size of the object, however...
	//For some of these structs/classes the size C++ returns/gets is wrong and doesn't match what telltale would expect.
	//So for saftey I will just manually calculate the byte size of the object here to what telltale expects.

	/// <summary>
	/// [40 BYTES]
	/// </summary>
	/// <returns></returns>
	unsigned int GetByteSize()
	{
		unsigned int totalByteSize = 0;
		totalByteSize += 4; //[4 BYTES] mMaterialRequirements_BlockSize
		totalByteSize += 4; //[4 BYTES] mPasses_BlockSize
		totalByteSize += 4; //[4 BYTES] mPasses
		totalByteSize += 4; //[4 BYTES] mChannels_BlockSize
		totalByteSize += 4; //[4 BYTES] mChannels1
		totalByteSize += 4; //[4 BYTES] mChannels2
		totalByteSize += 4; //[4 BYTES] mInputs_BlockSize
		totalByteSize += 4; //[4 BYTES] mInputs1
		totalByteSize += 4; //[4 BYTES] mInputs2
		totalByteSize += 4; //[4 BYTES] mInputs3
		return totalByteSize;
	}
};

#endif
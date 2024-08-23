#pragma once
#ifndef T3_MATERIAL_REQUIREMENTS_H
#define T3_MATERIAL_REQUIREMENTS_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"

//||||||||||||||||||||||||||||| T3 MATERIAL REQUIREMENTS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MATERIAL REQUIREMENTS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MATERIAL REQUIREMENTS |||||||||||||||||||||||||||||

/// <summary>
/// [40 BYTES]
/// </summary>
class T3MaterialRequirements
{
public:

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mMaterialRequirements_BlockSize;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mPasses_BlockSize;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mPasses;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mChannels_BlockSize;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mChannels1;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mChannels2;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mInputs_BlockSize;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mInputs1;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mInputs2;

	/// <summary>
	/// [4 bytes] 
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
		mMaterialRequirements_BlockSize = sizeof(T3MaterialRequirements);

		mPasses_BlockSize = 4;
		mPasses_BlockSize += sizeof(mPasses);

		mChannels_BlockSize = 4;
		mChannels_BlockSize += sizeof(mChannels1);
		mChannels_BlockSize += sizeof(mChannels2);

		mInputs_BlockSize = 4;
		mInputs_BlockSize += sizeof(mInputs1);
		mInputs_BlockSize += sizeof(mInputs2);
		mInputs_BlockSize += sizeof(mInputs3);

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
};

#endif
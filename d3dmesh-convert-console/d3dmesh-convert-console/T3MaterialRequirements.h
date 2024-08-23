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
		this->mMaterialRequirements_BlockSize = 0;
		this->mPasses_BlockSize = 0;
		this->mPasses = 0;
		this->mChannels_BlockSize = 0;
		this->mChannels1 = 0;
		this->mChannels2 = 0;
		this->mInputs_BlockSize = 0;
		this->mInputs1 = 0;
		this->mInputs2 = 0;
		this->mInputs3 = 0;
	};

	T3MaterialRequirements(std::ifstream* inputFileStream)
	{
		this->mMaterialRequirements_BlockSize = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mPasses_BlockSize = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mPasses = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mChannels_BlockSize = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mChannels1 = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mChannels2 = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mInputs_BlockSize = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mInputs1 = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mInputs2 = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mInputs3 = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
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
		WriteUInt32ToBinary(outputFileStream, this->mMaterialRequirements_BlockSize); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mPasses_BlockSize); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mPasses); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mChannels_BlockSize); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mChannels1); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mChannels2); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mInputs_BlockSize); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mInputs1); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mInputs2); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mInputs3); //[4 BYTES]
	};
};

#endif
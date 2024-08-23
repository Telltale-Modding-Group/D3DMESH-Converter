#pragma once
#ifndef TELLTALE_META_HEADER_VERSION_6_H
#define TELLTALE_META_HEADER_VERSION_6_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "TelltaleClassName.h"

//||||||||||||||||||||||||||||| TELLTALE META HEADER VERSION 6 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE META HEADER VERSION 6 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE META HEADER VERSION 6 |||||||||||||||||||||||||||||

/// <summary>
/// Meta Stream Version 6 (MSV6, or 6VSM), a meta header often used at the top of telltale files
/// </summary>
class TelltaleMetaHeaderVersion6
{
public:

	/// <summary>
	/// [4 bytes] The version of the meta stream version.
	/// </summary>
	std::string mMetaStreamVersion;

	/// <summary>
	/// [4 bytes] The size of the data 'header' after the meta header.
	/// </summary>
	unsigned int mDefaultSectionChunkSize;

	/// <summary>
	/// [4 bytes] The size of the debug data chunk after the meta header, which is always 0.
	/// </summary>
	unsigned int mDebugSectionChunkSize;

	/// <summary>
	/// [4 bytes] The size of the asynchronous data chunk (not the meta header, or the data chunk header, but the data itself).
	/// </summary>
	unsigned int mAsyncSectionChunkSize;

	/// <summary>
	/// [4 bytes] Amount of class name elements (CRC64 Class Names) used in the file.
	/// </summary>
	unsigned int mClassNamesLength;

	/// <summary>
	/// [12 bytes for each element] An array of class names (CRC64 Class Names) that are used in the file.
	/// </summary>
	std::vector<TelltaleClassName> mClassNames;

	TelltaleMetaHeaderVersion6()
	{
		mMetaStreamVersion = "";
		mDefaultSectionChunkSize = 0;
		mDebugSectionChunkSize = 0;
		mAsyncSectionChunkSize = 0;
		mClassNamesLength = 0;
		mClassNames = {};
	};

	TelltaleMetaHeaderVersion6(std::ifstream* inputFileStream)
	{
		mMetaStreamVersion = ReadFixedStringFromBinary(inputFileStream, 4); //[4 BYTES]
		mDefaultSectionChunkSize = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mDebugSectionChunkSize = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mAsyncSectionChunkSize = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mClassNamesLength = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]

		for (int i = 0; i < mClassNamesLength; i++)
		{
			mClassNames.push_back(TelltaleClassName(inputFileStream)); //[12 BYTES]
		}
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//update values
		mClassNamesLength = mClassNames.size();

		//begin serialization
		WriteFixedStringToBinary(outputFileStream, mMetaStreamVersion); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mDefaultSectionChunkSize); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mDebugSectionChunkSize); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mAsyncSectionChunkSize); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mClassNamesLength); //[4 BYTES]

		for (int i = 0; i < mClassNamesLength; i++)
		{
			mClassNames[i].BinarySerialize(outputFileStream); //[12 BYTES]
		}
	};
};

#endif
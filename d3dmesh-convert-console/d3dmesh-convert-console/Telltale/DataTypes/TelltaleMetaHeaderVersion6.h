#pragma once
#ifndef TELLTALE_META_HEADER_VERSION_6_H
#define TELLTALE_META_HEADER_VERSION_6_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "../../BinarySerialization.h"
#include "../../BinaryDeserialization.h"
#include "../../Json.h"
#include "../../Telltale/DataTypes/TelltaleClassName.h"

//||||||||||||||||||||||||||||| TELLTALE META HEADER VERSION 6 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE META HEADER VERSION 6 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE META HEADER VERSION 6 |||||||||||||||||||||||||||||

/// <summary>
/// [x BYTES] Meta Stream Version 6 (MSV6, or 6VSM), a meta header often used at the top of telltale files
/// </summary>
struct TelltaleMetaHeaderVersion6
{
	/// <summary>
	/// [4 BYTES] The version of the meta stream version.
	/// </summary>
	std::string mMetaStreamVersion;

	/// <summary>
	/// [4 BYTES] The size of the data 'header' after the meta header.
	/// </summary>
	unsigned int mDefaultSectionChunkSize;

	/// <summary>
	/// [4 BYTES] The size of the debug data chunk after the meta header, which is always 0.
	/// </summary>
	unsigned int mDebugSectionChunkSize;

	/// <summary>
	/// [4 BYTES] The size of the asynchronous data chunk (not the meta header, or the data chunk header, but the data itself).
	/// </summary>
	unsigned int mAsyncSectionChunkSize;

	/// <summary>
	/// [4 BYTES] Amount of class name elements (CRC64 Class Names) used in the file.
	/// </summary>
	unsigned int mClassNamesLength;

	/// <summary>
	/// [12 BYTES for each element] An array of class names (CRC64 Class Names) that are used in the file.
	/// </summary>
	std::vector<TelltaleClassName> mClassNames;

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

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

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

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

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "";
		output += "[TelltaleMetaHeaderVersion6] mMetaStreamVersion: " + mMetaStreamVersion + "\n";
		output += "[TelltaleMetaHeaderVersion6] mDefaultSectionChunkSize: " + std::to_string(mDefaultSectionChunkSize) + "\n";
		output += "[TelltaleMetaHeaderVersion6] mDebugSectionChunkSize: " + std::to_string(mDebugSectionChunkSize) + "\n";
		output += "[TelltaleMetaHeaderVersion6] mAsyncSectionChunkSize: " + std::to_string(mAsyncSectionChunkSize) + "\n";
		output += "[TelltaleMetaHeaderVersion6] mClassNamesLength: " + std::to_string(mClassNamesLength) + "\n";
		output += "[TelltaleMetaHeaderVersion6] ============ TelltaleClassName ARRAY START ============ \n";

		for (int i = 0; i < mClassNamesLength; i++)
		{
			output += "[TelltaleMetaHeaderVersion6] ============ TelltaleClassName " + std::to_string(i) + " ============ \n";
			output += mClassNames[i].ToString() + "\n";
		}

		output += "[TelltaleMetaHeaderVersion6] ============ TelltaleClassName ARRAY END ============";

		return output;
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(
		TelltaleMetaHeaderVersion6,
		mMetaStreamVersion,
		mDefaultSectionChunkSize,
		mDebugSectionChunkSize,
		mAsyncSectionChunkSize,
		mClassNamesLength,
		mClassNames)

	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//NOTE: Yes I'm aware that C++ has functionality/operators for returning the size of the object, however...
	//For some of these structs/classes the size C++ returns/gets is wrong and doesn't match what telltale would expect.
	//So for saftey I will just manually calculate the byte size of the object here to what telltale expects.

	/// <summary>
	/// [x BYTES]
	/// </summary>
	/// <returns></returns>
	unsigned int GetByteSize()
	{
		unsigned int totalByteSize = 0;
		totalByteSize += 4; //[4 BYTES] mMetaStreamVersion
		totalByteSize += 4; //[4 BYTES] mDefaultSectionChunkSize
		totalByteSize += 4; //[4 BYTES] mDebugSectionChunkSize
		totalByteSize += 4; //[4 BYTES] mAsyncSectionChunkSize
		totalByteSize += 4; //[4 BYTES] mClassNamesLength
		totalByteSize += 12 * mClassNamesLength; //[12 BYTES for each element] mClassNames
		return totalByteSize;
	}
};

#endif
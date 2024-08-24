#pragma once
#ifndef T3_GFX_BUFFER_H
#define T3_GFX_BUFFER_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "GFXPlatformFormat.h"

//||||||||||||||||||||||||||||| T3 GFX BUFFER |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 GFX BUFFER |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 GFX BUFFER |||||||||||||||||||||||||||||

/// <summary>
/// [20 BYTES] 
/// </summary>
struct T3GFXBuffer
{
	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mResourceUsage;

	/// <summary>
	/// [4 BYTES] This is an enum that defines the binary layout format of an attribute.
	/// </summary>
	GFXPlatformFormat mBufferFormat;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mBufferUsage;

	/// <summary>
	/// [4 BYTES] This indicates how many elements are in the T3GFXBuffer
	/// </summary>
	unsigned int mCount;

	/// <summary>
	/// [4 BYTES] This indicates the length of each element (in bytes) in the T3GFXBuffer
	/// </summary>
	unsigned int mStride;

	T3GFXBuffer()
	{
		mResourceUsage = 0;
		mBufferFormat = eGFXPlatformFormat_None;
		mBufferUsage = 0;
		mCount = 0;
		mStride = 0;
	};

	T3GFXBuffer(std::ifstream* inputFileStream)
	{
		mResourceUsage = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mBufferFormat = (GFXPlatformFormat)ReadInt32FromBinary(inputFileStream); //[4 BYTES]
		mBufferUsage = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mCount = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mStride = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//update values
		mStride = GetGFXPlatformFormatStrideLength(mBufferFormat);

		//begin serialization
		WriteUInt32ToBinary(outputFileStream, mResourceUsage); //[4 BYTES]
		WriteInt32ToBinary(outputFileStream, mBufferFormat); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mBufferUsage); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mCount); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mStride); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "";
		output += "[T3GFXBuffer] mResourceUsage: " + std::to_string(mResourceUsage) + "\n";
		output += "[T3GFXBuffer] mBufferFormat: " + std::to_string(mBufferFormat) + " | " + GetGFXPlatformFormatName(mBufferFormat) + "\n";
		output += "[T3GFXBuffer] mBufferUsage: " + std::to_string(mBufferUsage) + "\n";
		output += "[T3GFXBuffer] mCount: " + std::to_string(mCount) + "\n";
		output += "[T3GFXBuffer] mStride: " + std::to_string(mStride);
		return output;
	};

	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//NOTE: Yes I'm aware that C++ has functionality/operators for returning the size of the object, however...
	//For some of these structs/classes the size C++ returns/gets is wrong and doesn't match what telltale would expect.
	//So for saftey I will just manually calculate the byte size of the object here to what telltale expects.

	/// <summary>
	/// [20 BYTES]
	/// </summary>
	/// <returns></returns>
	unsigned int GetByteSize()
	{
		unsigned int totalByteSize = 0;
		totalByteSize += 4; //[4 BYTES] mResourceUsage
		totalByteSize += 4; //[4 BYTES] mBufferFormat
		totalByteSize += 4; //[4 BYTES] mBufferUsage
		totalByteSize += 4; //[4 BYTES] mCount
		totalByteSize += 4; //[4 BYTES] mStride
		return totalByteSize;
	}
};

#endif
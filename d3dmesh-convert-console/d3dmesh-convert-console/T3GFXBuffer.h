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
/// [20 bytes] 
/// </summary>
class T3GFXBuffer
{
public:

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mResourceUsage;

	/// <summary>
	/// [4 bytes] This is an enum that defines the binary layout format of an attribute.
	/// </summary>
	GFXPlatformFormat mBufferFormat;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mBufferUsage;

	/// <summary>
	/// [4 bytes] This indicates how many elements are in the T3GFXBuffer
	/// </summary>
	unsigned int mCount;

	/// <summary>
	/// [4 bytes] This indicates the length of each element (in bytes) in the T3GFXBuffer
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
};

#endif
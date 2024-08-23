#pragma once
#ifndef GFX_PLATFORM_ATTRIBUTE_PARAMS_H
#define GFX_PLATFORM_ATTRIBUTE_PARAMS_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "GFXPlatformFormat.h"
#include "GFXPlatformVertexAttribute.h"

//||||||||||||||||||||||||||||| GFX PLATFORM ATTRIBUTE PARAMS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| GFX PLATFORM ATTRIBUTE PARAMS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| GFX PLATFORM ATTRIBUTE PARAMS |||||||||||||||||||||||||||||

/// <summary>
/// [20 bytes] 
/// </summary>
class GFXPlatformAttributeParams
{
public:
	/// <summary>
	/// [4 bytes] This is an enum that indicates the mesh attribute type. (vertex position, vertex normal, vertex uv, etc)
	/// </summary>
	GFXPlatformVertexAttribute mAttribute;

	/// <summary>
	/// [4 bytes] This is an enum that defines the binary layout format of an attribute.
	/// </summary>
	GFXPlatformFormat mFormat;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mAttributeIndex;

	/// <summary>
	/// [4 bytes] This points to an element (by array index) in a T3GFXBuffer object array that this GFXPlatformAttributeParams is referencing.
	/// </summary>
	unsigned int mBufferIndex;

	/// <summary>
	/// [4 bytes] This points to the byte position in a T3GFXBuffer which is where the data for the buffer that this GFXPlatformAttributeParams is referencing starts at.
	/// </summary>
	unsigned int mBufferOffset;

	//NOTE: This was listed in the data structure in IDA, however upon additional discovery this is not actually serialized.
	//GFXPlatformVertexFrequency mFrequency;

	GFXPlatformAttributeParams()
	{
		this->mAttribute = eGFXPlatformAttribute_None;
		this->mFormat = eGFXPlatformFormat_None;
		this->mAttributeIndex = 0;
		this->mBufferIndex = 0;
		this->mBufferOffset = 0;
	};

	GFXPlatformAttributeParams(std::ifstream* inputFileStream)
	{
		this->mAttribute = (GFXPlatformVertexAttribute)ReadInt32FromBinary(inputFileStream); //GFXPlatformVertexAttribute [4 BYTES]
		this->mFormat = (GFXPlatformFormat)ReadInt32FromBinary(inputFileStream); //GFXPlatformFormat [4 BYTES]
		this->mAttributeIndex = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mBufferIndex = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mBufferOffset = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteInt32ToBinary(outputFileStream, this->mAttribute); //[4 BYTES]
		WriteInt32ToBinary(outputFileStream, this->mFormat); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mAttributeIndex); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mBufferIndex); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mBufferOffset); //[4 BYTES]
	};
};

#endif
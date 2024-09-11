#pragma once
#ifndef GFX_PLATFORM_ATTRIBUTE_PARAMS_H
#define GFX_PLATFORM_ATTRIBUTE_PARAMS_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "../../Binary/BinarySerialization.h"
#include "../../Binary/BinaryDeserialization.h"
#include "../../Helper/JsonHelper.h"
#include "../../Telltale/Enums/GFXPlatformFormat.h"
#include "../../Telltale/Enums/GFXPlatformVertexAttribute.h"

//||||||||||||||||||||||||||||| GFX PLATFORM ATTRIBUTE PARAMS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| GFX PLATFORM ATTRIBUTE PARAMS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| GFX PLATFORM ATTRIBUTE PARAMS |||||||||||||||||||||||||||||

/// <summary>
/// [20 BYTES] 
/// </summary>
struct GFXPlatformAttributeParams
{
	/// <summary>
	/// [4 BYTES] This is an enum that indicates the mesh attribute type. (vertex position, vertex normal, vertex uv, etc)
	/// </summary>
	GFXPlatformVertexAttribute mAttribute;

	/// <summary>
	/// [4 BYTES] This is an enum that defines the binary layout format of an attribute.
	/// </summary>
	GFXPlatformFormat mFormat;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mAttributeIndex;

	/// <summary>
	/// [4 BYTES] This points to an element (by array index) in a T3GFXBuffer object array that this GFXPlatformAttributeParams is referencing.
	/// </summary>
	unsigned int mBufferIndex;

	/// <summary>
	/// [4 BYTES] This points to the byte position in a T3GFXBuffer which is where the data for the buffer that this GFXPlatformAttributeParams is referencing starts at.
	/// </summary>
	unsigned int mBufferOffset;

	//NOTE: This was listed in the data structure in IDA, however upon additional discovery this is not actually serialized.
	//GFXPlatformVertexFrequency mFrequency;

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

	GFXPlatformAttributeParams()
	{
		mAttribute = GFXPlatformVertexAttribute::eGFXPlatformAttribute_None;
		mFormat = GFXPlatformFormat::eGFXPlatformFormat_None;
		mAttributeIndex = 0;
		mBufferIndex = 0;
		mBufferOffset = 0;
	};

	GFXPlatformAttributeParams(std::ifstream* inputFileStream)
	{
		mAttribute = (GFXPlatformVertexAttribute)ReadInt32FromBinary(inputFileStream); //GFXPlatformVertexAttribute [4 BYTES]
		mFormat = (GFXPlatformFormat)ReadInt32FromBinary(inputFileStream); //GFXPlatformFormat [4 BYTES]
		mAttributeIndex = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mBufferIndex = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mBufferOffset = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteInt32ToBinary(outputFileStream, mAttribute); //[4 BYTES]
		WriteInt32ToBinary(outputFileStream, mFormat); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mAttributeIndex); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mBufferIndex); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mBufferOffset); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "";
		output += "[GFXPlatformAttributeParams] mAttribute: " + std::to_string(mAttribute) + " | " + GetGFXPlatformVertexAttributeName(mAttribute) + "\n";
		output += "[GFXPlatformAttributeParams] mFormat: " + std::to_string(mFormat) + " | " + GetGFXPlatformFormatName(mFormat) + "\n";
		output += "[GFXPlatformAttributeParams] mAttributeIndex: " + std::to_string(mAttributeIndex) + "\n";
		output += "[GFXPlatformAttributeParams] mBufferIndex: " + std::to_string(mBufferIndex) + "\n";
		output += "[GFXPlatformAttributeParams] mBufferOffset: " + std::to_string(mBufferOffset);
		return output;
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(GFXPlatformAttributeParams, mAttribute, mFormat, mAttributeIndex, mBufferIndex, mBufferOffset)

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
		totalByteSize += 4; //[4 BYTES] mAttribute
		totalByteSize += 4; //[4 BYTES] mFormat
		totalByteSize += 4; //[4 BYTES] mAttributeIndex
		totalByteSize += 4; //[4 BYTES] mBufferIndex
		totalByteSize += 4; //[4 BYTES] mBufferOffset
		return totalByteSize;
	}
};

#endif
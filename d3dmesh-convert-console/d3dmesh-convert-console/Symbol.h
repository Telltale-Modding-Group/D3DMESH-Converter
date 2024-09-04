#pragma once
#ifndef SYMBOL_H
#define SYMBOL_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Json.h"

//||||||||||||||||||||||||||||| SYMBOL |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| SYMBOL |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| SYMBOL |||||||||||||||||||||||||||||

/// <summary>
/// [8 BYTES] A hashed "string" (CRC64)
/// </summary>
struct Symbol
{
	/// <summary>
	/// [8 BYTES] The hashed "string" (CRC64)
	/// </summary>
	unsigned long long mCrc64;

	Symbol()
	{
		mCrc64 = 0;
	};

	Symbol(std::ifstream* inputFileStream)
	{
		mCrc64 = ReadUInt64FromBinary(inputFileStream); //[8 BYTES]
	};

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteUInt64ToBinary(outputFileStream, mCrc64); //[8 BYTES]
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		return "[Symbol] mCrc64:" + std::to_string(mCrc64);
	};

	std::string ValueString() const
	{
		return std::to_string(mCrc64);
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Symbol, mCrc64)

	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//NOTE: Yes I'm aware that C++ has functionality/operators for returning the size of the object, however...
	//For some of these structs/classes the size C++ returns/gets is wrong and doesn't match what telltale would expect.
	//So for saftey I will just manually calculate the byte size of the object here to what telltale expects.

	/// <summary>
	/// [8 BYTES]
	/// </summary>
	/// <returns></returns>
	unsigned int GetByteSize()
	{
		unsigned int totalByteSize = 0;
		totalByteSize += 8; //[8 BYTES] mCrc64
		return totalByteSize;
	}
};

#endif
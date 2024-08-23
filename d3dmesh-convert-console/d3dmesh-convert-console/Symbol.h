#pragma once
#ifndef SYMBOL_H
#define SYMBOL_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"

//||||||||||||||||||||||||||||| SYMBOL |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| SYMBOL |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| SYMBOL |||||||||||||||||||||||||||||

/// <summary>
/// A hashed "string" (CRC64)
/// </summary>
struct Symbol
{
	/// <summary>
	/// [8 bytes] The hashed "string" (CRC64)
	/// </summary>
	unsigned long long mCrc64;

	Symbol()
	{
		this->mCrc64 = 0;
	};

	Symbol(std::ifstream* inputFileStream)
	{
		this->mCrc64 = ReadUInt64FromBinary(inputFileStream); //[8 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteUInt64ToBinary(outputFileStream, this->mCrc64); //[8 BYTES]
	};
};

#endif
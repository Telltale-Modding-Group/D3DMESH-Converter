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

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/

	void ToJson(nlohmann::json& json)
	{
		json = nlohmann::json
		{
			{ "mCrc64", mCrc64 },
		};
	}

	Symbol(const nlohmann::json& json)
	{
		mCrc64 = json.at("mCrc64").get_to(mCrc64);
	};

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
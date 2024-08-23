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

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/

	void to_json(nlohmann::json& json, const Symbol& value)
	{
		json = nlohmann::json
		{
			{ "mCrc64", value.mCrc64 },
		};
	}

	void from_json(const nlohmann::json& json, Symbol& value)
	{
		json.at("mCrc64").get_to(value.mCrc64);
	}
};

#endif
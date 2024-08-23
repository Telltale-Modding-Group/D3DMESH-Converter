#pragma once
#ifndef TELLTALE_CLASS_NAME_H
#define TELLTALE_CLASS_NAME_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Symbol.h"

//||||||||||||||||||||||||||||| TELLTALE CLASS NAME |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE CLASS NAME |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE CLASS NAME |||||||||||||||||||||||||||||

/// <summary>
/// [12 bytes] 
/// </summary>
class TelltaleClassName
{
public:

	Symbol mTypeNameCRC;

	unsigned int mVersionCRC;

	TelltaleClassName()
	{
		this->mTypeNameCRC = {};
		this->mVersionCRC = 0;
	};

	TelltaleClassName(std::ifstream* inputFileStream)
	{
		this->mTypeNameCRC = Symbol(inputFileStream); //[8 BYTES]
		this->mVersionCRC = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		mTypeNameCRC.BinarySerialize(outputFileStream); //[8 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mVersionCRC); //[4 BYTES]
	};
};

#endif
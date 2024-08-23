#pragma once
#ifndef TELLTALE_INTERNAL_RESOURCE_H
#define TELLTALE_INTERNAL_RESOURCE_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Symbol.h"

//||||||||||||||||||||||||||||| TELLTALE INTERNAL RESOURCE |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE INTERNAL RESOURCE |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE INTERNAL RESOURCE |||||||||||||||||||||||||||||

class TelltaleInternalResource
{
public:

	Symbol mInternalResourceSymbol;

	Symbol mInternalResourceType;

	unsigned int mInternalResourceBlockSize;

	char* mInternalResourceData;

	TelltaleInternalResource()
	{
		this->mInternalResourceSymbol = {};
		this->mInternalResourceType = {};
		this->mInternalResourceBlockSize = 0;
		this->mInternalResourceData = 0;
	};

	TelltaleInternalResource(std::ifstream* inputFileStream)
	{
		this->mInternalResourceSymbol = Symbol(inputFileStream);
		this->mInternalResourceType = Symbol(inputFileStream);
		this->mInternalResourceBlockSize = ReadUInt32FromBinary(inputFileStream);
		this->mInternalResourceData = ReadByteBufferFromBinary(inputFileStream, this->mInternalResourceBlockSize - 4); //skip this data block
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//begin serialization
		this->mInternalResourceSymbol.BinarySerialize(outputFileStream);
		this->mInternalResourceType.BinarySerialize(outputFileStream);
		WriteUInt32ToBinary(outputFileStream, this->mInternalResourceBlockSize);
		WriteByteBufferToBinary(outputFileStream, this->mInternalResourceBlockSize - 4, this->mInternalResourceData);
	};
};

#endif
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
		mInternalResourceSymbol = {};
		mInternalResourceType = {};
		mInternalResourceBlockSize = 0;
		mInternalResourceData = 0;
	};

	TelltaleInternalResource(std::ifstream* inputFileStream)
	{
		mInternalResourceSymbol = Symbol(inputFileStream);
		mInternalResourceType = Symbol(inputFileStream);
		mInternalResourceBlockSize = ReadUInt32FromBinary(inputFileStream);
		mInternalResourceData = ReadByteBufferFromBinary(inputFileStream, mInternalResourceBlockSize - 4); //skip this data block
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//begin serialization
		mInternalResourceSymbol.BinarySerialize(outputFileStream);
		mInternalResourceType.BinarySerialize(outputFileStream);
		WriteUInt32ToBinary(outputFileStream, mInternalResourceBlockSize);
		WriteByteBufferToBinary(outputFileStream, mInternalResourceBlockSize - 4, mInternalResourceData);
	};
};

#endif
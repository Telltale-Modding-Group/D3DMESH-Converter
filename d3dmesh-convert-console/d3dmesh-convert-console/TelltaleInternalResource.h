#pragma once
#ifndef TELLTALE_INTERNAL_RESOURCE_H
#define TELLTALE_INTERNAL_RESOURCE_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Json.h"
#include "Symbol.h"

//||||||||||||||||||||||||||||| TELLTALE INTERNAL RESOURCE |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE INTERNAL RESOURCE |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE INTERNAL RESOURCE |||||||||||||||||||||||||||||

/// <summary>
/// [x BYTES]
/// </summary>
struct TelltaleInternalResource
{
	/// <summary>
	/// [8 BYTES]
	/// </summary>
	Symbol mInternalResourceSymbol;

	/// <summary>
	/// [8 BYTES]
	/// </summary>
	Symbol mInternalResourceType;

	/// <summary>
	/// [4 BYTES]
	/// </summary>
	unsigned int mInternalResourceBlockSize;

	/// <summary>
	/// [x BYTES]
	/// </summary>
	//char* mInternalResourceData;
	std::vector<char> mInternalResourceData;

	TelltaleInternalResource()
	{
		mInternalResourceSymbol = {};
		mInternalResourceType = {};
		mInternalResourceBlockSize = 0;
		//mInternalResourceData = 0;
		mInternalResourceData = {};
	};

	TelltaleInternalResource(std::ifstream* inputFileStream)
	{
		mInternalResourceSymbol = Symbol(inputFileStream);
		mInternalResourceType = Symbol(inputFileStream);
		mInternalResourceBlockSize = ReadUInt32FromBinary(inputFileStream);
		//mInternalResourceData = ReadByteBufferFromBinary(inputFileStream, mInternalResourceBlockSize - 4); //skip this data block
		mInternalResourceData = ReadByteVectorBufferFromBinary(inputFileStream, mInternalResourceBlockSize - 4); //skip this data block
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//begin serialization
		mInternalResourceSymbol.BinarySerialize(outputFileStream);
		mInternalResourceType.BinarySerialize(outputFileStream);
		WriteUInt32ToBinary(outputFileStream, mInternalResourceBlockSize);
		//WriteByteBufferToBinary(outputFileStream, mInternalResourceBlockSize - 4, mInternalResourceData);
		WriteByteVectorBufferToBinary(outputFileStream, mInternalResourceData);
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "";
		output += "[TelltaleInternalResource] mInternalResourceSymbol: " + mInternalResourceSymbol.ToString() + "\n";
		output += "[TelltaleInternalResource] mInternalResourceType: " + mInternalResourceType.ToString() + "\n";
		output += "[TelltaleInternalResource] mInternalResourceBlockSize: " + std::to_string(mInternalResourceBlockSize) + "\n";
		output += "[TelltaleInternalResource] mInternalResourceData [" + std::to_string(mInternalResourceBlockSize - 4) + "BYTES]";
		return output;
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE(...) //throws exceptions when there are missing values
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(
		TelltaleInternalResource, 
		mInternalResourceSymbol, 
		mInternalResourceType, 
		mInternalResourceBlockSize,
		mInternalResourceData)

	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//NOTE: Yes I'm aware that C++ has functionality/operators for returning the size of the object, however...
	//For some of these structs/classes the size C++ returns/gets is wrong and doesn't match what telltale would expect.
	//So for saftey I will just manually calculate the byte size of the object here to what telltale expects.

	/// <summary>
	/// [x BYTES]
	/// </summary>
	/// <returns></returns>
	unsigned int GetByteSize()
	{
		unsigned int totalByteSize = 0;
		totalByteSize += mInternalResourceSymbol.GetByteSize(); //[8 BYTES] mInternalResourceSymbol
		totalByteSize += mInternalResourceType.GetByteSize(); //[8 BYTES] mInternalResourceType
		totalByteSize += 4; //[4 BYTES] mInternalResourceBlockSize
		totalByteSize += mInternalResourceBlockSize - 4; //[x BYTES] mInternalResourceData
		return totalByteSize;
	}
};

#endif
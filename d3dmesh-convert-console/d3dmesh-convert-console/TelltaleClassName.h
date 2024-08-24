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
/// [12 BYTES] 
/// </summary>
struct TelltaleClassName
{
	/// <summary>
	/// [8 BYTES]
	/// </summary>
	Symbol mTypeNameCRC;

	/// <summary>
	/// [4 BYTES]
	/// </summary>
	unsigned int mVersionCRC;

	TelltaleClassName()
	{
		mTypeNameCRC = {};
		mVersionCRC = 0;
	};

	TelltaleClassName(std::ifstream* inputFileStream)
	{
		mTypeNameCRC = Symbol(inputFileStream); //[8 BYTES]
		mVersionCRC = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		mTypeNameCRC.BinarySerialize(outputFileStream); //[8 BYTES]
		WriteUInt32ToBinary(outputFileStream, mVersionCRC); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "";
		output += "[TelltaleClassName] mTypeNameCRC: " + mTypeNameCRC.ToString() + "\n";
		output += "[TelltaleClassName] mVersionCRC: " + std::to_string(mVersionCRC);
		return output;
	};

	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//NOTE: Yes I'm aware that C++ has functionality/operators for returning the size of the object, however...
	//For some of these structs/classes the size C++ returns/gets is wrong and doesn't match what telltale would expect.
	//So for saftey I will just manually calculate the byte size of the object here to what telltale expects.

	/// <summary>
	/// [12 BYTES]
	/// </summary>
	/// <returns></returns>
	unsigned int GetByteSize()
	{
		unsigned int totalByteSize = 0;
		totalByteSize += mTypeNameCRC.GetByteSize(); //[8 BYTES] mTypeNameCRC
		totalByteSize += 4; //[4 BYTES] mVersionCRC
		return totalByteSize;
	}
};

#endif
#pragma once
#ifndef HANDLE_PROPERTY_SET_H
#define HANDLE_PROPERTY_SET_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "../../Binary/BinarySerialization.h"
#include "../../Binary/BinaryDeserialization.h"
#include "../../Helper/JsonHelper.h"
#include "../../Telltale/DataTypes/Symbol.h"

//||||||||||||||||||||||||||||| HANDLE PROPERTY SET |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| HANDLE PROPERTY SET |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| HANDLE PROPERTY SET |||||||||||||||||||||||||||||

/// <summary>
/// [12 BYTES]
/// </summary>
struct HandlePropertySet
{
	/// <summary>
	/// [4 BYTES]
	/// </summary>
	unsigned int mhMaterial_BlockSize;

	/// <summary>
	/// [8 BYTES]
	/// </summary>
	Symbol mhMaterial;

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

	HandlePropertySet()
	{
		mhMaterial_BlockSize = 12;
		mhMaterial = {};
	};

	HandlePropertySet(std::ifstream* inputFileStream)
	{
		mhMaterial_BlockSize = ReadUInt32FromBinary(inputFileStream);
		mhMaterial = Symbol(inputFileStream);
	};

	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//NOTE: This is critical as any mishap in regards to new/removed data will crash the game.
	//So in advance we need to update all structural values (block sizes, array lengths, array capacities) to make sure everything lines up.

	void UpdateStructure()
	{
		mhMaterial_BlockSize = GetByteSize();
	}

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteUInt32ToBinary(outputFileStream, mhMaterial_BlockSize);
		mhMaterial.BinarySerialize(outputFileStream);
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "\n";
		output += "[HandlePropertySet] mBlockSize: " + std::to_string(mhMaterial_BlockSize) + "\n";
		output += "[HandlePropertySet] mhMaterial: " + mhMaterial.ToString();
		return output;
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(HandlePropertySet,
		mhMaterial_BlockSize,
		mhMaterial)

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
		totalByteSize += 4; //mhMaterial_BlockSize [4 BYTES]
		totalByteSize += mhMaterial.GetByteSize(); //mhMaterial [8 BYTES]
		return totalByteSize;
	}
};

#endif
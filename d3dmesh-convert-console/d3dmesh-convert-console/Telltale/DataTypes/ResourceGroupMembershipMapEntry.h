#pragma once
#ifndef RESOURCE_GROUP_MEMBERSHIP_MAP_ENTRY_H
#define RESOURCE_GROUP_MEMBERSHIP_MAP_ENTRY_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "../../Binary/BinarySerialization.h"
#include "../../Binary/BinaryDeserialization.h"
#include "../../Helper/JsonHelper.h"
#include "../../Telltale/DataTypes/Symbol.h"

//||||||||||||||||||||||||||||| RESOURCE GROUP MEMBERSHIP MAP ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| RESOURCE GROUP MEMBERSHIP MAP ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| RESOURCE GROUP MEMBERSHIP MAP ENTRY |||||||||||||||||||||||||||||

/// <summary>
/// [12 BYTES]
/// </summary>
struct ResourceGroupMembershipMapEntry
{
	/// <summary>
	/// [8 BYTES]
	/// </summary>
	Symbol mSymbol;

	/// <summary>
	/// [4 BYTES]
	/// </summary>
	float mFloat;

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

	ResourceGroupMembershipMapEntry()
	{
		mSymbol = {};
		mFloat = 0.0f;
	};

	ResourceGroupMembershipMapEntry(std::ifstream* inputFileStream)
	{
		mSymbol = Symbol(inputFileStream);
		mFloat = ReadFloat32FromBinary(inputFileStream);
	};

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		mSymbol.BinarySerialize(outputFileStream);
		WriteFloat32ToBinary(outputFileStream, mFloat);
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		return "[ResourceGroupMembershipMapEntry] mSymbol:" + mSymbol.ToString() + " mFloat: " + std::to_string(mFloat);
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(ResourceGroupMembershipMapEntry, mSymbol, mFloat)

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
		totalByteSize += mSymbol.GetByteSize(); //[8 BYTES] mSymbol
		totalByteSize += 4; //[4 BYTES] mFloat
		return totalByteSize;
	}
};

#endif
#pragma once
#ifndef SKELETON_H
#define SKELETON_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "../../BinarySerialization.h"
#include "../../BinaryDeserialization.h"
#include "../../Json.h"
#include "../../Telltale/DataTypes/SkeletonEntry.h"

//||||||||||||||||||||||||||||| SKELETON |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| SKELETON |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| SKELETON |||||||||||||||||||||||||||||

struct Skeleton
{
	/// <summary>
	/// [4 BYTES]
	/// </summary>
	unsigned int mBlockSize;

	/// <summary>
	/// [4 BYTES]
	/// </summary>
	unsigned int mEntryCount;

	/// <summary>
	/// [x BYTES]
	/// </summary>
	std::vector<SkeletonEntry> mEntries;

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

	Skeleton()
	{
		mBlockSize = 0;
		mEntryCount = 0;
		mEntries = {};
	};

	Skeleton(std::ifstream* inputFileStream)
	{
		mBlockSize = ReadUInt32FromBinary(inputFileStream);
		mEntryCount = ReadUInt32FromBinary(inputFileStream);

		for (int i = 0; i < mEntryCount; i++)
			mEntries.push_back(SkeletonEntry(inputFileStream));
	};

	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//NOTE: This is critical as any mishap in regards to new/removed data will crash the game.
	//So in advance we need to update all structural values (block sizes, array lengths, array capacities) to make sure everything lines up.

	void UpdateStructures()
	{
		mBlockSize = GetByteSize();
		mEntryCount = mEntries.size();

		for (int i = 0; i < mEntryCount; i++)
			mEntries[i].UpdateStructures();
	}

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteUInt32ToBinary(outputFileStream, mBlockSize);
		WriteUInt32ToBinary(outputFileStream, mEntryCount);

		for (int i = 0; i < mEntryCount; i++)
			mEntries[i].BinarySerialize(outputFileStream);
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "";
		output += "[Skeleton] mBlockSize: " + std::to_string(mBlockSize) + "\n";
		output += "[Skeleton] mEntryCount: " + std::to_string(mEntryCount) + "\n";
		output += "[Skeleton] ============ SkeletonEntry ARRAY START ============ \n";

		for (int i = 0; i < mEntryCount; i++)
			output += mEntries[i].ToString() + "\n";

		output += "[Skeleton] ============ SkeletonEntry ARRAY END ============";

		return output;
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Skeleton, mBlockSize, mEntryCount, mEntries)

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
		totalByteSize += 4; //[4 BYTES] mBlockSize
		totalByteSize += 4; //[4 BYTES] mEntryCount

		for (int i = 0; i < mEntryCount; i++)
			totalByteSize += mEntries[i].GetByteSize(); //[x BYTES]

		return totalByteSize;
	}
};

#endif
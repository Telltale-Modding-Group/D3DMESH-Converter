#pragma once
#ifndef T3_MESH_EFFECT_PRELOAD_H
#define T3_MESH_EFFECT_PRELOAD_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "../../Binary/BinarySerialization.h"
#include "../../Binary/BinaryDeserialization.h"
#include "../../Helper/JsonHelper.h"
#include "../../Telltale/DataTypes/T3MeshEffectPreloadEntry.h"

//||||||||||||||||||||||||||||| T3 MESH EFFECT PRELOAD |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH EFFECT PRELOAD |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH EFFECT PRELOAD |||||||||||||||||||||||||||||

/// <summary>
/// [x BYTES] 
/// </summary>
struct T3MeshEffectPreload
{
	unsigned int mEffectQuality;
	unsigned int mEntries_ArrayCapacity;
	unsigned int mEntries_ArrayLength;
	std::vector<T3MeshEffectPreloadEntry> mEntries;
	unsigned int mTotalEffectCount;

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

	T3MeshEffectPreload()
	{
		mEffectQuality = 0;
		mEntries_ArrayCapacity = 0;
		mEntries_ArrayLength = 0;
		mEntries = {};
		mTotalEffectCount = 0;
	};

	T3MeshEffectPreload(std::ifstream* inputFileStream)
	{
		mEffectQuality = ReadUInt32FromBinary(inputFileStream);
		mEntries_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		mEntries_ArrayLength = ReadUInt32FromBinary(inputFileStream);
		
		for (int i = 0; i < mEntries_ArrayLength; i++)
			mEntries.push_back(T3MeshEffectPreloadEntry(inputFileStream));

		mTotalEffectCount = ReadUInt32FromBinary(inputFileStream);
	};

	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//NOTE: This is critical as any mishap in regards to new/removed data will crash the game.
	//So in advance we need to update all structural values (block sizes, array lengths, array capacities) to make sure everything lines up.

	void UpdateStructures()
	{
		mEntries_ArrayLength = mEntries.size();
		mEntries_ArrayCapacity = 8;
		mTotalEffectCount = 0;

		for (int i = 0; i < mEntries_ArrayLength; i++)
		{
			mEntries[i].UpdateStructures();
			mEntries_ArrayCapacity += mEntries[i].GetByteSize();
			mTotalEffectCount += mEntries[i].mDynamicEffectFeatures_ArrayLength;
		}
	}

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteUInt32ToBinary(outputFileStream, mEffectQuality);
		WriteUInt32ToBinary(outputFileStream, mEntries_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, mEntries_ArrayLength);

		for (int i = 0; i < mEntries_ArrayLength; i++)
			mEntries[i].BinarySerialize(outputFileStream);

		WriteUInt32ToBinary(outputFileStream, mTotalEffectCount);
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "";
		output += "[T3MeshEffectPreload] mEffectQuality: " + std::to_string(mEffectQuality) + "\n";
		output += "[T3MeshEffectPreload] mEntries_ArrayCapacity: " + std::to_string(mEntries_ArrayCapacity) + "\n";
		output += "[T3MeshEffectPreload] mEntries_ArrayLength: " + std::to_string(mEntries_ArrayLength) + "\n";
		output += "[T3MeshEffectPreload] ============ mEntries ARRAY START ============ \n";

		for (int i = 0; i < mEntries_ArrayLength; i++)
			output += mEntries[i].ToString() + "\n";

		output += "[T3MeshEffectPreload] ============ mEntries ARRAY END ============ \n";
		output += "[T3MeshEffectPreload] mTotalEffectCount: " + std::to_string(mTotalEffectCount);
		return output;
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(T3MeshEffectPreload, 
		mEffectQuality,
		mEntries_ArrayCapacity,
		mEntries_ArrayLength,
		mEntries,
		mTotalEffectCount)

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
		totalByteSize += 4; //[4 BYTES] mEffectQuality
		totalByteSize += 4; //[4 BYTES] mEntries_ArrayCapacity
		totalByteSize += 4; //[4 BYTES] mEntries_ArrayLength

		for (int i = 0; i < mEntries_ArrayLength; i++) //mEntries
			totalByteSize += mEntries[i].GetByteSize();

		totalByteSize += 4; //[4 BYTES] mTotalEffectCount
		return totalByteSize;
	}
};

#endif
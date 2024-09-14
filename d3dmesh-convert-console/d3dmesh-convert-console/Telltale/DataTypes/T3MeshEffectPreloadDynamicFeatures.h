#pragma once
#ifndef T3_MESH_EFFECT_PRELOAD_DYNAMIC_FEATURES_H
#define T3_MESH_EFFECT_PRELOAD_DYNAMIC_FEATURES_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "../../Binary/BinarySerialization.h"
#include "../../Binary/BinaryDeserialization.h"
#include "../../Helper/JsonHelper.h"

//||||||||||||||||||||||||||||| T3 MESH EFFECT PRELOAD DYNAMIC FEATURES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH EFFECT PRELOAD DYNAMIC FEATURES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH EFFECT PRELOAD DYNAMIC FEATURES |||||||||||||||||||||||||||||

/// <summary>
/// [x BYTES] 
/// </summary>
struct T3MeshEffectPreloadDynamicFeatures
{
	unsigned int mBlockSize;
	unsigned int mDynamicFeatures; //BitSetBase<1> mDynamicFeatures;
	unsigned int mPriority;

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

	T3MeshEffectPreloadDynamicFeatures()
	{
		mBlockSize = 0;
		mDynamicFeatures = 0;
		mPriority = 0;
	};

	T3MeshEffectPreloadDynamicFeatures(std::ifstream* inputFileStream)
	{
		mBlockSize = ReadUInt32FromBinary(inputFileStream);
		mDynamicFeatures = ReadUInt32FromBinary(inputFileStream);
		mPriority = ReadUInt32FromBinary(inputFileStream);
	};

	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//NOTE: This is critical as any mishap in regards to new/removed data will crash the game.
	//So in advance we need to update all structural values (block sizes, array lengths, array capacities) to make sure everything lines up.

	void UpdateStructures()
	{
		mBlockSize = 4; //[4 BYTES] mDynamicFeatures
		mBlockSize += 4; //[4 BYTES] mPriority
	}

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteUInt32ToBinary(outputFileStream, mBlockSize);
		WriteUInt32ToBinary(outputFileStream, mDynamicFeatures);
		WriteUInt32ToBinary(outputFileStream, mPriority);
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "";
		output += "[T3MeshEffectPreloadDynamicFeatures] mBlockSize: " + std::to_string(mBlockSize) + "\n";
		output += "[T3MeshEffectPreloadDynamicFeatures] mDynamicFeatures: " + std::to_string(mDynamicFeatures) + "\n";
		output += "[T3MeshEffectPreloadDynamicFeatures] mPriority: " + std::to_string(mPriority);
		return output;
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(T3MeshEffectPreloadDynamicFeatures, mBlockSize, mDynamicFeatures, mPriority)

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
		totalByteSize += 4; //[4 BYTES] mBlockSize
		totalByteSize += 4; //[4 BYTES] mDynamicFeatures
		totalByteSize += 4; //[4 BYTES] mPriority
		return totalByteSize;
	}
};

#endif
#pragma once
#ifndef T3_MESH_EFFECT_PRELOAD_ENTRY_H
#define T3_MESH_EFFECT_PRELOAD_ENTRY_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "../../Binary/BinarySerialization.h"
#include "../../Binary/BinaryDeserialization.h"
#include "../../Helper/JsonHelper.h"
#include "../../Telltale/DataTypes/Symbol.h"
#include "../../Telltale/DataTypes/T3MeshEffectPreloadDynamicFeatures.h"
#include "../../Telltale/Enums/T3EffectType.h"

//||||||||||||||||||||||||||||| T3 MESH EFFECT PRELOAD ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH EFFECT PRELOAD ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH EFFECT PRELOAD ENTRY |||||||||||||||||||||||||||||

/// <summary>
/// [x BYTES] 
/// </summary>
struct T3MeshEffectPreloadEntry
{
	T3EffectType mEffectType;
	unsigned int mStaticEffectFeatures_BlockSize;
	unsigned int mStaticEffectFeatures_1;
	unsigned int mStaticEffectFeatures_2;
	unsigned int mStaticEffectFeatures_3;
	Symbol mMaterialCRC;
	unsigned int mDynamicEffectFeatures_ArrayCapacity;
	unsigned int mDynamicEffectFeatures_ArrayLength;
	std::vector<T3MeshEffectPreloadDynamicFeatures> mDynamicEffectFeatures;

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

	T3MeshEffectPreloadEntry()
	{
		mEffectType = T3EffectType::eEffect_Mesh;
		mStaticEffectFeatures_BlockSize = 16;
		mStaticEffectFeatures_1 = 0;
		mStaticEffectFeatures_2 = 0;
		mStaticEffectFeatures_3 = 0;
		mMaterialCRC = {};
		mDynamicEffectFeatures_ArrayCapacity = 8;
		mDynamicEffectFeatures_ArrayLength = 0;
		mDynamicEffectFeatures = {};
	};

	T3MeshEffectPreloadEntry(std::ifstream* inputFileStream)
	{
		mEffectType = (T3EffectType)ReadInt32FromBinary(inputFileStream);
		mStaticEffectFeatures_BlockSize = ReadUInt32FromBinary(inputFileStream);
		mStaticEffectFeatures_1 = ReadUInt32FromBinary(inputFileStream);
		mStaticEffectFeatures_2 = ReadUInt32FromBinary(inputFileStream);
		mStaticEffectFeatures_3 = ReadUInt32FromBinary(inputFileStream);
		mMaterialCRC = Symbol(inputFileStream);
		mDynamicEffectFeatures_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		mDynamicEffectFeatures_ArrayLength = ReadUInt32FromBinary(inputFileStream);

		for (int i = 0; i < mDynamicEffectFeatures_ArrayLength; i++)
			mDynamicEffectFeatures.push_back(T3MeshEffectPreloadDynamicFeatures(inputFileStream));
	};

	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//NOTE: This is critical as any mishap in regards to new/removed data will crash the game.
	//So in advance we need to update all structural values (block sizes, array lengths, array capacities) to make sure everything lines up.

	void UpdateStructures()
	{
		mStaticEffectFeatures_BlockSize = 4; //[4 BYTES] mStaticEffectFeatures_BlockSize
		mStaticEffectFeatures_BlockSize += 4; //[4 BYTES] mStaticEffectFeatures_1
		mStaticEffectFeatures_BlockSize += 4; //[4 BYTES] mStaticEffectFeatures_2
		mStaticEffectFeatures_BlockSize += 4; //[4 BYTES] mStaticEffectFeatures_3

		mDynamicEffectFeatures_ArrayLength = mDynamicEffectFeatures.size();
		mDynamicEffectFeatures_ArrayCapacity = 8;

		for (int i = 0; i < mDynamicEffectFeatures_ArrayLength; i++)
		{
			mDynamicEffectFeatures[i].UpdateStructures();
			mDynamicEffectFeatures_ArrayCapacity += mDynamicEffectFeatures[i].GetByteSize();
		}
	}

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteInt32ToBinary(outputFileStream, mEffectType);
		WriteUInt32ToBinary(outputFileStream, mStaticEffectFeatures_BlockSize);
		WriteUInt32ToBinary(outputFileStream, mStaticEffectFeatures_1);
		WriteUInt32ToBinary(outputFileStream, mStaticEffectFeatures_2);
		WriteUInt32ToBinary(outputFileStream, mStaticEffectFeatures_3);
		mMaterialCRC.BinarySerialize(outputFileStream);
		WriteUInt32ToBinary(outputFileStream, mDynamicEffectFeatures_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, mDynamicEffectFeatures_ArrayLength);

		for (int i = 0; i < mDynamicEffectFeatures_ArrayLength; i++)
			mDynamicEffectFeatures[i].BinarySerialize(outputFileStream);
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "";
		output += "[T3MeshEffectPreloadEntry] mEffectType: " + std::to_string(mEffectType) + " (" + GetT3EffectTypeName(mEffectType) + ") \n";
		output += "[T3MeshEffectPreloadEntry] mStaticEffectFeatures_BlockSize: " + std::to_string(mStaticEffectFeatures_BlockSize) + "\n";
		output += "[T3MeshEffectPreloadEntry] mStaticEffectFeatures_1: " + std::to_string(mStaticEffectFeatures_1) + "\n";
		output += "[T3MeshEffectPreloadEntry] mStaticEffectFeatures_2: " + std::to_string(mStaticEffectFeatures_2) + "\n";
		output += "[T3MeshEffectPreloadEntry] mStaticEffectFeatures_3: " + std::to_string(mStaticEffectFeatures_3) + "\n";
		output += "[T3MeshEffectPreloadEntry] mMaterialCRC: " + mMaterialCRC.ToString() + "\n";
		output += "[T3MeshEffectPreloadEntry] mDynamicEffectFeatures_ArrayCapacity: " + std::to_string(mDynamicEffectFeatures_ArrayCapacity) + "\n";
		output += "[T3MeshEffectPreloadEntry] mDynamicEffectFeatures_ArrayLength: " + std::to_string(mDynamicEffectFeatures_ArrayLength) + "\n";
		output += "[T3MeshEffectPreloadEntry] ============ mDynamicEffectFeatures ARRAY START ============ \n";

		for (int i = 0; i < mDynamicEffectFeatures_ArrayLength; i++)
			output += mDynamicEffectFeatures[i].ToString() + "\n";

		output += "[T3MeshEffectPreloadEntry] ============ mDynamicEffectFeatures ARRAY END ============";
		return output;
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(T3MeshEffectPreloadEntry, 
		mEffectType,
		mStaticEffectFeatures_BlockSize,
		mStaticEffectFeatures_1,
		mStaticEffectFeatures_2,
		mStaticEffectFeatures_3,
		mMaterialCRC,
		mDynamicEffectFeatures_ArrayCapacity,
		mDynamicEffectFeatures_ArrayLength,
		mDynamicEffectFeatures)

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
		totalByteSize += 4; //[4 BYTES] mEffectType
		totalByteSize += 4; //[4 BYTES] mStaticEffectFeatures_BlockSize
		totalByteSize += 4; //[4 BYTES] mStaticEffectFeatures_1
		totalByteSize += 4; //[4 BYTES] mStaticEffectFeatures_2
		totalByteSize += 4; //[4 BYTES] mStaticEffectFeatures_3
		totalByteSize += mMaterialCRC.GetByteSize(); //[8 BYTES] mMaterialCRC
		totalByteSize += 4; //[4 BYTES] mDynamicEffectFeatures_ArrayCapacity
		totalByteSize += 4; //[4 BYTES] mDynamicEffectFeatures_ArrayLength

		for (int i = 0; i < mDynamicEffectFeatures_ArrayLength; i++) //mDynamicEffectFeatures
			totalByteSize += mDynamicEffectFeatures[i].GetByteSize();

		return totalByteSize;
	}
};

#endif
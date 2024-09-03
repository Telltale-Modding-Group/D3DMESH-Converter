#pragma once
#ifndef T3_MESH_BONE_ENTRY_H
#define T3_MESH_BONE_ENTRY_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Json.h"
#include "Symbol.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"

//||||||||||||||||||||||||||||| T3 MESH BONE ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH BONE ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH BONE ENTRY |||||||||||||||||||||||||||||

/// <summary>
/// [56 BYTES]
/// </summary>
struct T3MeshBoneEntry
{
	/// <summary>
	/// [8 BYTES]
	/// </summary>
	Symbol mBoneName;

	/// <summary>
	/// [24 BYTES] 
	/// </summary>
	BoundingBox mBoundingBox;

	/// <summary>
	/// [20 BYTES] 
	/// </summary>
	BoundingSphere mBoundingSphere;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mNumVerts;

	T3MeshBoneEntry() 
	{
		mBoneName = {};
		mBoundingBox = {};
		mBoundingSphere = {};
		mNumVerts = 0;
	};

	T3MeshBoneEntry(std::ifstream* inputFileStream) 
	{
		mBoneName = Symbol(inputFileStream); //[8 BYTES]
		mBoundingBox = BoundingBox(inputFileStream); //[24 BYTES]
		mBoundingSphere = BoundingSphere(inputFileStream); //[20 BYTES]
		mNumVerts = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		mBoneName.BinarySerialize(outputFileStream); //[8 BYTES]
		mBoundingBox.BinarySerialize(outputFileStream); //[24 BYTES]
		mBoundingSphere.BinarySerialize(outputFileStream); //[20 BYTES]
		WriteUInt32ToBinary(outputFileStream, mNumVerts); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "";
		output += "[T3MeshBoneEntry] mBoneName: " + mBoneName.ToString() + "\n";
		output += "[T3MeshBoneEntry] mBoundingBox: " + mBoundingBox.ToString() + "\n";
		output += "[T3MeshBoneEntry] mBoundingSphere: " + mBoundingSphere.ToString() + "\n";
		output += "[T3MeshBoneEntry] mNumVerts: " + std::to_string(mNumVerts);
		return output;
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(T3MeshBoneEntry, mBoneName, mBoundingBox, mBoundingSphere, mNumVerts)

	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//NOTE: Yes I'm aware that C++ has functionality/operators for returning the size of the object, however...
	//For some of these structs/classes the size C++ returns/gets is wrong and doesn't match what telltale would expect.
	//So for saftey I will just manually calculate the byte size of the object here to what telltale expects.

	/// <summary>
	/// [56 BYTES]
	/// </summary>
	/// <returns></returns>
	unsigned int GetByteSize()
	{
		unsigned int totalByteSize = 0;
		totalByteSize += mBoneName.GetByteSize(); //[8 BYTES] mBoneName
		totalByteSize += mBoundingBox.GetByteSize(); //[24 BYTES] mBoundingBox
		totalByteSize += mBoundingSphere.GetByteSize(); //[20 BYTES] mBoundingSphere
		totalByteSize += 4; //[4 BYTES] mNumVerts
		return totalByteSize;
	}
};

#endif
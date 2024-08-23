#pragma once
#ifndef T3_MESH_BONE_ENTRY_H
#define T3_MESH_BONE_ENTRY_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Symbol.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"

//||||||||||||||||||||||||||||| T3 MESH BONE ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH BONE ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH BONE ENTRY |||||||||||||||||||||||||||||

/// <summary>
/// [56 BYTES]
/// </summary>
class T3MeshBoneEntry
{
public:

	Symbol mBoneName;

	BoundingBox mBoundingBox;

	BoundingSphere mBoundingSphere;

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

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		mBoneName.BinarySerialize(outputFileStream); //[8 BYTES]
		mBoundingBox.BinarySerialize(outputFileStream); //[24 BYTES]
		mBoundingSphere.BinarySerialize(outputFileStream); //[20 BYTES]
		WriteUInt32ToBinary(outputFileStream, mNumVerts); //[4 BYTES]
	};
};

#endif
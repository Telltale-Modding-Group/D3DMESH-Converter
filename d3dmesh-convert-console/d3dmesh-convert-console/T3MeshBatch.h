#pragma once
#ifndef T3_MESH_BATCH_H
#define T3_MESH_BATCH_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"

//||||||||||||||||||||||||||||| T3 MESH BATCH |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH BATCH |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH BATCH |||||||||||||||||||||||||||||

/// <summary>
/// [88 bytes] This is a part of a mesh.
/// </summary>
class T3MeshBatch
{
public:

	/// <summary>
	/// [24 bytes] The bounding box defined for the mesh.
	/// </summary>
	BoundingBox mBoundingBox;

	/// <summary>
	/// [20 bytes] The bounding sphere defined for the mesh.
	/// </summary>
	BoundingSphere mBoundingSphere;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mBatchUsage_BlockSize;

	/// <summary>
	/// [4 bytes] mFlags
	/// </summary>
	unsigned int mBatchUsage;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mMinVertIndex;

	/// <summary>
	/// [4 bytes] (Seems to always be 0?)
	/// </summary>
	unsigned int mMaxVertIndex;

	/// <summary>
	/// [4 bytes] 
	/// <para> This starts at 0, but progressively towards the end with more batch elements, this gets incremented by mNumPrimitives. </para>
	/// <para> NOTE: This seems to be related with the index buffer. </para>
	/// </summary>
	unsigned int mBaseIndex;

	/// <summary>
	/// [4 bytes] 
	/// <para> NOTE 1: This seems to be related with the index buffer. </para>
	/// <para> NOTE 2: error.mdl noted that this aligns with (mNumPrimitives / 3). </para>
	/// </summary>
	unsigned int mStartIndex;

	/// <summary>
	/// [4 bytes] The number of triangles in the batch mesh.
	/// <para> NOTE 2: this seems to be (mStartIndex * 3). </para>
	/// </summary>
	unsigned int mNumPrimitives;

	/// <summary>
	/// [4 bytes] (Seems to always be 8?)
	/// <para> NOTE 1: error.mdl noted that this might actually be a flag field. Where 8 is 1<<3, triangles = 3 triangles </para>
	/// </summary>
	unsigned int mNumIndices;

	/// <summary>
	/// [4 bytes] Unsure what this is for... but it's value seems to always be 4294967295
	/// </summary>
	unsigned int mTextureIndices;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mMaterialIndex;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mAdjacencyStartIndex;

	T3MeshBatch()
	{
		this->mBoundingBox = {};
		this->mBoundingSphere = {};
		this->mBatchUsage_BlockSize = 0;
		this->mBatchUsage = 0;
		this->mBatchUsage = 0;
		this->mMinVertIndex = 0;
		this->mMaxVertIndex = 0;
		this->mBaseIndex = 0;
		this->mStartIndex = 0;
		this->mNumPrimitives = 0;
		this->mNumIndices = 0;
		this->mTextureIndices = 0;
		this->mMaterialIndex = 0;
		this->mAdjacencyStartIndex = 0;
	};

	T3MeshBatch(std::ifstream* inputFileStream)
	{
		this->mBoundingBox = BoundingBox(inputFileStream); //[24 BYTES]
		this->mBoundingSphere = BoundingSphere(inputFileStream); //[20 BYTES]
		this->mBatchUsage_BlockSize = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mBatchUsage = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mMinVertIndex = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mMaxVertIndex = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mBaseIndex = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mStartIndex = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mNumPrimitives = ReadUInt32FromBinary(inputFileStream); //[4 BYTES] (mNumIndices / 3)
		this->mNumIndices = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mTextureIndices = ReadUInt32FromBinary(inputFileStream); //[4 BYTES] (4294967295)
		this->mMaterialIndex = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		this->mAdjacencyStartIndex = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//update values
		//mBatchUsage_BlockSize = 4; //block size uint32 itself
		//mBatchUsage_BlockSize += sizeof(mBatchUsage); //FOR SOME REASON THIS SEEMS TO BE 1 IN THE ORIGINAL FILE?
		//mNumPrimitives = this->mNumIndices / 3;
		//NOTE: COMMENTED out because these are not caclulated correctly...

		//begin serialization
		this->mBoundingBox.BinarySerialize(outputFileStream);
		this->mBoundingSphere.BinarySerialize(outputFileStream);
		WriteUInt32ToBinary(outputFileStream, this->mBatchUsage_BlockSize); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mBatchUsage); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mMinVertIndex); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mMaxVertIndex); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mBaseIndex); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mStartIndex); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mNumPrimitives); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mNumIndices); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mTextureIndices); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mMaterialIndex); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, this->mAdjacencyStartIndex); //[4 BYTES]
	};
};

#endif
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
	/// [4 bytes] 
	/// </summary>
	unsigned int mTextureIndices_BlockSize;

	/// <summary>
	/// [x bytes]
	/// </summary>
	std::vector<unsigned int> mTextureIndices;

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
		mBoundingBox = {};
		mBoundingSphere = {};
		mBatchUsage = 0;
		mMinVertIndex = 0;
		mMaxVertIndex = 0;
		mBaseIndex = 0;
		mStartIndex = 0;
		mNumPrimitives = 0;
		mNumIndices = 0;
		mTextureIndices_BlockSize = 0;
		mTextureIndices = {};
		mMaterialIndex = 0;
		mAdjacencyStartIndex = 0;
	};

	T3MeshBatch(std::ifstream* inputFileStream)
	{
		mBoundingBox = BoundingBox(inputFileStream); //[24 BYTES]
		mBoundingSphere = BoundingSphere(inputFileStream); //[20 BYTES]
		mBatchUsage = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mMinVertIndex = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mMaxVertIndex = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mBaseIndex = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mStartIndex = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mNumPrimitives = ReadUInt32FromBinary(inputFileStream); //[4 BYTES] (mNumIndices / 3)
		mNumIndices = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mTextureIndices_BlockSize = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]

		//According to lucas, there is a maximum of two ints that can be read for texture indicies...
		for (int i = 0; i < 2; i++)
		{
			int parsedInt32 = ReadInt32FromBinary(inputFileStream); //[4 BYTES] 

			//If the parsed value is -1 then we stop
			if (parsedInt32 == -1)
				break;

			//otherwise keep going, these values are the actual texture index values
			mTextureIndices.push_back(parsedInt32);
		}

		mMaterialIndex = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mAdjacencyStartIndex = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//update values
		//mTextureIndices_BlockSize = 4; //block size uint32 itself
		//mTextureIndices_BlockSize += sizeof(mTextureIndices.size() * 4); //each texture index value (if there aren't any then this will just be 0)
		//mTextureIndices_BlockSize += 4; //the last -1 at the end
		// 
		//mNumPrimitives = mNumIndices / 3;
		//NOTE: COMMENTED out because these are not caclulated correctly at the moment...

		//begin serialization
		mBoundingBox.BinarySerialize(outputFileStream);
		mBoundingSphere.BinarySerialize(outputFileStream);
		WriteUInt32ToBinary(outputFileStream, mBatchUsage); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mMinVertIndex); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mMaxVertIndex); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mBaseIndex); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mStartIndex); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mNumPrimitives); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mNumIndices); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mTextureIndices_BlockSize); //[4 BYTES]

		//According to lucas, there is a maximum of two ints that can be read for texture indicies...
		for (int i = 0; i < mTextureIndices.size(); i++)
		{
			WriteUInt32ToBinary(outputFileStream, mTextureIndices[i]); //[4 BYTES] 
		}

		WriteInt32ToBinary(outputFileStream, -1); //[4 BYTES] NOTE: This is the stop value for texture indicies

		WriteUInt32ToBinary(outputFileStream, mMaterialIndex); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mAdjacencyStartIndex); //[4 BYTES]
	};
};

#endif
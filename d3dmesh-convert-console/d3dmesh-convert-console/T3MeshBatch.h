#pragma once
#ifndef T3_MESH_BATCH_H
#define T3_MESH_BATCH_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Json.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"

//||||||||||||||||||||||||||||| T3 MESH BATCH |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH BATCH |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH BATCH |||||||||||||||||||||||||||||

/// <summary>
/// [x BYTES] This is a part of a mesh.
/// </summary>
class T3MeshBatch
{
public:

	/// <summary>
	/// [24 BYTES] The bounding box defined for the mesh.
	/// </summary>
	BoundingBox mBoundingBox;

	/// <summary>
	/// [20 BYTES] The bounding sphere defined for the mesh.
	/// </summary>
	BoundingSphere mBoundingSphere;

	/// <summary>
	/// [4 BYTES] mFlags
	/// </summary>
	unsigned int mBatchUsage;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mMinVertIndex;

	/// <summary>
	/// [4 BYTES] (Seems to always be 0?)
	/// </summary>
	unsigned int mMaxVertIndex;

	/// <summary>
	/// [4 BYTES] 
	/// <para> This starts at 0, but progressively towards the end with more batch elements, this gets incremented by mNumPrimitives. </para>
	/// <para> NOTE: This seems to be related with the index buffer. </para>
	/// </summary>
	unsigned int mBaseIndex;

	/// <summary>
	/// [4 BYTES] 
	/// <para> NOTE 1: This seems to be related with the index buffer. </para>
	/// <para> NOTE 2: error.mdl noted that this aligns with (mNumPrimitives / 3). </para>
	/// </summary>
	unsigned int mStartIndex;

	/// <summary>
	/// [4 BYTES] The number of triangles in the batch mesh.
	/// <para> NOTE 2: this seems to be (mStartIndex * 3). </para>
	/// </summary>
	unsigned int mNumPrimitives;

	/// <summary>
	/// [4 BYTES] (Seems to always be 8?)
	/// <para> NOTE 1: error.mdl noted that this might actually be a flag field. Where 8 is 1<<3, triangles = 3 triangles </para>
	/// </summary>
	unsigned int mNumIndices;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mTextureIndices_BlockSize;

	/// <summary>
	/// [x BYTES]
	/// </summary>
	std::vector<unsigned int> mTextureIndices;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	int mTextureIndices_End;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mMaterialIndex;

	/// <summary>
	/// [4 BYTES] 
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
		mTextureIndices_End = 0;
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
			{
				mTextureIndices_End = parsedInt32;
				break;
			}

			//otherwise keep going, these values are the actual texture index values
			mTextureIndices.push_back(parsedInt32);
		}

		mMaterialIndex = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mAdjacencyStartIndex = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//update values
		mTextureIndices_BlockSize = 4; //[4 BYTES] block size uint32 itself
		mTextureIndices_BlockSize += mTextureIndices.size() * 4; //[4 BYTES] each texture index value (if there aren't any then this will just be 0)
		mTextureIndices_BlockSize += 4; //[4 BYTES] the last -1 at the end

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
			WriteUInt32ToBinary(outputFileStream, mTextureIndices[i]); //[4 BYTES] 

		WriteInt32ToBinary(outputFileStream, mTextureIndices_End); //[4 BYTES] NOTE: This is the stop value for texture indicies
		WriteUInt32ToBinary(outputFileStream, mMaterialIndex); //[4 BYTES]
		WriteUInt32ToBinary(outputFileStream, mAdjacencyStartIndex); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "";
		output += "[T3MeshBatch] mBoundingBox: " + mBoundingBox.ToString() + "\n";
		output += "[T3MeshBatch] mBoundingSphere: " + mBoundingSphere.ToString() + "\n";
		output += "[T3MeshBatch] mBatchUsage: " + std::to_string(mBatchUsage) + "\n";
		output += "[T3MeshBatch] mMinVertIndex: " + std::to_string(mMinVertIndex) + "\n";
		output += "[T3MeshBatch] mMaxVertIndex: " + std::to_string(mMaxVertIndex) + "\n";
		output += "[T3MeshBatch] mBaseIndex: " + std::to_string(mBaseIndex) + "\n";
		output += "[T3MeshBatch] mStartIndex: " + std::to_string(mStartIndex) + "\n";
		output += "[T3MeshBatch] mNumPrimitives: " + std::to_string(mNumPrimitives) + "\n";
		output += "[T3MeshBatch] mNumIndices: " + std::to_string(mNumIndices) + "\n";
		output += "[T3MeshBatch] mTextureIndices_BlockSize: " + std::to_string(mTextureIndices_BlockSize) + "\n";

		//According to lucas, there is a maximum of two ints that can be read for texture indicies...
		for (int i = 0; i < mTextureIndices.size(); i++)
			output += "[T3MeshBatch] mTextureIndices " + std::to_string(i) + ": " + std::to_string(mTextureIndices[i]) + "\n";

		output += "[T3MeshBatch] mTextureIndices_End: " + std::to_string(mTextureIndices_End) + "\n";
		output += "[T3MeshBatch] mMaterialIndex: " + std::to_string(mMaterialIndex) + "\n";
		output += "[T3MeshBatch] mAdjacencyStartIndex: " + std::to_string(mAdjacencyStartIndex);
		return output;
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE(...) //throws exceptions when there are missing values
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(
		T3MeshBatch, 
		mBoundingBox,
		mBoundingSphere,
		mBatchUsage,
		mMinVertIndex,
		mMaxVertIndex,
		mBaseIndex,
		mStartIndex,
		mNumPrimitives,
		mNumIndices,
		mTextureIndices_BlockSize,
		mTextureIndices,
		mTextureIndices_End,
		mMaterialIndex,
		mAdjacencyStartIndex)

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
		totalByteSize += mBoundingBox.GetByteSize(); //[24 BYTES] mBoundingBox
		totalByteSize += mBoundingSphere.GetByteSize(); //[20 BYTES] mBoundingSphere
		totalByteSize += 4; //[4 BYTES] mBatchUsage
		totalByteSize += 4; //[4 BYTES] mMinVertIndex
		totalByteSize += 4; //[4 BYTES] mMaxVertIndex
		totalByteSize += 4; //[4 BYTES] mBaseIndex
		totalByteSize += 4; //[4 BYTES] mStartIndex
		totalByteSize += 4; //[4 BYTES] mNumPrimitives
		totalByteSize += 4; //[4 BYTES] mNumIndices
		totalByteSize += 4; //[4 BYTES] mTextureIndices_BlockSize
		totalByteSize += mTextureIndices.size() * 4; //[x BYTES] mTextureIndices
		totalByteSize += 4; //[4 BYTES] mTextureIndices_End
		totalByteSize += 4; //[4 BYTES] mMaterialIndex
		totalByteSize += 4; //[4 BYTES] mAdjacencyStartIndex
		return totalByteSize;
	}
};

#endif
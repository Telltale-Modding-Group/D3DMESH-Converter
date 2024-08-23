#pragma once
#ifndef T3_MESH_LOD_H
#define T3_MESH_LOD_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "T3MeshBatch.h"
#include "Symbol.h"

//||||||||||||||||||||||||||||| T3 MESH LOD |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH LOD |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH LOD |||||||||||||||||||||||||||||

/// <summary>
/// [x bytes]
/// </summary>
class T3MeshLOD
{
public:

	/// <summary>
	/// [4 bytes]
	/// <para> (CALCULATION) to calculate array capacity... </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the array capacity. </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the amount of elements in the array. </para>
	/// <para> Then add the result of [ (element byte size) x (amount of elements) ] </para>
	/// </summary>
	unsigned int mBatches0_ArrayCapacity;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mBatches0_ArrayLength;

	/// <summary>
	/// [88 x mBatches0_ArrayLength bytes] This is the default mesh.
	/// </summary>
	std::vector<T3MeshBatch> mBatches0;

	/// <summary>
	/// [4 bytes]
	/// <para> (CALCULATION) to calculate array capacity... </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the array capacity. </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the amount of elements in the array. </para>
	/// <para> Then add the result of [ (element byte size) x (amount of elements) ] </para>
	/// </summary>
	unsigned int mBatches1_ArrayCapacity;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mBatches1_ArrayLength;

	/// <summary>
	/// [88 x mBatches0_ArrayLength bytes] This is the shadow caster variant of the mesh.
	/// </summary>
	std::vector<T3MeshBatch> mBatches1;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mVertexStreams_BlockSize;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mVertexStreams;

	/// <summary>
	/// [24 bytes]
	/// </summary>
	BoundingBox mBoundingBox;

	/// <summary>
	/// [20 bytes]
	/// </summary>
	BoundingSphere mBoundingSphere;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mFlags;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mVertexStateIndex;

	/// <summary>
	/// [4 bytes] 
	/// <para> NOTE: If we iterate through all T3MeshBatch's (either in mBatches0 or mBatches1), and for each T3MeshBatch, if we add up mStartIndex, then multiply the total by 2, we get the primitive count that matches this LOD level. </para>
	/// <para> NOTE: We can also take this inital value, and multiply it by 1.5 to get the total triangle count for this LOD level. </para>
	/// <para> NEW NOTE: This is the amount of triangles that are in the default mesh batch set for the current LOD level.
	/// </summary>
	unsigned int mNumPrimitives;

	/// <summary>
	/// [4 bytes] The total amount of mesh batches for this LOD group (mBatches0_ArrayLength + mBatches1_ArrayLength)
	/// </summary>
	unsigned int mNumBatches;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mVertexStart;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mVertexCount;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mTextureAtlasWidth;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mTextureAtlasHeight;

	/// <summary>
	/// [4 bytes] LOD specific parameter
	/// </summary>
	float mPixelSize;

	/// <summary>
	/// [4 bytes] LOD specific parameter
	/// </summary>
	float mDistance;

	/// <summary>
	/// [4 bytes]
	/// <para> (CALCULATION) to calculate array capacity... </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the array capacity. </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the amount of elements in the array. </para>
	/// <para> Then add the result of [ (element byte size) x (amount of elements) ] </para>
	/// </summary>
	unsigned int mBones_ArrayCapacity;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mBones_ArrayLength;

	std::vector<Symbol> mBones;

	T3MeshLOD() 
	{
		mBatches0_ArrayCapacity = 0;
		mBatches0_ArrayLength = 0;
		mBatches0 = {};
		mBatches1_ArrayCapacity = 0;
		mBatches1_ArrayLength = 0;
		mBatches1 = {};
		mVertexStreams_BlockSize = 0;
		mVertexStreams = 0;
		mBoundingBox = {};
		mBoundingSphere = {};
		mFlags = 0;
		mVertexStateIndex = 0;
		mNumPrimitives = 0;
		mNumBatches = 0;
		mVertexStart = 0;
		mVertexCount = 0;
		mTextureAtlasWidth = 0;
		mTextureAtlasHeight = 0;
		mPixelSize = 0.0f;
		mDistance = 0.0f;
		mBones_ArrayCapacity = 0;
		mBones_ArrayLength = 0;
		mBones = {};
	};

	T3MeshLOD(std::ifstream* inputFileStream)
	{
		mBatches0_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		mBatches0_ArrayLength = ReadUInt32FromBinary(inputFileStream);

		for (int mBatches0Index = 0; mBatches0Index < mBatches0_ArrayLength; mBatches0Index++)
		{
			mBatches0.push_back(T3MeshBatch(inputFileStream));
		}

		mBatches1_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		mBatches1_ArrayLength = ReadUInt32FromBinary(inputFileStream);

		for (int mBatches1Index = 0; mBatches1Index < mBatches1_ArrayLength; mBatches1Index++)
		{
			mBatches1.push_back(T3MeshBatch(inputFileStream));
		}

		mVertexStreams_BlockSize = ReadUInt32FromBinary(inputFileStream);
		mVertexStreams = ReadUInt32FromBinary(inputFileStream);
		mBoundingBox = BoundingBox(inputFileStream);
		mBoundingSphere = BoundingSphere(inputFileStream);
		mFlags = ReadUInt32FromBinary(inputFileStream);
		mVertexStateIndex = ReadUInt32FromBinary(inputFileStream);
		mNumPrimitives = ReadUInt32FromBinary(inputFileStream);
		mNumBatches = ReadUInt32FromBinary(inputFileStream);
		mVertexStart = ReadUInt32FromBinary(inputFileStream);
		mVertexCount = ReadUInt32FromBinary(inputFileStream);
		mTextureAtlasWidth = ReadUInt32FromBinary(inputFileStream);
		mTextureAtlasHeight = ReadUInt32FromBinary(inputFileStream);
		mPixelSize = ReadFloat32FromBinary(inputFileStream);
		mDistance = ReadFloat32FromBinary(inputFileStream);
		mBones_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		mBones_ArrayLength = ReadUInt32FromBinary(inputFileStream);

		for (int mBoneIndex = 0; mBoneIndex < mBones_ArrayLength; mBoneIndex++)
		{
			mBones.push_back(Symbol(inputFileStream));
		}
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//update values
		mBatches0_ArrayLength = mBatches0.size();
		mBatches1_ArrayLength = mBatches1.size();
		mBones_ArrayLength = mBones.size();

		mBatches0_ArrayCapacity = 4; //block size uint32 itself
		mBatches0_ArrayCapacity += sizeof(mBatches0_ArrayLength);
		mBatches0_ArrayCapacity += sizeof(T3MeshBatch) * mBatches0_ArrayLength;

		mBatches1_ArrayCapacity = 4; //block size uint32 itself
		mBatches1_ArrayCapacity += sizeof(mBatches1_ArrayLength);
		mBatches1_ArrayCapacity += sizeof(T3MeshBatch) * mBatches1_ArrayLength;

		mBones_ArrayCapacity = 4; //block size uint32 itself
		mBones_ArrayCapacity += sizeof(mBones_ArrayLength);
		mBones_ArrayCapacity += sizeof(Symbol) * mBones_ArrayLength;

		mVertexStreams_BlockSize = 4; //block size uint32 itself
		mVertexStreams_BlockSize += sizeof(mVertexStreams);

		mNumBatches = mBatches0_ArrayLength + mBatches1_ArrayLength;

		//begin serialization
		WriteUInt32ToBinary(outputFileStream, mBatches0_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, mBatches0_ArrayLength);

		for (int i = 0; i < mBatches0_ArrayLength; i++)
		{
			mBatches0[i].BinarySerialize(outputFileStream);
		}

		WriteUInt32ToBinary(outputFileStream, mBatches1_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, mBatches1_ArrayLength);

		for (int i = 0; i < mBatches1_ArrayLength; i++)
		{
			mBatches1[i].BinarySerialize(outputFileStream);
		}

		WriteUInt32ToBinary(outputFileStream, mVertexStreams_BlockSize);
		WriteUInt32ToBinary(outputFileStream, mVertexStreams);

		mBoundingBox.BinarySerialize(outputFileStream);
		mBoundingSphere.BinarySerialize(outputFileStream);

		WriteUInt32ToBinary(outputFileStream, mFlags);
		WriteUInt32ToBinary(outputFileStream, mVertexStateIndex);
		WriteUInt32ToBinary(outputFileStream, mNumPrimitives);
		WriteUInt32ToBinary(outputFileStream, mNumBatches);
		WriteUInt32ToBinary(outputFileStream, mVertexStart);
		WriteUInt32ToBinary(outputFileStream, mVertexCount);
		WriteUInt32ToBinary(outputFileStream, mTextureAtlasWidth);
		WriteUInt32ToBinary(outputFileStream, mTextureAtlasHeight);
		WriteUInt32ToBinary(outputFileStream, mPixelSize);
		WriteUInt32ToBinary(outputFileStream, mDistance);
		WriteUInt32ToBinary(outputFileStream, mBones_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, mBones_ArrayLength);

		for (int i = 0; i < mBones_ArrayLength; i++)
		{
			mBones[i].BinarySerialize(outputFileStream);
		}
	};
};

#endif
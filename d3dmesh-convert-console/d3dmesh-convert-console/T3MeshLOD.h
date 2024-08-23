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
		this->mBatches0_ArrayCapacity = 0;
		this->mBatches0_ArrayLength = 0;
		this->mBatches0 = {};
		unsigned int mBatches1_ArrayCapacity = 0;
		unsigned int mBatches1_ArrayLength = 0;
		this->mBatches1 = {};
		unsigned int mVertexStreams_BlockSize = 0;
		unsigned int mVertexStreams = 0;
		this->mBoundingBox = {};
		this->mBoundingSphere = {};
		unsigned int mFlags = 0;
		unsigned int mVertexStateIndex = 0;
		unsigned int mNumPrimitives = 0;
		unsigned int mNumBatches = 0;
		unsigned int mVertexStart = 0;
		unsigned int mVertexCount = 0;
		unsigned int mTextureAtlasWidth = 0;
		unsigned int mTextureAtlasHeight = 0;
		float mPixelSize = 0.0f;
		float mDistance = 0.0f;
		unsigned int mBones_ArrayCapacity = 0;
		unsigned int mBones_ArrayLength = 0;
		this->mBones = {};
	};

	T3MeshLOD(std::ifstream* inputFileStream)
	{
		this->mBatches0_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		this->mBatches0_ArrayLength = ReadUInt32FromBinary(inputFileStream);

		for (int mBatches0Index = 0; mBatches0Index < this->mBatches0_ArrayLength; mBatches0Index++)
		{
			this->mBatches0.push_back(T3MeshBatch(inputFileStream));
		}

		this->mBatches1_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		this->mBatches1_ArrayLength = ReadUInt32FromBinary(inputFileStream);

		for (int mBatches1Index = 0; mBatches1Index < this->mBatches1_ArrayLength; mBatches1Index++)
		{
			this->mBatches1.push_back(T3MeshBatch(inputFileStream));
		}

		this->mVertexStreams_BlockSize = ReadUInt32FromBinary(inputFileStream);
		this->mVertexStreams = ReadUInt32FromBinary(inputFileStream);
		this->mBoundingBox = BoundingBox(inputFileStream);
		this->mBoundingSphere = BoundingSphere(inputFileStream);
		this->mFlags = ReadUInt32FromBinary(inputFileStream);
		this->mVertexStateIndex = ReadUInt32FromBinary(inputFileStream);
		this->mNumPrimitives = ReadUInt32FromBinary(inputFileStream);
		this->mNumBatches = ReadUInt32FromBinary(inputFileStream);
		this->mVertexStart = ReadUInt32FromBinary(inputFileStream);
		this->mVertexCount = ReadUInt32FromBinary(inputFileStream);
		this->mTextureAtlasWidth = ReadUInt32FromBinary(inputFileStream);
		this->mTextureAtlasHeight = ReadUInt32FromBinary(inputFileStream);
		this->mPixelSize = ReadFloat32FromBinary(inputFileStream);
		this->mDistance = ReadFloat32FromBinary(inputFileStream);
		this->mBones_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		this->mBones_ArrayLength = ReadUInt32FromBinary(inputFileStream);

		for (int mBoneIndex = 0; mBoneIndex < this->mBones_ArrayLength; mBoneIndex++)
		{
			this->mBones.push_back(Symbol(inputFileStream));
		}
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//update values
		mBatches0_ArrayLength = this->mBatches0.size();
		mBatches1_ArrayLength = this->mBatches1.size();
		mBones_ArrayLength = this->mBones.size();

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
		WriteUInt32ToBinary(outputFileStream, this->mBatches0_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, this->mBatches0_ArrayLength);

		for (int i = 0; i < this->mBatches0_ArrayLength; i++)
		{
			this->mBatches0[i].BinarySerialize(outputFileStream);
		}

		WriteUInt32ToBinary(outputFileStream, this->mBatches1_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, this->mBatches1_ArrayLength);

		for (int i = 0; i < this->mBatches1_ArrayLength; i++)
		{
			this->mBatches1[i].BinarySerialize(outputFileStream);
		}

		WriteUInt32ToBinary(outputFileStream, this->mVertexStreams_BlockSize);
		WriteUInt32ToBinary(outputFileStream, this->mVertexStreams);

		this->mBoundingBox.BinarySerialize(outputFileStream);
		this->mBoundingSphere.BinarySerialize(outputFileStream);

		WriteUInt32ToBinary(outputFileStream, this->mFlags);
		WriteUInt32ToBinary(outputFileStream, this->mVertexStateIndex);
		WriteUInt32ToBinary(outputFileStream, this->mNumPrimitives);
		WriteUInt32ToBinary(outputFileStream, this->mNumBatches);
		WriteUInt32ToBinary(outputFileStream, this->mVertexStart);
		WriteUInt32ToBinary(outputFileStream, this->mVertexCount);
		WriteUInt32ToBinary(outputFileStream, this->mTextureAtlasWidth);
		WriteUInt32ToBinary(outputFileStream, this->mTextureAtlasHeight);
		WriteUInt32ToBinary(outputFileStream, this->mPixelSize);
		WriteUInt32ToBinary(outputFileStream, this->mDistance);
		WriteUInt32ToBinary(outputFileStream, this->mBones_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, this->mBones_ArrayLength);

		for (int i = 0; i < this->mBones_ArrayLength; i++)
		{
			this->mBones[i].BinarySerialize(outputFileStream);
		}
	};
};

#endif
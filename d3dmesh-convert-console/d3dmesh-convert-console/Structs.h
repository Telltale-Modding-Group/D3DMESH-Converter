//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||

//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Standard C++ Library
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <stdlib.h>
#include <time.h>

//Custom
#include "TelltaleEnums.h"
#include "BinarySerialization.h"

#pragma once
#ifndef STRUCTS_H
#define STRUCTS_H

//||||||||||||||||||||||||||||| STRUCTS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| STRUCTS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| STRUCTS |||||||||||||||||||||||||||||

//||||||||||||||||||||||||||||| FLOAT VECTORS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| FLOAT VECTORS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| FLOAT VECTORS |||||||||||||||||||||||||||||
//NOTE: These are actual data structures serialized in a telltale file.
//Each vector component is a float.

/// <summary>
/// [8 bytes] Vector with 2 float32 components (x, y)
/// </summary>
struct Vector2
{
	/// <summary>
	/// [4 bytes] x (horizontal) component.
	/// </summary>
	float x;

	/// <summary>
	/// [4 bytes] y (vertical) component.
	/// </summary>
	float y;

	Vector2()
	{
		this->x = 0.0f;
		this->y = 0.0f;
	};

	Vector2(nlohmann::json& json)
	{
		this->x = json.at("x").get_to(this->x);
		this->y = json.at("y").get_to(this->y);
	};

	void ToJson(nlohmann::json& json)
	{
		json.push_back(
			{
				{ "x", this->x },
				{ "y", this->y },
			}
		);
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		BinarySerialization::WriteFloat32ToBinary(outputFileStream, this->x);
		BinarySerialization::WriteFloat32ToBinary(outputFileStream, this->y);
	};
};

/// <summary>
/// [12 bytes] Vector with 3 float32 components (x, y, z)
/// </summary>
struct Vector3
{
	/// <summary>
	/// [4 bytes] x (horizontal) component.
	/// </summary>
	float x;

	/// <summary>
	/// [4 bytes] y (vertical) component.
	/// </summary>
	float y;

	/// <summary>
	/// [4 bytes] z (depth) component.
	/// </summary>
	float z;

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		BinarySerialization::WriteFloat32ToBinary(outputFileStream, this->x);
		BinarySerialization::WriteFloat32ToBinary(outputFileStream, this->y);
		BinarySerialization::WriteFloat32ToBinary(outputFileStream, this->z);
	};
};

/// <summary>
/// [16 bytes] Vector with 4 float32 components (x, y, z, w)
/// </summary>
struct Vector4
{
	/// <summary>
	/// [4 bytes] x (horizontal) component.
	/// </summary>
	float x;

	/// <summary>
	/// [4 bytes] y (vertical) component.
	/// </summary>
	float y;

	/// <summary>
	/// [4 bytes] z (depth) component.
	/// </summary>
	float z;

	/// <summary>
	/// [4 bytes] w (scalar) component.
	/// </summary>
	float w;

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		BinarySerialization::WriteFloat32ToBinary(outputFileStream, this->x);
		BinarySerialization::WriteFloat32ToBinary(outputFileStream, this->y);
		BinarySerialization::WriteFloat32ToBinary(outputFileStream, this->z);
		BinarySerialization::WriteFloat32ToBinary(outputFileStream, this->w);
	};
};

//||||||||||||||||||||||||||||| INTEGER VECTORS ||||||||||||||||||||||||||||| (CUSTOM)
//||||||||||||||||||||||||||||| INTEGER VECTORS ||||||||||||||||||||||||||||| (CUSTOM)
//||||||||||||||||||||||||||||| INTEGER VECTORS ||||||||||||||||||||||||||||| (CUSTOM)
//NOTE: These are NOT actual data structures serialized in a telltale file.
//However there are cases where the vector types do hold integer data per component.

/// <summary>
/// [8 bytes] Vector with 2 int32 components (x, y)
/// </summary>
struct IntegerVector2
{
	/// <summary>
	/// [4 bytes] x (horizontal) component.
	/// </summary>
	int x;

	/// <summary>
	/// [4 bytes] y (vertical) component.
	/// </summary>
	int y;
};

/// <summary>
/// [12 bytes] Vector with 3 int32 components (x, y, z)
/// </summary>
struct IntegerVector3
{
	/// <summary>
	/// [4 bytes] x (horizontal) component.
	/// </summary>
	int x;

	/// <summary>
	/// [4 bytes] y (vertical) component.
	/// </summary>
	int y;

	/// <summary>
	/// [4 bytes] z (depth) component.
	/// </summary>
	int z;
};

/// <summary>
/// [16 bytes] Vector with 4 int32 components (x, y, z, w)
/// </summary>
struct IntegerVector4
{
	/// <summary>
	/// [4 bytes] x (horizontal) component.
	/// </summary>
	int x;

	/// <summary>
	/// [4 bytes] y (vertical) component.
	/// </summary>
	int y;

	/// <summary>
	/// [4 bytes] z (depth) component.
	/// </summary>
	int z;

	/// <summary>
	/// [4 bytes] w (scalar) component.
	/// </summary>
	int w;
};

//||||||||||||||||||||||||||||| UNSIGNED INTEGER VECTORS ||||||||||||||||||||||||||||| (CUSTOM)
//||||||||||||||||||||||||||||| UNSIGNED INTEGER VECTORS ||||||||||||||||||||||||||||| (CUSTOM)
//||||||||||||||||||||||||||||| UNSIGNED INTEGER VECTORS ||||||||||||||||||||||||||||| (CUSTOM)
//NOTE: These are NOT actual data structures serialized in a telltale file.
//However there are cases where the vector types do hold unsigned integer data per component.

/// <summary>
/// [8 bytes] Vector with 2 uint32 components (x, y)
/// </summary>
struct UnsignedIntegerVector2
{
	/// <summary>
	/// [4 bytes] x (horizontal) component.
	/// </summary>
	unsigned int x;

	/// <summary>
	/// [4 bytes] y (vertical) component.
	/// </summary>
	unsigned int y;
};

/// <summary>
/// [12 bytes] Vector with 3 uint32 components (x, y, z)
/// </summary>
struct UnsignedIntegerVector3
{
	/// <summary>
	/// [4 bytes] x (horizontal) component.
	/// </summary>
	unsigned int x;

	/// <summary>
	/// [4 bytes] y (vertical) component.
	/// </summary>
	unsigned int y;

	/// <summary>
	/// [4 bytes] z (depth) component.
	/// </summary>
	unsigned int z;
};

/// <summary>
/// [16 bytes] Vector with 4 uint32 components (x, y, z, w)
/// </summary>
struct UnsignedIntegerVector4
{
	/// <summary>
	/// [4 bytes] x (horizontal) component.
	/// </summary>
	unsigned int x;

	/// <summary>
	/// [4 bytes] y (vertical) component.
	/// </summary>
	unsigned int y;

	/// <summary>
	/// [4 bytes] z (depth) component.
	/// </summary>
	unsigned int z;

	/// <summary>
	/// [4 bytes] w (scalar) component.
	/// </summary>
	unsigned int w;
};

//||||||||||||||||||||||||||||| QUATERNION |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| QUATERNION |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| QUATERNION |||||||||||||||||||||||||||||

/// <summary>
/// [16 bytes] A vector-like data structure used to represent rotations
/// </summary>
struct Quaternion
{
	/// <summary>
	/// [4 bytes] x component used to help define the axis of rotation
	/// </summary>
	float x;

	/// <summary>
	/// [4 bytes] y component used to help define the axis of rotation
	/// </summary>
	float y;

	/// <summary>
	/// [4 bytes] z component used to help define the axis of rotation
	/// </summary>
	float z;

	/// <summary>
	/// [4 bytes] w component used to determine the angle of rotation around the rotation axis
	/// </summary>
	float w;

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		BinarySerialization::WriteFloat32ToBinary(outputFileStream, this->x);
		BinarySerialization::WriteFloat32ToBinary(outputFileStream, this->y);
		BinarySerialization::WriteFloat32ToBinary(outputFileStream, this->z);
		BinarySerialization::WriteFloat32ToBinary(outputFileStream, this->w);
	};
};

//||||||||||||||||||||||||||||| TRANSFORM |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TRANSFORM |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TRANSFORM |||||||||||||||||||||||||||||

/// <summary>
/// [32 bytes] Defines a geometric rotation and position.
/// </summary>
struct Transform
{
	/// <summary>
	/// [4 bytes] The size of the current data structure (this value should be 32)
	/// <para>(CALCULATION) to calculate block size... </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the block size variable itself. </para>
	/// <para> Add 16, as this is the size of a Quaternion that represents the mRot variable. </para>
	/// <para> Add 12, as this is the size of a Vector3 that represents the mTrans variable. </para>
	/// </summary>
	unsigned int mBlockSize;

	/// <summary>
	/// [16 bytes] The rotation component of the transform.
	/// </summary>
	Quaternion mRot;

	/// <summary>
	/// [12 bytes] The position component of the transform.
	/// </summary>
	Vector3 mTrans;

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//update values
		mBlockSize = 4; //block size uint32 itself
		mBlockSize += sizeof(mRot);
		mBlockSize += sizeof(mTrans);

		//begin serialization
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mBlockSize);
		this->mRot.BinarySerialize(outputFileStream);
		this->mTrans.BinarySerialize(outputFileStream);
	};
};

//||||||||||||||||||||||||||||| SYMBOL |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| SYMBOL |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| SYMBOL |||||||||||||||||||||||||||||

/// <summary>
/// A hashed "string" (CRC64)
/// </summary>
struct Symbol
{
	/// <summary>
	/// [8 bytes] The hashed "string" (CRC64)
	/// </summary>
	unsigned long long mCrc64;

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		BinarySerialization::WriteUInt64ToBinary(outputFileStream, this->mCrc64);
	};
};

//||||||||||||||||||||||||||||| BOUNDING BOX |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| BOUNDING BOX |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| BOUNDING BOX |||||||||||||||||||||||||||||

/// <summary>
/// [24 bytes] A bounding box in three-dimensional space.
/// </summary>
struct BoundingBox
{
	/// <summary>
	/// [12 bytes] Represents the minimum coordinates of the bounding box in three-dimensional space.
	/// </summary>
	Vector3 mMin;

	/// <summary>
	/// [12 bytes] Represents the maximum coordinates of the bounding box in three-dimensional space.
	/// </summary>
	Vector3 mMax;

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		this->mMin.BinarySerialize(outputFileStream);
		this->mMax.BinarySerialize(outputFileStream);
	};
};

//||||||||||||||||||||||||||||| BOUNDING SPHERE |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| BOUNDING SPHERE |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| BOUNDING SPHERE |||||||||||||||||||||||||||||

/// <summary>
/// [20 bytes] A bounding sphere in three-dimensional space.
/// </summary>
struct BoundingSphere
{
	/// <summary>
	/// [4 bytes] The size of the current data structure (this value should be 20)
	/// <para>(CALCULATION) to calculate block size... </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the block size variable itself. </para>
	/// <para> Add 12, as this is the size of a Vector3 that represents the mCenter variable. </para>
	/// <para> Add 4, as this is the size of a float32 that represents the mRadius variable. </para>
	/// </summary>
	unsigned mBlockSize;

	/// <summary>
	/// [12 bytes] Center point of the bounding sphere in three-dimensional space.
	/// </summary>
	Vector3 mCenter;

	/// <summary>
	/// [4 bytes] Radius of the bounding sphere.
	/// </summary>
	float mRadius;

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//update values
		mBlockSize = 4; //block size uint32 itself
		mBlockSize += sizeof(mCenter);
		mBlockSize += sizeof(mRadius);

		//begin serialization
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mBlockSize);
		this->mCenter.BinarySerialize(outputFileStream);
		BinarySerialization::WriteFloat32ToBinary(outputFileStream, this->mRadius);
	};
};

//||||||||||||||||||||||||||||| GFX PLATFORM ATTRIBUTE PARAMS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| GFX PLATFORM ATTRIBUTE PARAMS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| GFX PLATFORM ATTRIBUTE PARAMS |||||||||||||||||||||||||||||

/// <summary>
/// [20 bytes] 
/// </summary>
struct GFXPlatformAttributeParams
{
	/// <summary>
	/// [4 bytes] This is an enum that indicates the mesh attribute type. (vertex position, vertex normal, vertex uv, etc)
	/// </summary>
	GFXPlatformVertexAttribute mAttribute;

	/// <summary>
	/// [4 bytes] This is an enum that defines the binary layout format of an attribute.
	/// </summary>
	GFXPlatformFormat mFormat;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mAttributeIndex;

	/// <summary>
	/// [4 bytes] This points to an element (by array index) in a T3GFXBuffer object array that this GFXPlatformAttributeParams is referencing.
	/// </summary>
	unsigned int mBufferIndex;

	/// <summary>
	/// [4 bytes] This points to the byte position in a T3GFXBuffer which is where the data for the buffer that this GFXPlatformAttributeParams is referencing starts at.
	/// </summary>
	unsigned int mBufferOffset;

	//NOTE: This was listed in the data structure in IDA, however upon additional discovery this is not actually serialized.
	//GFXPlatformVertexFrequency mFrequency;

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		BinarySerialization::WriteInt32ToBinary(outputFileStream, this->mAttribute);
		BinarySerialization::WriteInt32ToBinary(outputFileStream, this->mFormat);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mAttributeIndex);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mBufferIndex);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mBufferOffset);
	};
};

//||||||||||||||||||||||||||||| T3 GFX BUFFER |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 GFX BUFFER |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 GFX BUFFER |||||||||||||||||||||||||||||

/// <summary>
/// [20 bytes] 
/// </summary>
struct T3GFXBuffer
{
	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mResourceUsage;

	/// <summary>
	/// [4 bytes] This is an enum that defines the binary layout format of an attribute.
	/// </summary>
	GFXPlatformFormat mBufferFormat;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mBufferUsage;

	/// <summary>
	/// [4 bytes] This indicates how many elements are in the T3GFXBuffer
	/// </summary>
	unsigned int mCount;

	/// <summary>
	/// [4 bytes] This indicates the length of each element (in bytes) in the T3GFXBuffer
	/// </summary>
	unsigned int mStride;

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//update values
		mStride = GetGFXPlatformFormatStrideLength(this->mBufferFormat);

		//begin serialization
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mResourceUsage);
		BinarySerialization::WriteInt32ToBinary(outputFileStream, this->mBufferFormat);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mBufferUsage);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mCount);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mStride);
	};
};

//||||||||||||||||||||||||||||| T3 MESH BATCH |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH BATCH |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH BATCH |||||||||||||||||||||||||||||

/// <summary>
/// [88 bytes] This is a part of a mesh.
/// </summary>
struct T3MeshBatch
{
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
	/// <para> NOTE: This seems to be related with the index buffer. </para>
	/// </summary>
	unsigned int mStartIndex;

	/// <summary>
	/// [4 bytes] The number of triangles in the batch mesh.
	/// </summary>
	unsigned int mNumPrimitives;

	/// <summary>
	/// [4 bytes] (Seems to always be 8?)
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
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mBatchUsage_BlockSize);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mBatchUsage);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mMinVertIndex);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mMaxVertIndex);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mBaseIndex);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mStartIndex);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mNumPrimitives);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mNumIndices);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mTextureIndices);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mMaterialIndex);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mAdjacencyStartIndex);
	};
};

//||||||||||||||||||||||||||||| T3 MESH LOD |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH LOD |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH LOD |||||||||||||||||||||||||||||

/// <summary>
/// [x bytes]
/// </summary>
struct T3MeshLOD
{
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
	/// [88 x mBatches0_ArrayLength bytes]
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
	/// [88 x mBatches0_ArrayLength bytes]
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
	/// </summary>
	unsigned int mNumPrimitives;

	/// <summary>
	/// [4 bytes] The total amount of mesh batches (mBatches0_ArrayLength + mBatches1_ArrayLength)
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
	/// [4 bytes] 
	/// </summary>
	float mPixelSize;

	/// <summary>
	/// [4 bytes] 
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
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mBatches0_ArrayCapacity);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mBatches0_ArrayLength);

		for (int i = 0; i < this->mBatches0_ArrayLength; i++)
		{
			this->mBatches0[i].BinarySerialize(outputFileStream);
		}

		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mBatches1_ArrayCapacity);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mBatches1_ArrayLength);

		for (int i = 0; i < this->mBatches1_ArrayLength; i++)
		{
			this->mBatches1[i].BinarySerialize(outputFileStream);
		}

		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mVertexStreams_BlockSize);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mVertexStreams);

		this->mBoundingBox.BinarySerialize(outputFileStream);
		this->mBoundingSphere.BinarySerialize(outputFileStream);

		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mFlags);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mVertexStateIndex);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mNumPrimitives);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mNumBatches);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mVertexStart);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mVertexCount);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mTextureAtlasWidth);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mTextureAtlasHeight);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mPixelSize);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mDistance);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mBones_ArrayCapacity);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mBones_ArrayLength);

		for (int i = 0; i < this->mBones_ArrayLength; i++)
		{
			this->mBones[i].BinarySerialize(outputFileStream);
		}
	};
};

//||||||||||||||||||||||||||||| T3 MATERIAL REQUIREMENTS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MATERIAL REQUIREMENTS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MATERIAL REQUIREMENTS |||||||||||||||||||||||||||||

struct T3MaterialRequirements
{
	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mMaterialRequirements_BlockSize;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mPasses_BlockSize;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mPasses;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mChannels_BlockSize;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mChannels1;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mChannels2;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mInputs_BlockSize;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mInputs1;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mInputs2;

	/// <summary>
	/// [4 bytes] 
	/// </summary>
	unsigned int mInputs3;

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//update values
		mMaterialRequirements_BlockSize = sizeof(T3MaterialRequirements);

		mPasses_BlockSize = 4;
		mPasses_BlockSize += sizeof(mPasses);

		mChannels_BlockSize = 4;
		mChannels_BlockSize += sizeof(mChannels1);
		mChannels_BlockSize += sizeof(mChannels2);

		mInputs_BlockSize = 4;
		mInputs_BlockSize += sizeof(mInputs1);
		mInputs_BlockSize += sizeof(mInputs2);
		mInputs_BlockSize += sizeof(mInputs3);

		//begin serialization
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mMaterialRequirements_BlockSize);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mPasses_BlockSize);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mPasses);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mChannels_BlockSize);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mChannels1);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mChannels2);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mInputs_BlockSize);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mInputs1);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mInputs2);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mInputs3);
	};
};

//||||||||||||||||||||||||||||| TELLTALE INTERNAL RESOURCE |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE INTERNAL RESOURCE |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE INTERNAL RESOURCE |||||||||||||||||||||||||||||

struct TelltaleInternalResource
{
	Symbol mInternalResourceSymbol;
	Symbol mInternalResourceType;
	unsigned int mInternalResourceBlockSize;
	char* mInternalResourceData;

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//begin serialization
		this->mInternalResourceSymbol.BinarySerialize(outputFileStream);
		this->mInternalResourceType.BinarySerialize(outputFileStream);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mInternalResourceBlockSize);
		BinarySerialization::WriteByteBufferToBinary(outputFileStream, this->mInternalResourceBlockSize - 4, this->mInternalResourceData);
	};
};

//||||||||||||||||||||||||||||| EXTRACTED MESH ||||||||||||||||||||||||||||| (CUSTOM)
//||||||||||||||||||||||||||||| EXTRACTED MESH ||||||||||||||||||||||||||||| (CUSTOM)
//||||||||||||||||||||||||||||| EXTRACTED MESH ||||||||||||||||||||||||||||| (CUSTOM)

struct ExtractedMesh
{
	int vertexNormalsCount = 0;
	int vertexUVsCount = 0;
	int vertexColorsCount = 0;

	std::vector<unsigned short> triangleIndicies0;

	std::vector<Vector3> vertexPositions;

	//NOTE: Models normally have 1 set of vertex normals, however in the case of telltale...
	//Most models actually have 2 sets of vertex normals
	//1. The main regular normal set
	//2. creased normal set?
	std::vector<Vector3> vertexNormals0;
	std::vector<Vector3> vertexNormals1;
	std::vector<Vector3> vertexNormals2;
	std::vector<Vector3> vertexNormals3;

	std::vector<Vector3> vertexTangents;

	std::vector<Vector2> vertexUVs0;
	std::vector<Vector2> vertexUVs1;
	std::vector<Vector2> vertexUVs2;
	std::vector<Vector2> vertexUVs3;
	std::vector<Vector2> vertexUVs4;
	std::vector<Vector2> vertexUVs5;
	std::vector<Vector2> vertexUVs6;
	std::vector<Vector2> vertexUVs7;

	std::vector<Vector4> vertexColors0;
	std::vector<Vector4> vertexColors1;
	std::vector<Vector4> vertexColors2;
	std::vector<Vector4> vertexColors3;
	std::vector<Vector4> vertexColors4;
	std::vector<Vector4> vertexColors5;
	std::vector<Vector4> vertexColors6;
	std::vector<Vector4> vertexColors7;

	std::vector<UnsignedIntegerVector4> vertexBlendIndex0;

	std::vector<Vector3> vertexBlendWeight0;
};

struct ExtractedBufferData
{
	int vertexNormalsCount = 0;
	int vertexUVsCount = 0;
	int vertexColorsCount = 0;

	std::vector<unsigned short> triangleIndicies0;

	std::vector<Vector3> vertexPositions;

	//NOTE: Models normally have 1 set of vertex normals, however in the case of telltale...
	//Most models actually have 2 sets of vertex normals
	//1. The main regular normal set
	//2. creased normal set?
	std::vector<Vector3> vertexNormals0;
	std::vector<Vector3> vertexNormals1;
	std::vector<Vector3> vertexNormals2;
	std::vector<Vector3> vertexNormals3;

	std::vector<Vector3> vertexTangents;

	std::vector<Vector2> vertexUVs0;
	std::vector<Vector2> vertexUVs1;
	std::vector<Vector2> vertexUVs2;
	std::vector<Vector2> vertexUVs3;
	std::vector<Vector2> vertexUVs4;
	std::vector<Vector2> vertexUVs5;
	std::vector<Vector2> vertexUVs6;
	std::vector<Vector2> vertexUVs7;

	std::vector<Vector4> vertexColors0;
	std::vector<Vector4> vertexColors1;
	std::vector<Vector4> vertexColors2;
	std::vector<Vector4> vertexColors3;
	std::vector<Vector4> vertexColors4;
	std::vector<Vector4> vertexColors5;
	std::vector<Vector4> vertexColors6;
	std::vector<Vector4> vertexColors7;

	std::vector<UnsignedIntegerVector4> vertexBlendIndex0;

	std::vector<Vector3> vertexBlendWeight0;
};

struct ExtractedLOD
{
	std::vector<ExtractedMesh> submeshes;
};

//||||||||||||||||||||||||||||| TELLTALE CLASS NAME |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE CLASS NAME |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE CLASS NAME |||||||||||||||||||||||||||||

struct TelltaleClassName
{
	Symbol mTypeNameCRC;
	unsigned int mVersionCRC;

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		mTypeNameCRC.BinarySerialize(outputFileStream);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mVersionCRC);
	};
};

//||||||||||||||||||||||||||||| T3 MESH BONE ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH BONE ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH BONE ENTRY |||||||||||||||||||||||||||||

struct T3MeshBoneEntry
{
	Symbol mBoneName;
	BoundingBox mBoundingBox;
	BoundingSphere mBoundingSphere;
	unsigned int mNumVerts;

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		this->mBoneName.BinarySerialize(outputFileStream);
		this->mBoundingBox.BinarySerialize(outputFileStream);
		this->mBoundingSphere.BinarySerialize(outputFileStream);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mNumVerts);
	};
};

//||||||||||||||||||||||||||||| T3 MESH LOCAL TRANSFORM ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH LOCAL TRANSFORM ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH LOCAL TRANSFORM ENTRY |||||||||||||||||||||||||||||

struct T3MeshLocalTransformEntry
{
	Transform mTransform;
	unsigned int mCameraFacingType;

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		this->mTransform.BinarySerialize(outputFileStream);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mCameraFacingType);
	};
};

//||||||||||||||||||||||||||||| TELLTALE META HEADER (VERSION 6) |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE META HEADER (VERSION 6) |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE META HEADER (VERSION 6) |||||||||||||||||||||||||||||

/// <summary>
/// Meta Stream Version 6 (MSV6, or 6VSM), a meta header often used at the top of telltale files
/// </summary>
struct TelltaleMetaHeaderVersion6
{
	/// <summary>
	/// [4 bytes] The version of the meta stream version.
	/// </summary>
	std::string mMetaStreamVersion;

	/// <summary>
	/// [4 bytes] The size of the data 'header' after the meta header.
	/// </summary>
	unsigned int mDefaultSectionChunkSize;

	/// <summary>
	/// [4 bytes] The size of the debug data chunk after the meta header, which is always 0.
	/// </summary>
	unsigned int mDebugSectionChunkSize;

	/// <summary>
	/// [4 bytes] The size of the asynchronous data chunk (not the meta header, or the data chunk header, but the data itself).
	/// </summary>
	unsigned int mAsyncSectionChunkSize;

	/// <summary>
	/// [4 bytes] Amount of class name elements (CRC64 Class Names) used in the file.
	/// </summary>
	unsigned int mClassNamesLength;

	/// <summary>
	/// [12 bytes for each element] An array of class names (CRC64 Class Names) that are used in the file.
	/// </summary>
	std::vector<TelltaleClassName> mClassNames;

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//update values
		this->mClassNamesLength = mClassNames.size();

		//begin serialization
		BinarySerialization::WriteFixedStringToBinary(outputFileStream, this->mMetaStreamVersion);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mDefaultSectionChunkSize);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mDebugSectionChunkSize);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mAsyncSectionChunkSize);
		BinarySerialization::WriteUInt32ToBinary(outputFileStream, this->mClassNamesLength);

		for (int i = 0; i < this->mClassNamesLength; i++)
		{
			this->mClassNames[i].BinarySerialize(outputFileStream);
		}
	};
};

struct TelltaleD3DMeshV55
{
	unsigned int mNameBlockSize;
	std::string mName;
	unsigned int mVersion;
	char mToolProps;
	float mLightmapGlobalScale;
	unsigned int mLightmapTexCoordVersion;
	Symbol mLODParamCRC;
	unsigned int mInternalResourcesCount;
	std::vector<TelltaleInternalResource> mInternalResources;
	unsigned int mToolPropsBlockSize;
	char* mToolPropsData;
	char mHasOcclusionData;
	unsigned int mOcclusionDataBlockSize;
	char* mOcclusionData;
	unsigned int mT3MeshDataBlockSize;

	/// <summary>
	/// [4 bytes]
	/// <para> (CALCULATION) to calculate array capacity... </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the array capacity. </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the amount of elements in the array. </para>
	/// <para> Then add the result of [ (element byte size) x (amount of elements) ] </para>
	/// </summary>
	unsigned int mLODs_ArrayCapacity;
	unsigned int mLODs_ArrayLength;
	std::vector<T3MeshLOD> mLODs;

	/// <summary>
	/// [4 bytes]
	/// <para> (CALCULATION) to calculate array capacity... </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the array capacity. </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the amount of elements in the array. </para>
	/// <para> Then add the result of [ (element byte size) x (amount of elements) ] </para>
	/// </summary>
	unsigned int mTextures_ArrayCapacity;
	unsigned int mTextures_ArrayLength;
	char* mTexturesData;

	/// <summary>
	/// [4 bytes]
	/// <para> (CALCULATION) to calculate array capacity... </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the array capacity. </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the amount of elements in the array. </para>
	/// <para> Then add the result of [ (element byte size) x (amount of elements) ] </para>
	/// </summary>
	unsigned int mMaterials_ArrayCapacity;
	unsigned int mMaterials_ArrayLength;
	char* mMaterialsData;

	/// <summary>
	/// [4 bytes]
	/// <para> (CALCULATION) to calculate array capacity... </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the array capacity. </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the amount of elements in the array. </para>
	/// <para> Then add the result of [ (element byte size) x (amount of elements) ] </para>
	/// </summary>
	unsigned int mMaterialOverrides_ArrayCapacity;
	unsigned int mMaterialOverrides_ArrayLength;
	char* mMaterialOverridesData;

	/// <summary>
	/// [4 bytes]
	/// <para> (CALCULATION) to calculate array capacity... </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the array capacity. </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the amount of elements in the array. </para>
	/// <para> Then add the result of [ (element byte size) x (amount of elements) ] </para>
	/// </summary>
	unsigned int mBones_ArrayCapacity;
	unsigned int mBones_ArrayLength;
	std::vector<T3MeshBoneEntry> mBones;

	/// <summary>
	/// [4 bytes]
	/// <para> (CALCULATION) to calculate array capacity... </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the array capacity. </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the amount of elements in the array. </para>
	/// <para> Then add the result of [ (element byte size) x (amount of elements) ] </para>
	/// </summary>
	unsigned int mLocalTransforms_ArrayCapacity;
	unsigned int mLocalTransforms_ArrayLength;
	std::vector<T3MeshLocalTransformEntry> mLocalTransforms;
	T3MaterialRequirements mMaterialRequirements;
	unsigned int mVertexStreams_BlockSize; //value seems to always be 8
	unsigned int mVertexStreams;
	BoundingBox mBoundingBox;
	BoundingSphere mBoundingSphere;
	unsigned int mEndianType;
	Vector3 mPositionScale;
	Vector3 mPositionWScale;
	Vector3 mPositionOffset;
	float mLightmapTexelAreaPerSurfaceArea;
	Symbol mPropertyKeyBase;
	unsigned int mVertexCount;
	unsigned int mFlags;
	unsigned int mMeshPreload_BlockSize;
	char* mMeshPreloadData;
	unsigned int UNKNOWN1;
	unsigned int UNKNOWN2;
	unsigned int mVertexCountPerInstance;
	unsigned int mIndexBufferCount;
	unsigned int mVertexBufferCount;
	unsigned int mAttributeCount;
	std::vector<GFXPlatformAttributeParams> GFXPlatformAttributeParamsArray;
	std::vector<T3GFXBuffer> mIndexBuffers;
	std::vector<T3GFXBuffer> mVertexBuffers;
};

struct FileD3DMesh
{
	TelltaleMetaHeaderVersion6 metaHeader;
	TelltaleD3DMeshV55 d3dmeshHeader;
	std::vector<ExtractedLOD> extractedLODs;
};

#endif
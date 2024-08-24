#pragma once
#ifndef T3_MESH_LOD_H
#define T3_MESH_LOD_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Json.h"
#include "T3MeshBatch.h"
#include "Symbol.h"

//||||||||||||||||||||||||||||| T3 MESH LOD |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH LOD |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH LOD |||||||||||||||||||||||||||||

/// <summary>
/// [x BYTES]
/// </summary>
struct T3MeshLOD
{
	/// <summary>
	/// [4 BYTES]
	/// <para> (CALCULATION) to calculate array capacity... </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the array capacity. </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the amount of elements in the array. </para>
	/// <para> Then add the result of [ (element byte size) x (amount of elements) ] </para>
	/// </summary>
	unsigned int mBatches0_ArrayCapacity;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mBatches0_ArrayLength;

	/// <summary>
	/// [x BYTES] This is the default mesh.
	/// </summary>
	std::vector<T3MeshBatch> mBatches0;

	/// <summary>
	/// [4 BYTES]
	/// <para> (CALCULATION) to calculate array capacity... </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the array capacity. </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the amount of elements in the array. </para>
	/// <para> Then add the result of [ (element byte size) x (amount of elements) ] </para>
	/// </summary>
	unsigned int mBatches1_ArrayCapacity;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mBatches1_ArrayLength;

	/// <summary>
	/// [x BYTES] This is the shadow caster variant of the mesh.
	/// </summary>
	std::vector<T3MeshBatch> mBatches1;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mVertexStreams_BlockSize;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mVertexStreams;

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
	unsigned int mFlags;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mVertexStateIndex;

	/// <summary>
	/// [4 BYTES] 
	/// <para> NOTE: If we iterate through all T3MeshBatch's (either in mBatches0 or mBatches1), and for each T3MeshBatch, if we add up mStartIndex, then multiply the total by 2, we get the primitive count that matches this LOD level. </para>
	/// <para> NOTE: We can also take this inital value, and multiply it by 1.5 to get the total triangle count for this LOD level. </para>
	/// <para> NEW NOTE: This is the amount of triangles that are in the default mesh batch set for the current LOD level.
	/// </summary>
	unsigned int mNumPrimitives;

	/// <summary>
	/// [4 BYTES] The total amount of mesh batches for this LOD group (mBatches0_ArrayLength + mBatches1_ArrayLength)
	/// </summary>
	unsigned int mNumBatches;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mVertexStart;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mVertexCount;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mTextureAtlasWidth;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mTextureAtlasHeight;

	/// <summary>
	/// [4 BYTES] LOD specific parameter
	/// </summary>
	float mPixelSize;

	/// <summary>
	/// [4 BYTES] LOD specific parameter
	/// </summary>
	float mDistance;

	/// <summary>
	/// [4 BYTES]
	/// <para> (CALCULATION) to calculate array capacity... </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the array capacity. </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the amount of elements in the array. </para>
	/// <para> Then add the result of [ (element byte size) x (amount of elements) ] </para>
	/// </summary>
	unsigned int mBones_ArrayCapacity;

	/// <summary>
	/// [4 BYTES] 
	/// </summary>
	unsigned int mBones_ArrayLength;

	/// <summary>
	/// [x BYTES]
	/// </summary>
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

		for (int i = 0; i < mBatches0_ArrayLength; i++)
			mBatches0.push_back(T3MeshBatch(inputFileStream));

		mBatches1_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		mBatches1_ArrayLength = ReadUInt32FromBinary(inputFileStream);

		for (int i = 0; i < mBatches1_ArrayLength; i++)
			mBatches1.push_back(T3MeshBatch(inputFileStream));

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

		for (int i = 0; i < mBones_ArrayLength; i++)
			mBones.push_back(Symbol(inputFileStream));
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//update values
		mBatches0_ArrayLength = mBatches0.size();
		mBatches1_ArrayLength = mBatches1.size();
		mBones_ArrayLength = mBones.size();

		mBatches0_ArrayCapacity = 4; //[4 BYTES] block size uint32 itself
		mBatches0_ArrayCapacity += 4; //[4 BYTES] mBatches0_ArrayLength

		for (int i = 0; i < mBatches0_ArrayLength; i++)
			mBatches0_ArrayCapacity += mBatches0[i].GetByteSize();

		mBatches1_ArrayCapacity = 4; //[4 BYTES] block size uint32 itself
		mBatches1_ArrayCapacity += 4; //[4 BYTES] mBatches1_ArrayLength

		for (int i = 0; i < mBatches1_ArrayLength; i++)
			mBatches1_ArrayCapacity += mBatches1[i].GetByteSize();

		mBones_ArrayCapacity = 4; //[4 BYTES] block size uint32 itself
		mBones_ArrayCapacity += 4; //[4 BYTES] mBones_ArrayLength
		mBones_ArrayCapacity += 8 * mBones_ArrayLength; //8 is size of Symbol
		mVertexStreams_BlockSize = 4; //[4 BYTES] block size uint32 itself
		mVertexStreams_BlockSize += 4; //[4 BYTES] mVertexStreams
		mNumBatches = mBatches0_ArrayLength + mBatches1_ArrayLength;

		//begin serialization
		WriteUInt32ToBinary(outputFileStream, mBatches0_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, mBatches0_ArrayLength);

		for (int i = 0; i < mBatches0_ArrayLength; i++)
			mBatches0[i].BinarySerialize(outputFileStream);

		WriteUInt32ToBinary(outputFileStream, mBatches1_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, mBatches1_ArrayLength);

		for (int i = 0; i < mBatches1_ArrayLength; i++)
			mBatches1[i].BinarySerialize(outputFileStream);

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
		WriteFloat32ToBinary(outputFileStream, mPixelSize);
		WriteFloat32ToBinary(outputFileStream, mDistance);
		WriteUInt32ToBinary(outputFileStream, mBones_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, mBones_ArrayLength);

		for (int i = 0; i < mBones_ArrayLength; i++)
			mBones[i].BinarySerialize(outputFileStream);
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "";
		output += "[T3MeshLOD] mBatches0_ArrayCapacity: " + std::to_string(mBatches0_ArrayCapacity) + "\n";
		output += "[T3MeshLOD] mBatches0_ArrayLength: " + std::to_string(mBatches0_ArrayLength) + "\n";
		output += "[T3MeshLOD] ============ T3MeshBatch ARRAY START ============ \n";

		for (int i = 0; i < mBatches0_ArrayLength; i++)
		{
			output += "[T3MeshLOD] ============ T3MeshBatch " + std::to_string(i) + " ============ \n";
			output += mBatches0[i].ToString() + "\n";
		}

		output += "[T3MeshLOD] ============ T3MeshBatch ARRAY END ============ \n";
		output += "[T3MeshLOD] mBatches1_ArrayCapacity: " + std::to_string(mBatches1_ArrayCapacity) + "\n";
		output += "[T3MeshLOD] mBatches1_ArrayLength: " + std::to_string(mBatches1_ArrayLength) + "\n";

		for (int i = 0; i < mBatches1_ArrayLength; i++)
		{
			output += "[T3MeshLOD] ============ T3MeshBatch " + std::to_string(i) + " ============ \n";
			output += mBatches1[i].ToString() + "\n";
		}

		output += "[T3MeshLOD] ============ T3MeshBatch ARRAY END ============ \n";
		output += "[T3MeshLOD] mVertexStreams_BlockSize: " + std::to_string(mVertexStreams_BlockSize) + "\n";
		output += "[T3MeshLOD] mVertexStreams: " + std::to_string(mVertexStreams) + "\n";
		output += "[T3MeshLOD] mBoundingBox: " + mBoundingBox.ToString() + "\n";
		output += "[T3MeshLOD] mBoundingSphere: " + mBoundingSphere.ToString() + "\n";
		output += "[T3MeshLOD] mFlags: " + std::to_string(mFlags) + "\n";
		output += "[T3MeshLOD] mVertexStateIndex: " + std::to_string(mVertexStateIndex) + "\n";
		output += "[T3MeshLOD] mNumPrimitives: " + std::to_string(mNumPrimitives) + "\n";
		output += "[T3MeshLOD] mNumBatches: " + std::to_string(mNumBatches) + "\n";
		output += "[T3MeshLOD] mVertexStart: " + std::to_string(mVertexStart) + "\n";
		output += "[T3MeshLOD] mVertexCount: " + std::to_string(mVertexCount) + "\n";
		output += "[T3MeshLOD] mTextureAtlasWidth: " + std::to_string(mTextureAtlasWidth) + "\n";
		output += "[T3MeshLOD] mTextureAtlasHeight: " + std::to_string(mTextureAtlasHeight) + "\n";
		output += "[T3MeshLOD] mPixelSize: " + std::to_string(mPixelSize) + "\n";
		output += "[T3MeshLOD] mDistance: " + std::to_string(mDistance) + "\n";
		output += "[T3MeshLOD] mBones_ArrayCapacity: " + std::to_string(mBones_ArrayCapacity) + "\n";
		output += "[T3MeshLOD] mBones_ArrayLength: " + std::to_string(mBones_ArrayLength) + "\n";
		output += "[T3MeshLOD] ============ Symbol ARRAY START ============ \n";

		for (int i = 0; i < mBones_ArrayLength; i++)
			output += mBones[i].ToString() + "\n";

		output += "[T3MeshLOD] ============ Symbol ARRAY END ============";

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
		T3MeshLOD,
		mBatches0_ArrayCapacity,
		mBatches0_ArrayLength,
		mBatches0,
		mBatches1_ArrayCapacity,
		mBatches1_ArrayLength,
		mBatches1,
		mVertexStreams_BlockSize,
		mVertexStreams,
		mBoundingBox,
		mBoundingSphere,
		mFlags,
		mVertexStateIndex,
		mNumPrimitives,
		mNumBatches,
		mVertexStart,
		mVertexCount,
		mTextureAtlasWidth,
		mTextureAtlasHeight,
		mPixelSize,
		mDistance,
		mBones_ArrayCapacity,
		mBones_ArrayLength,
		mBones)

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
		totalByteSize += 4; //[4 BYTES] mBatches0_ArrayCapacity
		totalByteSize += 4; //[4 BYTES] mBatches0_ArrayLength

		for (int i = 0; i < mBatches0_ArrayLength; i++)
			totalByteSize += mBatches0[i].GetByteSize();

		totalByteSize += 4; //[4 BYTES] mBatches1_ArrayCapacity
		totalByteSize += 4; //[4 BYTES] mBatches1_ArrayLength

		for (int i = 0; i < mBatches1_ArrayLength; i++)
			totalByteSize += mBatches1[i].GetByteSize();

		totalByteSize += 4; //[4 BYTES] mVertexStreams_BlockSize
		totalByteSize += 4; //[4 BYTES] mVertexStreams
		totalByteSize += mBoundingBox.GetByteSize(); //[24 BYTES] mBoundingBox
		totalByteSize += mBoundingSphere.GetByteSize(); //[20 BYTES] mBatches1_ArrayLength
		totalByteSize += 4; //[4 BYTES] mFlags
		totalByteSize += 4; //[4 BYTES] mVertexStateIndex
		totalByteSize += 4; //[4 BYTES] mNumPrimitives
		totalByteSize += 4; //[4 BYTES] mNumBatches
		totalByteSize += 4; //[4 BYTES] mVertexStart
		totalByteSize += 4; //[4 BYTES] mVertexCount
		totalByteSize += 4; //[4 BYTES] mTextureAtlasWidth
		totalByteSize += 4; //[4 BYTES] mTextureAtlasHeight
		totalByteSize += 4; //[4 BYTES] mPixelSize
		totalByteSize += 4; //[4 BYTES] mDistance
		totalByteSize += 4; //[4 BYTES] mBones_ArrayCapacity
		totalByteSize += 4; //[4 BYTES] mBones_ArrayLength

		for (int i = 0; i < mBones_ArrayLength; i++)
			totalByteSize += mBones[i].GetByteSize(); //[8 BYTES]

		return totalByteSize;
	}
};

#endif
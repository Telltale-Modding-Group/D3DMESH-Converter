#pragma once
#ifndef TELLTALE_D3DMESH_HEADER_55_H
#define TELLTALE_D3DMESH_HEADER_55_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Symbol.h"
#include "Vector3.h"
#include "TelltaleInternalResource.h"
#include "T3MeshLOD.h"
#include "T3MeshBoneEntry.h"
#include "T3MeshLocalTransformEntry.h"
#include "T3MaterialRequirements.h"
#include "T3GFXBuffer.h"
#include "GFXPlatformAttributeParams.h"

//||||||||||||||||||||||||||||| TELLTALE D3DMESH HEADER V55 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE D3DMESH HEADER V55 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE D3DMESH HEADER V55 |||||||||||||||||||||||||||||

class TelltaleD3DMeshHeaderV55
{
public:

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

	TelltaleD3DMeshHeaderV55()
	{
		mNameBlockSize = 0;
		mName = "";
		mVersion = 0;
		mToolProps = 0;
		mLightmapGlobalScale = 0.0f;
		mLightmapTexCoordVersion = 0;
		mLODParamCRC = {};
		mInternalResourcesCount = 0;
		mInternalResources = {};
		mToolPropsBlockSize = 0;
		mToolPropsData = 0;
		mHasOcclusionData = 0;
		mOcclusionDataBlockSize = 0;
		mOcclusionData = 0;
		mT3MeshDataBlockSize = 0;
		mLODs_ArrayCapacity = 0;
		mLODs_ArrayLength = 0;
		mLODs = {};
		mTextures_ArrayCapacity = 0;
		mTextures_ArrayLength = 0;
		mTexturesData = 0;
		mMaterials_ArrayCapacity = 0;
		mMaterials_ArrayLength = 0;
		mMaterialsData = 0;
		mMaterialOverrides_ArrayCapacity = 0;
		mMaterialOverrides_ArrayLength = 0;
		mMaterialOverridesData = 0;
		mBones_ArrayCapacity = 0;
		mBones_ArrayLength = 0;
		mBones = {};
		mLocalTransforms_ArrayCapacity = 0;
		mLocalTransforms_ArrayLength = 0;
		mLocalTransforms = {};
		mMaterialRequirements = {};
		mVertexStreams_BlockSize = 0;
		mVertexStreams = 0;
		mBoundingBox = {};
		mBoundingSphere = {};
		mEndianType = 0;
		mPositionScale = {};
		mPositionWScale = {};
		mPositionOffset = {};
		mLightmapTexelAreaPerSurfaceArea = 0.0f;
		mPropertyKeyBase = {};
		mVertexCount = 0;
		mFlags = 0;
		mMeshPreload_BlockSize = 0;
		mMeshPreloadData = 0;
		UNKNOWN1 = 0;
		UNKNOWN2 = 0;
		mVertexCountPerInstance = 0;
		mIndexBufferCount = 0;
		mVertexBufferCount = 0;
		mAttributeCount = 0;
		GFXPlatformAttributeParamsArray = {};
		mIndexBuffers = {};
		mVertexBuffers = {};
	};

	TelltaleD3DMeshHeaderV55(std::ifstream* inputFileStream)
	{
		mNameBlockSize = ReadUInt32FromBinary(inputFileStream);
		mName = ReadLengthPrefixedStringFromBinary(inputFileStream);
		mVersion = ReadUInt32FromBinary(inputFileStream);
		mToolProps = ReadInt8FromBinary(inputFileStream);
		mLightmapGlobalScale = ReadFloat32FromBinary(inputFileStream);
		mLightmapTexCoordVersion = ReadUInt32FromBinary(inputFileStream);
		mLODParamCRC = Symbol(inputFileStream);

		//parse the internal resources block, this was difficult to track down but this basically contains propertysets or references to resources uses (i.e. materials)
		mInternalResourcesCount = ReadUInt32FromBinary(inputFileStream);

		for (int mInternalResourceIndex = 0; mInternalResourceIndex < mInternalResourcesCount; mInternalResourceIndex++)
		{
			mInternalResources.push_back(TelltaleInternalResource(inputFileStream)); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)
		}

		//parse the tool property set block, this shouldn't technically have any data since this is the final shipped file.
		mToolPropsBlockSize = ReadUInt32FromBinary(inputFileStream);
		mToolPropsData = ReadByteBufferFromBinary(inputFileStream, mToolPropsBlockSize); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)

		//parse the occlusion data block, this contains occlusion culling information regarding the mesh.
		mHasOcclusionData = ReadInt8FromBinary(inputFileStream);

		//if this is true then we need to skip it (ASCII '1' is true, ASCII '0' is false)
		if (mHasOcclusionData == '1')
		{
			mOcclusionDataBlockSize = ReadUInt32FromBinary(inputFileStream);
			mOcclusionData = ReadByteBufferFromBinary(inputFileStream, mOcclusionDataBlockSize - 4); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)
		}

		//this is the start of the main T3MeshData block
		mT3MeshDataBlockSize = ReadUInt32FromBinary(inputFileStream);

		//parse the LODs associated with the mesh (oddly enough telltale didn't use LODs very often?)
		mLODs_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		mLODs_ArrayLength = ReadUInt32FromBinary(inputFileStream);

		for (int i = 0; i < mLODs_ArrayLength; i++)
		{
			mLODs.push_back(T3MeshLOD(inputFileStream));
		}

		//parse the textures block (NOTE: This does not contain actual texture data, just references to it)
		mTextures_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		mTextures_ArrayLength = ReadUInt32FromBinary(inputFileStream);
		mTexturesData = ReadByteBufferFromBinary(inputFileStream, mTextures_ArrayCapacity - 8); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)

		//parse the materials block
		mMaterials_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		mMaterials_ArrayLength = ReadUInt32FromBinary(inputFileStream);
		mMaterialsData = ReadByteBufferFromBinary(inputFileStream, mMaterials_ArrayCapacity - 8); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)

		//parse the materials overrides block
		mMaterialOverrides_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		mMaterialOverrides_ArrayLength = ReadUInt32FromBinary(inputFileStream);
		mMaterialOverridesData = ReadByteBufferFromBinary(inputFileStream, mMaterialOverrides_ArrayCapacity - 8); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)

		//parse the rigging bones block
		mBones_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		mBones_ArrayLength = ReadUInt32FromBinary(inputFileStream);

		for (int i = 0; i < mBones_ArrayLength; i++)
		{
			mBones.push_back(T3MeshBoneEntry(inputFileStream));
		}

		//parse the rigging bones block
		mLocalTransforms_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		mLocalTransforms_ArrayLength = ReadUInt32FromBinary(inputFileStream);

		for (int i = 0; i < mLocalTransforms_ArrayLength; i++)
		{
			mLocalTransforms.push_back(T3MeshLocalTransformEntry(inputFileStream));
		}

		//parse other misc information in the d3dmesh header
		mMaterialRequirements = T3MaterialRequirements(inputFileStream);
		mVertexStreams_BlockSize = ReadUInt32FromBinary(inputFileStream); //value seems to always be 8
		mVertexStreams = ReadUInt32FromBinary(inputFileStream);
		mBoundingBox = BoundingBox(inputFileStream);
		mBoundingSphere = BoundingSphere(inputFileStream);
		mEndianType = ReadUInt32FromBinary(inputFileStream);
		mPositionScale = Vector3(inputFileStream);
		mPositionWScale = Vector3(inputFileStream);
		mPositionOffset = Vector3(inputFileStream);
		mLightmapTexelAreaPerSurfaceArea = ReadFloat32FromBinary(inputFileStream);
		mPropertyKeyBase = Symbol(inputFileStream);
		mVertexCount = ReadUInt32FromBinary(inputFileStream);
		mFlags = ReadUInt32FromBinary(inputFileStream);
		mMeshPreload_BlockSize = ReadUInt32FromBinary(inputFileStream);
		mMeshPreloadData = ReadByteBufferFromBinary(inputFileStream, mMeshPreload_BlockSize - 4); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)
		UNKNOWN1 = ReadUInt32FromBinary(inputFileStream);
		UNKNOWN2 = ReadUInt32FromBinary(inputFileStream);
		mVertexCountPerInstance = ReadUInt32FromBinary(inputFileStream);
		mIndexBufferCount = ReadUInt32FromBinary(inputFileStream);
		mVertexBufferCount = ReadUInt32FromBinary(inputFileStream);
		mAttributeCount = ReadUInt32FromBinary(inputFileStream);

		//parse the table of GFXPlatformAttributes, this is important as this is used during the vertex buffer parsing later to identify what buffers contain what data.
		for (int i = 0; i < mAttributeCount; i++)
		{
			GFXPlatformAttributeParamsArray.push_back(GFXPlatformAttributeParams(inputFileStream));
		}

		//parse the table of GFXBuffer data, these are "index" buffers (i.e. triangle indicies)
		for (int i = 0; i < mIndexBufferCount; i++)
		{
			mIndexBuffers.push_back(T3GFXBuffer(inputFileStream));
		}

		//parse the table of GFXBuffer data, these are "vertex" buffers (i.e. vertex position, normal, uv, etc)
		for (int i = 0; i < mVertexBufferCount; i++)
		{
			mVertexBuffers.push_back(T3GFXBuffer(inputFileStream));
		}
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		//update values
		mNameBlockSize = 8 + mName.length();

		//begin serialization
		WriteUInt32ToBinary(outputFileStream, mNameBlockSize);
		WriteLengthPrefixedStringToBinary(outputFileStream, mName);
		WriteUInt32ToBinary(outputFileStream, mVersion);
		WriteUInt8ToBinary(outputFileStream, mToolProps);
		WriteFloat32ToBinary(outputFileStream, mLightmapGlobalScale);
		WriteUInt32ToBinary(outputFileStream, mLightmapTexCoordVersion);
		mLODParamCRC.BinarySerialize(outputFileStream);
		WriteUInt32ToBinary(outputFileStream, mInternalResourcesCount);

		for (int mInternalResourceIndex = 0; mInternalResourceIndex < mInternalResourcesCount; mInternalResourceIndex++)
		{
			mInternalResources[mInternalResourceIndex].BinarySerialize(outputFileStream);
		}

		WriteUInt32ToBinary(outputFileStream, mToolPropsBlockSize);
		WriteByteBufferToBinary(outputFileStream, mToolPropsBlockSize - 4, mToolPropsData);
		WriteUInt8ToBinary(outputFileStream, mHasOcclusionData);

		//if this is true then we need to skip it (ASCII '1' is true, ASCII '0' is false)
		if (mHasOcclusionData == '1')
		{
			WriteUInt32ToBinary(outputFileStream, mOcclusionDataBlockSize);
			WriteByteBufferToBinary(outputFileStream, mOcclusionDataBlockSize - 4, mOcclusionData);
		}

		WriteUInt32ToBinary(outputFileStream, mT3MeshDataBlockSize);
		WriteUInt32ToBinary(outputFileStream, mLODs_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, mLODs_ArrayLength);

		for (int i = 0; i < mLODs_ArrayLength; i++)
		{
			mLODs[i].BinarySerialize(outputFileStream);
		}

		WriteUInt32ToBinary(outputFileStream, mTextures_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, mTextures_ArrayLength);
		WriteByteBufferToBinary(outputFileStream, mTextures_ArrayCapacity - 8, mTexturesData);

		WriteUInt32ToBinary(outputFileStream, mMaterials_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, mMaterials_ArrayLength);
		WriteByteBufferToBinary(outputFileStream, mMaterials_ArrayCapacity - 8, mMaterialsData);

		WriteUInt32ToBinary(outputFileStream, mMaterialOverrides_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, mMaterialOverrides_ArrayLength);
		WriteByteBufferToBinary(outputFileStream, mMaterialOverrides_ArrayCapacity - 8, mMaterialOverridesData);

		WriteUInt32ToBinary(outputFileStream, mBones_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, mBones_ArrayLength);

		for (int i = 0; i < mBones_ArrayLength; i++)
		{
			mBones[i].BinarySerialize(outputFileStream);
		}

		WriteUInt32ToBinary(outputFileStream, mLocalTransforms_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, mLocalTransforms_ArrayLength);

		for (int i = 0; i < mLocalTransforms_ArrayLength; i++)
		{
			mLocalTransforms[i].BinarySerialize(outputFileStream);
		}

		mMaterialRequirements.BinarySerialize(outputFileStream);
		WriteUInt32ToBinary(outputFileStream, mVertexStreams_BlockSize);
		WriteUInt32ToBinary(outputFileStream, mVertexStreams);
		mBoundingBox.BinarySerialize(outputFileStream);
		mBoundingSphere.BinarySerialize(outputFileStream);
		WriteUInt32ToBinary(outputFileStream, mEndianType);
		mPositionScale.BinarySerialize(outputFileStream);
		mPositionWScale.BinarySerialize(outputFileStream);
		mPositionOffset.BinarySerialize(outputFileStream);
		WriteFloat32ToBinary(outputFileStream, mLightmapTexelAreaPerSurfaceArea);
		mPropertyKeyBase.BinarySerialize(outputFileStream);
		WriteUInt32ToBinary(outputFileStream, mVertexCount);
		WriteUInt32ToBinary(outputFileStream, mFlags);
		WriteUInt32ToBinary(outputFileStream, mMeshPreload_BlockSize);
		WriteByteBufferToBinary(outputFileStream, mMeshPreload_BlockSize - 4, mMeshPreloadData);
		WriteUInt32ToBinary(outputFileStream, UNKNOWN1);
		WriteUInt32ToBinary(outputFileStream, UNKNOWN2);
		WriteUInt32ToBinary(outputFileStream, mVertexCountPerInstance);
		WriteUInt32ToBinary(outputFileStream, mIndexBufferCount);
		WriteUInt32ToBinary(outputFileStream, mVertexBufferCount);
		WriteUInt32ToBinary(outputFileStream, mAttributeCount);

		for (int i = 0; i < mAttributeCount; i++)
		{
			GFXPlatformAttributeParamsArray[i].BinarySerialize(outputFileStream);
		}

		for (int i = 0; i < mIndexBufferCount; i++)
		{
			mIndexBuffers[i].BinarySerialize(outputFileStream);
		}

		for (int i = 0; i < mVertexBufferCount; i++)
		{
			mVertexBuffers[i].BinarySerialize(outputFileStream);
		}
	};
};


#endif
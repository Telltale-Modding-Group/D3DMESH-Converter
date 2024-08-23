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
		this->mNameBlockSize = 0;
		this->mName = "";
		this->mVersion = 0;
		this->mToolProps = 0;
		this->mLightmapGlobalScale = 0.0f;
		this->mLightmapTexCoordVersion = 0;
		this->mLODParamCRC = {};
		this->mInternalResourcesCount = 0;
		this->mInternalResources = {};
		this->mToolPropsBlockSize = 0;
		this->mToolPropsData = 0;
		this->mHasOcclusionData = 0;
		this->mOcclusionDataBlockSize = 0;
		char* mOcclusionData = 0;
		this->mT3MeshDataBlockSize = 0;
		this->mLODs_ArrayCapacity = 0;
		this->mLODs_ArrayLength = 0;
		this->mLODs = {};
		this->mTextures_ArrayCapacity = 0;
		this->mTextures_ArrayLength = 0;
		this->mTexturesData = 0;
		this->mMaterials_ArrayCapacity = 0;
		this->mMaterials_ArrayLength = 0;
		this->mMaterialsData = 0;
		this->mMaterialOverrides_ArrayCapacity = 0;
		this->mMaterialOverrides_ArrayLength = 0;
		this->mMaterialOverridesData = 0;
		this->mBones_ArrayCapacity = 0;
		this->mBones_ArrayLength = 0;
		this->mBones = {};
		this->mLocalTransforms_ArrayCapacity = 0;
		this->mLocalTransforms_ArrayLength = 0;
		this->mLocalTransforms = {};
		this->mMaterialRequirements = {};
		this->mVertexStreams_BlockSize = 0;
		this->mVertexStreams = 0;
		this->mBoundingBox = {};
		this->mBoundingSphere = {};
		this->mEndianType = 0;
		this->mPositionScale = {};
		this->mPositionWScale = {};
		this->mPositionOffset = {};
		this->mLightmapTexelAreaPerSurfaceArea = 0.0f;
		this->mPropertyKeyBase = {};
		this->mVertexCount = 0;
		this->mFlags = 0;
		this->mMeshPreload_BlockSize = 0;
		this->mMeshPreloadData = 0;
		this->UNKNOWN1 = 0;
		this->UNKNOWN2 = 0;
		this->mVertexCountPerInstance = 0;
		this->mIndexBufferCount = 0;
		this->mVertexBufferCount = 0;
		this->mAttributeCount = 0;
		this->GFXPlatformAttributeParamsArray = {};
		this->mIndexBuffers = {};
		this->mVertexBuffers = {};
	};

	TelltaleD3DMeshHeaderV55(std::ifstream* inputFileStream)
	{
		this->mNameBlockSize = ReadUInt32FromBinary(inputFileStream);
		this->mName = ReadLengthPrefixedStringFromBinary(inputFileStream);
		this->mVersion = ReadUInt32FromBinary(inputFileStream);
		this->mToolProps = ReadInt8FromBinary(inputFileStream);
		this->mLightmapGlobalScale = ReadFloat32FromBinary(inputFileStream);
		this->mLightmapTexCoordVersion = ReadUInt32FromBinary(inputFileStream);
		this->mLODParamCRC = Symbol(inputFileStream);

		//parse the internal resources block, this was difficult to track down but this basically contains propertysets or references to resources uses (i.e. materials)
		this->mInternalResourcesCount = ReadUInt32FromBinary(inputFileStream);

		for (int mInternalResourceIndex = 0; mInternalResourceIndex < this->mInternalResourcesCount; mInternalResourceIndex++)
		{
			this->mInternalResources.push_back(TelltaleInternalResource(inputFileStream)); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)
		}

		//parse the tool property set block, this shouldn't technically have any data since this is the final shipped file.
		this->mToolPropsBlockSize = ReadUInt32FromBinary(inputFileStream);
		this->mToolPropsData = ReadByteBufferFromBinary(inputFileStream, this->mToolPropsBlockSize); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)

		//parse the occlusion data block, this contains occlusion culling information regarding the mesh.
		this->mHasOcclusionData = ReadInt8FromBinary(inputFileStream);

		//if this is true then we need to skip it (ASCII '1' is true, ASCII '0' is false)
		if (this->mHasOcclusionData == '1')
		{
			this->mOcclusionDataBlockSize = ReadUInt32FromBinary(inputFileStream);
			this->mOcclusionData = ReadByteBufferFromBinary(inputFileStream, this->mOcclusionDataBlockSize - 4); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)
		}

		//this is the start of the main T3MeshData block
		this->mT3MeshDataBlockSize = ReadUInt32FromBinary(inputFileStream);

		//parse the LODs associated with the mesh (oddly enough telltale didn't use LODs very often?)
		this->mLODs_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		this->mLODs_ArrayLength = ReadUInt32FromBinary(inputFileStream);

		for (int i = 0; i < this->mLODs_ArrayLength; i++)
		{
			this->mLODs.push_back(T3MeshLOD(inputFileStream));
		}

		//parse the textures block (NOTE: This does not contain actual texture data, just references to it)
		this->mTextures_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		this->mTextures_ArrayLength = ReadUInt32FromBinary(inputFileStream);
		this->mTexturesData = ReadByteBufferFromBinary(inputFileStream, this->mTextures_ArrayCapacity - 8); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)

		//parse the materials block
		this->mMaterials_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		this->mMaterials_ArrayLength = ReadUInt32FromBinary(inputFileStream);
		this->mMaterialsData = ReadByteBufferFromBinary(inputFileStream, this->mMaterials_ArrayCapacity - 8); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)

		//parse the materials overrides block
		this->mMaterialOverrides_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		this->mMaterialOverrides_ArrayLength = ReadUInt32FromBinary(inputFileStream);
		this->mMaterialOverridesData = ReadByteBufferFromBinary(inputFileStream, this->mMaterialOverrides_ArrayCapacity - 8); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)

		//parse the rigging bones block
		this->mBones_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		this->mBones_ArrayLength = ReadUInt32FromBinary(inputFileStream);

		for (int i = 0; i < this->mBones_ArrayLength; i++)
		{
			this->mBones.push_back(T3MeshBoneEntry(inputFileStream));
		}

		//parse the rigging bones block
		this->mLocalTransforms_ArrayCapacity = ReadUInt32FromBinary(inputFileStream);
		this->mLocalTransforms_ArrayLength = ReadUInt32FromBinary(inputFileStream);

		for (int i = 0; i < this->mLocalTransforms_ArrayLength; i++)
		{
			this->mLocalTransforms.push_back(T3MeshLocalTransformEntry(inputFileStream));
		}

		//parse other misc information in the d3dmesh header
		this->mMaterialRequirements = T3MaterialRequirements(inputFileStream);
		this->mVertexStreams_BlockSize = ReadUInt32FromBinary(inputFileStream); //value seems to always be 8
		this->mVertexStreams = ReadUInt32FromBinary(inputFileStream);
		this->mBoundingBox = BoundingBox(inputFileStream);
		this->mBoundingSphere = BoundingSphere(inputFileStream);
		this->mEndianType = ReadUInt32FromBinary(inputFileStream);
		this->mPositionScale = Vector3(inputFileStream);
		this->mPositionWScale = Vector3(inputFileStream);
		this->mPositionOffset = Vector3(inputFileStream);
		this->mLightmapTexelAreaPerSurfaceArea = ReadFloat32FromBinary(inputFileStream);
		this->mPropertyKeyBase = Symbol(inputFileStream);
		this->mVertexCount = ReadUInt32FromBinary(inputFileStream);
		this->mFlags = ReadUInt32FromBinary(inputFileStream);
		this->mMeshPreload_BlockSize = ReadUInt32FromBinary(inputFileStream);
		this->mMeshPreloadData = ReadByteBufferFromBinary(inputFileStream, this->mMeshPreload_BlockSize - 4); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)
		this->UNKNOWN1 = ReadUInt32FromBinary(inputFileStream);
		this->UNKNOWN2 = ReadUInt32FromBinary(inputFileStream);
		this->mVertexCountPerInstance = ReadUInt32FromBinary(inputFileStream);
		this->mIndexBufferCount = ReadUInt32FromBinary(inputFileStream);
		this->mVertexBufferCount = ReadUInt32FromBinary(inputFileStream);
		this->mAttributeCount = ReadUInt32FromBinary(inputFileStream);

		//parse the table of GFXPlatformAttributes, this is important as this is used during the vertex buffer parsing later to identify what buffers contain what data.
		for (int i = 0; i < this->mAttributeCount; i++)
		{
			this->GFXPlatformAttributeParamsArray.push_back(GFXPlatformAttributeParams(inputFileStream));
		}

		//parse the table of GFXBuffer data, these are "index" buffers (i.e. triangle indicies)
		for (int i = 0; i < this->mIndexBufferCount; i++)
		{
			this->mIndexBuffers.push_back(T3GFXBuffer(inputFileStream));
		}

		//parse the table of GFXBuffer data, these are "vertex" buffers (i.e. vertex position, normal, uv, etc)
		for (int i = 0; i < this->mVertexBufferCount; i++)
		{
			this->mVertexBuffers.push_back(T3GFXBuffer(inputFileStream));
		}
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteUInt32ToBinary(outputFileStream, this->mNameBlockSize);
		WriteLengthPrefixedStringToBinary(outputFileStream, this->mName);
		WriteUInt32ToBinary(outputFileStream, this->mVersion);
		WriteUInt8ToBinary(outputFileStream, this->mToolProps);
		WriteFloat32ToBinary(outputFileStream, this->mLightmapGlobalScale);
		WriteUInt32ToBinary(outputFileStream, this->mLightmapTexCoordVersion);
		this->mLODParamCRC.BinarySerialize(outputFileStream);
		WriteUInt32ToBinary(outputFileStream, this->mInternalResourcesCount);

		for (int mInternalResourceIndex = 0; mInternalResourceIndex < this->mInternalResourcesCount; mInternalResourceIndex++)
		{
			this->mInternalResources[mInternalResourceIndex].BinarySerialize(outputFileStream);
		}

		WriteUInt32ToBinary(outputFileStream, this->mToolPropsBlockSize);
		WriteByteBufferToBinary(outputFileStream, this->mToolPropsBlockSize - 4, this->mToolPropsData);
		WriteUInt8ToBinary(outputFileStream, this->mHasOcclusionData);

		//if this is true then we need to skip it (ASCII '1' is true, ASCII '0' is false)
		if (this->mHasOcclusionData == '1')
		{
			WriteUInt32ToBinary(outputFileStream, this->mOcclusionDataBlockSize);
			WriteByteBufferToBinary(outputFileStream, this->mOcclusionDataBlockSize - 4, this->mOcclusionData);
		}

		WriteUInt32ToBinary(outputFileStream, this->mT3MeshDataBlockSize);
		WriteUInt32ToBinary(outputFileStream, this->mLODs_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, this->mLODs_ArrayLength);

		for (int i = 0; i < this->mLODs_ArrayLength; i++)
		{
			this->mLODs[i].BinarySerialize(outputFileStream);
		}

		WriteUInt32ToBinary(outputFileStream, this->mTextures_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, this->mTextures_ArrayLength);
		WriteByteBufferToBinary(outputFileStream, this->mTextures_ArrayCapacity - 8, this->mTexturesData);

		WriteUInt32ToBinary(outputFileStream, this->mMaterials_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, this->mMaterials_ArrayLength);
		WriteByteBufferToBinary(outputFileStream, this->mMaterials_ArrayCapacity - 8, this->mMaterialsData);

		WriteUInt32ToBinary(outputFileStream, this->mMaterialOverrides_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, this->mMaterialOverrides_ArrayLength);
		WriteByteBufferToBinary(outputFileStream, this->mMaterialOverrides_ArrayCapacity - 8, this->mMaterialOverridesData);

		WriteUInt32ToBinary(outputFileStream, this->mBones_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, this->mBones_ArrayLength);

		for (int i = 0; i < this->mBones_ArrayLength; i++)
		{
			this->mBones[i].BinarySerialize(outputFileStream);
		}

		WriteUInt32ToBinary(outputFileStream, this->mLocalTransforms_ArrayCapacity);
		WriteUInt32ToBinary(outputFileStream, this->mLocalTransforms_ArrayLength);

		for (int i = 0; i < this->mLocalTransforms_ArrayLength; i++)
		{
			this->mLocalTransforms[i].BinarySerialize(outputFileStream);
		}

		this->mMaterialRequirements.BinarySerialize(outputFileStream);
		WriteUInt32ToBinary(outputFileStream, this->mVertexStreams_BlockSize);
		WriteUInt32ToBinary(outputFileStream, this->mVertexStreams);
		this->mBoundingBox.BinarySerialize(outputFileStream);
		this->mBoundingSphere.BinarySerialize(outputFileStream);
		WriteUInt32ToBinary(outputFileStream, this->mEndianType);
		this->mPositionScale.BinarySerialize(outputFileStream);
		this->mPositionWScale.BinarySerialize(outputFileStream);
		this->mPositionOffset.BinarySerialize(outputFileStream);
		WriteFloat32ToBinary(outputFileStream, this->mLightmapTexelAreaPerSurfaceArea);
		this->mPropertyKeyBase.BinarySerialize(outputFileStream);
		WriteUInt32ToBinary(outputFileStream, this->mVertexCount);
		WriteUInt32ToBinary(outputFileStream, this->mFlags);
		WriteUInt32ToBinary(outputFileStream, this->mMeshPreload_BlockSize);
		WriteByteBufferToBinary(outputFileStream, this->mMeshPreload_BlockSize - 4, this->mMeshPreloadData);
		WriteUInt32ToBinary(outputFileStream, this->UNKNOWN1);
		WriteUInt32ToBinary(outputFileStream, this->UNKNOWN2);
		WriteUInt32ToBinary(outputFileStream, this->mVertexCountPerInstance);
		WriteUInt32ToBinary(outputFileStream, this->mIndexBufferCount);
		WriteUInt32ToBinary(outputFileStream, this->mVertexBufferCount);
		WriteUInt32ToBinary(outputFileStream, this->mAttributeCount);

		for (int i = 0; i < this->mAttributeCount; i++)
		{
			this->GFXPlatformAttributeParamsArray[i].BinarySerialize(outputFileStream);
		}

		for (int i = 0; i < this->mIndexBufferCount; i++)
		{
			this->mIndexBuffers[i].BinarySerialize(outputFileStream);
		}

		for (int i = 0; i < this->mVertexBufferCount; i++)
		{
			this->mVertexBuffers[i].BinarySerialize(outputFileStream);
		}
	};
};


#endif
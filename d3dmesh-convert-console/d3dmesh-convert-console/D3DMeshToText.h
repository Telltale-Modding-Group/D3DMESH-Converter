#pragma once
#ifndef TEXT_FILE_D3DMESH_H
#define TEXT_FILE_D3DMESH_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "TelltaleD3DMeshFileV55.h"

//||||||||||||||||||||||||||||| TEXT FILE D3DMESH |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TEXT FILE D3DMESH |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TEXT FILE D3DMESH |||||||||||||||||||||||||||||

static void WriteStringToOutputTextFile(std::ofstream* testOutputTextFile, const std::string value)
{
	testOutputTextFile->write(value.c_str(), value.length());
}

static void WriteD3DMeshToText(std::string filename, TelltaleD3DMeshFileV55 d3dmeshFile)
{
	std::string testOutputTextFilePath = "Output/" + filename + "_EXTRACTED_MESH_DATA.txt";

	std::ofstream testOutputTextFile;
	testOutputTextFile.open(testOutputTextFilePath);

	WriteStringToOutputTextFile(&testOutputTextFile, "|||||||||||||||||||||| 6VSM HEADER |||||||||||||||||||||| \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "|||||||||||||||||||||| 6VSM HEADER |||||||||||||||||||||| \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "|||||||||||||||||||||| 6VSM HEADER |||||||||||||||||||||| \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[4 BYTES] mMetaStreamVersion: " + d3dmeshFile.metaHeader.mMetaStreamVersion + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mDefaultSectionChunkSize: " + std::to_string(d3dmeshFile.metaHeader.mDefaultSectionChunkSize) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mDebugSectionChunkSize: " + std::to_string(d3dmeshFile.metaHeader.mDebugSectionChunkSize) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mAsyncSectionChunkSize: " + std::to_string(d3dmeshFile.metaHeader.mAsyncSectionChunkSize) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mClassNamesLength: " + std::to_string(d3dmeshFile.metaHeader.mClassNamesLength) + "\n");

	for (int mClassNameIndex = 0; mClassNameIndex < d3dmeshFile.metaHeader.mClassNamesLength; mClassNameIndex++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	Class Name " + std::to_string(mClassNameIndex) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		mTypeNameCRC \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "			[UINT64] mCrc64: " + std::to_string(d3dmeshFile.metaHeader.mClassNames[mClassNameIndex].mTypeNameCRC.mCrc64) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mVersionCRC: " + std::to_string(d3dmeshFile.metaHeader.mClassNames[mClassNameIndex].mVersionCRC) + "\n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "|||||||||||||||||||||| D3DMESH HEADER |||||||||||||||||||||| \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "|||||||||||||||||||||| D3DMESH HEADER |||||||||||||||||||||| \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "|||||||||||||||||||||| D3DMESH HEADER |||||||||||||||||||||| \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mNameBlockSize: " + std::to_string(d3dmeshFile.d3dmeshHeader.mNameBlockSize) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mNameLength: " + std::to_string(d3dmeshFile.d3dmeshHeader.mName.length()) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[" + std::to_string(d3dmeshFile.d3dmeshHeader.mName.length()) + " BYTES] mName: " + d3dmeshFile.d3dmeshHeader.mName + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mVersion: " + std::to_string(d3dmeshFile.d3dmeshHeader.mVersion) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[BYTE] mToolProps: " + std::to_string(d3dmeshFile.d3dmeshHeader.mToolProps) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[FLOAT] mLightmapGlobalScale: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLightmapGlobalScale) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mLightmapTexCoordVersion: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLightmapTexCoordVersion) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "mLODParamCRC \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "	[UINT64] mCrc64: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODParamCRC.mCrc64) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mInternalResourcesCount: " + std::to_string(d3dmeshFile.d3dmeshHeader.mInternalResourcesCount) + "\n");

	for (int mInternalResourceIndex = 0; mInternalResourceIndex < d3dmeshFile.d3dmeshHeader.mInternalResourcesCount; mInternalResourceIndex++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	InternalResource " + std::to_string(mInternalResourceIndex) + " \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		mInternalResourceSymbol \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "			[UINT64] mCrc64: " + std::to_string(d3dmeshFile.d3dmeshHeader.mInternalResources[mInternalResourceIndex].mInternalResourceSymbol.mCrc64) + "\n");

		WriteStringToOutputTextFile(&testOutputTextFile, "		mInternalResourceType \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "			[UINT64] mCrc64: " + std::to_string(d3dmeshFile.d3dmeshHeader.mInternalResources[mInternalResourceIndex].mInternalResourceType.mCrc64) + "\n");

		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mInternalResourceBlockSize: " + std::to_string(d3dmeshFile.d3dmeshHeader.mInternalResources[mInternalResourceIndex].mInternalResourceBlockSize) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[" + std::to_string(d3dmeshFile.d3dmeshHeader.mInternalResources[mInternalResourceIndex].mInternalResourceBlockSize) + " BYTES] mInternalResourceData \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mToolPropsBlockSize: " + std::to_string(d3dmeshFile.d3dmeshHeader.mToolPropsBlockSize) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[" + std::to_string(d3dmeshFile.d3dmeshHeader.mToolPropsBlockSize) + " BYTES] mToolPropsData \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[BYTE] mHasOcclusionData: " + std::to_string(d3dmeshFile.d3dmeshHeader.mHasOcclusionData) + "\n");

	if (d3dmeshFile.d3dmeshHeader.mHasOcclusionData == '1') //if this is true then we need to skip it (ASCII '1' is true, ASCII '0' is false)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mOcclusionDataBlockSize: " + std::to_string(d3dmeshFile.d3dmeshHeader.mOcclusionDataBlockSize) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "[" + std::to_string(d3dmeshFile.d3dmeshHeader.mOcclusionDataBlockSize) + " BYTES] mOcclusionData \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "|||||||||||||||||||||| D3DMESH HEADER - T3MeshData |||||||||||||||||||||| \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "|||||||||||||||||||||| D3DMESH HEADER - T3MeshData |||||||||||||||||||||| \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "|||||||||||||||||||||| D3DMESH HEADER - T3MeshData |||||||||||||||||||||| \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mT3MeshDataBlockSize: " + std::to_string(d3dmeshFile.d3dmeshHeader.mT3MeshDataBlockSize) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mLODs_ArrayCapacity: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs_ArrayCapacity) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mLODs_ArrayLength: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs_ArrayLength) + "\n");

	for (int mLODIndex = 0; mLODIndex < d3dmeshFile.d3dmeshHeader.mLODs_ArrayLength; mLODIndex++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	T3MeshLOD " + std::to_string(mLODIndex) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mBatches0_ArrayCapacity: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0_ArrayCapacity) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mBatches0_ArrayLength: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0_ArrayLength) + "\n");

		for (int mBatches0Index = 0; mBatches0Index < d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0_ArrayLength; mBatches0Index++)
		{
			WriteStringToOutputTextFile(&testOutputTextFile, "			T3MeshBatch " + std::to_string(mBatches0Index) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				mBoundingBox \n");
			WriteStringToOutputTextFile(&testOutputTextFile, "					mMin \n");
			WriteStringToOutputTextFile(&testOutputTextFile, "						[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mBoundingBox.mMin.x) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "						[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mBoundingBox.mMin.y) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "						[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mBoundingBox.mMin.z) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "					mMax \n");
			WriteStringToOutputTextFile(&testOutputTextFile, "						[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mBoundingBox.mMax.x) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "						[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mBoundingBox.mMax.y) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "						[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mBoundingBox.mMax.z) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				mBoundingSphere \n");
			WriteStringToOutputTextFile(&testOutputTextFile, "					[UINT32] mBlockSize: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mBoundingSphere.mBlockSize) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "					mCenter \n");
			WriteStringToOutputTextFile(&testOutputTextFile, "						[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mBoundingSphere.mCenter.x) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "						[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mBoundingSphere.mCenter.y) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "						[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mBoundingSphere.mCenter.z) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "					[FLOAT] mRadius: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mBoundingSphere.mRadius) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mBatchUsage: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mBatchUsage) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mMinVertIndex: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mMinVertIndex) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mMaxVertIndex: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mMaxVertIndex) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mBaseIndex: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mBaseIndex) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mStartIndex: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mStartIndex) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mNumPrimitives: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mNumPrimitives) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mNumIndices: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mNumIndices) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mTextureIndices: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mTextureIndices) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mMaterialIndex: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mMaterialIndex) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mAdjacencyStartIndex: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches0Index].mAdjacencyStartIndex) + "\n");
		}

		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mBatches1_ArrayCapacity: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches1_ArrayCapacity) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mBatches1_ArrayLength: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches1_ArrayLength) + "\n");

		for (int mBatches1Index = 0; mBatches1Index < d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches1_ArrayLength; mBatches1Index++)
		{
			WriteStringToOutputTextFile(&testOutputTextFile, "			T3MeshBatch " + std::to_string(mBatches1Index) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				mBoundingBox \n");
			WriteStringToOutputTextFile(&testOutputTextFile, "					mMin \n");
			WriteStringToOutputTextFile(&testOutputTextFile, "						[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mBoundingBox.mMin.x) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "						[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mBoundingBox.mMin.y) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "						[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mBoundingBox.mMin.z) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "					mMax \n");
			WriteStringToOutputTextFile(&testOutputTextFile, "						[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mBoundingBox.mMax.x) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "						[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mBoundingBox.mMax.y) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "						[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mBoundingBox.mMax.z) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				mBoundingSphere \n");
			WriteStringToOutputTextFile(&testOutputTextFile, "					[UINT32] mBlockSize: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mBoundingSphere.mBlockSize) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "					mCenter \n");
			WriteStringToOutputTextFile(&testOutputTextFile, "						[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mBoundingSphere.mCenter.x) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "						[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mBoundingSphere.mCenter.y) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "						[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mBoundingSphere.mCenter.z) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "					[FLOAT] mRadius: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mBoundingSphere.mRadius) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mBatchUsage: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mBatchUsage) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mMinVertIndex: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mMinVertIndex) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mMaxVertIndex: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mMaxVertIndex) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mBaseIndex: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mBaseIndex) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mStartIndex: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mStartIndex) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mNumPrimitives: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mNumPrimitives) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mNumIndices: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mNumIndices) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mTextureIndices: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mTextureIndices) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mMaterialIndex: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mMaterialIndex) + "\n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT32] mAdjacencyStartIndex: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBatches0[mBatches1Index].mAdjacencyStartIndex) + "\n");
		}

		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mVertexStreams_BlockSize: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mVertexStreams_BlockSize) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mVertexStreams: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mVertexStreams) + "\n");

		WriteStringToOutputTextFile(&testOutputTextFile, "		mBoundingBox \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "			mMin \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBoundingBox.mMin.x) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBoundingBox.mMin.y) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBoundingBox.mMin.z) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "			mMax \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBoundingBox.mMax.x) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBoundingBox.mMax.y) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBoundingBox.mMax.z) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		mBoundingSphere \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "			[UINT32] mBlockSize: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBoundingSphere.mBlockSize) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				mCenter \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "					[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBoundingSphere.mCenter.x) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "					[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBoundingSphere.mCenter.y) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "					[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBoundingSphere.mCenter.z) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] mRadius: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBoundingSphere.mRadius) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mFlags: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mFlags) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mVertexStateIndex: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mVertexStateIndex) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mNumPrimitives: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mNumPrimitives) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mNumBatches: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mNumBatches) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mVertexStart: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mVertexStart) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mVertexCount: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mVertexCount) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mTextureAtlasWidth: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mTextureAtlasWidth) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mTextureAtlasHeight: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mTextureAtlasHeight) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[FLOAT] mPixelSize: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mPixelSize) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[FLOAT] mDistance: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mDistance) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mBones_ArrayCapacity: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBones_ArrayCapacity) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mBones_ArrayLength: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBones_ArrayLength) + "\n");

		for (int mBoneIndex = 0; mBoneIndex < d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBones_ArrayLength; mBoneIndex++)
		{
			WriteStringToOutputTextFile(&testOutputTextFile, "			mBone " + std::to_string(mBoneIndex) + " \n");
			WriteStringToOutputTextFile(&testOutputTextFile, "				[UINT64] mCrc64: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLODs[mLODIndex].mBones[mBoneIndex].mCrc64) + "\n");
		}
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mTextures_ArrayCapacity: " + std::to_string(d3dmeshFile.d3dmeshHeader.mTextures_ArrayCapacity) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mTextures_ArrayLength: " + std::to_string(d3dmeshFile.d3dmeshHeader.mTextures_ArrayLength) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[" + std::to_string(d3dmeshFile.d3dmeshHeader.mTextures_ArrayCapacity - 8) + " BYTES] mTexturesData \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mMaterials_ArrayCapacity: " + std::to_string(d3dmeshFile.d3dmeshHeader.mMaterials_ArrayCapacity) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mMaterials_ArrayLength: " + std::to_string(d3dmeshFile.d3dmeshHeader.mMaterials_ArrayLength) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[" + std::to_string(d3dmeshFile.d3dmeshHeader.mMaterials_ArrayCapacity - 8) + " BYTES] mMaterialsData \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mMaterialOverrides_ArrayCapacity: " + std::to_string(d3dmeshFile.d3dmeshHeader.mMaterialOverrides_ArrayCapacity) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mMaterialOverrides_ArrayLength: " + std::to_string(d3dmeshFile.d3dmeshHeader.mMaterialOverrides_ArrayLength) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[" + std::to_string(d3dmeshFile.d3dmeshHeader.mMaterialOverrides_ArrayCapacity - 8) + " BYTES] mMaterialOverridesData \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mBones_ArrayCapacity: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBones_ArrayCapacity) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mBones_ArrayLength: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBones_ArrayLength) + "\n");

	for (int mBoneIndex = 0; mBoneIndex < d3dmeshFile.d3dmeshHeader.mBones_ArrayLength; mBoneIndex++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	T3MeshBoneEntry " + std::to_string(mBoneIndex) + " \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		mBoneName \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "			[UINT64] mCrc64: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBones[mBoneIndex].mBoneName.mCrc64) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		mBoundingBox \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "			mMin \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBones[mBoneIndex].mBoneName.mCrc64) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBones[mBoneIndex].mBoundingBox.mMin.y) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBones[mBoneIndex].mBoundingBox.mMin.z) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "			mMax \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBones[mBoneIndex].mBoundingBox.mMax.x) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBones[mBoneIndex].mBoundingBox.mMax.y) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBones[mBoneIndex].mBoundingBox.mMax.z) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		mBoundingSphere \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "			[UINT32] mBlockSize: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBones[mBoneIndex].mBoundingSphere.mBlockSize) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				mCenter \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "					[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBones[mBoneIndex].mBoundingSphere.mCenter.x) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "					[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBones[mBoneIndex].mBoundingSphere.mCenter.y) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "					[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBones[mBoneIndex].mBoundingSphere.mCenter.z) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] mRadius: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBones[mBoneIndex].mBoundingSphere.mRadius) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mNumVerts: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBones[mBoneIndex].mNumVerts) + "\n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mLocalTransforms_ArrayCapacity: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLocalTransforms_ArrayCapacity) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mLocalTransforms_ArrayLength: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLocalTransforms_ArrayLength) + "\n");

	for (int mLocalTransformIndex = 0; mLocalTransformIndex < d3dmeshFile.d3dmeshHeader.mLocalTransforms_ArrayLength; mLocalTransformIndex++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	T3MeshLocalTransformEntry " + std::to_string(mLocalTransformIndex) + " \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		Transform \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "			[UINT32] mBlockSize: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLocalTransforms[mLocalTransformIndex].mTransform.mBlockSize) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "			mRot \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLocalTransforms[mLocalTransformIndex].mTransform.mRot.x) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLocalTransforms[mLocalTransformIndex].mTransform.mRot.y) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLocalTransforms[mLocalTransformIndex].mTransform.mRot.z) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] w: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLocalTransforms[mLocalTransformIndex].mTransform.mRot.w) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "			mTrans \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLocalTransforms[mLocalTransformIndex].mTransform.mTrans.x) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLocalTransforms[mLocalTransformIndex].mTransform.mTrans.y) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLocalTransforms[mLocalTransformIndex].mTransform.mTrans.z) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mCameraFacingType: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLocalTransforms[mLocalTransformIndex].mCameraFacingType) + "\n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "	T3MaterialRequirements \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mMaterialRequirements_BlockSize " + std::to_string(d3dmeshFile.d3dmeshHeader.mMaterialRequirements.mMaterialRequirements_BlockSize) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mPasses_BlockSize " + std::to_string(d3dmeshFile.d3dmeshHeader.mMaterialRequirements.mPasses_BlockSize) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mPasses " + std::to_string(d3dmeshFile.d3dmeshHeader.mMaterialRequirements.mPasses) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mChannels_BlockSize " + std::to_string(d3dmeshFile.d3dmeshHeader.mMaterialRequirements.mChannels_BlockSize) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mChannels1 " + std::to_string(d3dmeshFile.d3dmeshHeader.mMaterialRequirements.mChannels1) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mChannels2 " + std::to_string(d3dmeshFile.d3dmeshHeader.mMaterialRequirements.mChannels2) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mInputs_BlockSize " + std::to_string(d3dmeshFile.d3dmeshHeader.mMaterialRequirements.mInputs_BlockSize) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mInputs1 " + std::to_string(d3dmeshFile.d3dmeshHeader.mMaterialRequirements.mInputs1) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mInputs2 " + std::to_string(d3dmeshFile.d3dmeshHeader.mMaterialRequirements.mInputs2) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mInputs3 " + std::to_string(d3dmeshFile.d3dmeshHeader.mMaterialRequirements.mInputs3) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mVertexStreams_BlockSize: " + std::to_string(d3dmeshFile.d3dmeshHeader.mVertexStreams_BlockSize) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mVertexStreams: " + std::to_string(d3dmeshFile.d3dmeshHeader.mVertexStreams) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "	mBoundingBox \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		mMin \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "			[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBoundingBox.mMin.x) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "			[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBoundingBox.mMin.y) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "			[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBoundingBox.mMin.z) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		mMax \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "			[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBoundingBox.mMax.x) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "			[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBoundingBox.mMax.y) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "			[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBoundingBox.mMax.z) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "	mBoundingSphere \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mBlockSize: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBoundingSphere.mBlockSize) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "			mCenter \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBoundingSphere.mCenter.x) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBoundingSphere.mCenter.y) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "				[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBoundingSphere.mCenter.z) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "			[FLOAT] mRadius: " + std::to_string(d3dmeshFile.d3dmeshHeader.mBoundingSphere.mRadius) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mEndianType: " + std::to_string(d3dmeshFile.d3dmeshHeader.mEndianType) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "	mPositionScale \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mPositionScale.x) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mPositionScale.y) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mPositionScale.z) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "	mPositionWScale \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mPositionWScale.x) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mPositionWScale.y) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mPositionWScale.z) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "	mPositionOffset \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[FLOAT] x: " + std::to_string(d3dmeshFile.d3dmeshHeader.mPositionOffset.x) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[FLOAT] y: " + std::to_string(d3dmeshFile.d3dmeshHeader.mPositionOffset.y) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "		[FLOAT] z: " + std::to_string(d3dmeshFile.d3dmeshHeader.mPositionOffset.z) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[FLOAT] mLightmapTexelAreaPerSurfaceArea: " + std::to_string(d3dmeshFile.d3dmeshHeader.mLightmapTexelAreaPerSurfaceArea) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT64] mPropertyKeyBase: " + std::to_string(d3dmeshFile.d3dmeshHeader.mPropertyKeyBase.mCrc64) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mVertexCount: " + std::to_string(d3dmeshFile.d3dmeshHeader.mVertexCount) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mFlags: " + std::to_string(d3dmeshFile.d3dmeshHeader.mFlags) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mMeshPreload_BlockSize: " + std::to_string(d3dmeshFile.d3dmeshHeader.mMeshPreload_BlockSize) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[" + std::to_string(d3dmeshFile.d3dmeshHeader.mMeshPreload_BlockSize - 4) + " BYTES] mMeshPreloadData \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] UNKNOWN1: " + std::to_string(d3dmeshFile.d3dmeshHeader.UNKNOWN1) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] UNKNOWN2: " + std::to_string(d3dmeshFile.d3dmeshHeader.UNKNOWN2) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mVertexCountPerInstance: " + std::to_string(d3dmeshFile.d3dmeshHeader.mVertexCountPerInstance) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mIndexBufferCount: " + std::to_string(d3dmeshFile.d3dmeshHeader.mIndexBufferCount) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mVertexBufferCount: " + std::to_string(d3dmeshFile.d3dmeshHeader.mVertexBufferCount) + "\n");
	WriteStringToOutputTextFile(&testOutputTextFile, "[UINT32] mAttributeCount: " + std::to_string(d3dmeshFile.d3dmeshHeader.mAttributeCount) + "\n");

	for (int mAttributeIndex = 0; mAttributeIndex < d3dmeshFile.d3dmeshHeader.mAttributeCount; mAttributeIndex++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	GFXPlatformAttributeParams " + std::to_string(mAttributeIndex) + " \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[INT32] mAttribute: " + std::to_string(d3dmeshFile.d3dmeshHeader.GFXPlatformAttributeParamsArray[mAttributeIndex].mAttribute) + " | " + GetGFXPlatformVertexAttributeName(d3dmeshFile.d3dmeshHeader.GFXPlatformAttributeParamsArray[mAttributeIndex].mAttribute) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[INT32] mFormat: " + std::to_string(d3dmeshFile.d3dmeshHeader.GFXPlatformAttributeParamsArray[mAttributeIndex].mFormat) + " | " + GetGFXPlatformFormatName(d3dmeshFile.d3dmeshHeader.GFXPlatformAttributeParamsArray[mAttributeIndex].mFormat) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mAttributeIndex: " + std::to_string(d3dmeshFile.d3dmeshHeader.GFXPlatformAttributeParamsArray[mAttributeIndex].mAttributeIndex) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mBufferIndex: " + std::to_string(d3dmeshFile.d3dmeshHeader.GFXPlatformAttributeParamsArray[mAttributeIndex].mBufferIndex) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mBufferOffset: " + std::to_string(d3dmeshFile.d3dmeshHeader.GFXPlatformAttributeParamsArray[mAttributeIndex].mBufferOffset) + "\n");
	}

	for (int mIndexBufferIndex = 0; mIndexBufferIndex < d3dmeshFile.d3dmeshHeader.mIndexBufferCount; mIndexBufferIndex++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	T3GFXBuffer " + std::to_string(mIndexBufferIndex) + " \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mResourceUsage: " + std::to_string(d3dmeshFile.d3dmeshHeader.mIndexBuffers[mIndexBufferIndex].mResourceUsage) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[INT32] mBufferFormat: " + std::to_string(d3dmeshFile.d3dmeshHeader.mIndexBuffers[mIndexBufferIndex].mBufferFormat) + " | " + GetGFXPlatformFormatName(d3dmeshFile.d3dmeshHeader.mIndexBuffers[mIndexBufferIndex].mBufferFormat) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mBufferUsage: " + std::to_string(d3dmeshFile.d3dmeshHeader.mIndexBuffers[mIndexBufferIndex].mBufferUsage) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mCount: " + std::to_string(d3dmeshFile.d3dmeshHeader.mIndexBuffers[mIndexBufferIndex].mCount) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mStride: " + std::to_string(d3dmeshFile.d3dmeshHeader.mIndexBuffers[mIndexBufferIndex].mStride) + "\n");
	}

	for (int mVertexBufferIndex = 0; mVertexBufferIndex < d3dmeshFile.d3dmeshHeader.mVertexBufferCount; mVertexBufferIndex++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	T3GFXBuffer " + std::to_string(mVertexBufferIndex) + " \n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mResourceUsage: " + std::to_string(d3dmeshFile.d3dmeshHeader.mVertexBuffers[mVertexBufferIndex].mResourceUsage) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[INT32] mBufferFormat: " + std::to_string(d3dmeshFile.d3dmeshHeader.mVertexBuffers[mVertexBufferIndex].mBufferFormat) + " | " + GetGFXPlatformFormatName(d3dmeshFile.d3dmeshHeader.mVertexBuffers[mVertexBufferIndex].mBufferFormat) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mBufferUsage: " + std::to_string(d3dmeshFile.d3dmeshHeader.mVertexBuffers[mVertexBufferIndex].mBufferUsage) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mCount: " + std::to_string(d3dmeshFile.d3dmeshHeader.mVertexBuffers[mVertexBufferIndex].mCount) + "\n");
		WriteStringToOutputTextFile(&testOutputTextFile, "		[UINT32] mStride: " + std::to_string(d3dmeshFile.d3dmeshHeader.mVertexBuffers[mVertexBufferIndex].mStride) + "\n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "|||||||||||||||||||||| D3DMESH DATA (INDEX BUFFERS) |||||||||||||||||||||| \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "|||||||||||||||||||||| D3DMESH DATA (INDEX BUFFERS) |||||||||||||||||||||| \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "|||||||||||||||||||||| D3DMESH DATA (INDEX BUFFERS) |||||||||||||||||||||| \n");

	WriteStringToOutputTextFile(&testOutputTextFile, "mIndexBuffer0 (" + std::to_string(d3dmeshFile.d3dmeshData.indexBuffer0.size()) + ") \n");

	for (int mBufferDataIndex = 0; mBufferDataIndex < d3dmeshFile.d3dmeshData.indexBuffer0.size(); mBufferDataIndex++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[UINT16] Value: " + std::to_string(d3dmeshFile.d3dmeshData.indexBuffer0[mBufferDataIndex]) + "\n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "mIndexBuffer1 (" + std::to_string(d3dmeshFile.d3dmeshData.indexBuffer1.size()) + ") \n");

	for (int mBufferDataIndex = 0; mBufferDataIndex < d3dmeshFile.d3dmeshData.indexBuffer1.size(); mBufferDataIndex++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[UINT16] Value: " + std::to_string(d3dmeshFile.d3dmeshData.indexBuffer1[mBufferDataIndex]) + "\n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "mIndexBuffer2 (" + std::to_string(d3dmeshFile.d3dmeshData.indexBuffer2.size()) + ") \n");

	for (int mBufferDataIndex = 0; mBufferDataIndex < d3dmeshFile.d3dmeshData.indexBuffer2.size(); mBufferDataIndex++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[UINT16] Value: " + std::to_string(d3dmeshFile.d3dmeshData.indexBuffer2[mBufferDataIndex]) + "\n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "mIndexBuffer3 (" + std::to_string(d3dmeshFile.d3dmeshData.indexBuffer3.size()) + ") \n");

	for (int mBufferDataIndex = 0; mBufferDataIndex < d3dmeshFile.d3dmeshData.indexBuffer3.size(); mBufferDataIndex++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[UINT16] Value: " + std::to_string(d3dmeshFile.d3dmeshData.indexBuffer3[mBufferDataIndex]) + "\n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "mIndexBuffer4 (" + std::to_string(d3dmeshFile.d3dmeshData.indexBuffer4.size()) + ") \n");

	for (int mBufferDataIndex = 0; mBufferDataIndex < d3dmeshFile.d3dmeshData.indexBuffer4.size(); mBufferDataIndex++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[UINT16] Value: " + std::to_string(d3dmeshFile.d3dmeshData.indexBuffer4[mBufferDataIndex]) + "\n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "mIndexBuffer5 (" + std::to_string(d3dmeshFile.d3dmeshData.indexBuffer5.size()) + ") \n");

	for (int mBufferDataIndex = 0; mBufferDataIndex < d3dmeshFile.d3dmeshData.indexBuffer5.size(); mBufferDataIndex++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[UINT16] Value: " + std::to_string(d3dmeshFile.d3dmeshData.indexBuffer5[mBufferDataIndex]) + "\n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "mIndexBuffer6 (" + std::to_string(d3dmeshFile.d3dmeshData.indexBuffer6.size()) + ") \n");

	for (int mBufferDataIndex = 0; mBufferDataIndex < d3dmeshFile.d3dmeshData.indexBuffer6.size(); mBufferDataIndex++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[UINT16] Value: " + std::to_string(d3dmeshFile.d3dmeshData.indexBuffer6[mBufferDataIndex]) + "\n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "mIndexBuffer7 (" + std::to_string(d3dmeshFile.d3dmeshData.indexBuffer7.size()) + ") \n");

	for (int mBufferDataIndex = 0; mBufferDataIndex < d3dmeshFile.d3dmeshData.indexBuffer7.size(); mBufferDataIndex++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[UINT16] Value: " + std::to_string(d3dmeshFile.d3dmeshData.indexBuffer7[mBufferDataIndex]) + "\n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "|||||||||||||||||||||| D3DMESH DATA (VERTEX BUFFERS) |||||||||||||||||||||| \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "|||||||||||||||||||||| D3DMESH DATA (VERTEX BUFFERS) |||||||||||||||||||||| \n");
	WriteStringToOutputTextFile(&testOutputTextFile, "|||||||||||||||||||||| D3DMESH DATA (VERTEX BUFFERS) |||||||||||||||||||||| \n");

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexPositions (" + std::to_string(d3dmeshFile.d3dmeshData.vertexPositions.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexPositions.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) Position: [X: " + std::to_string(d3dmeshFile.d3dmeshData.vertexPositions[j].x) + " Y: " + std::to_string(d3dmeshFile.d3dmeshData.vertexPositions[j].y) + " Z: " + std::to_string(d3dmeshFile.d3dmeshData.vertexPositions[j].z) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexNormals0 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexNormals0.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexNormals0.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) Normal 0: [X: " + std::to_string(d3dmeshFile.d3dmeshData.vertexNormals0[j].x) + " Y: " + std::to_string(d3dmeshFile.d3dmeshData.vertexNormals0[j].y) + " Z: " + std::to_string(d3dmeshFile.d3dmeshData.vertexNormals0[j].z) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexNormals1 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexNormals1.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexNormals1.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) Normal 1: [X: " + std::to_string(d3dmeshFile.d3dmeshData.vertexNormals1[j].x) + " Y: " + std::to_string(d3dmeshFile.d3dmeshData.vertexNormals1[j].y) + " Z: " + std::to_string(d3dmeshFile.d3dmeshData.vertexNormals1[j].z) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexNormals2 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexNormals2.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexNormals2.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) Normal 2: [X: " + std::to_string(d3dmeshFile.d3dmeshData.vertexNormals2[j].x) + " Y: " + std::to_string(d3dmeshFile.d3dmeshData.vertexNormals2[j].y) + " Z: " + std::to_string(d3dmeshFile.d3dmeshData.vertexNormals2[j].z) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexNormals3 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexNormals3.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexNormals3.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) Normal 2: [X: " + std::to_string(d3dmeshFile.d3dmeshData.vertexNormals3[j].x) + " Y: " + std::to_string(d3dmeshFile.d3dmeshData.vertexNormals3[j].y) + " Z: " + std::to_string(d3dmeshFile.d3dmeshData.vertexNormals3[j].z) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexTangents (" + std::to_string(d3dmeshFile.d3dmeshData.vertexTangents.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexTangents.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) Tangent: [X: " + std::to_string(d3dmeshFile.d3dmeshData.vertexTangents[j].x) + " Y: " + std::to_string(d3dmeshFile.d3dmeshData.vertexTangents[j].y) + " Z: " + std::to_string(d3dmeshFile.d3dmeshData.vertexTangents[j].z) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexUVs0 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs0.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexUVs0.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) UV0: [X: " + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs0[j].x) + " Y: " + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs0[j].y) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexUVs1 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs1.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexUVs1.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) UV1: [X: " + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs1[j].x) + " Y: " + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs1[j].y) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexUVs2 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs2.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexUVs2.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) UV2: [X: " + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs2[j].x) + " Y: " + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs2[j].y) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexUVs3 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs3.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexUVs3.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) UV3: [X: " + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs3[j].x) + " Y: " + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs3[j].y) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexUVs4 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs4.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexUVs4.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) UV4: [X: " + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs4[j].x) + " Y: " + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs4[j].y) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexUVs5 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs5.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexUVs5.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) UV5: [X: " + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs5[j].x) + " Y: " + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs5[j].y) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexUVs6 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs6.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexUVs6.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) UV6: [X: " + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs6[j].x) + " Y: " + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs6[j].y) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexUVs7 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs7.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexUVs7.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) UV6: [X: " + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs7[j].x) + " Y: " + std::to_string(d3dmeshFile.d3dmeshData.vertexUVs7[j].y) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexColors0 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexColors0.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexColors0.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) Color0: [R: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors0[j].x) + " G: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors0[j].y) + " B: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors0[j].z) + " A: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors0[j].w) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexColors1 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexColors1.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexColors1.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) Color1: [R: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors1[j].x) + " G: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors1[j].y) + " B: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors1[j].z) + " A: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors1[j].w) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexColors2 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexColors2.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexColors2.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) Color2: [R: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors2[j].x) + " G: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors2[j].y) + " B: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors2[j].z) + " A: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors2[j].w) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexColors3 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexColors3.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexColors3.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) Color3: [R: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors3[j].x) + " G: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors3[j].y) + " B: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors3[j].z) + " A: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors3[j].w) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexColors4 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexColors4.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexColors4.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) Color4: [R: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors4[j].x) + " G: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors4[j].y) + " B: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors4[j].z) + " A: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors4[j].w) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexColors5 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexColors5.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexColors5.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) Color5: [R: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors5[j].x) + " G: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors5[j].y) + " B: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors5[j].z) + " A: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors5[j].w) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexColors6 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexColors6.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexColors6.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) Color6: [R: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors6[j].x) + " G: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors6[j].y) + " B: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors6[j].z) + " A: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors6[j].w) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexColors7 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexColors7.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexColors7.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) Color7: [R: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors7[j].x) + " G: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors7[j].y) + " B: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors7[j].z) + " A: " + std::to_string(d3dmeshFile.d3dmeshData.vertexColors7[j].w) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexBlendIndex0 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexBlendIndex0.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexBlendIndex0.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[UINT32] (Unpacked) BlendIndex0: [X: " + std::to_string(d3dmeshFile.d3dmeshData.vertexBlendIndex0[j].x) + " Y: " + std::to_string(d3dmeshFile.d3dmeshData.vertexBlendIndex0[j].y) + " Z: " + std::to_string(d3dmeshFile.d3dmeshData.vertexBlendIndex0[j].z) + " W: " + std::to_string(d3dmeshFile.d3dmeshData.vertexBlendIndex0[j].w) + "] \n");
	}

	WriteStringToOutputTextFile(&testOutputTextFile, "vertexBlendWeight0 (" + std::to_string(d3dmeshFile.d3dmeshData.vertexBlendWeight0.size()) + ") \n");

	for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexBlendWeight0.size(); j++)
	{
		WriteStringToOutputTextFile(&testOutputTextFile, "	[FLOAT] (Unpacked) BlendWeight0: [X: " + std::to_string(d3dmeshFile.d3dmeshData.vertexBlendWeight0[j].x) + " Y: " + std::to_string(d3dmeshFile.d3dmeshData.vertexBlendWeight0[j].y) + " Z: " + std::to_string(d3dmeshFile.d3dmeshData.vertexBlendWeight0[j].z) + "] \n");
	}

	testOutputTextFile.close();
}

#endif
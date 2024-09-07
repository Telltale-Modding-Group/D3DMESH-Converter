#pragma once
#ifndef ASSIMP_TO_D3DMESH_V1_H
#define ASSIMP_TO_D3DMESH_V1_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: ASSIMP Library
#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>

//Standard C++ Library
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <stdlib.h>

//Custom
#include "../../CustomTypes/FileEntry.h"
#include "../../Telltale/DataTypes/TelltaleD3DMeshFileV55.h"
#include "../../Json.h"
#include "../../AssimpHelper.h"

//||||||||||||||||||||||||||||| ASSIMP TO D3DMESH DATA V1 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| ASSIMP TO D3DMESH DATA V1 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| ASSIMP TO D3DMESH DATA V1 |||||||||||||||||||||||||||||

static void ConvertAssimpToD3DMeshDataV1(FileEntry* d3dmeshJsonFilePath, FileEntry* assimpFilePath, std::string outputPath)
{
	//||||||||||||||||||||||||||||| READ D3DMESH JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| READ D3DMESH JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| READ D3DMESH JSON |||||||||||||||||||||||||||||
	std::ifstream d3dmeshJsonInputFileStream;
	d3dmeshJsonInputFileStream.open(d3dmeshJsonFilePath->filePath, std::fstream::in | std::fstream::binary);

	nlohmann::ordered_json readJson;
	d3dmeshJsonInputFileStream >> readJson;

	TelltaleD3DMeshFileV55 parsedD3DMesh = readJson.template get<TelltaleD3DMeshFileV55>();

	d3dmeshJsonInputFileStream.close();

	//||||||||||||||||||||||||||||| READ ASSIMP MESH |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| READ ASSIMP MESH |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| READ ASSIMP MESH |||||||||||||||||||||||||||||
	Assimp::Importer assimpImporter;

	unsigned int assimpImportFlags = aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_GenBoundingBoxes | aiProcess_SortByPType | aiProcess_JoinIdenticalVertices;
	const aiScene* pScene = assimpImporter.ReadFile(assimpFilePath->filePath.c_str(), assimpImportFlags);

	//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP CONVERSION (VERTEX) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP CONVERSION (VERTEX) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP CONVERSION (VERTEX) |||||||||||||||||||||||||||||
	std::vector<Vector4> meshVertexPositions;
	std::vector<Vector4> meshVertexNormals;
	std::vector<Vector4> meshVertexTangents;
	std::vector<std::vector<Vector4>> meshVertexUVs;
	std::vector<std::vector<Vector4>> meshVertexColors;
	std::vector<Vector4> meshVertexBlendWeight;
	std::vector<UnsignedIntegerVector4> meshVertexBlendIndex;

	int totalVertexCount = 0;
	unsigned int maxVertexIndex = 0;

	std::vector<Vector4> meshVertexUVChannel;
	std::vector<Vector4> meshVertexColorChannel;

	Vector4 boundingBoxMin = Vector4();
	Vector4 boundingBoxMax = Vector4();

	for (int i = 0; i < pScene->mNumMeshes; i++)
	{
		aiMesh* assimpMesh = pScene->mMeshes[i];

		totalVertexCount += assimpMesh->mNumVertices;

		if (assimpMesh->HasPositions())
		{
			for (int j = 0; j < assimpMesh->mNumVertices; j++)
				meshVertexPositions.push_back(GetVector4FromAssimpVector3(assimpMesh->mVertices[j]));
		}

		if (assimpMesh->HasNormals())
		{
			for (int j = 0; j < assimpMesh->mNumVertices; j++)
				meshVertexNormals.push_back(GetVector4FromAssimpVector3(assimpMesh->mNormals[j]));
		}

		if (assimpMesh->HasTangentsAndBitangents())
		{
			for (int j = 0; j < assimpMesh->mNumVertices; j++)
				meshVertexTangents.push_back(GetVector4FromAssimpVector3(assimpMesh->mTangents[j]));
		}

		//for (int j = 0; j < assimpMesh->GetNumUVChannels(); j++)
		//{
			//std::vector<Vector4> meshVertexUVChannel;

			//for (int x = 0; x < assimpMesh->mNumVertices; x++)
				//meshVertexUVChannel.push_back(GetVector4FromAssimpVector3(assimpMesh->mTextureCoords[j][x]));

			//meshVertexUVs.push_back(meshVertexUVChannel);
		//}

		//std::vector<Vector4> meshVertexUVChannel;

		for (int j = 0; j < assimpMesh->GetNumUVChannels(); j++)
		{
			for (int x = 0; x < assimpMesh->mNumVertices; x++)
				meshVertexUVChannel.push_back(GetVector4FromAssimpVector3(assimpMesh->mTextureCoords[j][x]));
		}

		//for (int j = 0; j < assimpMesh->GetNumColorChannels(); j++)
		for (int j = 0; j < 1; j++)
		{
			//for (int x = 0; x < assimpMesh->mNumVertices; x++)
				//meshVertexColorChannel.push_back(GetVector4FromAssimpColor4(assimpMesh->mColors[j][x]));

			for (int x = 0; x < assimpMesh->mNumVertices; x++)
				meshVertexColorChannel.push_back(Vector4(1, 1, 1, 1));
		}

		Vector4 assimpMeshBoundingBoxMin = GetVector4FromAssimpVector3(assimpMesh->mAABB.mMin);
		Vector4 assimpMeshBoundingBoxMax = GetVector4FromAssimpVector3(assimpMesh->mAABB.mMax);

		boundingBoxMin.x = fmin(boundingBoxMin.x, assimpMeshBoundingBoxMin.x);
		boundingBoxMin.y = fmin(boundingBoxMin.y, assimpMeshBoundingBoxMin.y);
		boundingBoxMin.z = fmin(boundingBoxMin.z, assimpMeshBoundingBoxMin.z);
		boundingBoxMin.w = fmin(boundingBoxMin.w, assimpMeshBoundingBoxMin.w);

		boundingBoxMax.x = fmax(boundingBoxMax.x, assimpMeshBoundingBoxMax.x);
		boundingBoxMax.y = fmax(boundingBoxMax.y, assimpMeshBoundingBoxMax.y);
		boundingBoxMax.z = fmax(boundingBoxMax.z, assimpMeshBoundingBoxMax.z);
		boundingBoxMax.w = fmax(boundingBoxMax.w, assimpMeshBoundingBoxMax.w);
	}

	meshVertexUVs.push_back(meshVertexUVChannel);
	meshVertexColors.push_back(meshVertexColorChannel);

	BoundingBox newBoundingBox = BoundingBox();
	newBoundingBox.mMin = Vector3(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMin.z);
	newBoundingBox.mMax = Vector3(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMax.z);
	Vector3 boundingBoxCenter = newBoundingBox.CalculateCenter();

	parsedD3DMesh.d3dmeshHeader.mBoundingBox = newBoundingBox;

	//Vector3 newPositionScale = Vector3();
	//Vector3 newPositionScale = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 newPositionScale = newBoundingBox.CalculateSize();

	//NOTE: Since we are assuming buffer format eGFXPlatformFormat_UN10x3_UN2 this means we need a final position to be 0..1
	//So offset needed here is the extents "half size of bounds" to nudge the models from -0.5 to 0
	//In addition we also need to get the center of the bounding box and offset by that as well
	//NOTE: Compared to original hammer, position offset is negative
	Vector3 newPositionOffset = newBoundingBox.CalculateExtents();
	newPositionOffset.x -= boundingBoxCenter.x; //subtract by center offset
	newPositionOffset.y -= boundingBoxCenter.y; //subtract by center offset
	newPositionOffset.z -= boundingBoxCenter.z; //subtract by center offset

	//reverse offset
	newPositionOffset.x = -newPositionOffset.x;
	newPositionOffset.y = -newPositionOffset.y;
	newPositionOffset.z = -newPositionOffset.z;

	parsedD3DMesh.d3dmeshHeader.mPositionOffset = newPositionOffset;
	parsedD3DMesh.d3dmeshHeader.mPositionScale = newPositionScale;

	//clear original vertex buffer data
	parsedD3DMesh.EraseVertexBufferHeaderData();
	parsedD3DMesh.EraseGFXAttributeParamsHeaderData();
	parsedD3DMesh.EraseVertexBufferMeshData();

	parsedD3DMesh.AddNewVertexBufferVector4(
		GFXPlatformVertexAttribute::eGFXPlatformAttribute_Position, //mAttribute 0
		GFXPlatformFormat::eGFXPlatformFormat_UN10x3_UN2, //Format 41
		GFXPlatformBufferUsage::eGFXPlatformBuffer_Vertex | GFXPlatformBufferUsage::eGFXPlatformBuffer_ShaderRead, //mBufferUsage 9
		meshVertexPositions);

	parsedD3DMesh.AddNewVertexBufferVector4(
		GFXPlatformVertexAttribute::eGFXPlatformAttribute_Normal, //mAttribute 1
		GFXPlatformFormat::eGFXPlatformFormat_SN8x4, //Format 37
		GFXPlatformBufferUsage::eGFXPlatformBuffer_Vertex | GFXPlatformBufferUsage::eGFXPlatformBuffer_ShaderRead | GFXPlatformBufferUsage::eGFXPlatformBuffer_ShaderRawAccess, //mBufferUsage 41
		meshVertexNormals);

	/*
	parsedD3DMesh.AddNewVertexBufferVector4(
		GFXPlatformVertexAttribute::eGFXPlatformAttribute_Tangent, //mAttribute 2
		GFXPlatformFormat::eGFXPlatformFormat_SN8x4, //Format 37
		GFXPlatformBufferUsage::eGFXPlatformBuffer_Vertex | GFXPlatformBufferUsage::eGFXPlatformBuffer_ShaderRead | GFXPlatformBufferUsage::eGFXPlatformBuffer_ShaderRawAccess, //mBufferUsage 41
		meshVertexTangents);

	parsedD3DMesh.AddNewVertexBufferVector4(
		GFXPlatformVertexAttribute::eGFXPlatformAttribute_TexCoord, //mAttribute 6
		GFXPlatformFormat::eGFXPlatformFormat_SN16x2, //Format 23
		GFXPlatformBufferUsage::eGFXPlatformBuffer_Vertex | GFXPlatformBufferUsage::eGFXPlatformBuffer_ShaderRead | GFXPlatformBufferUsage::eGFXPlatformBuffer_ShaderRawAccess, //mBufferUsage 41
		meshVertexUVs[0]);
	*/

	parsedD3DMesh.AddNewVertexBufferVector4(
		GFXPlatformVertexAttribute::eGFXPlatformAttribute_Color, //mAttribute 5
		GFXPlatformFormat::eGFXPlatformFormat_UN8x4, //Format 23
		GFXPlatformBufferUsage::eGFXPlatformBuffer_Vertex | GFXPlatformBufferUsage::eGFXPlatformBuffer_ShaderRead, //mBufferUsage 9
		meshVertexColors[0]);

	//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP CONVERSION (TRIANGLES) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP CONVERSION (TRIANGLES) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP CONVERSION (TRIANGLES) |||||||||||||||||||||||||||||
	std::vector<unsigned short> meshTriangles;
	unsigned int faceCount = 0;

	for (int i = 0; i < pScene->mNumMeshes; i++)
	{
		aiMesh* assimpMesh = pScene->mMeshes[i];

		faceCount += assimpMesh->mNumFaces;
		
		for (int j = 0; j < assimpMesh->mNumFaces; j++)
		{
			aiFace assimpMeshFace = assimpMesh->mFaces[j];

			for (int x = 0; x < assimpMeshFace.mNumIndices; x++)
			{
				meshTriangles.push_back(assimpMeshFace.mIndices[x]);
				maxVertexIndex = fmax(maxVertexIndex, assimpMeshFace.mIndices[x]);
			}
		}
	}

	//clear original index buffer data
	parsedD3DMesh.EraseIndexBufferHeaderData();
	parsedD3DMesh.EraseIndexBufferMeshData();

	parsedD3DMesh.AddNewIndexBuffer(meshTriangles, GFXPlatformBufferUsage::eGFXPlatformBuffer_Index | GFXPlatformBufferUsage::eGFXPlatformBuffer_ShaderRead); //BUFFER USAGE 10
	//parsedD3DMesh.AddNewIndexBuffer(meshTriangles, GFXPlatformBufferUsage::eGFXPlatformBuffer_Index); //BUFFER USAGE 2

	//||||||||||||||||||||||||||||| D3DMESH HEADER TO ASSIMP CONVERSION (LODS/SUBMESHES) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH HEADER TO ASSIMP CONVERSION (LODS/SUBMESHES) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH HEADER TO ASSIMP CONVERSION (LODS/SUBMESHES) |||||||||||||||||||||||||||||
	//NOTE: We are making a LOT of assumptions here about the mesh conversion process in order to finally bridge the gap between (standard mesh format) -> d3dmesh.
	//1. We are basically assuming/forcing the standard mesh to be one single mesh (no lods, only one single sumbesh)
	//2. We are also assuming/forcing the standard mesh to have only one material
	//3. This has been taliored to work for only a specific d3dmesh that we are converting (specifically a hammer, that is only one submesh/material)
	//4. On the D3DMESH end there are no tangents, as that is not required
	//5. On the D3DMESH end there are no uvs, as that is no required.
	//6. On the D3DMESH end there is no mBatches1 (shadow) mesh batches, there is only 1 single mBatches0 (default) mesh batch.
	//7. On the D3DMESH end there is only one index buffer needed for rendering triangles (remember that initally most/if not all d3dmeshes has two index buffers?)

	parsedD3DMesh.d3dmeshHeader.mVertexCount = totalVertexCount;

	T3MeshLOD newLOD0 = T3MeshLOD();
	T3MeshBatch fullDefaultSubmesh = T3MeshBatch();

	//set new default mesh batch properties
	fullDefaultSubmesh.mBatchUsage = (T3MeshBatchUsageFlag)0;
	fullDefaultSubmesh.mMinVertIndex = 0;
	fullDefaultSubmesh.mMaxVertIndex = maxVertexIndex;
	fullDefaultSubmesh.mBaseIndex = 0;
	fullDefaultSubmesh.mStartIndex = 0;
	fullDefaultSubmesh.mNumPrimitives = faceCount;
	fullDefaultSubmesh.mNumIndices = meshTriangles.size();
	fullDefaultSubmesh.mMaterialIndex = 0;
	fullDefaultSubmesh.mBoundingBox = newBoundingBox;
	fullDefaultSubmesh.mBoundingSphere.SetBoundingSphereBasedOnBoundingBox(newBoundingBox);

	//set new LOD properties
	newLOD0.mVertexStart = 0;
	newLOD0.mVertexCount = totalVertexCount;
	newLOD0.mNumPrimitives = faceCount; //NOTE: this should be the total face count for both mBatches0 + mBatches1
	//newLOD0.mNumPrimitives = faceCount * 2;
	newLOD0.mBoundingBox = newBoundingBox;
	newLOD0.mBoundingSphere.SetBoundingSphereBasedOnBoundingBox(newBoundingBox);

	//copy original LOD properties
	newLOD0.mVertexStreams = parsedD3DMesh.d3dmeshHeader.mLODs[0].mVertexStreams;

	//add new batches to new LOD level
	newLOD0.mBatches0.push_back(fullDefaultSubmesh);

	//clear original LOD data and add our new LOD level
	parsedD3DMesh.d3dmeshHeader.mLODs.erase(parsedD3DMesh.d3dmeshHeader.mLODs.begin(), parsedD3DMesh.d3dmeshHeader.mLODs.end());
	parsedD3DMesh.d3dmeshHeader.mLODs.push_back(newLOD0);

	//update bounding boxes on materials?
	parsedD3DMesh.d3dmeshHeader.mMaterials[0].mBoundingBox = newBoundingBox;
	parsedD3DMesh.d3dmeshHeader.mMaterials[0].mBoundingSphere.SetBoundingSphereBasedOnBoundingBox(newBoundingBox);

	//||||||||||||||||||||||||||||| D3DMESH EXPORT |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH EXPORT |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH EXPORT |||||||||||||||||||||||||||||

	parsedD3DMesh.UpdateStructures();

	std::ofstream outputFileStream;
	outputFileStream.open(outputPath, std::ios::binary);
	parsedD3DMesh.BinarySerialize(&outputFileStream);
	outputFileStream.close();

	std::cout << "EXPORTED... " << outputPath << std::endl;
}

#endif
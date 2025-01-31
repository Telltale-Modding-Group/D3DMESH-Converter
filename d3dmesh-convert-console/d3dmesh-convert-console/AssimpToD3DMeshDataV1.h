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

//THIRD PARTY: GLM Library
#include <glm.hpp>

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
#include "../../Helper/JsonHelper.h"
#include "../../Helper/AssimpHelper.h"

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

	nlohmann::ordered_json jsonReader;
	d3dmeshJsonInputFileStream >> jsonReader;

	TelltaleD3DMeshFileV55 originalD3DMesh = jsonReader.template get<TelltaleD3DMeshFileV55>();

	bool isVertexPositionUnsignedNormalized = originalD3DMesh.IsVertexPositionFormatUnsignedNormalized();
	bool isVertexPositionSignedNormalized = originalD3DMesh.IsVertexPositionFormatUnsignedNormalized();
	bool isVertexPositionNormalized = isVertexPositionUnsignedNormalized || isVertexPositionSignedNormalized;

	d3dmeshJsonInputFileStream.close();

	//||||||||||||||||||||||||||||| READ ASSIMP MESH |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| READ ASSIMP MESH |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| READ ASSIMP MESH |||||||||||||||||||||||||||||
	Assimp::Importer assimpImporter;

	//most d3dmeshes have a U16 index buffer limit set
	assimpImporter.SetPropertyInteger(AI_CONFIG_PP_SLM_TRIANGLE_LIMIT, UINT16_MAX);
	assimpImporter.SetPropertyBool(AI_CONFIG_PP_PTV_NORMALIZE, true); //default is false
	assimpImporter.SetPropertyInteger(AI_CONFIG_PP_CT_TEXTURE_CHANNEL_INDEX, 0);
	assimpImporter.SetPropertyFloat(AI_CONFIG_PP_CT_MAX_SMOOTHING_ANGLE, 45); //Default 45, Max is 175

	unsigned int assimpImportFlags =
		aiProcess_Triangulate |
		aiProcess_FindInvalidData | 
		aiProcess_CalcTangentSpace |
		aiProcess_GenNormals |
		aiProcess_GenBoundingBoxes |
		aiProcess_SortByPType |
		aiProcess_JoinIdenticalVertices |
		aiProcess_ImproveCacheLocality |
		aiProcess_FindDegenerates |
		aiProcess_FlipUVs | 
		aiProcess_MakeLeftHanded | 
		aiProcess_FlipWindingOrder
		//aiProcess_ConvertToLeftHanded
		//aiProcess_SplitLargeMeshes
		;

	const aiScene* pScene = assimpImporter.ReadFile(assimpFilePath->filePath.c_str(), assimpImportFlags);

	//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP CONVERSION (MESH EXTRACTION) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP CONVERSION (MESH EXTRACTION) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP CONVERSION (MESH EXTRACTION) |||||||||||||||||||||||||||||
	std::vector<Vector4> assimpMeshVertexPositions;
	std::vector<Vector4> assimpMeshVertexNormals;
	std::vector<Vector4> assimpMeshVertexTangents;
	std::vector<std::vector<Vector4>> assimpMeshVertexUVs;
	std::vector<std::vector<Vector4>> assimpMeshVertexColors;
	std::vector<Vector4> assimpMeshVertexBlendWeight;
	std::vector<UnsignedIntegerVector4> assimpMeshVertexBlendIndex;

	unsigned int assimpMeshTotalVertexCount = 0;
	unsigned int assimpMeshMaxVertexIndex = 0;
	unsigned int assimpMeshTotalTriangleCount = 0;
	unsigned int assimpMeshTotalIndiciesCount = 0;

	std::vector<Vector4> assimpMeshVertexUVChannel;
	std::vector<Vector4> assimpMeshVertexColorChannel;

	glm::vec3 newD3DMeshBoundingBoxMin = glm::vec3(0.0f);
	glm::vec3 newD3DMeshBoundingBoxMax = glm::vec3(0.0f);

	for (int i = 0; i < pScene->mNumMeshes; i++)
	{
		aiMesh* assimpMesh = pScene->mMeshes[i];

		assimpMeshTotalVertexCount += assimpMesh->mNumVertices;

		if (assimpMesh->HasPositions())
		{
			for (int j = 0; j < assimpMesh->mNumVertices; j++)
				assimpMeshVertexPositions.push_back(GetVector4FromAssimpVector3(assimpMesh->mVertices[j]));
		}

		if (assimpMesh->HasNormals())
		{
			for (int j = 0; j < assimpMesh->mNumVertices; j++)
				assimpMeshVertexNormals.push_back(GetVector4FromAssimpVector3(assimpMesh->mNormals[j]));
		}

		if (assimpMesh->HasTangentsAndBitangents())
		{
			for (int j = 0; j < assimpMesh->mNumVertices; j++)
			{
				//Vector4 existingTangent = Vector4(1, 0, 0, 1);
				Vector4 existingTangent = GetVector4FromAssimpVector3(assimpMesh->mTangents[j]);
				//Vector4 existingTangent = GetVector4FromAssimpVector3(assimpMesh->mBitangents[j]);

				assimpMeshVertexTangents.push_back(existingTangent);
			}

			//std::vector<Vector4> newTangents = CalculateTangentsFromMesh(assimpMesh, 0);
			//std::vector<Vector4> newTangents = CalculateMikkTangentsFromMesh(assimpMesh, 0);

			//for (int j = 0; j < assimpMesh->mNumVertices; j++)
				//assimpMeshVertexTangents.push_back(newTangents[j]);
		}

		//for (int j = 0; j < assimpMesh->GetNumUVChannels(); j++)
		//{
			//std::vector<Vector4> assimpMeshVertexUVChannel;

			//for (int x = 0; x < assimpMesh->mNumVertices; x++)
				//assimpMeshVertexUVChannel.push_back(GetVector4FromAssimpVector3(assimpMesh->mTextureCoords[j][x]));

			//assimpMeshVertexUVs.push_back(assimpMeshVertexUVChannel);
		//}

		//std::vector<Vector4> assimpMeshVertexUVChannel;

		for (int j = 0; j < assimpMesh->GetNumUVChannels(); j++)
		{
			for (int x = 0; x < assimpMesh->mNumVertices; x++)
				assimpMeshVertexUVChannel.push_back(GetVector4FromAssimpVector3(assimpMesh->mTextureCoords[j][x]));
		}

		//for (int j = 0; j < assimpMesh->GetNumColorChannels(); j++)
		for (int j = 0; j < 1; j++)
		{
			//for (int x = 0; x < assimpMesh->mNumVertices; x++)
				//assimpMeshVertexColorChannel.push_back(GetVector4FromAssimpColor4(assimpMesh->mColors[j][x]));

			for (int x = 0; x < assimpMesh->mNumVertices; x++)
				assimpMeshVertexColorChannel.push_back(Vector4(0, 0, 0, 1));
		}

		glm::vec3 assimpMeshBoundingBoxMin = Get_vec3_FromAssimpVector3(assimpMesh->mAABB.mMin);
		glm::vec3 assimpMeshBoundingBoxMax = Get_vec3_FromAssimpVector3(assimpMesh->mAABB.mMax);

		newD3DMeshBoundingBoxMin = glm::min(newD3DMeshBoundingBoxMin, assimpMeshBoundingBoxMin);
		newD3DMeshBoundingBoxMax = glm::max(newD3DMeshBoundingBoxMax, assimpMeshBoundingBoxMax);
	}

	assimpMeshVertexUVs.push_back(assimpMeshVertexUVChannel);
	assimpMeshVertexColors.push_back(assimpMeshVertexColorChannel);

	//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP CONVERSION (BONE EXTRACTION) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP CONVERSION (BONE EXTRACTION) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP CONVERSION (BONE EXTRACTION) |||||||||||||||||||||||||||||



	//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP CONVERSION (VERTEX) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP CONVERSION (VERTEX) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP CONVERSION (VERTEX) |||||||||||||||||||||||||||||

	BoundingBox newD3DMeshBoundingBox = BoundingBox();
	newD3DMeshBoundingBox.mMin = Vector3(newD3DMeshBoundingBoxMin);
	newD3DMeshBoundingBox.mMax = Vector3(newD3DMeshBoundingBoxMax);
	Vector3 newD3DMeshBoundingBoxCenter = newD3DMeshBoundingBox.CalculateCenter();

	Vector3 newPositionScale = newD3DMeshBoundingBox.CalculateSize();

	//NOTE: Since we are assuming buffer format eGFXPlatformFormat_UN10x3_UN2 this means we need a final position to be 0..1
	//So offset needed here is the extents "half size of bounds" to nudge the models from -0.5 to 0
	//In addition we also need to get the center of the bounding box and offset by that as well
	//NOTE: Compared to original hammer, position offset is negative
	//Vector3 newPositionOffset = newD3DMeshBoundingBox.CalculateExtents();
	//newPositionOffset -= newD3DMeshBoundingBoxCenter; //subtract by center offset
	//newPositionOffset = -newPositionOffset;

	glm::vec3 newPositionOffset = glm::vec3(0.0f);
	newPositionOffset = -Get_vec3_FromVector3(newD3DMeshBoundingBoxCenter);

	if(originalD3DMesh.IsVertexPositionFormatUnsignedNormalized())
		newPositionOffset += Get_vec3_FromVector3(newD3DMeshBoundingBox.CalculateExtents()); //subtract by center offset

	newPositionOffset = -newPositionOffset;

	Vector3 newPositionWScale = Vector3();

	if (newPositionScale.x > newPositionScale.y && newPositionScale.x > newPositionScale.z)
		newPositionWScale.x = newPositionScale.x * 3.0f;
	else if (newPositionScale.y > newPositionScale.x && newPositionScale.y > newPositionScale.z)
		newPositionWScale.y = newPositionScale.y * 3.0f;
	else if (newPositionScale.z > newPositionScale.x && newPositionScale.z > newPositionScale.y)
		newPositionWScale.z = newPositionScale.z * 3.0f;

	originalD3DMesh.d3dmeshHeader.mPositionOffset = Vector3(newPositionOffset);
	originalD3DMesh.d3dmeshHeader.mPositionScale = newPositionScale;
	originalD3DMesh.d3dmeshHeader.mPositionWScale = newPositionWScale;

	/*
	//clear original vertex buffer data
	originalD3DMesh.EraseVertexBufferHeaderData();
	originalD3DMesh.EraseGFXAttributeParamsHeaderData();
	originalD3DMesh.EraseVertexBufferMeshData();

	originalD3DMesh.AddNewVertexBufferVector4(
		GFXPlatformVertexAttribute::eGFXPlatformAttribute_Position, //mAttribute 0
		GFXPlatformFormat::eGFXPlatformFormat_UN10x3_UN2, //Format 41
		GFXPlatformBufferUsage::eGFXPlatformBuffer_Vertex | GFXPlatformBufferUsage::eGFXPlatformBuffer_ShaderRead, //mBufferUsage 9
		assimpMeshVertexPositions);

	originalD3DMesh.AddNewVertexBufferVector4(
		GFXPlatformVertexAttribute::eGFXPlatformAttribute_Normal, //mAttribute 1
		GFXPlatformFormat::eGFXPlatformFormat_SN8x4, //Format 37
		GFXPlatformBufferUsage::eGFXPlatformBuffer_Vertex | GFXPlatformBufferUsage::eGFXPlatformBuffer_ShaderRead | GFXPlatformBufferUsage::eGFXPlatformBuffer_ShaderRawAccess, //mBufferUsage 41
		assimpMeshVertexNormals);

	originalD3DMesh.AddNewVertexBufferVector4(
		GFXPlatformVertexAttribute::eGFXPlatformAttribute_Tangent, //mAttribute 2
		GFXPlatformFormat::eGFXPlatformFormat_SN8x4, //Format 37
		GFXPlatformBufferUsage::eGFXPlatformBuffer_Vertex | GFXPlatformBufferUsage::eGFXPlatformBuffer_ShaderRead | GFXPlatformBufferUsage::eGFXPlatformBuffer_ShaderRawAccess, //mBufferUsage 41
		assimpMeshVertexTangents);

	originalD3DMesh.AddNewVertexBufferVector4(
		GFXPlatformVertexAttribute::eGFXPlatformAttribute_TexCoord, //mAttribute 6
		GFXPlatformFormat::eGFXPlatformFormat_SN16x2, //Format 23
		GFXPlatformBufferUsage::eGFXPlatformBuffer_Vertex | GFXPlatformBufferUsage::eGFXPlatformBuffer_ShaderRead, //mBufferUsage 9
		assimpMeshVertexUVs[0],
		4);

	originalD3DMesh.AddNewVertexBufferVector4(
		GFXPlatformVertexAttribute::eGFXPlatformAttribute_Color, //mAttribute 5
		GFXPlatformFormat::eGFXPlatformFormat_UN8x4, //Format 23
		GFXPlatformBufferUsage::eGFXPlatformBuffer_Vertex | GFXPlatformBufferUsage::eGFXPlatformBuffer_ShaderRead, //mBufferUsage 9
		assimpMeshVertexColors[0],
		1); //mAttributeIndex = 1 (NOTE THIS IS KEY TO GETTING THE MESH TO SHOW UP)

	originalD3DMesh.AddNewVertexBufferVector4(
		GFXPlatformVertexAttribute::eGFXPlatformAttribute_TexCoord, //mAttribute 6
		GFXPlatformFormat::eGFXPlatformFormat_F32x2, //Format 2
		GFXPlatformBufferUsage::eGFXPlatformBuffer_Vertex | GFXPlatformBufferUsage::eGFXPlatformBuffer_ShaderRead, //mBufferUsage 9
		assimpMeshVertexUVs[0]);
	*/

	originalD3DMesh.ModifyVertexBuffers(GFXPlatformVertexAttribute::eGFXPlatformAttribute_Position, assimpMeshVertexPositions); //mAttribute 0
	originalD3DMesh.ModifyVertexBuffers(GFXPlatformVertexAttribute::eGFXPlatformAttribute_Normal, assimpMeshVertexNormals); //mAttribute 1
	originalD3DMesh.ModifyVertexBuffers(GFXPlatformVertexAttribute::eGFXPlatformAttribute_Tangent, assimpMeshVertexTangents); //mAttribute 2
	originalD3DMesh.ModifyVertexBuffers(GFXPlatformVertexAttribute::eGFXPlatformAttribute_Color, assimpMeshVertexColors[0]); //mAttribute 5
	originalD3DMesh.ModifyVertexBuffers(GFXPlatformVertexAttribute::eGFXPlatformAttribute_TexCoord, assimpMeshVertexUVs[0]); //mAttribute 6

	//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP CONVERSION (TRIANGLES) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP CONVERSION (TRIANGLES) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP CONVERSION (TRIANGLES) |||||||||||||||||||||||||||||
	std::vector<unsigned short> assimpMeshTriangles;

	for (int i = 0; i < pScene->mNumMeshes; i++)
	{
		aiMesh* assimpMesh = pScene->mMeshes[i];

		assimpMeshTotalTriangleCount += assimpMesh->mNumFaces;
		
		for (int j = 0; j < assimpMesh->mNumFaces; j++)
		{
			aiFace assimpMeshFace = assimpMesh->mFaces[j];

			for (int x = 0; x < assimpMeshFace.mNumIndices; x++)
			{
				assimpMeshTriangles.push_back(assimpMeshFace.mIndices[x]);
				assimpMeshMaxVertexIndex = fmax(assimpMeshMaxVertexIndex, assimpMeshFace.mIndices[x]);
			}

			assimpMeshTotalIndiciesCount += assimpMeshFace.mNumIndices;
		}
	}

	//clear original index buffer data
	//originalD3DMesh.EraseIndexBufferHeaderData();
	//originalD3DMesh.EraseIndexBufferMeshData();

	//originalD3DMesh.AddNewIndexBuffer(assimpMeshTriangles, GFXPlatformBufferUsage::eGFXPlatformBuffer_Index | GFXPlatformBufferUsage::eGFXPlatformBuffer_ShaderRead); //BUFFER USAGE 10 (DEFAULT)
	//originalD3DMesh.AddNewIndexBuffer(assimpMeshTriangles, GFXPlatformBufferUsage::eGFXPlatformBuffer_Index); //BUFFER USAGE 2 (SHADOWS)

	//originalD3DMesh.AddNewIndexBuffer(assimpMeshTriangles, GFXPlatformBufferUsage::eGFXPlatformBuffer_Index | GFXPlatformBufferUsage::eGFXPlatformBuffer_ShaderRead, eGFXPlatformFormat_U32); //BUFFER USAGE 10 (DEFAULT)
	//originalD3DMesh.AddNewIndexBuffer(assimpMeshTriangles, GFXPlatformBufferUsage::eGFXPlatformBuffer_Index, eGFXPlatformFormat_U32); //BUFFER USAGE 2 (SHADOWS)

	originalD3DMesh.ModifyIndexBuffers(assimpMeshTriangles);

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

	T3MeshLOD newLOD0 = T3MeshLOD();
	T3MeshBatch fullDefaultSubmesh = T3MeshBatch();
	T3MeshBatch fullShadowSubmesh = T3MeshBatch();

	//set new default mesh batch properties
	fullDefaultSubmesh.mBatchUsage = (T3MeshBatchUsageFlag)0;
	fullDefaultSubmesh.mMinVertIndex = 0;
	fullDefaultSubmesh.mMaxVertIndex = assimpMeshMaxVertexIndex;
	fullDefaultSubmesh.mBaseIndex = 0;
	fullDefaultSubmesh.mStartIndex = 0;
	fullDefaultSubmesh.mNumPrimitives = assimpMeshTotalTriangleCount;
	fullDefaultSubmesh.mNumIndices = assimpMeshTotalIndiciesCount;
	fullDefaultSubmesh.mMaterialIndex = 0;
	fullDefaultSubmesh.mBoundingBox = newD3DMeshBoundingBox;
	fullDefaultSubmesh.mBoundingSphere.SetBoundingSphereBasedOnBoundingBox(newD3DMeshBoundingBox);

	//set new default mesh batch properties
	fullShadowSubmesh.mBatchUsage = (T3MeshBatchUsageFlag)0;
	fullShadowSubmesh.mMinVertIndex = 0;
	fullShadowSubmesh.mMaxVertIndex = assimpMeshMaxVertexIndex;
	fullShadowSubmesh.mBaseIndex = 0;
	fullShadowSubmesh.mStartIndex = 0;
	fullShadowSubmesh.mNumPrimitives = assimpMeshTotalTriangleCount;
	fullShadowSubmesh.mNumIndices = assimpMeshTotalIndiciesCount;
	fullShadowSubmesh.mMaterialIndex = 0;
	fullShadowSubmesh.mBoundingBox = newD3DMeshBoundingBox;
	fullShadowSubmesh.mBoundingSphere.SetBoundingSphereBasedOnBoundingBox(newD3DMeshBoundingBox);

	//set new LOD properties
	newLOD0.mVertexStart = 0;
	newLOD0.mVertexCount = assimpMeshTotalVertexCount;

	//copy original LOD properties
	newLOD0.mVertexStreams = originalD3DMesh.d3dmeshHeader.mLODs[0].mVertexStreams;

	//add new batches to new LOD level
	newLOD0.mBatches0.push_back(fullDefaultSubmesh);
	newLOD0.mBatches1.push_back(fullShadowSubmesh);

	//clear original LOD data and add our new LOD level
	originalD3DMesh.d3dmeshHeader.mLODs.erase(originalD3DMesh.d3dmeshHeader.mLODs.begin(), originalD3DMesh.d3dmeshHeader.mLODs.end());
	originalD3DMesh.d3dmeshHeader.mLODs.push_back(newLOD0);

	//update bounding boxes on materials?
	originalD3DMesh.d3dmeshHeader.mMaterials[0].mBoundingBox = newD3DMeshBoundingBox;
	originalD3DMesh.d3dmeshHeader.mMaterials[0].mBoundingSphere.SetBoundingSphereBasedOnBoundingBox(newD3DMeshBoundingBox);

	//||||||||||||||||||||||||||||| D3DMESH EXPORT |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH EXPORT |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH EXPORT |||||||||||||||||||||||||||||

	originalD3DMesh.UpdateStructures();

	std::ofstream outputFileStream;
	outputFileStream.open(outputPath, std::ios::binary);
	originalD3DMesh.BinarySerialize(&outputFileStream);
	outputFileStream.close();

	std::cout << "EXPORTED... " << outputPath << std::endl;
}

#endif
#pragma once
#ifndef D3DMESH_DATA_TO_ASSIMP_V1_H
#define D3DMESH_DATA_TO_ASSIMP_V1_H

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
#include "FileEntry.h"
#include "TelltaleD3DMeshFileV55.h"
#include "Json.h"
#include "AssimpHelper.h"

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

	unsigned int assimpImportFlags = aiProcess_Triangulate;
	const aiScene* pScene = assimpImporter.ReadFile(assimpFilePath->filePath.c_str(), assimpImportFlags);

	//||||||||||||||||||||||||||||| D3DMESH TO ASSIMP CONVERSION (VERTEX) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH TO ASSIMP CONVERSION (VERTEX) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH TO ASSIMP CONVERSION (VERTEX) |||||||||||||||||||||||||||||
	parsedD3DMesh.d3dmeshData.EraseData();

	std::vector<Vector4> meshVertexPositions;
	std::vector<Vector4> meshVertexNormals;
	std::vector<Vector4> meshVertexTangents;
	std::vector<std::vector<Vector4>> meshVertexUVs;
	std::vector<std::vector<Vector4>> meshVertexColors;
	std::vector<Vector4> meshVertexBlendWeight;
	std::vector<UnsignedIntegerVector4> meshVertexBlendIndex;
	int totalVertexCount = 0;

	for (int i = 0; i < pScene->mNumMeshes; i++)
	{
		aiMesh* assimpMesh = pScene->mMeshes[i];
		//assimpMesh->mName

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

		for (int j = 0; j < assimpMesh->GetNumUVChannels(); j++)
		{
			std::vector<Vector4> meshVertexUVChannel;

			for (int x = 0; x < assimpMesh->mNumVertices; x++)
				meshVertexUVChannel.push_back(GetVector4FromAssimpVector3(assimpMesh->mTextureCoords[j][x]));

			meshVertexUVs.push_back(meshVertexUVChannel);
		}

		for (int j = 0; j < assimpMesh->GetNumColorChannels(); j++)
		{
			std::vector<Vector4> meshVertexColorChannel;

			for (int x = 0; x < assimpMesh->mNumVertices; x++)
				meshVertexColorChannel.push_back(GetVector4FromAssimpColor4(assimpMesh->mColors[j][x]));

			meshVertexColors.push_back(meshVertexColorChannel);
		}
	}

	parsedD3DMesh.d3dmeshData.vertexPositions.push_back(meshVertexPositions);
	parsedD3DMesh.d3dmeshData.vertexNormals.push_back(meshVertexNormals);
	parsedD3DMesh.d3dmeshData.vertexTangents.push_back(meshVertexTangents);
	parsedD3DMesh.d3dmeshData.vertexUVs = meshVertexUVs;
	parsedD3DMesh.d3dmeshData.vertexColors = meshVertexColors;
	parsedD3DMesh.d3dmeshData.vertexBlendWeight.push_back(meshVertexBlendWeight);
	parsedD3DMesh.d3dmeshData.vertexBlendIndex.push_back(meshVertexBlendIndex);

	//||||||||||||||||||||||||||||| D3DMESH TO ASSIMP CONVERSION (TRIANGLES) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH TO ASSIMP CONVERSION (TRIANGLES) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH TO ASSIMP CONVERSION (TRIANGLES) |||||||||||||||||||||||||||||
	std::vector<unsigned short> meshTriangles;

	parsedD3DMesh.d3dmeshHeader.mLODs[0].mVertexStart = 0;
	parsedD3DMesh.d3dmeshHeader.mLODs[0].mVertexCount = totalVertexCount;

	for (int i = 0; i < pScene->mNumMeshes; i++)
	{
		aiMesh* assimpMesh = pScene->mMeshes[i];

	}

	parsedD3DMesh.d3dmeshData.indexBuffers.push_back(meshTriangles);

	//||||||||||||||||||||||||||||| D3DMESH TO ASSIMP CONVERSION (TRIANGLES) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH TO ASSIMP CONVERSION (TRIANGLES) |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| D3DMESH TO ASSIMP CONVERSION (TRIANGLES) |||||||||||||||||||||||||||||
}

#endif
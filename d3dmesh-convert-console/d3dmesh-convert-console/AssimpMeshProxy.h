#pragma once
#ifndef ASSIMP_MESH_PROXY_H
#define ASSIMP_MESH_PROXY_H

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
#include <vector>

//Custom
#include "../../Telltale/DataTypes/Vector4.h"
#include "../../Telltale/DataTypes/Vector3.h"
#include "../../Telltale/DataTypes/Vector2.h"

//||||||||||||||||||||||||||||| ASSIMP MESH PROXY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| ASSIMP MESH PROXY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| ASSIMP MESH PROXY |||||||||||||||||||||||||||||

/// <summary>
/// This holds data from an assimp mesh, into a custom object that is then fed into the mikktspace tangent calculation library.
/// </summary>
struct AssimpMeshProxy
{
	unsigned int faceCount;
	std::vector<unsigned int> indices;
	std::vector<Vector3> vertexPosition;
	std::vector<Vector3> vertexNormal;
	std::vector<Vector2> vertexUV;

	std::vector<Vector4> vertexTangents;

	AssimpMeshProxy(aiMesh* assimpMesh, unsigned int uvIndex = 0)
	{
		for (int i = 0; i < assimpMesh->mNumVertices; i++)
			vertexPosition.push_back(Vector3(assimpMesh->mVertices[i].x, assimpMesh->mVertices[i].y, assimpMesh->mVertices[i].z));

		for (int i = 0; i < assimpMesh->mNumVertices; i++)
			vertexNormal.push_back(Vector3(assimpMesh->mNormals[i].x, assimpMesh->mNormals[i].y, assimpMesh->mNormals[i].z));

		for (int i = 0; i < assimpMesh->mNumVertices; i++)
			vertexUV.push_back(Vector2(assimpMesh->mTextureCoords[uvIndex][i].x, assimpMesh->mTextureCoords[uvIndex][i].y));

		for (int i = 0; i < assimpMesh->mNumVertices; i++)
			vertexTangents.push_back(Vector4(0, 0, 0, 0));

		faceCount = assimpMesh->mNumFaces;

		for (int i = 0; i < assimpMesh->mNumFaces; i++)
		{
			for (int j = 0; j < assimpMesh->mFaces[i].mNumIndices; j++)
				indices.push_back(assimpMesh->mFaces[i].mIndices[j]);
		}
	};
};

#endif
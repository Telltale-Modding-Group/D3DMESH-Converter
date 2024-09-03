#pragma once
#ifndef D3DMESH_DATA_TO_ASSIMP_H
#define D3DMESH_DATA_TO_ASSIMP_H

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
#include "Vector2.h"
#include "Vector4.h"
#include "TelltaleD3DMeshFileV55.h"

static void BuildAssimpMeshFromD3DMesh(aiMesh* assimpMesh, TelltaleD3DMeshFileV55* d3dmeshFile, int d3dmeshIndexLOD, int d3dmeshIndexBatch, bool defaultMesh)
{
	T3MeshLOD d3dmeshLOD = d3dmeshFile->d3dmeshHeader.mLODs[d3dmeshIndexLOD];
	T3MeshBatch d3dmeshBatch;

	if (defaultMesh)
		d3dmeshBatch = d3dmeshLOD.mBatches0[d3dmeshIndexBatch];
	else
		d3dmeshBatch = d3dmeshLOD.mBatches1[d3dmeshIndexBatch];

	assimpMesh->mMaterialIndex = d3dmeshBatch.mMaterialIndex;

	//|||||||||||||||||||||||||||||||||||||||| VERTEX SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX SETUP ||||||||||||||||||||||||||||||||||||||||

	int vertexArrayStart = d3dmeshLOD.mVertexStart;
	int vertexArrayLength = d3dmeshLOD.mVertexStart + assimpMesh->mNumVertices;

	//|||||||||||||||||||||||||||||||||||||||| VERTEX POSITIONS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX POSITIONS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX POSITIONS ||||||||||||||||||||||||||||||||||||||||
	assimpMesh->mNumVertices = d3dmeshLOD.mVertexCount; //SELF NOTE: assign amount of verticies first... or all hell breaks loose
	assimpMesh->mVertices = new aiVector3D[assimpMesh->mNumVertices];

	for (int i = vertexArrayStart; i < vertexArrayLength; i++)
		assimpMesh->mVertices[i] = aiVector3D(d3dmeshFile->d3dmeshData.vertexPositions[0][i].x, d3dmeshFile->d3dmeshData.vertexPositions[0][i].y, d3dmeshFile->d3dmeshData.vertexPositions[0][i].z);

	//|||||||||||||||||||||||||||||||||||||||| VERTEX NORMALS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX NORMALS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX NORMALS ||||||||||||||||||||||||||||||||||||||||
	assimpMesh->mNormals = new aiVector3D[assimpMesh->mNumVertices];

	if (d3dmeshFile->d3dmeshData.vertexNormals.size() > 0)
	{
		for (int i = vertexArrayStart; i < vertexArrayLength; i++)
			assimpMesh->mNormals[i] = aiVector3D(d3dmeshFile->d3dmeshData.vertexNormals[0][i].x, d3dmeshFile->d3dmeshData.vertexNormals[0][i].y, d3dmeshFile->d3dmeshData.vertexNormals[0][i].z);
	}

	//|||||||||||||||||||||||||||||||||||||||| VERTEX TANGENTS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX TANGENTS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX TANGENTS ||||||||||||||||||||||||||||||||||||||||
	//assimpMesh->mTangents = new aiVector3D[assimpMesh->mNumVertices];

	//if (d3dmeshFile->d3dmeshData.vertexTangents.size() > 0)
	//{
		//for (int i = vertexArrayStart; i < vertexArrayLength; i++)
			//assimpMesh->mTangents[i] = aiVector3D(d3dmeshFile->d3dmeshData.vertexTangents[0][i].x, d3dmeshFile->d3dmeshData.vertexTangents[0][i].y, d3dmeshFile->d3dmeshData.vertexTangents[0][i].z);
	//}

	//|||||||||||||||||||||||||||||||||||||||| VERTEX COLORS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX COLORS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX COLORS ||||||||||||||||||||||||||||||||||||||||

	//for(int j = 0; j < d3dmeshFile->d3dmeshData.vertexColors.size(); j++)
	//{
		//for (int i = vertexArrayStart; i < vertexArrayLength; i++)
			//assimpMesh->mColors[j][i] = aiColor4D(d3dmeshFile->d3dmeshData.vertexColors[j][i].x, d3dmeshFile->d3dmeshData.vertexColors[j][i].y, d3dmeshFile->d3dmeshData.vertexColors[j][i].z, d3dmeshFile->d3dmeshData.vertexColors[j][i].w);
	//}

	//|||||||||||||||||||||||||||||||||||||||| VERTEX UVS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX UVS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX UVS ||||||||||||||||||||||||||||||||||||||||

	//for (int j = 0; j < d3dmeshFile->d3dmeshData.vertexUVs.size(); j++)
	//{
		//assimpMesh->mNumUVComponents[j] = 2;

		//for (int i = vertexArrayStart; i < vertexArrayLength; i++)
			//assimpMesh->mTextureCoords[j][i] = aiVector3D(d3dmeshFile->d3dmeshData.vertexUVs[j][i].x, d3dmeshFile->d3dmeshData.vertexUVs[j][i].y, d3dmeshFile->d3dmeshData.vertexUVs[j][i].z);
	//}

	//|||||||||||||||||||||||||||||||||||||||| VERTEX BLEND WEIGHTS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX BLEND WEIGHTS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX BLEND WEIGHTS ||||||||||||||||||||||||||||||||||||||||

	//|||||||||||||||||||||||||||||||||||||||| VERTEX BLEND INDEXES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX BLEND INDEXES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX BLEND INDEXES ||||||||||||||||||||||||||||||||||||||||

	//|||||||||||||||||||||||||||||||||||||||| MESH TRIANGLES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| MESH TRIANGLES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| MESH TRIANGLES ||||||||||||||||||||||||||||||||||||||||

	std::vector<aiFace> faces;

	for (int faceIndex = 0; faceIndex < d3dmeshBatch.mNumIndices; faceIndex += 3)
	{
		aiFace newFace = aiFace();

		//triangles are made up of 3 vertex positions, so indicies are 3
		newFace.mNumIndices = 3;
		newFace.mIndices = new unsigned int[newFace.mNumIndices];

		//assign each extracted triangle index to our assimp face
		newFace.mIndices[0] = d3dmeshFile->d3dmeshData.indexBuffers[0][faceIndex + 0 + d3dmeshBatch.mStartIndex] + d3dmeshBatch.mBaseIndex;
		newFace.mIndices[1] = d3dmeshFile->d3dmeshData.indexBuffers[0][faceIndex + 1 + d3dmeshBatch.mStartIndex] + d3dmeshBatch.mBaseIndex;
		newFace.mIndices[2] = d3dmeshFile->d3dmeshData.indexBuffers[0][faceIndex + 2 + d3dmeshBatch.mStartIndex] + d3dmeshBatch.mBaseIndex;

		//accumulate final assimp faces
		faces.push_back(newFace);
	}

	assimpMesh->mFaces = new aiFace[faces.size()];
	assimpMesh->mNumFaces = faces.size();

	std::copy(faces.begin(), faces.end(), assimpMesh->mFaces);
}

static void ExportFullAssimpMesh(TelltaleD3DMeshFileV55* d3dmeshFile, std::string fileName)
{
	//|||||||||||||||||||||||||||||||| MESH PRE-CHECKS ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| MESH PRE-CHECKS ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| MESH PRE-CHECKS ||||||||||||||||||||||||||||||||
	//if for some reason we don't have the critical data, then we'll just have to skip extracting this mesh because we don't have the data!

	if (d3dmeshFile->d3dmeshData.vertexPositions.size() <= 0)
	{
		std::cout << "ERROR! NO VERTEX POSITION DATA PROVIDED! NOT CONVERTING MESH WITH ASSIMP..." << std::endl;
		return;
	}

	if (d3dmeshFile->d3dmeshData.vertexNormals.size() <= 0)
	{
		std::cout << "ERROR! NO VERTEX NORMAL DATA PROVIDED! NOT CONVERTING MESH WITH ASSIMP..." << std::endl;
		return;
	}

	if (d3dmeshFile->d3dmeshData.indexBuffers.size() <= 0)
	{
		std::cout << "ERROR! NO TRIANGLE INDICIES PROVIDED! NOT CONVERTING MESH WITH ASSIMP..." << std::endl;
		return;
	}

	//|||||||||||||||||||||||||||||||| D3DMESH PRE-SETUP ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| D3DMESH PRE-SETUP ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| D3DMESH PRE-SETUP ||||||||||||||||||||||||||||||||

	int meshMaterialCount = d3dmeshFile->d3dmeshHeader.mMaterials_ArrayLength;
	int lodCount = d3dmeshFile->d3dmeshHeader.mLODs.size();
	int defaultMeshCount = 0;
	int shadowMeshCount = 0;
	int totalSubmeshCount = 0;

	for (int i = 0; i < lodCount; i++)
	{
		defaultMeshCount += d3dmeshFile->d3dmeshHeader.mLODs[i].mBatches0_ArrayLength;
		shadowMeshCount += d3dmeshFile->d3dmeshHeader.mLODs[i].mBatches1_ArrayLength;
		totalSubmeshCount += d3dmeshFile->d3dmeshHeader.mLODs[i].mNumBatches;
	}

	//|||||||||||||||||||||||||||||||| ASSIMP INITALIZATION ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| ASSIMP INITALIZATION ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| ASSIMP INITALIZATION ||||||||||||||||||||||||||||||||
	//Create and setup the assimp scene

	//start by building a scene in assimp
	aiScene* assimpScene = new aiScene;

	//construct an empty scene with no flags
	assimpScene->mFlags = 0;
	assimpScene->mRootNode = NULL;

	//initalize the scene first with no meshes
	assimpScene->mNumMeshes = 0;
	assimpScene->mMeshes = NULL;

	//initalize the scene first with no materials
	assimpScene->mNumMaterials = 0;
	assimpScene->mMaterials = NULL;

	//initalize the scene first with no animations
	assimpScene->mNumAnimations = 0;
	assimpScene->mAnimations = NULL;

	//initalize the scene first with no textures
	assimpScene->mNumTextures = 0;
	assimpScene->mTextures = NULL;

	//initalize the scene first with no lights
	assimpScene->mNumLights = 0;
	assimpScene->mLights = NULL;

	//initalize the scene first with no cameras
	assimpScene->mNumCameras = 0;
	assimpScene->mCameras = NULL;
	assimpScene->mPrivate = NULL;

	//construct the root node to store the meshes
	aiNode* rootNode = new aiNode;
	assimpScene->mRootNode = rootNode;

	//|||||||||||||||||||||||||||||||| ASSIMP D3DMESH NODES SETUP ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| ASSIMP D3DMESH NODES SETUP ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| ASSIMP D3DMESH NODES SETUP ||||||||||||||||||||||||||||||||
	//Using assimp, we will create our node tree for the d3dmesh for organization

	assimpScene->mRootNode->mChildren = new aiNode * [1];
	assimpScene->mRootNode->mNumChildren = 1;

	aiNode* d3dmeshParentNode = new aiNode;
	d3dmeshParentNode->mName = aiString(d3dmeshFile->d3dmeshHeader.mName);
	d3dmeshParentNode->mChildren = new aiNode * [2];
	d3dmeshParentNode->mNumChildren = 2;

	aiNode* defaultMeshParentNode = new aiNode;
	defaultMeshParentNode->mName = aiString("Default");
	defaultMeshParentNode->mChildren = new aiNode * [lodCount];
	defaultMeshParentNode->mNumChildren = lodCount;

	aiNode* shadowMeshParentNode = new aiNode;
	shadowMeshParentNode->mName = aiString("Shadow");
	shadowMeshParentNode->mChildren = new aiNode * [lodCount];
	shadowMeshParentNode->mNumChildren = lodCount;

	d3dmeshParentNode->mChildren[0] = defaultMeshParentNode;
	d3dmeshParentNode->mChildren[1] = shadowMeshParentNode;
	assimpScene->mRootNode->mChildren[0] = d3dmeshParentNode;

	for (int i = 0; i < lodCount; i++)
	{
		defaultMeshParentNode->mChildren[i] = new aiNode;
		defaultMeshParentNode->mChildren[i]->mName = "Default_LOD" + std::to_string(i);

		shadowMeshParentNode->mChildren[i] = new aiNode;
		shadowMeshParentNode->mChildren[i]->mName = "Shadow_LOD" + std::to_string(i);
	}

	//|||||||||||||||||||||||||||||||| ASSIMP MATERIAL SETUP ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| ASSIMP MATERIAL SETUP ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| ASSIMP MATERIAL SETUP ||||||||||||||||||||||||||||||||
	//NOTE: With assimp, we have to create a set of materials for the main scene.
	//The meshes we will create later will point to one of these materials defined for the scene.

	//create empty materials
	assimpScene->mMaterials = new aiMaterial * [meshMaterialCount];

	for (int i = 0; i < meshMaterialCount; i++)
		assimpScene->mMaterials[i] = new aiMaterial(); //create an actual material object

	assimpScene->mNumMaterials = meshMaterialCount; //update the material count

	//|||||||||||||||||||||||||||||||| ASSIMP MESH SETUP ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| ASSIMP MESH SETUP ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| ASSIMP MESH SETUP ||||||||||||||||||||||||||||||||
	//NOTE: With assimp, we have to create a set of meshes for the main scene.
	//The nodes we created earlier will point to one of these meshes defined for the scene.

	assimpScene->mMeshes = new aiMesh * [totalSubmeshCount];

	for (int i = 0; i < totalSubmeshCount; i++)
		assimpScene->mMeshes[i] = new aiMesh;

	assimpScene->mNumMeshes = totalSubmeshCount;

	//|||||||||||||||||||||||||||||||| ASSIMP ASSIGNING D3DMESH NODES ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| ASSIMP ASSIGNING D3DMESH NODES ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| ASSIMP ASSIGNING D3DMESH NODES ||||||||||||||||||||||||||||||||
	//NOTE: With assimp, we have to create a set of meshes for the main scene.
	//The nodes we created earlier will point to one of these meshes defined for the scene.

	int assimpMeshIndex = 0;

	for (int i = 0; i < lodCount; i++)
	{
		int defaultMeshCurrentLODLevelSubmeshCount = d3dmeshFile->d3dmeshHeader.mLODs[i].mBatches0_ArrayLength;
		int shadowMeshCurrentLODLevelSubmeshCount = d3dmeshFile->d3dmeshHeader.mLODs[i].mBatches1_ArrayLength;

		aiNode* defaultMeshParentLOD = defaultMeshParentNode->mChildren[i];
		aiNode* shadowMeshParentLOD = shadowMeshParentNode->mChildren[i];

		defaultMeshParentLOD->mMeshes = new unsigned int[defaultMeshCurrentLODLevelSubmeshCount];

		for (int j = 0; j < defaultMeshCurrentLODLevelSubmeshCount; j++)
			defaultMeshParentLOD->mMeshes[j] = 0;

		defaultMeshParentLOD->mNumMeshes = defaultMeshCurrentLODLevelSubmeshCount;

		shadowMeshParentLOD->mMeshes = new unsigned int[shadowMeshCurrentLODLevelSubmeshCount];

		for (int j = 0; j < shadowMeshCurrentLODLevelSubmeshCount; j++)
			shadowMeshParentLOD->mMeshes[j] = 0;

		shadowMeshParentLOD->mNumMeshes = shadowMeshCurrentLODLevelSubmeshCount;

		for (int j = 0; j < defaultMeshParentLOD->mNumMeshes; j++)
		{
			defaultMeshParentLOD->mMeshes[j] = assimpMeshIndex;
			assimpMeshIndex++;
		}

		for (int j = 0; j < shadowMeshParentLOD->mNumMeshes; j++)
		{
			shadowMeshParentLOD->mMeshes[j] = assimpMeshIndex;
			assimpMeshIndex++;
		}
	}

	//|||||||||||||||||||||||||||||||| ASSIMP DEFAULT MESH CONVERSION ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| ASSIMP DEFAULT MESH CONVERSION ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| ASSIMP DEFAULT MESH CONVERSION ||||||||||||||||||||||||||||||||

	for (int i = 0; i < lodCount; i++)
	{
		for (int j = 0; j < defaultMeshParentNode->mChildren[i]->mNumMeshes; j++)
		{
			aiMesh* defaultSubmesh = assimpScene->mMeshes[defaultMeshParentNode->mChildren[i]->mMeshes[j]];
			defaultSubmesh->mName = "Default_LOD" + std::to_string(i) + "_Submesh" + std::to_string(j);

			BuildAssimpMeshFromD3DMesh(defaultSubmesh, d3dmeshFile, i, j, true);
		}

		for (int j = 0; j < shadowMeshParentNode->mChildren[i]->mNumMeshes; j++)
		{
			aiMesh* shadowSubmesh = assimpScene->mMeshes[shadowMeshParentNode->mChildren[i]->mMeshes[j]];
			shadowSubmesh->mName = "Shadow_LOD" + std::to_string(i) + "_Submesh" + std::to_string(j);

			BuildAssimpMeshFromD3DMesh(shadowSubmesh, d3dmeshFile, i, j, false);
		}
	}







	/*



	//get a reference to the mesh so we can start filling it with data
	auto pMesh = assimpScene->mMeshes[0];

	//|||||||||||||||||||||||||||||||||||||||| VERTEX POSITIONS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX POSITIONS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX POSITIONS ||||||||||||||||||||||||||||||||||||||||
	//the most important and critical part of the model, the position of each vertex in the model.

	//initalize vertex position array
	pMesh->mNumVertices = extractedMesh.vertexPositions.size(); //SELF NOTE: assign amount of verticies first... or all hell breaks loose
	pMesh->mVertices = new aiVector3D[pMesh->mNumVertices];

	//fill up the vertex position array
	for (int vertexIndex = 0; vertexIndex < pMesh->mNumVertices; vertexIndex++)
		pMesh->mVertices[vertexIndex] = aiVector3D(extractedMesh.vertexPositions[vertexIndex].x, extractedMesh.vertexPositions[vertexIndex].y, extractedMesh.vertexPositions[vertexIndex].z);

	//|||||||||||||||||||||||||||||||||||||||| VERTEX NORMALS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX NORMALS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX NORMALS ||||||||||||||||||||||||||||||||||||||||
	//the second most important part of the model, the normals (which define the direction for triangles and where they face)

	//initalize vertex normal array
	pMesh->mNormals = new aiVector3D[pMesh->mNumVertices];

	//fill up the vertex normal array
	for (int normalIndex = 0; normalIndex < pMesh->mNumVertices; normalIndex++)
		pMesh->mNormals[normalIndex] = aiVector3D(extractedMesh.vertexNormals0[normalIndex].x, extractedMesh.vertexNormals0[normalIndex].y, extractedMesh.vertexNormals0[normalIndex].z);

	//|||||||||||||||||||||||||||||||||||||||| VERTEX TANGENTS (IF USED) ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX TANGENTS (IF USED) ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX TANGENTS (IF USED) ||||||||||||||||||||||||||||||||||||||||
	//not required for a mesh, but a tangent is a unit length vector that follows a surface along the X (or U from UVW) direction.

	//not every telltale mesh has a tangent buffer, so check if we have any
	if (extractedMesh.vertexTangents.size() > 0)
	{
		//initalize the vertex tangent array
		pMesh->mTangents = new aiVector3D[pMesh->mNumVertices];

		//fill up the vertex tangent array
		for (int tangentIndex = 0; tangentIndex < pMesh->mNumVertices; tangentIndex++)
			pMesh->mTangents[tangentIndex] = aiVector3D(extractedMesh.vertexTangents[tangentIndex].x, extractedMesh.vertexTangents[tangentIndex].y, extractedMesh.vertexTangents[tangentIndex].z);
	}

	//|||||||||||||||||||||||||||||||||||||||| VERTEX UVS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX UVS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX UVS ||||||||||||||||||||||||||||||||||||||||
	//not really required for a mesh, but they are important if textures are to be used. 
	//these store coordinates for how textures are mapped onto a vertex.

	//since meshes can have a variety of UV channels defined, we have up to 8 max UV channels
	//we will check each one if it contains data and increment the channel count by one if it has data
	int uvChannels = 0;
	uvChannels += extractedMesh.vertexUVs0.size() > 0 ? 1 : 0;
	uvChannels += extractedMesh.vertexUVs1.size() > 0 ? 1 : 0;
	uvChannels += extractedMesh.vertexUVs2.size() > 0 ? 1 : 0;
	uvChannels += extractedMesh.vertexUVs3.size() > 0 ? 1 : 0;
	uvChannels += extractedMesh.vertexUVs4.size() > 0 ? 1 : 0;
	uvChannels += extractedMesh.vertexUVs5.size() > 0 ? 1 : 0;
	uvChannels += extractedMesh.vertexUVs6.size() > 0 ? 1 : 0;
	uvChannels += extractedMesh.vertexUVs7.size() > 0 ? 1 : 0;

	//if there is UV data
	if (uvChannels > 0)
	{
		//iterate through each UV channel
		for (int uvChannelIndex = 0; uvChannelIndex < uvChannels; uvChannelIndex++)
		{
			//initalize the vertex uv array
			pMesh->mTextureCoords[uvChannelIndex] = new aiVector3D[pMesh->mNumVertices];

			//initalize our reference UV array object
			std::vector<Vector2> uvs;

			//depending on the current channel index we are on, pick the appropriate extracted UV channel array
			if (uvChannelIndex == 0)
				uvs = extractedMesh.vertexUVs0;
			if (uvChannelIndex == 1)
				uvs = extractedMesh.vertexUVs1;
			if (uvChannelIndex == 2)
				uvs = extractedMesh.vertexUVs2;
			if (uvChannelIndex == 3)
				uvs = extractedMesh.vertexUVs3;
			if (uvChannelIndex == 4)
				uvs = extractedMesh.vertexUVs4;
			if (uvChannelIndex == 5)
				uvs = extractedMesh.vertexUVs5;
			if (uvChannelIndex == 6)
				uvs = extractedMesh.vertexUVs6;
			if (uvChannelIndex == 7)
				uvs = extractedMesh.vertexUVs7;

			//fill up the vertex uv array for the current uv channel
			for (int uvIndex = 0; uvIndex < pMesh->mNumVertices; uvIndex++)
				pMesh->mTextureCoords[uvChannelIndex][uvIndex] = aiVector3D(uvs[uvIndex].x, uvs[uvIndex].y, 0.0f);
		}
	}

	//|||||||||||||||||||||||||||||||||||||||| VERTEX COLORS (IF USED) ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX COLORS (IF USED) ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX COLORS (IF USED) ||||||||||||||||||||||||||||||||||||||||
	//not required for a mesh, but sometimes they contain vertex colors. 
	//these are just colors that can be used by shaders for specific tasks (i.e. multiple texture blending, or other purposes).
	//NOTE: that these vertex colors can really be used for all kinds of things... so you can't really pin down what its exactly used for in the engine as it depends on the shader used to render the mesh.

	//since meshes can have a variety of vertex color channels defined, we have up to 8 max vertex color channels
	//we will check each one if it contains data and increment the channel count by one if it has data
	int colorChannels = 0;
	colorChannels += extractedMesh.vertexColors0.size() > 0 ? 1 : 0;
	colorChannels += extractedMesh.vertexColors1.size() > 0 ? 1 : 0;
	colorChannels += extractedMesh.vertexColors2.size() > 0 ? 1 : 0;
	colorChannels += extractedMesh.vertexColors3.size() > 0 ? 1 : 0;
	colorChannels += extractedMesh.vertexColors4.size() > 0 ? 1 : 0;
	colorChannels += extractedMesh.vertexColors5.size() > 0 ? 1 : 0;
	colorChannels += extractedMesh.vertexColors6.size() > 0 ? 1 : 0;
	colorChannels += extractedMesh.vertexColors7.size() > 0 ? 1 : 0;

	//if there is vertex color data
	if (colorChannels > 0)
	{
		//iterate through each vertex color channel
		for (int colorChannelIndex = 0; colorChannelIndex < colorChannels; colorChannelIndex++)
		{
			//initalize the vertex color array
			pMesh->mColors[colorChannelIndex] = new aiColor4D[pMesh->mNumVertices];

			//initalize our reference vertex color array object
			std::vector<Vector4> colors;

			//depending on the current channel index we are on, pick the appropriate extracted color channel array
			if (colorChannelIndex == 0)
				colors = extractedMesh.vertexColors0;
			if (colorChannelIndex == 1)
				colors = extractedMesh.vertexColors1;
			if (colorChannelIndex == 2)
				colors = extractedMesh.vertexColors2;
			if (colorChannelIndex == 3)
				colors = extractedMesh.vertexColors3;
			if (colorChannelIndex == 4)
				colors = extractedMesh.vertexColors4;
			if (colorChannelIndex == 5)
				colors = extractedMesh.vertexColors5;
			if (colorChannelIndex == 6)
				colors = extractedMesh.vertexColors6;
			if (colorChannelIndex == 7)
				colors = extractedMesh.vertexColors7;

			//fill up the vertex uv array for the current vertex color channel
			for (int colorIndex = 0; colorIndex < pMesh->mNumVertices; colorIndex++)
				pMesh->mColors[colorChannelIndex][colorIndex] = aiColor4D(colors[colorIndex].x, colors[colorIndex].y, colors[colorIndex].z, colors[colorIndex].w);
		}
	}

	//|||||||||||||||||||||||||||||||||||||||| MESH TRIANGLES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| MESH TRIANGLES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| MESH TRIANGLES ||||||||||||||||||||||||||||||||||||||||
	//another really critical part of the mesh, triangles. These are essentially indexes that point to what vertex to use.

	//initalize an array of assimp faces to store our extracted triangle indicies
	std::vector<aiFace> faces;

	//iterate through each extracted triangle index
	for (int faceIndex = 0; faceIndex < extractedMesh.triangleIndicies.size(); faceIndex += 3)
	{
		//initalize a new assimp face object
		aiFace newFace = aiFace();

		//triangles are made up of 3 vertex positions, so indicies are 3
		newFace.mNumIndices = 3;
		newFace.mIndices = new unsigned int[newFace.mNumIndices];

		//assign each extracted triangle index to our assimp face
		newFace.mIndices[0] = extractedMesh.triangleIndicies[faceIndex + 0];
		newFace.mIndices[1] = extractedMesh.triangleIndicies[faceIndex + 1];
		newFace.mIndices[2] = extractedMesh.triangleIndicies[faceIndex + 2];

		//accumulate final assimp faces
		faces.push_back(newFace);
	}

	//initalize the triangle indicies array
	pMesh->mFaces = new aiFace[faces.size()];
	pMesh->mNumFaces = faces.size();

	//copy the triangle data to the assimp faces array
	std::copy(faces.begin(), faces.end(), pMesh->mFaces);
	*/

	//|||||||||||||||||||||||||||||||||||||||| ASSIMP EXPORT ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| ASSIMP EXPORT ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| ASSIMP EXPORT ||||||||||||||||||||||||||||||||||||||||

	//initalize our assimp exporter objects
	Assimp::Exporter assimpExporter;
	Assimp::ExportProperties* properties = new Assimp::ExportProperties;

	//currenty supported assimp export formats
	//[ASSIMP] ID : x Extension : x
	//[ASSIMP] ID : stp Extension : stp
	//[ASSIMP] ID : obj Extension : obj
	//[ASSIMP] ID : objnomtl Extension : obj
	//[ASSIMP] ID : stl Extension : stl
	//[ASSIMP] ID : stlb Extension : stl
	//[ASSIMP] ID : ply Extension : ply
	//[ASSIMP] ID : plyb Extension : ply
	//[ASSIMP] ID : 3ds Extension : 3ds
	//[ASSIMP] ID : gltf2 Extension : gltf
	//[ASSIMP] ID : glb2 Extension : glb
	//[ASSIMP] ID : gltf Extension : gltf
	//[ASSIMP] ID : glb Extension : glb
	//[ASSIMP] ID : assbin Extension : assbin
	//[ASSIMP] ID : assxml Extension : assxml
	//[ASSIMP] ID : x3d Extension : x3d
	//[ASSIMP] ID : fbx Extension : fbx
	//[ASSIMP] ID : fbxa Extension : fbx
	//[ASSIMP] ID : 3mf Extension : 3mf
	//[ASSIMP] ID : pbrt Extension : pbrt
	//[ASSIMP] ID : assjson Extension : json
	std::string id = "fbx";
	std::string extension = "fbx";

	//construct our final exported file path for the final mesh
	std::string exportPath = "OutputASSIMP/" + fileName + "." + extension;

	std::cout << "[ASSIMP EXPORT] Exporting..." << std::endl;

	//redirect assimp logs to the console output so we can see if something goes wrong
	auto assimpExportStream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT, NULL);
	aiAttachLogStream(&assimpExportStream);

	//export our final model using assimp
	aiReturn exportResult = assimpExporter.Export(assimpScene, id, exportPath, aiProcess_FindInvalidData | aiProcess_ValidateDataStructure, properties);

	//print to the console if we ran int oa problem
	if (exportResult == aiReturn_FAILURE || exportResult == aiReturn_OUTOFMEMORY)
	{
		std::cout << "[ASSIMP EXPORT] Export Failed! Returned " << exportResult << std::endl;
	}
	else
	{
		std::cout << "[ASSIMP EXPORT] Export Success!" << std::endl;
	}

	//detatch the log stream from assimp since we are done
	aiDetachLogStream(&assimpExportStream);
}

#endif
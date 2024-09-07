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
#include "../../Telltale/DataTypes/TelltaleD3DMeshFileV55.h"
#include "../../AssimpHelper.h"

//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP V1 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP V1 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| D3DMESH DATA TO ASSIMP V1 |||||||||||||||||||||||||||||

static void ExportD3DMeshToAssimpV1(TelltaleD3DMeshFileV55* d3dmeshFile, std::string fileName, std::string outputFolderName)
{
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

	//construct the root node to store the mesh
	aiNode* rootNode = new aiNode;
	assimpScene->mRootNode = rootNode;

	//create one empty material
	assimpScene->mMaterials = new aiMaterial * [1];
	assimpScene->mMaterials[0] = nullptr; //initalize the first material to a null pointer
	assimpScene->mNumMaterials = 1; //update the material count
	assimpScene->mMaterials[0] = new aiMaterial(); //create an actual material object

	//create one mesh
	assimpScene->mMeshes = new aiMesh * [1];
	assimpScene->mMeshes[0] = nullptr;
	assimpScene->mNumMeshes = 1;

	//assign the singular mesh to the material we created
	assimpScene->mMeshes[0] = new aiMesh();
	assimpScene->mMeshes[0]->mMaterialIndex = 0;

	assimpScene->mRootNode->mMeshes = new unsigned int[1];
	assimpScene->mRootNode->mMeshes[0] = 0;
	assimpScene->mRootNode->mNumMeshes = 1;

	//get a reference to the mesh so we can start filling it with data
	auto pMesh = assimpScene->mMeshes[0];

	//|||||||||||||||||||||||||||||||||||||||| VERTEX POSITIONS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX POSITIONS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX POSITIONS ||||||||||||||||||||||||||||||||||||||||
	//the most important and critical part of the model, the position of each vertex in the model.

	pMesh->mNumVertices = d3dmeshFile->d3dmeshData.vertexPositions[0].size(); //SELF NOTE: assign amount of verticies first... or all hell breaks loose
	pMesh->mVertices = new aiVector3D[pMesh->mNumVertices];

	for (int vertexIndex = 0; vertexIndex < pMesh->mNumVertices; vertexIndex++)
		pMesh->mVertices[vertexIndex] = GetAssimpVector3FromVector4(d3dmeshFile->d3dmeshData.vertexPositions[0][vertexIndex]);

	//|||||||||||||||||||||||||||||||||||||||| VERTEX NORMALS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX NORMALS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX NORMALS ||||||||||||||||||||||||||||||||||||||||
	//the second most important part of the model, the normals (which define the direction for triangles and where they face)

	pMesh->mNormals = new aiVector3D[pMesh->mNumVertices];

	for (int normalIndex = 0; normalIndex < pMesh->mNumVertices; normalIndex++)
		pMesh->mNormals[normalIndex] = GetAssimpVector3FromVector4(d3dmeshFile->d3dmeshData.vertexNormals[0][normalIndex]);

	//|||||||||||||||||||||||||||||||||||||||| VERTEX TANGENTS (IF USED) ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX TANGENTS (IF USED) ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX TANGENTS (IF USED) ||||||||||||||||||||||||||||||||||||||||
	//not required for a mesh, but a tangent is a unit length vector that follows a surface along the X (or U from UVW) direction.

	//not every telltale mesh has a tangent buffer, so check if we have any
	if (d3dmeshFile->d3dmeshData.vertexTangents.size() > 0)
	{
		pMesh->mTangents = new aiVector3D[pMesh->mNumVertices];

		for (int tangentIndex = 0; tangentIndex < pMesh->mNumVertices; tangentIndex++)
			pMesh->mTangents[tangentIndex] = GetAssimpVector3FromVector4(d3dmeshFile->d3dmeshData.vertexTangents[0][tangentIndex]);
	}

	//|||||||||||||||||||||||||||||||||||||||| VERTEX UVS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX UVS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX UVS ||||||||||||||||||||||||||||||||||||||||
	//not really required for a mesh, but they are important if textures are to be used. 
	//these store coordinates for how textures are mapped onto a vertex.

	//since meshes can have a variety of UV channels defined, we have up to 8 max UV channels
	//we will check each one if it contains data and increment the channel count by one if it has data
	if (d3dmeshFile->d3dmeshData.vertexUVs.size() > 0)
	{
		for (int uvChannelIndex = 0; uvChannelIndex < d3dmeshFile->d3dmeshData.vertexUVs.size(); uvChannelIndex++)
		{
			pMesh->mTextureCoords[uvChannelIndex] = new aiVector3D[pMesh->mNumVertices];

			for (int uvIndex = 0; uvIndex < pMesh->mNumVertices; uvIndex++)
				pMesh->mTextureCoords[uvChannelIndex][uvIndex] = GetAssimpVector3FromVector4(d3dmeshFile->d3dmeshData.vertexUVs[uvChannelIndex][uvIndex]);
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
	if (d3dmeshFile->d3dmeshData.vertexColors.size() > 0)
	{
		for (int colorChannelIndex = 0; colorChannelIndex < d3dmeshFile->d3dmeshData.vertexColors.size(); colorChannelIndex++)
		{
			pMesh->mColors[colorChannelIndex] = new aiColor4D[pMesh->mNumVertices];

			for (int colorIndex = 0; colorIndex < pMesh->mNumVertices; colorIndex++)
				pMesh->mColors[colorChannelIndex][colorIndex] = GetAssimpColor4FromVector4(d3dmeshFile->d3dmeshData.vertexColors[colorChannelIndex][colorIndex]);
		}
	}

	//|||||||||||||||||||||||||||||||||||||||| MESH TRIANGLES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| MESH TRIANGLES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| MESH TRIANGLES ||||||||||||||||||||||||||||||||||||||||
	//another really critical part of the mesh, triangles. These are essentially indexes that point to what vertex to use.

	//initalize an array of assimp faces to store our extracted triangle indicies
	std::vector<aiFace> faces;

	//iterate through each extracted triangle index
	for (int faceIndex = 0; faceIndex < d3dmeshFile->d3dmeshData.indexBuffers[0].size(); faceIndex += 3)
	{
		//initalize a new assimp face object
		aiFace newFace = aiFace();

		//triangles are made up of 3 vertex positions, so indicies are 3
		newFace.mNumIndices = 3;
		newFace.mIndices = new unsigned int[newFace.mNumIndices];

		//assign each extracted triangle index to our assimp face
		newFace.mIndices[0] = d3dmeshFile->d3dmeshData.indexBuffers[0][faceIndex + 0];
		newFace.mIndices[1] = d3dmeshFile->d3dmeshData.indexBuffers[0][faceIndex + 1];
		newFace.mIndices[2] = d3dmeshFile->d3dmeshData.indexBuffers[0][faceIndex + 2];

		//accumulate final assimp faces
		faces.push_back(newFace);
	}

	//initalize the triangle indicies array
	pMesh->mFaces = new aiFace[faces.size()];
	pMesh->mNumFaces = faces.size();

	//copy the triangle data to the assimp faces array
	std::copy(faces.begin(), faces.end(), pMesh->mFaces);

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
	std::string exportPath = outputFolderName + "/" + fileName + "." + extension;

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
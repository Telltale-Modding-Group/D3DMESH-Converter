#pragma once
#ifndef NEW_MESH_TO_ASSIMP_H
#define NEW_MESH_TO_ASSIMP_H

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
#include "NewMesh.h"

static void ExportAssimpMesh(NewMesh extractedMesh, std::string fileName)
{
	//if for some reason we don't have the following critical data, then we will just have to skip...
	if (extractedMesh.vertexPositions.size() <= 0)
	{
		std::cout << "ERROR! NO VERTEX POSITION DATA PROVIDED! NOT CONVERTING MESH WITH ASSIMP..." << std::endl;
		return;
	}

	if (extractedMesh.vertexNormals0.size() <= 0)
	{
		std::cout << "ERROR! NO VERTEX NORMAL DATA PROVIDED! NOT CONVERTING MESH WITH ASSIMP..." << std::endl;
		return;
	}

	if (extractedMesh.triangleIndicies.size() <= 0)
	{
		std::cout << "ERROR! NO TRIANGLE INDICIES PROVIDED! NOT CONVERTING MESH WITH ASSIMP..." << std::endl;
		return;
	}

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
	std::string exportPath = "Output/" + fileName + "." + extension;

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
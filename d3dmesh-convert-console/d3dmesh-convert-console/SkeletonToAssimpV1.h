#pragma once
#ifndef SKELETON_TO_ASSIMP_V1_H
#define SKELETON_TO_ASSIMP_V1_H

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
#include "../../Application/Application_Macros.h"
#include "../../Telltale/DataTypes/TelltaleSkeletonFile.h"
#include "../../Helper/AssimpHelper.h"

//||||||||||||||||||||||||||||| SKELETON TO ASSIMP V1 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| SKELETON TO ASSIMP V1 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| SKELETON TO ASSIMP V1 |||||||||||||||||||||||||||||

static void BuildAssimpSkeletonFromSkeletonV1(TelltaleSkeletonFile* sklFile, std::string fileName, std::string outputFolderName)
{
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

	//|||||||||||||||||||||||||||||||| ASSIMP SKELETON NODES SETUP ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| ASSIMP SKELETON NODES SETUP ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| ASSIMP SKELETON NODES SETUP ||||||||||||||||||||||||||||||||
	//Using assimp, we will create our node tree for the SKL for organization

	assimpScene->mRootNode->mChildren = new aiNode * [sklFile->skeleton.mEntryCount];
	assimpScene->mRootNode->mNumChildren = sklFile->skeleton.mEntryCount;

	for (int i = 0; i < sklFile->skeleton.mEntryCount; i++)
	{
		SkeletonEntry telltaleSkeletonEntry = sklFile->skeleton.mEntries[i];

		aiNode* boneNode = new aiNode;
		boneNode->mName = aiString(telltaleSkeletonEntry.mJointName.ValueString());

		assimpScene->mRootNode->mChildren[i] = boneNode;
	}

	for (int i = 0; i < sklFile->skeleton.mEntryCount; i++)
	{
		SkeletonEntry telltaleSkeletonEntry = sklFile->skeleton.mEntries[i];

		std::string jointName = telltaleSkeletonEntry.mJointName.ValueString();
		std::string jointParentName = telltaleSkeletonEntry.mParentName.ValueString();

		aiNode* jointNode = assimpScene->mRootNode->FindNode(jointName.c_str());
		aiNode* jointParentNode = assimpScene->mRootNode->FindNode(jointParentName.c_str());

		//if (jointParentNode != nullptr)
			//ParentAssimpNodeToAssimpNode(jointNode, jointParentNode);
			//jointNode->mParent = jointParentNode;

		//aiVector3D transformScale = GetAssimpVector3FromVector3(telltaleSkeletonEntry.mAnimTranslationScale);
		//aiVector3D transformScale = GetAssimpVector3FromVector3(telltaleSkeletonEntry.mGlobalTranslationScale);
		aiVector3D transformScale = GetAssimpVector3FromVector3(telltaleSkeletonEntry.mLocalTranslationScale);
		aiQuaternion transformRotation = GetAssimpQuaternionFromQuaternion(telltaleSkeletonEntry.mLocalQuat);
		aiVector3D transformPosition = GetAssimpVector3FromVector3(telltaleSkeletonEntry.mLocalPos);

		aiMatrix4x4 sklBoneNodeTransform = aiMatrix4x4();
		aiMatrix4FromScalingQuaternionPosition(
			&sklBoneNodeTransform,
			&transformScale,
			&transformRotation,
			&transformPosition);

		jointNode->mTransformation = sklBoneNodeTransform;

		//aiSkeletonBone* assimpSkeletonBone = assimpSkeleton->mBones[i];
		//assimpSkeletonBone->m
	}

	//|||||||||||||||||||||||||||||||| ASSIMP SKELETON CONVERSION ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| ASSIMP SKELETON CONVERSION ||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||| ASSIMP SKELETON CONVERSION ||||||||||||||||||||||||||||||||

	assimpScene->mSkeletons = new aiSkeleton * [1];
	assimpScene->mNumSkeletons = 1;

	aiSkeleton* assimpSkeleton = new aiSkeleton;
	assimpSkeleton->mName = aiString("Telltale Skeleton");
	assimpSkeleton->mBones = new aiSkeletonBone * [sklFile->skeleton.mEntryCount];
	assimpSkeleton->mNumBones = sklFile->skeleton.mEntryCount;

	for (int i = 0; i < assimpSkeleton->mNumBones; i++)
	{
		//aiSkeletonBone* assimpSkeletonBone = assimpSkeleton->mBones[i];
		//assimpSkeletonBone->m
	}

	//if (d3dmeshFile->HasBones())
	//{
		//aiBone assimpBone = aiBone();
		//assimpBone.mArmature
		//assimpBone.mName
		//assimpBone.mNode
		//assimpBone.mOffsetMatrix
		//assimpBone.mNumWeights
		//assimpBone.mWeights

		//aiSkeleton assimpSkeleton = aiSkeleton();
		//assimpSkeleton.mName
		//assimpSkeleton.mNumBones
		//assimpSkeleton.mBones

		//aiSkeletonBone assimpSkeletonBone = aiSkeletonBone();
		//assimpSkeletonBone.mArmature
		//assimpSkeletonBone.mLocalMatrix
		//assimpSkeletonBone.mOffsetMatrix
		//assimpSkeletonBone.mMeshId
		//assimpSkeletonBone.mNode
		//assimpSkeletonBone.mParent
		//assimpSkeletonBone.mWeights
		//assimpSkeletonBone.mNumnWeights
	//}


	//|||||||||||||||||||||||||||||||||||||||| ASSIMP EXPORT ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| ASSIMP EXPORT ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| ASSIMP EXPORT ||||||||||||||||||||||||||||||||||||||||

	//initalize our assimp exporter objects
	Assimp::Exporter assimpExporter;
	Assimp::ExportProperties* properties = new Assimp::ExportProperties;

	//construct our final exported file path for the final mesh
	std::string exportPath = outputFolderName + "/" + fileName + "." + ASSIMP_EXPORT_EXTENSION;

	std::cout << "[ASSIMP EXPORT] Exporting..." << std::endl;

	//redirect assimp logs to the console output so we can see if something goes wrong
	auto assimpExportStream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT, NULL);
	aiAttachLogStream(&assimpExportStream);

	//export our final model using assimp
	aiReturn exportResult = assimpExporter.Export(assimpScene, ASSIMP_EXPORT_ID, exportPath, aiProcess_FindInvalidData | aiProcess_ValidateDataStructure, properties);

	//print to the console if we ran int oa problem
	if (exportResult == aiReturn_FAILURE || exportResult == aiReturn_OUTOFMEMORY)
		std::cout << "[ASSIMP EXPORT] Export Failed! Returned " << exportResult << std::endl;
	else
		std::cout << "[ASSIMP EXPORT] Export Success!" << std::endl;

	//detatch the log stream from assimp since we are done
	aiDetachLogStream(&assimpExportStream);
}

#endif
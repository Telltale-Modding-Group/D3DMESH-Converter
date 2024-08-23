//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||

//#define FULL_CONSOLE_OUTPUT

//Standard C++ Library
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <stdlib.h>
#include <time.h>

//Custom
#include "TelltaleD3DMeshFileV55.h"
#include "D3DMeshToText.h"
#include "NewMesh.h"
#include "NewMeshToAssimp.h"

//|||||||||||||||||||||||||||||||||||||||| MAIN ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| MAIN ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| MAIN ||||||||||||||||||||||||||||||||||||||||

int main()
{
	//|||||||||||||||||||||||||||||||||||||||| READING D3DMESH FILES FROM DATA FOLDER ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READING D3DMESH FILES FROM DATA FOLDER ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READING D3DMESH FILES FROM DATA FOLDER ||||||||||||||||||||||||||||||||||||||||
	//First we start by reading all of the .d3dmesh files in the Data folder relative to the application.
	//We read them into multiple array so we can iterate through each one and parse them

	//array of the d3dmesh file paths relative to the application
	std::vector<std::string> d3dmeshFilePaths;

	//array of the d3dmesh file names (with extension) relative to the application
	std::vector<std::string> d3dmeshFileNames;

	//array of the d3dmesh file byte sizes (only used for comparison later to check if we've reached the end of the file)
	std::vector<unsigned long> d3dmeshFileSizes;

	//iterate through every file that we find in the Data/ folder relative to the application
	for (const auto& entry : std::filesystem::recursive_directory_iterator("Data"))
	{
		//extract the following path information
		std::string assetFilePath = entry.path().string();
		std::string assetFileName = entry.path().filename().string();

		//if the extension matches what we are looking for, then add them to our arrays
		if (entry.path().extension() == ".d3dmesh")
		{
			d3dmeshFilePaths.push_back(assetFilePath);
			d3dmeshFileNames.push_back(assetFileName);
			d3dmeshFileSizes.push_back(entry.file_size());
		}
	}

	//|||||||||||||||||||||||||||||||||||||||| PARSING D3DMESH FILES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| PARSING D3DMESH FILES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| PARSING D3DMESH FILES ||||||||||||||||||||||||||||||||||||||||
	//Here we begin the main logic of parsing the data inside EACH d3dmesh file.

	for (int d3dmeshFilePathIndex = 0; d3dmeshFilePathIndex < d3dmeshFilePaths.size(); d3dmeshFilePathIndex++)
	{
		std::string currentD3DMESH_FilePath = d3dmeshFilePaths[d3dmeshFilePathIndex];
		std::string currentD3DMESH_FileName = d3dmeshFileNames[d3dmeshFilePathIndex];
		unsigned long currentD3DMESH_FileSize = d3dmeshFileSizes[d3dmeshFilePathIndex];

		//|||||||||||||||||||||||||||||||||||||||| OPEN D3DMESH FILE ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| OPEN D3DMESH FILE ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| OPEN D3DMESH FILE ||||||||||||||||||||||||||||||||||||||||
		//Here we open a binary input file stream of the current d3dmesh file

		//print the name to the console so we can see what file we are on
		std::cout << "READING... " << currentD3DMESH_FilePath << std::endl;
		std::cout << "[FILE INFO] File Size Bytes: " << currentD3DMESH_FileSize << std::endl;

		//create and open an input file stream
		std::ifstream currentD3DMESH_inputFileStream;
		currentD3DMESH_inputFileStream.open(currentD3DMESH_FilePath, std::fstream::in | std::fstream::binary);

		//parse the d3dmesh file
		TelltaleD3DMeshFileV55 d3dmeshFile = TelltaleD3DMeshFileV55(&currentD3DMESH_inputFileStream);

		//close the stream afterwards
		currentD3DMESH_inputFileStream.close();

		//|||||||||||||||||||||||||||||||||||||||| TXT OUTPUT ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| TXT OUTPUT ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| TXT OUTPUT ||||||||||||||||||||||||||||||||||||||||
		//This outputs all of the contents of the D3DMESH file into a generic text file (no json used)

		WriteD3DMeshToText(currentD3DMESH_FileName, d3dmeshFile);

		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V1 ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V1 ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V1 ||||||||||||||||||||||||||||||||||||||||
		//First attempt at doing a conversion of a d3dmesh to a standard model format (THIS DOES WORK... BUT THERE ARE PROBLEMS)
		//NOTE: This simply shoves the entire mesh into an assimp mesh, ignoring all LODs. 
		//This atleast works for getting a useable mesh export, however there are no materials/lods/submeshes/etc... it's a basic single mesh

		NewMesh extractedMesh = {};
		extractedMesh.triangleIndicies = d3dmeshFile.d3dmeshData.indexBuffer0;
		extractedMesh.vertexPositions = d3dmeshFile.d3dmeshData.vertexPositions;
		extractedMesh.vertexNormals0 = d3dmeshFile.d3dmeshData.vertexNormals0;
		ExportAssimpMesh(extractedMesh, currentD3DMESH_FileName);

		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V2 ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V2 ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V2 ||||||||||||||||||||||||||||||||||||||||
		//Attempt #1 At creating LODs/Submeshes from the D3DMESH (does not work)

		/*
		std::vector<ExtractedLOD> extractedLODs;

		for (int i = 0; i < d3dmeshFile.d3dmeshHeader.mLODs.size(); i++)
		{
			T3MeshLOD* mLOD = &d3dmeshFile.d3dmeshHeader.mLODs[i];
			ExtractedLOD extractedLOD{};

			for (int j = 0; j < mLOD->mBatches0_ArrayLength; j++)
			{
				ExtractedMesh extractedMesh{};
				extractedLOD.submeshes.push_back(extractedMesh);
			}

			extractedLODs.push_back(extractedLOD);
		}


		std::ofstream testOutputTextFile;
		std::string testOutputTextFilePath = "Output/" + currentD3DMESH_FileName + "_EXTRACTED_MESH_DATA.txt";
		testOutputTextFile.open(testOutputTextFilePath);

		for (int x = 0; x < d3dmeshFile.bufferData.indexBuffer0.size(); x++)
		{
			std::string line = "Item: " + std::to_string(x) + " | Triangle Index: " + std::to_string(d3dmeshFile.bufferData.indexBuffer0[x]) + " \n";
			testOutputTextFile.write(line.c_str(), line.length());
		}

		testOutputTextFile.close();

		for (int i = 0; i < d3dmeshFile.d3dmeshHeader.mLODs.size(); i++)
		{
			T3MeshLOD* mLOD = &d3dmeshFile.d3dmeshHeader.mLODs[i];
			ExtractedLOD* extractedLOD = &extractedLODs[i];

			for (int j = 0; j < extractedLOD->submeshes.size(); j++)
			{
				T3MeshBatch* mBatch = &mLOD->mBatches0[j];
				ExtractedMesh* extractedMesh = &extractedLOD->submeshes[j];

				//for (int x = 0; x < mBatch->mNumPrimitives; x++)
					//extractedMesh->triangleIndicies0.push_back(d3dmeshFile.bufferData.triangleIndicies0[x + mBatch->mBaseIndex]);

				//for (int x = 0; x < mBatch->mNumPrimitives; x++)
					//extractedMesh->triangleIndicies0.push_back(d3dmeshFile.bufferData.triangleIndicies0[x + mBatch->mStartIndex] + mBatch->mBaseIndex);

				//for (int x = 0; x < mBatch->mNumPrimitives * 3; x++)
					//extractedMesh->triangleIndicies0.push_back(d3dmeshFile.bufferData.triangleIndicies0[x + mBatch->mStartIndex] + mBatch->mBaseIndex);

				//for (int x = 0; x < mBatch->mNumPrimitives; x++)
				//{
					//extractedMesh->triangleIndicies0.push_back(d3dmeshFile.bufferData.triangleIndicies0[x + mBatch->mStartIndex + mBatch->mBaseIndex]);
					//extractedMesh->triangleIndicies0.push_back(d3dmeshFile.bufferData.triangleIndicies0[x + mBatch->mStartIndex] + mBatch->mBaseIndex);
				//}

				//for (int x = mLOD->mVertexStart + mBatch->mMinVertIndex; x < mLOD->mVertexCount; x++)
				//for (int x = mLOD->mVertexStart; x < mLOD->mVertexCount; x++)
				//{
					//extractedMesh->vertexPositions.push_back(d3dmeshFile.bufferData.vertexPositions[x]);
					//extractedMesh->vertexNormals0.push_back(d3dmeshFile.bufferData.vertexNormals0[x]);
				//}

				std::ofstream testOutputTextFile2;
				std::string newPath2 = "Output/LOD_" + std::to_string(i) + "_SUBMESH_" + std::to_string(j) + "_" + currentD3DMESH_FileName + ".txt";
				testOutputTextFile2.open(newPath2);

				std::string line2a1 = "mNumPrimitives: " + std::to_string(mBatch->mNumPrimitives) + " \n";
				std::string line2a2 = "mBaseIndex: " + std::to_string(mBatch->mBaseIndex) + " \n";
				std::string line2a3 = "mMaxVertIndex: " + std::to_string(mBatch->mMaxVertIndex) + " \n";
				std::string line2a4 = "mMinVertIndex: " + std::to_string(mBatch->mMinVertIndex) + " \n";
				std::string line2a5 = "mStartIndex: " + std::to_string(mBatch->mStartIndex) + " \n";
				std::string line2a6 = "mNumIndices: " + std::to_string(mBatch->mNumIndices) + " \n";
				std::string line2a7 = "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| \n";
				testOutputTextFile2.write(line2a1.c_str(), line2a1.length());
				testOutputTextFile2.write(line2a2.c_str(), line2a2.length());
				testOutputTextFile2.write(line2a3.c_str(), line2a3.length());
				testOutputTextFile2.write(line2a4.c_str(), line2a4.length());
				testOutputTextFile2.write(line2a5.c_str(), line2a5.length());
				testOutputTextFile2.write(line2a6.c_str(), line2a6.length());
				testOutputTextFile2.write(line2a7.c_str(), line2a7.length());

				for (int x = 0; x < mBatch->mNumPrimitives; x++)
				{
					int loopCalculatedIndex = x + mBatch->mStartIndex;
					int pickedTriangleIndex = d3dmeshFile.bufferData.indexBuffer0[loopCalculatedIndex];
					unsigned int adjustedTriangleIndex = pickedTriangleIndex + mBatch->mBaseIndex;
					std::string line2b = "Loop Index: " + std::to_string(x) + " | Calculated Triangle Index Picker: " + std::to_string(loopCalculatedIndex) + " | Picked Triangle Index Original Value: " + std::to_string(pickedTriangleIndex) + " | Triangle Index with added Base Index to value: " + std::to_string(adjustedTriangleIndex) + " \n";
					testOutputTextFile2.write(line2b.c_str(), line2b.length());
				}

				testOutputTextFile2.close();




				//std::string newPath = "LOD_" + std::to_string(i) + "_SUBMESH_" + std::to_string(j) + "_" + currentD3DMESH_FileName;
				//ExportAssimpMesh(*extractedMesh, newPath);
			}
		}
		*/

		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V3 ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V3 ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V3 ||||||||||||||||||||||||||||||||||||||||
		//Attempt #2 At creating LODs/Submeshes from the D3DMESH (does not work)

		/*
		std::vector<ExtractedLOD> extractedLODs;

		for (int i = 0; i < d3dmeshFile.d3dmeshHeader.mLODs.size(); i++)
		{
			T3MeshLOD* mLOD = &d3dmeshFile.d3dmeshHeader.mLODs[i];
			ExtractedLOD extractedLOD{};

			for (int j = 0; j < mLOD->mBatches0_ArrayLength; j++)
			{
				T3MeshBatch mBatch = mLOD->mBatches0[j];
				ExtractedMesh extractedMesh{};

				//|||||||||||||||||||||||||||||||||||||||| GET TRIANGLE SET ||||||||||||||||||||||||||||||||||||||||
				//|||||||||||||||||||||||||||||||||||||||| GET TRIANGLE SET ||||||||||||||||||||||||||||||||||||||||
				//|||||||||||||||||||||||||||||||||||||||| GET TRIANGLE SET ||||||||||||||||||||||||||||||||||||||||
				//NOTE: for each batch set, if we do [mBatch.mNumPrimitives - mBatch.mStartIndex] that is the total amount of actual primitives in the batch
				//Conversely, if we add up the results of [mBatch.mNumPrimitives - mBatch.mStartIndex] from each batch we will match mLOD->mNumPrimitives (atleast for the default mesh, or mBatches0)

				//for (int x = 0; x < mBatch.mNumPrimitives; x++)
				for (int x = mBatch.mStartIndex; x < mBatch.mNumPrimitives; x++)
				{
					//int finalIndex = x + mBatch.mBaseIndex + mBatch.mStartIndex;
					//extractedMesh.triangleIndicies.push_back(d3dmeshFile.bufferData.indexBuffer0[finalIndex]);

					//int finalIndex = x + mBatch.mStartIndex;
					//extractedMesh.triangleIndicies.push_back(d3dmeshFile.bufferData.indexBuffer0[finalIndex] + mBatch.mBaseIndex);

					//int finalIndex = x + mBatch.mBaseIndex;

					int selectedTriangleIndex = d3dmeshFile.bufferData.indexBuffer0[x];
					extractedMesh.triangleIndicies.push_back(selectedTriangleIndex);

					//mBatch.mNumPrimitives - mBatch.mStartIndex = triangle count for this batch set

					if (selectedTriangleIndex > d3dmeshFile.d3dmeshHeader.mVertexCount)
						std::cout << "PASSED THE VERTEX COUNT" << std::endl;
				}

				//|||||||||||||||||||||||||||||||||||||||| GET VERTEX SET ||||||||||||||||||||||||||||||||||||||||
				//|||||||||||||||||||||||||||||||||||||||| GET VERTEX SET ||||||||||||||||||||||||||||||||||||||||
				//|||||||||||||||||||||||||||||||||||||||| GET VERTEX SET ||||||||||||||||||||||||||||||||||||||||
				int vertexSize = mBatch.mMaxVertIndex - mBatch.mMinVertIndex;

				//for (int x = mLOD->mVertexStart + mBatch.mBaseIndex; x < mLOD->mVertexCount; x++)
				//for (int x = 0; x < vertexSize; x++)
				//{
					//extractedMesh.vertexPositions.push_back(d3dmeshFile.bufferData.vertexPositions[x]);
					//extractedMesh.vertexNormals0.push_back(d3dmeshFile.bufferData.vertexNormals0[x]);
				//}

				extractedMesh.vertexPositions = d3dmeshFile.bufferData.vertexPositions;
				extractedMesh.vertexNormals0 = d3dmeshFile.bufferData.vertexNormals0;

				//|||||||||||||||||||||||||||||||||||||||| ASSIMP EXPORT TEST ||||||||||||||||||||||||||||||||||||||||
				//|||||||||||||||||||||||||||||||||||||||| ASSIMP EXPORT TEST ||||||||||||||||||||||||||||||||||||||||
				//|||||||||||||||||||||||||||||||||||||||| ASSIMP EXPORT TEST ||||||||||||||||||||||||||||||||||||||||

				std::string newPath = "LOD_" + std::to_string(i) + "_SUBMESH_" + std::to_string(j) + "_" + currentD3DMESH_FileName;
				ExportAssimpMesh(extractedMesh, newPath);

				//extractedLOD.submeshes.push_back(extractedMesh);
			}

			extractedLODs.push_back(extractedLOD);
		}
		*/

		//|||||||||||||||||||||||||||||||||||||||| CONSOLE OUTPUT ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| CONSOLE OUTPUT ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| CONSOLE OUTPUT ||||||||||||||||||||||||||||||||||||||||
		//This will be moved later, but it's here at the moment for archival purposes as it will be useful for debugging later.

		//std::cout << "||||||||||||||||||||||||||||||||||||||||||" << std::endl;
		//std::cout << "||||||||||||||||||||||||||||||||||||||||||" << std::endl;
		//std::cout << "||||||||||||||||||||||||||||||||||||||||||" << std::endl;
		//std::cout << "[D3DMESH HEADER] mNameBlockSize: " << d3dmesh.mNameBlockSize << std::endl;
		//std::cout << "[D3DMESH HEADER] mNameLength: " << d3dmesh.mName.length() << std::endl;
		//std::cout << "[D3DMESH HEADER] mName: " << d3dmesh.mName << std::endl;
		//std::cout << "[D3DMESH HEADER] mVersion: " << mVersion << std::endl;
		//std::cout << "[D3DMESH HEADER] mToolProps: " << mToolProps << std::endl;
		//std::cout << "[D3DMESH HEADER] mLightmapGlobalScale: " << std::to_string(mLightmapGlobalScale) << std::endl;
		//std::cout << "[D3DMESH HEADER] mLightmapTexCoordVersion: " << mLightmapTexCoordVersion << std::endl;
		//std::cout << "[D3DMESH HEADER] mLODParamCRC: " << mLODParamCRC << std::endl;
		//std::cout << "[D3DMESH HEADER] mInternalResourcesCount: " << mInternalResourcesCount << std::endl;
		//std::cout << "[D3DMESH HEADER] mHasOcclusionData: " << d3dmesh.mHasOcclusionData << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mT3MeshDataBlockSize: " << mT3MeshDataBlockSize << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mLODs_ArrayCapacity: " << d3dmesh.mLODs_ArrayCapacity << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mLODs_ArrayLength: " << d3dmesh.mLODs_ArrayLength << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mTextures_ArrayCapacity: " << mTextures_ArrayCapacity << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mTextures_ArrayLength: " << mTextures_ArrayLength << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mMaterials_ArrayCapacity: " << mMaterials_ArrayCapacity << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mMaterials_ArrayLength: " << mMaterials_ArrayLength << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mMaterialOverrides_ArrayCapacity: " << mMaterialOverrides_ArrayCapacity << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mMaterialOverrides_ArrayLength: " << mMaterialOverrides_ArrayLength << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mBones_ArrayCapacity: " << mBones_ArrayCapacity << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mBones_ArrayLength: " << mBones_ArrayLength << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mLocalTransforms_ArrayCapacity: " << mLocalTransforms_ArrayCapacity << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mLocalTransforms_ArrayLength: " << d3dmesh.mLocalTransforms_ArrayLength << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mLocalTransforms_ArrayCapacity: " << mMaterialRequirements_BlockSize << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mPasses_BlockSize: " << mPasses_BlockSize << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mPasses: " << mPasses << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mChannels_BlockSize: " << mChannels_BlockSize << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mChannels1: " << mChannels1 << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mChannels2: " << mChannels2 << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mInputs_BlockSize: " << mInputs_BlockSize << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mInputs1: " << mInputs1 << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mInputs2: " << mInputs2 << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mInputs3: " << mInputs3 << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mVertexStreams_BlockSize: " << mVertexStreams_BlockSize << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mVertexStreams: " << mVertexStreams << std::endl;
		//std::printf("[D3DMESH HEADER] [T3MESHDATA] [BOUNDING BOX] mMin %f %f %f \n", mBoundingBox.mMin.x, mBoundingBox.mMin.y, mBoundingBox.mMin.z);
		//std::printf("[D3DMESH HEADER] [T3MESHDATA] [BOUNDING BOX] mMax %f %f %f \n", mBoundingBox.mMax.x, mBoundingBox.mMax.y, mBoundingBox.mMax.z);
		//std::printf("[D3DMESH HEADER] [T3MESHDATA] [BOUNDING SPHERE] mCenter %f %f %f \n", mBoundingSphere.mCenter.x, mBoundingSphere.mCenter.y, mBoundingSphere.mCenter.z);
		//std::printf("[D3DMESH HEADER] [T3MESHDATA] [BOUNDING SPHERE] mRadius %f \n", mBoundingSphere.mRadius);
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mEndianType: " << mEndianType << std::endl;
		//std::printf("[D3DMESH HEADER] [T3MESHDATA] mPositionScale %f %f %f \n", mPositionScale.x, mPositionScale.y, mPositionScale.z);
		//std::printf("[D3DMESH HEADER] [T3MESHDATA] mPositionWScale %f %f %f \n", mPositionWScale.x, mPositionWScale.y, mPositionWScale.z);
		//std::printf("[D3DMESH HEADER] [T3MESHDATA] mPositionOffset %f %f %f \n", mPositionOffset.x, mPositionOffset.y, mPositionOffset.z);
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mLightmapTexelAreaPerSurfaceArea: " << std::to_string(mLightmapTexelAreaPerSurfaceArea) << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mPropertyKeyBase: " << mPropertyKeyBase << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mVertexCount: " << mVertexCount << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mFlags: " << mFlags << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mMeshPreload_BlockSize: " << mMeshPreload_BlockSize << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] UNKNOWN1: " << UNKNOWN1 << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] UNKNOWN2: " << UNKNOWN2 << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3GFXVERTEXSTATE] mVertexCountPerInstance: " << mVertexCountPerInstance << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3GFXVERTEXSTATE] mIndexBufferCount: " << mIndexBufferCount << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3GFXVERTEXSTATE] mVertexBufferCount: " << mVertexBufferCount << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3GFXVERTEXSTATE] mAttributeCount: " << mAttributeCount << std::endl;

		/*
		for (int GFXPlatformVertexAttributeLoopIndex = 0; GFXPlatformVertexAttributeLoopIndex < d3dmesh.GFXPlatformAttributeParamsArray.size(); GFXPlatformVertexAttributeLoopIndex++)
		{
			GFXPlatformAttributeParams params = d3dmesh.GFXPlatformAttributeParamsArray[GFXPlatformVertexAttributeLoopIndex];

			std::printf("---------------------------------------------\n");
			std::printf("[D3DMESH HEADER] [T3MESHDATA] [GFXPLATFORMATTRIBUTEPARAMS] [ELEMENT %i] mAttribute: %i %s \n", GFXPlatformVertexAttributeLoopIndex, params.mAttribute, GetGFXPlatformVertexAttributeName(params.mAttribute).c_str());
			std::printf("[D3DMESH HEADER] [T3MESHDATA] [GFXPLATFORMATTRIBUTEPARAMS] [ELEMENT %i] mFormat: %i %s \n", GFXPlatformVertexAttributeLoopIndex, params.mFormat, GetGFXPlatformFormatName(params.mFormat).c_str());
			std::printf("[D3DMESH HEADER] [T3MESHDATA] [GFXPLATFORMATTRIBUTEPARAMS] [ELEMENT %i] mAttributeIndex: %i \n", GFXPlatformVertexAttributeLoopIndex, params.mAttributeIndex);
			std::printf("[D3DMESH HEADER] [T3MESHDATA] [GFXPLATFORMATTRIBUTEPARAMS] [ELEMENT %i] mBufferIndex: %i \n", GFXPlatformVertexAttributeLoopIndex, params.mBufferIndex);
			std::printf("[D3DMESH HEADER] [T3MESHDATA] [GFXPLATFORMATTRIBUTEPARAMS] [ELEMENT %i] mBufferOffset: %i \n", GFXPlatformVertexAttributeLoopIndex, params.mBufferOffset);
		}
		*/

		/*
		for (int indexBufferLoopIndex = 0; indexBufferLoopIndex < d3dmesh.mIndexBuffers.size(); indexBufferLoopIndex++)
		{
			T3GFXBuffer mIndexBuffer = ReadTelltaleGFXBufferFromBinary(&currentD3DMESH_inputFileStream);

			std::printf("---------------------------------------------\n");
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mIndexBuffer [ELEMENT %i] mResourceUsage: %i \n", indexBufferLoopIndex, mIndexBuffer.mResourceUsage);
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mIndexBuffer [ELEMENT %i] mBufferFormat: %i %s \n", indexBufferLoopIndex, mIndexBuffer.mBufferFormat, GetGFXPlatformFormatName(mIndexBuffer.mBufferFormat).c_str());
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mIndexBuffer [ELEMENT %i] mBufferUsage: %i \n", indexBufferLoopIndex, mIndexBuffer.mBufferUsage);
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mIndexBuffer [ELEMENT %i] mCount: %i \n", indexBufferLoopIndex, mIndexBuffer.mCount);
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mIndexBuffer [ELEMENT %i] mStride: %i \n", indexBufferLoopIndex, mIndexBuffer.mStride);
		}
		*/

		/*
		for (int vertexBufferLoopIndex = 0; vertexBufferLoopIndex < d3dmesh.mVertexBufferCount; vertexBufferLoopIndex++)
		{
			T3GFXBuffer mVertexBuffer = ReadTelltaleGFXBufferFromBinary(&currentD3DMESH_inputFileStream);

			std::printf("---------------------------------------------\n");
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mVertexBuffer [ELEMENT %i] mResourceUsage: %i \n", vertexBufferLoopIndex, mVertexBuffer.mResourceUsage);
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mVertexBuffer [ELEMENT %i] mBufferFormat: %i %s \n", vertexBufferLoopIndex, mVertexBuffer.mBufferFormat, GetGFXPlatformFormatName(mVertexBuffer.mBufferFormat).c_str());
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mVertexBuffer [ELEMENT %i] mBufferUsage: %i \n", vertexBufferLoopIndex, mVertexBuffer.mBufferUsage);
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mVertexBuffer [ELEMENT %i] mCount: %i \n", vertexBufferLoopIndex, mVertexBuffer.mCount);
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mVertexBuffer [ELEMENT %i] mStride: %i \n", vertexBufferLoopIndex, mVertexBuffer.mStride);
		}
		*/

		/*
		std::printf("Extracted Triangle Indicies %u \n", triangleIndicies0.size());
		std::printf("Extracted Vertex Positions %u \n", vertexPositions.size());

		std::printf("Extracted Vertex Normals (Set 0) %u \n", vertexNormals0.size());

		if (vertexNormals1.size() > 0)
			std::printf("Extracted Vertex Normals (Set 1) %u \n", vertexNormals1.size());
		if (vertexNormals2.size() > 0)
			std::printf("Extracted Vertex Normals (Set 2) %u \n", vertexNormals2.size());
		if (vertexNormals3.size() > 0)
			std::printf("Extracted Vertex Normals (Set 3) %u \n", vertexNormals3.size());

		std::printf("Extracted Vertex Tangents %u \n", vertexTangents.size());
		std::printf("Extracted Vertex UVs(Channel 0) %u \n", vertexUVs0.size());

		if (vertexUVs1.size() > 0)
			std::printf("Extracted Vertex UVs (Channel 1) %u \n", vertexUVs1.size());
		if (vertexUVs2.size() > 0)
			std::printf("Extracted Vertex UVs (Channel 2) %u \n", vertexUVs2.size());
		if (vertexUVs3.size() > 0)
			std::printf("Extracted Vertex UVs (Channel 3) %u \n", vertexUVs3.size());
		if (vertexUVs4.size() > 0)
			std::printf("Extracted Vertex UVs (Channel 4) %u \n", vertexUVs4.size());
		if (vertexUVs5.size() > 0)
			std::printf("Extracted Vertex UVs (Channel 5) %u \n", vertexUVs5.size());
		if (vertexUVs6.size() > 0)
			std::printf("Extracted Vertex UVs (Channel 6) %u \n", vertexUVs6.size());
		if (vertexUVs7.size() > 0)
			std::printf("Extracted Vertex UVs (Channel 7) %u \n", vertexUVs7.size());

		if (vertexColors0.size() > 0)
			std::printf("Extracted Vertex Colors0 %u \n", vertexColors0.size());
		if (vertexColors1.size() > 0)
			std::printf("Extracted Vertex Colors1 %u \n", vertexColors1.size());
		if (vertexColors2.size() > 0)
			std::printf("Extracted Vertex Colors2 %u \n", vertexColors2.size());
		if (vertexColors3.size() > 0)
			std::printf("Extracted Vertex Colors3 %u \n", vertexColors3.size());
		if (vertexColors4.size() > 0)
			std::printf("Extracted Vertex Colors4 %u \n", vertexColors4.size());
		if (vertexColors5.size() > 0)
			std::printf("Extracted Vertex Colors5 %u \n", vertexColors5.size());
		if (vertexColors6.size() > 0)
			std::printf("Extracted Vertex Colors6 %u \n", vertexColors6.size());
		if (vertexColors7.size() > 0)
			std::printf("Extracted Vertex Colors7 %u \n", vertexColors7.size());

		if (vertexBlendIndex0.size() > 0)
			std::printf("Extracted Vertex Blend Index %u \n", vertexBlendIndex0.size());

		if (vertexBlendWeight0.size() > 0)
			std::printf("Extracted Vertex Blend Weight %u \n", vertexBlendWeight0.size());
		*/

		//|||||||||||||||||||||||||||||||||||||||| JSON EXPORT ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| JSON EXPORT ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| JSON EXPORT ||||||||||||||||||||||||||||||||||||||||
		//WIP: This will be fully implemented later but the goal here is to parse a D3DMESH and output a human readable .json
		//This .json will be used in the future for doing conversions to and back to D3DMESH (just like the D3DTX DDS converter)		

		/*
		nlohmann::json jsonExport;

		nlohmann::json jsonTelltaleMetaHeader = nlohmann::json
		{
			{ "mMetaStreamVersion", metaHeader.mMetaStreamVersion },
			{ "mDefaultSectionChunkSize", metaHeader.mDefaultSectionChunkSize },
			{ "mDebugSectionChunkSize", metaHeader.mDebugSectionChunkSize },
			{ "mAsyncSectionChunkSize", metaHeader.mAsyncSectionChunkSize },
			{ "mClassNamesLength", metaHeader.mClassNamesLength },
		};

		Vector2 testVector2 = Vector2();

		testVector2.ToJson(jsonExport);

		std::ofstream jsonOutputFileStream;
		std::string jsonExportPath = "OutputJSON/" + currentD3DMESH_FileName + ".json";
		jsonOutputFileStream.open(jsonExportPath);

		std::string jsonDump = jsonExport.dump(4);
		jsonOutputFileStream.write(jsonDump.c_str(), jsonDump.length());

		jsonOutputFileStream.close();
		*/

		//|||||||||||||||||||||||||||||||||||||||| D3DMESH EXPORT ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| D3DMESH EXPORT ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| D3DMESH EXPORT ||||||||||||||||||||||||||||||||||||||||
		//This is a D3DMESH export test, here we just simply take the D3DMESH data that we just parsed...
		//Then we use that data, recalculate header lengths/sizes/etc. and then write a new d3dmesh file.
		//If all goes well the D3DMESH file that we exported should be the EXACT same sa the D3DMESH file we just parsed.
		//At the moment this does do that sucessfully, however the D3DMESH data (i.e. index/vertex buffers) are not serialized yet as that will take a bit more work...
		//So right now it's just the meta header + d3dmesh header (no d3dmesh data)

		//std::ofstream d3dmeshOutputFileStream;
		//std::string d3dmeshExportPath = "OutputD3DMESH/" + currentD3DMESH_FileName;
		//d3dmeshOutputFileStream.open(d3dmeshExportPath, std::ios::binary);
		//d3dmeshFile.BinarySerialize(&d3dmeshOutputFileStream);
		//d3dmeshOutputFileStream.close();
	}

	return 0;
}
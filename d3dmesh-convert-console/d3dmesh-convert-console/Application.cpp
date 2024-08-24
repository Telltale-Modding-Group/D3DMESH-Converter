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
		std::cout << "READING... " << currentD3DMESH_FilePath << " [" << currentD3DMESH_FileSize << " BYTES]" << std::endl;

		//create and open an input file stream
		std::ifstream currentD3DMESH_inputFileStream;
		currentD3DMESH_inputFileStream.open(currentD3DMESH_FilePath, std::fstream::in | std::fstream::binary);

		TelltaleD3DMeshFileV55 d3dmeshFile = TelltaleD3DMeshFileV55(&currentD3DMESH_inputFileStream);

		currentD3DMESH_inputFileStream.close();

		//|||||||||||||||||||||||||||||||||||||||| TXT OUTPUT ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| TXT OUTPUT ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| TXT OUTPUT ||||||||||||||||||||||||||||||||||||||||
		//This outputs all of the contents of the D3DMESH file into a generic text file (no json used)

		//WriteD3DMeshToText(currentD3DMESH_FileName, d3dmeshFile);

		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V1 ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V1 ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V1 ||||||||||||||||||||||||||||||||||||||||
		//First attempt at doing a conversion of a d3dmesh to a standard model format (THIS DOES WORK... BUT THERE ARE PROBLEMS)
		//NOTE: This simply shoves the entire mesh into an assimp mesh, ignoring all LODs. 
		//This atleast works for getting a useable mesh export, however there are no materials/lods/submeshes/etc... it's a basic single mesh

		//NewMesh extractedMesh = {};
		//extractedMesh.triangleIndicies = d3dmeshFile.d3dmeshData.indexBuffer0;
		//extractedMesh.vertexPositions = d3dmeshFile.d3dmeshData.vertexPositions;
		//extractedMesh.vertexNormals0 = d3dmeshFile.d3dmeshData.vertexNormals0;
		//ExportAssimpMesh(extractedMesh, currentD3DMESH_FileName);

		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V2 ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V2 ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V2 ||||||||||||||||||||||||||||||||||||||||

		/*
		for (int i = 0; i < d3dmeshFile.d3dmeshHeader.mLODs.size(); i++)
		{
			T3MeshLOD* mLOD = &d3dmeshFile.d3dmeshHeader.mLODs[i];

			for (int j = 0; j < mLOD->mBatches0_ArrayLength; j++)
			{
				T3MeshBatch mBatch = mLOD->mBatches0[j];
				NewMesh extractedMesh{};

				//|||||||||||||||||||||||||||||||||||||||| GET TRIANGLE SET ||||||||||||||||||||||||||||||||||||||||
				//|||||||||||||||||||||||||||||||||||||||| GET TRIANGLE SET ||||||||||||||||||||||||||||||||||||||||
				//|||||||||||||||||||||||||||||||||||||||| GET TRIANGLE SET ||||||||||||||||||||||||||||||||||||||||

				for (int x = 0; x < mBatch.mNumIndices; x++)
				{
					int selectedTriangleIndex = d3dmeshFile.d3dmeshData.indexBuffer0[x + mBatch.mStartIndex] + mBatch.mBaseIndex;
					extractedMesh.triangleIndicies.push_back(selectedTriangleIndex);
				}

				//|||||||||||||||||||||||||||||||||||||||| GET VERTEX SET ||||||||||||||||||||||||||||||||||||||||
				//|||||||||||||||||||||||||||||||||||||||| GET VERTEX SET ||||||||||||||||||||||||||||||||||||||||
				//|||||||||||||||||||||||||||||||||||||||| GET VERTEX SET ||||||||||||||||||||||||||||||||||||||||

				//Does work, but the problem with this is that we literally slap all of the vertex data of the model onto here rather than pulling what we need.
				extractedMesh.vertexPositions = d3dmeshFile.d3dmeshData.vertexPositions;
				extractedMesh.vertexNormals0 = d3dmeshFile.d3dmeshData.vertexNormals0;

				//for (int x = mLOD->mVertexStart + mBatch.mMinVertIndex; x < mLOD->mVertexStart + mBatch.mMaxVertIndex; x++) //DOES NOT WORK
				//for (int x = mLOD->mVertexStart + mBatch.mMinVertIndex; x < mBatch.mNumPrimitives; x++) //DOES NOT WORK
				//{
					//extractedMesh.vertexPositions.push_back(d3dmeshFile.d3dmeshData.vertexPositions[x]);
					//extractedMesh.vertexNormals0.push_back(d3dmeshFile.d3dmeshData.vertexNormals0[x]);
				//}

				//|||||||||||||||||||||||||||||||||||||||| ASSIMP EXPORT TEST ||||||||||||||||||||||||||||||||||||||||
				//|||||||||||||||||||||||||||||||||||||||| ASSIMP EXPORT TEST ||||||||||||||||||||||||||||||||||||||||
				//|||||||||||||||||||||||||||||||||||||||| ASSIMP EXPORT TEST ||||||||||||||||||||||||||||||||||||||||

				std::string newPath = currentD3DMESH_FileName + "_LOD_" + std::to_string(i) + "_SUBMESH_" + std::to_string(j);
				ExportAssimpMesh(extractedMesh, newPath);
			}
		}
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
		//At the moment this does do that sucessfully, however the D3DMESH data (specifically vertex buffers) are not serialized yet due to some missed buffers?
		//So right now it's just the meta header + d3dmesh header + d3dmesh index buffers (no vertex buffers yet)

		std::ofstream d3dmeshOutputFileStream;
		std::string d3dmeshExportPath = "OutputD3DMESH/" + currentD3DMESH_FileName;
		d3dmeshOutputFileStream.open(d3dmeshExportPath, std::ios::binary);
		d3dmeshFile.BinarySerialize(&d3dmeshOutputFileStream);
		d3dmeshOutputFileStream.close();
	}

	return 0;
}
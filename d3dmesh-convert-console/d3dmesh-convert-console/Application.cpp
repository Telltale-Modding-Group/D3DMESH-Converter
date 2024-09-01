	//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||

//#define FULL_CONSOLE_OUTPUT
//#define READ_D3DMESH_EXPORT_ASSIMP
//#define READ_D3DMESH_EXPORT_JSON
//#define READ_D3DMESH_EXPORT_D3DMESH
#define READ_JSON_EXPORT_D3DMESH

//Standard C++ Library
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>

//Custom
#include "TelltaleD3DMeshFileV55.h"
#include "NewMesh.h"
#include "NewMeshToAssimp.h"
#include "D3DMeshDataToAssimp.h"

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

	std::vector<std::string> d3dmeshFilePaths; //array of the d3dmesh file paths relative to the application
	std::vector<std::string> d3dmeshFileNames; //array of the d3dmesh file names (with extension) relative to the application
	std::vector<unsigned long> d3dmeshFileSizes; //array of the d3dmesh file byte sizes (only used for comparison later to check if we've reached the end of the file)

	//iterate through every file that we find in the Data/ folder relative to the application
	for (const auto& entry : std::filesystem::recursive_directory_iterator("Data"))
	{
		//extract path information
		std::string assetFilePath = entry.path().string();
		std::string assetFileName = entry.path().filename().string();

		//if the extension matches what we are looking for, then add them!
		if (entry.path().extension() == ".d3dmesh")
		{
			d3dmeshFilePaths.push_back(assetFilePath);
			d3dmeshFileNames.push_back(assetFileName);
			d3dmeshFileSizes.push_back(entry.file_size());
		}
	}

	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_D3DMESH_EXPORT_D3DMESH)
	for (int d3dmeshFilePathIndex = 0; d3dmeshFilePathIndex < d3dmeshFilePaths.size(); d3dmeshFilePathIndex++)
	{
		std::string currentD3DMESH_FilePath = d3dmeshFilePaths[d3dmeshFilePathIndex];
		std::string currentD3DMESH_FileName = d3dmeshFileNames[d3dmeshFilePathIndex];
		unsigned long currentD3DMESH_FileSize = d3dmeshFileSizes[d3dmeshFilePathIndex];

		std::cout << "READING... " << currentD3DMESH_FilePath << " [" << currentD3DMESH_FileSize << " BYTES]" << std::endl;

		std::ifstream currentD3DMESH_inputFileStream;
		currentD3DMESH_inputFileStream.open(currentD3DMESH_FilePath, std::fstream::in | std::fstream::binary);

		TelltaleD3DMeshFileV55 d3dmeshFile = TelltaleD3DMeshFileV55(&currentD3DMESH_inputFileStream);

		currentD3DMESH_inputFileStream.close();

		//This is a D3DMESH export test, here we just simply take the D3DMESH data that we just parsed...
		//Then we use that data, recalculate header lengths/sizes/etc. and then write a new d3dmesh file.
		//If all goes well the D3DMESH file that we exported should be the EXACT same sa the D3DMESH file we just parsed.
		//At the moment this does do that sucessfully, however the D3DMESH data (specifically vertex buffers) are not serialized yet due to some missed buffers?
		//So right now it's just the meta header + d3dmesh header + d3dmesh index buffers (no vertex buffers yet)

		//============================= (EXPERIMENTS) INDEX BUFFER REMOVALS =============================
		//remove index buffers (will crash the game)
		//d3dmeshFile.d3dmeshHeader.mIndexBuffers.erase(d3dmeshFile.d3dmeshHeader.mIndexBuffers.begin(), d3dmeshFile.d3dmeshHeader.mIndexBuffers.end());
		//d3dmeshFile.d3dmeshData.indexBuffers.erase(d3dmeshFile.d3dmeshData.indexBuffers.begin(), d3dmeshFile.d3dmeshData.indexBuffers.end());

		//remove second index buffer (no visible changes... what on earth is this secondary index buffer for?)
		//d3dmeshFile.d3dmeshHeader.mIndexBuffers.erase(d3dmeshFile.d3dmeshHeader.mIndexBuffers.begin() + 1, d3dmeshFile.d3dmeshHeader.mIndexBuffers.end());
		//d3dmeshFile.d3dmeshData.indexBuffers.erase(d3dmeshFile.d3dmeshData.indexBuffers.begin() + 1, d3dmeshFile.d3dmeshData.indexBuffers.end());

		//============================= (EXPERIMENTS) VERTEX FORMAT CHANGE =============================
		//NOTE: These are experiments in changing the vertex formats to a different channel to see how the engine behaves.
		//We are finding out that it seems like changing the buffer formats will break the model and some of it's properties and how its rendered.
		//There is a good chance that the materials/shaders used are likely expecting a specific format and are doing unpacking on their end.
		//d3dmeshFile.d3dmeshHeader.mPositionOffset = Vector3(0.0f, 0.0f, 0.0f);
		//d3dmeshFile.d3dmeshHeader.mPositionScale = Vector3(1.0f, 1.0f, 1.0f);
		//d3dmeshFile.d3dmeshHeader.mPositionWScale = Vector3(0.0f, 0.0f, 0.0f);

		//force set vertex buffers to be a specific format
		//for (int i = 0; i < d3dmeshFile.d3dmeshHeader.GFXPlatformAttributeParamsArray.size(); i++)
		//{
			//if(d3dmeshFile.d3dmeshHeader.GFXPlatformAttributeParamsArray[i].mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Position)
				//d3dmeshFile.d3dmeshHeader.GFXPlatformAttributeParamsArray[i].mFormat = GFXPlatformFormat::eGFXPlatformFormat_F32x3;

			//if(d3dmeshFile.d3dmeshHeader.GFXPlatformAttributeParamsArray[i].mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_TexCoord)
				//d3dmeshFile.d3dmeshHeader.GFXPlatformAttributeParamsArray[i].mFormat = GFXPlatformFormat::eGFXPlatformFormat_F32x2;
		//}

		//============================= (EXPERIMENTS) VERTEX BUFFER VALUE MODIFICATIONS =============================
		/*
		//Setting values of all UVs on model to a specific value.
		for (int i = 0; i < d3dmeshFile.d3dmeshData.vertexUVs.size(); i++)
		{
			for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexUVs[i].size(); j++)
			{
				d3dmeshFile.d3dmeshData.vertexUVs[i][j] = Vector4(0.5f, 0.5f, 0, 0);
			}
		}
		*/
		/*
		//Setting values of all normals on model to a specific value.
		for (int i = 0; i < d3dmeshFile.d3dmeshData.vertexNormals.size(); i++)
		{
			for (int j = 0; j < d3dmeshFile.d3dmeshData.vertexNormals[i].size(); j++)
			{
				d3dmeshFile.d3dmeshData.vertexNormals[i][j] = Vector4(0, 1, 0, 0);
			}
		}
		*/

		d3dmeshFile.UpdateValues();

		std::ofstream d3dmeshOutputFileStream;
		std::string d3dmeshExportPath = "OutputD3DMESH/" + currentD3DMESH_FileName;
		d3dmeshOutputFileStream.open(d3dmeshExportPath, std::ios::binary);
		d3dmeshFile.BinarySerialize(&d3dmeshOutputFileStream);
		d3dmeshOutputFileStream.close();
	}
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT JSON ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT JSON ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT JSON ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_D3DMESH_EXPORT_JSON)
	for (int d3dmeshFilePathIndex = 0; d3dmeshFilePathIndex < d3dmeshFilePaths.size(); d3dmeshFilePathIndex++)
	{
		std::string currentD3DMESH_FilePath = d3dmeshFilePaths[d3dmeshFilePathIndex];
		std::string currentD3DMESH_FileName = d3dmeshFileNames[d3dmeshFilePathIndex];
		unsigned long currentD3DMESH_FileSize = d3dmeshFileSizes[d3dmeshFilePathIndex];

		std::cout << "READING... " << currentD3DMESH_FilePath << " [" << currentD3DMESH_FileSize << " BYTES]" << std::endl;

		std::ifstream currentD3DMESH_inputFileStream;
		currentD3DMESH_inputFileStream.open(currentD3DMESH_FilePath, std::fstream::in | std::fstream::binary);

		TelltaleD3DMeshFileV55 d3dmeshFile = TelltaleD3DMeshFileV55(&currentD3DMESH_inputFileStream);

		currentD3DMESH_inputFileStream.close();

		std::ofstream jsonOutputFileStream;
		std::string jsonExportPath = "OutputJSON/" + currentD3DMESH_FileName + ".json";
		jsonOutputFileStream.open(jsonExportPath);

		nlohmann::ordered_json json;
		json = d3dmeshFile;

		std::string jsonDump = json.dump(4); //pretty print with indents
		jsonOutputFileStream.write(jsonDump.c_str(), jsonDump.length());

		jsonOutputFileStream.close();
	}
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT ASSIMP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT ASSIMP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT ASSIMP ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_D3DMESH_EXPORT_ASSIMP)
	for (int d3dmeshFilePathIndex = 0; d3dmeshFilePathIndex < d3dmeshFilePaths.size(); d3dmeshFilePathIndex++)
	{
		std::string currentD3DMESH_FilePath = d3dmeshFilePaths[d3dmeshFilePathIndex];
		std::string currentD3DMESH_FileName = d3dmeshFileNames[d3dmeshFilePathIndex];
		unsigned long currentD3DMESH_FileSize = d3dmeshFileSizes[d3dmeshFilePathIndex];

		std::cout << "READING... " << currentD3DMESH_FilePath << " [" << currentD3DMESH_FileSize << " BYTES]" << std::endl;

		std::ifstream currentD3DMESH_inputFileStream;
		currentD3DMESH_inputFileStream.open(currentD3DMESH_FilePath, std::fstream::in | std::fstream::binary);

		TelltaleD3DMeshFileV55 d3dmeshFile = TelltaleD3DMeshFileV55(&currentD3DMESH_inputFileStream);

		currentD3DMESH_inputFileStream.close();

		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V1 ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V1 ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V1 ||||||||||||||||||||||||||||||||||||||||
		//First attempt at doing a conversion of a d3dmesh to a standard model format (THIS DOES WORK... BUT THERE ARE PROBLEMS)
		//NOTE: This simply shoves the entire mesh into an assimp mesh, ignoring all LODs. 
		//This atleast works for getting a useable mesh export, however there are no materials/lods/submeshes/etc... it's a basic single mesh
		/*
		NewMesh extractedMesh = {};
		extractedMesh.triangleIndicies = d3dmeshFile.d3dmeshData.indexBuffers[0];

		for (int x = 0; x < d3dmeshFile.d3dmeshData.vertexPositions[0].size(); x++)
			extractedMesh.vertexPositions.push_back(Vector3(d3dmeshFile.d3dmeshData.vertexPositions[0][x].x, d3dmeshFile.d3dmeshData.vertexPositions[0][x].y, d3dmeshFile.d3dmeshData.vertexPositions[0][x].z));

		for (int x = 0; x < d3dmeshFile.d3dmeshData.vertexNormals[0].size(); x++)
			extractedMesh.vertexNormals0.push_back(Vector3(d3dmeshFile.d3dmeshData.vertexNormals[0][x].x, d3dmeshFile.d3dmeshData.vertexNormals[0][x].y, d3dmeshFile.d3dmeshData.vertexNormals[0][x].z));

		ExportAssimpMesh(extractedMesh, currentD3DMESH_FileName);
		*/
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
				//NOTE TO SELF: This works perfectly, works with LODs and pulls the submeshes correctly

				for (int x = 0; x < mBatch.mNumIndices; x++)
				{
					int selectedTriangleIndex = d3dmeshFile.d3dmeshData.indexBuffers[0][x + mBatch.mStartIndex] + mBatch.mBaseIndex;
					extractedMesh.triangleIndicies.push_back(selectedTriangleIndex);
				}

				//|||||||||||||||||||||||||||||||||||||||| GET VERTEX SET ||||||||||||||||||||||||||||||||||||||||
				//|||||||||||||||||||||||||||||||||||||||| GET VERTEX SET ||||||||||||||||||||||||||||||||||||||||
				//|||||||||||||||||||||||||||||||||||||||| GET VERTEX SET ||||||||||||||||||||||||||||||||||||||||
				//NOTE TO SELF: This needs additional work/attention...
				//While we can just slap all of the vertex buffer data into the mesh and have assimp handle it...
				//Its better and more proper to actually get the correct set of verticies that each coresponding LOD/Submesh has and will use.
				//This will also come in handy later when we need to convert a new mesh to d3dmesh.

				//Does work, but the problem with this is that we literally slap all of the vertex data of the model onto here rather than pulling what we need.
				for(int x = 0; x < d3dmeshFile.d3dmeshData.vertexPositions[0].size(); x++)
					extractedMesh.vertexPositions.push_back(Vector3(d3dmeshFile.d3dmeshData.vertexPositions[0][x].x, d3dmeshFile.d3dmeshData.vertexPositions[0][x].y, d3dmeshFile.d3dmeshData.vertexPositions[0][x].z));

				for (int x = 0; x < d3dmeshFile.d3dmeshData.vertexNormals[0].size(); x++)
					extractedMesh.vertexNormals0.push_back(Vector3(d3dmeshFile.d3dmeshData.vertexNormals[0][x].x, d3dmeshFile.d3dmeshData.vertexNormals[0][x].y, d3dmeshFile.d3dmeshData.vertexNormals[0][x].z));

				//This needs work...
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
		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V3 ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V3 ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V3 ||||||||||||||||||||||||||||||||||||||||

		//ExportFullAssimpMesh(&d3dmeshFile, currentD3DMESH_FileName);
	}
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ JSON / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ JSON / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ JSON / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_JSON_EXPORT_D3DMESH)
	for (const auto& entry : std::filesystem::recursive_directory_iterator("InputJSON"))
	{
		std::string assetFilePath = entry.path().string();
		std::string assetFileName = entry.path().filename().string();

		if (entry.path().extension() == ".json")
		{
			std::ifstream inputFileStream;
			inputFileStream.open(assetFilePath, std::fstream::in | std::fstream::binary);

			nlohmann::ordered_json readJson;
			inputFileStream >> readJson;

			TelltaleD3DMeshFileV55 parsedD3DMesh = readJson.template get<TelltaleD3DMeshFileV55>();

			inputFileStream.close();

			std::ofstream d3dmeshOutputFileStream;
			std::string d3dmeshExportPath = "OutputJSON_TO_D3DMESH/" + assetFileName + ".d3dmesh";
			d3dmeshOutputFileStream.open(d3dmeshExportPath, std::ios::binary);
			parsedD3DMesh.BinarySerialize(&d3dmeshOutputFileStream);
			d3dmeshOutputFileStream.close();

			std::cout << "EXPORTED... " << d3dmeshExportPath << std::endl;
		}
	}
#endif

	return 0;
}
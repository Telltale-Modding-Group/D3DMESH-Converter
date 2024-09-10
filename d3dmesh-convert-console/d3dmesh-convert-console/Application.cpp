//||||||||||||||||||||||||||||| PREPROCESSOR MACROS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| PREPROCESSOR MACROS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| PREPROCESSOR MACROS |||||||||||||||||||||||||||||

//assimp export options
#define ASSIMP_EXPORT_SHADOW

//d3dmesh conversion modes
//#define READ_D3DMESH
//#define READ_D3DMESH_AND_SKL
//#define READ_D3DMESH_EXPORT_ASSIMP
//#define READ_D3DMESH_EXPORT_JSON
//#define READ_D3DMESH_EXPORT_D3DMESH
//#define READ_D3DMESH_EXPORT_JSON_AND_ASSIMP
//#define READ_D3DMESH_JSON_EXPORT_D3DMESH
#define READ_D3DMESH_JSON_AND_ASSIMP_EXPORT_D3DMESH

//skl conversion modes
//#define READ_SKL
//#define READ_SKL_EXPORT_JSON
//#define READ_SKL_EXPORT_SKL
//#define READ_JSON_EXPORT_SKL

//file extensions
#define D3DMESH_EXTENSION ".d3dmesh"
#define SKL_EXTENSION ".skl"
#define JSON_EXTENSION ".json"
#define ASSIMP_EXTENSION ".fbx"

//input directories
//#define INPUT_DIRECTORY_D3DMESH "DebugWorkingDirectory/InputD3DMESH"
#define INPUT_DIRECTORY_D3DMESH "DebugWorkingDirectory/InputD3DMESH_MODIFIED"
#define INPUT_DIRECTORY_D3DMESH_AND_SKL "DebugWorkingDirectory/InputD3DMESH_AND_SKL"
#define INPUT_DIRECTORY_D3DMESH_JSON "DebugWorkingDirectory/InputD3DMESH_JSON"
#define INPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP "DebugWorkingDirectory/InputD3DMESH_JSON_AND_ASSIMP"
#define INPUT_DIRECTORY_SKL "DebugWorkingDirectory/InputSKL"
#define INPUT_DIRECTORY_SKL_JSON "DebugWorkingDirectory/InputSKL_JSON"

//output directories
#define OUTPUT_DIRECTORY_ASSIMP_TO_D3DMESH "DebugWorkingDirectory/OutputASSIMP_TO_D3DMESH/"
#define OUTPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP "DebugWorkingDirectory/OutputD3DMESH_JSON_AND_ASSIMP/"
#define OUTPUT_DIRECTORY_D3DMESH_TO_ASSIMP "DebugWorkingDirectory/OutputD3DMESH_TO_ASSIMP/"
#define OUTPUT_DIRECTORY_D3DMESH_TO_D3DMESH "DebugWorkingDirectory/OutputD3DMESH_TO_D3DMESH/"
#define OUTPUT_DIRECTORY_D3DMESH_TO_JSON "DebugWorkingDirectory/OutputD3DMESH_TO_JSON/"
#define OUTPUT_DIRECTORY_JSON_TO_D3DMESH "DebugWorkingDirectory/OutputJSON_TO_D3DMESH/"
#define OUTPUT_DIRECTORY_JSON_TO_SKL "DebugWorkingDirectory/OutputJSON_TO_SKL/"
#define OUTPUT_DIRECTORY_SKL_TO_JSON "DebugWorkingDirectory/OutputSKL_TO_JSON/"
#define OUTPUT_DIRECTORY_SKL_TO_SKL "DebugWorkingDirectory/OutputSKL_TO_SKL/"

//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||

//Standard C++ Library
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>

//Custom
#include "CustomTypes/FileEntry.h"
#include "Telltale/DataTypes/TelltaleD3DMeshFileV55.h"
#include "Telltale/DataTypes/TelltaleSkeletonFile.h"

#include "D3DMeshDataToAssimpV1.h"
#include "D3DMeshDataToAssimpV2.h"
#include "D3DMeshDataToAssimpV3.h"

#include "AssimpToD3DMeshDataV1.h"

//|||||||||||||||||||||||||||||||||||||||| MAIN ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| MAIN ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| MAIN ||||||||||||||||||||||||||||||||||||||||

void SetupDevelopmentDirectories() 
{
	if (std::filesystem::is_directory(INPUT_DIRECTORY_D3DMESH) == false)
	{
		std::cout << "INPUT_DIRECTORY_D3DMESH: " << INPUT_DIRECTORY_D3DMESH << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(INPUT_DIRECTORY_D3DMESH);
	}

	if (std::filesystem::is_directory(INPUT_DIRECTORY_D3DMESH_AND_SKL) == false)
	{
		std::cout << "INPUT_DIRECTORY_D3DMESH_AND_SKL: " << INPUT_DIRECTORY_D3DMESH_AND_SKL << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(INPUT_DIRECTORY_D3DMESH_AND_SKL);
	}

	if (std::filesystem::is_directory(INPUT_DIRECTORY_D3DMESH_JSON) == false)
	{
		std::cout << "INPUT_DIRECTORY_D3DMESH_JSON: " << INPUT_DIRECTORY_D3DMESH_JSON << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(INPUT_DIRECTORY_D3DMESH_JSON);
	}

	if (std::filesystem::is_directory(INPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP) == false)
	{
		std::cout << "INPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP: " << INPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(INPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP);
	}

	if (std::filesystem::is_directory(INPUT_DIRECTORY_SKL) == false)
	{
		std::cout << "INPUT_DIRECTORY_SKL: " << INPUT_DIRECTORY_SKL << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(INPUT_DIRECTORY_SKL);
	}

	if (std::filesystem::is_directory(INPUT_DIRECTORY_SKL_JSON) == false)
	{
		std::cout << "INPUT_DIRECTORY_SKL_JSON: " << INPUT_DIRECTORY_SKL_JSON << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(INPUT_DIRECTORY_SKL_JSON);
	}

	if (std::filesystem::is_directory(OUTPUT_DIRECTORY_ASSIMP_TO_D3DMESH) == false)
	{
		std::cout << "OUTPUT_DIRECTORY_ASSIMP_TO_D3DMESH: " << OUTPUT_DIRECTORY_ASSIMP_TO_D3DMESH << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(OUTPUT_DIRECTORY_ASSIMP_TO_D3DMESH);
	}

	if (std::filesystem::is_directory(OUTPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP) == false)
	{
		std::cout << "OUTPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP: " << OUTPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(OUTPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP);
	}

	if (std::filesystem::is_directory(OUTPUT_DIRECTORY_D3DMESH_TO_ASSIMP) == false)
	{
		std::cout << "OUTPUT_DIRECTORY_D3DMESH_TO_ASSIMP: " << OUTPUT_DIRECTORY_D3DMESH_TO_ASSIMP << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(OUTPUT_DIRECTORY_D3DMESH_TO_ASSIMP);
	}

	if (std::filesystem::is_directory(OUTPUT_DIRECTORY_D3DMESH_TO_D3DMESH) == false)
	{
		std::cout << "OUTPUT_DIRECTORY_D3DMESH_TO_D3DMESH: " << OUTPUT_DIRECTORY_D3DMESH_TO_D3DMESH << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(OUTPUT_DIRECTORY_D3DMESH_TO_D3DMESH);
	}

	if (std::filesystem::is_directory(OUTPUT_DIRECTORY_D3DMESH_TO_JSON) == false)
	{
		std::cout << "OUTPUT_DIRECTORY_D3DMESH_TO_JSON: " << OUTPUT_DIRECTORY_D3DMESH_TO_JSON << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(OUTPUT_DIRECTORY_D3DMESH_TO_JSON);
	}

	if (std::filesystem::is_directory(OUTPUT_DIRECTORY_JSON_TO_D3DMESH) == false)
	{
		std::cout << "OUTPUT_DIRECTORY_JSON_TO_D3DMESH: " << OUTPUT_DIRECTORY_JSON_TO_D3DMESH << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(OUTPUT_DIRECTORY_JSON_TO_D3DMESH);
	}

	if (std::filesystem::is_directory(OUTPUT_DIRECTORY_JSON_TO_SKL) == false)
	{
		std::cout << "OUTPUT_DIRECTORY_JSON_TO_SKL: " << OUTPUT_DIRECTORY_JSON_TO_SKL << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(OUTPUT_DIRECTORY_JSON_TO_SKL);
	}

	if (std::filesystem::is_directory(OUTPUT_DIRECTORY_SKL_TO_JSON) == false)
	{
		std::cout << "OUTPUT_DIRECTORY_SKL_TO_JSON: " << OUTPUT_DIRECTORY_SKL_TO_JSON << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(OUTPUT_DIRECTORY_SKL_TO_JSON);
	}

	if (std::filesystem::is_directory(OUTPUT_DIRECTORY_SKL_TO_SKL) == false)
	{
		std::cout << "OUTPUT_DIRECTORY_SKL_TO_SKL: " << OUTPUT_DIRECTORY_SKL_TO_SKL << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(OUTPUT_DIRECTORY_SKL_TO_SKL);
	}
}

int main()
{
	SetupDevelopmentDirectories();

	//|||||||||||||||||||||||||||||||||||||||| READ SKL ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ SKL ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ SKL ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_SKL)
	std::cout << "Starting... READ_SKL " << std::endl;

	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator(INPUT_DIRECTORY_SKL))
	{
		FileEntry fileEntry = FileEntry(directoryEntry);

		if (fileEntry.fileExtension == SKL_EXTENSION)
		{
			//=================== READ SKL ===================
			std::cout << "READING... " << fileEntry.filePath << " [" << fileEntry.fileSize << " BYTES]" << std::endl;

			std::ifstream inputFileStream;
			inputFileStream.open(fileEntry.filePath, std::fstream::in | std::fstream::binary);

			TelltaleSkeletonFile sklFile = TelltaleSkeletonFile(&inputFileStream);

			inputFileStream.close();
		}
	}

	std::cout << "Finished... READ_SKL " << std::endl;
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ SKL / EXPORT JSON ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ SKL / EXPORT JSON ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ SKL / EXPORT JSON ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_SKL_EXPORT_JSON)
	std::cout << "Starting... READ_SKL_EXPORT_JSON " << std::endl;

	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator(INPUT_DIRECTORY_SKL))
	{
		FileEntry fileEntry = FileEntry(directoryEntry);

		if (fileEntry.fileExtension == SKL_EXTENSION)
		{
			//=================== READ SKL ===================
			std::cout << "READING... " << fileEntry.filePath << " [" << fileEntry.fileSize << " BYTES]" << std::endl;

			std::ifstream inputFileStream;
			inputFileStream.open(fileEntry.filePath, std::fstream::in | std::fstream::binary);

			TelltaleSkeletonFile sklFile = TelltaleSkeletonFile(&inputFileStream);

			inputFileStream.close();

			//=================== EXPORT SKL TO JSON ===================
			std::ofstream outputFileStream;
			std::string jsonExportPath = OUTPUT_DIRECTORY_SKL_TO_JSON + fileEntry.fileNameWithoutExtension + JSON_EXTENSION;
			outputFileStream.open(jsonExportPath);

			nlohmann::ordered_json json;
			json = sklFile;

			std::string jsonDump = json.dump(4); //pretty print with indents
			outputFileStream.write(jsonDump.c_str(), jsonDump.length());
			outputFileStream.close();
		}
	}

	std::cout << "Finished... READ_SKL_EXPORT_JSON " << std::endl;
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ SKL / EXPORT SKL ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ SKL / EXPORT SKL ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ SKL / EXPORT SKL ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_SKL_EXPORT_SKL)
	std::cout << "Starting... READ_SKL_EXPORT_SKL " << std::endl;

	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator(INPUT_DIRECTORY_SKL))
	{
		FileEntry fileEntry = FileEntry(directoryEntry);

		if (fileEntry.fileExtension == SKL_EXTENSION)
		{
			//=================== READ SKL ===================
			std::cout << "READING... " << fileEntry.filePath << " [" << fileEntry.fileSize << " BYTES]" << std::endl;

			std::ifstream inputFileStream;
			inputFileStream.open(fileEntry.filePath, std::fstream::in | std::fstream::binary);

			TelltaleSkeletonFile sklFile = TelltaleSkeletonFile(&inputFileStream);

			inputFileStream.close();

			//=================== EXPORT SKL ===================
			sklFile.UpdateValues();

			std::ofstream outputFileStream;
			std::string sklExportPath = OUTPUT_DIRECTORY_SKL_TO_SKL + fileEntry.fileNameWithExtension;
			outputFileStream.open(sklExportPath, std::ios::binary);
			sklFile.BinarySerialize(&outputFileStream);
			outputFileStream.close();
		}
	}

	std::cout << "Finished... READ_SKL_EXPORT_SKL " << std::endl;
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ JSON / EXPORT SKL ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ JSON / EXPORT SKL ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ JSON / EXPORT SKL ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_JSON_EXPORT_SKL)
	std::cout << "Starting... READ_JSON_EXPORT_SKL " << std::endl;

	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator(INPUT_DIRECTORY_SKL_JSON))
	{
		FileEntry fileEntry = FileEntry(directoryEntry);

		if (fileEntry.fileExtension == JSON_EXTENSION)
		{
			//=================== READ SKL JSON ===================
			std::cout << "READING... " << fileEntry.filePath << " [" << fileEntry.fileSize << " BYTES]" << std::endl;

			std::ifstream inputFileStream;
			inputFileStream.open(fileEntry.filePath, std::fstream::in | std::fstream::binary);

			nlohmann::ordered_json readJson;
			inputFileStream >> readJson;

			TelltaleSkeletonFile sklFile = readJson.template get<TelltaleSkeletonFile>();

			inputFileStream.close();

			//=================== EXPORT SKL ===================
			std::ofstream outputFileStream;
			std::string sklExportPath = OUTPUT_DIRECTORY_JSON_TO_SKL + fileEntry.fileNameWithoutExtension + SKL_EXTENSION;
			outputFileStream.open(sklExportPath, std::ios::binary);
			sklFile.BinarySerialize(&outputFileStream);
			outputFileStream.close();

			std::cout << "EXPORTED... " << sklExportPath << std::endl;
		}
	}

	std::cout << "Finished... READ_JSON_EXPORT_SKL " << std::endl;
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_D3DMESH)
	std::cout << "Starting... READ_D3DMESH " << std::endl;

	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator(INPUT_DIRECTORY_D3DMESH))
	{
		FileEntry fileEntry = FileEntry(directoryEntry);

		if (fileEntry.fileExtension == D3DMESH_EXTENSION)
		{
			//=================== READ D3DMESH ===================
			std::cout << "READING... " << fileEntry.filePath << " [" << fileEntry.fileSize << " BYTES]" << std::endl;

			std::ifstream inputFileStream;
			inputFileStream.open(fileEntry.filePath, std::fstream::in | std::fstream::binary);

			TelltaleD3DMeshFileV55 parsedD3DMesh = TelltaleD3DMeshFileV55(&inputFileStream);

			inputFileStream.close();

			if (parsedD3DMesh.HasBones())
				std::cout << "[D3DMESH INFO] " << fileEntry.filePath << " has bones!" << std::endl;
		}
	}

	std::cout << "Finished... READ_D3DMESH " << std::endl;
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_D3DMESH_EXPORT_D3DMESH)
	std::cout << "Starting... READ_D3DMESH_EXPORT_D3DMESH " << std::endl;

	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator(INPUT_DIRECTORY_D3DMESH))
	{
		FileEntry fileEntry = FileEntry(directoryEntry);

		if (fileEntry.fileExtension == D3DMESH_EXTENSION)
		{
			//=================== READ D3DMESH ===================
			std::cout << "READING... " << fileEntry.filePath << " [" << fileEntry.fileSize << " BYTES]" << std::endl;

			std::ifstream inputFileStream;
			inputFileStream.open(fileEntry.filePath, std::fstream::in | std::fstream::binary);

			TelltaleD3DMeshFileV55 parsedD3DMesh = TelltaleD3DMeshFileV55(&inputFileStream);

			inputFileStream.close();

			if (parsedD3DMesh.HasBones())
				std::cout << "[D3DMESH INFO] " << fileEntry.filePath << " has bones!" << std::endl;

			//=================== D3DMESH DATA TESTS ===================
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

			//=================== EXPORT D3DMESH ===================
			parsedD3DMesh.UpdateValues();

			std::ofstream outputFileStream;
			std::string d3dmeshExportPath = OUTPUT_DIRECTORY_D3DMESH_TO_D3DMESH + fileEntry.fileNameWithExtension;
			outputFileStream.open(d3dmeshExportPath, std::ios::binary);
			parsedD3DMesh.BinarySerialize(&outputFileStream);
			outputFileStream.close();

			std::cout << "EXPORTED... " << d3dmeshExportPath << std::endl;
		}
	}

	std::cout << "Finished... READ_D3DMESH_EXPORT_D3DMESH " << std::endl;
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT JSON ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT JSON ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT JSON ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_D3DMESH_EXPORT_JSON)
	std::cout << "Starting... READ_D3DMESH_EXPORT_JSON " << std::endl;
	
	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator(INPUT_DIRECTORY_D3DMESH))
	{
		FileEntry fileEntry = FileEntry(directoryEntry);

		if (fileEntry.fileExtension == D3DMESH_EXTENSION)
		{
			//=================== READ D3DMESH ===================
			std::cout << "READING... " << fileEntry.filePath << " [" << fileEntry.fileSize << " BYTES]" << std::endl;

			std::ifstream inputFileStream;
			inputFileStream.open(fileEntry.filePath, std::fstream::in | std::fstream::binary);

			TelltaleD3DMeshFileV55 parsedD3DMesh = TelltaleD3DMeshFileV55(&inputFileStream);

			inputFileStream.close();

			if (parsedD3DMesh.HasBones())
				std::cout << "[D3DMESH INFO] " << fileEntry.filePath << " has bones!" << std::endl;

			//=================== EXPORT JSON ===================
			std::ofstream outputFileStream;
			std::string jsonExportPath = OUTPUT_DIRECTORY_D3DMESH_TO_JSON + fileEntry.fileNameWithoutExtension + JSON_EXTENSION;
			outputFileStream.open(jsonExportPath);

			nlohmann::ordered_json json;
			json = parsedD3DMesh;

			std::string jsonDump = json.dump(4); //pretty print with indents
			outputFileStream.write(jsonDump.c_str(), jsonDump.length());

			outputFileStream.close();

			std::cout << "EXPORTED... " << jsonExportPath << std::endl;
		}
	}

	std::cout << "Finished... READ_D3DMESH_EXPORT_JSON " << std::endl;
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT ASSIMP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT ASSIMP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT ASSIMP ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_D3DMESH_EXPORT_ASSIMP)
	std::cout << "Starting... READ_D3DMESH_EXPORT_ASSIMP " << std::endl;
	
	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator(INPUT_DIRECTORY_D3DMESH))
	{
		FileEntry fileEntry = FileEntry(directoryEntry);

		if (fileEntry.fileExtension == D3DMESH_EXTENSION)
		{
			//=================== READ D3DMESH ===================
			std::cout << "READING... " << fileEntry.filePath << " [" << fileEntry.fileSize << " BYTES]" << std::endl;

			std::ifstream inputFileStream;
			inputFileStream.open(fileEntry.filePath, std::fstream::in | std::fstream::binary);

			TelltaleD3DMeshFileV55 parsedD3DMesh = TelltaleD3DMeshFileV55(&inputFileStream);

			inputFileStream.close();

			if (parsedD3DMesh.HasBones())
				std::cout << "[D3DMESH INFO] " << fileEntry.filePath << " has bones!" << std::endl;

			//=================== EXPORT ASSIMP ===================
			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V1 ||||||||||||||||||||||||||||||||||||||||
			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V1 ||||||||||||||||||||||||||||||||||||||||
			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V1 ||||||||||||||||||||||||||||||||||||||||
			//First attempt at doing a conversion of a d3dmesh to a standard model format (THIS DOES WORK... BUT THERE ARE PROBLEMS)
			//This simply shoves the entire mesh into an assimp mesh, ignoring all LODs. 
			//This atleast works for getting a useable mesh export, however there are no materials/lods/submeshes/etc... it's a basic single mesh
			//If the d3dmesh has multiple LOD levels then this breaks pretty much
			//ExportD3DMeshToAssimpV1(&parsedD3DMesh, fileEntry.fileNameWithoutExtension, OUTPUT_DIRECTORY_D3DMESH_TO_ASSIMP);

			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V2 ||||||||||||||||||||||||||||||||||||||||
			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V2 ||||||||||||||||||||||||||||||||||||||||
			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V2 ||||||||||||||||||||||||||||||||||||||||
			//Second attempt at doing a conversion of a d3dmesh to a standard model format.
			//This uses the mLOD's and T3MeshBatch's to pull each LOD/Submesh from the model.
			//The verticies however that are currently referenced are from the ENTIRE model. (Ideally we segment the verticies by only what we use)
			//This is alot more sucessful than the first attempt as now we can factor in LOD/Submeshes
			//The only drawback however is that the entire verticie set of the model is dumped, rather than being segmented properly.
			//ExportD3DMeshToAssimpV2(&parsedD3DMesh, fileEntry.fileNameWithoutExtension, OUTPUT_DIRECTORY_D3DMESH_TO_ASSIMP);

			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V3 ||||||||||||||||||||||||||||||||||||||||
			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V3 ||||||||||||||||||||||||||||||||||||||||
			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V3 ||||||||||||||||||||||||||||||||||||||||
			ExportD3DMeshToAssimpV3(&parsedD3DMesh, fileEntry.fileNameWithoutExtension, OUTPUT_DIRECTORY_D3DMESH_TO_ASSIMP);
		}
	}

	std::cout << "Finished... READ_D3DMESH_EXPORT_ASSIMP " << std::endl;
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT JSON AND ASSIMP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT JSON AND ASSIMP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT JSON AND ASSIMP ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_D3DMESH_EXPORT_JSON_AND_ASSIMP)
	std::cout << "Starting... READ_D3DMESH_EXPORT_JSON_AND_ASSIMP " << std::endl;
	
	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator(INPUT_DIRECTORY_D3DMESH))
	{
		FileEntry fileEntry = FileEntry(directoryEntry);

		if (fileEntry.fileExtension == D3DMESH_EXTENSION)
		{
			//=================== READ D3DMESH ===================
			std::cout << "READING... " << fileEntry.filePath << " [" << fileEntry.fileSize << " BYTES]" << std::endl;

			std::ifstream inputFileStream;
			inputFileStream.open(fileEntry.filePath, std::fstream::in | std::fstream::binary);

			TelltaleD3DMeshFileV55 parsedD3DMesh = TelltaleD3DMeshFileV55(&inputFileStream);

			inputFileStream.close();

			if (parsedD3DMesh.HasBones())
				std::cout << "[D3DMESH INFO] " << fileEntry.filePath << " has bones!" << std::endl;

			//=================== EXPORT JSON ===================
			std::ofstream outputFileStream;
			std::string jsonExportPath = OUTPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP + fileEntry.fileNameWithoutExtension + JSON_EXTENSION;
			outputFileStream.open(jsonExportPath);

			nlohmann::ordered_json json;
			json = parsedD3DMesh;

			std::string jsonDump = json.dump(4); //pretty print with indents
			outputFileStream.write(jsonDump.c_str(), jsonDump.length());

			outputFileStream.close();

			//=================== EXPORT ASSIMP ===================
			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V1 ||||||||||||||||||||||||||||||||||||||||
			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V1 ||||||||||||||||||||||||||||||||||||||||
			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V1 ||||||||||||||||||||||||||||||||||||||||
			//First attempt at doing a conversion of a d3dmesh to a standard model format (THIS DOES WORK... BUT THERE ARE PROBLEMS)
			//This simply shoves the entire mesh into an assimp mesh, ignoring all LODs. 
			//This atleast works for getting a useable mesh export, however there are no materials/lods/submeshes/etc... it's a basic single mesh
			//If the d3dmesh has multiple LOD levels then this breaks pretty much
			//ExportD3DMeshToAssimpV1(&parsedD3DMesh, fileEntry.fileNameWithoutExtension, OUTPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP);

			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V2 ||||||||||||||||||||||||||||||||||||||||
			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V2 ||||||||||||||||||||||||||||||||||||||||
			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V2 ||||||||||||||||||||||||||||||||||||||||
			//Second attempt at doing a conversion of a d3dmesh to a standard model format.
			//This uses the mLOD's and T3MeshBatch's to pull each LOD/Submesh from the model.
			//The verticies however that are currently referenced are from the ENTIRE model. (Ideally we segment the verticies by only what we use)
			//This is alot more sucessful than the first attempt as now we can factor in LOD/Submeshes
			//The only drawback however is that the entire verticie set of the model is dumped, rather than being segmented properly.
			//ExportD3DMeshToAssimpV2(&parsedD3DMesh, fileEntry.fileNameWithoutExtension, OUTPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP);

			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V3 ||||||||||||||||||||||||||||||||||||||||
			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V3 ||||||||||||||||||||||||||||||||||||||||
			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V3 ||||||||||||||||||||||||||||||||||||||||
			ExportD3DMeshToAssimpV3(&parsedD3DMesh, fileEntry.fileNameWithoutExtension, OUTPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP);
		}
	}

	std::cout << "Finished... READ_D3DMESH_EXPORT_JSON_AND_ASSIMP " << std::endl;
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ JSON / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ JSON / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ JSON / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_D3DMESH_JSON_EXPORT_D3DMESH)
	std::cout << "Starting... READ_D3DMESH_JSON_EXPORT_D3DMESH " << std::endl;
	
	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator(INPUT_DIRECTORY_D3DMESH_JSON))
	{
		FileEntry fileEntry = FileEntry(directoryEntry);

		if (fileEntry.fileExtension == JSON_EXTENSION)
		{
			//=================== READ D3DMESH JSON ===================
			std::ifstream inputFileStream;
			inputFileStream.open(fileEntry.filePath, std::fstream::in | std::fstream::binary);

			nlohmann::ordered_json readJson;
			inputFileStream >> readJson;

			TelltaleD3DMeshFileV55 parsedD3DMesh = readJson.template get<TelltaleD3DMeshFileV55>();

			inputFileStream.close();

			//=================== EXPORT D3DMESH ===================
			//parsedD3DMesh.EraseAllBoneData();
			//parsedD3DMesh.ZeroOutBoneData();

			parsedD3DMesh.UpdateStructures();

			std::ofstream outputFileStream;
			std::string d3dmeshExportPath = OUTPUT_DIRECTORY_JSON_TO_D3DMESH + fileEntry.fileNameWithoutExtension + D3DMESH_EXTENSION;
			outputFileStream.open(d3dmeshExportPath, std::ios::binary);
			parsedD3DMesh.BinarySerialize(&outputFileStream);
			outputFileStream.close();

			std::cout << "EXPORTED... " << d3dmeshExportPath << std::endl;
		}
	}

	std::cout << "Finished... READ_D3DMESH_JSON_EXPORT_D3DMESH " << std::endl;
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH AND SKL ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH AND SKL ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH AND SKL ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_D3DMESH_AND_SKL)
	std::cout << "Starting... READ_D3DMESH_AND_SKL " << std::endl;
	
	for (const auto& d3dmeshDirectoryEntry : std::filesystem::recursive_directory_iterator(INPUT_DIRECTORY_D3DMESH_AND_SKL))
	{
		FileEntry d3dmeshFileEntry = FileEntry(d3dmeshDirectoryEntry);

		if (d3dmeshFileEntry.fileExtension == D3DMESH_EXTENSION)
		{
			//=================== READ D3DMESH ===================
			std::cout << "READING... " << d3dmeshFileEntry.filePath << " [" << d3dmeshFileEntry.fileSize << " BYTES]" << std::endl;

			std::ifstream inputFileStream;
			inputFileStream.open(d3dmeshFileEntry.filePath, std::fstream::in | std::fstream::binary);
			TelltaleD3DMeshFileV55 parsedD3DMesh = TelltaleD3DMeshFileV55(&inputFileStream);
			inputFileStream.close();

			if (parsedD3DMesh.HasBones())
			{
				FileEntry sklFileEntry;
				bool hasSKL = false;

				for (const auto& sklDirectoryEntry : std::filesystem::recursive_directory_iterator(INPUT_DIRECTORY_D3DMESH_AND_SKL))
				{
					FileEntry newFileEntry = FileEntry(sklDirectoryEntry);

					if (newFileEntry.fileExtension == SKL_EXTENSION)
					{
						if (d3dmeshFileEntry.fileNameWithoutExtension == newFileEntry.fileNameWithoutExtension)
						{
							sklFileEntry = newFileEntry;
							hasSKL = true;
						}
					}
				}

				if (!hasSKL)
					std::cout << "[D3DMESH INFO] " << d3dmeshFileEntry.filePath << " has bones but no matching .skl file was found!" << std::endl;
			}
		}
	}

	std::cout << "Finished... READ_D3DMESH_AND_SKL " << std::endl;
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH JSON AND ASSIMP / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH JSON AND ASSIMP / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH JSON AND ASSIMP / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
#if defined(READ_D3DMESH_JSON_AND_ASSIMP_EXPORT_D3DMESH)
	std::cout << "Starting... READ_D3DMESH_JSON_AND_ASSIMP_EXPORT_D3DMESH " << std::endl;
	
	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator(INPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP))
	{
		FileEntry d3dmeshJsonFileEntry = FileEntry(directoryEntry);

		if (d3dmeshJsonFileEntry.fileExtension == JSON_EXTENSION)
		{
			for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator(INPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP))
			{
				FileEntry assimpFileEntry = FileEntry(directoryEntry);

				if (assimpFileEntry.fileExtension == ASSIMP_EXTENSION && assimpFileEntry.fileNameWithoutExtension == d3dmeshJsonFileEntry.fileNameWithoutExtension)
				{
					ConvertAssimpToD3DMeshDataV1(&d3dmeshJsonFileEntry, &assimpFileEntry, OUTPUT_DIRECTORY_ASSIMP_TO_D3DMESH + d3dmeshJsonFileEntry.fileNameWithoutExtension + D3DMESH_EXTENSION);
					break;
				}
			}
		}
	}

	std::cout << "Finished... READ_D3DMESH_JSON_AND_ASSIMP_EXPORT_D3DMESH " << std::endl;
#endif

	return 0;
}
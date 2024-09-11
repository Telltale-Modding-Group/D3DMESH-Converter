#pragma once
#ifndef APPLICATION_READ_D3DMESH_EXPORT_D3DMESH_JSON_AND_ASSIMP_H
#define APPLICATION_READ_D3DMESH_EXPORT_D3DMESH_JSON_AND_ASSIMP_H

//||||||||||||||||||||||||||||| PREPROCESSOR MACROS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| PREPROCESSOR MACROS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| PREPROCESSOR MACROS |||||||||||||||||||||||||||||

#include "Application_Macros.h"

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

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

#include "D3DMeshDataToAssimpV1.h"
#include "D3DMeshDataToAssimpV2.h"
#include "D3DMeshDataToAssimpV3.h"

//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT D3DMESH JSON AND ASSIMP ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT D3DMESH JSON AND ASSIMP ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT D3DMESH JSON AND ASSIMP ||||||||||||||||||||||||||||||||||||||||

void Application_ReadD3DMesh_ExportD3DMeshJsonAndAssimp()
{
	std::cout << "Starting... READ D3DMESH / EXPORT D3DMESH JSON AND ASSIMP " << std::endl;

	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||

	if (std::filesystem::is_directory(INPUT_DIRECTORY_D3DMESH) == false)
	{
		std::cout << "INPUT_DIRECTORY_D3DMESH: " << INPUT_DIRECTORY_D3DMESH << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(INPUT_DIRECTORY_D3DMESH);
	}

	if (std::filesystem::is_directory(OUTPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP) == false)
	{
		std::cout << "OUTPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP: " << OUTPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(OUTPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP);
	}

	//|||||||||||||||||||||||||||||||||||||||| LOOP THROUGH DIRECTORY ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| LOOP THROUGH DIRECTORY ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| LOOP THROUGH DIRECTORY ||||||||||||||||||||||||||||||||||||||||

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

	std::cout << "Finished... READ D3DMESH / EXPORT D3DMESH JSON AND ASSIMP " << std::endl;
}

#endif
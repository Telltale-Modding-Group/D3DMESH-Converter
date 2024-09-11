#pragma once
#ifndef APPLICATION_READ_D3DMESH_JSON_EXPORT_D3DMESH_H
#define APPLICATION_READ_D3DMESH_JSON_EXPORT_D3DMESH_H

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

//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH JSON / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH JSON / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH JSON / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||

void Application_ReadD3DMeshJson_ExportD3DMesh()
{
	std::cout << "Starting... READ D3DMESH JSON / EXPORT D3DMESH " << std::endl;

	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||

	if (std::filesystem::is_directory(INPUT_DIRECTORY_D3DMESH_JSON) == false)
	{
		std::cout << "INPUT_DIRECTORY_D3DMESH_JSON: " << INPUT_DIRECTORY_D3DMESH_JSON << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(INPUT_DIRECTORY_D3DMESH_JSON);
	}

	if (std::filesystem::is_directory(OUTPUT_DIRECTORY_JSON_TO_D3DMESH) == false)
	{
		std::cout << "OUTPUT_DIRECTORY_JSON_TO_D3DMESH: " << OUTPUT_DIRECTORY_JSON_TO_D3DMESH << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(OUTPUT_DIRECTORY_JSON_TO_D3DMESH);
	}

	//|||||||||||||||||||||||||||||||||||||||| LOOP THROUGH DIRECTORY ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| LOOP THROUGH DIRECTORY ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| LOOP THROUGH DIRECTORY ||||||||||||||||||||||||||||||||||||||||

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

	std::cout << "Finished... READ D3DMESH JSON / EXPORT D3DMESH " << std::endl;
}

#endif
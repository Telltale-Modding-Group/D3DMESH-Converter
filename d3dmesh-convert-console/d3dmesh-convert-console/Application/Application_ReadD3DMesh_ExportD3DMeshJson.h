#pragma once
#ifndef APPLICATION_READ_D3DMESH_EXPORT_D3DMESH_JSON_H
#define APPLICATION_READ_D3DMESH_EXPORT_D3DMESH_JSON_H

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

//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT D3DMESH JSON ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT D3DMESH JSON ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT D3DMESH JSON ||||||||||||||||||||||||||||||||||||||||

void Application_ReadD3DMesh_ExportD3DMeshJson()
{
	std::cout << "Starting... READ D3DMESH / EXPORT D3DMESH JSON " << std::endl;

	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||

	if (std::filesystem::is_directory(INPUT_DIRECTORY_D3DMESH) == false)
	{
		std::cout << "INPUT_DIRECTORY_D3DMESH: " << INPUT_DIRECTORY_D3DMESH << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(INPUT_DIRECTORY_D3DMESH);
	}

	if (std::filesystem::is_directory(OUTPUT_DIRECTORY_D3DMESH_TO_JSON) == false)
	{
		std::cout << "OUTPUT_DIRECTORY_D3DMESH_TO_JSON: " << OUTPUT_DIRECTORY_D3DMESH_TO_JSON << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(OUTPUT_DIRECTORY_D3DMESH_TO_JSON);
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

	std::cout << "Finished... READ D3DMESH / EXPORT D3DMESH JSON " << std::endl;
}

#endif
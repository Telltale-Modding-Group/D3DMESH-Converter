#pragma once
#ifndef APPLICATION_READ_SKELETON_EXPORT_SKELETON_JSON_H
#define APPLICATION_READ_SKELETON_EXPORT_SKELETON_JSON_H

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
#include "Telltale/DataTypes/TelltaleSkeletonFile.h"

//|||||||||||||||||||||||||||||||||||||||| READ SKELETON / EXPORT SKELETON JSON ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| READ SKELETON / EXPORT SKELETON JSON ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| READ SKELETON / EXPORT SKELETON JSON ||||||||||||||||||||||||||||||||||||||||

void Application_ReadSkeleton_ExportSkeletonJson()
{
	std::cout << "Starting... READ SKELETON / EXPORT SKELETON JSON " << std::endl;

	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||

	if (std::filesystem::is_directory(INPUT_DIRECTORY_SKL) == false)
	{
		std::cout << "INPUT_DIRECTORY_SKL: " << INPUT_DIRECTORY_SKL << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(INPUT_DIRECTORY_SKL);
	}

	if (std::filesystem::is_directory(OUTPUT_DIRECTORY_SKL_TO_JSON) == false)
	{
		std::cout << "OUTPUT_DIRECTORY_SKL_TO_JSON: " << OUTPUT_DIRECTORY_SKL_TO_JSON << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(OUTPUT_DIRECTORY_SKL_TO_JSON);
	}

	//|||||||||||||||||||||||||||||||||||||||| LOOP THROUGH DIRECTORY ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| LOOP THROUGH DIRECTORY ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| LOOP THROUGH DIRECTORY ||||||||||||||||||||||||||||||||||||||||

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

	std::cout << "Finished... READ SKELETON / EXPORT SKELETON JSON " << std::endl;
}

#endif
#pragma once
#ifndef APPLICATION_READ_SKELETON_JSON_EXPORT_SKELETON_H
#define APPLICATION_READ_SKELETON_JSON_EXPORT_SKELETON_H

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

//|||||||||||||||||||||||||||||||||||||||| READ SKELETON JSON / EXPORT SKELETON ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| READ SKELETON JSON / EXPORT SKELETON ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| READ SKELETON JSON / EXPORT SKELETON ||||||||||||||||||||||||||||||||||||||||

void Application_ReadSkeletonJson_ExportSkeleton()
{
	std::cout << "Starting... READ SKELETON JSON / EXPORT SKELETON " << std::endl;

	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||

	if (std::filesystem::is_directory(INPUT_DIRECTORY_SKL_JSON) == false)
	{
		std::cout << "INPUT_DIRECTORY_SKL_JSON: " << INPUT_DIRECTORY_SKL_JSON << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(INPUT_DIRECTORY_SKL_JSON);
	}

	if (std::filesystem::is_directory(OUTPUT_DIRECTORY_JSON_TO_SKL) == false)
	{
		std::cout << "OUTPUT_DIRECTORY_JSON_TO_SKL: " << OUTPUT_DIRECTORY_JSON_TO_SKL << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(OUTPUT_DIRECTORY_JSON_TO_SKL);
	}

	//|||||||||||||||||||||||||||||||||||||||| LOOP THROUGH DIRECTORY ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| LOOP THROUGH DIRECTORY ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| LOOP THROUGH DIRECTORY ||||||||||||||||||||||||||||||||||||||||

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

	std::cout << "Finished... READ SKELETON JSON / EXPORT SKELETON " << std::endl;
}

#endif
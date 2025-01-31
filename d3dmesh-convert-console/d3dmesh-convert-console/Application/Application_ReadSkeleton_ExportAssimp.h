#pragma once
#ifndef APPLICATION_READ_SKELETON_EXPORT_ASSIMP_H
#define APPLICATION_READ_SKELETON_EXPORT_ASSIMP_H

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
#include "../CustomTypes/FileEntry.h"
#include "../Telltale/DataTypes/TelltaleSkeletonFile.h"

#include "SkeletonToAssimpV1.h"

//|||||||||||||||||||||||||||||||||||||||| READ SKELETON / EXPORT ASSIMP ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| READ SKELETON / EXPORT ASSIMP ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| READ SKELETON / EXPORT ASSIMP ||||||||||||||||||||||||||||||||||||||||

void Application_ReadSkeleton_ExportAssimp()
{
	std::cout << "Starting... READ SKELETON / EXPORT ASSIMP " << std::endl;

	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||

	if (std::filesystem::is_directory(INPUT_DIRECTORY_SKL) == false)
	{
		std::cout << "INPUT_DIRECTORY_SKL: " << INPUT_DIRECTORY_SKL << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(INPUT_DIRECTORY_SKL);
	}

	if (std::filesystem::is_directory(OUTPUT_DIRECTORY_SKL_TO_ASSIMP) == false)
	{
		std::cout << "OUTPUT_DIRECTORY_SKL_TO_ASSIMP: " << OUTPUT_DIRECTORY_SKL_TO_ASSIMP << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(OUTPUT_DIRECTORY_SKL_TO_ASSIMP);
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

			//=================== EXPORT ASSIMP ===================
			BuildAssimpSkeletonFromSkeletonV1(&sklFile, fileEntry.fileNameWithoutExtension, OUTPUT_DIRECTORY_SKL_TO_ASSIMP);
		}
	}

	std::cout << "Finished... READ SKELETON / EXPORT ASSIMP " << std::endl;
}

#endif
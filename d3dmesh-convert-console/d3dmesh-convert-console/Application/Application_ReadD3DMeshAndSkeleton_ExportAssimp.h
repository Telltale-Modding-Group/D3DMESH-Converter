#pragma once
#ifndef APPLICATION_READ_D3DMESH_AND_SKELETON_EXPORT_ASSIMP_H
#define APPLICATION_READ_D3DMESH_AND_SKELETON_EXPORT_ASSIMP_H

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

//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH AND SKELETON ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH AND SKELETON ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH AND SKELETON ||||||||||||||||||||||||||||||||||||||||

void Application_ReadD3DMeshAndSkeleton_ExportAssimp()
{
	std::cout << "Starting... READ D3DMESH AND SKELETON AND EXPORT ASSIMP " << std::endl;

	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||

	if (std::filesystem::is_directory(INPUT_DIRECTORY_D3DMESH_AND_SKL) == false)
	{
		std::cout << "INPUT_DIRECTORY_D3DMESH_AND_SKL: " << INPUT_DIRECTORY_D3DMESH_AND_SKL << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(INPUT_DIRECTORY_D3DMESH_AND_SKL);
	}

	//|||||||||||||||||||||||||||||||||||||||| LOOP THROUGH DIRECTORY ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| LOOP THROUGH DIRECTORY ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| LOOP THROUGH DIRECTORY ||||||||||||||||||||||||||||||||||||||||

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

	std::cout << "Finished... READ D3DMESH AND SKELETON " << std::endl;
}

#endif
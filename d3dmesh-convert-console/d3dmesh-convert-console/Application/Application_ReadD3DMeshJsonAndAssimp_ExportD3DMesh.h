#pragma once
#ifndef APPLICATION_READ_D3DMESH_JSON_AND_ASSIMP_EXPORT_D3DMESH_H
#define APPLICATION_READ_D3DMESH_JSON_AND_ASSIMP_EXPORT_D3DMESH_H

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

#include "AssimpToD3DMeshDataV1.h"

//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH JSON AND ASSIMP / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH JSON AND ASSIMP / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH JSON AND ASSIMP / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||

void Application_ReadD3DMeshJsonAndAssimp_ExportD3DMesh()
{
	std::cout << "Starting... READ D3DMESH JSON AND ASSIMP / EXPORT D3DMESH " << std::endl;

	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||

	if (std::filesystem::is_directory(INPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP) == false)
	{
		std::cout << "INPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP: " << INPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(INPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP);
	}

	if (std::filesystem::is_directory(OUTPUT_DIRECTORY_ASSIMP_TO_D3DMESH) == false)
	{
		std::cout << "OUTPUT_DIRECTORY_ASSIMP_TO_D3DMESH: " << OUTPUT_DIRECTORY_ASSIMP_TO_D3DMESH << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(OUTPUT_DIRECTORY_ASSIMP_TO_D3DMESH);
	}

	//|||||||||||||||||||||||||||||||||||||||| LOOP THROUGH DIRECTORY ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| LOOP THROUGH DIRECTORY ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| LOOP THROUGH DIRECTORY ||||||||||||||||||||||||||||||||||||||||

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

	std::cout << "Finished... READ D3DMESH JSON AND ASSIMP / EXPORT D3DMESH " << std::endl;
}

#endif
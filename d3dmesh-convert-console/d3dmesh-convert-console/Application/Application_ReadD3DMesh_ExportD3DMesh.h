#pragma once
#ifndef APPLICATION_READ_D3DMESH_EXPORT_D3DMESH_H
#define APPLICATION_READ_D3DMESH_EXPORT_D3DMESH_H

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

//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||

void Application_ReadD3DMesh_ExportD3DMesh()
{
	std::cout << "Starting... READ D3DMESH / EXPORT D3DMESH " << std::endl;

	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| DIRECTORY CHECKING/SETUP ||||||||||||||||||||||||||||||||||||||||

	if (std::filesystem::is_directory(INPUT_DIRECTORY_D3DMESH) == false)
	{
		std::cout << "INPUT_DIRECTORY_D3DMESH: " << INPUT_DIRECTORY_D3DMESH << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(INPUT_DIRECTORY_D3DMESH);
	}

	if (std::filesystem::is_directory(OUTPUT_DIRECTORY_D3DMESH_TO_D3DMESH) == false)
	{
		std::cout << "OUTPUT_DIRECTORY_D3DMESH_TO_D3DMESH: " << OUTPUT_DIRECTORY_D3DMESH_TO_D3DMESH << " does not exist! Creating directory..." << std::endl;
		std::filesystem::create_directory(OUTPUT_DIRECTORY_D3DMESH_TO_D3DMESH);
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
			parsedD3DMesh.UpdateStructures();

			std::ofstream outputFileStream;
			std::string d3dmeshExportPath = OUTPUT_DIRECTORY_D3DMESH_TO_D3DMESH + fileEntry.fileNameWithExtension;
			outputFileStream.open(d3dmeshExportPath, std::ios::binary);
			parsedD3DMesh.BinarySerialize(&outputFileStream);
			outputFileStream.close();

			std::cout << "EXPORTED... " << d3dmeshExportPath << std::endl;
		}
	}

	std::cout << "Finished... READ D3DMESH / EXPORT D3DMESH " << std::endl;
}

#endif
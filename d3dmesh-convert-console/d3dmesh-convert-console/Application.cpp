//||||||||||||||||||||||||||||| PREPROCESSOR MACROS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| PREPROCESSOR MACROS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| PREPROCESSOR MACROS |||||||||||||||||||||||||||||

#define ASSIMP_EXPORT_SHADOW

//#define READ_D3DMESH
//#define READ_D3DMESH_AND_SKL
#define READ_D3DMESH_EXPORT_ASSIMP
//#define READ_D3DMESH_EXPORT_JSON
//#define READ_D3DMESH_EXPORT_D3DMESH
//#define READ_JSON_EXPORT_D3DMESH

//#define READ_SKL
//#define READ_SKL_EXPORT_JSON
//#define READ_SKL_EXPORT_SKL
//#define READ_JSON_EXPORT_SKL

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
#include "FileEntry.h"
#include "TelltaleD3DMeshFileV55.h"
#include "TelltaleSkeletonFile.h"
#include "D3DMeshDataToAssimpV1.h"
#include "D3DMeshDataToAssimpV2.h"
#include "D3DMeshDataToAssimpV3.h"

//|||||||||||||||||||||||||||||||||||||||| MAIN ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| MAIN ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| MAIN ||||||||||||||||||||||||||||||||||||||||

int main()
{
	//|||||||||||||||||||||||||||||||||||||||| READ SKL ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ SKL ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ SKL ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_SKL)
	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator("InputSKL"))
	{
		FileEntry fileEntry = FileEntry(directoryEntry);

		if (fileEntry.fileExtension == ".skl")
		{
			//=================== READ SKL ===================
			std::cout << "READING... " << fileEntry.filePath << " [" << fileEntry.fileSize << " BYTES]" << std::endl;

			std::ifstream inputFileStream;
			inputFileStream.open(fileEntry.filePath, std::fstream::in | std::fstream::binary);

			TelltaleSkeletonFile sklFile = TelltaleSkeletonFile(&inputFileStream);

			inputFileStream.close();
		}
	}
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ SKL / EXPORT JSON ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ SKL / EXPORT JSON ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ SKL / EXPORT JSON ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_SKL_EXPORT_JSON)
	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator("InputSKL"))
	{
		FileEntry fileEntry = FileEntry(directoryEntry);

		if (fileEntry.fileExtension == ".skl")
		{
			//=================== READ SKL ===================
			std::cout << "READING... " << fileEntry.filePath << " [" << fileEntry.fileSize << " BYTES]" << std::endl;

			std::ifstream inputFileStream;
			inputFileStream.open(fileEntry.filePath, std::fstream::in | std::fstream::binary);

			TelltaleSkeletonFile sklFile = TelltaleSkeletonFile(&inputFileStream);

			inputFileStream.close();

			//=================== EXPORT SKL TO JSON ===================
			std::ofstream outputFileStream;
			std::string jsonExportPath = "OutputSKL_TO_JSON/" + fileEntry.fileNameWithoutExtension + ".json";
			outputFileStream.open(jsonExportPath);

			nlohmann::ordered_json json;
			json = sklFile;

			std::string jsonDump = json.dump(4); //pretty print with indents
			outputFileStream.write(jsonDump.c_str(), jsonDump.length());
			outputFileStream.close();
		}
	}
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ SKL / EXPORT SKL ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ SKL / EXPORT SKL ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ SKL / EXPORT SKL ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_SKL_EXPORT_SKL)
	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator("InputSKL"))
	{
		FileEntry fileEntry = FileEntry(directoryEntry);

		if (fileEntry.fileExtension == ".skl")
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
			std::string sklExportPath = "OutputSKL_TO_SKL/" + fileEntry.fileNameWithExtension;
			outputFileStream.open(sklExportPath, std::ios::binary);
			sklFile.BinarySerialize(&outputFileStream);
			outputFileStream.close();
		}
	}
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ JSON / EXPORT SKL ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ JSON / EXPORT SKL ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ JSON / EXPORT SKL ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_JSON_EXPORT_SKL)
	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator("InputSKL_JSON"))
	{
		FileEntry fileEntry = FileEntry(directoryEntry);

		if (fileEntry.fileExtension == ".json")
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
			std::string sklExportPath = "OutputJSON_TO_SKL/" + fileEntry.fileNameWithoutExtension + ".skl";
			outputFileStream.open(sklExportPath, std::ios::binary);
			sklFile.BinarySerialize(&outputFileStream);
			outputFileStream.close();

			std::cout << "EXPORTED... " << sklExportPath << std::endl;
		}
	}
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_D3DMESH)
	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator("InputD3DMESH"))
	{
		FileEntry fileEntry = FileEntry(directoryEntry);

		if (fileEntry.fileExtension == ".d3dmesh")
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
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_D3DMESH_EXPORT_D3DMESH)
	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator("InputD3DMESH"))
	{
		FileEntry fileEntry = FileEntry(directoryEntry);

		if (fileEntry.fileExtension == ".d3dmesh")
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
			std::string d3dmeshExportPath = "OutputD3DMESH_TO_D3DMESH/" + fileEntry.fileNameWithExtension;
			outputFileStream.open(d3dmeshExportPath, std::ios::binary);
			parsedD3DMesh.BinarySerialize(&outputFileStream);
			outputFileStream.close();

			std::cout << "EXPORTED... " << d3dmeshExportPath << std::endl;
		}
	}
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT JSON ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT JSON ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT JSON ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_D3DMESH_EXPORT_JSON)
	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator("InputD3DMESH"))
	{
		FileEntry fileEntry = FileEntry(directoryEntry);

		if (fileEntry.fileExtension == ".d3dmesh")
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
			std::string jsonExportPath = "OutputD3DMESH_TO_JSON/" + fileEntry.fileNameWithoutExtension + ".json";
			outputFileStream.open(jsonExportPath);

			nlohmann::ordered_json json;
			json = parsedD3DMesh;

			std::string jsonDump = json.dump(4); //pretty print with indents
			outputFileStream.write(jsonDump.c_str(), jsonDump.length());

			outputFileStream.close();
		}
	}
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT ASSIMP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT ASSIMP ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ D3DMESH / EXPORT ASSIMP ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_D3DMESH_EXPORT_ASSIMP)
	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator("InputD3DMESH"))
	{
		FileEntry fileEntry = FileEntry(directoryEntry);

		if (fileEntry.fileExtension == ".d3dmesh")
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
			//ExportD3DMeshToAssimpV1(&parsedD3DMesh, fileEntry.fileNameWithoutExtension);

			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V2 ||||||||||||||||||||||||||||||||||||||||
			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V2 ||||||||||||||||||||||||||||||||||||||||
			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V2 ||||||||||||||||||||||||||||||||||||||||
			//Second attempt at doing a conversion of a d3dmesh to a standard model format.
			//This uses the mLOD's and T3MeshBatch's to pull each LOD/Submesh from the model.
			//The verticies however that are currently referenced are from the ENTIRE model. (Ideally we segment the verticies by only what we use)
			//This is alot more sucessful than the first attempt as now we can factor in LOD/Submeshes
			//The only drawback however is that the entire verticie set of the model is dumped, rather than being segmented properly.
			//ExportD3DMeshToAssimpV2(&parsedD3DMesh, fileEntry.fileNameWithoutExtension);

			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V3 ||||||||||||||||||||||||||||||||||||||||
			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V3 ||||||||||||||||||||||||||||||||||||||||
			//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V3 ||||||||||||||||||||||||||||||||||||||||
			ExportD3DMeshToAssimpV3(&parsedD3DMesh, fileEntry.fileNameWithoutExtension);
		}
	}
#endif

	//|||||||||||||||||||||||||||||||||||||||| READ JSON / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ JSON / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READ JSON / EXPORT D3DMESH ||||||||||||||||||||||||||||||||||||||||
#if defined (READ_JSON_EXPORT_D3DMESH)
	for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator("InputD3DMESH_JSON"))
	{
		FileEntry fileEntry = FileEntry(directoryEntry);

		if (fileEntry.fileExtension == ".json")
		{
			//=================== READ D3DMESH JSON ===================
			std::ifstream inputFileStream;
			inputFileStream.open(fileEntry.filePath, std::fstream::in | std::fstream::binary);

			nlohmann::ordered_json readJson;
			inputFileStream >> readJson;

			TelltaleD3DMeshFileV55 parsedD3DMesh = readJson.template get<TelltaleD3DMeshFileV55>();

			inputFileStream.close();

			//=================== EXPORT D3DMESH ===================
			std::ofstream outputFileStream;
			std::string d3dmeshExportPath = "OutputJSON_TO_D3DMESH/" + fileEntry.fileNameWithoutExtension + ".d3dmesh";
			outputFileStream.open(d3dmeshExportPath, std::ios::binary);
			parsedD3DMesh.BinarySerialize(&outputFileStream);
			outputFileStream.close();

			std::cout << "EXPORTED... " << d3dmeshExportPath << std::endl;
		}
	}
#endif

#if defined (READ_D3DMESH_AND_SKL)
	for (const auto& d3dmeshDirectoryEntry : std::filesystem::recursive_directory_iterator("InputD3DMESH_AND_SKL"))
	{
		FileEntry d3dmeshFileEntry = FileEntry(d3dmeshDirectoryEntry);

		if (d3dmeshFileEntry.fileExtension == ".d3dmesh")
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

				for (const auto& sklDirectoryEntry : std::filesystem::recursive_directory_iterator("InputD3DMESH_AND_SKL"))
				{
					FileEntry newFileEntry = FileEntry(sklDirectoryEntry);

					if (newFileEntry.fileExtension == ".skl")
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
#endif

	return 0;
}
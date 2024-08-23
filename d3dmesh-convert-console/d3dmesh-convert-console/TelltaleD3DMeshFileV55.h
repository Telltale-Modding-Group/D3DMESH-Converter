#pragma once
#ifndef TELLTALE_D3DMESH_FILE_55_H
#define TELLTALE_D3DMESH_FILE_55_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "TelltaleMetaHeaderVersion6.h"
#include "TelltaleD3DMeshHeaderV55.h"
#include "TelltaleD3DMeshDataV55.h"

//||||||||||||||||||||||||||||| TELLTALE D3DMESH FILE V55 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE D3DMESH FILE V55 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE D3DMESH FILE V55 |||||||||||||||||||||||||||||

class TelltaleD3DMeshFileV55
{
public:
	TelltaleMetaHeaderVersion6 metaHeader;
	TelltaleD3DMeshHeaderV55 d3dmeshHeader;
	TelltaleD3DMeshDataV55 d3dmeshData;

	TelltaleD3DMeshFileV55()
	{

	};

	TelltaleD3DMeshFileV55(std::ifstream* inputFileStream)
	{
		//telltale files always have a "meta" header serialized ontop of the file
		//this header is important as it tells the engine (and us) the size of the d3dmesh header, and the size of the file data after the headers.
		//it also contains misc information like the reference class names and types, which are hashed (CRC64)
		metaHeader = TelltaleMetaHeaderVersion6(inputFileStream);

		//we finished going through the meta header, so the offset we left off at matches the size of the meta header
		unsigned long metaHeaderSize = inputFileStream->tellg();

		//here we get into the important parts of the file.
		//after parsing the meta header, the main d3dmesh header is serialized right after it
		//this is the most important part as it contains all of the necessary information about the mesh so that we can read/extract it properly.
		d3dmeshHeader = TelltaleD3DMeshHeaderV55(inputFileStream);

		//here after reading the header, the actual mesh data is serialized right after it, using what we know from the header we pull the data accordingly here.
		d3dmeshData = TelltaleD3DMeshDataV55(inputFileStream, &d3dmeshHeader);

		//We have (hopefully) reached the end of the file!
		//print output so we can check if we actually reached the end of the file. If we did then the bytes left to traverse in the file should be 0.
		unsigned long long totalFileSizeCalculation = metaHeaderSize + metaHeader.mDefaultSectionChunkSize + metaHeader.mAsyncSectionChunkSize;
		unsigned long long currentSeekPosition = inputFileStream->tellg();
		std::cout << "[READER INFO] Left Off At Offset: " << currentSeekPosition << std::endl;
		//std::cout << "[READER INFO] Bytes Left To Traverse In D3DMESH Header: " << (mDefaultSectionChunkSize - (currentSeekPosition - MetaHeaderSize)) << std::endl;
		std::cout << "[READER INFO] Bytes Left To Traverse In File: " << (long)(totalFileSizeCalculation - currentSeekPosition) << std::endl;
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		metaHeader.BinarySerialize(outputFileStream);
		d3dmeshHeader.BinarySerialize(outputFileStream);
		d3dmeshData.BinarySerialize(outputFileStream);
	};
};

#endif
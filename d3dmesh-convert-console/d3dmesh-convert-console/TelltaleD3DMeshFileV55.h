#pragma once
#ifndef TELLTALE_D3DMESH_FILE_55_H
#define TELLTALE_D3DMESH_FILE_55_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Json.h"

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

		//std::cout << metaHeader.ToString() << std::endl;

		//here we get into the important parts of the file.
		//after parsing the meta header, the main d3dmesh header is serialized right after it
		//this is the most important part as it contains all of the necessary information about the mesh so that we can read/extract it properly.
		d3dmeshHeader = TelltaleD3DMeshHeaderV55(inputFileStream);

		//std::cout << d3dmeshHeader.ToString() << std::endl;

		//here after reading the header, the actual mesh data is serialized right after it, using what we know from the header we pull the data accordingly here.
		d3dmeshData = TelltaleD3DMeshDataV55(inputFileStream, &d3dmeshHeader);

		//We have (hopefully) reached the end of the file!
		//print output so we can check if we actually reached the end of the file. If we did then the bytes left to traverse in the file should be 0.
		unsigned long long totalFileSizeCalculation = metaHeaderSize + metaHeader.mDefaultSectionChunkSize + metaHeader.mAsyncSectionChunkSize;
		unsigned long long currentSeekPosition = inputFileStream->tellg();
		long bytesLeftInFile = (long)(totalFileSizeCalculation - currentSeekPosition);

		if(bytesLeftInFile > 0)
			std::cout << "[READER INFO] |||||||||||||||||||||||||||||||| DID NOT REACH END OF FILE! Bytes Left To Traverse In File: " << bytesLeftInFile << std::endl;
	};

	void UpdateValues() 
	{
		d3dmeshHeader.mIndexBufferCount = d3dmeshData.indexBuffers.size();
	}

	bool HasBones() 
	{
		for (int i = 0; i < d3dmeshHeader.mLODs_ArrayLength; i++)
		{
			if (d3dmeshHeader.mLODs[i].mBones_ArrayLength > 0)
				return true;
		}

		return false;
	}

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		metaHeader.mDefaultSectionChunkSize = d3dmeshHeader.GetByteSize();
		metaHeader.mAsyncSectionChunkSize = d3dmeshHeader.GetD3DMeshDataSize();

		metaHeader.BinarySerialize(outputFileStream);
 		d3dmeshHeader.BinarySerialize(outputFileStream);
		d3dmeshData.BinarySerialize(outputFileStream, &d3dmeshHeader);
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(TelltaleD3DMeshFileV55, metaHeader, d3dmeshHeader, d3dmeshData)
};

#endif
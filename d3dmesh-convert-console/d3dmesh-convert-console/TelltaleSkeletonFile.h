#pragma once
#ifndef TELLTALE_SKL_H
#define TELLTALE_SKL_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Json.h"

#include "TelltaleMetaHeaderVersion6.h"
#include "Skeleton.h"

//||||||||||||||||||||||||||||| TELLTALE SKL FILE |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE SKL FILE |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE SKL FILE |||||||||||||||||||||||||||||

class TelltaleSkeletonFile
{
public:

	TelltaleMetaHeaderVersion6 metaHeader;
	Skeleton skeleton;

	TelltaleSkeletonFile()
	{

	};

	TelltaleSkeletonFile(std::ifstream* inputFileStream)
	{
		//telltale files always have a "meta" header serialized ontop of the file
		//this header is important as it tells the engine (and us) the size of the d3dmesh header, and the size of the file data after the headers.
		//it also contains misc information like the reference class names and types, which are hashed (CRC64)
		metaHeader = TelltaleMetaHeaderVersion6(inputFileStream);

		//we finished going through the meta header, so the offset we left off at matches the size of the meta header
		unsigned long metaHeaderSize = inputFileStream->tellg();

		skeleton = Skeleton(inputFileStream);

		//We have (hopefully) reached the end of the file!
		//print output so we can check if we actually reached the end of the file. If we did then the bytes left to traverse in the file should be 0.
		unsigned long long totalFileSizeCalculation = metaHeaderSize + metaHeader.mDefaultSectionChunkSize + metaHeader.mAsyncSectionChunkSize;
		unsigned long long currentSeekPosition = inputFileStream->tellg();
		long bytesLeftInFile = (long)(totalFileSizeCalculation - currentSeekPosition);

		if (bytesLeftInFile > 0)
			std::cout << "[READER INFO] |||||||||||||||||||||||||||||||| DID NOT REACH END OF FILE! Bytes Left To Traverse In File: " << bytesLeftInFile << std::endl;
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{

	};
};

#endif
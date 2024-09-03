#pragma once
#ifndef SKELETON_H
#define SKELETON_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Json.h"

#include "SkeletonEntry.h"

//||||||||||||||||||||||||||||| SKELETON |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| SKELETON |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| SKELETON |||||||||||||||||||||||||||||

class Skeleton
{
public:

	Skeleton()
	{

	};

	Skeleton(std::ifstream* inputFileStream)
	{
		unsigned int mBlockSize = ReadUInt32FromBinary(inputFileStream);
		unsigned int mEntriesCount = ReadUInt32FromBinary(inputFileStream);

		std::cout << "[Skeleton] mBlockSize: " << mBlockSize << std::endl;
		std::cout << "[Skeleton] mEntriesCount: " << mEntriesCount << std::endl;

		//for (int i = 0; i < mEntriesCount; i++)
		for (int i = 0; i < 1; i++)
		{
			std::cout << "[Skeleton] --------- SKELETON ENTRY " << i << " ---------" << std::endl;

			SkeletonEntry skeletonEntry = SkeletonEntry(inputFileStream);
		}

		std::cout << "[READER INFO] Left Off At Offset: " << inputFileStream->tellg() << std::endl;
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{

	};
};

#endif
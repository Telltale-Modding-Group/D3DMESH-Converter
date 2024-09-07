#pragma once
#ifndef TELLTALE_SKL_H
#define TELLTALE_SKL_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "../../BinarySerialization.h"
#include "../../BinaryDeserialization.h"
#include "../../Json.h"
#include "../../Telltale/DataTypes/TelltaleMetaHeaderVersion6.h"
#include "../../Telltale/DataTypes/Skeleton.h"

//||||||||||||||||||||||||||||| TELLTALE SKL FILE |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE SKL FILE |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE SKL FILE |||||||||||||||||||||||||||||

class TelltaleSkeletonFile
{
public:

	TelltaleMetaHeaderVersion6 metaHeader;
	Skeleton skeleton;

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

	TelltaleSkeletonFile()
	{
		metaHeader = {};
		skeleton = {};
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

	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//NOTE: This is critical as any mishap in regards to new/removed data will crash the game.
	//So in advance we need to update all structural values (block sizes, array lengths, array capacities) to make sure everything lines up.

	void UpdateStructures()
	{
		//need to update our main data before getting the final size for the meta header later.
		skeleton.UpdateStructures();

		metaHeader.mDefaultSectionChunkSize = skeleton.GetByteSize();
	}

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		metaHeader.BinarySerialize(outputFileStream);
		skeleton.BinarySerialize(outputFileStream);
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "";
		output += "[TelltaleSkeletonFile] metaHeader: " + metaHeader.ToString() + "\n";
		output += "[TelltaleSkeletonFile] skeleton: " + skeleton.ToString() + "\n";
		return output;
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(TelltaleSkeletonFile, metaHeader, skeleton)

	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//NOTE: Yes I'm aware that C++ has functionality/operators for returning the size of the object, however...
	//For some of these structs/classes the size C++ returns/gets is wrong and doesn't match what telltale would expect.
	//So for saftey I will just manually calculate the byte size of the object here to what telltale expects.

	/// <summary>
	/// [x BYTES]
	/// </summary>
	/// <returns></returns>
	unsigned int GetByteSize()
	{
		unsigned int totalByteSize = 0;
		totalByteSize += metaHeader.GetByteSize(); //[x BYTES] metaHeader
		totalByteSize += skeleton.GetByteSize(); //[x BYTES] skeleton
		return totalByteSize;
	}
};

#endif
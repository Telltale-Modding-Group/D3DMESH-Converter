#pragma once
#ifndef TELLTALE_MESH_DATA_STORAGE_H
#define TELLTALE_MESH_DATA_STORAGE_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "../../Telltale/DataTypes/TelltaleD3DMeshFileV55.h"
#include "../../Telltale/DataTypes/TelltaleSkeletonFile.h"

//||||||||||||||||||||||||||||| TELLTALE MESH DATA STORAGE |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE MESH DATA STORAGE |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE MESH DATA STORAGE |||||||||||||||||||||||||||||
//NOTE: This is NOT a data structure used by telltale.

struct TelltaleMeshDataStorage
{
	TelltaleD3DMeshFileV55 d3dmeshFile;
	TelltaleSkeletonFile skeletonFile;

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

	TelltaleMeshDataStorage()
	{
		d3dmeshFile = {};
		skeletonFile = {};
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(TelltaleMeshDataStorage, d3dmeshFile, skeletonFile)
};

#endif
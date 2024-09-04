#pragma once
#ifndef MESH_BATCH_USAGE_H
#define MESH_BATCH_USAGE_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Standard C++ Library
#include <string>

//Custom
#include "BinaryHelper.h"

//|||||||||||||||||||||||||||||||||||||||| MESH BATCH USAGE ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| MESH BATCH USAGE ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| MESH BATCH USAGE ||||||||||||||||||||||||||||||||||||||||

enum eMeshBatchUsage
{
	eMeshBatchUsage_Deformable = 0x1,
	eMeshBatchUsage_DeformableSingle = 0x2,
	eMeshBatchUsage_DoubleSided = 0x4,
	eMeshBatchUsage_TriangleStrip = 0x8
};

//|||||||||||||||||||||||||||||||||||||||| BONE TYPE STRINGS ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BONE TYPE STRINGS ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BONE TYPE STRINGS ||||||||||||||||||||||||||||||||||||||||

static std::string GetMeshBatchUsageName(eMeshBatchUsage value)
{
	switch (value)
	{
	default:
		return "NULL";
	}
}

#endif
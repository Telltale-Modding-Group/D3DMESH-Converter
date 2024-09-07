#pragma once
#ifndef T3_MESH_BATCH_USAGE_H
#define T3_MESH_BATCH_USAGE_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Standard C++ Library
#include <string>

//|||||||||||||||||||||||||||||||||||||||| T3 MESH BATCH USAGE ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3 MESH BATCH USAGE ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3 MESH BATCH USAGE ||||||||||||||||||||||||||||||||||||||||
//NOTE: This is a flag style enum

enum class T3MeshBatchUsageFlag : unsigned int
{
	eMeshBatchUsage_Deformable = 1,
	eMeshBatchUsage_DeformableSingle = 2,
	eMeshBatchUsage_DoubleSided = 4,
	eMeshBatchUsage_TriangleStrip = 8
};

T3MeshBatchUsageFlag operator |(T3MeshBatchUsageFlag leftHandSide, T3MeshBatchUsageFlag rightHandSide)
{
	return static_cast<T3MeshBatchUsageFlag>(static_cast<unsigned int>(leftHandSide) | static_cast<unsigned int>(rightHandSide));
}

#endif
#pragma once
#ifndef T3_MESH_LOCAL_TRANSFORM_ENTRY_H
#define T3_MESH_LOCAL_TRANSFORM_ENTRY_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Transform.h"

//||||||||||||||||||||||||||||| T3 MESH LOCAL TRANSFORM ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH LOCAL TRANSFORM ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH LOCAL TRANSFORM ENTRY |||||||||||||||||||||||||||||

/// <summary>
/// [36 BYTES]
/// </summary>
class T3MeshLocalTransformEntry
{
public:

	Transform mTransform;

	unsigned int mCameraFacingType;

	T3MeshLocalTransformEntry()
	{
		mTransform = {};
		mCameraFacingType = 0;
	};

	T3MeshLocalTransformEntry(std::ifstream* inputFileStream)
	{
		mTransform = Transform(inputFileStream); //[32 BYTES]
		mCameraFacingType = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		mTransform.BinarySerialize(outputFileStream); //[32 BYTES]
		WriteUInt32ToBinary(outputFileStream, mCameraFacingType); //[4 BYTES]
	};
};

#endif
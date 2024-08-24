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
struct T3MeshLocalTransformEntry
{
	/// <summary>
	/// [32 BYTES]
	/// </summary>
	Transform mTransform;

	/// <summary>
	/// [4 BYTES]
	/// </summary>
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

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "";
		output += "[T3MeshLocalTransformEntry] mTransform: " + mTransform.ToString() + "\n";
		output += "[T3MeshLocalTransformEntry] mCameraFacingType: " + std::to_string(mCameraFacingType);
		return output;
	};

	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//NOTE: Yes I'm aware that C++ has functionality/operators for returning the size of the object, however...
	//For some of these structs/classes the size C++ returns/gets is wrong and doesn't match what telltale would expect.
	//So for saftey I will just manually calculate the byte size of the object here to what telltale expects.

	/// <summary>
	/// [36 BYTES]
	/// </summary>
	/// <returns></returns>
	unsigned int GetByteSize()
	{
		unsigned int totalByteSize = 0;
		totalByteSize += mTransform.GetByteSize(); //[32 BYTES] mTransform
		totalByteSize += 4; //[4 BYTES] mCameraFacingType
		return totalByteSize;
	}
};

#endif
#pragma once
#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: GLM Library
#include <glm.hpp>

//Custom
#include "../../Binary/BinarySerialization.h"
#include "../../Binary/BinaryDeserialization.h"
#include "../../Helper/JsonHelper.h"
#include "../../Helper/GLMHelper.h"
#include "../../Telltale/DataTypes/Vector3.h"

//||||||||||||||||||||||||||||| BOUNDING SPHERE |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| BOUNDING SPHERE |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| BOUNDING SPHERE |||||||||||||||||||||||||||||

/// <summary>
/// [20 BYTES] A bounding sphere in three-dimensional space.
/// </summary>
struct BoundingSphere
{
	/// <summary>
	/// [4 BYTES] The size of the current data structure (this value should be 20)
	/// <para>(CALCULATION) to calculate block size... </para>
	/// <para> Add 4, as this is the size of a uint32 that represents the block size variable itself. </para>
	/// <para> Add 12, as this is the size of a Vector3 that represents the mCenter variable. </para>
	/// <para> Add 4, as this is the size of a float32 that represents the mRadius variable. </para>
	/// </summary>
	unsigned int mBlockSize;

	/// <summary>
	/// [12 BYTES] Center point of the bounding sphere in three-dimensional space.
	/// </summary>
	Vector3 mCenter;

	/// <summary>
	/// [4 BYTES] Radius of the bounding sphere.
	/// </summary>
	float mRadius;

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

	BoundingSphere()
	{
		mBlockSize = 20;
		mCenter = {};
		mRadius = 0.0f;
	};

	BoundingSphere(std::ifstream* inputFileStream)
	{
		mBlockSize = ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mCenter = Vector3(inputFileStream); //[12 BYTES]
		mRadius = ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//NOTE: This is critical as any mishap in regards to new/removed data will crash the game.
	//So in advance we need to update all structural values (block sizes, array lengths, array capacities) to make sure everything lines up.

	void UpdateStructures() 
	{
		mBlockSize = 4; //[4 BYTES] block size uint32 itself
		mBlockSize += 12; //[12 BYTES] mCenter
		mBlockSize += 4; //[4 BYTES] mRadius;
	}

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteUInt32ToBinary(outputFileStream, mBlockSize); //[4 BYTES]
		mCenter.BinarySerialize(outputFileStream); //[12 BYTES]
		WriteFloat32ToBinary(outputFileStream, mRadius); //[4 BYTES]
	};

	//||||||||||||||||||||||||||||| CUSTOM LOGIC |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CUSTOM LOGIC |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CUSTOM LOGIC |||||||||||||||||||||||||||||

	void SetBoundingSphereBasedOnBoundingBox(BoundingBox boundingBox)
	{
		mCenter = boundingBox.CalculateCenter();
		mRadius = glm::length(Get_vec3_FromVector3(boundingBox.CalculateSize()));
	}

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "\n";
		output += "[BoundingSphere] mBlockSize: " + std::to_string(mBlockSize) + "\n";
		output += "[BoundingSphere] mCenter: " + mCenter.ToString() + "\n";
		output += "[BoundingSphere] mRadius: " + std::to_string(mRadius);
		return output;
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(BoundingSphere, mBlockSize, mCenter, mRadius)

	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//NOTE: Yes I'm aware that C++ has functionality/operators for returning the size of the object, however...
	//For some of these structs/classes the size C++ returns/gets is wrong and doesn't match what telltale would expect.
	//So for saftey I will just manually calculate the byte size of the object here to what telltale expects.

	/// <summary>
	/// [20 BYTES]
	/// </summary>
	/// <returns></returns>
	unsigned int GetByteSize()
	{
		unsigned int totalByteSize = 0;
		totalByteSize += 4; //[4 BYTES] mBlockSize
		totalByteSize += mCenter.GetByteSize(); //[12 BYTES] mCenter
		totalByteSize += 4; //[4 BYTES] mRadius
		return totalByteSize;
	}
};

#endif
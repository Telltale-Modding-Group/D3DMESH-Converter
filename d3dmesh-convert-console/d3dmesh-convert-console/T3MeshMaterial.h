#pragma once
#ifndef T3_MESH_MATERIAL_H
#define T3_MESH_MATERIAL_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Json.h"
#include "Symbol.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"

//||||||||||||||||||||||||||||| T3 MESH MATERIAL |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH MATERIAL |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH MATERIAL |||||||||||||||||||||||||||||

/// <summary>
/// [76 BYTES]
/// </summary>
struct T3MeshMaterial
{
	/// <summary>
	/// [4 BYTES]
	/// </summary>
	unsigned int mhMaterial_BlockSize;

	/// <summary>
	/// [8 BYTES]
	/// </summary>
	Symbol mhMaterial;

	/// <summary>
	/// [8 BYTES]
	/// </summary>
	Symbol mBaseMaterialName;

	/// <summary>
	/// [8 BYTES]
	/// </summary>
	Symbol mLegacyRenderTextureProperty;

	/// <summary>
	/// [24 BYTES]
	/// </summary>
	BoundingBox mBoundingBox;

	/// <summary>
	/// [20 BYTES]
	/// </summary>
	BoundingSphere mBoundingSphere;

	/// <summary>
	/// [4 BYTES]
	/// </summary>
	unsigned int mFlags;

	T3MeshMaterial()
	{
		mhMaterial_BlockSize = 0;
		mhMaterial = {};
		mBaseMaterialName = {};
		mLegacyRenderTextureProperty = {};
		mBoundingBox = {};
		mBoundingSphere = {};
		mFlags = 0;
	};

	T3MeshMaterial(std::ifstream* inputFileStream)
	{
		mhMaterial_BlockSize = ReadUInt32FromBinary(inputFileStream);
		mhMaterial = Symbol(inputFileStream);
		mBaseMaterialName = Symbol(inputFileStream);
		mLegacyRenderTextureProperty = Symbol(inputFileStream);
		mBoundingBox = BoundingBox(inputFileStream);
		mBoundingSphere = BoundingSphere(inputFileStream);
		mFlags = ReadUInt32FromBinary(inputFileStream);
	};

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		WriteUInt32ToBinary(outputFileStream, mhMaterial_BlockSize);
		mhMaterial.BinarySerialize(outputFileStream);
		mBaseMaterialName.BinarySerialize(outputFileStream);
		mLegacyRenderTextureProperty.BinarySerialize(outputFileStream);
		mBoundingBox.BinarySerialize(outputFileStream);
		mBoundingSphere.BinarySerialize(outputFileStream);
		WriteUInt32ToBinary(outputFileStream, mFlags);
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "\n";
		output += "[T3MeshMaterial] mBlockSize: " + std::to_string(mhMaterial_BlockSize) + "\n";
		output += "[T3MeshMaterial] mhMaterial: " + mhMaterial.ToString() + "\n";
		output += "[T3MeshMaterial] mBaseMaterialName: " + mBaseMaterialName.ToString() + "\n";
		output += "[T3MeshMaterial] mLegacyRenderTextureProperty: " + mLegacyRenderTextureProperty.ToString() + "\n";
		output += "[T3MeshMaterial] mBoundingBox: " + mBoundingBox.ToString() + "\n";
		output += "[T3MeshMaterial] mBoundingSphere: " + mBoundingSphere.ToString() + "\n";
		output += "[T3MeshMaterial] mFlags: " + std::to_string(mFlags);
		return output;
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(T3MeshMaterial, 
		mhMaterial_BlockSize,
		mhMaterial,
		mBaseMaterialName,
		mLegacyRenderTextureProperty,
		mBoundingBox,
		mBoundingSphere,
		mFlags)

	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BYTE SIZE |||||||||||||||||||||||||||||
	//NOTE: Yes I'm aware that C++ has functionality/operators for returning the size of the object, however...
	//For some of these structs/classes the size C++ returns/gets is wrong and doesn't match what telltale would expect.
	//So for saftey I will just manually calculate the byte size of the object here to what telltale expects.

	/// <summary>
	/// [76 BYTES]
	/// </summary>
	/// <returns></returns>
	unsigned int GetByteSize()
	{
		unsigned int totalByteSize = 0;
		totalByteSize += 4; //mhMaterial_BlockSize [4 BYTES]
		totalByteSize += mhMaterial.GetByteSize(); //mhMaterial [8 BYTES]
		totalByteSize += mBaseMaterialName.GetByteSize(); //mBaseMaterialName [8 BYTES]
		totalByteSize += mLegacyRenderTextureProperty.GetByteSize(); //mLegacyRenderTextureProperty [8 BYTES]
		totalByteSize += mBoundingBox.GetByteSize(); //mBoundingBox [24 BYTES]
		totalByteSize += mBoundingSphere.GetByteSize(); //mBoundingSphere [20 BYTES]
		totalByteSize += 4; //mFlags [4 BYTES]
		return totalByteSize;
	}
};

#endif
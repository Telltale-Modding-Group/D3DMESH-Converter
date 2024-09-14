#pragma once
#ifndef T3_MESH_MATERIAL_H
#define T3_MESH_MATERIAL_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "../../Binary/BinarySerialization.h"
#include "../../Binary/BinaryDeserialization.h"
#include "../../Helper/JsonHelper.h"
#include "../../Telltale/DataTypes/Symbol.h"
#include "../../Telltale/DataTypes/BoundingBox.h"
#include "../../Telltale/DataTypes/BoundingSphere.h"
#include "../../Telltale/DataTypes/HandlePropertySet.h"

//||||||||||||||||||||||||||||| T3 MESH MATERIAL |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH MATERIAL |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| T3 MESH MATERIAL |||||||||||||||||||||||||||||

/// <summary>
/// [76 BYTES]
/// </summary>
struct T3MeshMaterial
{
	/// <summary>
	/// [12 BYTES]
	/// </summary>
	HandlePropertySet mMaterialPropertySetHandle;

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

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

	T3MeshMaterial()
	{
		mMaterialPropertySetHandle = {};
		mBaseMaterialName = {};
		mLegacyRenderTextureProperty = {};
		mBoundingBox = {};
		mBoundingSphere = {};
		mFlags = 0;
	};

	T3MeshMaterial(std::ifstream* inputFileStream)
	{
		mMaterialPropertySetHandle = HandlePropertySet(inputFileStream);
		mBaseMaterialName = Symbol(inputFileStream);
		mLegacyRenderTextureProperty = Symbol(inputFileStream);
		mBoundingBox = BoundingBox(inputFileStream);
		mBoundingSphere = BoundingSphere(inputFileStream);
		mFlags = ReadUInt32FromBinary(inputFileStream);
	};

	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//NOTE: This is critical as any mishap in regards to new/removed data will crash the game.
	//So in advance we need to update all structural values (block sizes, array lengths, array capacities) to make sure everything lines up.

	void UpdateStructure()
	{
		mMaterialPropertySetHandle.UpdateStructure();
		mBoundingSphere.UpdateStructures();
	}

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		mMaterialPropertySetHandle.BinarySerialize(outputFileStream);
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
		output += "[T3MeshMaterial] mMaterialPropertySetHandle: " + mMaterialPropertySetHandle.ToString() + "\n";
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
		mMaterialPropertySetHandle,
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
		totalByteSize += mMaterialPropertySetHandle.GetByteSize(); //mMaterialPropertySetHandle [12 BYTES]
		totalByteSize += mBaseMaterialName.GetByteSize(); //mBaseMaterialName [8 BYTES]
		totalByteSize += mLegacyRenderTextureProperty.GetByteSize(); //mLegacyRenderTextureProperty [8 BYTES]
		totalByteSize += mBoundingBox.GetByteSize(); //mBoundingBox [24 BYTES]
		totalByteSize += mBoundingSphere.GetByteSize(); //mBoundingSphere [20 BYTES]
		totalByteSize += 4; //mFlags [4 BYTES]
		return totalByteSize;
	}
};

#endif
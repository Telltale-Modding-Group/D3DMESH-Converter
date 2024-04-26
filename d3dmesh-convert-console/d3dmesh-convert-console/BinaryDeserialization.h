//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||

//Standard C++ Library
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <stdlib.h>
#include <time.h>

//Custom
#include "Structs.h"
#include "BinaryHelper.h"

#pragma once
#ifndef BINARY_DESERIALIZATION_H
#define BINARY_DESERIALIZATION_H

//||||||||||||||||||||||||||||| BINARY DESERIALIZATION CLASS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| BINARY DESERIALIZATION CLASS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| BINARY DESERIALIZATION CLASS |||||||||||||||||||||||||||||

static class BinaryDeserialization
{
public:
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - CORE DATA TYPES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - CORE DATA TYPES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - CORE DATA TYPES ||||||||||||||||||||||||||||||||||||||||

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - UINT64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - UINT64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - UINT64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||

	/// <summary>
	/// Reads a 64 bit (8 bytes) unsigned integer [0, 18446744073709551615]  from an input file stream.
	/// </summary>
	/// <param name="inputFileStream"></param>
	/// <returns></returns>
	static unsigned long long ReadUInt64FromBinary(std::ifstream* inputFileStream)
	{
		unsigned long long uint64_value = 0;
		inputFileStream->read((char*)&uint64_value, sizeof(unsigned long long));
		return uint64_value;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - INT64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - INT64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - INT64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||

	/// <summary>
	/// Reads a 64 bit (8 bytes) integer [-9223372036854775808, 9223372036854775807] from an input file stream.
	/// </summary>
	/// <param name="inputFileStream"></param>
	/// <returns></returns>
	static long long ReadInt64FromBinary(std::ifstream* inputFileStream)
	{
		long long int64_value = 0;
		inputFileStream->read((char*)&int64_value, sizeof(long long));
		return int64_value;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - CORE DATA TYPES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - CORE DATA TYPES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - CORE DATA TYPES ||||||||||||||||||||||||||||||||||||||||

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - DOUBLE64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - DOUBLE64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - DOUBLE64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||

	/// <summary>
	/// Reads a 64 bit (8 bytes) double [1.7E +/- 308 (15 digits)] from an input file stream.
	/// </summary>
	/// <param name="inputFileStream"></param>
	/// <returns></returns>
	static double ReadDouble64FromBinary(std::ifstream* inputFileStream)
	{
		double double64_value = 0;
		inputFileStream->read((char*)&double64_value, sizeof(double));
		return double64_value;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - UINT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - UINT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - UINT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||

	/// <summary>
	/// Reads a 32 bit (4 bytes) unsigned integer [0, 4294967295] from an input file stream.
	/// </summary>
	/// <param name="inputFileStream"></param>
	/// <returns></returns>
	static unsigned int ReadUInt32FromBinary(std::ifstream* inputFileStream)
	{
		unsigned int uint32_value = 0;
		inputFileStream->read((char*)&uint32_value, sizeof(unsigned int));
		return uint32_value;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - INT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - INT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - INT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||

	/// <summary>
	/// Reads a 32 bit (4 bytes) integer [-2147483648, 2147483647] from an input file stream.
	/// </summary>
	/// <param name="inputFileStream"></param>
	/// <returns></returns>
	static int ReadInt32FromBinary(std::ifstream* inputFileStream)
	{
		int int32_value = 0;
		inputFileStream->read((char*)&int32_value, sizeof(int));
		return int32_value;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - FLOAT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - FLOAT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - FLOAT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||

	/// <summary>
	/// Reads a 32 bit (4 bytes) float [3.4E +/- 38 (7 digits)] from an input file stream.
	/// </summary>
	/// <param name="inputFileStream"></param>
	/// <returns></returns>
	static float ReadFloat32FromBinary(std::ifstream* inputFileStream)
	{
		float float32_value = 0;
		inputFileStream->read((char*)&float32_value, sizeof(float));
		return float32_value;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - UINT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - UINT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - UINT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||

	/// <summary>
	/// Reads a 16 bit (2 bytes) unsigned integer [0, 65535] from an input file stream.
	/// </summary>
	/// <param name="inputFileStream"></param>
	/// <returns></returns>
	static unsigned short ReadUInt16FromBinary(std::ifstream* inputFileStream)
	{
		unsigned short uint16_value = 0;
		inputFileStream->read((char*)&uint16_value, sizeof(unsigned short));
		return uint16_value;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - INT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - INT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - INT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||

	/// <summary>
	/// Reads a 16 bit (2 bytes) integer [-32768, 32767] from an input file stream.
	/// </summary>
	/// <param name="inputFileStream"></param>
	/// <returns></returns>
	static short ReadInt16FromBinary(std::ifstream* inputFileStream)
	{
		short int16_value = 0;
		inputFileStream->read((char*)&int16_value, sizeof(short));
		return int16_value;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - FLOAT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - FLOAT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - FLOAT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||

	/// <summary>
	/// Reads a 16 bit (2 bytes) half-float [+ or - 65504] from an input file stream.
	/// </summary>
	/// <param name="inputFileStream"></param>
	/// <returns></returns>
	static float ReadFloat16FromBinary(std::ifstream* inputFileStream)
	{
		return BinaryHelper::half_to_float(BinaryDeserialization::ReadUInt16FromBinary(inputFileStream));
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - UINT8 [1 BYTE] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - UINT8 [1 BYTE] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - UINT8 [1 BYTE] ||||||||||||||||||||||||||||||||||||||||

	/// <summary>
	/// Reads an 8 bit (1 byte) unsigned integer [0, 255] from an input file stream.
	/// </summary>
	/// <param name="inputFileStream"></param>
	/// <returns></returns>
	static unsigned char ReadUInt8FromBinary(std::ifstream* inputFileStream)
	{
		unsigned char uint8_value = 0;
		inputFileStream->read((char*)&uint8_value, sizeof(unsigned char));
		return uint8_value;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - INT8 [1 BYTE] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - INT8 [1 BYTE] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - INT8 [1 BYTE] ||||||||||||||||||||||||||||||||||||||||

	/// <summary>
	/// Reads an 8 bit (1 byte) integer [-128, 127] from an input file stream.
	/// </summary>
	/// <param name="inputFileStream"></param>
	/// <returns></returns>
	static char ReadInt8FromBinary(std::ifstream* inputFileStream)
	{
		char int8_value = 0;
		inputFileStream->read((char*)&int8_value, sizeof(char));
		return int8_value;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - BYTE BUFFER [X BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - BYTE BUFFER [X BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - BYTE BUFFER [X BYTES] ||||||||||||||||||||||||||||||||||||||||

	/// <summary>
	/// Reads a block of bytes from an input file stream.
	/// </summary>
	/// <param name="inputFileStream"></param>
	/// <param name="blockSize"></param>
	/// <returns></returns>
	static char* ReadByteBufferFromBinary(std::ifstream* inputFileStream, int blockSize)
	{
		char* byteBuffer = new char[blockSize];
		inputFileStream->read(byteBuffer, blockSize);
		return byteBuffer;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - STRING [X BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - STRING [X BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - STRING [X BYTES] ||||||||||||||||||||||||||||||||||||||||

	/// <summary>
	/// Reads a string of characters from an input file stream.
	/// </summary>
	/// <param name="inputFileStream"></param>
	/// <param name="stringLength"></param>
	/// <returns></returns>
	static std::string ReadFixedStringFromBinary(std::ifstream* inputFileStream, int stringLength)
	{
		std::string writtenString = "";

		char* stringBuffer = new char[stringLength];
		inputFileStream->read(stringBuffer, stringLength);
		writtenString.append(stringBuffer, stringLength);

		return writtenString;
	}

	/// <summary>
	/// Reads a length prefixed (32 bit integer) string of characters from an input file stream.
	/// </summary>
	/// <param name="inputFileStream"></param>
	/// <returns></returns>
	static std::string ReadLengthPrefixedStringFromBinary(std::ifstream* inputFileStream)
	{
		int stringLength = BinaryDeserialization::ReadInt32FromBinary(inputFileStream);
		return BinaryDeserialization::ReadFixedStringFromBinary(inputFileStream, stringLength);
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - STRUCT DATA TYPES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - STRUCT DATA TYPES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - STRUCT DATA TYPES ||||||||||||||||||||||||||||||||||||||||

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - SYMBOL [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - SYMBOL [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - SYMBOL [8 BYTES] ||||||||||||||||||||||||||||||||||||||||

	//[8 BYTES]
	static Symbol ReadSymbolFromBinary(std::ifstream* inputFileStream)
	{
		Symbol symbol{};
		symbol.mCrc64 = BinaryDeserialization::ReadUInt64FromBinary(inputFileStream); //[8 BYTES]
		return symbol;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - STRUCT DATA TYPES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - STRUCT DATA TYPES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - STRUCT DATA TYPES ||||||||||||||||||||||||||||||||||||||||

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE CLASS NAME [12 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE CLASS NAME [12 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE CLASS NAME [12 BYTES] ||||||||||||||||||||||||||||||||||||||||

	//[12 BYTES]
	static TelltaleClassName ReadTelltaleClassNameFromBinary(std::ifstream* inputFileStream)
	{
		TelltaleClassName telltaleClassName{};
		telltaleClassName.mTypeNameCRC = BinaryDeserialization::ReadSymbolFromBinary(inputFileStream); //[8 BYTES]
		telltaleClassName.mVersionCRC = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		return telltaleClassName;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE META HEADER VERSION 6 [X BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE META HEADER VERSION 6 [X BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE META HEADER VERSION 6 [X BYTES] ||||||||||||||||||||||||||||||||||||||||

	//[x BYTES]
	static TelltaleMetaHeaderVersion6 ReadTelltaleMetaHeaderVersion6FromBinary(std::ifstream* inputFileStream)
	{
		TelltaleMetaHeaderVersion6 metaHeader{};
		metaHeader.mMetaStreamVersion = BinaryDeserialization::ReadFixedStringFromBinary(inputFileStream, 4); //[4 BYTES]
		metaHeader.mDefaultSectionChunkSize = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		metaHeader.mDebugSectionChunkSize = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		metaHeader.mAsyncSectionChunkSize = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		metaHeader.mClassNamesLength = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]

		for (int i = 0; i < metaHeader.mClassNamesLength; i++)
		{
			metaHeader.mClassNames.push_back(BinaryDeserialization::ReadTelltaleClassNameFromBinary(inputFileStream)); //[12 BYTES]
		}

		return metaHeader;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE INTERNAL RESOURCE [X BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE INTERNAL RESOURCE [X BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE INTERNAL RESOURCE [X BYTES] ||||||||||||||||||||||||||||||||||||||||

	//[x BYTES]
	static TelltaleInternalResource ReadTelltaleInternalResourceFromBinary(std::ifstream* inputFileStream)
	{
		TelltaleInternalResource mInternalResource{};
		mInternalResource.mInternalResourceSymbol = BinaryDeserialization::ReadSymbolFromBinary(inputFileStream);
		mInternalResource.mInternalResourceType = BinaryDeserialization::ReadSymbolFromBinary(inputFileStream);
		mInternalResource.mInternalResourceBlockSize = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		mInternalResource.mInternalResourceData = BinaryDeserialization::ReadByteBufferFromBinary(inputFileStream, mInternalResource.mInternalResourceBlockSize - 4); //skip this data block
		return mInternalResource;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - VECTOR 3 [12 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - VECTOR 3 [12 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - VECTOR 3 [12 BYTES] ||||||||||||||||||||||||||||||||||||||||

	//[12 BYTES]
	static Vector3 ReadVector3FromBinary(std::ifstream* inputFileStream)
	{
		Vector3 vector3{};
		vector3.x = BinaryDeserialization::ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		vector3.y = BinaryDeserialization::ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		vector3.z = BinaryDeserialization::ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		return vector3;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - QUATERNION [16 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - QUATERNION [16 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - QUATERNION [16 BYTES] ||||||||||||||||||||||||||||||||||||||||

	//[16 BYTES]
	static Quaternion ReadQuaternionFromBinary(std::ifstream* inputFileStream)
	{
		Quaternion quaternion{};
		quaternion.x = BinaryDeserialization::ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		quaternion.y = BinaryDeserialization::ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		quaternion.z = BinaryDeserialization::ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		quaternion.w = BinaryDeserialization::ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		return quaternion;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TRANSFORM [32 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TRANSFORM [32 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TRANSFORM [32 BYTES] ||||||||||||||||||||||||||||||||||||||||

	//[32 BYTES]
	static Transform ReadTransformFromBinary(std::ifstream* inputFileStream)
	{
		Transform transform{};
		transform.mBlockSize = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //4 bytes (value should always be 32)
		transform.mRot = BinaryDeserialization::ReadQuaternionFromBinary(inputFileStream); //16 bytes
		transform.mTrans = BinaryDeserialization::ReadVector3FromBinary(inputFileStream); //12 bytes
		return transform;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - BOUNDING BOX [24 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - BOUNDING BOX [24 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - BOUNDING BOX [24 BYTES] ||||||||||||||||||||||||||||||||||||||||

	//[24 BYTES]
	static BoundingBox ReadBoundingBoxFromBinary(std::ifstream* inputFileStream)
	{
		BoundingBox boundingBox{};
		boundingBox.mMin = BinaryDeserialization::ReadVector3FromBinary(inputFileStream); //[12 BYTES]
		boundingBox.mMax = BinaryDeserialization::ReadVector3FromBinary(inputFileStream); //[12 BYTES]
		return boundingBox;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - BOUNDING SPHERE [20 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - BOUNDING SPHERE [20 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - BOUNDING SPHERE [20 BYTES] ||||||||||||||||||||||||||||||||||||||||

	//[20 BYTES]
	static BoundingSphere ReadBoundingSphereFromBinary(std::ifstream* inputFileStream)
	{
		BoundingSphere mBoundingSphere{};
		mBoundingSphere.mBlockSize = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mBoundingSphere.mCenter = BinaryDeserialization::ReadVector3FromBinary(inputFileStream); //[12 BYTES]
		mBoundingSphere.mRadius = BinaryDeserialization::ReadFloat32FromBinary(inputFileStream); //[4 BYTES]
		return mBoundingSphere;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE MESH BONE ENTRY [56 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE MESH BONE ENTRY [56 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE MESH BONE ENTRY [56 BYTES] ||||||||||||||||||||||||||||||||||||||||

	//[56 BYTES]
	static T3MeshBoneEntry ReadTelltaleMeshBoneEntryFromBinary(std::ifstream* inputFileStream)
	{
		T3MeshBoneEntry mBone{};
		mBone.mBoneName = BinaryDeserialization::ReadSymbolFromBinary(inputFileStream); //[8 BYTES]
		mBone.mBoundingBox = BinaryDeserialization::ReadBoundingBoxFromBinary(inputFileStream); //[24 BYTES]
		mBone.mBoundingSphere = BinaryDeserialization::ReadBoundingSphereFromBinary(inputFileStream); //[20 BYTES]
		mBone.mNumVerts = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		return mBone;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE MESH LOCAL TRANSFORM ENTRY [36 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE MESH LOCAL TRANSFORM ENTRY [36 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE MESH LOCAL TRANSFORM ENTRY [36 BYTES] ||||||||||||||||||||||||||||||||||||||||

	//[36 BYTES]
	static T3MeshLocalTransformEntry ReadTelltaleMeshLocalTransformEntryFromBinary(std::ifstream* inputFileStream)
	{
		T3MeshLocalTransformEntry mLocalTransform{};
		mLocalTransform.mTransform = BinaryDeserialization::ReadTransformFromBinary(inputFileStream); //32 bytes
		mLocalTransform.mCameraFacingType = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //4 bytes
		return mLocalTransform;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE MATERIAL REQUIREMENTS [40 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE MATERIAL REQUIREMENTS [40 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE MATERIAL REQUIREMENTS [40 BYTES] ||||||||||||||||||||||||||||||||||||||||

	//[40 BYTES]
	static T3MaterialRequirements ReadTelltaleMaterialRequirementsFromBinary(std::ifstream* inputFileStream)
	{
		T3MaterialRequirements mMaterialRequirements{};
		mMaterialRequirements.mMaterialRequirements_BlockSize = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //4 bytes
		mMaterialRequirements.mPasses_BlockSize = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //4 bytes
		mMaterialRequirements.mPasses = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //4 bytes
		mMaterialRequirements.mChannels_BlockSize = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //4 bytes
		mMaterialRequirements.mChannels1 = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //4 bytes
		mMaterialRequirements.mChannels2 = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //4 bytes
		mMaterialRequirements.mInputs_BlockSize = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //4 bytes
		mMaterialRequirements.mInputs1 = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //4 bytes
		mMaterialRequirements.mInputs2 = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //4 bytes
		mMaterialRequirements.mInputs3 = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //4 bytes
		return mMaterialRequirements;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE GRAPHICS PLATFORM ATTRIBUTE PARAMETERS [20 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE GRAPHICS PLATFORM ATTRIBUTE PARAMETERS [20 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE GRAPHICS PLATFORM ATTRIBUTE PARAMETERS [20 BYTES] ||||||||||||||||||||||||||||||||||||||||

	//[20 BYTES]
	static GFXPlatformAttributeParams ReadTelltaleGraphicsPlatformAttributeParametersFromBinary(std::ifstream* inputFileStream)
	{
		GFXPlatformAttributeParams mGFXPlatformAttributeParams{};
		mGFXPlatformAttributeParams.mAttribute = (GFXPlatformVertexAttribute)BinaryDeserialization::ReadInt32FromBinary(inputFileStream); //GFXPlatformVertexAttribute [4 BYTES]
		mGFXPlatformAttributeParams.mFormat = (GFXPlatformFormat)BinaryDeserialization::ReadInt32FromBinary(inputFileStream); //GFXPlatformFormat [4 BYTES]
		mGFXPlatformAttributeParams.mAttributeIndex = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mGFXPlatformAttributeParams.mBufferIndex = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mGFXPlatformAttributeParams.mBufferOffset = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		return mGFXPlatformAttributeParams;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE GRAPHICS BUFFER [20 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE GRAPHICS BUFFER [20 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - TELLTALE GRAPHICS BUFFER [20 BYTES] ||||||||||||||||||||||||||||||||||||||||

	//[20 BYTES]
	static T3GFXBuffer ReadTelltaleGFXBufferFromBinary(std::ifstream* inputFileStream)
	{
		T3GFXBuffer mBuffer{};
		mBuffer.mResourceUsage = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mBuffer.mBufferFormat = (GFXPlatformFormat)BinaryDeserialization::ReadInt32FromBinary(inputFileStream); //[4 BYTES]
		mBuffer.mBufferUsage = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mBuffer.mCount = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mBuffer.mStride = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		return mBuffer;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3 MESH BATCH [88 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3 MESH BATCH [88 BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3 MESH BATCH [88 BYTES] ||||||||||||||||||||||||||||||||||||||||

	//[88 BYTES]
	static T3MeshBatch ReadTelltaleMeshBatchFromBinary(std::ifstream* inputFileStream)
	{
		T3MeshBatch mMeshBatch{};
		mMeshBatch.mBoundingBox = BinaryDeserialization::ReadBoundingBoxFromBinary(inputFileStream); //[24 BYTES]
		mMeshBatch.mBoundingSphere = BinaryDeserialization::ReadBoundingSphereFromBinary(inputFileStream); //[20 BYTES]
		mMeshBatch.mBatchUsage_BlockSize = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mMeshBatch.mBatchUsage = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mMeshBatch.mMinVertIndex = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mMeshBatch.mMaxVertIndex = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mMeshBatch.mBaseIndex = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mMeshBatch.mStartIndex = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mMeshBatch.mNumPrimitives = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES] (mNumIndices / 3)
		mMeshBatch.mNumIndices = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mMeshBatch.mTextureIndices = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES] (4294967295)
		mMeshBatch.mMaterialIndex = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		mMeshBatch.mAdjacencyStartIndex = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream); //[4 BYTES]
		return mMeshBatch;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3 MESH LOD [x BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3 MESH LOD [x BYTES] ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3 MESH LOD [x BYTES] ||||||||||||||||||||||||||||||||||||||||

	//[x BYTES]
	static T3MeshLOD ReadTelltaleMeshLODFromBinary(std::ifstream* inputFileStream)
	{
		T3MeshLOD mLOD{};

		mLOD.mBatches0_ArrayCapacity = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		mLOD.mBatches0_ArrayLength = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);

		for (int mBatches0Index = 0; mBatches0Index < mLOD.mBatches0_ArrayLength; mBatches0Index++)
		{
			mLOD.mBatches0.push_back(BinaryDeserialization::ReadTelltaleMeshBatchFromBinary(inputFileStream));
		}

		mLOD.mBatches1_ArrayCapacity = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		mLOD.mBatches1_ArrayLength = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);

		for (int mBatches1Index = 0; mBatches1Index < mLOD.mBatches1_ArrayLength; mBatches1Index++)
		{
			mLOD.mBatches1.push_back(BinaryDeserialization::ReadTelltaleMeshBatchFromBinary(inputFileStream));
		}

		mLOD.mVertexStreams_BlockSize = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		mLOD.mVertexStreams = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		mLOD.mBoundingBox = BinaryDeserialization::ReadBoundingBoxFromBinary(inputFileStream);
		mLOD.mBoundingSphere = BinaryDeserialization::ReadBoundingSphereFromBinary(inputFileStream);
		mLOD.mFlags = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		mLOD.mVertexStateIndex = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		mLOD.mNumPrimitives = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		mLOD.mNumBatches = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		mLOD.mVertexStart = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		mLOD.mVertexCount = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		mLOD.mTextureAtlasWidth = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		mLOD.mTextureAtlasHeight = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		mLOD.mPixelSize = BinaryDeserialization::ReadFloat32FromBinary(inputFileStream);
		mLOD.mDistance = BinaryDeserialization::ReadFloat32FromBinary(inputFileStream);
		mLOD.mBones_ArrayCapacity = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		mLOD.mBones_ArrayLength = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);

		for (int mBoneIndex = 0; mBoneIndex < mLOD.mBones_ArrayLength; mBoneIndex++)
		{
			mLOD.mBones.push_back(BinaryDeserialization::ReadSymbolFromBinary(inputFileStream));
		}

		return mLOD;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER F32 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER F32 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER F32 ||||||||||||||||||||||||||||||||||||||||

	//[8 BYTES] eGFXPlatformFormat_F32x2
	static Vector2 ReadT3GFXBuffer_2x32BitFloat(std::ifstream* inputFileStream)
	{
		Vector2 vector2{};
		vector2.x = BinaryDeserialization::ReadFloat32FromBinary(inputFileStream);
		vector2.y = BinaryDeserialization::ReadFloat32FromBinary(inputFileStream);
		return vector2;
	}

	//[12 BYTES] eGFXPlatformFormat_F32x3
	static Vector3 ReadT3GFXBuffer_3x32BitFloat(std::ifstream* inputFileStream)
	{
		Vector3 vector3{};
		vector3.x = BinaryDeserialization::ReadFloat32FromBinary(inputFileStream);
		vector3.y = BinaryDeserialization::ReadFloat32FromBinary(inputFileStream);
		vector3.z = BinaryDeserialization::ReadFloat32FromBinary(inputFileStream);
		return vector3;
	}

	//[16 BYTES] eGFXPlatformFormat_F32x4
	static Vector4 ReadT3GFXBuffer_4x32BitFloat(std::ifstream* inputFileStream)
	{
		Vector4 vector4{};
		vector4.x = BinaryDeserialization::ReadFloat32FromBinary(inputFileStream);
		vector4.y = BinaryDeserialization::ReadFloat32FromBinary(inputFileStream);
		vector4.z = BinaryDeserialization::ReadFloat32FromBinary(inputFileStream);
		vector4.w = BinaryDeserialization::ReadFloat32FromBinary(inputFileStream);

		return vector4;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER U32 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER U32 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER U32 ||||||||||||||||||||||||||||||||||||||||

	//[8 BYTES] eGFXPlatformFormat_U32x2
	static UnsignedIntegerVector2 ReadT3GFXBuffer_Unsigned_2x32BitInteger(std::ifstream* inputFileStream)
	{
		UnsignedIntegerVector2 uivector2{};
		uivector2.x = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		uivector2.y = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		return uivector2;
	}

	//[12 BYTES] eGFXPlatformFormat_U32x3
	static UnsignedIntegerVector3 ReadT3GFXBuffer_Unsigned_3x32BitInteger(std::ifstream* inputFileStream)
	{
		UnsignedIntegerVector3 uivector3{};
		uivector3.x = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		uivector3.y = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		uivector3.z = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		return uivector3;
	}

	//[16 BYTES] eGFXPlatformFormat_U32x4
	static UnsignedIntegerVector4 ReadT3GFXBuffer_Unsigned_4x32BitInteger(std::ifstream* inputFileStream)
	{
		UnsignedIntegerVector4 uivector4{};
		uivector4.x = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		uivector4.y = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		uivector4.z = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		uivector4.w = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);
		return uivector4;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER S32 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER S32 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER S32 ||||||||||||||||||||||||||||||||||||||||

	//[8 BYTES] eGFXPlatformFormat_S32x2
	static IntegerVector2 ReadT3GFXBuffer_Signed_2x32BitInteger(std::ifstream* inputFileStream)
	{
		IntegerVector2 ivector2{};
		ivector2.x = BinaryDeserialization::ReadInt32FromBinary(inputFileStream);
		ivector2.y = BinaryDeserialization::ReadInt32FromBinary(inputFileStream);
		return ivector2;
	}

	//[12 BYTES] eGFXPlatformFormat_S32x3
	static IntegerVector3 ReadT3GFXBuffer_Signed_3x32BitInteger(std::ifstream* inputFileStream)
	{
		IntegerVector3 ivector3{};
		ivector3.x = BinaryDeserialization::ReadInt32FromBinary(inputFileStream);
		ivector3.y = BinaryDeserialization::ReadInt32FromBinary(inputFileStream);
		ivector3.z = BinaryDeserialization::ReadInt32FromBinary(inputFileStream);
		return ivector3;
	}

	//[16 BYTES] eGFXPlatformFormat_S32x4
	static IntegerVector4 ReadT3GFXBuffer_Signed_4x32BitInteger(std::ifstream* inputFileStream)
	{
		IntegerVector4 ivector4{};
		ivector4.x = BinaryDeserialization::ReadInt32FromBinary(inputFileStream);
		ivector4.y = BinaryDeserialization::ReadInt32FromBinary(inputFileStream);
		ivector4.z = BinaryDeserialization::ReadInt32FromBinary(inputFileStream);
		ivector4.w = BinaryDeserialization::ReadInt32FromBinary(inputFileStream);
		return ivector4;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER U16 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER U16 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER U16 ||||||||||||||||||||||||||||||||||||||||

	//[4 BYTES] eGFXPlatformFormat_U16x2
	static UnsignedIntegerVector2 ReadT3GFXBuffer_Unsigned_2x16BitInteger(std::ifstream* inputFileStream)
	{
		UnsignedIntegerVector2 uivector2{};
		uivector2.x = BinaryDeserialization::ReadUInt16FromBinary(inputFileStream);
		uivector2.y = BinaryDeserialization::ReadUInt16FromBinary(inputFileStream);
		return uivector2;
	}

	//[8 BYTES] eGFXPlatformFormat_U16x4
	static UnsignedIntegerVector4 ReadT3GFXBuffer_Unsigned_4x16BitInteger(std::ifstream* inputFileStream)
	{
		UnsignedIntegerVector4 uivector4{};
		uivector4.x = BinaryDeserialization::ReadUInt16FromBinary(inputFileStream);
		uivector4.y = BinaryDeserialization::ReadUInt16FromBinary(inputFileStream);
		uivector4.z = BinaryDeserialization::ReadUInt16FromBinary(inputFileStream);
		uivector4.z = BinaryDeserialization::ReadUInt16FromBinary(inputFileStream);
		return uivector4;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER S16 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER S16 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER S16 ||||||||||||||||||||||||||||||||||||||||

	//[4 BYTES] eGFXPlatformFormat_S16x2
	static IntegerVector2 ReadT3GFXBuffer_Signed_2x16BitInteger(std::ifstream* inputFileStream)
	{
		IntegerVector2 ivector2{};
		ivector2.x = BinaryDeserialization::ReadInt16FromBinary(inputFileStream);
		ivector2.y = BinaryDeserialization::ReadInt16FromBinary(inputFileStream);
		return ivector2;
	}

	//[8 BYTES] eGFXPlatformFormat_S16x4
	static IntegerVector4 ReadT3GFXBuffer_Signed_4x16BitInteger(std::ifstream* inputFileStream)
	{
		IntegerVector4 ivector4{};
		ivector4.x = BinaryDeserialization::ReadInt16FromBinary(inputFileStream);
		ivector4.y = BinaryDeserialization::ReadInt16FromBinary(inputFileStream);
		ivector4.z = BinaryDeserialization::ReadInt16FromBinary(inputFileStream);
		ivector4.w = BinaryDeserialization::ReadInt16FromBinary(inputFileStream);
		return ivector4;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER UN16 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER UN16 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER UN16 ||||||||||||||||||||||||||||||||||||||||
	//REFERENCES - https://gamedev.net/forums/topic/696946-normalized-unsigned-integers-vs-floats-as-vertex-data/5379766/

	//[2 BYTES] eGFXPlatformFormat_UN16
	static float ReadT3GFXBuffer_UnsignedNormalized_16BitInteger(std::ifstream* inputFileStream)
	{
		unsigned short ushort = BinaryDeserialization::ReadUInt16FromBinary(inputFileStream); //[0,65535]
		float resultFloat = ushort / (float)65535; //normalize 16 bit ushort [0,65535] to float [0, 1]
		return resultFloat;
	}

	//[4 BYTES] eGFXPlatformFormat_UN16x2
	static Vector2 ReadT3GFXBuffer_UnsignedNormalized_2x16BitInteger(std::ifstream* inputFileStream)
	{
		Vector2 vector2{};
		vector2.x = ReadT3GFXBuffer_UnsignedNormalized_16BitInteger(inputFileStream);
		vector2.y = ReadT3GFXBuffer_UnsignedNormalized_16BitInteger(inputFileStream);
		return vector2;
	}

	//[8 BYTES] eGFXPlatformFormat_UN16x4
	static Vector4 ReadT3GFXBuffer_UnsignedNormalized_4x16BitInteger(std::ifstream* inputFileStream)
	{
		Vector4 vector4{};
		vector4.x = ReadT3GFXBuffer_UnsignedNormalized_16BitInteger(inputFileStream);
		vector4.y = ReadT3GFXBuffer_UnsignedNormalized_16BitInteger(inputFileStream);
		vector4.z = ReadT3GFXBuffer_UnsignedNormalized_16BitInteger(inputFileStream);
		vector4.w = ReadT3GFXBuffer_UnsignedNormalized_16BitInteger(inputFileStream);
		return vector4;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN16 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN16 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN16 ||||||||||||||||||||||||||||||||||||||||

	//[2 BYTES] eGFXPlatformFormat_SN16
	static float ReadT3GFXBuffer_Normalized_16BitInteger(std::ifstream* inputFileStream)
	{
		short shortSigned = BinaryDeserialization::ReadInt16FromBinary(inputFileStream);
		float resultFloat = shortSigned / (float)32767; //normalize 16 bit short [-32768, 32767] to float [-1, 1]
		return resultFloat;
	}

	//[4 BYTES] eGFXPlatformFormat_SN16x2
	static Vector2 ReadT3GFXBuffer_Normalized_2x16BitInteger(std::ifstream* inputFileStream)
	{
		Vector2 vector2{};
		vector2.x = ReadT3GFXBuffer_Normalized_16BitInteger(inputFileStream);
		vector2.y = ReadT3GFXBuffer_Normalized_16BitInteger(inputFileStream);
		return vector2;
	}

	//[8 BYTES] eGFXPlatformFormat_SN16x4
	static Vector4 ReadT3GFXBuffer_Normalized_4x16BitInteger(std::ifstream* inputFileStream)
	{
		Vector4 vector4{};
		vector4.x = ReadT3GFXBuffer_Normalized_16BitInteger(inputFileStream);
		vector4.y = ReadT3GFXBuffer_Normalized_16BitInteger(inputFileStream);
		vector4.z = ReadT3GFXBuffer_Normalized_16BitInteger(inputFileStream);
		vector4.w = ReadT3GFXBuffer_Normalized_16BitInteger(inputFileStream);
		return vector4;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER U8 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER U8 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER U8 ||||||||||||||||||||||||||||||||||||||||

	//[2 BYTES] eGFXPlatformFormat_U8x2
	static UnsignedIntegerVector2 ReadT3GFXBuffer_Unsigned_2x8BitInteger(std::ifstream* inputFileStream)
	{
		UnsignedIntegerVector2 uivector2{};
		uivector2.x = BinaryDeserialization::ReadUInt8FromBinary(inputFileStream);
		uivector2.y = BinaryDeserialization::ReadUInt8FromBinary(inputFileStream);
		return uivector2;
	}

	//[4 BYTES] eGFXPlatformFormat_U8x4
	static UnsignedIntegerVector4 ReadT3GFXBuffer_Unsigned_4x8BitInteger(std::ifstream* inputFileStream)
	{
		UnsignedIntegerVector4 uivector4{};
		uivector4.x = BinaryDeserialization::ReadUInt8FromBinary(inputFileStream);
		uivector4.y = BinaryDeserialization::ReadUInt8FromBinary(inputFileStream);
		uivector4.z = BinaryDeserialization::ReadUInt8FromBinary(inputFileStream);
		uivector4.w = BinaryDeserialization::ReadUInt8FromBinary(inputFileStream);
		return uivector4;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER S8 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER S8 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER S8 ||||||||||||||||||||||||||||||||||||||||

	//[2 BYTES] eGFXPlatformFormat_S8x2
	static IntegerVector2 ReadT3GFXBuffer_Signed_2x8BitInteger(std::ifstream* inputFileStream)
	{
		IntegerVector2 ivector2{};
		ivector2.x = BinaryDeserialization::ReadInt8FromBinary(inputFileStream);
		ivector2.y = BinaryDeserialization::ReadInt8FromBinary(inputFileStream);
		return ivector2;
	}

	//[4 BYTES] eGFXPlatformFormat_S8x4
	static IntegerVector4 ReadT3GFXBuffer_Signed_4x8BitInteger(std::ifstream* inputFileStream)
	{
		IntegerVector4 ivector4{};
		ivector4.x = BinaryDeserialization::ReadInt8FromBinary(inputFileStream);
		ivector4.y = BinaryDeserialization::ReadInt8FromBinary(inputFileStream);
		ivector4.z = BinaryDeserialization::ReadInt8FromBinary(inputFileStream);
		ivector4.w = BinaryDeserialization::ReadInt8FromBinary(inputFileStream);
		return ivector4;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER UN8 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER UN8 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER UN8 ||||||||||||||||||||||||||||||||||||||||

	//[1 BYTE] eGFXPlatformFormat_UN8
	static float ReadT3GFXBuffer_UnsignedNormalized_8BitInteger(std::ifstream* inputFileStream)
	{
		unsigned char uchar = BinaryDeserialization::ReadUInt8FromBinary(inputFileStream);
		float resultFloat = uchar / (float)255; //normalize 8 bit uchar [0,255] to float [0, 1]
		return resultFloat;
	}

	//[2 BYTES] eGFXPlatformFormat_UN8x2
	static Vector2 ReadT3GFXBuffer_UnsignedNormalized_2x8BitInteger(std::ifstream* inputFileStream)
	{
		Vector2 vector2{};
		vector2.x = ReadT3GFXBuffer_UnsignedNormalized_8BitInteger(inputFileStream);
		vector2.y = ReadT3GFXBuffer_UnsignedNormalized_8BitInteger(inputFileStream);
		return vector2;
	}

	//[4 BYTES] eGFXPlatformFormat_UN8x4
	static Vector4 ReadT3GFXBuffer_UnsignedNormalized_4x8BitInteger(std::ifstream* inputFileStream)
	{
		Vector4 vector4{};
		vector4.x = ReadT3GFXBuffer_UnsignedNormalized_8BitInteger(inputFileStream);
		vector4.y = ReadT3GFXBuffer_UnsignedNormalized_8BitInteger(inputFileStream);
		vector4.z = ReadT3GFXBuffer_UnsignedNormalized_8BitInteger(inputFileStream);
		vector4.w = ReadT3GFXBuffer_UnsignedNormalized_8BitInteger(inputFileStream);
		return vector4;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN8 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN8 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN8 ||||||||||||||||||||||||||||||||||||||||

	//[1 BYTE] eGFXPlatformFormat_SN8
	static float ReadT3GFXBuffer_Normalized_8BitInteger(std::ifstream* inputFileStream)
	{
		char signedChar = BinaryDeserialization::ReadInt8FromBinary(inputFileStream);
		float resultFloat = signedChar / (float)127; //normalize 8 bit uchar [-128, 127] to float [0, 1]
		return resultFloat;
	}

	//[2 BYTES] eGFXPlatformFormat_SN8x2
	static Vector2 ReadT3GFXBuffer_Normalized_2x8BitInteger(std::ifstream* inputFileStream)
	{
		Vector2 vector2{};
		vector2.x = ReadT3GFXBuffer_Normalized_8BitInteger(inputFileStream);
		vector2.y = ReadT3GFXBuffer_Normalized_8BitInteger(inputFileStream);
		return vector2;
	}

	//[4 BYTES] eGFXPlatformFormat_SN8x4
	static Vector4 ReadT3GFXBuffer_Normalized_4x8BitInteger(std::ifstream* inputFileStream)
	{
		Vector4 vector4{};
		vector4.x = ReadT3GFXBuffer_Normalized_8BitInteger(inputFileStream);
		vector4.y = ReadT3GFXBuffer_Normalized_8BitInteger(inputFileStream);
		vector4.z = ReadT3GFXBuffer_Normalized_8BitInteger(inputFileStream);
		vector4.w = ReadT3GFXBuffer_Normalized_8BitInteger(inputFileStream);
		return vector4;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN10_SN11_SN11 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN10_SN11_SN11 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN10_SN11_SN11 ||||||||||||||||||||||||||||||||||||||||

	static Vector4 ReadT3GFXBuffer_Normalized_10BitInteger_2x11BitInteger(std::ifstream* inputFileStream)
	{
		Vector4 vector4{};

		//read the whole 4 bytes as a uint
		unsigned int uint = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);

		//---------------------BIT EXTRACTION---------------------
		//first 10 bits
		unsigned int first_10bit = BinaryHelper::BitFieldExtract(uint, 0, 10); //10 bits [0,1023]
		int firstSigned_10bit = first_10bit - 512; //convert to signed [-512,511]

		//second 11 bits
		unsigned int second_11bit = BinaryHelper::BitFieldExtract(uint, 10, 11); //11 bits [0,2047]
		int secondSigned_11bit = second_11bit - 1024; //convert to signed [-1024,1023]

		//third 11 bits
		unsigned int third_11bit = BinaryHelper::BitFieldExtract(uint, 21, 11); //11 bits [0,2047]
		int thirdSigned_11bit = third_11bit - 1024; //convert to signed [-1024,1023]

		//---------------------NORMALIZATION---------------------
		vector4.x = firstSigned_10bit / (float)511; //normalize 10 bit ushort [-512, 511] to float [-1, 1]
		vector4.y = secondSigned_11bit / (float)1023; //normalize 11 bit ushort [-1024,1023] to float [-1, 1]
		vector4.z = thirdSigned_11bit / (float)1023; //normalize 11 bit ushort [-1024,1023] to float [-1, 1]

		return vector4;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER UN10x3_UN2 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER UN10x3_UN2 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER UN10x3_UN2 ||||||||||||||||||||||||||||||||||||||||

	//[4 BYTES] eGFXPlatformFormat_UN10x3_UN2
	static Vector3 ReadT3GFXBuffer_UnsignedNormalized_3x10BitInteger_2BitInteger(std::ifstream* inputFileStream, Vector3& mPositionWScale)
	{
		Vector3 vector3{};

		//read the whole 4 bytes as a uint
		unsigned int uint = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);

		//temp variables
		unsigned int firstValue = 0;
		unsigned int secondValue = 0;
		unsigned int thirdValue = 0;
		unsigned int fourthValue = 0;

		//---------------------BIT EXTRACTION---------------------
		//first 10 bits
		firstValue = BinaryHelper::BitFieldExtract(uint, 0, 10); //10 bits [0,1023]

		//second 10 bits
		secondValue = BinaryHelper::BitFieldExtract(uint, 10, 10); //10 bits [0,1023]

		//third 10 bits
		thirdValue = BinaryHelper::BitFieldExtract(uint, 20, 10); //10 bits [0,1023]

		//fourth 2 bits
		fourthValue = BinaryHelper::BitFieldExtract(uint, 30, 2); //2 bits [0, 3]

		//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE X AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE X AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE X AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
		if (mPositionWScale.x != 0.0f)
		{
			//---------------------BIT COMBINE---------------------
			//combine last bits for x axis
			firstValue = fourthValue << 10 | firstValue;
		}
		//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE Y AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE Y AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE Y AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
		else if (mPositionWScale.y != 0.0f)
		{
			//---------------------BIT COMBINE---------------------
			//combine last bits for y axis
			secondValue = fourthValue << 10 | secondValue;
		}
		//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE Z AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE Z AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE Z AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
		else if (mPositionWScale.z != 0.0f)
		{
			//---------------------BIT COMBINE---------------------
			//combine last bits for z axis
			thirdValue = fourthValue << 10 | thirdValue;
		}

		//---------------------NORMALIZATION---------------------
		vector3.x = firstValue / (float)1023; //normalize 10 bit ushort [0, 1023] to float [0, 1]
		vector3.y = secondValue / (float)1023; //normalize 10 bit ushort [0, 1023] to float [0, 1]
		vector3.z = thirdValue / (float)1023; //normalize 10 bit ushort [0, 1023] to float [0, 1]

		return vector3;
	}

	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN10x3_SN2 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN10x3_SN2 ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN10x3_SN2 ||||||||||||||||||||||||||||||||||||||||

	//[4 BYTES] eGFXPlatformFormat_SN10x3_SN2
	static Vector3 ReadT3GFXBuffer_Normalized_3x10BitInteger_2BitInteger(std::ifstream* inputFileStream, Vector3& mPositionWScale)
	{
		Vector3 vector3{};

		//read the whole 4 bytes as a uint
		unsigned int uint = BinaryDeserialization::ReadUInt32FromBinary(inputFileStream);

		//temp variables
		unsigned int firstValue = 0;
		unsigned int secondValue = 0;
		unsigned int thirdValue = 0;
		unsigned int fourthValue = 0;

		//---------------------BIT EXTRACTION---------------------
		//first 10 bits
		firstValue = BinaryHelper::BitFieldExtract(uint, 0, 10) - 512; //extract 10 bits [0, 1023] then convert to signed integer [-512,511]

		//second 10 bits
		secondValue = BinaryHelper::BitFieldExtract(uint, 10, 10) - 512; //extract 10 bits [0, 1023] then convert to signed integer [-512,511]

		//third 10 bits
		thirdValue = BinaryHelper::BitFieldExtract(uint, 20, 10) - 512; //extract 10 bits [0, 1023] then convert to signed integer [-512,511]

		//fourth 2 bits
		fourthValue = BinaryHelper::BitFieldExtract(uint, 30, 2) - 1; //extract 2 bits [0, 3] then convert to signed integer [-1,2]

		//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE X AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE X AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE X AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
		if (mPositionWScale.x != 0.0f)
		{
			//---------------------BIT COMBINE---------------------
			//combine last bits for x axis
			firstValue = fourthValue << 10 | firstValue;
		}
		//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE Y AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE Y AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE Y AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
		else if (mPositionWScale.y != 0.0f)
		{
			//---------------------BIT COMBINE---------------------
			//combine last bits for y axis
			secondValue = fourthValue << 10 | secondValue;
		}
		//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE Z AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE Z AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE Z AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
		else if (mPositionWScale.z != 0.0f)
		{
			//---------------------BIT COMBINE---------------------
			//combine last bits for z axis
			thirdValue = fourthValue << 10 | thirdValue;
		}

		//---------------------NORMALIZATION---------------------
		vector3.x = firstValue / (float)511; //normalize 10 bit ushort [-512, 511] to float [-1, 1]
		vector3.y = secondValue / (float)511; //normalize 10 bit ushort [-512, 511] to float [-1, 1]
		vector3.z = thirdValue / (float)511; //normalize 10 bit ushort [-512, 511] to float [-1, 1]

		return vector3;
	}
};

#endif
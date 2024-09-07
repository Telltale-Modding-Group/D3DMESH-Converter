#pragma once
#ifndef SKELETON_ENTRY_H
#define SKELETON_ENTRY_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "../../BinarySerialization.h"
#include "../../BinaryDeserialization.h"
#include "../../Json.h"
#include "../../Telltale/DataTypes/ResourceGroupMembership.h"
#include "../../Telltale/DataTypes/BoneConstraints.h"
#include "../../Telltale/DataTypes/Quaternion.h"
#include "../../Telltale/DataTypes/Transform.h"

//||||||||||||||||||||||||||||| SKELETON ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| SKELETON ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| SKELETON ENTRY |||||||||||||||||||||||||||||

struct SkeletonEntry
{
	/// <summary>
	/// [8 BYTES]
	/// </summary>
	Symbol mJointName;

	/// <summary>
	/// [8 BYTES]
	/// </summary>
	Symbol mParentName;

	/// <summary>
	/// [4 BYTES]
	/// </summary>
	int mParentIndex;

	/// <summary>
	/// [8 BYTES]
	/// </summary>
	Symbol mMirrorBoneName;

	/// <summary>
	/// [4 BYTES]
	/// </summary>
	int mMirrorBoneIndex;

	/// <summary>
	/// [12 BYTES]
	/// </summary>
	Vector3 mLocalPos;

	/// <summary>
	/// [16 BYTES]
	/// </summary>
	Quaternion mLocalQuat;

	/// <summary>
	/// [32 BYTES]
	/// </summary>
	Transform mRestXform;

	/// <summary>
	/// [12 BYTES]
	/// </summary>
	Vector3 mGlobalTranslationScale;

	/// <summary>
	/// [12 BYTES]
	/// </summary>
	Vector3 mLocalTranslationScale;

	/// <summary>
	/// [12 BYTES]
	/// </summary>
	Vector3 mAnimTranslationScale;

	/// <summary>
	/// [x BYTES]
	/// </summary>
	ResourceGroupMembership mResourceGroupMembership;

	/// <summary>
	/// [60 BYTES]
	/// </summary>
	BoneConstraints mBoneConstraints;

	/// <summary>
	/// [4 BYTES]
	/// </summary>
	unsigned int mFlags;

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

	SkeletonEntry()
	{
		mJointName = {};
		mParentName = {};
		mParentIndex = 0;
		mMirrorBoneName = {};
		mMirrorBoneIndex = 0;
		mLocalPos = {};
		mLocalQuat = {};
		mRestXform = {};
		mGlobalTranslationScale = {};
		mLocalTranslationScale = {};
		mAnimTranslationScale = {};
		mResourceGroupMembership = {};
		mBoneConstraints = {};
		mFlags = 0;
	};

	SkeletonEntry(std::ifstream* inputFileStream)
	{
		mJointName = Symbol(inputFileStream);
		mParentName = Symbol(inputFileStream);
		mParentIndex = ReadInt32FromBinary(inputFileStream);
		mMirrorBoneName = Symbol(inputFileStream);
		mMirrorBoneIndex = ReadInt32FromBinary(inputFileStream);
		mLocalPos = Vector3(inputFileStream);
		mLocalQuat = Quaternion(inputFileStream);
		mRestXform = Transform(inputFileStream);
		mGlobalTranslationScale = Vector3(inputFileStream);
		mLocalTranslationScale = Vector3(inputFileStream);
		mAnimTranslationScale = Vector3(inputFileStream);
		mResourceGroupMembership = ResourceGroupMembership(inputFileStream);
		mBoneConstraints = BoneConstraints(inputFileStream);
		mFlags = ReadUInt32FromBinary(inputFileStream);
	};

	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//NOTE: This is critical as any mishap in regards to new/removed data will crash the game.
	//So in advance we need to update all structural values (block sizes, array lengths, array capacities) to make sure everything lines up.

	void UpdateStructures()
	{
		mRestXform.UpdateStructures();
		mResourceGroupMembership.UpdateStructures();
		mBoneConstraints.UpdateStructures();
	}

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		mJointName.BinarySerialize(outputFileStream);
		mParentName.BinarySerialize(outputFileStream);
		WriteInt32ToBinary(outputFileStream, mParentIndex);
		mMirrorBoneName.BinarySerialize(outputFileStream);
		WriteInt32ToBinary(outputFileStream, mMirrorBoneIndex);
		mLocalPos.BinarySerialize(outputFileStream);
		mLocalQuat.BinarySerialize(outputFileStream);
		mRestXform.BinarySerialize(outputFileStream);
		mGlobalTranslationScale.BinarySerialize(outputFileStream);
		mLocalTranslationScale.BinarySerialize(outputFileStream);
		mAnimTranslationScale.BinarySerialize(outputFileStream);
		mResourceGroupMembership.BinarySerialize(outputFileStream);
		mBoneConstraints.BinarySerialize(outputFileStream);
		WriteUInt32ToBinary(outputFileStream, mFlags);
	};

	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| TO STRING |||||||||||||||||||||||||||||

	std::string ToString() const
	{
		std::string output = "";
		output += "[SkeletonEntry] mJointName: " + mJointName.ToString() + "\n";
		output += "[SkeletonEntry] mParentName: " + mParentName.ToString() + "\n";
		output += "[SkeletonEntry] mParentIndex: " + std::to_string(mParentIndex) + "\n";
		output += "[SkeletonEntry] mMirrorBoneName: " + mMirrorBoneName.ToString() + "\n";
		output += "[SkeletonEntry] mMirrorBoneIndex: " + std::to_string(mMirrorBoneIndex) + "\n";
		output += "[SkeletonEntry] mLocalPos: " + mLocalPos.ToString() + "\n";
		output += "[SkeletonEntry] mLocalQuat: " + mLocalQuat.ToString() + "\n";
		output += "[SkeletonEntry] mRestXform: " + mRestXform.ToString() + "\n";
		output += "[SkeletonEntry] mGlobalTranslationScale: " + mGlobalTranslationScale.ToString() + "\n";
		output += "[SkeletonEntry] mLocalTranslationScale: " + mLocalTranslationScale.ToString() + "\n";
		output += "[SkeletonEntry] mAnimTranslationScale: " + mAnimTranslationScale.ToString() + "\n";
		output += "[SkeletonEntry] mResourceGroupMembership: " + mResourceGroupMembership.ToString() + "\n";
		output += "[SkeletonEntry] mBoneConstraints: " + mBoneConstraints.ToString() + "\n";
		output += "[SkeletonEntry] mFlags: " + std::to_string(mFlags);
		return output;
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(SkeletonEntry,
		mJointName,
		mParentName,
		mParentIndex,
		mMirrorBoneName,
		mMirrorBoneIndex,
		mLocalPos,
		mLocalQuat,
		mRestXform,
		mGlobalTranslationScale,
		mLocalTranslationScale,
		mAnimTranslationScale,
		mResourceGroupMembership,
		mBoneConstraints,
		mFlags)

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
		totalByteSize += mJointName.GetByteSize(); //[8 BYTES] mJointName
		totalByteSize += mParentName.GetByteSize(); //[8 BYTES] mParentName
		totalByteSize += 4; //[4 BYTES] mParentIndex
		totalByteSize += mMirrorBoneName.GetByteSize(); //[8 BYTES] mMirrorBoneName
		totalByteSize += 4; //[4 BYTES] mMirrorBoneIndex
		totalByteSize += mLocalPos.GetByteSize(); //[12 BYTES] mLocalPos
		totalByteSize += mLocalQuat.GetByteSize(); //[16 BYTES] mLocalQuat
		totalByteSize += mRestXform.GetByteSize(); //[32 BYTES] mRestXform
		totalByteSize += mGlobalTranslationScale.GetByteSize(); //[12 BYTES] mGlobalTranslationScale
		totalByteSize += mLocalTranslationScale.GetByteSize(); //[12 BYTES] mLocalTranslationScale
		totalByteSize += mAnimTranslationScale.GetByteSize(); //[12 BYTES] mAnimTranslationScale
		totalByteSize += mResourceGroupMembership.GetByteSize(); //[x BYTES] mResourceGroupMembership
		totalByteSize += mBoneConstraints.GetByteSize(); //[60 BYTES] mBoneConstraints
		totalByteSize += 4; //[4 BYTES] mFlags
		return totalByteSize;
	}
};

#endif
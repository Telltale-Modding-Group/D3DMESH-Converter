#pragma once
#ifndef SKELETON_ENTRY_H
#define SKELETON_ENTRY_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Json.h"

#include "BoneType.h"

//||||||||||||||||||||||||||||| SKELETON ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| SKELETON ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| SKELETON ENTRY |||||||||||||||||||||||||||||

class SkeletonEntry
{
public:

	SkeletonEntry()
	{

	};

	SkeletonEntry(std::ifstream* inputFileStream)
	{
		Symbol mJointName = Symbol(inputFileStream);
		Symbol mParentName = Symbol(inputFileStream);
		int mParentIndex = ReadInt32FromBinary(inputFileStream);
		Symbol mMirrorBoneName = Symbol(inputFileStream);
		int mMirrorBoneIndex = ReadInt32FromBinary(inputFileStream);

		Vector3 mLocalPos = Vector3(inputFileStream);
		Quaternion mLocalQuat = Quaternion(inputFileStream);
		Transform mRestXform = Transform(inputFileStream);

		Vector3 mGlobalTranslationScale = Vector3(inputFileStream);
		Vector3 mLocalTranslationScale = Vector3(inputFileStream);
		Vector3 mAnimTranslationScale = Vector3(inputFileStream);

		//I get lost around here...

		//mResourceGroupMembership?
		unsigned int mResourceGroupMembershipBlockSize = ReadUInt32FromBinary(inputFileStream);
		Symbol mResourceGroupMembershipSymbol = {};
		float mResourceGroupMembershipFloat = 0.0f;

		//?????????????
		if (mResourceGroupMembershipBlockSize > 0)
		{
			mResourceGroupMembershipSymbol = Symbol(inputFileStream);
			//mResourceGroupMembershipFloat = ReadFloat32FromBinary(inputFileStream);
		}

		//BoneContraints
		unsigned int mBlockSize_BoneContraints = ReadUInt32FromBinary(inputFileStream);
		BoneType mBoneType = (BoneType)ReadInt32FromBinary(inputFileStream); // 0 = eBoneType_Hinge, 1 = eBoneType_Ball
		Vector3 mHingeAxis = Vector3(inputFileStream);

		//StaticArray 3 Elements
		//TRange<float>
		float mAxisRange0_min = ReadFloat32FromBinary(inputFileStream);
		float mAxisRange0_max = ReadFloat32FromBinary(inputFileStream);

		//TRange<float>
		float mAxisRange1_min = ReadFloat32FromBinary(inputFileStream);
		float mAxisRange1_max = ReadFloat32FromBinary(inputFileStream);

		//TRange<float>
		float mAxisRange2_min = ReadFloat32FromBinary(inputFileStream);
		float mAxisRange2_max = ReadFloat32FromBinary(inputFileStream);

		unsigned int flags = ReadUInt32FromBinary(inputFileStream);

		std::cout << "[SkeletonEntry] mJointName: " << mJointName.ToString() << std::endl;
		std::cout << "[SkeletonEntry] mParentName: " << mParentName.ToString() << std::endl;
		std::cout << "[SkeletonEntry] mParentIndex: " << mParentIndex << std::endl;
		std::cout << "[SkeletonEntry] mMirrorBoneName: " << mMirrorBoneName.ToString() << std::endl;
		std::cout << "[SkeletonEntry] mMirrorBoneIndex: " << mMirrorBoneIndex << std::endl;
		std::cout << "[SkeletonEntry] mLocalPos: " << mLocalPos.ToString() << std::endl;
		std::cout << "[SkeletonEntry] mLocalQuat: " << mLocalQuat.ToString() << std::endl;
		std::cout << "[SkeletonEntry] mRestXform: " << mRestXform.ToString() << std::endl;
		std::cout << "[SkeletonEntry] mGlobalTranslationScale: " << mGlobalTranslationScale.ToString() << std::endl;
		std::cout << "[SkeletonEntry] mLocalTranslationScale: " << mLocalTranslationScale.ToString() << std::endl;
		std::cout << "[SkeletonEntry] mAnimTranslationScale: " << mAnimTranslationScale.ToString() << std::endl;
		std::cout << "[SkeletonEntry] mResourceGroupMembershipBlockSize: " << mResourceGroupMembershipBlockSize << std::endl;
		std::cout << "[SkeletonEntry] mResourceGroupMembershipSymbol: " << mResourceGroupMembershipSymbol.ToString() << std::endl;
		std::cout << "[SkeletonEntry] mResourceGroupMembershipFloat: " << mResourceGroupMembershipFloat << std::endl;
		std::cout << "[SkeletonEntry] mBlockSize_BoneContraints: " << mBlockSize_BoneContraints << std::endl;
		std::cout << "[SkeletonEntry] mBoneType: " << mBoneType << std::endl;
		std::cout << "[SkeletonEntry] mHingeAxis: " << mHingeAxis.ToString() << std::endl;
		std::cout << "[SkeletonEntry] mAxisRange0_min: " << mAxisRange0_min << std::endl;
		std::cout << "[SkeletonEntry] mAxisRange0_max: " << mAxisRange0_max << std::endl;
		std::cout << "[SkeletonEntry] mAxisRange1_min: " << mAxisRange1_min << std::endl;
		std::cout << "[SkeletonEntry] mAxisRange1_max: " << mAxisRange1_max << std::endl;
		std::cout << "[SkeletonEntry] mAxisRange2_min: " << mAxisRange2_min << std::endl;
		std::cout << "[SkeletonEntry] mAxisRange2_max: " << mAxisRange2_max << std::endl;
	};

	void BinarySerialize(std::ofstream* outputFileStream)
	{

	};
};

#endif
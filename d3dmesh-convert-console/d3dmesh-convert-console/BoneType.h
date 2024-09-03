#pragma once
#ifndef BONE_TYPE_H
#define BONE_TYPE_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Standard C++ Library
#include <string>

//|||||||||||||||||||||||||||||||||||||||| BONE TYPE ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BONE TYPE ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BONE TYPE ||||||||||||||||||||||||||||||||||||||||

/// <summary>
/// [ENUM] This defines a specific kind of mesh attribute.
/// </summary>
enum BoneType
{
	eBoneType_Hinge = 0,
	eBoneType_Ball = 1,
};

//|||||||||||||||||||||||||||||||||||||||| BONE TYPE STRINGS ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BONE TYPE STRINGS ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BONE TYPE STRINGS ||||||||||||||||||||||||||||||||||||||||

static std::string GetBoneTypeName(BoneType value)
{
	switch (value)
	{
	case BoneType::eBoneType_Hinge:
		return "eBoneType_Hinge";
	case BoneType::eBoneType_Ball:
		return "eBoneType_Ball";
	default:
		return "NULL";
	}
}

#endif
#pragma once
#ifndef GFX_PLATFORM_VERTEX_ATTRIBUTE_H
#define GFX_PLATFORM_VERTEX_ATTRIBUTE_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Standard C++ Library
#include <string>

//|||||||||||||||||||||||||||||||||||||||| GFX PLATFORM VERTEX ATTRIBUTE ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| GFX PLATFORM VERTEX ATTRIBUTE ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| GFX PLATFORM VERTEX ATTRIBUTE ||||||||||||||||||||||||||||||||||||||||
//NOTE: This is a regular int enum

/// <summary>
/// [ENUM] This defines a specific kind of mesh attribute.
/// </summary>
enum GFXPlatformVertexAttribute
{
	eGFXPlatformAttribute_Position = 0,
	eGFXPlatformAttribute_Normal = 1,
	eGFXPlatformAttribute_Tangent = 2,
	eGFXPlatformAttribute_BlendWeight = 3,
	eGFXPlatformAttribute_BlendIndex = 4,
	eGFXPlatformAttribute_Color = 5,
	eGFXPlatformAttribute_TexCoord = 6,
	eGFXPlatformAttribute_Count = 7,
	eGFXPlatformAttribute_None = 4294967295,
};

//|||||||||||||||||||||||||||||||||||||||| GFX PLATFORM VERTEX ATTRIBUTE STRINGS ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| GFX PLATFORM VERTEX ATTRIBUTE STRINGS ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| GFX PLATFORM VERTEX ATTRIBUTE STRINGS ||||||||||||||||||||||||||||||||||||||||

static std::string GetGFXPlatformVertexAttributeName(GFXPlatformVertexAttribute value)
{
	switch (value)
	{
	case GFXPlatformVertexAttribute::eGFXPlatformAttribute_Position:
		return "eGFXPlatformAttribute_Position";
	case GFXPlatformVertexAttribute::eGFXPlatformAttribute_Normal:
		return "eGFXPlatformAttribute_Normal";
	case GFXPlatformVertexAttribute::eGFXPlatformAttribute_Tangent:
		return "eGFXPlatformAttribute_Tangent";
	case GFXPlatformVertexAttribute::eGFXPlatformAttribute_BlendWeight:
		return "eGFXPlatformAttribute_BlendWeight";
	case GFXPlatformVertexAttribute::eGFXPlatformAttribute_BlendIndex:
		return "eGFXPlatformAttribute_BlendIndex";
	case GFXPlatformVertexAttribute::eGFXPlatformAttribute_Color:
		return "eGFXPlatformAttribute_Color";
	case GFXPlatformVertexAttribute::eGFXPlatformAttribute_TexCoord:
		return "eGFXPlatformAttribute_TexCoord";
	case GFXPlatformVertexAttribute::eGFXPlatformAttribute_Count:
		return "eGFXPlatformAttribute_Count";
	case GFXPlatformVertexAttribute::eGFXPlatformAttribute_None:
		return "eGFXPlatformAttribute_None";
	default:
		return "NULL";
	}
}

#endif
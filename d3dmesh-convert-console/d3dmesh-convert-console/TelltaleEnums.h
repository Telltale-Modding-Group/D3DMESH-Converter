//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||

//Standard C++ Library
#include <string>

#pragma once
#ifndef TELLTALE_ENUMS_H
#define TELLTALE_ENUMS_H

//|||||||||||||||||||||||||||||||||||||||| ENUMS ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| ENUMS ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| ENUMS ||||||||||||||||||||||||||||||||||||||||

/// <summary>
/// [ENUM] This defines the binary layout format of an attribute.
/// </summary>
enum GFXPlatformFormat
{
	eGFXPlatformFormat_None = 0,
	eGFXPlatformFormat_F32 = 1,
	eGFXPlatformFormat_F32x2 = 2,
	eGFXPlatformFormat_F32x3 = 3,
	eGFXPlatformFormat_F32x4 = 4,
	eGFXPlatformFormat_F16x2 = 5,
	eGFXPlatformFormat_F16x4 = 6,
	eGFXPlatformFormat_S32 = 7,
	eGFXPlatformFormat_U32 = 8,
	eGFXPlatformFormat_S32x2 = 9,
	eGFXPlatformFormat_U32x2 = 10,
	eGFXPlatformFormat_S32x3 = 11,
	eGFXPlatformFormat_U32x3 = 12,
	eGFXPlatformFormat_S32x4 = 13,
	eGFXPlatformFormat_U32x4 = 14,
	eGFXPlatformFormat_S16 = 15,
	eGFXPlatformFormat_U16 = 16,
	eGFXPlatformFormat_S16x2 = 17,
	eGFXPlatformFormat_U16x2 = 18,
	eGFXPlatformFormat_S16x4 = 19,
	eGFXPlatformFormat_U16x4 = 20,
	eGFXPlatformFormat_SN16 = 21,
	eGFXPlatformFormat_UN16 = 22,
	eGFXPlatformFormat_SN16x2 = 23,
	eGFXPlatformFormat_UN16x2 = 24,
	eGFXPlatformFormat_SN16x4 = 25,
	eGFXPlatformFormat_UN16x4 = 26,
	eGFXPlatformFormat_S8 = 27,
	eGFXPlatformFormat_U8 = 28,
	eGFXPlatformFormat_S8x2 = 29,
	eGFXPlatformFormat_U8x2 = 30,
	eGFXPlatformFormat_S8x4 = 31,
	eGFXPlatformFormat_U8x4 = 32,
	eGFXPlatformFormat_SN8 = 33,
	eGFXPlatformFormat_UN8 = 34,
	eGFXPlatformFormat_SN8x2 = 35,
	eGFXPlatformFormat_UN8x2 = 36,
	eGFXPlatformFormat_SN8x4 = 37,
	eGFXPlatformFormat_UN8x4 = 38,
	eGFXPlatformFormat_SN10_SN11_SN11 = 39,
	eGFXPlatformFormat_SN10x3_SN2 = 40,
	eGFXPlatformFormat_UN10x3_UN2 = 41,
	eGFXPlatformFormat_D3DCOLOR = 42,
	eGFXPlatformFormat_Count = 43,
};

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

//|||||||||||||||||||||||||||||||||||||||| ENUM STRINGS ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| ENUM STRINGS ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| ENUM STRINGS ||||||||||||||||||||||||||||||||||||||||

static std::string GetGFXPlatformFormatName(GFXPlatformFormat value)
{
	switch (value)
	{
	case GFXPlatformFormat::eGFXPlatformFormat_None:
		return "eGFXPlatformFormat_None";
	case GFXPlatformFormat::eGFXPlatformFormat_F32:
		return "eGFXPlatformFormat_F32";
	case GFXPlatformFormat::eGFXPlatformFormat_F32x2:
		return "eGFXPlatformFormat_F32x2";
	case GFXPlatformFormat::eGFXPlatformFormat_F32x3:
		return "eGFXPlatformFormat_F32x3";
	case GFXPlatformFormat::eGFXPlatformFormat_F32x4:
		return "eGFXPlatformFormat_F32x4";
	case GFXPlatformFormat::eGFXPlatformFormat_F16x2:
		return "eGFXPlatformFormat_F16x2";
	case GFXPlatformFormat::eGFXPlatformFormat_F16x4:
		return "eGFXPlatformFormat_F16x4";
	case GFXPlatformFormat::eGFXPlatformFormat_S32:
		return "eGFXPlatformFormat_S32";
	case GFXPlatformFormat::eGFXPlatformFormat_U32:
		return "eGFXPlatformFormat_U32";
	case GFXPlatformFormat::eGFXPlatformFormat_S32x2:
		return "eGFXPlatformFormat_S32x2";
	case GFXPlatformFormat::eGFXPlatformFormat_U32x2:
		return "eGFXPlatformFormat_U32x2";
	case GFXPlatformFormat::eGFXPlatformFormat_S32x3:
		return "eGFXPlatformFormat_S32x3";
	case GFXPlatformFormat::eGFXPlatformFormat_U32x3:
		return "eGFXPlatformFormat_U32x3";
	case GFXPlatformFormat::eGFXPlatformFormat_S32x4:
		return "eGFXPlatformFormat_S32x4";
	case GFXPlatformFormat::eGFXPlatformFormat_U32x4:
		return "eGFXPlatformFormat_U32x4";
	case GFXPlatformFormat::eGFXPlatformFormat_S16:
		return "eGFXPlatformFormat_S16";
	case GFXPlatformFormat::eGFXPlatformFormat_U16:
		return "eGFXPlatformFormat_U16";
	case GFXPlatformFormat::eGFXPlatformFormat_S16x2:
		return "eGFXPlatformFormat_S16x2";
	case GFXPlatformFormat::eGFXPlatformFormat_U16x2:
		return "eGFXPlatformFormat_U16x2";
	case GFXPlatformFormat::eGFXPlatformFormat_S16x4:
		return "eGFXPlatformFormat_S16x4";
	case GFXPlatformFormat::eGFXPlatformFormat_U16x4:
		return "eGFXPlatformFormat_U16x4";
	case GFXPlatformFormat::eGFXPlatformFormat_SN16:
		return "eGFXPlatformFormat_SN16";
	case GFXPlatformFormat::eGFXPlatformFormat_UN16:
		return "eGFXPlatformFormat_UN16";
	case GFXPlatformFormat::eGFXPlatformFormat_SN16x2:
		return "eGFXPlatformFormat_SN16x2";
	case GFXPlatformFormat::eGFXPlatformFormat_UN16x2:
		return "eGFXPlatformFormat_UN16x2";
	case GFXPlatformFormat::eGFXPlatformFormat_SN16x4:
		return "eGFXPlatformFormat_SN16x4";
	case GFXPlatformFormat::eGFXPlatformFormat_UN16x4:
		return "eGFXPlatformFormat_UN16x4";
	case GFXPlatformFormat::eGFXPlatformFormat_S8:
		return "eGFXPlatformFormat_S8";
	case GFXPlatformFormat::eGFXPlatformFormat_U8:
		return "eGFXPlatformFormat_U8";
	case GFXPlatformFormat::eGFXPlatformFormat_S8x2:
		return "eGFXPlatformFormat_S8x2";
	case GFXPlatformFormat::eGFXPlatformFormat_U8x2:
		return "eGFXPlatformFormat_U8x2";
	case GFXPlatformFormat::eGFXPlatformFormat_S8x4:
		return "eGFXPlatformFormat_S8x4";
	case GFXPlatformFormat::eGFXPlatformFormat_U8x4:
		return "eGFXPlatformFormat_U8x4";
	case GFXPlatformFormat::eGFXPlatformFormat_SN8:
		return "eGFXPlatformFormat_SN8";
	case GFXPlatformFormat::eGFXPlatformFormat_UN8:
		return "eGFXPlatformFormat_UN8";
	case GFXPlatformFormat::eGFXPlatformFormat_SN8x2:
		return "eGFXPlatformFormat_SN8x2";
	case GFXPlatformFormat::eGFXPlatformFormat_UN8x2:
		return "eGFXPlatformFormat_UN8x2";
	case GFXPlatformFormat::eGFXPlatformFormat_SN8x4:
		return "eGFXPlatformFormat_SN8x4";
	case GFXPlatformFormat::eGFXPlatformFormat_UN8x4:
		return "eGFXPlatformFormat_UN8x4";
	case GFXPlatformFormat::eGFXPlatformFormat_SN10_SN11_SN11:
		return "eGFXPlatformFormat_SN10_SN11_SN11";
	case GFXPlatformFormat::eGFXPlatformFormat_SN10x3_SN2:
		return "eGFXPlatformFormat_SN10x3_SN2";
	case GFXPlatformFormat::eGFXPlatformFormat_UN10x3_UN2:
		return "eGFXPlatformFormat_UN10x3_UN2";
	case GFXPlatformFormat::eGFXPlatformFormat_D3DCOLOR:
		return "eGFXPlatformFormat_D3DCOLOR";
	case GFXPlatformFormat::eGFXPlatformFormat_Count:
		return "eGFXPlatformFormat_Count";
	default:
		return "NULL";
	}
}

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

//|||||||||||||||||||||||||||||||||||||||| ENUM UTILITY ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| ENUM UTILITY ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| ENUM UTILITY ||||||||||||||||||||||||||||||||||||||||

static unsigned int GetGFXPlatformFormatStrideLength(GFXPlatformFormat value)
{
	switch (value)
	{
	case GFXPlatformFormat::eGFXPlatformFormat_None:
		return 4;
	case GFXPlatformFormat::eGFXPlatformFormat_F32:
		return 4;
	case GFXPlatformFormat::eGFXPlatformFormat_F32x2:
		return 8;
	case GFXPlatformFormat::eGFXPlatformFormat_F32x3:
		return 12;
	case GFXPlatformFormat::eGFXPlatformFormat_F32x4:
		return 16;
	case GFXPlatformFormat::eGFXPlatformFormat_F16x2:
		return 4;
	case GFXPlatformFormat::eGFXPlatformFormat_F16x4:
		return 8;
	case GFXPlatformFormat::eGFXPlatformFormat_S32:
		return 4;
	case GFXPlatformFormat::eGFXPlatformFormat_U32:
		return 4;
	case GFXPlatformFormat::eGFXPlatformFormat_S32x2:
		return 8;
	case GFXPlatformFormat::eGFXPlatformFormat_U32x2:
		return 8;
	case GFXPlatformFormat::eGFXPlatformFormat_S32x3:
		return 12;
	case GFXPlatformFormat::eGFXPlatformFormat_U32x3:
		return 12;
	case GFXPlatformFormat::eGFXPlatformFormat_S32x4:
		return 16;
	case GFXPlatformFormat::eGFXPlatformFormat_U32x4:
		return 16;
	case GFXPlatformFormat::eGFXPlatformFormat_S16:
		return 2;
	case GFXPlatformFormat::eGFXPlatformFormat_U16:
		return 2;
	case GFXPlatformFormat::eGFXPlatformFormat_S16x2:
		return 4;
	case GFXPlatformFormat::eGFXPlatformFormat_U16x2:
		return 4;
	case GFXPlatformFormat::eGFXPlatformFormat_S16x4:
		return 8;
	case GFXPlatformFormat::eGFXPlatformFormat_U16x4:
		return 8;
	case GFXPlatformFormat::eGFXPlatformFormat_SN16:
		return 2;
	case GFXPlatformFormat::eGFXPlatformFormat_UN16:
		return 2;
	case GFXPlatformFormat::eGFXPlatformFormat_SN16x2:
		return 4;
	case GFXPlatformFormat::eGFXPlatformFormat_UN16x2:
		return 4;
	case GFXPlatformFormat::eGFXPlatformFormat_SN16x4:
		return 8;
	case GFXPlatformFormat::eGFXPlatformFormat_UN16x4:
		return 8;
	case GFXPlatformFormat::eGFXPlatformFormat_S8:
		return 1;
	case GFXPlatformFormat::eGFXPlatformFormat_U8:
		return 1;
	case GFXPlatformFormat::eGFXPlatformFormat_S8x2:
		return 2;
	case GFXPlatformFormat::eGFXPlatformFormat_U8x2:
		return 2;
	case GFXPlatformFormat::eGFXPlatformFormat_S8x4:
		return 4;
	case GFXPlatformFormat::eGFXPlatformFormat_U8x4:
		return 4;
	case GFXPlatformFormat::eGFXPlatformFormat_SN8:
		return 1;
	case GFXPlatformFormat::eGFXPlatformFormat_UN8:
		return 1;
	case GFXPlatformFormat::eGFXPlatformFormat_SN8x2:
		return 2;
	case GFXPlatformFormat::eGFXPlatformFormat_UN8x2:
		return 2;
	case GFXPlatformFormat::eGFXPlatformFormat_SN8x4:
		return 4;
	case GFXPlatformFormat::eGFXPlatformFormat_UN8x4:
		return 4;
	case GFXPlatformFormat::eGFXPlatformFormat_SN10_SN11_SN11:
		return 4;
	case GFXPlatformFormat::eGFXPlatformFormat_SN10x3_SN2:
		return 4;
	case GFXPlatformFormat::eGFXPlatformFormat_UN10x3_UN2:
		return 4;
	case GFXPlatformFormat::eGFXPlatformFormat_D3DCOLOR:
		return 4;
	case GFXPlatformFormat::eGFXPlatformFormat_Count:
		return 4;
	default:
		return 4;
	}
}

#endif
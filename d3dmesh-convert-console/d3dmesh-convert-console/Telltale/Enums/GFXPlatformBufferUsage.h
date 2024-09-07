#pragma once
#ifndef GFX_PLATFORM_BUFFER_USAGE_H
#define GFX_PLATFORM_BUFFER_USAGE_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Standard C++ Library
#include <string>

//|||||||||||||||||||||||||||||||||||||||| GFX PLATFORM BUFFER USAGE ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| GFX PLATFORM BUFFER USAGE ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| GFX PLATFORM BUFFER USAGE ||||||||||||||||||||||||||||||||||||||||
//NOTE: This is a flag style enum

enum class GFXPlatformBufferUsage : unsigned int
{
	eGFXPlatformBuffer_None = 0,
	eGFXPlatformBuffer_Vertex = 1,
	eGFXPlatformBuffer_Index = 2,
	eGFXPlatformBuffer_Uniform = 4,
	eGFXPlatformBuffer_ShaderRead = 8,
	eGFXPlatformBuffer_ShaderWrite = 0x10,
	eGFXPlatformBuffer_ShaderReadWrite = 0x18,
	eGFXPlatformBuffer_ShaderRawAccess = 0x20,
	eGFXPlatformBuffer_ShaderReadRaw = 0x28,
	eGFXPlatformBuffer_ShaderWriteRaw = 0x30,
	eGFXPlatformBuffer_ShaderReadWriteRaw = 0x38,
	eGFXPlatformBuffer_DrawIndirectArgs = 0x40,
	eGFXPlatformBuffer_SingleValue = 0x80,
};

GFXPlatformBufferUsage operator |(GFXPlatformBufferUsage leftHandSide, GFXPlatformBufferUsage rightHandSide)
{
	return static_cast<GFXPlatformBufferUsage>(static_cast<unsigned int>(leftHandSide) | static_cast<unsigned int>(rightHandSide));
}

#endif
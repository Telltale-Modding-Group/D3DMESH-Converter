#pragma once
#ifndef BINARY_HELPER_H
#define BINARY_HELPER_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Standard C++ Library
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <bitset>

//|||||||||||||||||||||||||||||||||||||||| BIT DISPLAY ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BIT DISPLAY ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BIT DISPLAY ||||||||||||||||||||||||||||||||||||||||

static void PrintBinaryStringOfUInt32(unsigned int value)
{
	std::bitset<32> valueBitSet(value);
	std::cout << valueBitSet << std::endl;
}

//|||||||||||||||||||||||||||||||||||||||| BIT OPERATION HELPERS ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BIT OPERATION HELPERS ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BIT OPERATION HELPERS ||||||||||||||||||||||||||||||||||||||||
// REFERENCE - https://github.com/Unity-Technologies/Graphics/blob/master/Packages/com.unity.render-pipelines.core/ShaderLibrary/Common.hlsl

static unsigned int GetMaskOfBitsToKeep(unsigned int bitOffsetStart, unsigned int bitsToKeep)
{
	unsigned int mask = (1ULL << bitsToKeep) - 1;
	return mask << bitOffsetStart;
}

static unsigned int KeepBitsOfValue(unsigned int sourceData, unsigned int bitsToKeepOffsetStart, unsigned int amountOfBitsToKeep)
{
	return sourceData & GetMaskOfBitsToKeep(bitsToKeepOffsetStart, amountOfBitsToKeep);
}

static unsigned int ExtractBits(unsigned int sourceData, unsigned int bitOffsetStart, unsigned int bitsToExtract)
{
	unsigned int bitmask = (1u << bitsToExtract) - 1u;
	return (sourceData >> bitOffsetStart) & bitmask;
}

static bool IsBitAtOffsetSet(unsigned int sourceData, unsigned int bitOffsetLocation)
{
	return ExtractBits(sourceData, bitOffsetLocation, 1u) != 0;
}

static unsigned int SetBitAtOffset(unsigned int sourceData, unsigned int bitOffsetLocation)
{
	return sourceData |= 1u << bitOffsetLocation;
}

static unsigned int ClearBitAtOffset(unsigned int sourceData, unsigned int bitOffsetLocation)
{
	return sourceData &= ~(1u << bitOffsetLocation);
}

static unsigned int CombineBits(unsigned int sourceData, unsigned int sourceDataBitSize, unsigned int newData, unsigned int newDataBitSize)
{
	unsigned int bitsA = KeepBitsOfValue(sourceData, 0, sourceDataBitSize);
	unsigned int bitsB = KeepBitsOfValue(newData, 0, newDataBitSize);
	return bitsA | bitsB << sourceDataBitSize;
}

//|||||||||||||||||||||||||||||||||||||||| HALF FLOATS CONVERSION ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| HALF FLOATS CONVERSION ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| HALF FLOATS CONVERSION ||||||||||||||||||||||||||||||||||||||||s
// REFERENCE - https://stackoverflow.com/questions/1659440/32-bit-to-16-bit-floating-point-conversion/60047308#60047308

static unsigned int AsUInt(const float x)
{
	return *(unsigned int*)&x;
}

static float AsFloat(const unsigned int  x)
{
	return *(float*)&x;
}

// IEEE-754 16-bit floating-point format (without infinity): 1-5-10, exp-15, +-131008.0, +-6.1035156E-5, +-5.9604645E-8, 3.311 digits
static float HalfToFloat(const unsigned short x)
{
	const unsigned int e = (x & 0x7C00) >> 10; // exponent
	const unsigned int m = (x & 0x03FF) << 13; // mantissa
	const unsigned int v = AsUInt((float)m) >> 23; // evil log2 bit hack to count leading zeros in denormalized format
	return AsFloat((x & 0x8000) << 16 | (e != 0) * ((e + 112) << 23 | m) | ((e == 0) & (m != 0)) * ((v - 37) << 23 | ((m << (150 - v)) & 0x007FE000))); // sign : normalized : denormalized
}

// IEEE-754 16-bit floating-point format (without infinity): 1-5-10, exp-15, +-131008.0, +-6.1035156E-5, +-5.9604645E-8, 3.311 digits
static unsigned short FloatToHalf(const float x)
{
	const unsigned int b = AsUInt(x) + 0x00001000; // round-to-nearest-even: add last bit after truncated mantissa
	const unsigned int e = (b & 0x7F800000) >> 23; // exponent
	const unsigned int m = b & 0x007FFFFF; // mantissa; in line below: 0x007FF000 = 0x00800000-0x00001000 = decimal indicator flag - initial rounding
	return (b & 0x80000000) >> 16 | (e > 112) * ((((e - 112) << 10) & 0x7C00) | m >> 13) | ((e < 113) & (e > 101)) * ((((0x007FF000 + m) >> (125 - e)) + 1) >> 1) | (e > 143) * 0x7FFF; // sign : normalized : denormalized : saturate
}

#endif
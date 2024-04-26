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

#pragma once
#ifndef BINARY_HELPER_H
#define BINARY_HELPER_H

//||||||||||||||||||||||||||||| BINARY HELPER CLASS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| BINARY HELPER CLASS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| BINARY HELPER CLASS |||||||||||||||||||||||||||||

static class BinaryHelper
{
public:
	//|||||||||||||||||||||||||||||||||||||||| BIT OPERATION HELPERS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BIT OPERATION HELPERS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| BIT OPERATION HELPERS ||||||||||||||||||||||||||||||||||||||||
	// REFERENCE - https://github.com/Unity-Technologies/Graphics/blob/master/Packages/com.unity.render-pipelines.core/ShaderLibrary/Common.hlsl

	// Unsigned integer bit field extraction.
	static unsigned int BitFieldExtract(unsigned int data, unsigned int offset, unsigned int numBits)
	{
		unsigned int mask = (1u << numBits) - 1u;
		return (data >> offset) & mask;
	}

	// Inserts the bits indicated by 'mask' from 'src' into 'dst'.
	//static unsigned int BitFieldInsert(unsigned int mask, unsigned int src, unsigned int dst)
	//{
		//return (src & mask) | (dst & ~mask);
	//}

	// Inserts the bits indicated by 'mask' from 'src' into 'dst'.
	static unsigned int BitFieldInsert(unsigned int numBits, unsigned int src, unsigned int dst)
	{
		unsigned int mask = (1u << numBits) - 1u;
		return (src & mask) | (dst & ~mask);
	}

	//|||||||||||||||||||||||||||||||||||||||| HALF FLOATS CONVERSION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| HALF FLOATS CONVERSION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| HALF FLOATS CONVERSION ||||||||||||||||||||||||||||||||||||||||s
	// REFERENCE - https://stackoverflow.com/questions/1659440/32-bit-to-16-bit-floating-point-conversion/60047308#60047308

	// IEEE-754 16-bit floating-point format (without infinity): 1-5-10, exp-15, +-131008.0, +-6.1035156E-5, +-5.9604645E-8, 3.311 digits
	static float half_to_float(const unsigned short x)
	{
		const unsigned int e = (x & 0x7C00) >> 10; // exponent
		const unsigned int m = (x & 0x03FF) << 13; // mantissa
		const unsigned int v = as_uint((float)m) >> 23; // evil log2 bit hack to count leading zeros in denormalized format
		return as_float((x & 0x8000) << 16 | (e != 0) * ((e + 112) << 23 | m) | ((e == 0) & (m != 0)) * ((v - 37) << 23 | ((m << (150 - v)) & 0x007FE000))); // sign : normalized : denormalized
	}

	// IEEE-754 16-bit floating-point format (without infinity): 1-5-10, exp-15, +-131008.0, +-6.1035156E-5, +-5.9604645E-8, 3.311 digits
	static unsigned short float_to_half(const float x)
	{
		const unsigned int b = as_uint(x) + 0x00001000; // round-to-nearest-even: add last bit after truncated mantissa
		const unsigned int e = (b & 0x7F800000) >> 23; // exponent
		const unsigned int m = b & 0x007FFFFF; // mantissa; in line below: 0x007FF000 = 0x00800000-0x00001000 = decimal indicator flag - initial rounding
		return (b & 0x80000000) >> 16 | (e > 112) * ((((e - 112) << 10) & 0x7C00) | m >> 13) | ((e < 113) & (e > 101)) * ((((0x007FF000 + m) >> (125 - e)) + 1) >> 1) | (e > 143) * 0x7FFF; // sign : normalized : denormalized : saturate
	}

private:
	static unsigned int as_uint(const float x)
	{
		return *(unsigned int*)&x;
	}

	static float as_float(const unsigned int  x)
	{
		return *(float*)&x;
	}
};

#endif
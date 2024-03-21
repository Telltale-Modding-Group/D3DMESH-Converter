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
	static unsigned int BitFieldExtract(unsigned int data, unsigned int offset, unsigned int numBits);

	// Inserts the bits indicated by 'mask' from 'src' into 'dst'.
	//unsigned int BitFieldInsert(unsigned int mask, unsigned int src, unsigned int dst);

	// Inserts the bits indicated by 'mask' from 'src' into 'dst'.
	static unsigned int BitFieldInsert(unsigned int numBits, unsigned int src, unsigned int dst);

	//|||||||||||||||||||||||||||||||||||||||| HALF FLOATS CONVERSION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| HALF FLOATS CONVERSION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| HALF FLOATS CONVERSION ||||||||||||||||||||||||||||||||||||||||s
	// REFERENCE - https://stackoverflow.com/questions/1659440/32-bit-to-16-bit-floating-point-conversion/60047308#60047308

	static unsigned int as_uint(const float x);
	static float as_float(const unsigned int  x);

	// IEEE-754 16-bit floating-point format (without infinity): 1-5-10, exp-15, +-131008.0, +-6.1035156E-5, +-5.9604645E-8, 3.311 digits
	static float half_to_float(const unsigned short x);

	// IEEE-754 16-bit floating-point format (without infinity): 1-5-10, exp-15, +-131008.0, +-6.1035156E-5, +-5.9604645E-8, 3.311 digits
	static unsigned short float_to_half(const float x);
};

#endif
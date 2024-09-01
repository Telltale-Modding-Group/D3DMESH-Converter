//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

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
#include "BinaryHelper.h"

#pragma once
#ifndef BINARY_DESERIALIZATION_H
#define BINARY_DESERIALIZATION_H

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
	return HalfToFloat(ReadUInt16FromBinary(inputFileStream));
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

static std::vector<char> ReadByteVectorBufferFromBinary(std::ifstream* inputFileStream, int blockSize)
{
	std::vector<char> vectorData;

	for (int i = 0; i < blockSize; i++)
		vectorData.push_back(ReadInt8FromBinary(inputFileStream));

	return vectorData;
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
	int stringLength = ReadInt32FromBinary(inputFileStream);
	return ReadFixedStringFromBinary(inputFileStream, stringLength);
}

#endif
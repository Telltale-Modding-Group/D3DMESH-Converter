

#pragma once
#ifndef BINARY_SERIALIZATION_H
#define BINARY_SERIALIZATION_H

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

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||

static void WriteUInt64ToBinary(std::ofstream* outputFileStream, unsigned long long value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||

static void WriteInt64ToBinary(std::ofstream* outputFileStream, long long value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - DOUBLE64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - DOUBLE64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - DOUBLE64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||

static void WriteDouble64ToBinary(std::ofstream* outputFileStream, double value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||

static void WriteUInt32ToBinary(std::ofstream* outputFileStream, unsigned int value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||

static void WriteInt32ToBinary(std::ofstream* outputFileStream, int value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - FLOAT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - FLOAT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - FLOAT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||

static void WriteFloat32ToBinary(std::ofstream* outputFileStream, float value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||

static void WriteUInt16ToBinary(std::ofstream* outputFileStream, unsigned short value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||

static void WriteInt16ToBinary(std::ofstream* outputFileStream, short value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - FLOAT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - FLOAT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - FLOAT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||

static void WriteFloat16ToBinary(std::ofstream* outputFileStream, float value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT8 [1 BYTE] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT8 [1 BYTE] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT8 [1 BYTE] ||||||||||||||||||||||||||||||||||||||||

static void WriteUInt8ToBinary(std::ofstream* outputFileStream, unsigned char value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT8 [1 BYTE] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT8 [1 BYTE] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT8 [1 BYTE] ||||||||||||||||||||||||||||||||||||||||

static void WriteInt8ToBinary(std::ofstream* outputFileStream, char value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - BYTE BUFFER [X BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - BYTE BUFFER [X BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - BYTE BUFFER [X BYTES] ||||||||||||||||||||||||||||||||||||||||

static void WriteByteBufferToBinary(std::ofstream* outputFileStream, int dataSize, char* data)
{
	outputFileStream->write(data, dataSize);
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - STRING [X BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - STRING [X BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - STRING [X BYTES] ||||||||||||||||||||||||||||||||||||||||

static void WriteFixedStringToBinary(std::ofstream* outputFileStream, std::string value)
{
	outputFileStream->write(value.c_str(), value.length());
}

static void WriteLengthPrefixedStringToBinary(std::ofstream* outputFileStream, std::string value)
{
	WriteInt32ToBinary(outputFileStream, value.length());
	WriteFixedStringToBinary(outputFileStream, value);
}

#endif
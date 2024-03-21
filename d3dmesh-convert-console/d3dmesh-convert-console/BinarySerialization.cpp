#include "BinarySerialization.h"

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||

void BinarySerialization::WriteUInt64ToBinary(std::ofstream* outputFileStream, unsigned long long value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||

void BinarySerialization::WriteInt64ToBinary(std::ofstream* outputFileStream, long long value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - DOUBLE64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - DOUBLE64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - DOUBLE64 [8 BYTES] ||||||||||||||||||||||||||||||||||||||||

void BinarySerialization::WriteDouble64ToBinary(std::ofstream* outputFileStream, double value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||

void BinarySerialization::WriteUInt32ToBinary(std::ofstream* outputFileStream, unsigned int value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||

void BinarySerialization::WriteInt32ToBinary(std::ofstream* outputFileStream, int value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - FLOAT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - FLOAT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - FLOAT32 [4 BYTES] ||||||||||||||||||||||||||||||||||||||||

void BinarySerialization::WriteFloat32ToBinary(std::ofstream* outputFileStream, float value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||

void BinarySerialization::WriteUInt16ToBinary(std::ofstream* outputFileStream, unsigned short value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||

void BinarySerialization::WriteInt16ToBinary(std::ofstream* outputFileStream, short value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - FLOAT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - FLOAT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - FLOAT16 [2 BYTES] ||||||||||||||||||||||||||||||||||||||||

void BinarySerialization::WriteFloat16ToBinary(std::ofstream* outputFileStream, float value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT8 [1 BYTE] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT8 [1 BYTE] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - UINT8 [1 BYTE] ||||||||||||||||||||||||||||||||||||||||

void BinarySerialization::WriteUInt8ToBinary(std::ofstream* outputFileStream, unsigned char value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT8 [1 BYTE] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT8 [1 BYTE] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - INT8 [1 BYTE] ||||||||||||||||||||||||||||||||||||||||

void BinarySerialization::WriteInt8ToBinary(std::ofstream* outputFileStream, char value)
{
	outputFileStream->write(reinterpret_cast<char*>(&value), sizeof(value));
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - BYTE BUFFER [X BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - BYTE BUFFER [X BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - BYTE BUFFER [X BYTES] ||||||||||||||||||||||||||||||||||||||||

void BinarySerialization::WriteByteBufferToBinary(std::ofstream* outputFileStream, int dataSize, char* data)
{
	outputFileStream->write(data, dataSize);
}

//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - STRING [X BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - STRING [X BYTES] ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY WRITER - STRING [X BYTES] ||||||||||||||||||||||||||||||||||||||||

void BinarySerialization::WriteFixedStringToBinary(std::ofstream* outputFileStream, std::string value)
{
	outputFileStream->write(value.c_str(), value.length());
}

void BinarySerialization::WriteLengthPrefixedStringToBinary(std::ofstream* outputFileStream, std::string value)
{
	WriteInt32ToBinary(outputFileStream, value.length());
	WriteFixedStringToBinary(outputFileStream, value);
}
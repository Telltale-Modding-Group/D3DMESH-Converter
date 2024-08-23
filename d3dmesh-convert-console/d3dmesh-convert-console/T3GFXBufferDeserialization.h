#pragma once
#ifndef T3_GFX_BUFFER_DESERIALIZATION_H
#define T3_GFX_BUFFER_DESERIALIZATION_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "BinaryHelper.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "IntegerVector2.h"
#include "IntegerVector3.h"
#include "IntegerVector4.h"
#include "UnsignedIntegerVector2.h"
#include "UnsignedIntegerVector3.h"
#include "UnsignedIntegerVector4.h"

//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER F32 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER F32 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER F32 ||||||||||||||||||||||||||||||||||||||||

//[8 BYTES] eGFXPlatformFormat_F32x2
static Vector2 ReadT3GFXBuffer_2x32BitFloat(std::ifstream* inputFileStream)
{
	Vector2 vector2{};
	vector2.x = ReadFloat32FromBinary(inputFileStream);
	vector2.y = ReadFloat32FromBinary(inputFileStream);
	return vector2;
}

//[12 BYTES] eGFXPlatformFormat_F32x3
static Vector3 ReadT3GFXBuffer_3x32BitFloat(std::ifstream* inputFileStream)
{
	Vector3 vector3{};
	vector3.x = ReadFloat32FromBinary(inputFileStream);
	vector3.y = ReadFloat32FromBinary(inputFileStream);
	vector3.z = ReadFloat32FromBinary(inputFileStream);
	return vector3;
}

//[16 BYTES] eGFXPlatformFormat_F32x4
static Vector4 ReadT3GFXBuffer_4x32BitFloat(std::ifstream* inputFileStream)
{
	Vector4 vector4{};
	vector4.x = ReadFloat32FromBinary(inputFileStream);
	vector4.y = ReadFloat32FromBinary(inputFileStream);
	vector4.z = ReadFloat32FromBinary(inputFileStream);
	vector4.w = ReadFloat32FromBinary(inputFileStream);

	return vector4;
}

//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER U32 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER U32 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER U32 ||||||||||||||||||||||||||||||||||||||||

//[8 BYTES] eGFXPlatformFormat_U32x2
static UnsignedIntegerVector2 ReadT3GFXBuffer_Unsigned_2x32BitInteger(std::ifstream* inputFileStream)
{
	UnsignedIntegerVector2 uivector2{};
	uivector2.x = ReadUInt32FromBinary(inputFileStream);
	uivector2.y = ReadUInt32FromBinary(inputFileStream);
	return uivector2;
}

//[12 BYTES] eGFXPlatformFormat_U32x3
static UnsignedIntegerVector3 ReadT3GFXBuffer_Unsigned_3x32BitInteger(std::ifstream* inputFileStream)
{
	UnsignedIntegerVector3 uivector3{};
	uivector3.x = ReadUInt32FromBinary(inputFileStream);
	uivector3.y = ReadUInt32FromBinary(inputFileStream);
	uivector3.z = ReadUInt32FromBinary(inputFileStream);
	return uivector3;
}

//[16 BYTES] eGFXPlatformFormat_U32x4
static UnsignedIntegerVector4 ReadT3GFXBuffer_Unsigned_4x32BitInteger(std::ifstream* inputFileStream)
{
	UnsignedIntegerVector4 uivector4{};
	uivector4.x = ReadUInt32FromBinary(inputFileStream);
	uivector4.y = ReadUInt32FromBinary(inputFileStream);
	uivector4.z = ReadUInt32FromBinary(inputFileStream);
	uivector4.w = ReadUInt32FromBinary(inputFileStream);
	return uivector4;
}

//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER S32 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER S32 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER S32 ||||||||||||||||||||||||||||||||||||||||

//[8 BYTES] eGFXPlatformFormat_S32x2
static IntegerVector2 ReadT3GFXBuffer_Signed_2x32BitInteger(std::ifstream* inputFileStream)
{
	IntegerVector2 ivector2{};
	ivector2.x = ReadInt32FromBinary(inputFileStream);
	ivector2.y = ReadInt32FromBinary(inputFileStream);
	return ivector2;
}

//[12 BYTES] eGFXPlatformFormat_S32x3
static IntegerVector3 ReadT3GFXBuffer_Signed_3x32BitInteger(std::ifstream* inputFileStream)
{
	IntegerVector3 ivector3{};
	ivector3.x = ReadInt32FromBinary(inputFileStream);
	ivector3.y = ReadInt32FromBinary(inputFileStream);
	ivector3.z = ReadInt32FromBinary(inputFileStream);
	return ivector3;
}

//[16 BYTES] eGFXPlatformFormat_S32x4
static IntegerVector4 ReadT3GFXBuffer_Signed_4x32BitInteger(std::ifstream* inputFileStream)
{
	IntegerVector4 ivector4{};
	ivector4.x = ReadInt32FromBinary(inputFileStream);
	ivector4.y = ReadInt32FromBinary(inputFileStream);
	ivector4.z = ReadInt32FromBinary(inputFileStream);
	ivector4.w = ReadInt32FromBinary(inputFileStream);
	return ivector4;
}

//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER U16 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER U16 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER U16 ||||||||||||||||||||||||||||||||||||||||

//[4 BYTES] eGFXPlatformFormat_U16x2
static UnsignedIntegerVector2 ReadT3GFXBuffer_Unsigned_2x16BitInteger(std::ifstream* inputFileStream)
{
	UnsignedIntegerVector2 uivector2{};
	uivector2.x = ReadUInt16FromBinary(inputFileStream);
	uivector2.y = ReadUInt16FromBinary(inputFileStream);
	return uivector2;
}

//[8 BYTES] eGFXPlatformFormat_U16x4
static UnsignedIntegerVector4 ReadT3GFXBuffer_Unsigned_4x16BitInteger(std::ifstream* inputFileStream)
{
	UnsignedIntegerVector4 uivector4{};
	uivector4.x = ReadUInt16FromBinary(inputFileStream);
	uivector4.y = ReadUInt16FromBinary(inputFileStream);
	uivector4.z = ReadUInt16FromBinary(inputFileStream);
	uivector4.z = ReadUInt16FromBinary(inputFileStream);
	return uivector4;
}

//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER S16 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER S16 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER S16 ||||||||||||||||||||||||||||||||||||||||

//[4 BYTES] eGFXPlatformFormat_S16x2
static IntegerVector2 ReadT3GFXBuffer_Signed_2x16BitInteger(std::ifstream* inputFileStream)
{
	IntegerVector2 ivector2{};
	ivector2.x = ReadInt16FromBinary(inputFileStream);
	ivector2.y = ReadInt16FromBinary(inputFileStream);
	return ivector2;
}

//[8 BYTES] eGFXPlatformFormat_S16x4
static IntegerVector4 ReadT3GFXBuffer_Signed_4x16BitInteger(std::ifstream* inputFileStream)
{
	IntegerVector4 ivector4{};
	ivector4.x = ReadInt16FromBinary(inputFileStream);
	ivector4.y = ReadInt16FromBinary(inputFileStream);
	ivector4.z = ReadInt16FromBinary(inputFileStream);
	ivector4.w = ReadInt16FromBinary(inputFileStream);
	return ivector4;
}

//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER UN16 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER UN16 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER UN16 ||||||||||||||||||||||||||||||||||||||||
//REFERENCES - https://gamedev.net/forums/topic/696946-normalized-unsigned-integers-vs-floats-as-vertex-data/5379766/

//[2 BYTES] eGFXPlatformFormat_UN16
static float ReadT3GFXBuffer_UnsignedNormalized_16BitInteger(std::ifstream* inputFileStream)
{
	unsigned short ushort = ReadUInt16FromBinary(inputFileStream); //[0,65535]
	float resultFloat = ushort / (float)65535; //normalize 16 bit ushort [0,65535] to float [0, 1]
	return resultFloat;
}

//[4 BYTES] eGFXPlatformFormat_UN16x2
static Vector2 ReadT3GFXBuffer_UnsignedNormalized_2x16BitInteger(std::ifstream* inputFileStream)
{
	Vector2 vector2{};
	vector2.x = ReadT3GFXBuffer_UnsignedNormalized_16BitInteger(inputFileStream);
	vector2.y = ReadT3GFXBuffer_UnsignedNormalized_16BitInteger(inputFileStream);
	return vector2;
}

//[8 BYTES] eGFXPlatformFormat_UN16x4
static Vector4 ReadT3GFXBuffer_UnsignedNormalized_4x16BitInteger(std::ifstream* inputFileStream)
{
	Vector4 vector4{};
	vector4.x = ReadT3GFXBuffer_UnsignedNormalized_16BitInteger(inputFileStream);
	vector4.y = ReadT3GFXBuffer_UnsignedNormalized_16BitInteger(inputFileStream);
	vector4.z = ReadT3GFXBuffer_UnsignedNormalized_16BitInteger(inputFileStream);
	vector4.w = ReadT3GFXBuffer_UnsignedNormalized_16BitInteger(inputFileStream);
	return vector4;
}

//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN16 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN16 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN16 ||||||||||||||||||||||||||||||||||||||||

//[2 BYTES] eGFXPlatformFormat_SN16
static float ReadT3GFXBuffer_Normalized_16BitInteger(std::ifstream* inputFileStream)
{
	short shortSigned = ReadInt16FromBinary(inputFileStream);
	float resultFloat = shortSigned / (float)32767; //normalize 16 bit short [-32768, 32767] to float [-1, 1]
	return resultFloat;
}

//[4 BYTES] eGFXPlatformFormat_SN16x2
static Vector2 ReadT3GFXBuffer_Normalized_2x16BitInteger(std::ifstream* inputFileStream)
{
	Vector2 vector2{};
	vector2.x = ReadT3GFXBuffer_Normalized_16BitInteger(inputFileStream);
	vector2.y = ReadT3GFXBuffer_Normalized_16BitInteger(inputFileStream);
	return vector2;
}

//[8 BYTES] eGFXPlatformFormat_SN16x4
static Vector4 ReadT3GFXBuffer_Normalized_4x16BitInteger(std::ifstream* inputFileStream)
{
	Vector4 vector4{};
	vector4.x = ReadT3GFXBuffer_Normalized_16BitInteger(inputFileStream);
	vector4.y = ReadT3GFXBuffer_Normalized_16BitInteger(inputFileStream);
	vector4.z = ReadT3GFXBuffer_Normalized_16BitInteger(inputFileStream);
	vector4.w = ReadT3GFXBuffer_Normalized_16BitInteger(inputFileStream);
	return vector4;
}

//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER U8 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER U8 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER U8 ||||||||||||||||||||||||||||||||||||||||

//[2 BYTES] eGFXPlatformFormat_U8x2
static UnsignedIntegerVector2 ReadT3GFXBuffer_Unsigned_2x8BitInteger(std::ifstream* inputFileStream)
{
	UnsignedIntegerVector2 uivector2{};
	uivector2.x = ReadUInt8FromBinary(inputFileStream);
	uivector2.y = ReadUInt8FromBinary(inputFileStream);
	return uivector2;
}

//[4 BYTES] eGFXPlatformFormat_U8x4
static UnsignedIntegerVector4 ReadT3GFXBuffer_Unsigned_4x8BitInteger(std::ifstream* inputFileStream)
{
	UnsignedIntegerVector4 uivector4{};
	uivector4.x = ReadUInt8FromBinary(inputFileStream);
	uivector4.y = ReadUInt8FromBinary(inputFileStream);
	uivector4.z = ReadUInt8FromBinary(inputFileStream);
	uivector4.w = ReadUInt8FromBinary(inputFileStream);
	return uivector4;
}

//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER S8 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER S8 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER S8 ||||||||||||||||||||||||||||||||||||||||

//[2 BYTES] eGFXPlatformFormat_S8x2
static IntegerVector2 ReadT3GFXBuffer_Signed_2x8BitInteger(std::ifstream* inputFileStream)
{
	IntegerVector2 ivector2{};
	ivector2.x = ReadInt8FromBinary(inputFileStream);
	ivector2.y = ReadInt8FromBinary(inputFileStream);
	return ivector2;
}

//[4 BYTES] eGFXPlatformFormat_S8x4
static IntegerVector4 ReadT3GFXBuffer_Signed_4x8BitInteger(std::ifstream* inputFileStream)
{
	IntegerVector4 ivector4{};
	ivector4.x = ReadInt8FromBinary(inputFileStream);
	ivector4.y = ReadInt8FromBinary(inputFileStream);
	ivector4.z = ReadInt8FromBinary(inputFileStream);
	ivector4.w = ReadInt8FromBinary(inputFileStream);
	return ivector4;
}

//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER UN8 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER UN8 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER UN8 ||||||||||||||||||||||||||||||||||||||||

//[1 BYTE] eGFXPlatformFormat_UN8
static float ReadT3GFXBuffer_UnsignedNormalized_8BitInteger(std::ifstream* inputFileStream)
{
	unsigned char uchar = ReadUInt8FromBinary(inputFileStream);
	float resultFloat = uchar / (float)255; //normalize 8 bit uchar [0,255] to float [0, 1]
	return resultFloat;
}

//[2 BYTES] eGFXPlatformFormat_UN8x2
static Vector2 ReadT3GFXBuffer_UnsignedNormalized_2x8BitInteger(std::ifstream* inputFileStream)
{
	Vector2 vector2{};
	vector2.x = ReadT3GFXBuffer_UnsignedNormalized_8BitInteger(inputFileStream);
	vector2.y = ReadT3GFXBuffer_UnsignedNormalized_8BitInteger(inputFileStream);
	return vector2;
}

//[4 BYTES] eGFXPlatformFormat_UN8x4
static Vector4 ReadT3GFXBuffer_UnsignedNormalized_4x8BitInteger(std::ifstream* inputFileStream)
{
	Vector4 vector4{};
	vector4.x = ReadT3GFXBuffer_UnsignedNormalized_8BitInteger(inputFileStream);
	vector4.y = ReadT3GFXBuffer_UnsignedNormalized_8BitInteger(inputFileStream);
	vector4.z = ReadT3GFXBuffer_UnsignedNormalized_8BitInteger(inputFileStream);
	vector4.w = ReadT3GFXBuffer_UnsignedNormalized_8BitInteger(inputFileStream);
	return vector4;
}

//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN8 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN8 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN8 ||||||||||||||||||||||||||||||||||||||||

//[1 BYTE] eGFXPlatformFormat_SN8
static float ReadT3GFXBuffer_Normalized_8BitInteger(std::ifstream* inputFileStream)
{
	char signedChar = ReadInt8FromBinary(inputFileStream);
	float resultFloat = signedChar / (float)127; //normalize 8 bit uchar [-128, 127] to float [0, 1]
	return resultFloat;
}

//[2 BYTES] eGFXPlatformFormat_SN8x2
static Vector2 ReadT3GFXBuffer_Normalized_2x8BitInteger(std::ifstream* inputFileStream)
{
	Vector2 vector2{};
	vector2.x = ReadT3GFXBuffer_Normalized_8BitInteger(inputFileStream);
	vector2.y = ReadT3GFXBuffer_Normalized_8BitInteger(inputFileStream);
	return vector2;
}

//[4 BYTES] eGFXPlatformFormat_SN8x4
static Vector4 ReadT3GFXBuffer_Normalized_4x8BitInteger(std::ifstream* inputFileStream)
{
	Vector4 vector4{};
	vector4.x = ReadT3GFXBuffer_Normalized_8BitInteger(inputFileStream);
	vector4.y = ReadT3GFXBuffer_Normalized_8BitInteger(inputFileStream);
	vector4.z = ReadT3GFXBuffer_Normalized_8BitInteger(inputFileStream);
	vector4.w = ReadT3GFXBuffer_Normalized_8BitInteger(inputFileStream);
	return vector4;
}

//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN10_SN11_SN11 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN10_SN11_SN11 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN10_SN11_SN11 ||||||||||||||||||||||||||||||||||||||||

static Vector4 ReadT3GFXBuffer_Normalized_10BitInteger_2x11BitInteger(std::ifstream* inputFileStream)
{
	Vector4 vector4{};

	//read the whole 4 bytes as a uint
	unsigned int uint = ReadUInt32FromBinary(inputFileStream);

	//---------------------BIT EXTRACTION---------------------
	//first 10 bits
	unsigned int first_10bit = BitFieldExtract(uint, 0, 10); //10 bits [0,1023]
	int firstSigned_10bit = first_10bit - 512; //convert to signed [-512,511]

	//second 11 bits
	unsigned int second_11bit = BitFieldExtract(uint, 10, 11); //11 bits [0,2047]
	int secondSigned_11bit = second_11bit - 1024; //convert to signed [-1024,1023]

	//third 11 bits
	unsigned int third_11bit = BitFieldExtract(uint, 21, 11); //11 bits [0,2047]
	int thirdSigned_11bit = third_11bit - 1024; //convert to signed [-1024,1023]

	//---------------------NORMALIZATION---------------------
	vector4.x = firstSigned_10bit / (float)511; //normalize 10 bit ushort [-512, 511] to float [-1, 1]
	vector4.y = secondSigned_11bit / (float)1023; //normalize 11 bit ushort [-1024,1023] to float [-1, 1]
	vector4.z = thirdSigned_11bit / (float)1023; //normalize 11 bit ushort [-1024,1023] to float [-1, 1]

	return vector4;
}

//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER UN10x3_UN2 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER UN10x3_UN2 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER UN10x3_UN2 ||||||||||||||||||||||||||||||||||||||||

//[4 BYTES] eGFXPlatformFormat_UN10x3_UN2
static Vector3 ReadT3GFXBuffer_UnsignedNormalized_3x10BitInteger_2BitInteger(std::ifstream* inputFileStream, Vector3& mPositionWScale)
{
	Vector3 vector3{};

	//read the whole 4 bytes as a uint
	unsigned int uint = ReadUInt32FromBinary(inputFileStream);

	//temp variables
	unsigned int firstValue = 0;
	unsigned int secondValue = 0;
	unsigned int thirdValue = 0;
	unsigned int fourthValue = 0;

	//---------------------BIT EXTRACTION---------------------
	//first 10 bits
	firstValue = BitFieldExtract(uint, 0, 10); //10 bits [0,1023]

	//second 10 bits
	secondValue = BitFieldExtract(uint, 10, 10); //10 bits [0,1023]

	//third 10 bits
	thirdValue = BitFieldExtract(uint, 20, 10); //10 bits [0,1023]

	//fourth 2 bits
	fourthValue = BitFieldExtract(uint, 30, 2); //2 bits [0, 3]

	//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE X AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE X AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE X AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	if (mPositionWScale.x != 0.0f)
	{
		//---------------------BIT COMBINE---------------------
		//combine last bits for x axis
		firstValue = fourthValue << 10 | firstValue;
	}
	//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE Y AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE Y AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE Y AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	else if (mPositionWScale.y != 0.0f)
	{
		//---------------------BIT COMBINE---------------------
		//combine last bits for y axis
		secondValue = fourthValue << 10 | secondValue;
	}
	//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE Z AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE Z AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE Z AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	else if (mPositionWScale.z != 0.0f)
	{
		//---------------------BIT COMBINE---------------------
		//combine last bits for z axis
		thirdValue = fourthValue << 10 | thirdValue;
	}

	//---------------------NORMALIZATION---------------------
	vector3.x = firstValue / (float)1023; //normalize 10 bit ushort [0, 1023] to float [0, 1]
	vector3.y = secondValue / (float)1023; //normalize 10 bit ushort [0, 1023] to float [0, 1]
	vector3.z = thirdValue / (float)1023; //normalize 10 bit ushort [0, 1023] to float [0, 1]

	return vector3;
}

//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN10x3_SN2 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN10x3_SN2 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| BINARY READER - T3GFXBUFFER SN10x3_SN2 ||||||||||||||||||||||||||||||||||||||||

//[4 BYTES] eGFXPlatformFormat_SN10x3_SN2
static Vector3 ReadT3GFXBuffer_Normalized_3x10BitInteger_2BitInteger(std::ifstream* inputFileStream, Vector3& mPositionWScale)
{
	Vector3 vector3{};

	//read the whole 4 bytes as a uint
	unsigned int uint = ReadUInt32FromBinary(inputFileStream);

	//temp variables
	unsigned int firstValue = 0;
	unsigned int secondValue = 0;
	unsigned int thirdValue = 0;
	unsigned int fourthValue = 0;

	//---------------------BIT EXTRACTION---------------------
	//first 10 bits
	firstValue = BitFieldExtract(uint, 0, 10) - 512; //extract 10 bits [0, 1023] then convert to signed integer [-512,511]

	//second 10 bits
	secondValue = BitFieldExtract(uint, 10, 10) - 512; //extract 10 bits [0, 1023] then convert to signed integer [-512,511]

	//third 10 bits
	thirdValue = BitFieldExtract(uint, 20, 10) - 512; //extract 10 bits [0, 1023] then convert to signed integer [-512,511]

	//fourth 2 bits
	fourthValue = BitFieldExtract(uint, 30, 2) - 1; //extract 2 bits [0, 3] then convert to signed integer [-1,2]

	//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE X AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE X AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE X AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	if (mPositionWScale.x != 0.0f)
	{
		//---------------------BIT COMBINE---------------------
		//combine last bits for x axis
		firstValue = fourthValue << 10 | firstValue;
	}
	//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE Y AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE Y AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE Y AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	else if (mPositionWScale.y != 0.0f)
	{
		//---------------------BIT COMBINE---------------------
		//combine last bits for y axis
		secondValue = fourthValue << 10 | secondValue;
	}
	//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE Z AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE Z AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE Z AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	else if (mPositionWScale.z != 0.0f)
	{
		//---------------------BIT COMBINE---------------------
		//combine last bits for z axis
		thirdValue = fourthValue << 10 | thirdValue;
	}

	//---------------------NORMALIZATION---------------------
	vector3.x = firstValue / (float)511; //normalize 10 bit ushort [-512, 511] to float [-1, 1]
	vector3.y = secondValue / (float)511; //normalize 10 bit ushort [-512, 511] to float [-1, 1]
	vector3.z = thirdValue / (float)511; //normalize 10 bit ushort [-512, 511] to float [-1, 1]

	return vector3;
}

#endif
#pragma once
#ifndef T3_GFX_BUFFER_SERIALIZATION_H
#define T3_GFX_BUFFER_SERIALIZATION_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "BinarySerialization.h"
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

//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER F32 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER F32 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER F32 ||||||||||||||||||||||||||||||||||||||||

//[8 BYTES] eGFXPlatformFormat_F32x2
static void WriteT3GFXBuffer_2x32BitFloat(std::ofstream* outputFileStream, Vector2 vector2)
{
	WriteFloat32ToBinary(outputFileStream, vector2.x); //[4 BYTES]
	WriteFloat32ToBinary(outputFileStream, vector2.y); //[4 BYTES]
}

//[12 BYTES] eGFXPlatformFormat_F32x3
static void WriteT3GFXBuffer_3x32BitFloat(std::ofstream* outputFileStream, Vector3 vector3)
{
	WriteFloat32ToBinary(outputFileStream, vector3.x); //[4 BYTES]
	WriteFloat32ToBinary(outputFileStream, vector3.y); //[4 BYTES]
	WriteFloat32ToBinary(outputFileStream, vector3.z); //[4 BYTES]
}

//[16 BYTES] eGFXPlatformFormat_F32x4
static void WriteT3GFXBuffer_4x32BitFloat(std::ofstream* outputFileStream, Vector4 vector4)
{
	WriteFloat32ToBinary(outputFileStream, vector4.x); //[4 BYTES]
	WriteFloat32ToBinary(outputFileStream, vector4.y); //[4 BYTES]
	WriteFloat32ToBinary(outputFileStream, vector4.z); //[4 BYTES]
	WriteFloat32ToBinary(outputFileStream, vector4.w); //[4 BYTES]
}

//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER U32 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER U32 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER U32 ||||||||||||||||||||||||||||||||||||||||

//[8 BYTES] eGFXPlatformFormat_U32x2
static void WriteT3GFXBuffer_Unsigned_2x32BitInteger(std::ofstream* outputFileStream, UnsignedIntegerVector2 uivector2)
{
	WriteUInt32ToBinary(outputFileStream, uivector2.x); //[4 BYTES]
	WriteUInt32ToBinary(outputFileStream, uivector2.y); //[4 BYTES]
}

//[12 BYTES] eGFXPlatformFormat_U32x3
static void WriteT3GFXBuffer_Unsigned_3x32BitInteger(std::ofstream* outputFileStream, UnsignedIntegerVector3 uivector3)
{
	WriteUInt32ToBinary(outputFileStream, uivector3.x); //[4 BYTES]
	WriteUInt32ToBinary(outputFileStream, uivector3.y); //[4 BYTES]
	WriteUInt32ToBinary(outputFileStream, uivector3.z); //[4 BYTES]
}

//[16 BYTES] eGFXPlatformFormat_U32x4
static void WriteT3GFXBuffer_Unsigned_4x32BitInteger(std::ofstream* outputFileStream, UnsignedIntegerVector4 uivector4)
{
	WriteUInt32ToBinary(outputFileStream, uivector4.x); //[4 BYTES]
	WriteUInt32ToBinary(outputFileStream, uivector4.y); //[4 BYTES]
	WriteUInt32ToBinary(outputFileStream, uivector4.z); //[4 BYTES]
	WriteUInt32ToBinary(outputFileStream, uivector4.w); //[4 BYTES]
}

//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER S32 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER S32 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER S32 ||||||||||||||||||||||||||||||||||||||||

//[8 BYTES] eGFXPlatformFormat_S32x2
static void WriteT3GFXBuffer_Signed_2x32BitInteger(std::ofstream* outputFileStream, IntegerVector2 ivector2)
{
	WriteInt32ToBinary(outputFileStream, ivector2.x); //[4 BYTES]
	WriteInt32ToBinary(outputFileStream, ivector2.y); //[4 BYTES]
}

//[12 BYTES] eGFXPlatformFormat_S32x3
static void WriteT3GFXBuffer_Signed_3x32BitInteger(std::ofstream* outputFileStream, IntegerVector3 ivector3)
{
	WriteInt32ToBinary(outputFileStream, ivector3.x); //[4 BYTES]
	WriteInt32ToBinary(outputFileStream, ivector3.y); //[4 BYTES]
	WriteInt32ToBinary(outputFileStream, ivector3.z); //[4 BYTES]
}

//[16 BYTES] eGFXPlatformFormat_S32x4
static void WriteT3GFXBuffer_Signed_4x32BitInteger(std::ofstream* outputFileStream, IntegerVector4 ivector4)
{
	WriteInt32ToBinary(outputFileStream, ivector4.x); //[4 BYTES]
	WriteInt32ToBinary(outputFileStream, ivector4.y); //[4 BYTES]
	WriteInt32ToBinary(outputFileStream, ivector4.z); //[4 BYTES]
	WriteInt32ToBinary(outputFileStream, ivector4.w); //[4 BYTES]
}

//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER U16 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER U16 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER U16 ||||||||||||||||||||||||||||||||||||||||

//[4 BYTES] eGFXPlatformFormat_U16x2
static void WriteT3GFXBuffer_Unsigned_2x16BitInteger(std::ofstream* outputFileStream, UnsignedIntegerVector2 uivector2)
{
	WriteUInt16ToBinary(outputFileStream, uivector2.x); //[2 BYTES]
	WriteUInt16ToBinary(outputFileStream, uivector2.y); //[2 BYTES]
}

//[8 BYTES] eGFXPlatformFormat_U16x4
static void WriteT3GFXBuffer_Unsigned_4x16BitInteger(std::ofstream* outputFileStream, UnsignedIntegerVector4 uivector4)
{
	WriteUInt16ToBinary(outputFileStream, uivector4.x); //[2 BYTES]
	WriteUInt16ToBinary(outputFileStream, uivector4.y); //[2 BYTES]
	WriteUInt16ToBinary(outputFileStream, uivector4.z); //[2 BYTES]
	WriteUInt16ToBinary(outputFileStream, uivector4.w); //[2 BYTES]
}

//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER S16 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER S16 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER S16 ||||||||||||||||||||||||||||||||||||||||

//[4 BYTES] eGFXPlatformFormat_S16x2
static void WriteT3GFXBuffer_Signed_2x16BitInteger(std::ofstream* outputFileStream, IntegerVector2 ivector2)
{
	WriteInt16ToBinary(outputFileStream, ivector2.x); //[2 BYTES]
	WriteInt16ToBinary(outputFileStream, ivector2.y); //[2 BYTES]
}

//[8 BYTES] eGFXPlatformFormat_S16x4
static void WriteT3GFXBuffer_Signed_4x16BitInteger(std::ofstream* outputFileStream, IntegerVector4 ivector4)
{
	WriteInt16ToBinary(outputFileStream, ivector4.x); //[2 BYTES]
	WriteInt16ToBinary(outputFileStream, ivector4.y); //[2 BYTES]
	WriteInt16ToBinary(outputFileStream, ivector4.z); //[2 BYTES]
	WriteInt16ToBinary(outputFileStream, ivector4.w); //[2 BYTES]
}

//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER UN16 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER UN16 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER UN16 ||||||||||||||||||||||||||||||||||||||||
//REFERENCES - https://gamedev.net/forums/topic/696946-normalized-unsigned-integers-vs-floats-as-vertex-data/5379766/

//[2 BYTES] eGFXPlatformFormat_UN16
static void WriteT3GFXBuffer_UnsignedNormalized_16BitInteger(std::ofstream* outputFileStream, float normalizedFloat)
{
	unsigned short ushort = normalizedFloat * 65535; //float [0, 1] to unsigned short [0,65535]
	WriteUInt16ToBinary(outputFileStream, ushort); //[2 BYTES]

	//UN16 Reading Reference
	//unsigned short ushort = ReadUInt16FromBinary(outputFileStream); //[0,65535]
	//float resultFloat = ushort / (float)65535; //normalize 16 bit ushort [0,65535] to float [0, 1]
}

//[4 BYTES] eGFXPlatformFormat_UN16x2
static void WriteT3GFXBuffer_UnsignedNormalized_2x16BitInteger(std::ofstream* outputFileStream, Vector2 vector2)
{
	WriteT3GFXBuffer_UnsignedNormalized_16BitInteger(outputFileStream, vector2.x);
	WriteT3GFXBuffer_UnsignedNormalized_16BitInteger(outputFileStream, vector2.y);
}

//[8 BYTES] eGFXPlatformFormat_UN16x4
static void WriteT3GFXBuffer_UnsignedNormalized_4x16BitInteger(std::ofstream* outputFileStream, Vector4 vector4)
{
	WriteT3GFXBuffer_UnsignedNormalized_16BitInteger(outputFileStream, vector4.x);
	WriteT3GFXBuffer_UnsignedNormalized_16BitInteger(outputFileStream, vector4.y);
	WriteT3GFXBuffer_UnsignedNormalized_16BitInteger(outputFileStream, vector4.z);
	WriteT3GFXBuffer_UnsignedNormalized_16BitInteger(outputFileStream, vector4.w);
}

//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER SN16 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER SN16 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER SN16 ||||||||||||||||||||||||||||||||||||||||

//[2 BYTES] eGFXPlatformFormat_SN16
static void WriteT3GFXBuffer_Normalized_16BitInteger(std::ofstream* outputFileStream, float normalizedFloat)
{
	short shortSigned = normalizedFloat * 32767; //float [-1, 1] to signed short [-32768, 32767]
	WriteInt16ToBinary(outputFileStream, shortSigned); //[2 BYTES]

	//SN16 Reading Reference
	//short shortSigned = ReadInt16FromBinary(outputFileStream);
	//float resultFloat = shortSigned / (float)32767; //normalize 16 bit short [-32768, 32767] to float [-1, 1]
}

//[4 BYTES] eGFXPlatformFormat_SN16x2
static void WriteT3GFXBuffer_Normalized_2x16BitInteger(std::ofstream* outputFileStream, Vector2 vector2)
{
	WriteT3GFXBuffer_Normalized_16BitInteger(outputFileStream, vector2.x);
	WriteT3GFXBuffer_Normalized_16BitInteger(outputFileStream, vector2.y);
}

//[8 BYTES] eGFXPlatformFormat_SN16x4
static void WriteT3GFXBuffer_Normalized_4x16BitInteger(std::ofstream* outputFileStream, Vector4 vector4)
{
	WriteT3GFXBuffer_Normalized_16BitInteger(outputFileStream, vector4.x);
	WriteT3GFXBuffer_Normalized_16BitInteger(outputFileStream, vector4.y);
	WriteT3GFXBuffer_Normalized_16BitInteger(outputFileStream, vector4.z);
	WriteT3GFXBuffer_Normalized_16BitInteger(outputFileStream, vector4.w);
}

//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER U8 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER U8 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER U8 ||||||||||||||||||||||||||||||||||||||||

//[2 BYTES] eGFXPlatformFormat_U8x2
static void WriteT3GFXBuffer_Unsigned_2x8BitInteger(std::ofstream* outputFileStream, UnsignedIntegerVector2 uivector2)
{
	WriteUInt8ToBinary(outputFileStream, uivector2.x);
	WriteUInt8ToBinary(outputFileStream, uivector2.y);
}

//[4 BYTES] eGFXPlatformFormat_U8x4
static void WriteT3GFXBuffer_Unsigned_4x8BitInteger(std::ofstream* outputFileStream, UnsignedIntegerVector4 uivector4)
{
	WriteUInt8ToBinary(outputFileStream, uivector4.x);
	WriteUInt8ToBinary(outputFileStream, uivector4.y);
	WriteUInt8ToBinary(outputFileStream, uivector4.z);
	WriteUInt8ToBinary(outputFileStream, uivector4.w);
}

//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER S8 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER S8 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER S8 ||||||||||||||||||||||||||||||||||||||||

//[2 BYTES] eGFXPlatformFormat_S8x2
static void WriteT3GFXBuffer_Signed_2x8BitInteger(std::ofstream* outputFileStream, IntegerVector2 ivector2)
{
	WriteInt8ToBinary(outputFileStream, ivector2.x);
	WriteInt8ToBinary(outputFileStream, ivector2.y);
}

//[4 BYTES] eGFXPlatformFormat_S8x4
static void WriteT3GFXBuffer_Signed_4x8BitInteger(std::ofstream* outputFileStream, IntegerVector4 ivector4)
{
	WriteInt8ToBinary(outputFileStream, ivector4.x);
	WriteInt8ToBinary(outputFileStream, ivector4.y);
	WriteInt8ToBinary(outputFileStream, ivector4.z);
	WriteInt8ToBinary(outputFileStream, ivector4.w);
}

//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER UN8 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER UN8 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER UN8 ||||||||||||||||||||||||||||||||||||||||

//[1 BYTE] eGFXPlatformFormat_UN8
static void WriteT3GFXBuffer_UnsignedNormalized_8BitInteger(std::ofstream* outputFileStream, float normalizedFloat)
{
	unsigned char uchar = normalizedFloat * 255; //float [0, 1] to unsigned char [0, 255]
	WriteUInt8ToBinary(outputFileStream, uchar); //[1 BYTE]

	//UN8 Reading Reference
	//unsigned char uchar = ReadUInt8FromBinary(outputFileStream);
	//float resultFloat = uchar / (float)255; //normalize 8 bit uchar [0,255] to float [0, 1]
}

//[2 BYTES] eGFXPlatformFormat_UN8x2
static void WriteT3GFXBuffer_UnsignedNormalized_2x8BitInteger(std::ofstream* outputFileStream, Vector2 vector2)
{
	WriteT3GFXBuffer_UnsignedNormalized_8BitInteger(outputFileStream, vector2.x);
	WriteT3GFXBuffer_UnsignedNormalized_8BitInteger(outputFileStream, vector2.y);
}

//[4 BYTES] eGFXPlatformFormat_UN8x4
static void WriteT3GFXBuffer_UnsignedNormalized_4x8BitInteger(std::ofstream* outputFileStream, Vector4 vector4)
{
	WriteT3GFXBuffer_UnsignedNormalized_8BitInteger(outputFileStream, vector4.x);
	WriteT3GFXBuffer_UnsignedNormalized_8BitInteger(outputFileStream, vector4.y);
	WriteT3GFXBuffer_UnsignedNormalized_8BitInteger(outputFileStream, vector4.z);
	WriteT3GFXBuffer_UnsignedNormalized_8BitInteger(outputFileStream, vector4.w);
}

//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER SN8 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER SN8 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER SN8 ||||||||||||||||||||||||||||||||||||||||

//[1 BYTE] eGFXPlatformFormat_SN8
static void WriteT3GFXBuffer_Normalized_8BitInteger(std::ofstream* outputFileStream, float normalizedFloat)
{
	char signedChar = normalizedFloat * 127; //float [-1, 1] to signed char [-128, 127]
	WriteInt8ToBinary(outputFileStream, signedChar); //[1 BYTE]

	//SN8 Reading Reference
	//char signedChar = ReadInt8FromBinary(outputFileStream);
	//float resultFloat = signedChar / (float)127; //normalize 8 bit uchar [-128, 127] to float [-1, 1]
}

//[2 BYTES] eGFXPlatformFormat_SN8x2
static void WriteT3GFXBuffer_Normalized_2x8BitInteger(std::ofstream* outputFileStream, Vector2 vector2)
{
	WriteT3GFXBuffer_Normalized_8BitInteger(outputFileStream, vector2.x);
	WriteT3GFXBuffer_Normalized_8BitInteger(outputFileStream, vector2.y);
}

//[4 BYTES] eGFXPlatformFormat_SN8x4
static void WriteT3GFXBuffer_Normalized_4x8BitInteger(std::ofstream* outputFileStream, Vector4 vector4)
{
	WriteT3GFXBuffer_Normalized_8BitInteger(outputFileStream, vector4.x);
	WriteT3GFXBuffer_Normalized_8BitInteger(outputFileStream, vector4.y);
	WriteT3GFXBuffer_Normalized_8BitInteger(outputFileStream, vector4.z);
	WriteT3GFXBuffer_Normalized_8BitInteger(outputFileStream, vector4.w);
}

//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER SN10_SN11_SN11 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER SN10_SN11_SN11 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER SN10_SN11_SN11 ||||||||||||||||||||||||||||||||||||||||

static void WriteT3GFXBuffer_Normalized_10BitInteger_2x11BitInteger(std::ofstream* outputFileStream, Vector4 vector4)
{
	//read the whole 4 bytes as a uint
	//unsigned int uint = ReadUInt32FromBinary(outputFileStream);

	//---------------------BIT EXTRACTION---------------------
	//first 10 bits
	//unsigned int first_10bit = BitFieldExtract(uint, 0, 10); //10 bits [0,1023]
	//int firstSigned_10bit = first_10bit - 512; //convert to signed [-512,511]

	//second 11 bits
	//unsigned int second_11bit = BitFieldExtract(uint, 10, 11); //11 bits [0,2047]
	//int secondSigned_11bit = second_11bit - 1024; //convert to signed [-1024,1023]

	//third 11 bits
	//unsigned int third_11bit = BitFieldExtract(uint, 21, 11); //11 bits [0,2047]
	//int thirdSigned_11bit = third_11bit - 1024; //convert to signed [-1024,1023]

	//---------------------NORMALIZATION---------------------
	//vector4.x = firstSigned_10bit / (float)511; //normalize 10 bit ushort [-512, 511] to float [-1, 1]
	//vector4.y = secondSigned_11bit / (float)1023; //normalize 11 bit ushort [-1024,1023] to float [-1, 1]
	//vector4.z = thirdSigned_11bit / (float)1023; //normalize 11 bit ushort [-1024,1023] to float [-1, 1]
}

//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER UN10x3_UN2 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER UN10x3_UN2 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER UN10x3_UN2 ||||||||||||||||||||||||||||||||||||||||

//[4 BYTES] eGFXPlatformFormat_UN10x3_UN2
static void WriteT3GFXBuffer_UnsignedNormalized_3x10BitInteger_2BitInteger(std::ofstream* outputFileStream, Vector3 vector3, Vector3& mPositionWScale)
{
	//read the whole 4 bytes as a uint
	//unsigned int uint = ReadUInt32FromBinary(outputFileStream);

	//temp variables
	//unsigned int firstValue = 0;
	//unsigned int secondValue = 0;
	//unsigned int thirdValue = 0;
	//unsigned int fourthValue = 0;

	//---------------------BIT EXTRACTION---------------------
	//first 10 bits
	//firstValue = BitFieldExtract(uint, 0, 10); //10 bits [0,1023]

	//second 10 bits
	//secondValue = BitFieldExtract(uint, 10, 10); //10 bits [0,1023]

	//third 10 bits
	//thirdValue = BitFieldExtract(uint, 20, 10); //10 bits [0,1023]

	//fourth 2 bits
	//fourthValue = BitFieldExtract(uint, 30, 2); //2 bits [0, 3]

	//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE X AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE X AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE X AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//if (mPositionWScale.x != 0.0f)
	//{
		//---------------------BIT COMBINE---------------------
		//combine last bits for x axis
		//firstValue = fourthValue << 10 | firstValue;
	//}
	//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE Y AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE Y AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE Y AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//else if (mPositionWScale.y != 0.0f)
	//{
		//---------------------BIT COMBINE---------------------
		//combine last bits for y axis
		//secondValue = fourthValue << 10 | secondValue;
	//}
	//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE Z AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE Z AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| UN10x3_UN2 - MORE Z AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//else if (mPositionWScale.z != 0.0f)
	//{
		//---------------------BIT COMBINE---------------------
		//combine last bits for z axis
		//thirdValue = fourthValue << 10 | thirdValue;
	//}

	//---------------------NORMALIZATION---------------------
	//vector3.x = firstValue / (float)1023; //normalize 10 bit ushort [0, 1023] to float [0, 1]
	//vector3.y = secondValue / (float)1023; //normalize 10 bit ushort [0, 1023] to float [0, 1]
	//vector3.z = thirdValue / (float)1023; //normalize 10 bit ushort [0, 1023] to float [0, 1]
}

//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER SN10x3_SN2 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER SN10x3_SN2 ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3GFXBUFFER SN10x3_SN2 ||||||||||||||||||||||||||||||||||||||||

//[4 BYTES] eGFXPlatformFormat_SN10x3_SN2
static void WriteT3GFXBuffer_Normalized_3x10BitInteger_2BitInteger(std::ofstream* outputFileStream, Vector3 vector3, Vector3& mPositionWScale)
{
	//read the whole 4 bytes as a uint
	//unsigned int uint = ReadUInt32FromBinary(outputFileStream);

	//temp variables
	//unsigned int firstValue = 0;
	//unsigned int secondValue = 0;
	//unsigned int thirdValue = 0;
	//unsigned int fourthValue = 0;

	//---------------------BIT EXTRACTION---------------------
	//first 10 bits
	//firstValue = BitFieldExtract(uint, 0, 10) - 512; //extract 10 bits [0, 1023] then convert to signed integer [-512,511]

	//second 10 bits
	//secondValue = BitFieldExtract(uint, 10, 10) - 512; //extract 10 bits [0, 1023] then convert to signed integer [-512,511]

	//third 10 bits
	//thirdValue = BitFieldExtract(uint, 20, 10) - 512; //extract 10 bits [0, 1023] then convert to signed integer [-512,511]

	//fourth 2 bits
	//fourthValue = BitFieldExtract(uint, 30, 2) - 1; //extract 2 bits [0, 3] then convert to signed integer [-1,2]

	//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE X AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE X AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE X AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//if (mPositionWScale.x != 0.0f)
	//{
		//---------------------BIT COMBINE---------------------
		//combine last bits for x axis
		//firstValue = fourthValue << 10 | firstValue;
	//}
	//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE Y AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE Y AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE Y AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//else if (mPositionWScale.y != 0.0f)
	//{
		//---------------------BIT COMBINE---------------------
		//combine last bits for y axis
		//secondValue = fourthValue << 10 | secondValue;
	//}
	//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE Z AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE Z AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| SN10x3_SN2 - MORE Z AXIS PRECISION ||||||||||||||||||||||||||||||||||||||||
	//else if (mPositionWScale.z != 0.0f)
	//{
		//---------------------BIT COMBINE---------------------
		//combine last bits for z axis
		//thirdValue = fourthValue << 10 | thirdValue;
	//}

	//---------------------NORMALIZATION---------------------
	//vector3.x = firstValue / (float)511; //normalize 10 bit ushort [-512, 511] to float [-1, 1]
	//vector3.y = secondValue / (float)511; //normalize 10 bit ushort [-512, 511] to float [-1, 1]
	//vector3.z = thirdValue / (float)511; //normalize 10 bit ushort [-512, 511] to float [-1, 1]
}

#endif
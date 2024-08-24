#pragma once
#ifndef TELLTALE_D3DMESH_DATA_55_H
#define TELLTALE_D3DMESH_DATA_55_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "T3GFXBufferDeserialization.h"
#include "T3GFXBufferSerialization.h"

#include "Symbol.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "UnsignedIntegerVector4.h"
#include "TelltaleInternalResource.h"
#include "T3MeshLOD.h"
#include "T3MeshBoneEntry.h"
#include "T3MeshLocalTransformEntry.h"
#include "T3MaterialRequirements.h"
#include "T3GFXBuffer.h"
#include "GFXPlatformAttributeParams.h"
#include "TelltaleD3DMeshHeaderV55.h"

//||||||||||||||||||||||||||||| TELLTALE D3DMESH DATA V55 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE D3DMESH DATA V55 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE D3DMESH DATA V55 |||||||||||||||||||||||||||||

struct TelltaleD3DMeshDataV55
{
	int indexBufferCount = 0;
	int vertexNormalsCount = 0;
	int vertexUVsCount = 0;
	int vertexColorsCount = 0;

	std::vector<unsigned short> indexBuffer0;
	std::vector<unsigned short> indexBuffer1;
	std::vector<unsigned short> indexBuffer2;
	std::vector<unsigned short> indexBuffer3;
	std::vector<unsigned short> indexBuffer4;
	std::vector<unsigned short> indexBuffer5;
	std::vector<unsigned short> indexBuffer6;
	std::vector<unsigned short> indexBuffer7;

	//NOTE: Most of these types are not actually a "Vector4"
	//However in certain circumstances depending on the format used for the buffer, they will return a 4 component value.
	//So to make sure we capture ALL of the possible data we will assume everything is a Vector4

	std::vector<Vector4> vertexPositions;

	//NOTE: Models normally have 1 set of vertex normals, however in the case of telltale...
	//Most models actually have 2 sets of vertex normals
	//1. The main regular normal set
	//2. creased normal set?
	std::vector<Vector4> vertexNormals0;
	std::vector<Vector4> vertexNormals1;
	std::vector<Vector4> vertexNormals2;
	std::vector<Vector4> vertexNormals3;

	std::vector<Vector4> vertexTangents;

	std::vector<Vector4> vertexUVs0;
	std::vector<Vector4> vertexUVs1;
	std::vector<Vector4> vertexUVs2;
	std::vector<Vector4> vertexUVs3;
	std::vector<Vector4> vertexUVs4;
	std::vector<Vector4> vertexUVs5;
	std::vector<Vector4> vertexUVs6;
	std::vector<Vector4> vertexUVs7;

	std::vector<Vector4> vertexColors0;
	std::vector<Vector4> vertexColors1;
	std::vector<Vector4> vertexColors2;
	std::vector<Vector4> vertexColors3;
	std::vector<Vector4> vertexColors4;
	std::vector<Vector4> vertexColors5;
	std::vector<Vector4> vertexColors6;
	std::vector<Vector4> vertexColors7;

	std::vector<UnsignedIntegerVector4> vertexBlendIndex0;

	std::vector<Vector4> vertexBlendWeight0;

	TelltaleD3DMeshDataV55()
	{

	};

	TelltaleD3DMeshDataV55(std::ifstream* inputFileStream, TelltaleD3DMeshHeaderV55* d3dmeshHeader)
	{
		//|||||||||||||||||||||||||||||||||||||||| D3DMESH BUFFER DATA - mIndexBuffers ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| D3DMESH BUFFER DATA - mIndexBuffers ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| D3DMESH BUFFER DATA - mIndexBuffers ||||||||||||||||||||||||||||||||||||||||
		//here we begin actually parsing the d3dmesh data
		//the first chunks here are the index buffers, these essentially "indexes"

		/*
		//NOTE: This simply skips through each index buffer.
		//It's kept here because this is used as a reference to ensure that we can read through an entire index buffer correctly so we can be left at the correct offset for reading vertex buffers.
		for (int i = 0; i < d3dmeshFile.d3dmeshHeader.mIndexBuffers.size(); i++)
		{
			T3GFXBuffer* mIndexBuffer = &d3dmeshFile.d3dmeshHeader.mIndexBuffers[i];
			BinaryDeserialization::ReadByteBufferFromBinary(&currentD3DMESH_inputFileStream, mIndexBuffer->mCount * mIndexBuffer->mStride); //skip this data block
		}
		*/

		//Loop through each index buffer
		for (int i = 0; i < d3dmeshHeader->mIndexBuffers.size(); i++)
		{
			//reference to the main index buffer that we are currently on
			T3GFXBuffer* mIndexBuffer = &d3dmeshHeader->mIndexBuffers[i];

			switch (mIndexBuffer->mBufferFormat)
			{
			case GFXPlatformFormat::eGFXPlatformFormat_U16:
				//if (mIndexBuffer->mBufferUsage == 2) //eGFXPlatformBuffer_Index

				for (int j = 0; j < mIndexBuffer->mCount; j++)
				{
					unsigned short triangleIndex = ReadUInt16FromBinary(inputFileStream);

					if (indexBufferCount == 0)
						indexBuffer0.push_back(triangleIndex);
					else if (indexBufferCount == 1)
						indexBuffer1.push_back(triangleIndex);
					else if (indexBufferCount == 2)
						indexBuffer2.push_back(triangleIndex);
					else if (indexBufferCount == 3)
						indexBuffer3.push_back(triangleIndex);
					else if (indexBufferCount == 4)
						indexBuffer4.push_back(triangleIndex);
					else if (indexBufferCount == 5)
						indexBuffer5.push_back(triangleIndex);
					else if (indexBufferCount == 6)
						indexBuffer6.push_back(triangleIndex);
					else if (indexBufferCount == 7)
						indexBuffer7.push_back(triangleIndex);
				}

				//std::cout << "Index Buffer: " << indexBufferCount << " | mIndexBuffer->mBufferUsage: " << mIndexBuffer->mBufferUsage << std::endl;
				indexBufferCount++;

				break;
			default:
				std::cout << "SKIPPING DATA IN INDEX BUFFER!" << d3dmeshHeader->mName << std::endl;
				ReadByteBufferFromBinary(inputFileStream, mIndexBuffer->mCount * mIndexBuffer->mStride); //skip this data block
				break;
			}
		}

		//|||||||||||||||||||||||||||||||||||||||| D3DMESH DATA - mVertexBuffers ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| D3DMESH DATA - mVertexBuffers ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| D3DMESH DATA - mVertexBuffers ||||||||||||||||||||||||||||||||||||||||
		//now the last part of the entire file, which are the vertex buffers
		//these last chunks are the most important, as these are multiple buffers that contains information like vertex position, normals, etc.

		/*
		//NOTE: This simply skips through each index buffer.
		//It's kept here because this is used as a reference to ensure that we can read through an entire index buffer correctly so we can be left at the correct offset for reading vertex buffers.
		for (int i = 0; i < d3dmeshFile.d3dmeshHeader.mVertexBuffers.size(); i++)
		{
			T3GFXBuffer* mVertexBuffer = &d3dmeshFile.d3dmeshHeader.mVertexBuffers[i];
			BinaryDeserialization::ReadByteBufferFromBinary(&currentD3DMESH_inputFileStream, mVertexBuffer->mCount * mVertexBuffer->mStride); //skip this data block
		}
		*/

		///*
		for (int i = 0; i < d3dmeshHeader->mVertexBuffers.size(); i++)
		{
			T3GFXBuffer* mVertexBuffer = &d3dmeshHeader->mVertexBuffers[i];
			GFXPlatformAttributeParams* attributeParams = &d3dmeshHeader->GFXPlatformAttributeParamsArray[i];

			//||||||||||||||||||||||||||||||||||||| VERTEX POSITION |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX POSITION |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX POSITION |||||||||||||||||||||||||||||||||||||
			if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Position)
			{
				//if (mVertexBuffer->mBufferFormat == GFXPlatformFormat::eGFXPlatformFormat_UN16x4)
				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_UN16x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector4 parsedVertexPosition = ReadT3GFXBuffer_UnsignedNormalized_4x16BitInteger(inputFileStream);

						//SELF NOTE: DIVIDING BY THE W COMPONENT WILL CREATE VECTORS OF INFINITY/NAN VALUES, SO DONT DO IT!
						Vector4 convertedVertexPosition;
						convertedVertexPosition.x = parsedVertexPosition.x * d3dmeshHeader->mPositionScale.x + d3dmeshHeader->mPositionOffset.x;
						convertedVertexPosition.y = parsedVertexPosition.y * d3dmeshHeader->mPositionScale.y + d3dmeshHeader->mPositionOffset.y;
						convertedVertexPosition.z = parsedVertexPosition.z * d3dmeshHeader->mPositionScale.z + d3dmeshHeader->mPositionOffset.z;
						convertedVertexPosition.w = parsedVertexPosition.w;

						vertexPositions.push_back(convertedVertexPosition);
					}
				}
				//else if (mVertexBuffer->mBufferFormat == GFXPlatformFormat::eGFXPlatformFormat_UN10x3_UN2)
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_UN10x3_UN2)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector3 parsedVertexPosition = ReadT3GFXBuffer_UnsignedNormalized_3x10BitInteger_2BitInteger(inputFileStream, d3dmeshHeader->mPositionWScale);

						Vector4 convertedVertexPosition;
						convertedVertexPosition.x = parsedVertexPosition.x * d3dmeshHeader->mPositionScale.x + d3dmeshHeader->mPositionOffset.x;
						convertedVertexPosition.y = parsedVertexPosition.y * d3dmeshHeader->mPositionScale.y + d3dmeshHeader->mPositionOffset.y;
						convertedVertexPosition.z = parsedVertexPosition.z * d3dmeshHeader->mPositionScale.z + d3dmeshHeader->mPositionOffset.z;
						convertedVertexPosition.w = 0;

						vertexPositions.push_back(convertedVertexPosition);
					}
				}
				//else if (mVertexBuffer->mBufferFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x3)
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x3)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector3 parsedVertexPosition = ReadT3GFXBuffer_3x32BitFloat(inputFileStream);

						Vector4 convertedVertexPosition;
						convertedVertexPosition.x = parsedVertexPosition.x * d3dmeshHeader->mPositionScale.x + d3dmeshHeader->mPositionOffset.x;
						convertedVertexPosition.y = parsedVertexPosition.y * d3dmeshHeader->mPositionScale.y + d3dmeshHeader->mPositionOffset.y;
						convertedVertexPosition.z = parsedVertexPosition.z * d3dmeshHeader->mPositionScale.z + d3dmeshHeader->mPositionOffset.z;
						convertedVertexPosition.w = 0;

						vertexPositions.push_back(convertedVertexPosition);
					}
				}
				else
				{
					std::cout << "SKIPPING DATA IN VERTEX BUFFER!" << d3dmeshHeader->mName << std::endl;
					ReadByteBufferFromBinary(inputFileStream, mVertexBuffer->mCount * mVertexBuffer->mStride); //skip this data block
				}
			}
			//||||||||||||||||||||||||||||||||||||| VERTEX NORMAL |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX NORMAL |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX NORMAL |||||||||||||||||||||||||||||||||||||
			else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Normal)
			{
				vertexNormalsCount++;

				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_SN8x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector4 parsedVertexNormal = ReadT3GFXBuffer_Normalized_4x8BitInteger(inputFileStream);

						//SELF NOTE: DIVIDING BY THE W COMPONENT WILL CREATE VECTORS OF INFINITY/NAN VALUES, SO DONT DO IT!
						Vector4 convertedVertexNormal;
						convertedVertexNormal.x = parsedVertexNormal.x;
						convertedVertexNormal.y = parsedVertexNormal.y;
						convertedVertexNormal.z = parsedVertexNormal.z;
						convertedVertexNormal.w = parsedVertexNormal.w;

						if (vertexNormalsCount == 1)
							vertexNormals0.push_back(convertedVertexNormal);
						if (vertexNormalsCount == 2)
							vertexNormals1.push_back(convertedVertexNormal);
						if (vertexNormalsCount == 3)
							vertexNormals2.push_back(convertedVertexNormal);
						if (vertexNormalsCount == 4)
							vertexNormals3.push_back(convertedVertexNormal);
					}
				}
				else
				{
					std::cout << "SKIPPING DATA IN VERTEX BUFFER!" << d3dmeshHeader->mName << std::endl;
					ReadByteBufferFromBinary(inputFileStream, mVertexBuffer->mCount * mVertexBuffer->mStride); //skip this data block
				}
			}
			//||||||||||||||||||||||||||||||||||||| VERTEX TANGENT |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX TANGENT |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX TANGENT |||||||||||||||||||||||||||||||||||||
			else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Tangent)
			{
				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_SN8x4 && vertexTangents.size() <= 0)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector4 parsedVertexTangent = ReadT3GFXBuffer_Normalized_4x8BitInteger(inputFileStream);

						//SELF NOTE: DIVIDING BY THE W COMPONENT WILL CREATE VECTORS OF INFINITY/NAN VALUES, SO DONT DO IT!
						Vector4 convertedVertexTangent;
						convertedVertexTangent.x = parsedVertexTangent.x;
						convertedVertexTangent.y = parsedVertexTangent.y;
						convertedVertexTangent.z = parsedVertexTangent.z;
						convertedVertexTangent.w = parsedVertexTangent.w;

						vertexTangents.push_back(convertedVertexTangent);
					}
				}
				else
				{
					std::cout << "SKIPPING DATA IN VERTEX BUFFER!" << d3dmeshHeader->mName << std::endl;
					ReadByteBufferFromBinary(inputFileStream, mVertexBuffer->mCount * mVertexBuffer->mStride); //skip this data block
				}
			}
			//||||||||||||||||||||||||||||||||||||| VERTEX UV |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX UV |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX UV |||||||||||||||||||||||||||||||||||||
			else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_TexCoord)
			{
				vertexUVsCount++;

				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x2)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector2 parsedVertexUV = ReadT3GFXBuffer_2x32BitFloat(inputFileStream);

						if (vertexUVsCount == 1)
							vertexUVs0.push_back(Vector4(parsedVertexUV.x, parsedVertexUV.y, 0, 0));
						if (vertexUVsCount == 2)
							vertexUVs1.push_back(Vector4(parsedVertexUV.x, parsedVertexUV.y, 0, 0));
						if (vertexUVsCount == 3)
							vertexUVs2.push_back(Vector4(parsedVertexUV.x, parsedVertexUV.y, 0, 0));
						if (vertexUVsCount == 4)
							vertexUVs3.push_back(Vector4(parsedVertexUV.x, parsedVertexUV.y, 0, 0));
						if (vertexUVsCount == 5)
							vertexUVs4.push_back(Vector4(parsedVertexUV.x, parsedVertexUV.y, 0, 0));
						if (vertexUVsCount == 6)
							vertexUVs5.push_back(Vector4(parsedVertexUV.x, parsedVertexUV.y, 0, 0));
						if (vertexUVsCount == 7)
							vertexUVs6.push_back(Vector4(parsedVertexUV.x, parsedVertexUV.y, 0, 0));
						if (vertexUVsCount == 8)
							vertexUVs7.push_back(Vector4(parsedVertexUV.x, parsedVertexUV.y, 0, 0));
					}
				}
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_SN16x2)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector2 parsedVertexUV = ReadT3GFXBuffer_Normalized_2x16BitInteger(inputFileStream);

						if (vertexUVsCount == 1)
							vertexUVs0.push_back(Vector4(parsedVertexUV.x, parsedVertexUV.y, 0, 0));
						if (vertexUVsCount == 2)
							vertexUVs1.push_back(Vector4(parsedVertexUV.x, parsedVertexUV.y, 0, 0));
						if (vertexUVsCount == 3)
							vertexUVs2.push_back(Vector4(parsedVertexUV.x, parsedVertexUV.y, 0, 0));
						if (vertexUVsCount == 4)
							vertexUVs3.push_back(Vector4(parsedVertexUV.x, parsedVertexUV.y, 0, 0));
						if (vertexUVsCount == 5)
							vertexUVs4.push_back(Vector4(parsedVertexUV.x, parsedVertexUV.y, 0, 0));
						if (vertexUVsCount == 6)
							vertexUVs5.push_back(Vector4(parsedVertexUV.x, parsedVertexUV.y, 0, 0));
						if (vertexUVsCount == 7)
							vertexUVs6.push_back(Vector4(parsedVertexUV.x, parsedVertexUV.y, 0, 0));
						if (vertexUVsCount == 8)
							vertexUVs7.push_back(Vector4(parsedVertexUV.x, parsedVertexUV.y, 0, 0));
					}
				}
				else
				{
					std::cout << "SKIPPING DATA IN VERTEX BUFFER!" << d3dmeshHeader->mName << std::endl;
					ReadByteBufferFromBinary(inputFileStream, mVertexBuffer->mCount * mVertexBuffer->mStride); //skip this data block
				}
			}
			//||||||||||||||||||||||||||||||||||||| VERTEX COLOR |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX COLOR |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX COLOR |||||||||||||||||||||||||||||||||||||
			else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Color)
			{
				vertexColorsCount++;

				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_UN8x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector4 parsedVertexColor = ReadT3GFXBuffer_UnsignedNormalized_4x8BitInteger(inputFileStream);

						if (vertexColorsCount == 1)
							vertexColors0.push_back(parsedVertexColor);
						if (vertexColorsCount == 2)
							vertexColors1.push_back(parsedVertexColor);
						if (vertexColorsCount == 3)
							vertexColors2.push_back(parsedVertexColor);
						if (vertexColorsCount == 4)
							vertexColors3.push_back(parsedVertexColor);
						if (vertexColorsCount == 5)
							vertexColors4.push_back(parsedVertexColor);
						if (vertexColorsCount == 6)
							vertexColors5.push_back(parsedVertexColor);
						if (vertexColorsCount == 7)
							vertexColors6.push_back(parsedVertexColor);
						if (vertexColorsCount == 8)
							vertexColors7.push_back(parsedVertexColor);
					}
				}
				else
				{
					std::cout << "SKIPPING DATA IN VERTEX BUFFER!" << d3dmeshHeader->mName << std::endl;
					ReadByteBufferFromBinary(inputFileStream, mVertexBuffer->mCount * mVertexBuffer->mStride); //skip this data block
				}
			}
			//||||||||||||||||||||||||||||||||||||| VERTEX BLEND INDEX |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX BLEND INDEX |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX BLEND INDEX |||||||||||||||||||||||||||||||||||||
			else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_BlendIndex)
			{
				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_U8x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						UnsignedIntegerVector4 parsedVertexBlendIndex = ReadT3GFXBuffer_Unsigned_4x8BitInteger(inputFileStream);

						vertexBlendIndex0.push_back(parsedVertexBlendIndex);
					}
				}
				else
				{
					std::cout << "SKIPPING DATA IN VERTEX BUFFER!" << d3dmeshHeader->mName << std::endl;
					ReadByteBufferFromBinary(inputFileStream, mVertexBuffer->mCount * mVertexBuffer->mStride); //skip this data block
				}
			}
			//||||||||||||||||||||||||||||||||||||| VERTEX BLEND WEIGHT |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX BLEND WEIGHT |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX BLEND WEIGHT |||||||||||||||||||||||||||||||||||||
			else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_BlendWeight)
			{
				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_UN10x3_UN2)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector3 parsedVertexBlendWeight = ReadT3GFXBuffer_UnsignedNormalized_3x10BitInteger_2BitInteger(inputFileStream, d3dmeshHeader->mPositionWScale);

						vertexBlendWeight0.push_back(Vector4(parsedVertexBlendWeight.x, parsedVertexBlendWeight.y, parsedVertexBlendWeight.z, 0));
					}
				}
				else
				{
					std::cout << "SKIPPING DATA IN VERTEX BUFFER!" << d3dmeshHeader->mName << std::endl;
					ReadByteBufferFromBinary(inputFileStream, mVertexBuffer->mCount * mVertexBuffer->mStride); //skip this data block
				}
			}
			//||||||||||||||||||||||||||||||||||||| SKIP |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| SKIP |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| SKIP |||||||||||||||||||||||||||||||||||||
			else
			{
				std::cout << "SKIPPING DATA IN VERTEX BUFFER!" << d3dmeshHeader->mName << std::endl;
				ReadByteBufferFromBinary(inputFileStream, mVertexBuffer->mCount * mVertexBuffer->mStride); //skip this data block
			}
		}
		//*/
	};

	void BinarySerialize(std::ofstream* outputFileStream, TelltaleD3DMeshHeaderV55* d3dmeshHeader)
	{
		indexBufferCount = 0;
		vertexNormalsCount = 0;
		vertexUVsCount = 0;
		vertexColorsCount = 0;

		//|||||||||||||||||||||||||||||||||||||||| D3DMESH BUFFER DATA - mIndexBuffers ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| D3DMESH BUFFER DATA - mIndexBuffers ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| D3DMESH BUFFER DATA - mIndexBuffers ||||||||||||||||||||||||||||||||||||||||

		for (int i = 0; i < d3dmeshHeader->mIndexBuffers.size(); i++)
		{
			//reference to the main index buffer that we are currently on
			T3GFXBuffer* mIndexBuffer = &d3dmeshHeader->mIndexBuffers[i];

			switch (mIndexBuffer->mBufferFormat)
			{
			case GFXPlatformFormat::eGFXPlatformFormat_U16:
				for (int j = 0; j < mIndexBuffer->mCount; j++)
				{
					if (indexBufferCount == 0)
						WriteUInt16ToBinary(outputFileStream, indexBuffer0[j]);
					else if (indexBufferCount == 1)
						WriteUInt16ToBinary(outputFileStream, indexBuffer1[j]);
					else if (indexBufferCount == 2)
						WriteUInt16ToBinary(outputFileStream, indexBuffer2[j]);
					else if (indexBufferCount == 3)
						WriteUInt16ToBinary(outputFileStream, indexBuffer3[j]);
					else if (indexBufferCount == 4)
						WriteUInt16ToBinary(outputFileStream, indexBuffer4[j]);
					else if (indexBufferCount == 5)
						WriteUInt16ToBinary(outputFileStream, indexBuffer5[j]);
					else if (indexBufferCount == 6)
						WriteUInt16ToBinary(outputFileStream, indexBuffer6[j]);
					else if (indexBufferCount == 7)
						WriteUInt16ToBinary(outputFileStream, indexBuffer7[j]);
				}

				indexBufferCount++;

				break;
			default:
				break;
			}
		}

		//|||||||||||||||||||||||||||||||||||||||| D3DMESH DATA - mVertexBuffers ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| D3DMESH DATA - mVertexBuffers ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| D3DMESH DATA - mVertexBuffers ||||||||||||||||||||||||||||||||||||||||

		/*
		for (int i = 0; i < d3dmeshHeader->mVertexBuffers.size(); i++)
		{
			T3GFXBuffer* mVertexBuffer = &d3dmeshHeader->mVertexBuffers[i];
			GFXPlatformAttributeParams* attributeParams = &d3dmeshHeader->GFXPlatformAttributeParamsArray[i];

			//||||||||||||||||||||||||||||||||||||| VERTEX POSITION |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX POSITION |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX POSITION |||||||||||||||||||||||||||||||||||||
			if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Position)
			{
				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_UN16x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector4 convertedVertexPosition;
						convertedVertexPosition.x = (vertexPositions[j].x - d3dmeshHeader->mPositionOffset.x) / d3dmeshHeader->mPositionScale.x;
						convertedVertexPosition.y = (vertexPositions[j].y - d3dmeshHeader->mPositionOffset.y) / d3dmeshHeader->mPositionScale.y;
						convertedVertexPosition.z = (vertexPositions[j].z - d3dmeshHeader->mPositionOffset.z) / d3dmeshHeader->mPositionScale.z;
						convertedVertexPosition.w = vertexPositions[j].w;
						WriteT3GFXBuffer_UnsignedNormalized_4x16BitInteger(outputFileStream, convertedVertexPosition);
					}
				}
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_UN10x3_UN2)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector3 convertedVertexPosition = Vector3(vertexPositions[j].x, vertexPositions[j].y, vertexPositions[j].z);
						convertedVertexPosition.x = (vertexPositions[j].x - d3dmeshHeader->mPositionOffset.x) / d3dmeshHeader->mPositionScale.x;
						convertedVertexPosition.y = (vertexPositions[j].y - d3dmeshHeader->mPositionOffset.y) / d3dmeshHeader->mPositionScale.y;
						convertedVertexPosition.z = (vertexPositions[j].z - d3dmeshHeader->mPositionOffset.z) / d3dmeshHeader->mPositionScale.z;
						WriteT3GFXBuffer_UnsignedNormalized_3x10BitInteger_2BitInteger(outputFileStream, convertedVertexPosition, d3dmeshHeader->mPositionWScale);
					}
				}
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x3)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector3 convertedVertexPosition = Vector3(vertexPositions[j].x, vertexPositions[j].y, vertexPositions[j].z);
						convertedVertexPosition.x = (vertexPositions[j].x - d3dmeshHeader->mPositionOffset.x) / d3dmeshHeader->mPositionScale.x;
						convertedVertexPosition.y = (vertexPositions[j].y - d3dmeshHeader->mPositionOffset.y) / d3dmeshHeader->mPositionScale.y;
						convertedVertexPosition.z = (vertexPositions[j].z - d3dmeshHeader->mPositionOffset.z) / d3dmeshHeader->mPositionScale.z;
						WriteT3GFXBuffer_3x32BitFloat(outputFileStream, convertedVertexPosition);
					}
				}
			}
			//||||||||||||||||||||||||||||||||||||| VERTEX NORMAL |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX NORMAL |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX NORMAL |||||||||||||||||||||||||||||||||||||
			else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Normal)
			{
				vertexNormalsCount++;

				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_SN8x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector4 originalVertexNormal{};

						if (vertexNormalsCount == 1)
							originalVertexNormal = vertexNormals0[j];
						if (vertexNormalsCount == 2)
							originalVertexNormal = vertexNormals1[j];
						if (vertexNormalsCount == 3)
							originalVertexNormal = vertexNormals2[j];
						if (vertexNormalsCount == 4)
							originalVertexNormal = vertexNormals3[j];

						Vector4 convertedVertexNormal;
						convertedVertexNormal.x = originalVertexNormal.x;
						convertedVertexNormal.y = originalVertexNormal.y;
						convertedVertexNormal.z = originalVertexNormal.z;
						convertedVertexNormal.w = originalVertexNormal.w;
						WriteT3GFXBuffer_Normalized_4x8BitInteger(outputFileStream, convertedVertexNormal);
					}
				}
			}

			//||||||||||||||||||||||||||||||||||||| VERTEX TANGENT |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX TANGENT |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX TANGENT |||||||||||||||||||||||||||||||||||||
			else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Tangent)
			{
				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_SN8x4 && vertexTangents.size() <= 0)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector4 convertedVertexNormal;
						convertedVertexNormal.x = vertexTangents[j].x;
						convertedVertexNormal.y = vertexTangents[j].y;
						convertedVertexNormal.z = vertexTangents[j].z;
						convertedVertexNormal.w = vertexTangents[j].w;
						WriteT3GFXBuffer_Normalized_4x8BitInteger(outputFileStream, convertedVertexNormal);
					}
				}
			}
			//||||||||||||||||||||||||||||||||||||| VERTEX UV |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX UV |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX UV |||||||||||||||||||||||||||||||||||||
			else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_TexCoord)
			{
				vertexUVsCount++;

				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x2)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector4 originalVertexUV{};

						if (vertexUVsCount == 1)
							originalVertexUV = vertexUVs0[j];
						if (vertexUVsCount == 2)
							originalVertexUV = vertexUVs1[j];
						if (vertexUVsCount == 3)
							originalVertexUV = vertexUVs2[j];
						if (vertexUVsCount == 4)
							originalVertexUV = vertexUVs3[j];
						if (vertexUVsCount == 5)
							originalVertexUV = vertexUVs4[j];
						if (vertexUVsCount == 6)
							originalVertexUV = vertexUVs5[j];
						if (vertexUVsCount == 7)
							originalVertexUV = vertexUVs6[j];
						if (vertexUVsCount == 8)
							originalVertexUV = vertexUVs7[j];

						WriteT3GFXBuffer_2x32BitFloat(outputFileStream, Vector2(originalVertexUV.x, originalVertexUV.y));
					}
				}
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_SN16x2)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector4 originalVertexUV{};

						if (vertexUVsCount == 1)
							originalVertexUV = vertexUVs0[j];
						if (vertexUVsCount == 2)
							originalVertexUV = vertexUVs1[j];
						if (vertexUVsCount == 3)
							originalVertexUV = vertexUVs2[j];
						if (vertexUVsCount == 4)
							originalVertexUV = vertexUVs3[j];
						if (vertexUVsCount == 5)
							originalVertexUV = vertexUVs4[j];
						if (vertexUVsCount == 6)
							originalVertexUV = vertexUVs5[j];
						if (vertexUVsCount == 7)
							originalVertexUV = vertexUVs6[j];
						if (vertexUVsCount == 8)
							originalVertexUV = vertexUVs7[j];

						WriteT3GFXBuffer_Normalized_2x16BitInteger(outputFileStream, Vector2(originalVertexUV.x, originalVertexUV.y));
					}
				}
			}
			//||||||||||||||||||||||||||||||||||||| VERTEX COLOR |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX COLOR |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX COLOR |||||||||||||||||||||||||||||||||||||
			else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Color)
			{
				vertexColorsCount++;

				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_UN8x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector4 originalVertexColor{};

						if (vertexColorsCount == 1)
							originalVertexColor = vertexColors0[j];
						if (vertexColorsCount == 2)
							originalVertexColor = vertexColors1[j];
						if (vertexColorsCount == 3)
							originalVertexColor = vertexColors2[j];
						if (vertexColorsCount == 4)
							originalVertexColor = vertexColors3[j];
						if (vertexColorsCount == 5)
							originalVertexColor = vertexColors4[j];
						if (vertexColorsCount == 6)
							originalVertexColor = vertexColors5[j];
						if (vertexColorsCount == 7)
							originalVertexColor = vertexColors6[j];
						if (vertexColorsCount == 8)
							originalVertexColor = vertexColors7[j];

						WriteT3GFXBuffer_UnsignedNormalized_4x8BitInteger(outputFileStream, originalVertexColor);
					}
				}
			}
			//||||||||||||||||||||||||||||||||||||| VERTEX BLEND INDEX |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX BLEND INDEX |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX BLEND INDEX |||||||||||||||||||||||||||||||||||||
			else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_BlendIndex)
			{
				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_U8x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						WriteT3GFXBuffer_Unsigned_4x8BitInteger(outputFileStream, vertexBlendIndex0[j]);
					}
				}
			}
			//||||||||||||||||||||||||||||||||||||| VERTEX BLEND WEIGHT |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX BLEND WEIGHT |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX BLEND WEIGHT |||||||||||||||||||||||||||||||||||||
			else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_BlendWeight)
			{
				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_UN10x3_UN2)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						WriteT3GFXBuffer_UnsignedNormalized_3x10BitInteger_2BitInteger(outputFileStream, Vector3(vertexBlendWeight0[j].x, vertexBlendWeight0[j].y, vertexBlendWeight0[j].z), d3dmeshHeader->mPositionWScale);
					}
				}
			}
		}
		*/
	};
};

#endif
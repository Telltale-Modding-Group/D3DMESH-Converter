#pragma once
#ifndef TELLTALE_D3DMESH_DATA_55_H
#define TELLTALE_D3DMESH_DATA_55_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "../../BinarySerialization.h"
#include "../../BinaryDeserialization.h"
#include "../../Json.h"
#include "../../Telltale/T3GFXBufferDeserialization.h"
#include "../../Telltale/T3GFXBufferSerialization.h"
#include "../../Telltale/DataTypes/Symbol.h"
#include "../../Telltale/DataTypes/Vector2.h"
#include "../../Telltale/DataTypes/Vector3.h"
#include "../../Telltale/DataTypes/Vector4.h"
#include "../../Telltale/DataTypes/TelltaleInternalResource.h"
#include "../../Telltale/DataTypes/T3MeshLOD.h"
#include "../../Telltale/DataTypes/T3MeshBoneEntry.h"
#include "../../Telltale/DataTypes/T3MeshLocalTransformEntry.h"
#include "../../Telltale/DataTypes/T3MaterialRequirements.h"
#include "../../Telltale/DataTypes/T3GFXBuffer.h"
#include "../../Telltale/DataTypes/GFXPlatformAttributeParams.h"
#include "../../Telltale/DataTypes/TelltaleD3DMeshHeaderV55.h"
#include "../../CustomTypes/UnsignedIntegerVector4.h"

//||||||||||||||||||||||||||||| TELLTALE D3DMESH DATA V55 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE D3DMESH DATA V55 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE D3DMESH DATA V55 |||||||||||||||||||||||||||||

struct TelltaleD3DMeshDataV55
{
	std::vector<std::vector<unsigned short>> indexBuffers;

	//NOTE: Most of these types are not actually a "Vector4"
	//However in certain circumstances depending on the format used for the buffer, they will return a 4 component value.
	//So to make sure we capture ALL of the possible data we will assume everything is a Vector4

	//NOTE: Models normally have 1 set of vertex normals, however in the case of telltale...
	//Most models actually have 2 sets of vertex normals
	//1. The main regular normal set
	//2. creased normal set?

	std::vector<std::vector<Vector4>> vertexPositions; //eGFXPlatformAttribute_Position (0)
	std::vector<std::vector<Vector4>> vertexNormals; //eGFXPlatformAttribute_Normal (1) 
	std::vector<std::vector<Vector4>> vertexTangents; //eGFXPlatformAttribute_Tangent (2) 
	std::vector<std::vector<Vector4>> vertexBlendWeight; //eGFXPlatformAttribute_BlendWeight (3)
	std::vector<std::vector<UnsignedIntegerVector4>> vertexBlendIndex; //eGFXPlatformAttribute_BlendIndex (4)
	std::vector<std::vector<Vector4>> vertexColors; //eGFXPlatformAttribute_Color (5) 
	std::vector<std::vector<Vector4>> vertexUVs; //eGFXPlatformAttribute_TexCoord (6)

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

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
			T3GFXBuffer* mIndexBuffer = &d3dmeshHeader->mIndexBuffers[i];

			std::vector<unsigned short> newIndexBuffer;

			switch (mIndexBuffer->mBufferFormat)
			{
				case GFXPlatformFormat::eGFXPlatformFormat_U16:
					//if (mIndexBuffer->mBufferUsage == 2) //eGFXPlatformBuffer_Index

					for (int j = 0; j < mIndexBuffer->mCount; j++)
						newIndexBuffer.push_back(ReadUInt16FromBinary(inputFileStream));

					indexBuffers.push_back(newIndexBuffer);
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
				std::vector<Vector4> newVertexPositions;

				//if (mVertexBuffer->mBufferFormat == GFXPlatformFormat::eGFXPlatformFormat_UN16x4)
				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_UN16x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector4 parsedVertexPosition = ReadT3GFXBuffer_UnsignedNormalized_4x16BitInteger(inputFileStream);

						Vector4 convertedVertexPosition;
						convertedVertexPosition.x = parsedVertexPosition.x * d3dmeshHeader->mPositionScale.x + d3dmeshHeader->mPositionOffset.x;
						convertedVertexPosition.y = parsedVertexPosition.y * d3dmeshHeader->mPositionScale.y + d3dmeshHeader->mPositionOffset.y;
						convertedVertexPosition.z = parsedVertexPosition.z * d3dmeshHeader->mPositionScale.z + d3dmeshHeader->mPositionOffset.z;
						convertedVertexPosition.w = parsedVertexPosition.w; //SELF NOTE: DIVIDING BY THE W COMPONENT WILL CREATE VECTORS OF INFINITY/NAN VALUES, SO DONT DO IT!
						newVertexPositions.push_back(convertedVertexPosition);
					}

					vertexPositions.push_back(newVertexPositions);
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
						newVertexPositions.push_back(convertedVertexPosition);
					}

					vertexPositions.push_back(newVertexPositions);
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
						newVertexPositions.push_back(convertedVertexPosition);
					}

					vertexPositions.push_back(newVertexPositions);
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
				std::vector<Vector4> newVertexNormals;

				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_SN8x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector4 parsedVertexNormal = ReadT3GFXBuffer_Normalized_4x8BitInteger(inputFileStream);

						Vector4 convertedVertexNormal;
						convertedVertexNormal.x = parsedVertexNormal.x;
						convertedVertexNormal.y = parsedVertexNormal.y;
						convertedVertexNormal.z = parsedVertexNormal.z;
						convertedVertexNormal.w = parsedVertexNormal.w; //SELF NOTE: DIVIDING BY THE W COMPONENT WILL CREATE VECTORS OF INFINITY/NAN VALUES, SO DONT DO IT!
						newVertexNormals.push_back(convertedVertexNormal);
					}

					vertexNormals.push_back(newVertexNormals);
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
				std::vector<Vector4> newVertexTangents;

				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_SN8x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector4 parsedVertexTangent = ReadT3GFXBuffer_Normalized_4x8BitInteger(inputFileStream);

						Vector4 convertedVertexTangent;
						convertedVertexTangent.x = parsedVertexTangent.x;
						convertedVertexTangent.y = parsedVertexTangent.y;
						convertedVertexTangent.z = parsedVertexTangent.z;
						convertedVertexTangent.w = parsedVertexTangent.w; //SELF NOTE: DIVIDING BY THE W COMPONENT WILL CREATE VECTORS OF INFINITY/NAN VALUES, SO DONT DO IT!
						newVertexTangents.push_back(convertedVertexTangent);
					}

					vertexTangents.push_back(newVertexTangents);
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
				std::vector<Vector4> newVertexUVs;

				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x2)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector2 parsedVertexUV = ReadT3GFXBuffer_2x32BitFloat(inputFileStream);
						newVertexUVs.push_back(Vector4(parsedVertexUV.x, parsedVertexUV.y, 0, 0));
					}

					vertexUVs.push_back(newVertexUVs);
				}
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_SN16x2)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector2 parsedVertexUV = ReadT3GFXBuffer_Normalized_2x16BitInteger(inputFileStream);
						newVertexUVs.push_back(Vector4(parsedVertexUV.x, parsedVertexUV.y, 0, 0));
					}

					vertexUVs.push_back(newVertexUVs);
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
				std::vector<Vector4> newVertexColors;

				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_UN8x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector4 parsedVertexColor = ReadT3GFXBuffer_UnsignedNormalized_4x8BitInteger(inputFileStream);
						newVertexColors.push_back(parsedVertexColor);
					}

					vertexColors.push_back(newVertexColors);
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
				std::vector<UnsignedIntegerVector4> newVertexBlendIndex;

				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_U8x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						UnsignedIntegerVector4 parsedVertexBlendIndex = ReadT3GFXBuffer_Unsigned_4x8BitInteger(inputFileStream);
						newVertexBlendIndex.push_back(parsedVertexBlendIndex);
					}

					vertexBlendIndex.push_back(newVertexBlendIndex);
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
				std::vector<Vector4> newVertexBlendWeights;

				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_UN10x3_UN2)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector3 parsedVertexBlendWeight = ReadT3GFXBuffer_UnsignedNormalized_3x10BitInteger_2BitInteger(inputFileStream, d3dmeshHeader->mPositionWScale);
						newVertexBlendWeights.push_back(Vector4(parsedVertexBlendWeight.x, parsedVertexBlendWeight.y, parsedVertexBlendWeight.z, 0));
					}

					vertexBlendWeight.push_back(newVertexBlendWeights);
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

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream, TelltaleD3DMeshHeaderV55* d3dmeshHeader)
	{
		//update values

		//NOTE: all vertex buffer sizes should be consistent

		//|||||||||||||||||||||||||||||||||||||||| D3DMESH BUFFER DATA - mIndexBuffers ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| D3DMESH BUFFER DATA - mIndexBuffers ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| D3DMESH BUFFER DATA - mIndexBuffers ||||||||||||||||||||||||||||||||||||||||

		for (int i = 0; i < d3dmeshHeader->mIndexBufferCount; i++)
		{
			T3GFXBuffer* mIndexBuffer = &d3dmeshHeader->mIndexBuffers[i];

			switch (mIndexBuffer->mBufferFormat)
			{
				case GFXPlatformFormat::eGFXPlatformFormat_U16:
					for (int j = 0; j < mIndexBuffer->mCount; j++)
						WriteUInt16ToBinary(outputFileStream, indexBuffers[i][j]);

					break;
				default:
					break;
			}
		}

		//|||||||||||||||||||||||||||||||||||||||| D3DMESH DATA - mVertexBuffers ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| D3DMESH DATA - mVertexBuffers ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| D3DMESH DATA - mVertexBuffers ||||||||||||||||||||||||||||||||||||||||

		int vertexPositionBufferIndex = 0; //vertexPositions
		int vertexNormalBufferIndex = 0; //vertexNormals
		int vertexTangentBufferIndex = 0; //vertexTangents
		int vertexBlendWeightBufferIndex = 0; //vertexBlendWeight
		int vertexBlendIndexBufferIndex = 0; //vertexBlendIndex
		int vertexColorBufferIndex = 0; //vertexColors
		int vertexUVBufferIndex = 0; //vertexUVs

		for (int i = 0; i < d3dmeshHeader->mAttributeCount; i++)
		{
			T3GFXBuffer* mVertexBuffer = &d3dmeshHeader->mVertexBuffers[i];
			GFXPlatformAttributeParams* attributeParams = &d3dmeshHeader->GFXPlatformAttributeParamsArray[i];

			//||||||||||||||||||||||||||||||||||||| VERTEX POSITION |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX POSITION |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX POSITION |||||||||||||||||||||||||||||||||||||
			if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Position)
			{
				std::vector<Vector4> currentVertexPositionsBuffer = vertexPositions[vertexPositionBufferIndex];

				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_UN16x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector4 convertedVertexPosition;
						convertedVertexPosition.x = (currentVertexPositionsBuffer[j].x - d3dmeshHeader->mPositionOffset.x) / d3dmeshHeader->mPositionScale.x;
						convertedVertexPosition.y = (currentVertexPositionsBuffer[j].y - d3dmeshHeader->mPositionOffset.y) / d3dmeshHeader->mPositionScale.y;
						convertedVertexPosition.z = (currentVertexPositionsBuffer[j].z - d3dmeshHeader->mPositionOffset.z) / d3dmeshHeader->mPositionScale.z;
						convertedVertexPosition.w = currentVertexPositionsBuffer[j].w;
						WriteT3GFXBuffer_UnsignedNormalized_4x16BitInteger(outputFileStream, convertedVertexPosition);
					}
				}
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_UN10x3_UN2)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector3 convertedVertexPosition = Vector3(currentVertexPositionsBuffer[j].x, currentVertexPositionsBuffer[j].y, currentVertexPositionsBuffer[j].z);
						convertedVertexPosition.x = (currentVertexPositionsBuffer[j].x - d3dmeshHeader->mPositionOffset.x) / d3dmeshHeader->mPositionScale.x;
						convertedVertexPosition.y = (currentVertexPositionsBuffer[j].y - d3dmeshHeader->mPositionOffset.y) / d3dmeshHeader->mPositionScale.y;
						convertedVertexPosition.z = (currentVertexPositionsBuffer[j].z - d3dmeshHeader->mPositionOffset.z) / d3dmeshHeader->mPositionScale.z;
						WriteT3GFXBuffer_UnsignedNormalized_3x10BitInteger_2BitInteger(outputFileStream, convertedVertexPosition, d3dmeshHeader->mPositionWScale);
					}
				}
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x3)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector3 convertedVertexPosition = Vector3(currentVertexPositionsBuffer[j].x, currentVertexPositionsBuffer[j].y, currentVertexPositionsBuffer[j].z);
						convertedVertexPosition.x = (currentVertexPositionsBuffer[j].x - d3dmeshHeader->mPositionOffset.x) / d3dmeshHeader->mPositionScale.x;
						convertedVertexPosition.y = (currentVertexPositionsBuffer[j].y - d3dmeshHeader->mPositionOffset.y) / d3dmeshHeader->mPositionScale.y;
						convertedVertexPosition.z = (currentVertexPositionsBuffer[j].z - d3dmeshHeader->mPositionOffset.z) / d3dmeshHeader->mPositionScale.z;
						WriteT3GFXBuffer_3x32BitFloat(outputFileStream, convertedVertexPosition);
					}
				}
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector4 convertedVertexPosition = Vector4(currentVertexPositionsBuffer[j].x, currentVertexPositionsBuffer[j].y, currentVertexPositionsBuffer[j].z, currentVertexPositionsBuffer[j].w);
						convertedVertexPosition.x = (currentVertexPositionsBuffer[j].x - d3dmeshHeader->mPositionOffset.x) / d3dmeshHeader->mPositionScale.x;
						convertedVertexPosition.y = (currentVertexPositionsBuffer[j].y - d3dmeshHeader->mPositionOffset.y) / d3dmeshHeader->mPositionScale.y;
						convertedVertexPosition.z = (currentVertexPositionsBuffer[j].z - d3dmeshHeader->mPositionOffset.z) / d3dmeshHeader->mPositionScale.z;
						WriteT3GFXBuffer_4x32BitFloat(outputFileStream, convertedVertexPosition);
					}
				}

				vertexPositionBufferIndex++;
			}
			//||||||||||||||||||||||||||||||||||||| VERTEX NORMAL |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX NORMAL |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX NORMAL |||||||||||||||||||||||||||||||||||||
			else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Normal)
			{
				std::vector<Vector4> currentVertexNormalsBuffer = vertexNormals[vertexNormalBufferIndex];

				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_SN8x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
						WriteT3GFXBuffer_Normalized_4x8BitInteger(outputFileStream, currentVertexNormalsBuffer[j]);
				}
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
						WriteT3GFXBuffer_4x32BitFloat(outputFileStream, currentVertexNormalsBuffer[j]);
				}

				vertexNormalBufferIndex++;
			}
			//||||||||||||||||||||||||||||||||||||| VERTEX TANGENT |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX TANGENT |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX TANGENT |||||||||||||||||||||||||||||||||||||
			else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Tangent)
			{
				std::vector<Vector4> currentVertexTangentsBuffer = vertexTangents[vertexTangentBufferIndex];

				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_SN8x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
						WriteT3GFXBuffer_Normalized_4x8BitInteger(outputFileStream, currentVertexTangentsBuffer[j]);
				}
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
						WriteT3GFXBuffer_4x32BitFloat(outputFileStream, currentVertexTangentsBuffer[j]);
				}

				vertexTangentBufferIndex++;
			}
			//||||||||||||||||||||||||||||||||||||| VERTEX BLEND WEIGHT |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX BLEND WEIGHT |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX BLEND WEIGHT |||||||||||||||||||||||||||||||||||||
			else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_BlendWeight)
			{
				std::vector<Vector4> currentVertexBlendWeightsBuffer = vertexBlendWeight[vertexBlendWeightBufferIndex];

				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_UN10x3_UN2)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
						WriteT3GFXBuffer_UnsignedNormalized_3x10BitInteger_2BitInteger(outputFileStream, Vector3(currentVertexBlendWeightsBuffer[j].x, currentVertexBlendWeightsBuffer[j].y, currentVertexBlendWeightsBuffer[j].z), d3dmeshHeader->mPositionWScale);
				}
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
						WriteT3GFXBuffer_4x32BitFloat(outputFileStream, currentVertexBlendWeightsBuffer[j]);
				}

				vertexBlendWeightBufferIndex++;
			}
			//||||||||||||||||||||||||||||||||||||| VERTEX BLEND INDEX |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX BLEND INDEX |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX BLEND INDEX |||||||||||||||||||||||||||||||||||||
			else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_BlendIndex)
			{
				std::vector<UnsignedIntegerVector4> currentVertexBlendIndexBuffer = vertexBlendIndex[vertexBlendIndexBufferIndex];

				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_U8x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
						WriteT3GFXBuffer_Unsigned_4x8BitInteger(outputFileStream, currentVertexBlendIndexBuffer[j]);
				}
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
						WriteT3GFXBuffer_4x32BitFloat(outputFileStream, Vector4(currentVertexBlendIndexBuffer[j].x, currentVertexBlendIndexBuffer[j].y, currentVertexBlendIndexBuffer[j].z, currentVertexBlendIndexBuffer[j].w));
				}

				vertexBlendIndexBufferIndex++;
			}
			//||||||||||||||||||||||||||||||||||||| VERTEX COLOR |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX COLOR |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX COLOR |||||||||||||||||||||||||||||||||||||
			else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Color)
			{
				std::vector<Vector4> currentVertexColorsBuffer = vertexColors[vertexColorBufferIndex];

				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_UN8x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
						WriteT3GFXBuffer_UnsignedNormalized_4x8BitInteger(outputFileStream, currentVertexColorsBuffer[j]);
				}
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
						WriteT3GFXBuffer_4x32BitFloat(outputFileStream, currentVertexColorsBuffer[j]);
				}

				vertexColorBufferIndex++;
			}
			//||||||||||||||||||||||||||||||||||||| VERTEX UV |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX UV |||||||||||||||||||||||||||||||||||||
			//||||||||||||||||||||||||||||||||||||| VERTEX UV |||||||||||||||||||||||||||||||||||||
			else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_TexCoord)
			{
				std::vector<Vector4> currentVertexUVsBuffer = vertexUVs[vertexUVBufferIndex];

				if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x2)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
						WriteT3GFXBuffer_2x32BitFloat(outputFileStream, Vector2(currentVertexUVsBuffer[j].x, currentVertexUVsBuffer[j].y));
				}
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_SN16x2)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
						WriteT3GFXBuffer_Normalized_2x16BitInteger(outputFileStream, Vector2(currentVertexUVsBuffer[j].x, currentVertexUVsBuffer[j].y));
				}
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x4)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
						WriteT3GFXBuffer_4x32BitFloat(outputFileStream, currentVertexUVsBuffer[j]);
				}

				vertexUVBufferIndex++;
			}
		}
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(
		TelltaleD3DMeshDataV55, 
		indexBuffers,
		vertexPositions, //eGFXPlatformAttribute_Position (0)
		vertexNormals, //eGFXPlatformAttribute_Normal (1) 
		vertexTangents, //eGFXPlatformAttribute_Tangent (2) 
		vertexBlendWeight, //eGFXPlatformAttribute_BlendWeight (3)
		vertexBlendIndex, //eGFXPlatformAttribute_BlendIndex (4)
		vertexColors, //eGFXPlatformAttribute_Color (5) 
		vertexUVs) //eGFXPlatformAttribute_TexCoord (6)
};

#endif
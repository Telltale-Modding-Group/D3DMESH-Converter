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

class TelltaleD3DMeshDataV55
{
public:

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

	std::vector<Vector3> vertexPositions;

	//NOTE: Models normally have 1 set of vertex normals, however in the case of telltale...
	//Most models actually have 2 sets of vertex normals
	//1. The main regular normal set
	//2. creased normal set?
	std::vector<Vector3> vertexNormals0;
	std::vector<Vector3> vertexNormals1;
	std::vector<Vector3> vertexNormals2;
	std::vector<Vector3> vertexNormals3;

	std::vector<Vector3> vertexTangents;

	std::vector<Vector2> vertexUVs0;
	std::vector<Vector2> vertexUVs1;
	std::vector<Vector2> vertexUVs2;
	std::vector<Vector2> vertexUVs3;
	std::vector<Vector2> vertexUVs4;
	std::vector<Vector2> vertexUVs5;
	std::vector<Vector2> vertexUVs6;
	std::vector<Vector2> vertexUVs7;

	std::vector<Vector4> vertexColors0;
	std::vector<Vector4> vertexColors1;
	std::vector<Vector4> vertexColors2;
	std::vector<Vector4> vertexColors3;
	std::vector<Vector4> vertexColors4;
	std::vector<Vector4> vertexColors5;
	std::vector<Vector4> vertexColors6;
	std::vector<Vector4> vertexColors7;

	std::vector<UnsignedIntegerVector4> vertexBlendIndex0;

	std::vector<Vector3> vertexBlendWeight0;

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

				std::cout << "Index Buffer: " << indexBufferCount << " | mIndexBuffer->mBufferUsage: " << mIndexBuffer->mBufferUsage << std::endl;

				indexBufferCount++;

				break;
			default:
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
						Vector3 convertedVertexPosition;
						convertedVertexPosition.x = parsedVertexPosition.x * d3dmeshHeader->mPositionScale.x + d3dmeshHeader->mPositionOffset.x;
						convertedVertexPosition.y = parsedVertexPosition.y * d3dmeshHeader->mPositionScale.y + d3dmeshHeader->mPositionOffset.y;
						convertedVertexPosition.z = parsedVertexPosition.z * d3dmeshHeader->mPositionScale.z + d3dmeshHeader->mPositionOffset.z;

						vertexPositions.push_back(convertedVertexPosition);
					}
				}
				//else if (mVertexBuffer->mBufferFormat == GFXPlatformFormat::eGFXPlatformFormat_UN10x3_UN2)
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_UN10x3_UN2)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector3 parsedVertexPosition = ReadT3GFXBuffer_UnsignedNormalized_3x10BitInteger_2BitInteger(inputFileStream, d3dmeshHeader->mPositionWScale);

						Vector3 convertedVertexPosition;
						convertedVertexPosition.x = parsedVertexPosition.x * d3dmeshHeader->mPositionScale.x + d3dmeshHeader->mPositionOffset.x;
						convertedVertexPosition.y = parsedVertexPosition.y * d3dmeshHeader->mPositionScale.y + d3dmeshHeader->mPositionOffset.y;
						convertedVertexPosition.z = parsedVertexPosition.z * d3dmeshHeader->mPositionScale.z + d3dmeshHeader->mPositionOffset.z;

						vertexPositions.push_back(convertedVertexPosition);
					}
				}
				//else if (mVertexBuffer->mBufferFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x3)
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x3)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector3 parsedVertexPosition = ReadT3GFXBuffer_3x32BitFloat(inputFileStream);

						Vector3 convertedVertexPosition;
						convertedVertexPosition.x = parsedVertexPosition.x * d3dmeshHeader->mPositionScale.x + d3dmeshHeader->mPositionOffset.x;
						convertedVertexPosition.y = parsedVertexPosition.y * d3dmeshHeader->mPositionScale.y + d3dmeshHeader->mPositionOffset.y;
						convertedVertexPosition.z = parsedVertexPosition.z * d3dmeshHeader->mPositionScale.z + d3dmeshHeader->mPositionOffset.z;

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
						Vector3 convertedVertexNormal;
						convertedVertexNormal.x = parsedVertexNormal.x;
						convertedVertexNormal.y = parsedVertexNormal.y;
						convertedVertexNormal.z = parsedVertexNormal.z;

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
						Vector3 convertedVertexTangent;
						convertedVertexTangent.x = parsedVertexTangent.x;
						convertedVertexTangent.y = parsedVertexTangent.y;
						convertedVertexTangent.z = parsedVertexTangent.z;

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
							vertexUVs0.push_back(parsedVertexUV);
						if (vertexUVsCount == 2)
							vertexUVs1.push_back(parsedVertexUV);
						if (vertexUVsCount == 3)
							vertexUVs2.push_back(parsedVertexUV);
						if (vertexUVsCount == 4)
							vertexUVs3.push_back(parsedVertexUV);
						if (vertexUVsCount == 5)
							vertexUVs4.push_back(parsedVertexUV);
						if (vertexUVsCount == 6)
							vertexUVs5.push_back(parsedVertexUV);
						if (vertexUVsCount == 7)
							vertexUVs6.push_back(parsedVertexUV);
						if (vertexUVsCount == 8)
							vertexUVs7.push_back(parsedVertexUV);
					}
				}
				else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_SN16x2)
				{
					for (int j = 0; j < mVertexBuffer->mCount; j++)
					{
						Vector2 parsedVertexUV = ReadT3GFXBuffer_Normalized_2x16BitInteger(inputFileStream);

						if (vertexUVsCount == 1)
							vertexUVs0.push_back(parsedVertexUV);
						if (vertexUVsCount == 2)
							vertexUVs1.push_back(parsedVertexUV);
						if (vertexUVsCount == 3)
							vertexUVs2.push_back(parsedVertexUV);
						if (vertexUVsCount == 4)
							vertexUVs3.push_back(parsedVertexUV);
						if (vertexUVsCount == 5)
							vertexUVs4.push_back(parsedVertexUV);
						if (vertexUVsCount == 6)
							vertexUVs5.push_back(parsedVertexUV);
						if (vertexUVsCount == 7)
							vertexUVs6.push_back(parsedVertexUV);
						if (vertexUVsCount == 8)
							vertexUVs7.push_back(parsedVertexUV);
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

						vertexBlendWeight0.push_back(parsedVertexBlendWeight);
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

	void BinarySerialize(std::ofstream* outputFileStream)
	{

	};
};

#endif
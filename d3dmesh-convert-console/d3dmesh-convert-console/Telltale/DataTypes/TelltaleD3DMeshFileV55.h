#pragma once
#ifndef TELLTALE_D3DMESH_FILE_55_H
#define TELLTALE_D3DMESH_FILE_55_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Custom
#include "../../Binary/BinarySerialization.h"
#include "../../Binary/BinaryDeserialization.h"
#include "../../Helper/JsonHelper.h"
#include "../../Telltale/DataTypes/TelltaleMetaHeaderVersion6.h"
#include "../../Telltale/DataTypes/TelltaleD3DMeshHeaderV55.h"
#include "../../Telltale/DataTypes/TelltaleD3DMeshDataV55.h"

//||||||||||||||||||||||||||||| TELLTALE D3DMESH FILE V55 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE D3DMESH FILE V55 |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE D3DMESH FILE V55 |||||||||||||||||||||||||||||

class TelltaleD3DMeshFileV55
{
public:
	TelltaleMetaHeaderVersion6 metaHeader;
	TelltaleD3DMeshHeaderV55 d3dmeshHeader;
	TelltaleD3DMeshDataV55 d3dmeshData;

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

	TelltaleD3DMeshFileV55()
	{

	};

	TelltaleD3DMeshFileV55(std::ifstream* inputFileStream)
	{
		//telltale files always have a "meta" header serialized ontop of the file
		//this header is important as it tells the engine (and us) the size of the d3dmesh header, and the size of the file data after the headers.
		//it also contains misc information like the reference class names and types, which are hashed (CRC64)
		metaHeader = TelltaleMetaHeaderVersion6(inputFileStream);

		//we finished going through the meta header, so the offset we left off at matches the size of the meta header
		unsigned long metaHeaderSize = inputFileStream->tellg();

		//std::cout << metaHeader.ToString() << std::endl;

		//here we get into the important parts of the file.
		//after parsing the meta header, the main d3dmesh header is serialized right after it
		//this is the most important part as it contains all of the necessary information about the mesh so that we can read/extract it properly.
		d3dmeshHeader = TelltaleD3DMeshHeaderV55(inputFileStream);

		//std::cout << d3dmeshHeader.ToString() << std::endl;

		//here after reading the header, the actual mesh data is serialized right after it, using what we know from the header we pull the data accordingly here.
		d3dmeshData = TelltaleD3DMeshDataV55(inputFileStream, &d3dmeshHeader);

		//We have (hopefully) reached the end of the file!
		//print output so we can check if we actually reached the end of the file. If we did then the bytes left to traverse in the file should be 0.
		unsigned long long totalFileSizeCalculation = metaHeaderSize + metaHeader.mDefaultSectionChunkSize + metaHeader.mAsyncSectionChunkSize;
		unsigned long long currentSeekPosition = inputFileStream->tellg();
		long bytesLeftInFile = (long)(totalFileSizeCalculation - currentSeekPosition);

		if(bytesLeftInFile > 0)
			std::cout << "[READER INFO] |||||||||||||||||||||||||||||||| DID NOT REACH END OF FILE! Bytes Left To Traverse In File: " << bytesLeftInFile << std::endl;
	};

	//||||||||||||||||||||||||||||| GET BOOLEANS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| GET BOOLEANS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| GET BOOLEANS |||||||||||||||||||||||||||||

	bool HasBones() 
	{
		for (int i = 0; i < d3dmeshHeader.mLODs_ArrayLength; i++)
		{
			if (d3dmeshHeader.mLODs[i].mBones_ArrayLength > 0)
				return true;
		}

		return false;
	}

	bool HasIndexBuffers()
	{
		return d3dmeshData.indexBuffers.size() > 0;
	}

	bool HasVertexPositions() 
	{
		return d3dmeshData.vertexPositions.size() > 0;
	}

	bool HasVertexNormals()
	{
		return d3dmeshData.vertexNormals.size() > 0;
	}

	bool HasVertexTangents()
	{
		return d3dmeshData.vertexTangents.size() > 0;
	}

	bool HasVertexColors()
	{
		return d3dmeshData.vertexColors.size() > 0;
	}

	bool HasVertexUVs()
	{
		return d3dmeshData.vertexUVs.size() > 0;
	}

	bool HasVertexBlendWeights()
	{
		return d3dmeshData.vertexBlendWeight.size() > 0;
	}

	bool HasVertexBlendIndexes()
	{
		return d3dmeshData.vertexBlendIndex.size() > 0;
	}

	//||||||||||||||||||||||||||||| GET INTS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| GET INTS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| GET INTS |||||||||||||||||||||||||||||

	unsigned int GetAmountOfIndexBuffers()
	{
		return d3dmeshData.indexBuffers.size();
	}

	unsigned int GetAmountOfVertexPositions()
	{
		return d3dmeshData.vertexPositions.size();
	}

	unsigned int GetAmountOfVertexNormals()
	{
		return d3dmeshData.vertexNormals.size();
	}

	unsigned int GetAmountOfVertexTangents()
	{
		return d3dmeshData.vertexTangents.size();
	}

	unsigned int GetAmountOfVertexColors()
	{
		return d3dmeshData.vertexColors.size();
	}

	unsigned int GetAmountOfVertexUVs()
	{
		return d3dmeshData.vertexUVs.size();
	}

	unsigned int GetAmountOfVertexBlendWeights()
	{
		return d3dmeshData.vertexBlendWeight.size();
	}

	unsigned int GetAmountOfVertexBlendIndexes()
	{
		return d3dmeshData.vertexBlendIndex.size();
	}

	unsigned int GetTotalTriangleCount()
	{
		if (d3dmeshData.indexBuffers.size() > 0)
			return d3dmeshData.indexBuffers[0].size();
		else
			return 0;
	}

	unsigned int GetTotalVertexCount()
	{
		if (d3dmeshData.vertexPositions.size() > 0)
			return d3dmeshData.vertexPositions[0].size();
		else
			return 0;
	}

	//||||||||||||||||||||||||||||| METHODS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| METHODS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| METHODS |||||||||||||||||||||||||||||

	void EraseIndexBufferMeshData()
	{
		d3dmeshData.indexBuffers.erase(d3dmeshData.indexBuffers.begin(), d3dmeshData.indexBuffers.end());
	}

	void EraseVertexBufferMeshData() 
	{
		d3dmeshData.vertexPositions.erase(d3dmeshData.vertexPositions.begin(), d3dmeshData.vertexPositions.end());
		d3dmeshData.vertexNormals.erase(d3dmeshData.vertexNormals.begin(), d3dmeshData.vertexNormals.end());
		d3dmeshData.vertexTangents.erase(d3dmeshData.vertexTangents.begin(), d3dmeshData.vertexTangents.end());
		d3dmeshData.vertexUVs.erase(d3dmeshData.vertexUVs.begin(), d3dmeshData.vertexUVs.end());
		d3dmeshData.vertexColors.erase(d3dmeshData.vertexColors.begin(), d3dmeshData.vertexColors.end());
		d3dmeshData.vertexBlendWeight.erase(d3dmeshData.vertexBlendWeight.begin(), d3dmeshData.vertexBlendWeight.end());
		d3dmeshData.vertexBlendIndex.erase(d3dmeshData.vertexBlendIndex.begin(), d3dmeshData.vertexBlendIndex.end());
	}

	void EraseIndexBufferHeaderData()
	{
		d3dmeshHeader.mIndexBuffers.erase(d3dmeshHeader.mIndexBuffers.begin(), d3dmeshHeader.mIndexBuffers.end());
		d3dmeshHeader.mIndexBufferCount = 0;
	}

	void EraseGFXAttributeParamsHeaderData()
	{
		d3dmeshHeader.GFXPlatformAttributeParamsArray.erase(d3dmeshHeader.GFXPlatformAttributeParamsArray.begin(), d3dmeshHeader.GFXPlatformAttributeParamsArray.end());
		d3dmeshHeader.mAttributeCount = 0;
	}

	void EraseVertexBufferHeaderData()
	{
		d3dmeshHeader.mVertexBuffers.erase(d3dmeshHeader.mVertexBuffers.begin(), d3dmeshHeader.mVertexBuffers.end());
		d3dmeshHeader.mVertexBufferCount = 0;
	}

	void EraseFullVertexPositionData()
	{
		d3dmeshData.vertexPositions.erase(d3dmeshData.vertexPositions.begin(), d3dmeshData.vertexPositions.end());
	}

	void EraseFullVertexNormalData()
	{
		d3dmeshData.vertexNormals.erase(d3dmeshData.vertexNormals.begin(), d3dmeshData.vertexNormals.end());
	}

	void EraseFullVertexTangentData()
	{
		d3dmeshData.vertexTangents.erase(d3dmeshData.vertexTangents.begin(), d3dmeshData.vertexTangents.end());
	}

	void EraseFullVertexUVData()
	{
		d3dmeshData.vertexUVs.erase(d3dmeshData.vertexUVs.begin(), d3dmeshData.vertexUVs.end());
	}

	void EraseFullVertexColorData()
	{
		d3dmeshData.vertexColors.erase(d3dmeshData.vertexColors.begin(), d3dmeshData.vertexColors.end());
	}

	void EraseFullVertexBlendWeightData()
	{
		d3dmeshData.vertexBlendWeight.erase(d3dmeshData.vertexBlendWeight.begin(), d3dmeshData.vertexBlendWeight.end());
	}

	void EraseFullVertexBlendIndexData()
	{
		d3dmeshData.vertexBlendIndex.erase(d3dmeshData.vertexBlendIndex.begin(), d3dmeshData.vertexBlendIndex.end());
	}

	void AddNewIndexBuffer(std::vector<unsigned short> newMeshIndexBufferData, GFXPlatformBufferUsage bufferUsage, GFXPlatformFormat platformFormat = eGFXPlatformFormat_U16)
	{
		T3GFXBuffer newIndexT3GFXBuffer = T3GFXBuffer();
		newIndexT3GFXBuffer.mResourceUsage = eResourceUsage_Static;
		newIndexT3GFXBuffer.mBufferFormat = platformFormat;
		newIndexT3GFXBuffer.mBufferUsage = bufferUsage;
		newIndexT3GFXBuffer.mCount = newMeshIndexBufferData.size();
		newIndexT3GFXBuffer.UpdateIndexBuffer();

		d3dmeshHeader.mIndexBuffers.push_back(newIndexT3GFXBuffer);
		d3dmeshData.indexBuffers.push_back(newMeshIndexBufferData);
		d3dmeshHeader.mIndexBufferCount = d3dmeshHeader.mIndexBuffers.size();
	}

	void AddNewVertexBufferVector4(GFXPlatformVertexAttribute attributeType, GFXPlatformFormat format, GFXPlatformBufferUsage bufferUsage, std::vector<Vector4> newMeshVertexBufferData, unsigned int newAttributeIndex = 0)
	{
		//int currentIndex = fmin(d3dmeshHeader.GFXPlatformAttributeParamsArray.size() - 1, 0
		int currentIndex = d3dmeshHeader.GFXPlatformAttributeParamsArray.size();

		GFXPlatformAttributeParams newAttributeParams = GFXPlatformAttributeParams();
		newAttributeParams.mAttribute = attributeType;
		newAttributeParams.mFormat = format;
		newAttributeParams.mAttributeIndex = newAttributeIndex;
		newAttributeParams.mBufferIndex = currentIndex;
		newAttributeParams.mBufferOffset = 0;

		T3GFXBuffer newVertexT3GFXBuffer = T3GFXBuffer();
		newVertexT3GFXBuffer.mResourceUsage = eResourceUsage_Static;
		newVertexT3GFXBuffer.mBufferUsage = bufferUsage;
		newVertexT3GFXBuffer.mCount = newMeshVertexBufferData.size();
		newVertexT3GFXBuffer.UpdateVertexBuffer(&newAttributeParams); //handles buffer format and stride

		d3dmeshHeader.GFXPlatformAttributeParamsArray.push_back(newAttributeParams);
		d3dmeshHeader.mVertexBuffers.push_back(newVertexT3GFXBuffer);

		switch (attributeType)
		{
		case GFXPlatformVertexAttribute::eGFXPlatformAttribute_Position:
			d3dmeshData.vertexPositions.push_back(newMeshVertexBufferData);
			break;
		case GFXPlatformVertexAttribute::eGFXPlatformAttribute_Normal:
			d3dmeshData.vertexNormals.push_back(newMeshVertexBufferData);
			break;
		case GFXPlatformVertexAttribute::eGFXPlatformAttribute_Tangent:
			d3dmeshData.vertexTangents.push_back(newMeshVertexBufferData);
			break;
		case GFXPlatformVertexAttribute::eGFXPlatformAttribute_BlendWeight:
			d3dmeshData.vertexBlendWeight.push_back(newMeshVertexBufferData);
			break;
		//case GFXPlatformVertexAttribute::eGFXPlatformAttribute_BlendIndex:
			//d3dmeshData.vertexBlendIndex.push_back(newMeshVertexBufferData);
			//break;
		case GFXPlatformVertexAttribute::eGFXPlatformAttribute_Color:
			d3dmeshData.vertexColors.push_back(newMeshVertexBufferData);
			break;
		case GFXPlatformVertexAttribute::eGFXPlatformAttribute_TexCoord:
			d3dmeshData.vertexUVs.push_back(newMeshVertexBufferData);
			break;
		}

		d3dmeshHeader.mAttributeCount = d3dmeshHeader.GFXPlatformAttributeParamsArray.size();
		d3dmeshHeader.mVertexBufferCount = d3dmeshHeader.mVertexBuffers.size();
	}

	void EraseBones() 
	{
		d3dmeshHeader.mBones.erase(d3dmeshHeader.mBones.begin(), d3dmeshHeader.mBones.end());
	}

	void ModifyIndexBuffers(std::vector<unsigned short> newMeshIndexBufferData)
	{
		for (int i = 0; i < d3dmeshHeader.mIndexBuffers.size(); i++)
		{
			T3GFXBuffer* indexT3GFXBuffer = &d3dmeshHeader.mIndexBuffers[i];
			indexT3GFXBuffer->mCount = newMeshIndexBufferData.size();
			indexT3GFXBuffer->UpdateIndexBuffer();
			d3dmeshData.indexBuffers[i].erase(d3dmeshData.indexBuffers[i].begin(), d3dmeshData.indexBuffers[i].end());
			d3dmeshData.indexBuffers[i] = newMeshIndexBufferData;
		}
	}

	void ModifyVertexBuffers(GFXPlatformVertexAttribute attributeType, std::vector<Vector4> newMeshVertexBufferData)
	{
		for (int i = 0; i < d3dmeshHeader.GFXPlatformAttributeParamsArray.size(); i++)
		{
			GFXPlatformAttributeParams* currentVertexAttributeParams = &d3dmeshHeader.GFXPlatformAttributeParamsArray[i];
			T3GFXBuffer* currentVertexT3GFXBuffer = &d3dmeshHeader.mVertexBuffers[i];

			if (currentVertexAttributeParams->mAttribute == attributeType)
			{
				currentVertexT3GFXBuffer->mCount = newMeshVertexBufferData.size();
				currentVertexT3GFXBuffer->UpdateVertexBuffer(currentVertexAttributeParams); //handles buffer format and stride
			}
		}

		int originalSize = 0;

		switch (attributeType)
		{
		case GFXPlatformVertexAttribute::eGFXPlatformAttribute_Position:

			originalSize = d3dmeshData.vertexPositions.size();
			d3dmeshData.vertexPositions.erase(d3dmeshData.vertexPositions.begin(), d3dmeshData.vertexPositions.end());

			for (int i = 0; i < originalSize; i++)
				d3dmeshData.vertexPositions.push_back(newMeshVertexBufferData);

			break;
		case GFXPlatformVertexAttribute::eGFXPlatformAttribute_Normal:

			originalSize = d3dmeshData.vertexNormals.size();
			d3dmeshData.vertexNormals.erase(d3dmeshData.vertexNormals.begin(), d3dmeshData.vertexNormals.end());

			for (int i = 0; i < originalSize; i++)
				d3dmeshData.vertexNormals.push_back(newMeshVertexBufferData);

			break;
		case GFXPlatformVertexAttribute::eGFXPlatformAttribute_Tangent:

			originalSize = d3dmeshData.vertexTangents.size();
			d3dmeshData.vertexTangents.erase(d3dmeshData.vertexTangents.begin(), d3dmeshData.vertexTangents.end());

			for (int i = 0; i < originalSize; i++)
				d3dmeshData.vertexTangents.push_back(newMeshVertexBufferData);

			break;
		case GFXPlatformVertexAttribute::eGFXPlatformAttribute_BlendWeight:

			originalSize = d3dmeshData.vertexBlendWeight.size();
			d3dmeshData.vertexBlendWeight.erase(d3dmeshData.vertexBlendWeight.begin(), d3dmeshData.vertexBlendWeight.end());

			for (int i = 0; i < originalSize; i++)
				d3dmeshData.vertexBlendWeight.push_back(newMeshVertexBufferData);

			break;
		//case GFXPlatformVertexAttribute::eGFXPlatformAttribute_BlendIndex:
			//d3dmeshData.vertexBlendIndex.push_back(newMeshVertexBufferData);
			//break;
		case GFXPlatformVertexAttribute::eGFXPlatformAttribute_Color:

			originalSize = d3dmeshData.vertexColors.size();
			d3dmeshData.vertexColors.erase(d3dmeshData.vertexColors.begin(), d3dmeshData.vertexColors.end());

			for (int i = 0; i < originalSize; i++)
				d3dmeshData.vertexColors.push_back(newMeshVertexBufferData);

			break;
		case GFXPlatformVertexAttribute::eGFXPlatformAttribute_TexCoord:

			originalSize = d3dmeshData.vertexUVs.size();
			d3dmeshData.vertexUVs.erase(d3dmeshData.vertexUVs.begin(), d3dmeshData.vertexUVs.end());

			for (int i = 0; i < originalSize; i++)
				d3dmeshData.vertexUVs.push_back(newMeshVertexBufferData);

			break;
		}
	}

	void EraseAllBoneData()
	{
		d3dmeshHeader.mBones.erase(d3dmeshHeader.mBones.begin(), d3dmeshHeader.mBones.end());
		
		for (int i = 0; i < d3dmeshHeader.mLODs.size(); i++)
			d3dmeshHeader.mLODs[i].mBones.erase(d3dmeshHeader.mLODs[i].mBones.begin(), d3dmeshHeader.mLODs[i].mBones.end());

		for (int i = 0; i < d3dmeshHeader.GFXPlatformAttributeParamsArray.size(); i++)
		{
			GFXPlatformAttributeParams* currentVertexAttributeParams = &d3dmeshHeader.GFXPlatformAttributeParamsArray[i];
			T3GFXBuffer* currentVertexT3GFXBuffer = &d3dmeshHeader.mVertexBuffers[i];

			if (currentVertexAttributeParams->mAttribute == eGFXPlatformAttribute_BlendIndex)
			{
				d3dmeshHeader.GFXPlatformAttributeParamsArray.erase(d3dmeshHeader.GFXPlatformAttributeParamsArray.begin() + i);
				d3dmeshHeader.mVertexBuffers.erase(d3dmeshHeader.mVertexBuffers.begin() + i);
			}
		}

		for (int i = 0; i < d3dmeshHeader.GFXPlatformAttributeParamsArray.size(); i++)
		{
			GFXPlatformAttributeParams* currentVertexAttributeParams = &d3dmeshHeader.GFXPlatformAttributeParamsArray[i];
			T3GFXBuffer* currentVertexT3GFXBuffer = &d3dmeshHeader.mVertexBuffers[i];

			if (currentVertexAttributeParams->mAttribute == eGFXPlatformAttribute_BlendWeight)
			{
				d3dmeshHeader.GFXPlatformAttributeParamsArray.erase(d3dmeshHeader.GFXPlatformAttributeParamsArray.begin() + i);
				d3dmeshHeader.mVertexBuffers.erase(d3dmeshHeader.mVertexBuffers.begin() + i);
			}
		}

		for (int i = 0; i < d3dmeshData.vertexBlendIndex.size(); i++)
			d3dmeshData.vertexBlendIndex.erase(d3dmeshData.vertexBlendIndex.begin(), d3dmeshData.vertexBlendIndex.end());

		for (int i = 0; i < d3dmeshData.vertexBlendWeight.size(); i++)
			d3dmeshData.vertexBlendWeight.erase(d3dmeshData.vertexBlendWeight.begin(), d3dmeshData.vertexBlendWeight.end());
	}

	void ZeroOutBoneData()
	{
		for (int i = 0; i < d3dmeshData.vertexBlendIndex.size(); i++)
		{
			for (int j = 0; j < d3dmeshData.vertexBlendIndex[i].size(); j++)
				d3dmeshData.vertexBlendIndex[i][j] = UnsignedIntegerVector4(0, 0, 0, 0);
		}

		for (int i = 0; i < d3dmeshData.vertexBlendWeight.size(); i++)
		{
			for (int j = 0; j < d3dmeshData.vertexBlendWeight[i].size(); j++)
				d3dmeshData.vertexBlendWeight[i][j] = Vector4(0, 0, 0, 0);
		}
	}

	bool IsVertexPositionFormatUnsignedNormalized()
	{
		for (int i = 0; i < d3dmeshHeader.GFXPlatformAttributeParamsArray.size(); i++)
		{
			if(d3dmeshHeader.GFXPlatformAttributeParamsArray[i].mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Position)
				return IsGFXPlatformFormatUnsignedNormalized(d3dmeshHeader.GFXPlatformAttributeParamsArray[i].mFormat);
		}

		return false;
	}

	bool IsVertexPositionFormatSignedNormalized()
	{
		for (int i = 0; i < d3dmeshHeader.GFXPlatformAttributeParamsArray.size(); i++)
		{
			if (d3dmeshHeader.GFXPlatformAttributeParamsArray[i].mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Position)
				return IsGFXPlatformFormatSignedNormalized(d3dmeshHeader.GFXPlatformAttributeParamsArray[i].mFormat);
		}

		return false;
	}

	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| UPDATE STRUCTURES |||||||||||||||||||||||||||||
	//NOTE: This is critical as any mishap in regards to new/removed data will crash the game.
	//So in advance we need to update all structural values (block sizes, array lengths, array capacities) to make sure everything lines up.

	void UpdateStructures()
	{
		d3dmeshHeader.mIndexBufferCount = d3dmeshData.indexBuffers.size();

		d3dmeshHeader.UpdateStructures();

		metaHeader.mDefaultSectionChunkSize = d3dmeshHeader.GetByteSize();
		metaHeader.mAsyncSectionChunkSize = d3dmeshHeader.GetD3DMeshDataSize();
	}

	//||||||||||||||||||||||||||||| VALIDATE STRUCTURE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| VALIDATE STRUCTURE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| VALIDATE STRUCTURE |||||||||||||||||||||||||||||

	bool ValidateStructure() 
	{
		/*
		* TODO: Implement this function for this and every struct/class.
		* With this function we will run through the data structure and validate it.
		* Printing out lines to the console when we notice oddities with the data.
		* 
		* I.e. for example with T3MeshLODs...
		* Check the size/length/capacity.
		* If the length doesn't match the actual array, validation failed and print a note to console.
		* 
		* NOTE TO SELF: Don't stop if one validation fails, go through the entire structure before returning the boolean result.
		*/

		return true;
	}

	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| BINARY SERIALIZE |||||||||||||||||||||||||||||

	void BinarySerialize(std::ofstream* outputFileStream)
	{
		metaHeader.BinarySerialize(outputFileStream);
 		d3dmeshHeader.BinarySerialize(outputFileStream);
		d3dmeshData.BinarySerialize(outputFileStream, &d3dmeshHeader);
	};

	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| JSON |||||||||||||||||||||||||||||
	//REFERENCE - https://json.nlohmann.me/features/arbitrary_types/
	//NOTE: These macros are limited to 64 members at most (if there are more you'll need to implement manually.

	//These are supposed to be inside the class/struct
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...) //will not throw exceptions, fills in values with default constructor
	NLOHMANN_ORDERED_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(TelltaleD3DMeshFileV55, metaHeader, d3dmeshHeader, d3dmeshData)
};

#endif
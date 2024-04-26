//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| LIBRARIES |||||||||||||||||||||||||||||

//THIRD PARTY: ASSIMP Library
#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

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
#include "BinaryDeserialization.h"
#include "BinarySerialization.h"
#include "TelltaleEnums.h"
#include "Structs.h"

//|||||||||||||||||||||||||||||||||||||||| MAIN ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| MAIN ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| MAIN ||||||||||||||||||||||||||||||||||||||||

void ExportAssimpMesh(ExtractedMesh extractedMesh, std::string fileName)
{
	//if for some reason we don't have the following critical data, then we will just have to skip...
	if (extractedMesh.vertexPositions.size() <= 0)
		return;

	if (extractedMesh.vertexNormals0.size() <= 0)
		return;

	if (extractedMesh.triangleIndicies.size() <= 0)
		return;

	//start by building a scene in assimp
	aiScene* assimpScene = new aiScene;

	//construct an empty scene with no flags
	assimpScene->mFlags = 0;
	assimpScene->mRootNode = NULL;

	//initalize the scene first with no meshes
	assimpScene->mNumMeshes = 0;
	assimpScene->mMeshes = NULL;

	//initalize the scene first with no materials
	assimpScene->mNumMaterials = 0;
	assimpScene->mMaterials = NULL;

	//initalize the scene first with no animations
	assimpScene->mNumAnimations = 0;
	assimpScene->mAnimations = NULL;

	//initalize the scene first with no textures
	assimpScene->mNumTextures = 0;
	assimpScene->mTextures = NULL;

	//initalize the scene first with no lights
	assimpScene->mNumLights = 0;
	assimpScene->mLights = NULL;

	//initalize the scene first with no cameras
	assimpScene->mNumCameras = 0;
	assimpScene->mCameras = NULL;
	assimpScene->mPrivate = NULL;

	//construct the root node to store the mesh
	aiNode* rootNode = new aiNode;
	assimpScene->mRootNode = rootNode;

	//create one empty material
	assimpScene->mMaterials = new aiMaterial * [1];
	assimpScene->mMaterials[0] = nullptr; //initalize the first material to a null pointer
	assimpScene->mNumMaterials = 1; //update the material count
	assimpScene->mMaterials[0] = new aiMaterial(); //create an actual material object

	//create one mesh
	assimpScene->mMeshes = new aiMesh * [1];
	assimpScene->mMeshes[0] = nullptr;
	assimpScene->mNumMeshes = 1;

	//assign the singular mesh to the material we created
	assimpScene->mMeshes[0] = new aiMesh();
	assimpScene->mMeshes[0]->mMaterialIndex = 0;

	assimpScene->mRootNode->mMeshes = new unsigned int[1];
	assimpScene->mRootNode->mMeshes[0] = 0;
	assimpScene->mRootNode->mNumMeshes = 1;

	//get a reference to the mesh so we can start filling it with data
	auto pMesh = assimpScene->mMeshes[0];

	//|||||||||||||||||||||||||||||||||||||||| VERTEX POSITIONS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX POSITIONS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX POSITIONS ||||||||||||||||||||||||||||||||||||||||
	//the most important and critical part of the model, the position of each vertex in the model.

	//initalize vertex position array
	pMesh->mNumVertices = extractedMesh.vertexPositions.size(); //SELF NOTE: assign amount of verticies first... or all hell breaks loose
	pMesh->mVertices = new aiVector3D[pMesh->mNumVertices];

	//fill up the vertex position array
	for (int vertexIndex = 0; vertexIndex < pMesh->mNumVertices; vertexIndex++)
		pMesh->mVertices[vertexIndex] = aiVector3D(extractedMesh.vertexPositions[vertexIndex].x, extractedMesh.vertexPositions[vertexIndex].y, extractedMesh.vertexPositions[vertexIndex].z);

	//|||||||||||||||||||||||||||||||||||||||| VERTEX NORMALS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX NORMALS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX NORMALS ||||||||||||||||||||||||||||||||||||||||
	//the second most important part of the model, the normals (which define the direction for triangles and where they face)

	//initalize vertex normal array
	pMesh->mNormals = new aiVector3D[pMesh->mNumVertices];

	//fill up the vertex normal array
	for (int normalIndex = 0; normalIndex < pMesh->mNumVertices; normalIndex++)
		pMesh->mNormals[normalIndex] = aiVector3D(extractedMesh.vertexNormals0[normalIndex].x, extractedMesh.vertexNormals0[normalIndex].y, extractedMesh.vertexNormals0[normalIndex].z);

	//|||||||||||||||||||||||||||||||||||||||| VERTEX TANGENTS (IF USED) ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX TANGENTS (IF USED) ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX TANGENTS (IF USED) ||||||||||||||||||||||||||||||||||||||||
	//not required for a mesh, but a tangent is a unit length vector that follows a surface along the X (or U from UVW) direction.

	//not every telltale mesh has a tangent buffer, so check if we have any
	if (extractedMesh.vertexTangents.size() > 0)
	{
		//initalize the vertex tangent array
		pMesh->mTangents = new aiVector3D[pMesh->mNumVertices];

		//fill up the vertex tangent array
		for (int tangentIndex = 0; tangentIndex < pMesh->mNumVertices; tangentIndex++)
			pMesh->mTangents[tangentIndex] = aiVector3D(extractedMesh.vertexTangents[tangentIndex].x, extractedMesh.vertexTangents[tangentIndex].y, extractedMesh.vertexTangents[tangentIndex].z);
	}

	//|||||||||||||||||||||||||||||||||||||||| VERTEX UVS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX UVS ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX UVS ||||||||||||||||||||||||||||||||||||||||
	//not really required for a mesh, but they are important if textures are to be used. 
	//these store coordinates for how textures are mapped onto a vertex.

	//since meshes can have a variety of UV channels defined, we have up to 8 max UV channels
	//we will check each one if it contains data and increment the channel count by one if it has data
	int uvChannels = 0;
	uvChannels += extractedMesh.vertexUVs0.size() > 0 ? 1 : 0;
	uvChannels += extractedMesh.vertexUVs1.size() > 0 ? 1 : 0;
	uvChannels += extractedMesh.vertexUVs2.size() > 0 ? 1 : 0;
	uvChannels += extractedMesh.vertexUVs3.size() > 0 ? 1 : 0;
	uvChannels += extractedMesh.vertexUVs4.size() > 0 ? 1 : 0;
	uvChannels += extractedMesh.vertexUVs5.size() > 0 ? 1 : 0;
	uvChannels += extractedMesh.vertexUVs6.size() > 0 ? 1 : 0;
	uvChannels += extractedMesh.vertexUVs7.size() > 0 ? 1 : 0;

	//if there is UV data
	if (uvChannels > 0)
	{
		//iterate through each UV channel
		for (int uvChannelIndex = 0; uvChannelIndex < uvChannels; uvChannelIndex++)
		{
			//initalize the vertex uv array
			pMesh->mTextureCoords[uvChannelIndex] = new aiVector3D[pMesh->mNumVertices];

			//initalize our reference UV array object
			std::vector<Vector2> uvs;

			//depending on the current channel index we are on, pick the appropriate extracted UV channel array
			if (uvChannelIndex == 0)
				uvs = extractedMesh.vertexUVs0;
			if (uvChannelIndex == 1)
				uvs = extractedMesh.vertexUVs1;
			if (uvChannelIndex == 2)
				uvs = extractedMesh.vertexUVs2;
			if (uvChannelIndex == 3)
				uvs = extractedMesh.vertexUVs3;
			if (uvChannelIndex == 4)
				uvs = extractedMesh.vertexUVs4;
			if (uvChannelIndex == 5)
				uvs = extractedMesh.vertexUVs5;
			if (uvChannelIndex == 6)
				uvs = extractedMesh.vertexUVs6;
			if (uvChannelIndex == 7)
				uvs = extractedMesh.vertexUVs7;

			//fill up the vertex uv array for the current uv channel
			for (int uvIndex = 0; uvIndex < pMesh->mNumVertices; uvIndex++)
				pMesh->mTextureCoords[uvChannelIndex][uvIndex] = aiVector3D(uvs[uvIndex].x, uvs[uvIndex].y, 0.0f);
		}
	}

	//|||||||||||||||||||||||||||||||||||||||| VERTEX COLORS (IF USED) ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX COLORS (IF USED) ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| VERTEX COLORS (IF USED) ||||||||||||||||||||||||||||||||||||||||
	//not required for a mesh, but sometimes they contain vertex colors. 
	//these are just colors that can be used by shaders for specific tasks (i.e. multiple texture blending, or other purposes).
	//NOTE: that these vertex colors can really be used for all kinds of things... so you can't really pin down what its exactly used for in the engine as it depends on the shader used to render the mesh.

	//since meshes can have a variety of vertex color channels defined, we have up to 8 max vertex color channels
	//we will check each one if it contains data and increment the channel count by one if it has data
	int colorChannels = 0;
	colorChannels += extractedMesh.vertexColors0.size() > 0 ? 1 : 0;
	colorChannels += extractedMesh.vertexColors1.size() > 0 ? 1 : 0;
	colorChannels += extractedMesh.vertexColors2.size() > 0 ? 1 : 0;
	colorChannels += extractedMesh.vertexColors3.size() > 0 ? 1 : 0;
	colorChannels += extractedMesh.vertexColors4.size() > 0 ? 1 : 0;
	colorChannels += extractedMesh.vertexColors5.size() > 0 ? 1 : 0;
	colorChannels += extractedMesh.vertexColors6.size() > 0 ? 1 : 0;
	colorChannels += extractedMesh.vertexColors7.size() > 0 ? 1 : 0;

	//if there is vertex color data
	if (colorChannels > 0)
	{
		//iterate through each vertex color channel
		for (int colorChannelIndex = 0; colorChannelIndex < colorChannels; colorChannelIndex++)
		{
			//initalize the vertex color array
			pMesh->mColors[colorChannelIndex] = new aiColor4D[pMesh->mNumVertices];

			//initalize our reference vertex color array object
			std::vector<Vector4> colors;

			//depending on the current channel index we are on, pick the appropriate extracted color channel array
			if (colorChannelIndex == 0)
				colors = extractedMesh.vertexColors0;
			if (colorChannelIndex == 1)
				colors = extractedMesh.vertexColors1;
			if (colorChannelIndex == 2)
				colors = extractedMesh.vertexColors2;
			if (colorChannelIndex == 3)
				colors = extractedMesh.vertexColors3;
			if (colorChannelIndex == 4)
				colors = extractedMesh.vertexColors4;
			if (colorChannelIndex == 5)
				colors = extractedMesh.vertexColors5;
			if (colorChannelIndex == 6)
				colors = extractedMesh.vertexColors6;
			if (colorChannelIndex == 7)
				colors = extractedMesh.vertexColors7;

			//fill up the vertex uv array for the current vertex color channel
			for (int colorIndex = 0; colorIndex < pMesh->mNumVertices; colorIndex++)
				pMesh->mColors[colorChannelIndex][colorIndex] = aiColor4D(colors[colorIndex].x, colors[colorIndex].y, colors[colorIndex].z, colors[colorIndex].w);
		}
	}

	//|||||||||||||||||||||||||||||||||||||||| MESH TRIANGLES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| MESH TRIANGLES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| MESH TRIANGLES ||||||||||||||||||||||||||||||||||||||||
	//another really critical part of the mesh, triangles. These are essentially indexes that point to what vertex to use.

	//initalize an array of assimp faces to store our extracted triangle indicies
	std::vector<aiFace> faces;

	//iterate through each extracted triangle index
	for (int faceIndex = 0; faceIndex < extractedMesh.triangleIndicies.size(); faceIndex += 3)
	{
		//initalize a new assimp face object
		aiFace newFace = aiFace();

		//triangles are made up of 3 vertex positions, so indicies are 3
		newFace.mNumIndices = 3;
		newFace.mIndices = new unsigned int[newFace.mNumIndices];

		//assign each extracted triangle index to our assimp face
		newFace.mIndices[0] = extractedMesh.triangleIndicies[faceIndex + 0];
		newFace.mIndices[1] = extractedMesh.triangleIndicies[faceIndex + 1];
		newFace.mIndices[2] = extractedMesh.triangleIndicies[faceIndex + 2];

		//accumulate final assimp faces
		faces.push_back(newFace);
	}

	//initalize the triangle indicies array
	pMesh->mFaces = new aiFace[faces.size()];
	pMesh->mNumFaces = faces.size();

	//copy the triangle data to the assimp faces array
	std::copy(faces.begin(), faces.end(), pMesh->mFaces);

	//|||||||||||||||||||||||||||||||||||||||| ASSIMP EXPORT ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| ASSIMP EXPORT ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| ASSIMP EXPORT ||||||||||||||||||||||||||||||||||||||||

	//initalize our assimp exporter objects
	Assimp::Exporter assimpExporter;
	Assimp::ExportProperties* properties = new Assimp::ExportProperties;

	//currenty supported assimp export formats
	//[ASSIMP] ID : x Extension : x
	//[ASSIMP] ID : stp Extension : stp
	//[ASSIMP] ID : obj Extension : obj
	//[ASSIMP] ID : objnomtl Extension : obj
	//[ASSIMP] ID : stl Extension : stl
	//[ASSIMP] ID : stlb Extension : stl
	//[ASSIMP] ID : ply Extension : ply
	//[ASSIMP] ID : plyb Extension : ply
	//[ASSIMP] ID : 3ds Extension : 3ds
	//[ASSIMP] ID : gltf2 Extension : gltf
	//[ASSIMP] ID : glb2 Extension : glb
	//[ASSIMP] ID : gltf Extension : gltf
	//[ASSIMP] ID : glb Extension : glb
	//[ASSIMP] ID : assbin Extension : assbin
	//[ASSIMP] ID : assxml Extension : assxml
	//[ASSIMP] ID : x3d Extension : x3d
	//[ASSIMP] ID : fbx Extension : fbx
	//[ASSIMP] ID : fbxa Extension : fbx
	//[ASSIMP] ID : 3mf Extension : 3mf
	//[ASSIMP] ID : pbrt Extension : pbrt
	//[ASSIMP] ID : assjson Extension : json
	std::string id = "fbx";
	std::string extension = "fbx";

	//construct our final exported file path for the final mesh
	std::string exportPath = "Output/" + fileName + "." + extension;

	std::cout << "[ASSIMP EXPORT] Exporting..." << std::endl;

	//redirect assimp logs to the console output so we can see if something goes wrong
	auto assimpExportStream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT, NULL);
	aiAttachLogStream(&assimpExportStream);

	//export our final model using assimp
	aiReturn exportResult = assimpExporter.Export(assimpScene, id, exportPath, aiProcess_FindInvalidData | aiProcess_ValidateDataStructure, properties);

	//print to the console if we ran int oa problem
	if (exportResult == aiReturn_FAILURE || exportResult == aiReturn_OUTOFMEMORY)
	{
		std::cout << "[ASSIMP EXPORT] Export Failed! Returned " << exportResult << std::endl;
	}
	else
	{
		std::cout << "[ASSIMP EXPORT] Export Success!" << std::endl;
	}

	//detatch the log stream from assimp since we are done
	aiDetachLogStream(&assimpExportStream);
}

FileD3DMesh ParseD3DMeshFile(std::ifstream &currentD3DMESH_inputFileStream)
{
	//initalize our d3dmesh file object so we can start filling it with data
	FileD3DMesh d3dmeshFile{};

	//|||||||||||||||||||||||||||||||||||||||| META HEADER ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| META HEADER ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| META HEADER ||||||||||||||||||||||||||||||||||||||||
	//telltale files always have a "meta" header serialized ontop of the file
	//this header is important as it tells the engine (and us) the size of the d3dmesh header, and the size of the file data after the headers.
	//it also contains misc information like the reference class names and types, which are hashed (CRC64)

	//parse the telltale meta header
	d3dmeshFile.metaHeader = BinaryDeserialization::ReadTelltaleMetaHeaderVersion6FromBinary(&currentD3DMESH_inputFileStream);

	//we finished going through the meta header, so the offset we left off at matches the size of the meta header
	unsigned long metaHeaderSize = currentD3DMESH_inputFileStream.tellg();

	//|||||||||||||||||||||||||||||||||||||||| D3DMESH HEADER ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| D3DMESH HEADER ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| D3DMESH HEADER ||||||||||||||||||||||||||||||||||||||||
	//here we get into the important parts of the file.
	//after parsing the meta header, the main d3dmesh header is serialized right after it
	//this is the most important part as it contains all of the necessary information about the mesh so that we can read/extract it properly.

	//initalize our header object
	d3dmeshFile.d3dmeshHeader = {};

	//parse the inital chunks here, according to ida this is the main D3DMesh chunk
	d3dmeshFile.d3dmeshHeader.mNameBlockSize = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mName = BinaryDeserialization::ReadLengthPrefixedStringFromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mVersion = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mToolProps = BinaryDeserialization::ReadInt8FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mLightmapGlobalScale = BinaryDeserialization::ReadFloat32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mLightmapTexCoordVersion = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mLODParamCRC = BinaryDeserialization::ReadSymbolFromBinary(&currentD3DMESH_inputFileStream);

	//parse the internal resources block, this was difficult to track down but this basically contains propertysets or references to resources uses (i.e. materials)
	d3dmeshFile.d3dmeshHeader.mInternalResourcesCount = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);

	for (int mInternalResourceIndex = 0; mInternalResourceIndex < d3dmeshFile.d3dmeshHeader.mInternalResourcesCount; mInternalResourceIndex++)
	{
		d3dmeshFile.d3dmeshHeader.mInternalResources.push_back(BinaryDeserialization::ReadTelltaleInternalResourceFromBinary(&currentD3DMESH_inputFileStream)); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)
	}

	//parse the tool property set block, this shouldn't technically have any data since this is the final shipped file.
	d3dmeshFile.d3dmeshHeader.mToolPropsBlockSize = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mToolPropsData = BinaryDeserialization::ReadByteBufferFromBinary(&currentD3DMESH_inputFileStream, d3dmeshFile.d3dmeshHeader.mToolPropsBlockSize); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)

	//parse the occlusion data block, this contains occlusion culling information regarding the mesh.
	d3dmeshFile.d3dmeshHeader.mHasOcclusionData = BinaryDeserialization::ReadInt8FromBinary(&currentD3DMESH_inputFileStream);

	//if this is true then we need to skip it (ASCII '1' is true, ASCII '0' is false)
	if (d3dmeshFile.d3dmeshHeader.mHasOcclusionData == '1')
	{
		d3dmeshFile.d3dmeshHeader.mOcclusionDataBlockSize = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
		d3dmeshFile.d3dmeshHeader.mOcclusionData = BinaryDeserialization::ReadByteBufferFromBinary(&currentD3DMESH_inputFileStream, d3dmeshFile.d3dmeshHeader.mOcclusionDataBlockSize - 4); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)
	}

	//this is the start of the main T3MeshData block
	d3dmeshFile.d3dmeshHeader.mT3MeshDataBlockSize = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);

	//parse the LODs associated with the mesh (oddly enough telltale didn't use LODs very often?)
	d3dmeshFile.d3dmeshHeader.mLODs_ArrayCapacity = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mLODs_ArrayLength = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);

	for (int i = 0; i < d3dmeshFile.d3dmeshHeader.mLODs_ArrayLength; i++)
	{
		d3dmeshFile.d3dmeshHeader.mLODs.push_back(BinaryDeserialization::ReadTelltaleMeshLODFromBinary(&currentD3DMESH_inputFileStream));
	}

	//parse the textures block (NOTE: This does not contain actual texture data, just references to it)
	d3dmeshFile.d3dmeshHeader.mTextures_ArrayCapacity = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mTextures_ArrayLength = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mTexturesData = BinaryDeserialization::ReadByteBufferFromBinary(&currentD3DMESH_inputFileStream, d3dmeshFile.d3dmeshHeader.mTextures_ArrayCapacity - 8); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)

	//parse the materials block
	d3dmeshFile.d3dmeshHeader.mMaterials_ArrayCapacity = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mMaterials_ArrayLength = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mMaterialsData = BinaryDeserialization::ReadByteBufferFromBinary(&currentD3DMESH_inputFileStream, d3dmeshFile.d3dmeshHeader.mMaterials_ArrayCapacity - 8); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)

	//parse the materials overrides block
	d3dmeshFile.d3dmeshHeader.mMaterialOverrides_ArrayCapacity = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mMaterialOverrides_ArrayLength = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mMaterialOverridesData = BinaryDeserialization::ReadByteBufferFromBinary(&currentD3DMESH_inputFileStream, d3dmeshFile.d3dmeshHeader.mMaterialOverrides_ArrayCapacity - 8); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)

	//parse the rigging bones block
	d3dmeshFile.d3dmeshHeader.mBones_ArrayCapacity = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mBones_ArrayLength = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);

	for (int i = 0; i < d3dmeshFile.d3dmeshHeader.mBones_ArrayLength; i++)
	{
		d3dmeshFile.d3dmeshHeader.mBones.push_back(BinaryDeserialization::ReadTelltaleMeshBoneEntryFromBinary(&currentD3DMESH_inputFileStream));
	}

	//parse the rigging bones block
	d3dmeshFile.d3dmeshHeader.mLocalTransforms_ArrayCapacity = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mLocalTransforms_ArrayLength = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);

	for (int i = 0; i < d3dmeshFile.d3dmeshHeader.mLocalTransforms_ArrayLength; i++)
	{
		d3dmeshFile.d3dmeshHeader.mLocalTransforms.push_back(BinaryDeserialization::ReadTelltaleMeshLocalTransformEntryFromBinary(&currentD3DMESH_inputFileStream));
	}

	//parse other misc information in the d3dmesh header
	d3dmeshFile.d3dmeshHeader.mMaterialRequirements = BinaryDeserialization::ReadTelltaleMaterialRequirementsFromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mVertexStreams_BlockSize = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream); //value seems to always be 8
	d3dmeshFile.d3dmeshHeader.mVertexStreams = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mBoundingBox = BinaryDeserialization::ReadBoundingBoxFromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mBoundingSphere = BinaryDeserialization::ReadBoundingSphereFromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mEndianType = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mPositionScale = BinaryDeserialization::ReadVector3FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mPositionWScale = BinaryDeserialization::ReadVector3FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mPositionOffset = BinaryDeserialization::ReadVector3FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mLightmapTexelAreaPerSurfaceArea = BinaryDeserialization::ReadFloat32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mPropertyKeyBase = BinaryDeserialization::ReadSymbolFromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mVertexCount = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mFlags = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mMeshPreload_BlockSize = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mMeshPreloadData = BinaryDeserialization::ReadByteBufferFromBinary(&currentD3DMESH_inputFileStream, d3dmeshFile.d3dmeshHeader.mMeshPreload_BlockSize - 4); //IMPORTANT NOTE: this is mostly skipped (we still keep the block of bytes so we can write later)
	d3dmeshFile.d3dmeshHeader.UNKNOWN1 = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.UNKNOWN2 = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mVertexCountPerInstance = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mIndexBufferCount = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mVertexBufferCount = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);
	d3dmeshFile.d3dmeshHeader.mAttributeCount = BinaryDeserialization::ReadUInt32FromBinary(&currentD3DMESH_inputFileStream);

	//parse the table of GFXPlatformAttributes, this is important as this is used during the vertex buffer parsing later to identify what buffers contain what data.
	for (int i = 0; i < d3dmeshFile.d3dmeshHeader.mAttributeCount; i++)
	{
		d3dmeshFile.d3dmeshHeader.GFXPlatformAttributeParamsArray.push_back(BinaryDeserialization::ReadTelltaleGraphicsPlatformAttributeParametersFromBinary(&currentD3DMESH_inputFileStream));
	}

	//parse the table of GFXBuffer data, these are "index" buffers (i.e. triangle indicies)
	for (int i = 0; i < d3dmeshFile.d3dmeshHeader.mIndexBufferCount; i++)
	{
		d3dmeshFile.d3dmeshHeader.mIndexBuffers.push_back(BinaryDeserialization::ReadTelltaleGFXBufferFromBinary(&currentD3DMESH_inputFileStream));
	}

	//parse the table of GFXBuffer data, these are "vertex" buffers (i.e. vertex position, normal, uv, etc)
	for (int i = 0; i < d3dmeshFile.d3dmeshHeader.mVertexBufferCount; i++)
	{
		d3dmeshFile.d3dmeshHeader.mVertexBuffers.push_back(BinaryDeserialization::ReadTelltaleGFXBufferFromBinary(&currentD3DMESH_inputFileStream));
	}

	//we have now reached the end of the d3dmesh header, after this lies the actual data of the mesh
	//
	//|||||||||||||||||||||||||||||||||||||||| D3DMESH BUFFER DATA PREPARE ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| D3DMESH BUFFER DATA PREPARE ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| D3DMESH BUFFER DATA PREPARE ||||||||||||||||||||||||||||||||||||||||
	//before we parse the actual d3dmesh data we will first initalize an array of extracted mesh LODs and submeshes
	//we do this so we can store the extracted results and feed them into assimp to export them to useable meshes

	d3dmeshFile.bufferData = {};

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
	for (int i = 0; i < d3dmeshFile.d3dmeshHeader.mIndexBuffers.size(); i++)
	{
		//reference to the main index buffer that we are currently on
		T3GFXBuffer* mIndexBuffer = &d3dmeshFile.d3dmeshHeader.mIndexBuffers[i];

		switch (mIndexBuffer->mBufferFormat)
		{
		case GFXPlatformFormat::eGFXPlatformFormat_U16:
			//if (mIndexBuffer->mBufferUsage == 2) //eGFXPlatformBuffer_Index

			for (int j = 0; j < mIndexBuffer->mCount; j++)
			{
				unsigned short triangleIndex = BinaryDeserialization::ReadUInt16FromBinary(&currentD3DMESH_inputFileStream);

				if (d3dmeshFile.bufferData.indexBufferCount == 0)
					d3dmeshFile.bufferData.indexBuffer0.push_back(triangleIndex);
				else if (d3dmeshFile.bufferData.indexBufferCount == 1)
					d3dmeshFile.bufferData.indexBuffer1.push_back(triangleIndex);
				else if (d3dmeshFile.bufferData.indexBufferCount == 2)
					d3dmeshFile.bufferData.indexBuffer2.push_back(triangleIndex);
				else if (d3dmeshFile.bufferData.indexBufferCount == 3)
					d3dmeshFile.bufferData.indexBuffer3.push_back(triangleIndex);
				else if (d3dmeshFile.bufferData.indexBufferCount == 4)
					d3dmeshFile.bufferData.indexBuffer4.push_back(triangleIndex);
				else if (d3dmeshFile.bufferData.indexBufferCount == 5)
					d3dmeshFile.bufferData.indexBuffer5.push_back(triangleIndex);
				else if (d3dmeshFile.bufferData.indexBufferCount == 6)
					d3dmeshFile.bufferData.indexBuffer6.push_back(triangleIndex);
				else if (d3dmeshFile.bufferData.indexBufferCount == 7)
					d3dmeshFile.bufferData.indexBuffer7.push_back(triangleIndex);
			}

			std::cout << "Index Buffer: " << d3dmeshFile.bufferData.indexBufferCount << " | mIndexBuffer->mBufferUsage: " << mIndexBuffer->mBufferUsage << std::endl;

			d3dmeshFile.bufferData.indexBufferCount++;

			break;
		default:
			BinaryDeserialization::ReadByteBufferFromBinary(&currentD3DMESH_inputFileStream, mIndexBuffer->mCount * mIndexBuffer->mStride); //skip this data block
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
	for (int i = 0; i < d3dmeshFile.d3dmeshHeader.mVertexBuffers.size(); i++)
	{
		T3GFXBuffer* mVertexBuffer = &d3dmeshFile.d3dmeshHeader.mVertexBuffers[i];
		GFXPlatformAttributeParams* attributeParams = &d3dmeshFile.d3dmeshHeader.GFXPlatformAttributeParamsArray[i];

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
					Vector4 parsedVertexPosition = BinaryDeserialization::ReadT3GFXBuffer_UnsignedNormalized_4x16BitInteger(&currentD3DMESH_inputFileStream);

					//SELF NOTE: DIVIDING BY THE W COMPONENT WILL CREATE VECTORS OF INFINITY/NAN VALUES, SO DONT DO IT!
					Vector3 convertedVertexPosition;
					convertedVertexPosition.x = parsedVertexPosition.x * d3dmeshFile.d3dmeshHeader.mPositionScale.x + d3dmeshFile.d3dmeshHeader.mPositionOffset.x;
					convertedVertexPosition.y = parsedVertexPosition.y * d3dmeshFile.d3dmeshHeader.mPositionScale.y + d3dmeshFile.d3dmeshHeader.mPositionOffset.y;
					convertedVertexPosition.z = parsedVertexPosition.z * d3dmeshFile.d3dmeshHeader.mPositionScale.z + d3dmeshFile.d3dmeshHeader.mPositionOffset.z;

					d3dmeshFile.bufferData.vertexPositions.push_back(convertedVertexPosition);
				}
			}
			//else if (mVertexBuffer->mBufferFormat == GFXPlatformFormat::eGFXPlatformFormat_UN10x3_UN2)
			else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_UN10x3_UN2)
			{
				for (int j = 0; j < mVertexBuffer->mCount; j++)
				{
					Vector3 parsedVertexPosition = BinaryDeserialization::ReadT3GFXBuffer_UnsignedNormalized_3x10BitInteger_2BitInteger(&currentD3DMESH_inputFileStream, d3dmeshFile.d3dmeshHeader.mPositionWScale);

					Vector3 convertedVertexPosition;
					convertedVertexPosition.x = parsedVertexPosition.x * d3dmeshFile.d3dmeshHeader.mPositionScale.x + d3dmeshFile.d3dmeshHeader.mPositionOffset.x;
					convertedVertexPosition.y = parsedVertexPosition.y * d3dmeshFile.d3dmeshHeader.mPositionScale.y + d3dmeshFile.d3dmeshHeader.mPositionOffset.y;
					convertedVertexPosition.z = parsedVertexPosition.z * d3dmeshFile.d3dmeshHeader.mPositionScale.z + d3dmeshFile.d3dmeshHeader.mPositionOffset.z;

					d3dmeshFile.bufferData.vertexPositions.push_back(convertedVertexPosition);
				}
			}
			//else if (mVertexBuffer->mBufferFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x3)
			else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x3)
			{
				for (int j = 0; j < mVertexBuffer->mCount; j++)
				{
					Vector3 parsedVertexPosition = BinaryDeserialization::ReadT3GFXBuffer_3x32BitFloat(&currentD3DMESH_inputFileStream);

					Vector3 convertedVertexPosition;
					convertedVertexPosition.x = parsedVertexPosition.x * d3dmeshFile.d3dmeshHeader.mPositionScale.x + d3dmeshFile.d3dmeshHeader.mPositionOffset.x;
					convertedVertexPosition.y = parsedVertexPosition.y * d3dmeshFile.d3dmeshHeader.mPositionScale.y + d3dmeshFile.d3dmeshHeader.mPositionOffset.y;
					convertedVertexPosition.z = parsedVertexPosition.z * d3dmeshFile.d3dmeshHeader.mPositionScale.z + d3dmeshFile.d3dmeshHeader.mPositionOffset.z;

					d3dmeshFile.bufferData.vertexPositions.push_back(convertedVertexPosition);
				}
			}
			else
			{
				std::cout << "SKIPPING DATA IN VERTEX BUFFER!" << d3dmeshFile.d3dmeshHeader.mName << std::endl;
				BinaryDeserialization::ReadByteBufferFromBinary(&currentD3DMESH_inputFileStream, mVertexBuffer->mCount * mVertexBuffer->mStride); //skip this data block
			}
		}
		//||||||||||||||||||||||||||||||||||||| VERTEX NORMAL |||||||||||||||||||||||||||||||||||||
		//||||||||||||||||||||||||||||||||||||| VERTEX NORMAL |||||||||||||||||||||||||||||||||||||
		//||||||||||||||||||||||||||||||||||||| VERTEX NORMAL |||||||||||||||||||||||||||||||||||||
		else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Normal)
		{
			d3dmeshFile.bufferData.vertexNormalsCount++;

			if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_SN8x4)
			{
				for (int j = 0; j < mVertexBuffer->mCount; j++)
				{
					Vector4 parsedVertexNormal = BinaryDeserialization::ReadT3GFXBuffer_Normalized_4x8BitInteger(&currentD3DMESH_inputFileStream);

					//SELF NOTE: DIVIDING BY THE W COMPONENT WILL CREATE VECTORS OF INFINITY/NAN VALUES, SO DONT DO IT!
					Vector3 convertedVertexNormal;
					convertedVertexNormal.x = parsedVertexNormal.x;
					convertedVertexNormal.y = parsedVertexNormal.y;
					convertedVertexNormal.z = parsedVertexNormal.z;

					if (d3dmeshFile.bufferData.vertexNormalsCount == 1)
						d3dmeshFile.bufferData.vertexNormals0.push_back(convertedVertexNormal);
					if (d3dmeshFile.bufferData.vertexNormalsCount == 2)
						d3dmeshFile.bufferData.vertexNormals1.push_back(convertedVertexNormal);
					if (d3dmeshFile.bufferData.vertexNormalsCount == 3)
						d3dmeshFile.bufferData.vertexNormals2.push_back(convertedVertexNormal);
					if (d3dmeshFile.bufferData.vertexNormalsCount == 4)
						d3dmeshFile.bufferData.vertexNormals3.push_back(convertedVertexNormal);
				}
			}
			else
			{
				std::cout << "SKIPPING DATA IN VERTEX BUFFER!" << d3dmeshFile.d3dmeshHeader.mName << std::endl;
				BinaryDeserialization::ReadByteBufferFromBinary(&currentD3DMESH_inputFileStream, mVertexBuffer->mCount * mVertexBuffer->mStride); //skip this data block
			}
		}
		//||||||||||||||||||||||||||||||||||||| VERTEX TANGENT |||||||||||||||||||||||||||||||||||||
		//||||||||||||||||||||||||||||||||||||| VERTEX TANGENT |||||||||||||||||||||||||||||||||||||
		//||||||||||||||||||||||||||||||||||||| VERTEX TANGENT |||||||||||||||||||||||||||||||||||||
		else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Tangent)
		{
			if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_SN8x4 && d3dmeshFile.bufferData.vertexTangents.size() <= 0)
			{
				for (int j = 0; j < mVertexBuffer->mCount; j++)
				{
					Vector4 parsedVertexTangent = BinaryDeserialization::ReadT3GFXBuffer_Normalized_4x8BitInteger(&currentD3DMESH_inputFileStream);

					//SELF NOTE: DIVIDING BY THE W COMPONENT WILL CREATE VECTORS OF INFINITY/NAN VALUES, SO DONT DO IT!
					Vector3 convertedVertexTangent;
					convertedVertexTangent.x = parsedVertexTangent.x;
					convertedVertexTangent.y = parsedVertexTangent.y;
					convertedVertexTangent.z = parsedVertexTangent.z;

					d3dmeshFile.bufferData.vertexTangents.push_back(convertedVertexTangent);
				}
			}
			else
			{
				std::cout << "SKIPPING DATA IN VERTEX BUFFER!" << d3dmeshFile.d3dmeshHeader.mName << std::endl;
				BinaryDeserialization::ReadByteBufferFromBinary(&currentD3DMESH_inputFileStream, mVertexBuffer->mCount * mVertexBuffer->mStride); //skip this data block
			}
		}
		//||||||||||||||||||||||||||||||||||||| VERTEX UV |||||||||||||||||||||||||||||||||||||
		//||||||||||||||||||||||||||||||||||||| VERTEX UV |||||||||||||||||||||||||||||||||||||
		//||||||||||||||||||||||||||||||||||||| VERTEX UV |||||||||||||||||||||||||||||||||||||
		else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_TexCoord)
		{
			d3dmeshFile.bufferData.vertexUVsCount++;

			if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_F32x2)
			{
				for (int j = 0; j < mVertexBuffer->mCount; j++)
				{
					Vector2 parsedVertexUV = BinaryDeserialization::ReadT3GFXBuffer_2x32BitFloat(&currentD3DMESH_inputFileStream);

					if (d3dmeshFile.bufferData.vertexUVsCount == 1)
						d3dmeshFile.bufferData.vertexUVs0.push_back(parsedVertexUV);
					if (d3dmeshFile.bufferData.vertexUVsCount == 2)
						d3dmeshFile.bufferData.vertexUVs1.push_back(parsedVertexUV);
					if (d3dmeshFile.bufferData.vertexUVsCount == 3)
						d3dmeshFile.bufferData.vertexUVs2.push_back(parsedVertexUV);
					if (d3dmeshFile.bufferData.vertexUVsCount == 4)
						d3dmeshFile.bufferData.vertexUVs3.push_back(parsedVertexUV);
					if (d3dmeshFile.bufferData.vertexUVsCount == 5)
						d3dmeshFile.bufferData.vertexUVs4.push_back(parsedVertexUV);
					if (d3dmeshFile.bufferData.vertexUVsCount == 6)
						d3dmeshFile.bufferData.vertexUVs5.push_back(parsedVertexUV);
					if (d3dmeshFile.bufferData.vertexUVsCount == 7)
						d3dmeshFile.bufferData.vertexUVs6.push_back(parsedVertexUV);
					if (d3dmeshFile.bufferData.vertexUVsCount == 8)
						d3dmeshFile.bufferData.vertexUVs7.push_back(parsedVertexUV);
				}
			}
			else if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_SN16x2)
			{
				for (int j = 0; j < mVertexBuffer->mCount; j++)
				{
					Vector2 parsedVertexUV = BinaryDeserialization::ReadT3GFXBuffer_Normalized_2x16BitInteger(&currentD3DMESH_inputFileStream);

					if (d3dmeshFile.bufferData.vertexUVsCount == 1)
						d3dmeshFile.bufferData.vertexUVs0.push_back(parsedVertexUV);
					if (d3dmeshFile.bufferData.vertexUVsCount == 2)
						d3dmeshFile.bufferData.vertexUVs1.push_back(parsedVertexUV);
					if (d3dmeshFile.bufferData.vertexUVsCount == 3)
						d3dmeshFile.bufferData.vertexUVs2.push_back(parsedVertexUV);
					if (d3dmeshFile.bufferData.vertexUVsCount == 4)
						d3dmeshFile.bufferData.vertexUVs3.push_back(parsedVertexUV);
					if (d3dmeshFile.bufferData.vertexUVsCount == 5)
						d3dmeshFile.bufferData.vertexUVs4.push_back(parsedVertexUV);
					if (d3dmeshFile.bufferData.vertexUVsCount == 6)
						d3dmeshFile.bufferData.vertexUVs5.push_back(parsedVertexUV);
					if (d3dmeshFile.bufferData.vertexUVsCount == 7)
						d3dmeshFile.bufferData.vertexUVs6.push_back(parsedVertexUV);
					if (d3dmeshFile.bufferData.vertexUVsCount == 8)
						d3dmeshFile.bufferData.vertexUVs7.push_back(parsedVertexUV);
				}
			}
			else
			{
				std::cout << "SKIPPING DATA IN VERTEX BUFFER!" << d3dmeshFile.d3dmeshHeader.mName << std::endl;
				BinaryDeserialization::ReadByteBufferFromBinary(&currentD3DMESH_inputFileStream, mVertexBuffer->mCount * mVertexBuffer->mStride); //skip this data block
			}
		}
		//||||||||||||||||||||||||||||||||||||| VERTEX COLOR |||||||||||||||||||||||||||||||||||||
		//||||||||||||||||||||||||||||||||||||| VERTEX COLOR |||||||||||||||||||||||||||||||||||||
		//||||||||||||||||||||||||||||||||||||| VERTEX COLOR |||||||||||||||||||||||||||||||||||||
		else if (attributeParams->mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Color)
		{
			d3dmeshFile.bufferData.vertexColorsCount++;

			if (attributeParams->mFormat == GFXPlatformFormat::eGFXPlatformFormat_UN8x4)
			{
				for (int j = 0; j < mVertexBuffer->mCount; j++)
				{
					Vector4 parsedVertexColor = BinaryDeserialization::ReadT3GFXBuffer_UnsignedNormalized_4x8BitInteger(&currentD3DMESH_inputFileStream);

					if (d3dmeshFile.bufferData.vertexColorsCount == 1)
						d3dmeshFile.bufferData.vertexColors0.push_back(parsedVertexColor);
					if (d3dmeshFile.bufferData.vertexColorsCount == 2)
						d3dmeshFile.bufferData.vertexColors1.push_back(parsedVertexColor);
					if (d3dmeshFile.bufferData.vertexColorsCount == 3)
						d3dmeshFile.bufferData.vertexColors2.push_back(parsedVertexColor);
					if (d3dmeshFile.bufferData.vertexColorsCount == 4)
						d3dmeshFile.bufferData.vertexColors3.push_back(parsedVertexColor);
					if (d3dmeshFile.bufferData.vertexColorsCount == 5)
						d3dmeshFile.bufferData.vertexColors4.push_back(parsedVertexColor);
					if (d3dmeshFile.bufferData.vertexColorsCount == 6)
						d3dmeshFile.bufferData.vertexColors5.push_back(parsedVertexColor);
					if (d3dmeshFile.bufferData.vertexColorsCount == 7)
						d3dmeshFile.bufferData.vertexColors6.push_back(parsedVertexColor);
					if (d3dmeshFile.bufferData.vertexColorsCount == 8)
						d3dmeshFile.bufferData.vertexColors7.push_back(parsedVertexColor);
				}
			}
			else
			{
				std::cout << "SKIPPING DATA IN VERTEX BUFFER!" << d3dmeshFile.d3dmeshHeader.mName << std::endl;
				BinaryDeserialization::ReadByteBufferFromBinary(&currentD3DMESH_inputFileStream, mVertexBuffer->mCount * mVertexBuffer->mStride); //skip this data block
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
					UnsignedIntegerVector4 parsedVertexBlendIndex = BinaryDeserialization::ReadT3GFXBuffer_Unsigned_4x8BitInteger(&currentD3DMESH_inputFileStream);

					d3dmeshFile.bufferData.vertexBlendIndex0.push_back(parsedVertexBlendIndex);
				}
			}
			else
			{
				std::cout << "SKIPPING DATA IN VERTEX BUFFER!" << d3dmeshFile.d3dmeshHeader.mName << std::endl;
				BinaryDeserialization::ReadByteBufferFromBinary(&currentD3DMESH_inputFileStream, mVertexBuffer->mCount * mVertexBuffer->mStride); //skip this data block
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
					Vector3 parsedVertexBlendWeight = BinaryDeserialization::ReadT3GFXBuffer_UnsignedNormalized_3x10BitInteger_2BitInteger(&currentD3DMESH_inputFileStream, d3dmeshFile.d3dmeshHeader.mPositionWScale);

					d3dmeshFile.bufferData.vertexBlendWeight0.push_back(parsedVertexBlendWeight);
				}
			}
			else
			{
				std::cout << "SKIPPING DATA IN VERTEX BUFFER!" << d3dmeshFile.d3dmeshHeader.mName << std::endl;
				BinaryDeserialization::ReadByteBufferFromBinary(&currentD3DMESH_inputFileStream, mVertexBuffer->mCount * mVertexBuffer->mStride); //skip this data block
			}
		}
		//||||||||||||||||||||||||||||||||||||| SKIP |||||||||||||||||||||||||||||||||||||
		//||||||||||||||||||||||||||||||||||||| SKIP |||||||||||||||||||||||||||||||||||||
		//||||||||||||||||||||||||||||||||||||| SKIP |||||||||||||||||||||||||||||||||||||
		else
		{
			std::cout << "SKIPPING DATA IN VERTEX BUFFER!" << d3dmeshFile.d3dmeshHeader.mName << std::endl;
			BinaryDeserialization::ReadByteBufferFromBinary(&currentD3DMESH_inputFileStream, mVertexBuffer->mCount * mVertexBuffer->mStride); //skip this data block
		}
	}
	//*/

	//|||||||||||||||||||||||||||||||||||||||| END OF FILE ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| END OF FILE ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| END OF FILE ||||||||||||||||||||||||||||||||||||||||
	//We have (hopefully) reached the end of the file!

	//print output so we can check if we actually reached the end of the file. If we did then the bytes left to traverse in the file should be 0.
	unsigned long long totalFileSizeCalculation = metaHeaderSize + d3dmeshFile.metaHeader.mDefaultSectionChunkSize + d3dmeshFile.metaHeader.mAsyncSectionChunkSize;
	unsigned long long currentSeekPosition = currentD3DMESH_inputFileStream.tellg();
	std::cout << "[READER INFO] Left Off At Offset: " << currentSeekPosition << std::endl;
	//std::cout << "[READER INFO] Bytes Left To Traverse In D3DMESH Header: " << (mDefaultSectionChunkSize - (currentSeekPosition - MetaHeaderSize)) << std::endl;
	std::cout << "[READER INFO] Bytes Left To Traverse In File: " << (long)(totalFileSizeCalculation - currentSeekPosition) << std::endl;

	//close the stream, we are done with reading the file
	currentD3DMESH_inputFileStream.close();

	return d3dmeshFile;
}

int main()
{
	//|||||||||||||||||||||||||||||||||||||||| READING D3DMESH FILES FROM DATA FOLDER ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READING D3DMESH FILES FROM DATA FOLDER ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| READING D3DMESH FILES FROM DATA FOLDER ||||||||||||||||||||||||||||||||||||||||
	//First we start by reading all of the .d3dmesh files in the Data folder relative to the application.
	//We read them into multiple array so we can iterate through each one and parse them

	//array of the d3dmesh file paths relative to the application
	std::vector<std::string> d3dmeshFilePaths;

	//array of the d3dmesh file names (with extension) relative to the application
	std::vector<std::string> d3dmeshFileNames;

	//array of the d3dmesh file byte sizes (only used for comparison later to check if we've reached the end of the file)
	std::vector<unsigned long> d3dmeshFileSizes;

	//iterate through every file that we find in the Data/ folder relative to the application
	for (const auto& entry : std::filesystem::recursive_directory_iterator("Data"))
	{
		//extract the following path information
		std::string assetFilePath = entry.path().string();
		std::string assetFileName = entry.path().filename().string();

		//if the extension matches what we are looking for, then add them to our arrays
		if (entry.path().extension() == ".d3dmesh")
		{
			d3dmeshFilePaths.push_back(assetFilePath);
			d3dmeshFileNames.push_back(assetFileName);
			d3dmeshFileSizes.push_back(entry.file_size());
		}
	}

	//|||||||||||||||||||||||||||||||||||||||| PARSING D3DMESH FILES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| PARSING D3DMESH FILES ||||||||||||||||||||||||||||||||||||||||
	//|||||||||||||||||||||||||||||||||||||||| PARSING D3DMESH FILES ||||||||||||||||||||||||||||||||||||||||
	//Here we begin the main logic of parsing the data inside EACH d3dmesh file.

	for (int i = 0; i < d3dmeshFilePaths.size(); i++)
	{
		std::string currentD3DMESH_FilePath = d3dmeshFilePaths[i];
		std::string currentD3DMESH_FileName = d3dmeshFileNames[i];
		unsigned long currentD3DMESH_FileSize = d3dmeshFileSizes[i];

		//|||||||||||||||||||||||||||||||||||||||| OPEN D3DMESH FILE ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| OPEN D3DMESH FILE ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| OPEN D3DMESH FILE ||||||||||||||||||||||||||||||||||||||||
		//Here we open a binary input file stream of the current d3dmesh file

		//print the name to the console so we can see what file we are on
		std::cout << "READING... " << currentD3DMESH_FilePath << std::endl;
		std::cout << "[FILE INFO] File Size Bytes: " << currentD3DMESH_FileSize << std::endl;

		//create and open an input file stream
		std::ifstream currentD3DMESH_inputFileStream;
		currentD3DMESH_inputFileStream.open(currentD3DMESH_FilePath, std::fstream::in | std::fstream::binary);

		//initalize our d3dmesh file object so we can start filling it with data
		FileD3DMesh d3dmeshFile = ParseD3DMeshFile(currentD3DMESH_inputFileStream);

		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V1 ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V1 ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V1 ||||||||||||||||||||||||||||||||||||||||
		//NOTE: This simply shoves the entire mesh into an assimp mesh, ignoring all LODs. 
		//This atleast works for getting a useable mesh export, however there are no materials/lods/submeshes.

		//ExtractedMesh* extractedMesh = &d3dmeshFile.extractedLODs[0].submeshes[0];
		//extractedMesh->triangleIndicies0 = d3dmeshFile.bufferData.triangleIndicies0;
		//extractedMesh->vertexPositions = d3dmeshFile.bufferData.vertexPositions;
		//extractedMesh->vertexNormals0 = d3dmeshFile.bufferData.vertexNormals0;
		//ExportAssimpMesh(*extractedMesh, currentD3DMESH_FileName);

		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V2 ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V2 ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| ASSIMP MODEL EXPORT V2 ||||||||||||||||||||||||||||||||||||||||

		std::vector<ExtractedLOD> extractedLODs;

		for (int i = 0; i < d3dmeshFile.d3dmeshHeader.mLODs.size(); i++)
		{
			T3MeshLOD* mLOD = &d3dmeshFile.d3dmeshHeader.mLODs[i];
			ExtractedLOD extractedLOD{};

			for (int j = 0; j < mLOD->mBatches0_ArrayLength; j++)
			{
				ExtractedMesh extractedMesh{};
				extractedLOD.submeshes.push_back(extractedMesh);
			}

			extractedLODs.push_back(extractedLOD);
		}

		///*
		std::ofstream testOutputTextFile;
		std::string testOutputTextFilePath = "Output/" + currentD3DMESH_FileName + "_EXTRACTED_MESH_DATA.txt";
		testOutputTextFile.open(testOutputTextFilePath);

		for (int x = 0; x < d3dmeshFile.bufferData.indexBuffer0.size(); x++)
		{
			std::string line = "Item: " + std::to_string(x) + " | Triangle Index: " + std::to_string(d3dmeshFile.bufferData.indexBuffer0[x]) + " \n";
			testOutputTextFile.write(line.c_str(), line.length());
		}

		testOutputTextFile.close();

		for (int i = 0; i < d3dmeshFile.d3dmeshHeader.mLODs.size(); i++)
		{
			T3MeshLOD* mLOD = &d3dmeshFile.d3dmeshHeader.mLODs[i];
			ExtractedLOD* extractedLOD = &extractedLODs[i];

			for (int j = 0; j < extractedLOD->submeshes.size(); j++)
			{
				T3MeshBatch* mBatch = &mLOD->mBatches0[j];
				ExtractedMesh* extractedMesh = &extractedLOD->submeshes[j];

				//for (int x = 0; x < mBatch->mNumPrimitives; x++)
					//extractedMesh->triangleIndicies0.push_back(d3dmeshFile.bufferData.triangleIndicies0[x + mBatch->mBaseIndex]);

				//for (int x = 0; x < mBatch->mNumPrimitives; x++)
					//extractedMesh->triangleIndicies0.push_back(d3dmeshFile.bufferData.triangleIndicies0[x + mBatch->mStartIndex] + mBatch->mBaseIndex);

				//for (int x = 0; x < mBatch->mNumPrimitives * 3; x++)
					//extractedMesh->triangleIndicies0.push_back(d3dmeshFile.bufferData.triangleIndicies0[x + mBatch->mStartIndex] + mBatch->mBaseIndex);

				//for (int x = 0; x < mBatch->mNumPrimitives; x++)
				//{
					//extractedMesh->triangleIndicies0.push_back(d3dmeshFile.bufferData.triangleIndicies0[x + mBatch->mStartIndex + mBatch->mBaseIndex]);
					//extractedMesh->triangleIndicies0.push_back(d3dmeshFile.bufferData.triangleIndicies0[x + mBatch->mStartIndex] + mBatch->mBaseIndex);
				//}

				//for (int x = mLOD->mVertexStart + mBatch->mMinVertIndex; x < mLOD->mVertexCount; x++)
				//for (int x = mLOD->mVertexStart; x < mLOD->mVertexCount; x++)
				//{
					//extractedMesh->vertexPositions.push_back(d3dmeshFile.bufferData.vertexPositions[x]);
					//extractedMesh->vertexNormals0.push_back(d3dmeshFile.bufferData.vertexNormals0[x]);
				//}

				std::ofstream testOutputTextFile2;
				std::string newPath2 = "Output/LOD_" + std::to_string(i) + "_SUBMESH_" + std::to_string(j) + "_" + currentD3DMESH_FileName + ".txt";
				testOutputTextFile2.open(newPath2);

				std::string line2a1 = "mNumPrimitives: " + std::to_string(mBatch->mNumPrimitives) + " \n";
				std::string line2a2 = "mBaseIndex: " + std::to_string(mBatch->mBaseIndex) + " \n";
				std::string line2a3 = "mMaxVertIndex: " + std::to_string(mBatch->mMaxVertIndex) + " \n";
				std::string line2a4 = "mMinVertIndex: " + std::to_string(mBatch->mMinVertIndex) + " \n";
				std::string line2a5 = "mStartIndex: " + std::to_string(mBatch->mStartIndex) + " \n";
				std::string line2a6 = "mNumIndices: " + std::to_string(mBatch->mNumIndices) + " \n";
				std::string line2a7 = "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| \n";
				testOutputTextFile2.write(line2a1.c_str(), line2a1.length());
				testOutputTextFile2.write(line2a2.c_str(), line2a2.length());
				testOutputTextFile2.write(line2a3.c_str(), line2a3.length());
				testOutputTextFile2.write(line2a4.c_str(), line2a4.length());
				testOutputTextFile2.write(line2a5.c_str(), line2a5.length());
				testOutputTextFile2.write(line2a6.c_str(), line2a6.length());
				testOutputTextFile2.write(line2a7.c_str(), line2a7.length());

				for (int x = 0; x < mBatch->mNumPrimitives; x++)
				{
					int loopCalculatedIndex = x + mBatch->mStartIndex;
					int pickedTriangleIndex = d3dmeshFile.bufferData.indexBuffer0[loopCalculatedIndex];
					unsigned int adjustedTriangleIndex = pickedTriangleIndex + mBatch->mBaseIndex;
					std::string line2b = "Loop Index: " + std::to_string(x) + " | Calculated Triangle Index Picker: " + std::to_string(loopCalculatedIndex) + " | Picked Triangle Index Original Value: " + std::to_string(pickedTriangleIndex) + " | Triangle Index with added Base Index to value: " + std::to_string(adjustedTriangleIndex) + " \n";
					testOutputTextFile2.write(line2b.c_str(), line2b.length());
				}

				testOutputTextFile2.close();




				//std::string newPath = "LOD_" + std::to_string(i) + "_SUBMESH_" + std::to_string(j) + "_" + currentD3DMESH_FileName;
				//ExportAssimpMesh(*extractedMesh, newPath);
			}
		}
		//*/

		//|||||||||||||||||||||||||||||||||||||||| CONSOLE OUTPUT ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| CONSOLE OUTPUT ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| CONSOLE OUTPUT ||||||||||||||||||||||||||||||||||||||||

		//std::cout << "||||||||||||||||||||||||||||||||||||||||||" << std::endl;
		//std::cout << "||||||||||||||||||||||||||||||||||||||||||" << std::endl;
		//std::cout << "||||||||||||||||||||||||||||||||||||||||||" << std::endl;
		//std::cout << "[D3DMESH HEADER] mNameBlockSize: " << d3dmesh.mNameBlockSize << std::endl;
		//std::cout << "[D3DMESH HEADER] mNameLength: " << d3dmesh.mName.length() << std::endl;
		//std::cout << "[D3DMESH HEADER] mName: " << d3dmesh.mName << std::endl;
		//std::cout << "[D3DMESH HEADER] mVersion: " << mVersion << std::endl;
		//std::cout << "[D3DMESH HEADER] mToolProps: " << mToolProps << std::endl;
		//std::cout << "[D3DMESH HEADER] mLightmapGlobalScale: " << std::to_string(mLightmapGlobalScale) << std::endl;
		//std::cout << "[D3DMESH HEADER] mLightmapTexCoordVersion: " << mLightmapTexCoordVersion << std::endl;
		//std::cout << "[D3DMESH HEADER] mLODParamCRC: " << mLODParamCRC << std::endl;
		//std::cout << "[D3DMESH HEADER] mInternalResourcesCount: " << mInternalResourcesCount << std::endl;
		//std::cout << "[D3DMESH HEADER] mHasOcclusionData: " << d3dmesh.mHasOcclusionData << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mT3MeshDataBlockSize: " << mT3MeshDataBlockSize << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mLODs_ArrayCapacity: " << d3dmesh.mLODs_ArrayCapacity << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mLODs_ArrayLength: " << d3dmesh.mLODs_ArrayLength << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mTextures_ArrayCapacity: " << mTextures_ArrayCapacity << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mTextures_ArrayLength: " << mTextures_ArrayLength << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mMaterials_ArrayCapacity: " << mMaterials_ArrayCapacity << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mMaterials_ArrayLength: " << mMaterials_ArrayLength << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mMaterialOverrides_ArrayCapacity: " << mMaterialOverrides_ArrayCapacity << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mMaterialOverrides_ArrayLength: " << mMaterialOverrides_ArrayLength << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mBones_ArrayCapacity: " << mBones_ArrayCapacity << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mBones_ArrayLength: " << mBones_ArrayLength << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mLocalTransforms_ArrayCapacity: " << mLocalTransforms_ArrayCapacity << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mLocalTransforms_ArrayLength: " << d3dmesh.mLocalTransforms_ArrayLength << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mLocalTransforms_ArrayCapacity: " << mMaterialRequirements_BlockSize << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mPasses_BlockSize: " << mPasses_BlockSize << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mPasses: " << mPasses << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mChannels_BlockSize: " << mChannels_BlockSize << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mChannels1: " << mChannels1 << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mChannels2: " << mChannels2 << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mInputs_BlockSize: " << mInputs_BlockSize << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mInputs1: " << mInputs1 << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mInputs2: " << mInputs2 << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3MATERIALREQUIREMENTS] mInputs3: " << mInputs3 << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mVertexStreams_BlockSize: " << mVertexStreams_BlockSize << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mVertexStreams: " << mVertexStreams << std::endl;
		//std::printf("[D3DMESH HEADER] [T3MESHDATA] [BOUNDING BOX] mMin %f %f %f \n", mBoundingBox.mMin.x, mBoundingBox.mMin.y, mBoundingBox.mMin.z);
		//std::printf("[D3DMESH HEADER] [T3MESHDATA] [BOUNDING BOX] mMax %f %f %f \n", mBoundingBox.mMax.x, mBoundingBox.mMax.y, mBoundingBox.mMax.z);
		//std::printf("[D3DMESH HEADER] [T3MESHDATA] [BOUNDING SPHERE] mCenter %f %f %f \n", mBoundingSphere.mCenter.x, mBoundingSphere.mCenter.y, mBoundingSphere.mCenter.z);
		//std::printf("[D3DMESH HEADER] [T3MESHDATA] [BOUNDING SPHERE] mRadius %f \n", mBoundingSphere.mRadius);
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mEndianType: " << mEndianType << std::endl;
		//std::printf("[D3DMESH HEADER] [T3MESHDATA] mPositionScale %f %f %f \n", mPositionScale.x, mPositionScale.y, mPositionScale.z);
		//std::printf("[D3DMESH HEADER] [T3MESHDATA] mPositionWScale %f %f %f \n", mPositionWScale.x, mPositionWScale.y, mPositionWScale.z);
		//std::printf("[D3DMESH HEADER] [T3MESHDATA] mPositionOffset %f %f %f \n", mPositionOffset.x, mPositionOffset.y, mPositionOffset.z);
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mLightmapTexelAreaPerSurfaceArea: " << std::to_string(mLightmapTexelAreaPerSurfaceArea) << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mPropertyKeyBase: " << mPropertyKeyBase << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mVertexCount: " << mVertexCount << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mFlags: " << mFlags << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] mMeshPreload_BlockSize: " << mMeshPreload_BlockSize << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] UNKNOWN1: " << UNKNOWN1 << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] UNKNOWN2: " << UNKNOWN2 << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3GFXVERTEXSTATE] mVertexCountPerInstance: " << mVertexCountPerInstance << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3GFXVERTEXSTATE] mIndexBufferCount: " << mIndexBufferCount << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3GFXVERTEXSTATE] mVertexBufferCount: " << mVertexBufferCount << std::endl;
		//std::cout << "[D3DMESH HEADER] [T3MESHDATA] [T3GFXVERTEXSTATE] mAttributeCount: " << mAttributeCount << std::endl;

		/*
		for (int GFXPlatformVertexAttributeLoopIndex = 0; GFXPlatformVertexAttributeLoopIndex < d3dmesh.GFXPlatformAttributeParamsArray.size(); GFXPlatformVertexAttributeLoopIndex++)
		{
			GFXPlatformAttributeParams params = d3dmesh.GFXPlatformAttributeParamsArray[GFXPlatformVertexAttributeLoopIndex];

			std::printf("---------------------------------------------\n");
			std::printf("[D3DMESH HEADER] [T3MESHDATA] [GFXPLATFORMATTRIBUTEPARAMS] [ELEMENT %i] mAttribute: %i %s \n", GFXPlatformVertexAttributeLoopIndex, params.mAttribute, GetGFXPlatformVertexAttributeName(params.mAttribute).c_str());
			std::printf("[D3DMESH HEADER] [T3MESHDATA] [GFXPLATFORMATTRIBUTEPARAMS] [ELEMENT %i] mFormat: %i %s \n", GFXPlatformVertexAttributeLoopIndex, params.mFormat, GetGFXPlatformFormatName(params.mFormat).c_str());
			std::printf("[D3DMESH HEADER] [T3MESHDATA] [GFXPLATFORMATTRIBUTEPARAMS] [ELEMENT %i] mAttributeIndex: %i \n", GFXPlatformVertexAttributeLoopIndex, params.mAttributeIndex);
			std::printf("[D3DMESH HEADER] [T3MESHDATA] [GFXPLATFORMATTRIBUTEPARAMS] [ELEMENT %i] mBufferIndex: %i \n", GFXPlatformVertexAttributeLoopIndex, params.mBufferIndex);
			std::printf("[D3DMESH HEADER] [T3MESHDATA] [GFXPLATFORMATTRIBUTEPARAMS] [ELEMENT %i] mBufferOffset: %i \n", GFXPlatformVertexAttributeLoopIndex, params.mBufferOffset);
		}
		*/

		/*
		for (int indexBufferLoopIndex = 0; indexBufferLoopIndex < d3dmesh.mIndexBuffers.size(); indexBufferLoopIndex++)
		{
			T3GFXBuffer mIndexBuffer = ReadTelltaleGFXBufferFromBinary(&currentD3DMESH_inputFileStream);

			std::printf("---------------------------------------------\n");
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mIndexBuffer [ELEMENT %i] mResourceUsage: %i \n", indexBufferLoopIndex, mIndexBuffer.mResourceUsage);
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mIndexBuffer [ELEMENT %i] mBufferFormat: %i %s \n", indexBufferLoopIndex, mIndexBuffer.mBufferFormat, GetGFXPlatformFormatName(mIndexBuffer.mBufferFormat).c_str());
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mIndexBuffer [ELEMENT %i] mBufferUsage: %i \n", indexBufferLoopIndex, mIndexBuffer.mBufferUsage);
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mIndexBuffer [ELEMENT %i] mCount: %i \n", indexBufferLoopIndex, mIndexBuffer.mCount);
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mIndexBuffer [ELEMENT %i] mStride: %i \n", indexBufferLoopIndex, mIndexBuffer.mStride);
		}
		*/

		/*
		for (int vertexBufferLoopIndex = 0; vertexBufferLoopIndex < d3dmesh.mVertexBufferCount; vertexBufferLoopIndex++)
		{
			T3GFXBuffer mVertexBuffer = ReadTelltaleGFXBufferFromBinary(&currentD3DMESH_inputFileStream);

			std::printf("---------------------------------------------\n");
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mVertexBuffer [ELEMENT %i] mResourceUsage: %i \n", vertexBufferLoopIndex, mVertexBuffer.mResourceUsage);
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mVertexBuffer [ELEMENT %i] mBufferFormat: %i %s \n", vertexBufferLoopIndex, mVertexBuffer.mBufferFormat, GetGFXPlatformFormatName(mVertexBuffer.mBufferFormat).c_str());
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mVertexBuffer [ELEMENT %i] mBufferUsage: %i \n", vertexBufferLoopIndex, mVertexBuffer.mBufferUsage);
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mVertexBuffer [ELEMENT %i] mCount: %i \n", vertexBufferLoopIndex, mVertexBuffer.mCount);
			std::printf("[D3DMESH HEADER] [T3MESHDATA] mVertexBuffer [ELEMENT %i] mStride: %i \n", vertexBufferLoopIndex, mVertexBuffer.mStride);
		}
		*/

		/*
		std::printf("Extracted Triangle Indicies %u \n", triangleIndicies0.size());
		std::printf("Extracted Vertex Positions %u \n", vertexPositions.size());

		std::printf("Extracted Vertex Normals (Set 0) %u \n", vertexNormals0.size());

		if (vertexNormals1.size() > 0)
			std::printf("Extracted Vertex Normals (Set 1) %u \n", vertexNormals1.size());
		if (vertexNormals2.size() > 0)
			std::printf("Extracted Vertex Normals (Set 2) %u \n", vertexNormals2.size());
		if (vertexNormals3.size() > 0)
			std::printf("Extracted Vertex Normals (Set 3) %u \n", vertexNormals3.size());

		std::printf("Extracted Vertex Tangents %u \n", vertexTangents.size());
		std::printf("Extracted Vertex UVs(Channel 0) %u \n", vertexUVs0.size());

		if (vertexUVs1.size() > 0)
			std::printf("Extracted Vertex UVs (Channel 1) %u \n", vertexUVs1.size());
		if (vertexUVs2.size() > 0)
			std::printf("Extracted Vertex UVs (Channel 2) %u \n", vertexUVs2.size());
		if (vertexUVs3.size() > 0)
			std::printf("Extracted Vertex UVs (Channel 3) %u \n", vertexUVs3.size());
		if (vertexUVs4.size() > 0)
			std::printf("Extracted Vertex UVs (Channel 4) %u \n", vertexUVs4.size());
		if (vertexUVs5.size() > 0)
			std::printf("Extracted Vertex UVs (Channel 5) %u \n", vertexUVs5.size());
		if (vertexUVs6.size() > 0)
			std::printf("Extracted Vertex UVs (Channel 6) %u \n", vertexUVs6.size());
		if (vertexUVs7.size() > 0)
			std::printf("Extracted Vertex UVs (Channel 7) %u \n", vertexUVs7.size());

		if (vertexColors0.size() > 0)
			std::printf("Extracted Vertex Colors0 %u \n", vertexColors0.size());
		if (vertexColors1.size() > 0)
			std::printf("Extracted Vertex Colors1 %u \n", vertexColors1.size());
		if (vertexColors2.size() > 0)
			std::printf("Extracted Vertex Colors2 %u \n", vertexColors2.size());
		if (vertexColors3.size() > 0)
			std::printf("Extracted Vertex Colors3 %u \n", vertexColors3.size());
		if (vertexColors4.size() > 0)
			std::printf("Extracted Vertex Colors4 %u \n", vertexColors4.size());
		if (vertexColors5.size() > 0)
			std::printf("Extracted Vertex Colors5 %u \n", vertexColors5.size());
		if (vertexColors6.size() > 0)
			std::printf("Extracted Vertex Colors6 %u \n", vertexColors6.size());
		if (vertexColors7.size() > 0)
			std::printf("Extracted Vertex Colors7 %u \n", vertexColors7.size());

		if (vertexBlendIndex0.size() > 0)
			std::printf("Extracted Vertex Blend Index %u \n", vertexBlendIndex0.size());

		if (vertexBlendWeight0.size() > 0)
			std::printf("Extracted Vertex Blend Weight %u \n", vertexBlendWeight0.size());
		*/

		//|||||||||||||||||||||||||||||||||||||||| JSON EXPORT ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| JSON EXPORT ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| JSON EXPORT ||||||||||||||||||||||||||||||||||||||||
		
		/*
		nlohmann::json jsonExport;

		nlohmann::json jsonTelltaleMetaHeader = nlohmann::json
		{
			{ "mMetaStreamVersion", metaHeader.mMetaStreamVersion },
			{ "mDefaultSectionChunkSize", metaHeader.mDefaultSectionChunkSize },
			{ "mDebugSectionChunkSize", metaHeader.mDebugSectionChunkSize },
			{ "mAsyncSectionChunkSize", metaHeader.mAsyncSectionChunkSize },
			{ "mClassNamesLength", metaHeader.mClassNamesLength },
		};

		Vector2 testVector2 = Vector2();

		testVector2.ToJson(jsonExport);

		std::ofstream jsonOutputFileStream;
		std::string jsonExportPath = "OutputJSON/" + currentD3DMESH_FileName + ".json";
		jsonOutputFileStream.open(jsonExportPath);

		std::string jsonDump = jsonExport.dump(4);
		jsonOutputFileStream.write(jsonDump.c_str(), jsonDump.length());

		jsonOutputFileStream.close();
		*/

		//|||||||||||||||||||||||||||||||||||||||| D3DMESH EXPORT ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| D3DMESH EXPORT ||||||||||||||||||||||||||||||||||||||||
		//|||||||||||||||||||||||||||||||||||||||| D3DMESH EXPORT ||||||||||||||||||||||||||||||||||||||||
		/*
		//recalculate values
		d3dmesh.mNameBlockSize = 8 + d3dmesh.mName.length();

		std::ofstream d3dmeshOutputFileStream;
		std::string d3dmeshExportPath = "OutputD3DMESH/" + currentD3DMESH_FileName;
		d3dmeshOutputFileStream.open(d3dmeshExportPath, std::ios::binary);

		//telltale meta header
		metaHeader.BinarySerialize(&d3dmeshOutputFileStream);

		//d3dmesh header
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mNameBlockSize);
		BinarySerialization::WriteLengthPrefixedStringToBinary(&d3dmeshOutputFileStream, d3dmesh.mName);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mVersion);
		BinarySerialization::WriteUInt8ToBinary(&d3dmeshOutputFileStream, d3dmesh.mToolProps);
		BinarySerialization::WriteFloat32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mLightmapGlobalScale);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mLightmapTexCoordVersion);
		d3dmesh.mLODParamCRC.BinarySerialize(&d3dmeshOutputFileStream);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mInternalResourcesCount);

		for (int mInternalResourceIndex = 0; mInternalResourceIndex < d3dmesh.mInternalResourcesCount; mInternalResourceIndex++)
		{
			d3dmesh.mInternalResources[mInternalResourceIndex].BinarySerialize(&d3dmeshOutputFileStream);
		}

		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mToolPropsBlockSize);
		BinarySerialization::WriteByteBufferToBinary(&d3dmeshOutputFileStream, d3dmesh.mToolPropsBlockSize - 4, d3dmesh.mToolPropsData);
		BinarySerialization::WriteUInt8ToBinary(&d3dmeshOutputFileStream, d3dmesh.mHasOcclusionData);

		//if this is true then we need to skip it (ASCII '1' is true, ASCII '0' is false)
		if (d3dmesh.mHasOcclusionData == '1')
		{
			BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mOcclusionDataBlockSize);
			BinarySerialization::WriteByteBufferToBinary(&d3dmeshOutputFileStream, d3dmesh.mOcclusionDataBlockSize - 4, d3dmesh.mOcclusionData);
		}

		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mT3MeshDataBlockSize);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mLODs_ArrayCapacity);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mLODs_ArrayLength);

		for (int i = 0; i < d3dmesh.mLODs_ArrayLength; i++)
		{
			d3dmesh.mLODs[i].BinarySerialize(&d3dmeshOutputFileStream);
		}

		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mTextures_ArrayCapacity);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mTextures_ArrayLength);
		BinarySerialization::WriteByteBufferToBinary(&d3dmeshOutputFileStream, d3dmesh.mTextures_ArrayCapacity - 8, d3dmesh.mTexturesData);

		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mMaterials_ArrayCapacity);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mMaterials_ArrayLength);
		BinarySerialization::WriteByteBufferToBinary(&d3dmeshOutputFileStream, d3dmesh.mMaterials_ArrayCapacity - 8, d3dmesh.mMaterialsData);

		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mMaterialOverrides_ArrayCapacity);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mMaterialOverrides_ArrayLength);
		BinarySerialization::WriteByteBufferToBinary(&d3dmeshOutputFileStream, d3dmesh.mMaterialOverrides_ArrayCapacity - 8, d3dmesh.mMaterialOverridesData);

		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mBones_ArrayCapacity);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mBones_ArrayLength);

		for (int i = 0; i < d3dmesh.mBones_ArrayLength; i++)
		{
			d3dmesh.mBones[i].BinarySerialize(&d3dmeshOutputFileStream);
		}

		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mLocalTransforms_ArrayCapacity);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mLocalTransforms_ArrayLength);

		for (int i = 0; i < d3dmesh.mLocalTransforms_ArrayLength; i++)
		{
			d3dmesh.mLocalTransforms[i].BinarySerialize(&d3dmeshOutputFileStream);
		}

		d3dmesh.mMaterialRequirements.BinarySerialize(&d3dmeshOutputFileStream);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mVertexStreams_BlockSize);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mVertexStreams);
		d3dmesh.mBoundingBox.BinarySerialize(&d3dmeshOutputFileStream);
		d3dmesh.mBoundingSphere.BinarySerialize(&d3dmeshOutputFileStream);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mEndianType);
		d3dmesh.mPositionScale.BinarySerialize(&d3dmeshOutputFileStream);
		d3dmesh.mPositionWScale.BinarySerialize(&d3dmeshOutputFileStream);
		d3dmesh.mPositionOffset.BinarySerialize(&d3dmeshOutputFileStream);
		BinarySerialization::WriteFloat32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mLightmapTexelAreaPerSurfaceArea);
		d3dmesh.mPropertyKeyBase.BinarySerialize(&d3dmeshOutputFileStream);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mVertexCount);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mFlags);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mMeshPreload_BlockSize);
		BinarySerialization::WriteByteBufferToBinary(&d3dmeshOutputFileStream, d3dmesh.mMeshPreload_BlockSize - 4, d3dmesh.mMeshPreloadData);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.UNKNOWN1);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.UNKNOWN2);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mVertexCountPerInstance);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mIndexBufferCount);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mVertexBufferCount);
		BinarySerialization::WriteUInt32ToBinary(&d3dmeshOutputFileStream, d3dmesh.mAttributeCount);

		for (int i = 0; i < d3dmesh.mAttributeCount; i++)
		{
			d3dmesh.GFXPlatformAttributeParamsArray[i].BinarySerialize(&d3dmeshOutputFileStream);
		}

		for (int i = 0; i < d3dmesh.mIndexBufferCount; i++)
		{
			d3dmesh.mIndexBuffers[i].BinarySerialize(&d3dmeshOutputFileStream);
		}

		for (int i = 0; i < d3dmesh.mVertexBufferCount; i++)
		{
			d3dmesh.mVertexBuffers[i].BinarySerialize(&d3dmeshOutputFileStream);
		}

		d3dmeshOutputFileStream.close();
		*/
	}

	return 0;
}
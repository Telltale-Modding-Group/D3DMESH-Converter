#pragma once
#ifndef XATLAS_HELPER_H
#define XATLAS_HELPER_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: xatlas library
#include <xatlas.h>

//Custom
#include "../../AssimpMeshProxy.h"
#include "../../Telltale/DataTypes/Vector3.h"

static void Test(AssimpMeshProxy& assimpMeshProxy)
{
	xatlas::MeshDecl meshDeclaration = xatlas::MeshDecl();

	meshDeclaration.vertexCount = assimpMeshProxy.vertexPosition.size();
	meshDeclaration.vertexPositionData = assimpMeshProxy.vertexPosition.data();
	meshDeclaration.vertexPositionStride = sizeof(Vector3);

	meshDeclaration.vertexNormalData = assimpMeshProxy.vertexNormal.data();
	meshDeclaration.vertexNormalStride = sizeof(Vector3);

	meshDeclaration.vertexUvData = assimpMeshProxy.vertexUV.data();
	meshDeclaration.vertexUvStride = sizeof(Vector2);

	meshDeclaration.indexCount = assimpMeshProxy.indices.size();
	meshDeclaration.indexData = assimpMeshProxy.indices.data();
	meshDeclaration.indexOffset = 0;
	meshDeclaration.indexFormat = xatlas::IndexFormat::UInt32;

	meshDeclaration.faceCount = assimpMeshProxy.indices.size() / 3.0f;

	xatlas::Atlas* newAtlas = xatlas::Create();
	xatlas::AddMesh(newAtlas, meshDeclaration);
	xatlas::Generate(newAtlas);

	xatlas::Destroy(newAtlas);
}

#endif
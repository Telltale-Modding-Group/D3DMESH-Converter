#pragma once
#ifndef ASSIMP_HELPER_H
#define ASSIMP_HELPER_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: ASSIMP Library
#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>

//Standard C++ Library
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <stdlib.h>

//Custom
#include "../../Telltale/DataTypes/Vector4.h"
#include "../../Telltale/DataTypes/Vector3.h"
#include "../../Math.h"
#include "../../MikkTSpace.h"

//||||||||||||||||||||||||||||| ASSIMP HELPER |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| ASSIMP HELPER |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| ASSIMP HELPER |||||||||||||||||||||||||||||

static aiVector3D GetAssimpVector3FromVector4(Vector4 value)
{
	return aiVector3D(value.x, value.y, value.z);
}

static aiColor4D GetAssimpColor4FromVector4(Vector4 value)
{
	return aiColor4D(value.x, value.y, value.z, value.w);
}

static Vector4 GetVector4FromAssimpVector3(aiVector3D value)
{
	return Vector4(value.x, value.y, value.z, 0.0f);
}

static Vector4 GetVector4FromAssimpColor4(aiColor4D value)
{
	return Vector4(value.r, value.g, value.b, value.a);
}

static Vector3 GetVector3FromAssimpVector3(aiVector3D value)
{
    return Vector3(value.x, value.y, value.z);
}

static Vector2 GetVector2FromAssimpVector3(aiVector3D value)
{
    return Vector2(value.x, value.y);
}

//https://terathon.com/blog/tangent-space.html
static std::vector<Vector4> CalculateTangentsFromMesh(aiMesh* assimpMesh, unsigned int uvIndex = 0)
{
    std::vector<Vector4> newTangents;

    Vector3* tan1 = new Vector3[assimpMesh->mNumVertices * 2];
    Vector3* tan2 = tan1 + assimpMesh->mNumVertices;
    memset(tan1, 0, assimpMesh->mNumVertices * sizeof(Vector3) * 2);

    for (long a = 0; a < assimpMesh->mNumFaces; a++)
    {
        aiFace* face = &assimpMesh->mFaces[a];

        long i1 = face->mIndices[0];
        long i2 = face->mIndices[1];
        long i3 = face->mIndices[2];

        const Vector3& v1 = GetVector3FromAssimpVector3(assimpMesh->mVertices[i1]);
        const Vector3& v2 = GetVector3FromAssimpVector3(assimpMesh->mVertices[i2]);
        const Vector3& v3 = GetVector3FromAssimpVector3(assimpMesh->mVertices[i3]);

        const Vector2& w1 = GetVector2FromAssimpVector3(assimpMesh->mTextureCoords[uvIndex][i1]);
        const Vector2& w2 = GetVector2FromAssimpVector3(assimpMesh->mTextureCoords[uvIndex][i2]);
        const Vector2& w3 = GetVector2FromAssimpVector3(assimpMesh->mTextureCoords[uvIndex][i3]);

        float x1 = v2.x - v1.x;
        float x2 = v3.x - v1.x;
        float y1 = v2.y - v1.y;
        float y2 = v3.y - v1.y;
        float z1 = v2.z - v1.z;
        float z2 = v3.z - v1.z;

        float s1 = w2.x - w1.x;
        float s2 = w3.x - w1.x;
        float t1 = w2.y - w1.y;
        float t2 = w3.y - w1.y;

        float r = 1.0F / (s1 * t2 - s2 * t1);

        Vector3 sdir = Vector3(
            (t2 * x1 - t1 * x2) * r, 
            (t2 * y1 - t1 * y2) * r,
            (t2 * z1 - t1 * z2) * r);

        Vector3 tdir = Vector3(
            (s1 * x2 - s2 * x1) * r, 
            (s1 * y2 - s2 * y1) * r,
            (s1 * z2 - s2 * z1) * r);

        tan1[i1] += sdir;
        tan1[i2] += sdir;
        tan1[i3] += sdir;

        tan2[i1] += tdir;
        tan2[i2] += tdir;
        tan2[i3] += tdir;
    }

    for (long a = 0; a < assimpMesh->mNumVertices; a++)
    {
        Vector3 n = GetVector3FromAssimpVector3(assimpMesh->mNormals[a]);
        Vector3 t = tan1[a];

        // Gram-Schmidt orthogonalize
        Vector3 orthogonalize = (t - n * Dot(n, t));
        orthogonalize.Normalize();

        Vector4 tangent = Vector4();
        tangent.x = orthogonalize.x;
        tangent.y = orthogonalize.y;
        tangent.z = orthogonalize.z;

        // Calculate handedness
        tangent.w = (Dot(Cross(n, t), tan2[a]) < 0.0F) ? -1.0F : 1.0F;

        newTangents.push_back(tangent);
    }

    delete[] tan1;

    return newTangents;
}

static std::vector<Vector4> CalculateMikkTangentsFromMesh(aiMesh* assimpMesh, unsigned int uvIndex = 0)
{
    AssimpMeshProxy assimpMeshProxy = AssimpMeshProxy(assimpMesh, uvIndex);
    CalcMikkTangents calcMikkTangents = CalcMikkTangents();
    calcMikkTangents.calc(&assimpMeshProxy);
    return assimpMeshProxy.vertexTangents;
}
#endif
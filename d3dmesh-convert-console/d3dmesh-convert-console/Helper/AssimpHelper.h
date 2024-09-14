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

//THIRD PARTY: GLM Library
#include <glm.hpp>

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
#include "../../Helper/GLMHelper.h"
#include "../../Helper/MikkTSpaceHelper.h"

//||||||||||||||||||||||||||||| TELLTALE TYPES TO ASSIMP TYPES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE TYPES TO ASSIMP TYPES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TELLTALE TYPES TO ASSIMP TYPES |||||||||||||||||||||||||||||

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

//||||||||||||||||||||||||||||| GLM TYPES TO ASSIMP TYPES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| GLM TYPES TO ASSIMP TYPES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| GLM TYPES TO ASSIMP TYPES |||||||||||||||||||||||||||||

//aiVector3D <- vec4
static aiVector3D GetAssimpVector3From_vec4(glm::vec4 value)
{
    return aiVector3D(value.x, value.y, value.z);
}

static aiVector3D GetAssimpVector3From_ivec4(glm::ivec4 value)
{
    return aiVector3D(value.x, value.y, value.z);
}

static aiVector3D GetAssimpVector3From_uvec4(glm::uvec4 value)
{
    return aiVector3D(value.x, value.y, value.z);
}

//aiVector3D <- vec3
static aiVector3D GetAssimpVector3From_vec3(glm::vec3 value)
{
    return aiVector3D(value.x, value.y, value.z);
}

static aiVector3D GetAssimpVector3From_ivec3(glm::ivec3 value)
{
    return aiVector3D(value.x, value.y, value.z);
}

static aiVector3D GetAssimpVector3From_uvec3(glm::uvec3 value)
{
    return aiVector3D(value.x, value.y, value.z);
}

//aiColor4D <- vec4
static aiColor4D GetAssimpColor4From_vec4(glm::vec4 value)
{
    return aiColor4D(value.x, value.y, value.z, value.w);
}

static aiColor4D GetAssimpColor4From_ivec4(glm::ivec4 value)
{
    return aiColor4D(value.x, value.y, value.z, value.w);
}

static aiColor4D GetAssimpColor4From_uvec4(glm::uvec4 value)
{
    return aiColor4D(value.x, value.y, value.z, value.w);
}

//vec4 <- aiVector3D
static glm::vec4 Get_vec4_FromAssimpVector3(aiVector3D value)
{
    return glm::vec4(value.x, value.y, value.z, 0.0f);
}

static glm::ivec4 Get_ivec4_FromAssimpVector3(aiVector3D value)
{
    return glm::ivec4((int)value.x, (int)value.y, (int)value.z, 0);
}

static glm::uvec4 Get_uvec4_FromAssimpVector3(aiVector3D value)
{
    return glm::uvec4((unsigned int)value.x, (unsigned int)value.y, (unsigned int)value.z, 0);
}

//vec3 <- aiVector3D
static glm::vec3 Get_vec3_FromAssimpVector3(aiVector3D value)
{
    return glm::vec3(value.x, value.y, value.z);
}

static glm::ivec3 Get_ivec3_FromAssimpVector3(aiVector3D value)
{
    return glm::ivec3((int)value.x, (int)value.y, (int)value.z);
}

static glm::uvec3 Get_uvec3_FromAssimpVector3(aiVector3D value)
{
    return glm::uvec3((unsigned int)value.x, (unsigned int)value.y, (unsigned int)value.z);
}

//vec4 <- aiColor4D
static glm::vec4 Get_vec4_FromAssimpColor4(aiColor4D value)
{
    return glm::vec4(value.r, value.g, value.b, value.a);
}

static glm::ivec4 Get_ivec4_FromAssimpColor4(aiColor4D value)
{
    return glm::ivec4((int)value.r, (int)value.g, (int)value.b, (int)value.a);
}

static glm::uvec4 Get_uvec4_FromAssimpColor4(aiColor4D value)
{
    return glm::uvec4((unsigned int)value.r, (unsigned int)value.g, (unsigned int)value.b, (unsigned int)value.a);
}

//vec2 <- aiVector3D
static glm::vec2 Get_vec2_FromAssimpVector3(aiVector3D value)
{
    return glm::vec2(value.x, value.y);
}

static glm::ivec2 Get_ivec2_FromAssimpVector3(aiVector3D value)
{
    return glm::ivec2((int)value.x, (int)value.y);
}

static glm::uvec2 Get_uvec2_FromAssimpVector3(aiVector3D value)
{
    return glm::uvec2((unsigned int)value.x, (unsigned int)value.y);
}

//||||||||||||||||||||||||||||| TANGENT RECALCULATIONS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TANGENT RECALCULATIONS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| TANGENT RECALCULATIONS |||||||||||||||||||||||||||||

//https://terathon.com/blog/tangent-space.html
static std::vector<Vector4> CalculateTangentsFromMesh(aiMesh* assimpMesh, unsigned int uvIndex = 0)
{
    std::vector<Vector4> newTangents;

    glm::vec3* tan1 = new glm::vec3[assimpMesh->mNumVertices * 2];
    glm::vec3* tan2 = tan1 + assimpMesh->mNumVertices;
    memset(tan1, 0, assimpMesh->mNumVertices * sizeof(glm::vec3) * 2);

    for (long a = 0; a < assimpMesh->mNumFaces; a++)
    {
        aiFace* face = &assimpMesh->mFaces[a];

        long i1 = face->mIndices[0];
        long i2 = face->mIndices[1];
        long i3 = face->mIndices[2];

        const glm::vec3& v1 = Get_vec3_FromAssimpVector3(assimpMesh->mVertices[i1]);
        const glm::vec3& v2 = Get_vec3_FromAssimpVector3(assimpMesh->mVertices[i2]);
        const glm::vec3& v3 = Get_vec3_FromAssimpVector3(assimpMesh->mVertices[i3]);

        const glm::vec2& w1 = Get_vec2_FromAssimpVector3(assimpMesh->mTextureCoords[uvIndex][i1]);
        const glm::vec2& w2 = Get_vec2_FromAssimpVector3(assimpMesh->mTextureCoords[uvIndex][i2]);
        const glm::vec2& w3 = Get_vec2_FromAssimpVector3(assimpMesh->mTextureCoords[uvIndex][i3]);

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

        glm::vec3 sdir = glm::vec3(
            (t2 * x1 - t1 * x2) * r, 
            (t2 * y1 - t1 * y2) * r,
            (t2 * z1 - t1 * z2) * r);

        glm::vec3 tdir = glm::vec3(
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
        glm::vec3 n = Get_vec3_FromAssimpVector3(assimpMesh->mNormals[a]);
        glm::vec3 t = tan1[a];

        // Gram-Schmidt orthogonalize
        glm::vec3 orthogonalize = (t - n * glm::dot(n, t));
        orthogonalize = glm::normalize(orthogonalize);

        Vector4 tangent = Vector4();
        tangent.x = orthogonalize.x;
        tangent.y = orthogonalize.y;
        tangent.z = orthogonalize.z;

        // Calculate handedness
        tangent.w = (glm::dot(glm::cross(n, t), tan2[a]) < 0.0f) ? -1.0f : 1.0f;

        newTangents.push_back(tangent);
    }

    delete[] tan1;

    return newTangents;
}

static std::vector<Vector4> CalculateMikkTangentsFromMesh(aiMesh* assimpMesh, unsigned int uvIndex = 0)
{
    AssimpMeshProxy assimpMeshProxy = AssimpMeshProxy(assimpMesh, uvIndex);
    CalcMikkTangentsHelper calcMikkTangents = CalcMikkTangentsHelper();
    calcMikkTangents.calc(&assimpMeshProxy);
    return assimpMeshProxy.vertexTangents;
}
#endif
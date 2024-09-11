#pragma once
#ifndef GLM_HELPER_H
#define GLM_HELPER_H

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
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/quaternion.hpp>

//Standard C++ Library
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <stdlib.h>

//Custom
#include "../../Telltale/DataTypes/Vector2.h"
#include "../../Telltale/DataTypes/Vector3.h"
#include "../../Telltale/DataTypes/Vector4.h"
#include "../../Telltale/DataTypes/Quaternion.h"

#include "../../CustomTypes/IntegerVector2.h"
#include "../../CustomTypes/IntegerVector3.h"
#include "../../CustomTypes/IntegerVector4.h"

#include "../../CustomTypes/UnsignedIntegerVector2.h"
#include "../../CustomTypes/UnsignedIntegerVector3.h"
#include "../../CustomTypes/UnsignedIntegerVector4.h"

//quat
static glm::quat Get_quat_FromQuaternion(Quaternion quaternion)
{
	return glm::quat(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
}

//vec
static glm::vec2 Get_vec2_FromVector2(Vector2 vector)
{
	return glm::vec2(vector.x, vector.y);
}

static glm::vec3 Get_vec3_FromVector3(Vector3 vector)
{
	return glm::vec3(vector.x, vector.y, vector.z);
}

static glm::vec4 Get_vec4_FromVector4(Vector4 vector)
{
	return glm::vec4(vector.x, vector.y, vector.z, vector.w);
}

//ivec
static glm::ivec2 Get_ivec2_FromIntegerVector2(IntegerVector2 vector)
{
	return glm::ivec2(vector.x, vector.y);
}

static glm::ivec3 Get_ivec3_FromIntegerVector3(IntegerVector3 vector)
{
	return glm::ivec3(vector.x, vector.y, vector.z);
}

static glm::ivec4 Get_ivec4_FromIntegerVector4(IntegerVector4 vector)
{
	return glm::ivec4(vector.x, vector.y, vector.z, vector.w);
}

//uvec
static glm::uvec2 Get_uvec2_FromUnsignedIntegerVector2(UnsignedIntegerVector2 vector)
{
	return glm::uvec2(vector.x, vector.y);
}

static glm::uvec3 Get_uvec3_FromUnsignedIntegerVector3(UnsignedIntegerVector3 vector)
{
	return glm::uvec3(vector.x, vector.y, vector.z);
}

static glm::uvec4 Get_uvec4_FromUnsignedIntegerVector4(UnsignedIntegerVector4 vector)
{
	return glm::uvec4(vector.x, vector.y, vector.z, vector.w);
}

#endif
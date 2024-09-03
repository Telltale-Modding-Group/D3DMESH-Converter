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
#include "Vector2.h"
#include "Vector4.h"

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

#endif
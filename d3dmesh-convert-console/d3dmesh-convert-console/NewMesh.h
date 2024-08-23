#pragma once
#ifndef NEW_MESH_H
#define NEW_MESH_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: JSON Library
#include <nlohmann/json.hpp>

//Custom
#include "BinarySerialization.h"
#include "BinaryDeserialization.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "UnsignedIntegerVector4.h"

//||||||||||||||||||||||||||||| NEW MESH |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| NEW MESH |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| NEW MESH |||||||||||||||||||||||||||||

class NewMesh
{
public:

	int indexBufferCount = 0;
	int vertexNormalsCount = 0;
	int vertexUVsCount = 0;
	int vertexColorsCount = 0;

	std::vector<unsigned short> triangleIndicies;

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
};

#endif
#pragma once
#ifndef APPLICATION_MACROS_H
#define APPLICATION_MACROS_H

//||||||||||||||||||||||||||||| PREPROCESSOR MACROS / ASSIMP OPTIONS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| PREPROCESSOR MACROS / ASSIMP OPTIONS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| PREPROCESSOR MACROS / ASSIMP OPTIONS |||||||||||||||||||||||||||||

//assimp export options
#define ASSIMP_EXPORT_D3DMESH_SHADOW

//assimp supported export formats
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

#define ASSIMP_EXPORT_ID "fbx"
#define ASSIMP_EXPORT_EXTENSION "fbx"

//||||||||||||||||||||||||||||| PREPROCESSOR MACROS / FILE EXTENSIONS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| PREPROCESSOR MACROS / FILE EXTENSIONS |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| PREPROCESSOR MACROS / FILE EXTENSIONS |||||||||||||||||||||||||||||

//file extensions
#define D3DMESH_EXTENSION ".d3dmesh"
#define SKL_EXTENSION ".skl"
#define JSON_EXTENSION ".json"
//#define ASSIMP_EXTENSION ".fbx"
#define ASSIMP_EXTENSION ".glb"

//||||||||||||||||||||||||||||| PREPROCESSOR MACROS / DEBUG DIRECTORIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| PREPROCESSOR MACROS / DEBUG DIRECTORIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| PREPROCESSOR MACROS / DEBUG DIRECTORIES |||||||||||||||||||||||||||||

//input directories
//#define INPUT_DIRECTORY_D3DMESH "DebugWorkingDirectory/InputD3DMESH"
#define INPUT_DIRECTORY_D3DMESH "DebugWorkingDirectory/InputD3DMESH_MODIFIED"
#define INPUT_DIRECTORY_D3DMESH_AND_SKL "DebugWorkingDirectory/InputD3DMESH_AND_SKL"
#define INPUT_DIRECTORY_D3DMESH_JSON "DebugWorkingDirectory/InputD3DMESH_JSON"
#define INPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP "DebugWorkingDirectory/InputD3DMESH_JSON_AND_ASSIMP"
#define INPUT_DIRECTORY_SKL "DebugWorkingDirectory/InputSKL"
#define INPUT_DIRECTORY_SKL_JSON "DebugWorkingDirectory/InputSKL_JSON"

//output directories
#define OUTPUT_DIRECTORY_ASSIMP_TO_D3DMESH "DebugWorkingDirectory/OutputASSIMP_TO_D3DMESH/"
#define OUTPUT_DIRECTORY_D3DMESH_JSON_AND_ASSIMP "DebugWorkingDirectory/OutputD3DMESH_JSON_AND_ASSIMP/"
#define OUTPUT_DIRECTORY_D3DMESH_TO_ASSIMP "DebugWorkingDirectory/OutputD3DMESH_TO_ASSIMP/"
#define OUTPUT_DIRECTORY_D3DMESH_TO_D3DMESH "DebugWorkingDirectory/OutputD3DMESH_TO_D3DMESH/"
#define OUTPUT_DIRECTORY_D3DMESH_TO_JSON "DebugWorkingDirectory/OutputD3DMESH_TO_JSON/"
#define OUTPUT_DIRECTORY_JSON_TO_D3DMESH "DebugWorkingDirectory/OutputJSON_TO_D3DMESH/"
#define OUTPUT_DIRECTORY_JSON_TO_SKL "DebugWorkingDirectory/OutputJSON_TO_SKL/"
#define OUTPUT_DIRECTORY_SKL_TO_JSON "DebugWorkingDirectory/OutputSKL_TO_JSON/"
#define OUTPUT_DIRECTORY_SKL_TO_SKL "DebugWorkingDirectory/OutputSKL_TO_SKL/"

#endif
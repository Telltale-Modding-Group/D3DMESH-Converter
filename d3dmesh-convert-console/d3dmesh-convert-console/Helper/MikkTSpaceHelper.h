#pragma once
#ifndef MIKKTSPACE_HELPER_H
#define MIKKTSPACE_HELPER_H

//REFERENCE IMPLEMENTATION - https://www.turais.de/using-mikktspace-in-your-project/
//SOURCE - https://github.com/mmikk/MikkTSpace

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//THIRD PARTY: mikktspace
#define __cplusplus
#include <mikktspace.h>

//Custom
#include "../../AssimpMeshProxy.h"

class CalcMikkTangentsHelper
{
public:
    CalcMikkTangentsHelper()
    {
        iface.m_getNumFaces = get_num_faces;
        iface.m_getNumVerticesOfFace = get_num_vertices_of_face;

        iface.m_getNormal = get_normal;
        iface.m_getPosition = get_position;
        iface.m_getTexCoord = get_tex_coords;
        iface.m_setTSpaceBasic = set_tspace_basic;

        context.m_pInterface = &iface;
    }

    void calc(AssimpMeshProxy* mesh)
    {
        context.m_pUserData = mesh;
        genTangSpaceDefault(&this->context);
    }

private:
    SMikkTSpaceInterface iface{};
    SMikkTSpaceContext context{};

    static int get_vertex_index(const SMikkTSpaceContext* context, int iFace, int iVert)
    {
        AssimpMeshProxy* working_mesh = static_cast<AssimpMeshProxy*> (context->m_pUserData);

        auto face_size = get_num_vertices_of_face(context, iFace);
        auto indices_index = (iFace * face_size) + iVert;

        int index = working_mesh->indices[indices_index];
        return index;
    }

    static int get_num_faces(const SMikkTSpaceContext* context)
    {
        AssimpMeshProxy* working_mesh = static_cast<AssimpMeshProxy*> (context->m_pUserData);

        float f_size = (float)working_mesh->faceCount;
        int i_size = (int)working_mesh->faceCount;

        return i_size;
    }

    static int get_num_vertices_of_face(const SMikkTSpaceContext* context, int iFace)
    {
        return 3;
    }

    static void get_position(const SMikkTSpaceContext* context, float outpos[], int iFace, int iVert)
    {
        AssimpMeshProxy* working_mesh = static_cast<AssimpMeshProxy*> (context->m_pUserData);
        auto index = get_vertex_index(context, iFace, iVert);
        outpos[0] = working_mesh->vertexPosition[index].x;
        outpos[1] = working_mesh->vertexPosition[index].y;
        outpos[2] = working_mesh->vertexPosition[index].z;
    }

    static void get_normal(const SMikkTSpaceContext* context, float outnormal[], int iFace, int iVert)
    {
        AssimpMeshProxy* working_mesh = static_cast<AssimpMeshProxy*> (context->m_pUserData);
        auto index = get_vertex_index(context, iFace, iVert);
        outnormal[0] = working_mesh->vertexNormal[index].x;
        outnormal[1] = working_mesh->vertexNormal[index].y;
        outnormal[2] = working_mesh->vertexNormal[index].z;
    }

    static void get_tex_coords(const SMikkTSpaceContext* context, float outuv[], int iFace, int iVert)
    {
        AssimpMeshProxy* working_mesh = static_cast<AssimpMeshProxy*> (context->m_pUserData);
        auto index = get_vertex_index(context, iFace, iVert);
        outuv[0] = working_mesh->vertexUV[index].x;
        outuv[1] = working_mesh->vertexUV[index].y;
    }

    static void set_tspace_basic(const SMikkTSpaceContext* context, const float tangentu[], float fSign, int iFace, int iVert)
    {
        AssimpMeshProxy* working_mesh = static_cast<AssimpMeshProxy*> (context->m_pUserData);
        auto index = get_vertex_index(context, iFace, iVert);
        auto* vertex = &working_mesh->vertexTangents[index];

        vertex->x = tangentu[0];
        vertex->y = tangentu[1];
        vertex->z = tangentu[2];
        vertex->w = fSign;
    }
};

#endif
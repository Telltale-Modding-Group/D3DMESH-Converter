using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace converter
{
    public struct Bone_Info_Struct
    {
        public uint Bone1;
        public uint Bone2;
        public uint Bone3;
        public uint Bone4;
    }

    public struct Weight_Info_Struct
    {
        public float Weight1;
        public float Weight2;
        public float Weight3;
        public float Weight4;
    }

    public struct Weight_data
    {
        public List<uint> BoneIDs;
        public List<float> weights;
    }

    public struct Polygon_Info_Struct
    {
        public uint VertexMin;
        public uint VertexMax;
        public uint PolygonStart;
        public uint PolygonCount;
        public uint FacePointCount;
        public string MatName;
        public uint BoneSetNum;
        public uint SingleBindNode;
    }

    //Version 5: The Walking Dead Season 1[PC]
    public struct Polygon_Info_V5_Struct
    {
        public uint VertexMin;
        public uint VertexMax;
        public uint PolygonStart;
        public uint PolygonCount;
        public uint FacePointCount;

        public uint DifNum;
        public uint BakeNum;
        public uint BumpNum;
        public uint EnvNum;
        public uint DtlDifNum;
        public uint DtlBumpNum;
        public uint SpecNum;
        public uint Tex8Num;
        public uint GrdNum;
        public uint Tex10Num;
        public uint ShdNum;

        public uint BoneSetNum;
        public uint SingleBindNode;
    }

    public struct Color_Data
    {
        public float r;
        public float g;
        public float b;
        public float a;
    }

    public struct Normal_Data
    {
        public float x;
        public float y;
        public float z;
        public float q;
    }

    public struct Binormal_Data
    {
        public float x;
        public float y;
        public float z;
        public float q;
    }

    public struct Tangent_Data
    {
        public float x;
        public float y;
        public float z;
        public float q;
    }

    public struct Vertex_Data
    {
        public float x;
        public float y;
        public float z;
    }

    public struct UV_Data
    {
        public float u;
        public float v;
        public float a;
    }

    public struct Face_Data
    {
        public ushort a;
        public ushort b;
        public ushort c;
    }
}

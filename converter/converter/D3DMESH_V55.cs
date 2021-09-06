using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace converter
{
    /// <summary>
    /// Version 55: The Walking Dead: The Final Season, The Walking Dead: The Telltale Definitive Series
    /// </summary>
    public static class D3DMESH_V55
    {
        public static List<int> MultiMat = new List<int>();

        public static string BaseName;

        public static List<Vertex_Data> AllVert_array = new List<Vertex_Data>();
        public static List<Normal_Data> AllNormal_array = new List<Normal_Data>();
        public static List<UV_Data> AllUV_array = new List<UV_Data>();
        public static List<UV_Data> AllUV2_array = new List<UV_Data>();
        public static List<UV_Data> AllUV3_array = new List<UV_Data>();
        public static List<UV_Data> AllUV4_array = new List<UV_Data>();
        public static List<UV_Data> AllUV5_array = new List<UV_Data>();
        public static List<UV_Data> AllUV6_array = new List<UV_Data>();
        public static List<Color_Data> AllColor_array = new List<Color_Data>();
        public static List<float> AllAlpha_array = new List<float>();
        public static List<Weight_data> AllWeight_array = new List<Weight_data>();
        public static List<uint> AllFace_array = new List<uint>();
        public static List<uint> AllMatID_array = new List<uint>();
        public static List<uint> BoneSetup = new List<uint>();

        public static int BoneIDSets;
        public static int LODNum = 0;
        public static int UVLayers;

        //STARTS AT LINE 10448 IN THE TelltaleGames_D3DMesh.ms script
        public static void ConvertMesh_D3DMESH(byte[] fileBytes, ref uint bytePointerLocation, string D3DName, SKL sklFile)
        {
            List<List<ushort>> Face_array = new List<List<ushort>>();
            List<Vertex_Data> Vert_array = new List<Vertex_Data>();
            List<Normal_Data> Normal_array = new List<Normal_Data>();
            List<UV_Data> UV_array = new List<UV_Data>();
            List<UV_Data> UV2_array = new List<UV_Data>();
            List<UV_Data> UV3_array = new List<UV_Data>();
            List<UV_Data> UV4_array = new List<UV_Data>();
            List<Bone_Info_Struct> B1_array = new List<Bone_Info_Struct>();
            List<Weight_Info_Struct> W1_array = new List<Weight_Info_Struct>();
            List<Color_Data> Color_array = new List<Color_Data>();
            List<Color_Data> MatColor_array = new List<Color_Data>();
            List<float> Alpha_array = new List<float>();
            List<uint> FixedBoneID_array = new List<uint>();
            List<uint> BoneIDOffset_array = new List<uint>();
            List<Polygon_Info_V5_Struct> PolyStructV5_array = new List<Polygon_Info_V5_Struct>();

            List<string> DifName_array = new List<string>();
            List<string> BakeName_array = new List<string>();
            List<string> BumpName_array = new List<string>();
            List<string> EnvName_array = new List<string>();
            List<string> DtlDifName_array = new List<string>();
            List<string> DtlBumpName_array = new List<string>();
            List<string> SpecName_array = new List<string>();
            List<string> Tex8Name_array = new List<string>();
            List<string> GrdName_array = new List<string>();
            List<string> Tex10Name_array = new List<string>();
            List<string> ShdName_array = new List<string>();
            List<uint> NoRig = new List<uint>();

            uint MatPlus = 0;
            uint FooterPlus = 0;
            uint FooterCheck = 0;

            //rtb then seeks ahead 7 bytes
            bytePointerLocation += 7;

            Console.WriteLine("Model start = {0}", bytePointerLocation);

            float BoundingMinX = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
            float BoundingMinY = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
            float BoundingMinZ = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
            float BoundingMaxX = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
            float BoundingMaxY = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
            float BoundingMaxZ = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);

            uint HeaderLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 4; //rtb subtracts 4 for whatever reason?

            //rtb then seeks ahead for the length of the header
            bytePointerLocation += HeaderLength;

            uint Head3ASubSize = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint PolyTotal = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            Console.WriteLine("Count = {0}", PolyTotal);

            for (int x = 0; x < PolyTotal; x++)
            {
                Console.WriteLine("Model info start = {0}", bytePointerLocation);

                uint unknown1 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                uint BoneSetNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) + 1;
                uint SingleBindNode = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                uint VertexMin = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) + 1;
                uint VertexMax = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) + 1;
                uint FacepointStart = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                uint PolygonStart = (FacepointStart / 3) + 1;
                uint PolygonCount = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                uint FacepointCount = PolygonCount * 3;

                BoundingMinX = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                BoundingMinY = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                BoundingMinZ = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                BoundingMaxX = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                BoundingMaxY = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                BoundingMaxZ = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);

                HeaderLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                float UnkFloat1 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                float UnkFloat2 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                float UnkFloat3 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                uint UnkFloat4 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                uint HeaderLength2 = (uint)bytePointerLocation + ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                uint DifNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) + 1;
                uint BakeNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) + 1;
                uint BumpNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) + 1;
                uint EnvNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) + 1;
                uint DtlDifNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) + 1;
                uint DtlBumpNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) + 1;
                uint SpecNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) + 1;
                uint Tex8Num = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) + 1;
                uint GrdNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) + 1;
                uint Tex10Num = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) + 1;
                uint ShdNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) + 1;

                bytePointerLocation = HeaderLength2;
                bytePointerLocation += 0xA8;

                float ColorR = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                float ColorG = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                float ColorB = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                float ColorA = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);

                Color_Data matColorData = new Color_Data()
                {
                    r = ColorR,
                    g = ColorG,
                    b = ColorB,
                    a = ColorA
                };

                Polygon_Info_V5_Struct polygon_Info_V5_Struct = new Polygon_Info_V5_Struct()
                {
                    VertexMin = VertexMin,
                    VertexMax = VertexMax,
                    PolygonStart = PolygonStart,
                    PolygonCount = PolygonCount,
                    FacePointCount = FacepointCount,
                    DifNum = DifNum,
                    BakeNum = BakeNum,
                    BumpNum = BumpNum,
                    EnvNum = EnvNum,
                    DtlDifNum = DtlDifNum,
                    DtlBumpNum = DtlBumpNum,
                    SpecNum = SpecNum,
                    Tex8Num = Tex8Num,
                    GrdNum = GrdNum,
                    Tex10Num = Tex10Num,
                    ShdNum = ShdNum,
                    BoneSetNum = BoneSetNum,
                    SingleBindNode = SingleBindNode
                };

                MatColor_array.Add(matColorData);
                PolyStructV5_array.Add(polygon_Info_V5_Struct);
            }

            Console.WriteLine("Header B start = {0}", bytePointerLocation);
            uint headerBsize = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 4;
            bytePointerLocation += headerBsize;

            Console.WriteLine("Header C (Bone IDs) start = {0}", bytePointerLocation);
            uint IDHeaderLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 4;
            uint BoneIDSets = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            Console.WriteLine("Count = {0}", bytePointerLocation);

            for (int x = 0; x < BoneIDSets; x++)
            {
                BoneIDOffset_array.Add((uint)bytePointerLocation);
                uint BoneIDTotal = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                List<uint> ProperBoneID_array = new List<uint>();

                for (int y = 0; y < BoneIDTotal; y++)
                {
                    uint BoneHash2 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                    uint BoneHash1 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                    uint nothing = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                }
            }

            Console.WriteLine("Header D start = {0}", bytePointerLocation);
            uint headerDsize = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 4;
            bytePointerLocation += headerDsize;

            Console.WriteLine("Header E start = {0}", bytePointerLocation);
            uint headerEsize = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 4;
            bytePointerLocation += headerDsize;

            Console.WriteLine("Header F start = {0}", bytePointerLocation);
            bytePointerLocation += 0x08;

            Console.WriteLine("Header G (Texture Info) start = {0}", bytePointerLocation);
            uint TexGroupSize = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            Console.WriteLine("--------------------");
            //1: Diffuse Map
            //2: Bake Map
            //3: Bump Map
            //4: Environment Map
            //5: Detail Dffuse Map
            //6: Detail Bump Map
            //7: Specular Map
            //8: Unused?
            //9: Gradient Map
            //10: Unused?
            //11: Shadow Map
            for (int m = 0; m < 11; m++)
            {
                uint TexGroupCount = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                for (int n = 0; n < TexGroupCount; n++)
                {
                    uint TexSectionLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                    uint TexNameLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 6;
                    string TexName = ByteFunctions.ReadFixedString(fileBytes, TexNameLength, ref bytePointerLocation);

                    //Console.WriteLine("{0}", TexName);

                    if (m.Equals(1))
                        DifName_array.Add(TexName);
                    if (m.Equals(2))
                        BakeName_array.Add(TexName);
                    if (m.Equals(3))
                        BumpName_array.Add(TexName);
                    if (m.Equals(4))
                        EnvName_array.Add(TexName);
                    if (m.Equals(5))
                        DtlDifName_array.Add(TexName);
                    if (m.Equals(6))
                        DtlBumpName_array.Add(TexName);
                    if (m.Equals(7))
                        SpecName_array.Add(TexName);
                    if (m.Equals(8))
                        Tex8Name_array.Add(TexName);
                    if (m.Equals(9))
                        GrdName_array.Add(TexName);
                    if (m.Equals(10))
                        Tex10Name_array.Add(TexName);
                    if (m.Equals(11))
                        ShdName_array.Add(TexName);

                    bytePointerLocation += 0x06;

                    uint somekindamaterialthing = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                    bytePointerLocation += 0x18;

                    uint somekindamaterialthing2 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                    bytePointerLocation += somekindamaterialthing2;
                }
            }

            bytePointerLocation = TexGroupSize;

            for (int m = 0; m < PolyStructV5_array.Count; m++)
            {
                Console.WriteLine("Material #{0} uses the following textures:", m);

                if (PolyStructV5_array[m].DifNum > 0 && DifName_array.Count > 0)
                    Console.WriteLine("Diffuse Map: {0}", DifName_array[(int)PolyStructV5_array[m].DifNum]);

                if (PolyStructV5_array[m].BakeNum > 0 && BakeName_array.Count > 0)
                    Console.WriteLine("Bake Map: {0}", BakeName_array[(int)PolyStructV5_array[m].BakeNum]);

                if (PolyStructV5_array[m].BumpNum > 0 && BumpName_array.Count > 0)
                    Console.WriteLine("Bump Map: {0}", BumpName_array[(int)PolyStructV5_array[m].BumpNum]);

                if (PolyStructV5_array[m].EnvNum > 0 && EnvName_array.Count > 0)
                    Console.WriteLine("Environment Map: {0}", EnvName_array[(int)PolyStructV5_array[m].EnvNum]);

                if (PolyStructV5_array[m].DtlDifNum > 0 && DtlDifName_array.Count > 0)
                    Console.WriteLine("Detail Diffuse Map: {0}", DtlDifName_array[(int)PolyStructV5_array[m].DtlDifNum]);

                if (PolyStructV5_array[m].DtlBumpNum > 0 && DtlBumpName_array.Count > 0)
                    Console.WriteLine("Detail Bump Map: {0}", DtlBumpName_array[(int)PolyStructV5_array[m].DtlBumpNum]);

                if (PolyStructV5_array[m].SpecNum > 0 && SpecName_array.Count > 0)
                    Console.WriteLine("Specular Map: {0}", SpecName_array[(int)PolyStructV5_array[m].SpecNum]);

                if (PolyStructV5_array[m].Tex8Num > 0 && Tex8Name_array.Count > 0)
                    Console.WriteLine("Tex8 Map: {0}", Tex8Name_array[(int)PolyStructV5_array[m].Tex8Num]);

                if (PolyStructV5_array[m].GrdNum > 0 && GrdName_array.Count > 0)
                    Console.WriteLine("Gradient Map: {0}", GrdName_array[(int)PolyStructV5_array[m].GrdNum]);

                if (PolyStructV5_array[m].Tex10Num > 0 && Tex10Name_array.Count > 0)
                    Console.WriteLine("Tex10 Map: {0}", Tex10Name_array[(int)PolyStructV5_array[m].Tex10Num]);

                if (PolyStructV5_array[m].ShdNum > 0 && ShdName_array.Count > 0)
                    Console.WriteLine("Shadow Map: {0}", ShdName_array[(int)PolyStructV5_array[m].ShdNum]);

                Console.WriteLine("Material colors: R({0}) G({1}) B({2}) A({3})", MatColor_array[m].r, MatColor_array[m].g, MatColor_array[m].b, MatColor_array[m].a);
                Console.WriteLine("--------------------");
            }
        }
        //ENDS AT LINE 11750 IN THE TelltaleGames_D3DMesh.ms script
    }
}

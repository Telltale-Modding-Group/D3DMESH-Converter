using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Assimp;
using Assimp.Configs;
using Assimp.Unmanaged;

namespace converter
{
    /// <summary>
    /// Version 5: The Walking Dead Season 1 [PC]
    /// </summary>
    public static class D3DMESH_V5
    {
        public static string objFilePath = "";

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
        public static List<Weight_data> AllWeight_array = new List<Weight_data>();
        public static List<Face_Data> AllFace_array = new List<Face_Data>();
        public static List<uint> AllMatID_array = new List<uint>();
        public static List<uint> BoneSetup = new List<uint>();

        public static int BoneIDSets;
        public static int LODNum = 0;
        public static int UVLayers;

        /// <summary>
        /// Converts D3DMESH files for Version 5: The Walking Dead Season 1 [PC]
        /// </summary>
        /// <param name="fileBytes"></param>
        /// <param name="bytePointerLocation"></param>
        /// <param name="D3DName"></param>
        /// <param name="sklFile"></param>
        public static void ConvertMesh_D3DMESH(byte[] fileBytes, ref uint bytePointerLocation, string D3DName, SKL sklFile, string resultPath = "", bool writeFileAtEnd = false)
        {
            //STARTS AT LINE 2939 IN THE TelltaleGames_D3DMesh.ms script
            List<Face_Data> Face_array = new List<Face_Data>();
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
            bytePointerLocation += 0x07;

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
                uint HeaderLength2 = bytePointerLocation + ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                //NOTE: Originall RTB incremented theses material values by one, but since we start from zero we don't need to increment these values
                uint DifNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                uint BakeNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                uint BumpNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                uint EnvNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                uint DtlDifNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                uint DtlBumpNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                uint SpecNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                uint Tex8Num = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                uint GrdNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                uint Tex10Num = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                uint ShdNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

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

            Console.WriteLine("Count = {0}", BoneIDSets);

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

                    //NOTE: decreased values by one since we start from 0 rather than 1
                    if (m == 0)
                        DifName_array.Add(TexName);
                    else if (m.Equals(1))
                        BakeName_array.Add(TexName);
                    else if(m.Equals(2))
                        BumpName_array.Add(TexName);
                    else if(m.Equals(3))
                        EnvName_array.Add(TexName);
                    else if(m.Equals(4))
                        DtlDifName_array.Add(TexName);
                    else if(m.Equals(5))
                        DtlBumpName_array.Add(TexName);
                    else if(m.Equals(6))
                        SpecName_array.Add(TexName);
                    else if(m.Equals(7))
                        Tex8Name_array.Add(TexName);
                    else if(m.Equals(8))
                        GrdName_array.Add(TexName);
                    else if(m.Equals(9))
                        Tex10Name_array.Add(TexName);
                    else if(m.Equals(10))
                        ShdName_array.Add(TexName);

                    bytePointerLocation += 0x06;

                    uint somekindamaterialthing = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                    bytePointerLocation += 0x18;

                    uint somekindamaterialthing2 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                    bytePointerLocation += somekindamaterialthing2;
                }
            }

            //original in RTB's script but commented out because it screws up everything (despite him SETTING the pointer position there)
            //bytePointerLocation = TexGroupSize;

            for (int m = 0; m < PolyStructV5_array.Count; m++)
            {
                Console.WriteLine("Material #{0} uses the following textures:", m);

                //added additional checks (so we don't error out)
                //1st check is original (RTB does it too), checks if the value is greater or equal to zero
                //2nd check is for checking if there are elements within the name array we are trying to check
                //3rd check is for making sure that the "index" value of the texture that we are trying to show is not greater than the length of the array

                if (PolyStructV5_array[m].DifNum >= 0 && DifName_array.Count > 0 && PolyStructV5_array[m].DifNum < DifName_array.Count)
                    Console.WriteLine("Diffuse Map: {0}", DifName_array[(int)PolyStructV5_array[m].DifNum]);

                if (PolyStructV5_array[m].BakeNum >= 0 && BakeName_array.Count > 0 && PolyStructV5_array[m].BakeNum < BakeName_array.Count)
                    Console.WriteLine("Bake Map: {0}", BakeName_array[(int)PolyStructV5_array[m].BakeNum]);

                if (PolyStructV5_array[m].BumpNum >= 0 && BumpName_array.Count > 0 && PolyStructV5_array[m].BumpNum < BumpName_array.Count)
                    Console.WriteLine("Bump Map: {0}", BumpName_array[(int)PolyStructV5_array[m].BumpNum]);

                if (PolyStructV5_array[m].EnvNum >= 0 && EnvName_array.Count > 0 && PolyStructV5_array[m].EnvNum < EnvName_array.Count)
                    Console.WriteLine("Environment Map: {0}", EnvName_array[(int)PolyStructV5_array[m].EnvNum]);

                if (PolyStructV5_array[m].DtlDifNum >= 0 && DtlDifName_array.Count > 0 && PolyStructV5_array[m].DtlDifNum < DtlDifName_array.Count)
                    Console.WriteLine("Detail Diffuse Map: {0}", DtlDifName_array[(int)PolyStructV5_array[m].DtlDifNum]);

                if (PolyStructV5_array[m].DtlBumpNum >= 0 && DtlBumpName_array.Count > 0 && PolyStructV5_array[m].DtlBumpNum < DtlBumpName_array.Count)
                    Console.WriteLine("Detail Bump Map: {0}", DtlBumpName_array[(int)PolyStructV5_array[m].DtlBumpNum]);

                if (PolyStructV5_array[m].SpecNum >= 0 && SpecName_array.Count > 0 && PolyStructV5_array[m].SpecNum < SpecName_array.Count)
                    Console.WriteLine("Specular Map: {0}", SpecName_array[(int)PolyStructV5_array[m].SpecNum]);

                if (PolyStructV5_array[m].Tex8Num >= 0 && Tex8Name_array.Count > 0 && PolyStructV5_array[m].Tex8Num < Tex8Name_array.Count)
                    Console.WriteLine("Tex8 Map: {0}", Tex8Name_array[(int)PolyStructV5_array[m].Tex8Num]);

                if (PolyStructV5_array[m].GrdNum >= 0 && GrdName_array.Count > 0 && PolyStructV5_array[m].GrdNum < GrdName_array.Count)
                    Console.WriteLine("Gradient Map: {0}", GrdName_array[(int)PolyStructV5_array[m].GrdNum]);

                if (PolyStructV5_array[m].Tex10Num >= 0 && Tex10Name_array.Count > 0 && PolyStructV5_array[m].Tex10Num < Tex10Name_array.Count)
                    Console.WriteLine("Tex10 Map: {0}", Tex10Name_array[(int)PolyStructV5_array[m].Tex10Num]);

                if (PolyStructV5_array[m].ShdNum >= 0 && ShdName_array.Count > 0 && PolyStructV5_array[m].ShdNum < ShdName_array.Count)
                    Console.WriteLine("Shadow Map: {0}", ShdName_array[(int)PolyStructV5_array[m].ShdNum]);

                Console.WriteLine("Material colors: RGBA[{0}, {1}, {2}, {3}]", MatColor_array[m].r, MatColor_array[m].g, MatColor_array[m].b, MatColor_array[m].a);
                Console.WriteLine("--------------------");
            }

            
            Console.WriteLine("Header H start = {0}", bytePointerLocation);
            bytePointerLocation += 0x0C;

            Console.WriteLine("Header I start = {0}", bytePointerLocation);
            float UV1XMult = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
            float UV1YMult = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
            float UV4XMult = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
            float UV4YMult = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
            float UV2XMult = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
            float UV2YMult = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
            float UV3XMult = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
            float UV3YMult = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
            Console.WriteLine("UV Multipliers = 1({0}, {1}), 2({2}, {3}), 3({4}, {5}), 4({6}, {7})", UV1XMult, UV1YMult, UV2XMult, UV2YMult, UV3XMult, UV3YMult, UV4XMult, UV4YMult);

            Console.WriteLine("Header J start = {0}", bytePointerLocation);
            uint headerJsize = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 4;
            bytePointerLocation += headerJsize;

            Console.WriteLine("Header K start = {0}", bytePointerLocation);
            uint headerKsize = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 4;
            bytePointerLocation += headerKsize;

            uint BytePad = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);
            uint BytePad2 = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);
            uint unknown = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            Console.WriteLine("Face info start = {0}", bytePointerLocation);
            uint FaceCount = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            bytePointerLocation += 0x08;

            for(int x = 0; x < FaceCount/(uint)3; x++)
            {
                ushort fa = ByteFunctions.ReadUnsignedShort(fileBytes, ref bytePointerLocation);
                ushort fb = ByteFunctions.ReadUnsignedShort(fileBytes, ref bytePointerLocation);
                ushort fc = ByteFunctions.ReadUnsignedShort(fileBytes, ref bytePointerLocation);

                Face_Data face_Data = new Face_Data()
                {
                    a = fa,
                    b = fb,
                    c = fc
                };

                Face_array.Add(face_Data);
            }

            Console.WriteLine("Vertex Buffer start = {0}", bytePointerLocation);
            uint VertCount = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint VertLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            bytePointerLocation += 0x0C;

            uint VertHeaderLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            /*  RTB ORIGINAL COMMENT
                1 = floats
				2 = bytes, signed
				3 = bytes, unsigned
				4 = shorts, signed
				5 = shorts, unsigned
				8 = bytes, signed
				11 = half floats
            */

            uint VertexOffset = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint VertexAmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint VertexFmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            if(VertexFmt > 0)
            {
                Console.WriteLine("Vertex Offset = {0}, Count = {1}, Format = {2}", VertexOffset, VertexAmt, VertexFmt);
            }

            uint UVOffset = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint UVAmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint UVFmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            if (UVFmt > 0)
            {
                Console.WriteLine("UV Offset = {0}, Count = {1}, Format = {2}", UVOffset, UVAmt, UVFmt);
            }

            uint NormalsOffset = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint NormalsAmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint NormalsFmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            if (NormalsFmt > 0)
            {
                Console.WriteLine("Normals Offset = {0}, Count = {1}, Format = {2}", NormalsOffset, NormalsAmt, NormalsFmt);
            }

            uint WeightsOffset = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint WeightsAmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint WeightsFmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            if (WeightsFmt > 0)
            {
                Console.WriteLine("Weights Offset = {0}, Count = {1}, Format = {2}", WeightsOffset, WeightsAmt, WeightsFmt);
            }

            uint BonesOffset = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint BonesAmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint BonesFmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            if (BonesFmt > 0)
            {
                Console.WriteLine("Bones Offset = {0}, Count = {1}, Format = {2}", BonesOffset, BonesAmt, BonesFmt);
            }

            uint ColorsOffset = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint ColorsAmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint ColorsFmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            if (ColorsFmt > 0)
            {
                Console.WriteLine("Colors Offset = {0}, Count = {1}, Format = {2}", ColorsOffset, ColorsAmt, ColorsFmt);
            }

            uint Unknown1Offset = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint Unknown1Amt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint Unknown1Fmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            if (Unknown1Fmt > 0)
            {
                Console.WriteLine("Unknown1 Offset = {0}, Count = {1}, Format = {2}", Unknown1Offset, Unknown1Amt, Unknown1Fmt);
            }

            uint BinormalsOffset = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint BinormalsAmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint BinormalsFmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            if (BinormalsFmt > 0)
            {
                Console.WriteLine("Binormals Offset = {0}, Count = {1}, Format = {2}", BinormalsOffset, BinormalsAmt, BinormalsFmt);
            }

            uint TangentsOffset = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint TangentsAmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint TangentsFmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            if (TangentsFmt > 0)
            {
                Console.WriteLine("Tangents? Offset = {0}, Count = {1}, Format = {2}", TangentsOffset, TangentsAmt, TangentsFmt);
            }

            uint UV2Offset = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint UV2Amt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint UV2Fmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            if (UV2Fmt > 0)
            {
                Console.WriteLine("UV2 Offset = {0}, Count = {1}, Format = {2}", UV2Offset, UV2Amt, UV2Fmt);
            }

            uint UV3Offset = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint UV3Amt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint UV3Fmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            if (UV3Fmt > 0)
            {
                Console.WriteLine("UV3 Offset = {0}, Count = {1}, Format = {2}", UV3Offset, UV3Amt, UV3Fmt);
            }

            uint UV4Offset = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint UV4Amt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint UV4Fmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            if (UV4Fmt > 0)
            {
                Console.WriteLine("UV4 Offset = {0}, Count = {1}, Format = {2}", UV4Offset, UV4Amt, UV4Fmt);
            }

            uint Unknown2Offset = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint Unknown2Amt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint Unknown2Fmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            if (Unknown2Fmt > 0)
            {
                ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red);
                Console.WriteLine("Something went wrong! Crashing gracefully!");
                Console.ResetColor();
                return;
            }

            uint Unknown3Offset = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint Unknown3Amt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint Unknown3Fmt = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            if (Unknown3Fmt > 0)
            {
                ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red);
                Console.WriteLine("Something went wrong! Crashing gracefully!");
                Console.ResetColor();
                return;
            }

            if(BonesFmt.Equals(0) && BoneIDSets > 0)
            {
                NoRig = new List<uint>();
                Console.WriteLine("{0}, uses single-bind rigging.", BaseName);
            }

            Console.WriteLine("Vertex start = {0}", bytePointerLocation);

            //offsets go south here for whatever reason
            for(int x = 0; x < VertCount; x++)
            {
                //read vertex
                Read_Vertex(VertexFmt, fileBytes, ref bytePointerLocation, ref Vert_array);

                //READ UV SET 1
                Read_UVSet(UVFmt, UV1XMult, UV1YMult, fileBytes, ref bytePointerLocation, ref UV_array);

                //READ UV SET 2
                Read_UVSet(UV2Fmt, UV2XMult, UV2YMult, fileBytes, ref bytePointerLocation, ref UV2_array);

                //READ UV SET 3
                Read_UVSet(UV3Fmt, UV3XMult, UV3YMult, fileBytes, ref bytePointerLocation, ref UV3_array);

                //READ UV SET 4
                Read_UVSet(UV4Fmt, UV4XMult, UV4YMult, fileBytes, ref bytePointerLocation, ref UV4_array);

                //read bones
                Read_Bones(BonesFmt, fileBytes, ref bytePointerLocation, ref B1_array);

                //read weights
                Read_Weights(WeightsFmt, fileBytes, ref bytePointerLocation, ref W1_array);

                //read vertex colors
                if (D3DMESH.options_VERTEX_COLORS)
                    Read_Colors(ColorsFmt, fileBytes, ref bytePointerLocation, ref Color_array);

                //read an unknown data structure
                if(Unknown1Fmt > 0)
                {
                    if(Unknown1Fmt.Equals(1))
                    {
                        float unknown1 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    }
                    else
                    {
                        ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red);
                        Console.WriteLine("Unknown unknown format!");
                        Console.ResetColor();
                        return;
                    }
                }

                //read normals
                Read_Normals(NormalsFmt, fileBytes, ref bytePointerLocation, ref Normal_array);

                //read binormals
                Read_Binormals(BinormalsFmt, fileBytes, ref bytePointerLocation);

                //read tangents
                Read_Tangents(TangentsFmt, fileBytes, ref bytePointerLocation);
            }

            Console.WriteLine("End of file = {0}", bytePointerLocation);

            for(int i = 0; i < PolyStructV5_array.Count; i++)
            {
                List<string> ProperBoneID_array = new List<string>();
                List<string> FixedBoneID_array1 = new List<string>();
                List<Bone_Info_Struct> ActualB1_array = new List<Bone_Info_Struct>();
                List<Weight_data> Weight_array = new List<Weight_data>();
                List<Face_Data> Face_array2 = new List<Face_Data>();

                //for(uint y = PolyStructV5_array[i].PolygonStart; y < (PolyStructV5_array[i].PolygonCount + PolyStructV5_array[i].PolygonStart); y++)
                //{
                //    Face_array2.Add(Face_array[(int)y - 1]);
                //}

                uint VertexMin = PolyStructV5_array[i].VertexMin;
                uint VertexMax = PolyStructV5_array[i].VertexMax;
                int FacePlus = AllVert_array.Count;

                for(uint x = VertexMin; x < VertexMax; x++)
                {
                    AllVert_array.Add(Vert_array[(int)x]);

                    if(Normal_array.Count > 0)
                        AllNormal_array.Add(Normal_array[(int)x]);

                    AllUV_array.Add(UV_array[(int)x]);

                    if (UV2_array.Count > 0)
                        AllUV2_array.Add(UV2_array[(int)x]);

                    if (UV3_array.Count > 0)
                        AllUV3_array.Add(UV3_array[(int)x]);

                    if (UV4_array.Count > 0)
                        AllUV4_array.Add(UV4_array[(int)x]);

                    if(Color_array.Count > 0)
                        AllColor_array.Add(Color_array[(int)x]);

                    if(Weight_array.Count > 0)
                        AllWeight_array.Add(Weight_array[(int)x]);
                }

                for(int x = 0; x < PolyStructV5_array[i].PolygonCount; x++)
                {
                    //Face_Data faces3 = ((Face_array2[x] - PolyStructV5_array[i].VertexMin) + 1 + FacePlus);
                    //Face_Data faces3 = new Face_Data()
                    //{
                    //    a = ((ushort)((Face_array2[x].a - PolyStructV5_array[i].VertexMin) + 1 + FacePlus)),
                    //    b = ((ushort)((Face_array2[x].b - PolyStructV5_array[i].VertexMin) + 1 + FacePlus)),
                    //    c = ((ushort)((Face_array2[x].c - PolyStructV5_array[i].VertexMin) + 1 + FacePlus))
                    //};

                    //AllFace_array.Add(faces3);
                }
            }

            //ENDS AT LINE 3618 IN THE TelltaleGames_D3DMesh.ms script

            if (writeFileAtEnd)
            {
                OBJ_Export.WriteOBJ_File(resultPath, AllVert_array, AllUV_array, AllNormal_array, AllFace_array);
            }
        }

        public static void Read_Vertex(uint VertexFmt, byte[] fileBytes, ref uint bytePointerLocation, ref List<Vertex_Data> Vertex_array)
        {
            if (VertexFmt == 1)
            {
                Vertex_Data vertex_Data = new Vertex_Data()
                {
                    x = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation) * D3DMESH.options_MODEL_SCALE,
                    y = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation) * D3DMESH.options_MODEL_SCALE,
                    z = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation) * D3DMESH.options_MODEL_SCALE
                };

                Vertex_array.Add(vertex_Data);
            }
            else
            {
                ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red);
                Console.WriteLine("Unknown positions format!");
                Console.ResetColor();
                return;
            }
        }

        //TODO: should probably store the data we are parsing here into a tangent array
        public static void Read_Tangents(uint TangentsFmt, byte[] fileBytes, ref uint bytePointerLocation)
        {
            Tangent_Data tangent_Data = new Tangent_Data();

            if (TangentsFmt == 2)
            {
                tangent_Data.x = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 127;
                tangent_Data.y = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 127;
                tangent_Data.z = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 127;
                tangent_Data.q = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 127;
            }
            else if (TangentsFmt == 4)
            {
                tangent_Data.x = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation) / 32767;
                tangent_Data.y = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation) / 32767;
                tangent_Data.z = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation) / 32767;
                tangent_Data.q = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation) / 32767;
            }
        }

        //TODO: should probably store the data we are parsing here into a binormal array
        public static void Read_Binormals(uint BinormalsFmt, byte[] fileBytes, ref uint bytePointerLocation)
        {
            Binormal_Data binormal_Data = new Binormal_Data();

            if (BinormalsFmt == 2)
            {
                binormal_Data.x = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 127;
                binormal_Data.y = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 127;
                binormal_Data.z = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 127;
                binormal_Data.q = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 127;
            }
            else if (BinormalsFmt == 4)
            {
                binormal_Data.x = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation) / 32767;
                binormal_Data.y = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation) / 32767;
                binormal_Data.z = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation) / 32767;
                binormal_Data.q = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation) / 32767;
            }
        }

        public static void Read_Normals(uint NormalsFmt, byte[] fileBytes, ref uint bytePointerLocation, ref List<Normal_Data> Normal_array)
        {
            Normal_Data normal_Data = new Normal_Data();

            if (NormalsFmt == 2)
            {
                normal_Data.x = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 127;
                normal_Data.y = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 127;
                normal_Data.z = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 127;
                normal_Data.q = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 127;
                Normal_array.Add(normal_Data);
            }
            else if (NormalsFmt == 4)
            {
                normal_Data.x = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation) / 32767;
                normal_Data.y = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation) / 32767;
                normal_Data.z = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation) / 32767;
                normal_Data.q = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation) / 32767;
                Normal_array.Add(normal_Data);
            }
        }

        public static void Read_Colors(uint ColorsFmt, byte[] fileBytes, ref uint bytePointerLocation, ref List<Color_Data> Color_array)
        {
            Color_Data color_Data = new Color_Data();

            if (ColorsFmt == 1)
            {
                color_Data.r = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation) * 255;
                color_Data.g = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation) * 255;
                color_Data.b = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation) * 255;
                color_Data.a = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                Color_array.Add(color_Data);
            }
            else if (ColorsFmt == 3)
            {
                color_Data.r = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);
                color_Data.g = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);
                color_Data.b = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);
                color_Data.a = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 255;
                Color_array.Add(color_Data);
            }
        }

        public static void Read_Weights(uint WeightsFmt, byte[] fileBytes, ref uint bytePointerLocation, ref List<Weight_Info_Struct> Weight_array)
        {
            Weight_Info_Struct weight_Info_Struct = new Weight_Info_Struct();

            if (WeightsFmt == 0)
            {
                Weight_array.Add(weight_Info_Struct);
            }
            else if (WeightsFmt == 1)
            {
                weight_Info_Struct.Weight1 = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);
                weight_Info_Struct.Weight2 = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);
                weight_Info_Struct.Weight3 = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);
                weight_Info_Struct.Weight4 = 0;
                Weight_array.Add(weight_Info_Struct);
            }
            else if (WeightsFmt == 4)
            {
                weight_Info_Struct.Weight1 = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation) / 32767;
                weight_Info_Struct.Weight2 = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation) / 32767;
                weight_Info_Struct.Weight3 = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation) / 32767;
                weight_Info_Struct.Weight4 = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation) / 32767;
                Weight_array.Add(weight_Info_Struct);
            }
            else if (WeightsFmt == 5)
            {
                weight_Info_Struct.Weight1 = ByteFunctions.ReadUnsignedShort(fileBytes, ref bytePointerLocation) / 65535;
                weight_Info_Struct.Weight2 = ByteFunctions.ReadUnsignedShort(fileBytes, ref bytePointerLocation) / 65535;
                weight_Info_Struct.Weight3 = ByteFunctions.ReadUnsignedShort(fileBytes, ref bytePointerLocation) / 65535;
                weight_Info_Struct.Weight4 = ByteFunctions.ReadUnsignedShort(fileBytes, ref bytePointerLocation) / 65535;
                Weight_array.Add(weight_Info_Struct);
            }
        }

        public static void Read_Bones(uint BonesFmt, byte[] fileBytes, ref uint bytePointerLocation, ref List<Bone_Info_Struct> Bone_array)
        {
            Bone_Info_Struct bone_Info_Struct = new Bone_Info_Struct();

            if (BonesFmt == 0)
            {
                Bone_array.Add(bone_Info_Struct);
            }
            else if (BonesFmt == 3)
            {
                bone_Info_Struct.Bone1 = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 4;
                bone_Info_Struct.Bone2 = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 4;
                bone_Info_Struct.Bone3 = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 4;
                bone_Info_Struct.Bone4 = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 4;
                Bone_array.Add(bone_Info_Struct);
            }
            else if (BonesFmt == 8)
            {
                bone_Info_Struct.Bone1 = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 3;
                bone_Info_Struct.Bone2 = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 3;
                bone_Info_Struct.Bone3 = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 3;
                bone_Info_Struct.Bone4 = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 3;
                Bone_array.Add(bone_Info_Struct);
            }
        }

        public static void Read_UVSet(uint UVFmt, float UVXMult, float UVYMult, byte[] fileBytes, ref uint bytePointerLocation, ref List<UV_Data> UV_array)
        {
            UV_Data uv_Data = new UV_Data();

            if (UVFmt == 0)
            {
                UV_array.Add(uv_Data);
            }
            else if (UVFmt == 1)
            {
                float tu = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                float tv = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);

                tv = (tv * -1) + 1;

                uv_Data.u = tu;
                uv_Data.v = tv;

                UV_array.Add(uv_Data);
            }
            else if (UVFmt == 4)
            {
                float tu = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation);
                float tv = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation);

                tu = (tu / 32767) * UVXMult;
                tv = (((tv / 32767) * UVYMult) * -1) + 1;

                uv_Data.u = tu;
                uv_Data.v = tv;

                UV_array.Add(uv_Data);
            }
            else if (UVFmt == 5)
            {
                float tu = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation);
                float tv = ByteFunctions.ReadShort(fileBytes, ref bytePointerLocation);

                tu = (tu / 65535) * UVXMult;
                tv = (((tv / 65535) * UVYMult) * -1) + 1;

                uv_Data.u = tu;
                uv_Data.v = tv;

                UV_array.Add(uv_Data);
            }
            else if (UVFmt == 11)
            {
                float tu = ByteFunctions.ReadHalfFloat(fileBytes, ref bytePointerLocation);
                float tv = ByteFunctions.ReadHalfFloat(fileBytes, ref bytePointerLocation);

                tu = tu * 2;
                tv = ((tv * 2) * -1) + 1;

                uv_Data.u = tu;
                uv_Data.v = tv;

                UV_array.Add(uv_Data);
            }
        }
    }
}

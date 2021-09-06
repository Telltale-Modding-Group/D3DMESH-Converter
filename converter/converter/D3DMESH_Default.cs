using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace converter
{
    /// <summary>
    /// "Version 0.A" MBIN: Telltale Texas Hold'em, Bone, Sam & Max Season 1, Season 2 Episodes 1-2, CSI 3/4
    /// <para>"Version 0.B" MBIN: Sam & Max Season 2 Episodes 3 - 4</para>
    /// <para>"Version 0.C" MBIN: Sam & Max Season 2 Episode 5</para>
    /// </summary>
    public static class D3DMESH_Default
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

        //STARTS AT LINE 1128 IN THE TelltaleGames_D3DMesh.ms script
        public static void ConvertMesh_D3DMESH(byte[] fileBytes, ref uint bytePointerLocation, string D3DName, SKL sklFile)
        {
            List<Vertex_Data> Vert_array = new List<Vertex_Data>();
            List<Normal_Data> Normal_array = new List<Normal_Data>();
            List<UV_Data> UV_array = new List<UV_Data>();
            List<UV_Data> UV2_array = new List<UV_Data>();
            List<UV_Data> UV3_array = new List<UV_Data>();
            List<UV_Data> UV4_array = new List<UV_Data>();
            List<Color_Data> Color_array = new List<Color_Data>();
            List<float> Alpha_array = new List<float>();
            List<Bone_Info_Struct> B1_array = new List<Bone_Info_Struct>();
            List<Weight_Info_Struct> W1_array = new List<Weight_Info_Struct>();
            List<Face_Data> Face_array = new List<Face_Data>();
            List<uint> FacePoint_array = new List<uint>();
            List<uint> TriStrip_array = new List<uint>();
            List<uint> FixedBoneID_array = new List<uint>();
            List<uint> BoneIDOffset_array = new List<uint>();
            List<Polygon_Info_Struct> PolyStruct_array = new List<Polygon_Info_Struct>();
            uint NoRig = 0;
            uint MatPlus = 0;
            uint FooterPlus = 0;
            uint FooterCheck = 0;

            //RTB then goes back 1 byte from the current position
            bytePointerLocation -= 1;

            ushort HeaderCheck1 = ByteFunctions.ReadUnsignedShort(fileBytes, ref bytePointerLocation);

            if (HeaderCheck1 != 0x3131 && HeaderCheck1 != 0x3031 && HeaderCheck1 != 0x3130 && HeaderCheck1 != 0x3030)
            {
                //RTB then goes back 1 byte from the current position
                bytePointerLocation -= 1;
            }

            float BoundingMinX = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
            float BoundingMinY = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
            float BoundingMinZ = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
            float BoundingMaxX = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
            float BoundingMaxY = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
            float BoundingMaxZ = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);

            uint Head3ASubSize = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint PolyTotal = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            if (PolyTotal > 1000)
            {
                //RTB then goes back 33 bytes from the current position
                bytePointerLocation -= 33;

                BoundingMinX = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                BoundingMinY = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                BoundingMinZ = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                BoundingMaxX = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                BoundingMaxY = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                BoundingMaxZ = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);

                Head3ASubSize = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                PolyTotal = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            }

            if (PolyTotal > 1000)
            {
                ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red);
                Console.WriteLine("Something went wrong! Crashing gracefully!");
                Console.ResetColor();
                return;
            }

            for (int i = 0; i < PolyTotal; i++)
            {
                uint NameHeaderLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 8; //rtb subtracts by 8 for whatever reason?

                if (NameHeaderLength > 1000)
                {
                    ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red);
                    Console.WriteLine("Something went wrong! Crashing gracefully!");
                    return;
                }

                uint NameLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 4; //rtb subtracts by 4 for whatever reason?

                //RTB then offsets the current pointer position by the header length
                bytePointerLocation += NameHeaderLength;

                uint NameHeaderLength2 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 8; //rtb subtracts by 8 for whatever reason?

                if (NameHeaderLength2 > 1000)
                {
                    ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red);
                    Console.WriteLine("Something went wrong! Crashing gracefully!");
                    Console.ResetColor();
                    return;
                }

                uint NameLength2 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 4;

                //RTB then offsets the current pointer position by the header length
                bytePointerLocation += NameHeaderLength2;

                uint BoneSetNum = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) + 1;
                uint SingleBindNode = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                uint VertexMin = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) + 1;
                uint VertexMax = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) + 1;

                //rtb does a super specific mesh name check?
                if (D3DName.Equals("obj_tvsitcom_fakehallway.d3dmesh"))
                {
                    VertexMin = 1;
                    VertexMax = 28;
                }

                uint FacepointStart = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                uint PolygonStart = (FacepointStart / 3) + 1;
                uint PolygonCount = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                uint FacepointCount = PolygonCount * 3;
                uint NameHeaderLength3 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                uint NameLength3 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                //RTB then offsets the current pointer position by the header length
                bytePointerLocation += NameLength3;

                BoundingMinX = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                BoundingMinY = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                BoundingMinZ = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                BoundingMaxX = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                BoundingMaxY = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                BoundingMaxZ = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);

                uint MaterialHeaderLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                if (MaterialHeaderLength > 1000)
                {
                    ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red);
                    Console.WriteLine("Something went wrong! Crashing gracefully!");
                    Console.ResetColor();
                    return;
                }

                uint MaterialNameLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 6; //rtb subtracts 6 for whatever reason?
                string MaterialName = "";

                if (MaterialHeaderLength > 8)
                {
                    MaterialName = ByteFunctions.ReadFixedString(fileBytes, MaterialNameLength, ref bytePointerLocation);
                    Console.WriteLine("Diffuse Map: {0}", MaterialName);

                    //RTB then skips ahead 6 bytes from the current position
                    bytePointerLocation += 6;
                }

                uint MaterialHeaderLength2 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                if (MaterialHeaderLength2 > 1000)
                {
                    ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red);
                    Console.WriteLine("Something went wrong! Crashing gracefully!");
                    Console.ResetColor();
                    return;
                }

                uint MaterialNameLength2 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 6; //rtb subtracts 6 for whatever reason?

                if (MaterialNameLength2 > 8)
                {
                    string MaterialName2 = ByteFunctions.ReadFixedString(fileBytes, MaterialNameLength2, ref bytePointerLocation);
                    Console.WriteLine("Specular Map: {0}", MaterialName2);

                    //RTB then skips ahead 6 bytes from the current position
                    bytePointerLocation += 6;
                }

                uint MaterialHeaderLength3 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                if (MaterialHeaderLength3 > 1000)
                {
                    ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red);
                    Console.WriteLine("Something went wrong! Crashing gracefully!");
                    Console.ResetColor();
                    return;
                }

                uint MaterialNameLength3 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 6; //rtb subtracts 6 for whatever reason?

                if (MaterialHeaderLength3 > 8)
                {
                    string MaterialName3 = ByteFunctions.ReadFixedString(fileBytes, MaterialNameLength3, ref bytePointerLocation);
                    Console.WriteLine("Bake Map: {0}", MaterialName3);

                    //RTB then skips ahead 6 bytes from the current position
                    bytePointerLocation += 6;
                }

                uint MaterialHeaderLength4 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                if (MaterialHeaderLength4 > 1000)
                {
                    ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red);
                    Console.WriteLine("Something went wrong! Crashing gracefully!");
                    Console.ResetColor();
                    return;
                }

                uint MaterialNameLength4 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 6; //rtb subtracts 6 for whatever reason?

                if (MaterialHeaderLength4 > 8)
                {
                    string MaterialName4 = ByteFunctions.ReadFixedString(fileBytes, MaterialNameLength4, ref bytePointerLocation);
                    Console.WriteLine("Bump Map: {0}", MaterialName4);

                    //RTB then skips ahead 6 bytes from the current position
                    bytePointerLocation += 6;
                }

                if (D3DMESH.options_EARLY_GAME_FIX == 1)
                {
                    //note, for the variable I, might need to change it to zero instead of 1
                    if (i == 1)
                    {
                        ushort MatCheck = ByteFunctions.ReadUnsignedShort(fileBytes, ref bytePointerLocation);

                        //RTB then goes back 2 bytes from the current position
                        bytePointerLocation -= 2;

                        if (MatCheck < 256)
                        {
                            MatPlus = 1;
                        }
                    }

                    if (MatPlus == 1)
                    {
                        uint MaterialHeaderLength4B = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                        uint MaterialNameLength4B = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 6; //rtb subtracts 6 for whatever reason?

                        if (MaterialNameLength4B > 8)
                        {
                            string MaterialName4B = ByteFunctions.ReadFixedString(fileBytes, MaterialNameLength4B, ref bytePointerLocation);
                            Console.WriteLine("Tex4B Map: {0}", MaterialName4B);

                            //RTB then skips ahead 6 bytes from the current position
                            bytePointerLocation += 6;
                        }
                    }

                    //uint FooterCheck = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);
                    FooterCheck = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);

                    //note, for the variable I, might need to change it to zero instead of 1
                    if (i == 1)
                    {
                        if (FooterCheck != 48)
                        {
                            FooterPlus = 1;
                        }
                    }

                    uint MaterialHeaderLength5 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                    if (MaterialHeaderLength5 > 1000)
                    {
                        ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Yellow);
                        Console.WriteLine("Readjusting MatHeader5...");
                        Console.ResetColor();

                        //RTB then goes back 5 bytes from the current position
                        bytePointerLocation -= 5;

                        MaterialHeaderLength5 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                        if (MaterialHeaderLength5 > 1000)
                        {
                            ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red);
                            Console.WriteLine("Something went wrong! Crashing gracefully!");
                            Console.ResetColor();
                            return;
                        }
                    }

                    uint MaterialNameLength5 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 6; //rtb subtracts 6 for whatever reason?

                    if (MaterialHeaderLength5 > 8)
                    {
                        string MaterialName5 = ByteFunctions.ReadFixedString(fileBytes, MaterialNameLength5, ref bytePointerLocation);
                        Console.WriteLine("Tex5 Map: {0}", MaterialName5);

                        //RTB then skips ahead 6 bytes from the current position
                        bytePointerLocation += 6;
                    }

                    uint UnknownEnvValue = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                    //RTB then skips ahead 5 bytes from the current position
                    bytePointerLocation += 5;

                    uint HeaderCheck3 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                    //RTB then skips ahead 9 bytes from the current position
                    bytePointerLocation += 9;

                    if (HeaderCheck3 != 8)
                    {
                        //RTB then skips ahead 1 byte from the current position
                        bytePointerLocation += 1;
                    }

                    //RTB then skips ahead 1 byte again from the current position
                    bytePointerLocation += 1;

                    float Float2 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);

                    uint MaterialHeaderLength6 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                    if (MaterialHeaderLength6 > 1000)
                    {
                        ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Yellow);
                        Console.WriteLine("Readjusting MatHeader6...");
                        Console.ResetColor();

                        //RTB then goes back 5 bytes from the current position
                        bytePointerLocation -= 5;

                        MaterialHeaderLength6 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                        if (MaterialHeaderLength6 > 1000)
                        {
                            ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red);
                            Console.WriteLine("Something went wrong! Crashing gracefully!");
                            Console.ResetColor();
                            return;
                        }
                    }

                    uint MaterialNameLength6 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 6; //rtb subtracts 6 for whatever reason?

                    if (MaterialNameLength6 > 8)
                    {
                        string MaterialName6 = ByteFunctions.ReadFixedString(fileBytes, MaterialNameLength6, ref bytePointerLocation);
                        Console.WriteLine("Environment Map: {0}", MaterialName6);

                        //RTB then skips ahead 6 bytes from the current position
                        bytePointerLocation += 6;
                    }
                }
                else if (D3DMESH.options_EARLY_GAME_FIX != 1)
                {
                    uint MaterialHeaderLength5 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                    if (MaterialHeaderLength5 > 1000)
                    {
                        ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red);
                        Console.WriteLine("Something went wrong! Crashing gracefully!");
                        Console.ResetColor();
                        return;
                    }

                    uint MaterialNameLength5 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 6; //rtb subtracts 6 for whatever reason?

                    if (MaterialNameLength5 > 8)
                    {
                        string MaterialName5 = ByteFunctions.ReadFixedString(fileBytes, MaterialNameLength5, ref bytePointerLocation);
                        Console.WriteLine("Tex5 Map: {0}", MaterialName5);

                        //RTB then skips ahead 6 bytes from the current position
                        bytePointerLocation += 6;
                    }

                    //RTB then skips ahead 1 byte from the current position
                    bytePointerLocation += 1;

                    uint MaterialHeaderLength6 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                    if (MaterialHeaderLength6 > 1000)
                    {
                        ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red);
                        Console.WriteLine("Something went wrong! Crashing gracefully!");
                        Console.ResetColor();
                        return;
                    }

                    uint MaterialNameLength6 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 6; //rtb subtracts 6 for whatever reason?

                    if (MaterialHeaderLength6 > 8)
                    {
                        string MaterialName6 = ByteFunctions.ReadFixedString(fileBytes, MaterialNameLength6, ref bytePointerLocation);
                        Console.WriteLine("Tex6 Map: {0}", MaterialName6);

                        //RTB then skips ahead 6 bytes from the current position
                        bytePointerLocation += 6;
                    }

                    uint UnknownEnvValue = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                    //RTB then skips ahead 2 bytes from the current position
                    bytePointerLocation += 2;

                    float Float2 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    uint MaterialHeaderLength7 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                    if (MaterialHeaderLength7 > 1000)
                    {
                        ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red);
                        Console.WriteLine("Something went wrong! Crashing gracefully!");
                        Console.ResetColor();
                        return;
                    }

                    uint MaterialNameLength7 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 6; //rtb subtracts 6 for whatever reason?

                    if (MaterialHeaderLength7 > 8)
                    {
                        string MaterialName7 = ByteFunctions.ReadFixedString(fileBytes, MaterialNameLength7, ref bytePointerLocation);
                        Console.WriteLine("Environment Map: {0}", MaterialName7);

                        //RTB then skips ahead 6 bytes from the current position
                        bytePointerLocation += 6;
                    }
                }

                float FloatX3 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                float FloatY3 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                float FloatZ3 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                float FloatX4 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                float FloatY4 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                float FloatZ4 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                float FloatX5 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                float FloatY5 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                float FloatZ5 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);

                //RTB then skips ahead 1 byte from the current position
                bytePointerLocation += 1;

                if (D3DMESH.options_EARLY_GAME_FIX == 1)
                {
                    if (MatPlus == 1)
                    {
                        float FloatX6 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                        float FloatY6 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                        float FloatZ6 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                        float FloatX7 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                        float FloatY7 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                        float FloatZ7 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                        float FloatX8 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                        float FloatY8 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                        float FloatZ8 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    }

                    float Float10 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float Float11 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);

                    if (MatPlus == 1)
                    {
                        uint unknown = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                        //RTB then skips ahead 1 byte from the current position
                        bytePointerLocation += 1;
                    }
                }
                else if (D3DMESH.options_EARLY_GAME_FIX == 2)
                {
                    float FloatX6 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float FloatY6 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float FloatZ6 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float FloatX7 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float FloatY7 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float FloatZ7 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float FloatX8 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float FloatY8 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float FloatZ8 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float Float10 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float Float11 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);

                    //RTB then skips ahead 2 bytes from the current position
                    bytePointerLocation += 2;

                    uint unknown1 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                    uint Float12 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                    uint unknown2 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                    //RTB then skips ahead 1 byte from the current position
                    bytePointerLocation += 1;
                }
                else if (D3DMESH.options_EARLY_GAME_FIX == 3)
                {
                    float FloatX6 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float FloatY6 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float FloatZ6 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float FloatX7 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float FloatY7 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float FloatZ7 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float FloatX8 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float FloatY8 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float FloatZ8 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float Float10 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                    float Float11 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);

                    //RTB then skips ahead 5 bytes from the current position
                    bytePointerLocation += 5;

                    uint unknown1 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                    uint float12 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                    uint unknown2 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                    //RTB then skips ahead 1 byte from the current position
                    bytePointerLocation += 1;
                }

                //uint NameLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                NameLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                if (NameLength > 1000)
                {
                    ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red);
                    Console.WriteLine("Something went wrong! Crashing gracefully!");
                    Console.ResetColor();
                    return;
                }

                //RTB then skips ahead 'NameLength' amount from the current position
                bytePointerLocation += NameLength;

                if (D3DMESH.options_EARLY_GAME_FIX == 1)
                {
                    if (FooterPlus == 1)
                    {
                        //uint NameLength2 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                        NameLength2 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                        if (NameLength2 > 1000)
                        {
                            ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red);
                            Console.WriteLine("Something went wrong! Crashing gracefully!");
                            Console.ResetColor();
                            return;
                        }

                        //RTB then skips ahead 'NameLength2' amount from the current position
                        bytePointerLocation += NameLength2;
                    }
                }
                else if (D3DMESH.options_EARLY_GAME_FIX > 1)
                {
                    //uint NameLength2 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                    NameLength2 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                    if (NameLength2 > 1000)
                    {
                        ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red);
                        Console.WriteLine("Something went wrong! Crashing gracefully!");
                        Console.ResetColor();
                        return;
                    }

                    //RTB then skips ahead 'NameLength2' amount from the current position
                    bytePointerLocation += NameLength2;
                }

                Polygon_Info_Struct polygon_Info_Struct = new Polygon_Info_Struct()
                {
                    VertexMin = VertexMin,
                    VertexMax = VertexMax,
                    PolygonStart = PolygonStart,
                    PolygonCount = PolygonCount,
                    FacePointCount = FacepointCount,
                    MatName = MaterialName,
                    BoneSetNum = BoneSetNum,
                    SingleBindNode = SingleBindNode
                };

                PolyStruct_array.Add(polygon_Info_Struct);
            }

            Console.WriteLine("Header C (Bone IDs) start = {0}", bytePointerLocation);

            uint IDHeaderLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation) - 4;
            uint BoneIDSets = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

            Console.WriteLine("Count = {0}", BoneIDSets);

            for (int i = 0; i < BoneIDSets; i++)
            {
                BoneIDOffset_array.Add((uint)bytePointerLocation);

                uint BoneIDTotal = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                for (int x = 0; x < BoneIDTotal; x++)
                {
                    uint BoneIDHeaderLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                    uint BoneIDNameLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                    string BoneName = ByteFunctions.ReadFixedString(fileBytes, BoneIDNameLength, ref bytePointerLocation);
                    uint FFFFFFFF = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                }
            }

            FooterCheck = 48;

            do
            {
                FooterCheck = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);
            }
            while (FooterCheck != 101);

            //RTB then seeks ahead 3 bytes
            bytePointerLocation += 3;

            Console.WriteLine("Face info start = {0}", bytePointerLocation);

            uint FaceCount = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            uint FaceLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            Console.WriteLine("Count = {0}, Length = {1}", FaceCount, FaceLength);
            Console.WriteLine("Face start = {0}", bytePointerLocation);

            for (int i = 0; i < FaceCount / 3; i++)
            {
                ushort fa = ByteFunctions.ReadUnsignedShort(fileBytes, ref bytePointerLocation);
                fa += 1; //RTB adds 1 for whatever reason?

                ushort fb = ByteFunctions.ReadUnsignedShort(fileBytes, ref bytePointerLocation);
                fb += 1; //RTB adds 1 for whatever reason?

                ushort fc = ByteFunctions.ReadUnsignedShort(fileBytes, ref bytePointerLocation);
                fc += 1; //RTB adds 1 for whatever reason?

                Face_Data face_Data = new Face_Data()
                {
                    a = fa,
                    b = fb,
                    c = fc
                };

                Face_array.Add(face_Data);
            }

            uint FileEnd = 0;
            uint BufferNum = 0;
            uint NormalLayer = 1;
            uint UVLayer = 1;
            uint BufferFlag = 1; //can't do undefined, so we will just substitue zero for undefined
            uint Failsafe = 0;

            do
            {
                BufferFlag = 0x30;
                Failsafe = 0;

                do
                {
                    BufferFlag = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);

                    if (Failsafe > 5)
                    {
                        BufferFlag = 0;
                        Console.WriteLine("Unexpected flag count!");
                    }

                    BufferNum += 1;
                    Failsafe += 1;
                }
                while (BufferFlag == 0x30);

                if (BufferFlag != 0)
                {
                    BufferFlag = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);
                    uint BufferCount = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                    uint BufferLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                    uint BufferType = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                    //Flags - "1" = buffer, "0" - skip
                    //1 = Vertex positions
                    //2 = Normals
                    //3 = Weights
                    //4 = Bone IDs
                    //5 = UVs(1)
                    //6 = UVs(2)
                    //7 = UVs(3)
                    //8 = UVs(4)
                    //9 = Binormals ?
                    //10 = Vertex alphas

                    if (BufferType == 1 || (BufferType == 0 && BufferNum == 1))
                    {
                        uint BufferFlagB = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);
                        Console.WriteLine("Vertex start = {0}, Count = {1}, Length = {2}, Type = {3}", bytePointerLocation, BufferCount, BufferLength, BufferType);

                        for (int i = 0; i < BufferCount; i++)
                        {
                            float vx = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation) * D3DMESH.options_MODEL_SCALE;
                            float vy = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation) * D3DMESH.options_MODEL_SCALE;
                            float vz = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation) * D3DMESH.options_MODEL_SCALE;

                            Vertex_Data vertex_Data = new Vertex_Data()
                            {
                                x = vx,
                                y = vy,
                                z = vz
                            };

                            Vert_array.Add(vertex_Data);
                        }
                    }
                    else if (BufferType == 2 || (BufferType == 0 && BufferNum == 2 || BufferNum == 9))
                    {
                        uint BufferFlagB = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);
                        Console.WriteLine("Normals ({0}) start = {1}, Count = {2}, Length = {3}, Type = {4}", NormalLayer, bytePointerLocation, BufferCount, BufferLength, BufferType);

                        if (BufferType == 0)
                        {
                            for (int i = 0; i < BufferCount; i++)
                            {
                                float nx = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                                float ny = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                                float nz = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);

                                Normal_Data normal_Data = new Normal_Data()
                                {
                                    x = nx,
                                    y = ny,
                                    z = nz
                                };

                                Normal_array.Add(normal_Data);
                            }
                        }
                        else if (BufferType == 2)
                        {
                            for (int i = 0; i < BufferCount; i++)
                            {
                                ushort normVal = ByteFunctions.ReadUnsignedShort(fileBytes, ref bytePointerLocation);
                            }
                        }

                        NormalLayer += 1;
                    }
                    else if (BufferType == 3 || (BufferType == 0 && BufferNum > 4 && BufferNum < 9))
                    {
                        uint BufferFlagB = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);
                        Console.WriteLine("UVs ({0}) start = {1}, Count = {2}, Length = {3}, Type = {4}", UVLayer, bytePointerLocation, BufferCount, BufferLength, BufferType);

                        for (int i = 0; i < BufferCount; i++)
                        {
                            float tu = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                            float tv = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                            tv = (tv * -1) + 1;

                            UV_Data uv_data = new UV_Data()
                            {
                                u = tu,
                                v = tv,
                                a = 0
                            };

                            switch (UVLayer)
                            {
                                case 1:
                                    UV_array.Add(uv_data);
                                    break;
                                case 2:
                                    UV2_array.Add(uv_data);
                                    break;
                                case 3:
                                    UV3_array.Add(uv_data);
                                    break;
                                case 4:
                                    UV4_array.Add(uv_data);
                                    break;
                            }
                        }

                        UVLayer += 1;
                    }
                    else if (BufferType == 4 || (BufferType == 0 && BufferNum == 3))
                    {
                        //LEFT OFF AT 1493 LINE

                        uint BufferFlagB = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);
                        Console.WriteLine("Weights start = {0}, Count = {1}, Length = {2}, Type = {3}", bytePointerLocation, BufferCount, BufferLength, BufferType);

                        for (int i = 0; i < BufferCount; i++)
                        {
                            float Weight1 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                            float Weight2 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                            float Weight3 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                            float Weight4 = 0.0f;

                            Weight_Info_Struct weight_Info_Struct = new Weight_Info_Struct()
                            {
                                Weight1 = Weight1,
                                Weight2 = Weight2,
                                Weight3 = Weight3,
                                Weight4 = Weight4
                            };

                            W1_array.Add(weight_Info_Struct);
                        }
                    }
                    else if (BufferType == 5 || (BufferType == 0 && BufferNum == 4))
                    {
                        uint BufferFlagB = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);
                        Console.WriteLine("Bone IDs start = {0}, Count = {1}, Length = {2}, Type = {3}", bytePointerLocation, BufferCount, BufferLength, BufferType);

                        for (int i = 0; i < BufferCount; i++)
                        {
                            uint Bone1 = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 4;
                            uint Bone2 = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 4;
                            uint Bone3 = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 4;
                            uint Bone4 = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation) / 4;

                            Bone_Info_Struct bone_Info_Struct = new Bone_Info_Struct()
                            {
                                Bone1 = Bone1,
                                Bone2 = Bone2,
                                Bone3 = Bone3,
                                Bone4 = Bone4
                            };

                            B1_array.Add(bone_Info_Struct);
                        }
                    }
                    else if (BufferType == 6 || (BufferType == 0 && BufferNum == 10))
                    {
                        uint BufferFlagB = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);
                        Console.WriteLine("Vertex alphas start = {0}, Count = {1}, Length = {2}, Type = {3}", bytePointerLocation, BufferCount, BufferLength, BufferType);

                        for (int i = 0; i < BufferCount; i++)
                        {
                            float VertexAlpha = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);

                            if (D3DMESH.options_VERTEX_COLORS)
                            {
                                Color_Data color_Data = new Color_Data()
                                {
                                    r = 255,
                                    g = 255,
                                    b = 255
                                };

                                Color_array.Add(color_Data);
                                Alpha_array.Add(VertexAlpha);
                            }
                        }
                    }
                    else
                    {
                        Console.WriteLine("Error parsing buffer, cancelling process.");
                        BufferFlag = 0;
                    }
                }

                Console.WriteLine("Buffer end = {0}", bytePointerLocation);
            }
            while (BufferFlag != 0);

            Console.WriteLine("End of file = {0}", bytePointerLocation);
            Console.WriteLine(PolyStruct_array);

            if (B1_array.Count == 0)
            {
                for (int i = 0; i < Vert_array.Count; i++)
                {
                    Bone_Info_Struct bone_Info_Struct = new Bone_Info_Struct()
                    {
                        Bone1 = 0,
                        Bone2 = 0,
                        Bone3 = 0,
                        Bone4 = 0
                    };

                    B1_array.Add(bone_Info_Struct);
                }

                NoRig = 1;

                if (BoneIDSets > 0)
                {
                    Console.WriteLine("{0} uses single-bind rigging.", BaseName);
                }
            }

            if (W1_array.Count == 0)
            {
                for (int i = 0; i < Vert_array.Count; i++)
                {
                    Weight_Info_Struct weight_Info_Struct = new Weight_Info_Struct()
                    {
                        Weight1 = 1,
                        Weight2 = 0,
                        Weight3 = 0,
                        Weight4 = 0
                    };

                    W1_array.Add(weight_Info_Struct);
                }
            }

            if (UV_array.Count == 0)
            {
                for (int i = 0; i < Vert_array.Count; i++)
                {
                    UV_Data uv_data = new UV_Data()
                    {
                        u = 0,
                        v = 0,
                        a = 0
                    };

                    UV_array.Add(uv_data);
                }
            }

            for (int i = 0; i < PolyStruct_array.Count; i++)
            {
                List<string> ProperBoneID_array = new List<string>();
                List<Bone_Info_Struct> ActualB1_array = new List<Bone_Info_Struct>();
                List<Weight_data> Weight_array = new List<Weight_data>();
                List<Face_Data> Face_array2 = new List<Face_Data>();

                if (sklFile.BoneCount != 0 && BoneIDSets > 0)
                {
                    int index = 1 * (int)PolyStruct_array[i].BoneSetNum;
                    bytePointerLocation = BoneIDOffset_array[index];

                    uint BoneIDTotal = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                    ProperBoneID_array = new List<string>();

                    for (int x = 0; x < BoneIDTotal; x++)
                    {
                        uint BoneIDHeaderLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                        uint BoneIDNameLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                        string BoneName = ByteFunctions.ReadFixedString(fileBytes, BoneIDNameLength, ref bytePointerLocation);
                        ProperBoneID_array.Add(BoneName);
                        uint FFFFFFFF = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                    }

                    for (int x = 0; x < BoneIDTotal; x++)
                    {
                        for (int y = 0; y < BoneIDTotal; y++)
                        {
                            if (ProperBoneID_array[x] == sklFile.BoneName_array[y])
                            {
                                FixedBoneID_array.Add((uint)y);
                            }
                        }
                    }

                    for (int x = 0; x < B1_array.Count; x++)
                    {
                        if (NoRig == 1)
                        {
                            uint ProperBone1 = FixedBoneID_array[(int)PolyStruct_array[i].SingleBindNode + 1];

                            Bone_Info_Struct bone_Info_Struct = new Bone_Info_Struct()
                            {
                                Bone1 = ProperBone1,
                                Bone2 = 1,
                                Bone3 = 1,
                                Bone4 = 1
                            };

                            ActualB1_array.Add(bone_Info_Struct);
                        }
                        else
                        {
                            uint ProperBone1 = FixedBoneID_array[(int)B1_array[x].Bone1 + 1];
                            uint ProperBone2 = FixedBoneID_array[(int)B1_array[x].Bone2 + 1];
                            uint ProperBone3 = FixedBoneID_array[(int)B1_array[x].Bone3 + 1];
                            uint ProperBone4 = FixedBoneID_array[(int)B1_array[x].Bone4 + 1];

                            if (ProperBone1 == 0)
                            {
                                ProperBone1 = 1;
                            }

                            if (ProperBone2 == 0)
                            {
                                ProperBone2 = 1;
                            }

                            if (ProperBone3 == 0)
                            {
                                ProperBone3 = 1;
                            }

                            if (ProperBone4 == 0)
                            {
                                ProperBone4 = 1;
                            }

                            Bone_Info_Struct bone_Info_Struct = new Bone_Info_Struct();
                            bone_Info_Struct.Bone1 = ProperBone1;
                            bone_Info_Struct.Bone2 = ProperBone2;
                            bone_Info_Struct.Bone3 = ProperBone3;
                            bone_Info_Struct.Bone4 = ProperBone4;

                            ActualB1_array.Add(bone_Info_Struct);
                        }
                    }

                    for (int b = 1; b < W1_array.Count; b++)
                    {
                        Weight_data weight_Data = new Weight_data();
                        weight_Data.BoneIDs = new List<uint>();
                        weight_Data.weights = new List<float>();

                        float maxweight = 0;

                        if (W1_array[b].Weight1 != 0)
                        {
                            maxweight += W1_array[b].Weight1;
                        }

                        if (W1_array[b].Weight2 != 0)
                        {
                            maxweight += W1_array[b].Weight2;
                        }

                        if (W1_array[b].Weight3 != 0)
                        {
                            maxweight += W1_array[b].Weight3;
                        }

                        if (W1_array[b].Weight4 != 0)
                        {
                            maxweight += W1_array[b].Weight4;
                        }

                        if (maxweight != 0)
                        {
                            if (W1_array[b].Weight1 != 0)
                            {
                                weight_Data.BoneIDs.Add(ActualB1_array[b].Bone1);
                                weight_Data.weights.Add(W1_array[b].Weight1);
                            }
                            if (W1_array[b].Weight2 != 0)
                            {
                                weight_Data.BoneIDs.Add(ActualB1_array[b].Bone2);
                                weight_Data.weights.Add(W1_array[b].Weight2);
                            }
                            if (W1_array[b].Weight3 != 0)
                            {
                                weight_Data.BoneIDs.Add(ActualB1_array[b].Bone3);
                                weight_Data.weights.Add(W1_array[b].Weight3);
                            }
                            if (W1_array[b].Weight4 != 0)
                            {
                                weight_Data.BoneIDs.Add(ActualB1_array[b].Bone4);
                                weight_Data.weights.Add(W1_array[b].Weight4);
                            }
                        }

                        Weight_array.Add(weight_Data);
                    }

                    for (uint y = PolyStruct_array[i].PolygonStart; y < PolyStruct_array[i].PolygonCount + PolyStruct_array[i].PolygonStart; y++)
                    {
                        Face_array2.Add(Face_array[(int)y]);
                    }

                    uint VertexMin = PolyStruct_array[i].VertexMin;
                    uint VertexMax = PolyStruct_array[i].VertexMax;

                    int FacePlus = AllVert_array.Count;

                    for (int x = (int)VertexMin; x < VertexMax; x++)
                    {
                        AllVert_array.Add(Vert_array[x]);

                        if (Normal_array.Count > 0)
                        {
                            AllNormal_array.Add(Normal_array[x]);
                        }

                        AllUV_array.Add(UV_array[0]);

                        if (UV2_array.Count > 0)
                        {
                            AllUV2_array.Add(UV2_array[x]);
                        }

                        if (UV3_array.Count > 0)
                        {
                            AllUV3_array.Add(UV3_array[x]);
                        }

                        if (UV4_array.Count > 0)
                        {
                            AllUV4_array.Add(UV4_array[x]);
                        }

                        if (Color_array.Count > 0)
                        {
                            AllColor_array.Add(Color_array[x]);
                            AllAlpha_array.Add(Alpha_array[x]);
                        }

                        AllWeight_array.Add(Weight_array[x]);
                    }

                    for (int x = 0; x < PolyStruct_array[i].PolygonCount; x++)
                    {
                        var t = Face_array2[x];
                        var fh = PolyStruct_array[i].VertexMin;
                        //var Faces3 = ((t - fh) + 1 + FacePlus);
                        //LEFT OFF AT LINE 1652
                    }
                }
            }
        }
        //ENDS AT LINE 1680 IN THE TelltaleGames_D3DMesh.ms script
    }
}

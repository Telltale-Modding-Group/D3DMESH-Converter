using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace converter
{
    public class SKL
    {
        public uint BoneCount;
        public uint VerNum;
        public uint D3DNameHeaderLength;
        public List<string> BoneName_array = new List<string>();

        public void ParseSKLFile(string sklFilePath, BoneNames boneNames)
        {
            //STARTS AT LINE 927 IN THE TelltaleGames_D3DMesh.ms script
            ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Blue); 
            Console.WriteLine("Parsing {0}...", sklFilePath);
            Console.ResetColor();

            //---------------GETTING .SKL FILE---------------
            //read the byte data from the SKL file
            byte[] fileBytes = File.ReadAllBytes(sklFilePath);
            uint bytePointerLocation = 0;

            int BttFCheck = 0;
            int BttFFix = 0;
            int BoneHeaderMagic = 0;

            if (VerNum == 17)
            {
                //RTB skips ahead 40 bytes in the SKL file
                bytePointerLocation = 40;

                BttFCheck = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);
                Console.WriteLine("BttFCheck: {0}", D3DNameHeaderLength);

                //RTB then goes back to the start of the SKL file
                bytePointerLocation = 0;

                //From RTB: Back to the Future PS4 uses "Version 17" models with "Version 18" bone structures for some reason.
                if (BttFCheck == -1339414801)
                {
                    BttFFix = 1;
                }
            }

            BoneHeaderMagic = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);
            Console.WriteLine("BoneHeaderMagic: {0}", BoneHeaderMagic);

            //---------------PARSING AND INTERPERTING DATA FROM THE SKL HEADER---------------

            //temp values that will be assigned
            byte[] raw_ParamCount = null;
            uint ParamCount = 0;
            byte[] raw_ParamHashCheck = null;
            uint ParamHashCheck = 0;

            byte[] raw_FileSize = null;
            uint FileSize = 0;

            //account for different header versions (shortened from the original switch statement because there was redudant code)
            if (BoneHeaderMagic == 1296189774 || BoneHeaderMagic == 1297371717)
            {
                //------------------------------------Headers with - MBIN (NIBM)------------------------------------
                //------------------------------------AND Headers with - MTRE (ERTM)------------------------------------
                ParamCount = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                Console.WriteLine("ParamCount: {0}", ParamCount);

                ParamHashCheck = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                Console.WriteLine("ParamHashCheck: {0}", ParamHashCheck);

                //RTB goes back 4 bytes from the current position?
                bytePointerLocation -= 4;

                //--------------GET PARAMETERS WITHIN HEADER--------------
                //not sure what this is for but RTB seems to attempt to parse some "parameters" within the header
                if (ParamHashCheck > 0 && ParamHashCheck < 128)
                {
                    for (int i = 0; i < ParamCount; i++)
                    {
                        uint ParamNameLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                        Console.WriteLine("ParamNameLength: {0}", ParamNameLength);

                        string ParamName = ByteFunctions.ReadFixedString(fileBytes, ParamNameLength, ref bytePointerLocation);
                        Console.WriteLine("ParamName: {0}", ParamName);

                        uint ParamUnk = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                        Console.WriteLine("ParamUnk: {0}", ParamUnk);
                    }
                }
                else
                {
                    //for each 'parameter' in the SKL header
                    for (int i = 0; i < ParamCount; i++)
                    {
                        //RTB then skips ahead 12 bytes from the current position?
                        bytePointerLocation += 12;
                    }
                }
            }
            else if(BoneHeaderMagic == 1297307189 || BoneHeaderMagic == 1297307190)
            {
                //------------------------------------Headers with - MSV5 (5VSM)------------------------------------
                //------------------------------------AND Headers with - MSV6 (6VSM)------------------------------------
                FileSize = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                Console.WriteLine("FileSize: {0}", FileSize);

                //RTB then skips ahead 8 bytes?
                bytePointerLocation += 8;

                ParamCount = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                Console.WriteLine("ParamCount: {0}", ParamCount);

                //for each 'parameter' in the SKL header
                for (int i = 0; i < ParamCount; i++)
                {
                    //RTB then skips ahead 12 bytes from the current position?
                    bytePointerLocation += 12;
                }
            }
            else
            {
                Console.WriteLine("Bone header seems malformed, attempting to parse anyway.");

                ParamCount = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                Console.WriteLine("ParamCount: {0}", ParamCount);

                ParamHashCheck = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                Console.WriteLine("ParamHashCheck: {0}", ParamHashCheck);

                //RTB goes back 4 bytes from the current position?
                bytePointerLocation -= 4;

                //--------------GET PARAMETERS WITHIN HEADER--------------
                //not sure what this is for but RTB seems to attempt to parse some "parameters" within the header
                if (ParamHashCheck > 0 && ParamHashCheck < 128)
                {
                    for (int i = 0; i < ParamCount; i++)
                    {
                        uint ParamNameLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                        Console.WriteLine("ParamNameLength: {0}", ParamNameLength);

                        string ParamName = ByteFunctions.ReadFixedString(fileBytes, ParamNameLength, ref bytePointerLocation);
                        Console.WriteLine("ParamName: {0}", ParamName);

                        uint ParamUnk = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                        Console.WriteLine("ParamUnk: {0}", ParamUnk);
                    }
                }
                else
                {
                    //for each 'parameter' in the SKL header
                    for (int i = 0; i < ParamCount; i++)
                    {
                        //RTB then skips ahead 12 bytes from the current position?
                        bytePointerLocation += 12;
                    }
                }
            }

            //---------------------GETTING ADDITIONAL DATA FROM SKL HEADER---------------------

            if (VerNum == 0 && D3DMESH.options_EARLY_GAME_FIX > 4 && D3DMESH.options_EARLY_GAME_FIX < 8)
            {
                //RTB then skips ahead 1 byte from the current position?
                bytePointerLocation += 1;
            }

            uint BoneFileSize = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            Console.WriteLine("BoneFileSize: {0}", BoneFileSize);

            BoneCount = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            Console.WriteLine("BoneCount: {0}", BoneCount);

            //---------------------START PARSING BONE DATA---------------------
            //if the bone count is not at zero
            if (BoneCount != 0)
            {
                //foreach bone in the skl file
                for (int i = 0; i < BoneCount; i++)
                {
                    //Console.WriteLine("BONE ENTRY {0}", i);

                    if (VerNum > 0 || (VerNum == 0 && D3DMESH.options_EARLY_GAME_FIX > 3))
                    {
                        uint BoneHash2 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                        uint BoneHash1 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);

                        //---------------BoneName---------------
                        //string BoneName = "0x" + BoneHash1.ToString("X");
                        string BoneName = BoneHash1.ToString("X");

                        //ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Yellow); 

                        //check in our bone names hash database if we have the name for the matching hash
                        for (int x = 0; x < boneNames.BoneHash_array.Count; x++)
                        {
                            bool firstHashCheck = BoneHash1 == boneNames.BoneHash_array[x].BoneHash1;
                            bool secondHashCheck = BoneHash2 == boneNames.BoneHash_array[x].BoneHash2;

                            if (firstHashCheck && secondHashCheck)
                            {
                                BoneName = boneNames.BoneHash_array[x].BoneString;

                                //ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Green); 
                            }
                        }

                        //Console.WriteLine("BoneName: {0}", BoneName);
                        //Console.ResetColor();

                        BoneName_array.Add(BoneName);

                        if (VerNum < 13)
                        {
                            int Padding = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);
                        }
                    }
                    else
                    {
                        int BoneNameSectLength = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);
                        int BoneNameLength = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);
                        string BoneName = ByteFunctions.ReadFixedString(fileBytes, BoneNameLength, ref bytePointerLocation);

                        BoneName_array.Add(BoneName);
                    }

                   if(VerNum > 0 || (VerNum == 0 && D3DMESH.options_EARLY_GAME_FIX > 3))
                   {
                       uint BoneParentHash2 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                       uint BoneParentHash1 = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                       string BoneParentName = BoneParentHash1.ToString("X");

                       if (VerNum < 13)
                       {
                            int Padding = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);
                       }
                   }
                   else
                   {
                       int BoneParentNameSectLength = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);
                       int BoneParentNameLength = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);
                       string BoneParentName = ByteFunctions.ReadFixedString(fileBytes, BoneParentNameLength, ref bytePointerLocation);
                   }

                   int BoneParent = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);

                   if(BoneParent < -1)
                   {
                       BoneParent = -1;
                   }

                   //append BoneParent_array BoneParent

                   if (VerNum >= 18 || BttFFix == 1)
                   {
                       float BoneUnk1 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                       float BoneUnk2 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                       float BoneUnk3 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   }

                   float BoneTX = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation) * D3DMESH.options_MODEL_SCALE;
                   float BoneTY = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation) * D3DMESH.options_MODEL_SCALE;
                   float BoneTZ = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation) * D3DMESH.options_MODEL_SCALE;
                   float BoneRX = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   float BoneRY = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   float BoneRZ = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   float BoneRW = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation) * -1.0f;
                   int MayBeHeader = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);
                   float nothing3 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   float nothing4 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   float nothing5 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   float BoneQ = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   float nothing6 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   float nothing7 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   float nothing8 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   float BoneXX = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   float BoneXY = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   float BoneXZ = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   float BoneYX = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   float BoneYY = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   float BoneYZ = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   float BoneZX = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   float BoneZY = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   float BoneZZ = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   int IKHeaderLength = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);
                   int IKAmount = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);

                   for(int x = 0; x < IKAmount; x++)
                   {
                       if(VerNum == 55)
                       {
                           int IKNameHash1 = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);
                           int IKNameHash2 = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);
                       }
                       else
                       {
                           int IKNameLength = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);
                           string IKName = ByteFunctions.ReadFixedString(fileBytes, IKNameLength, ref bytePointerLocation);
                       }

                       float IKInfluence = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   }

                   if (VerNum > 1)
                   {
                       int landofpilength = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);
                       int piamountlength = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);

                       for (int x = 0; x < piamountlength; x++)
                       {
                           float float1 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                           float float2 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                           float float3 = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                       }

                       int piHeaderLength = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);
                       float pinx = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                       float pipx = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                       float piny = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                       float pipy = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                       float pinz = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                       float pipz = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                       float piend = ByteFunctions.ReadFloat(fileBytes, ref bytePointerLocation);
                   }
                }
            }

            //ENDS AT LINE 1126 IN THE TelltaleGames_D3DMesh.ms script
        }
    }
}

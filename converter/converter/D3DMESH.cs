using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

/*
-- Known version numbers:
-- "NIBM" (a.k.a. "Version 0"): Bone: Out from Boneville / The Great Cow Race, CSI: 3 Dimensions of Murder / Hard Evidence, Sam & Max: Save the World / Beyond Time and Space, Telltale Texas Hold'em
-- "ERTM" (a.k.a. "Version 0.5"): Strong Bad's Cool Game for Attractive People, Wallace & Gromit's Grand Adventures Ep. 1-3
-- Version 1 [UNSUPPORTED]: Back to the Future: The Game [PC], CSI: Deadly Intent / Fatal Conspiracy, Poker Night at the Inventory, Sam & Max: The Devil's Playhouse, Tales of Monkey Island, Wallace & Gromit Ep. 4
-- Version 2: Jurassic Park: The Game, Law & Order: Legacies
-- Version 5: The Walking Dead: Season 1 [PC]
-- Version 12: Poker Night 2
-- Version 13: The Wolf Among Us [PC]
-- Version 14: The Wolf Among Us [PS4], The Walking Dead: Season 1 [PS4], The Walking Dead: Season 2 [PC / PS4]
-- Version 17: Back to the Future: The Game (30th Anniversary) [PS4], Game of Thrones [PC / PS4], Tales from the Borderlands [PC / PS4], Minecraft: Story Mode [PS4 Ep. 1]
-- Version 18: Minecraft: Story Mode [PC / PS4 Ep. 2-8]
-- Version 25: The Walking Dead: Michonne [PC]
-- Version 33: Batman: The Telltale Series [PC (08/05/16, pre-Ep. 5), PS4 Ep. 1]
-- Version 36: Batman: The Telltale Series [PC (12/02/16, Ep. 5, pre-"Noir")]
-- Version 37: Minecraft: Story Mode [Switch, UNSUPPORTED], The Walking Dead: A New Frontier [PC / PS4]
-- Version 38: The Walking Dead: A New Frontier [PC / PS4, "EOS" / "UpdatedMeshes"]
-- Version 39 [UNSUPPORTED]: Guardians of the Galaxy: The Telltale Series [PS4 Ep. 1]
-- Version 42: Guardians of the Galaxy: The Telltale Series [PC]
-- Version 45: Batman: The Enemy Within, Minecraft: Story Mode – Season Two [PC / PS4]
-- Version 46: Batman: The Telltale Series [PC, newest (08/08/17, "Noir" patch)], Minecraft: Story Mode – Season Two [PC / PS4, Miscellaneous] The Walking Dead Collection [PS4]
-- Version 55: The Walking Dead: The Final Season [PC], The Walking Dead: The Telltale Definitive Series [PC]
*/

/*
USEFUL LINKS WHEN CONVERTING
- Hexadecimal to decimal converter - https://www.rapidtables.com/convert/number/hex-to-decimal.html
- Maxscript documentation - https://help.autodesk.com/view/3DSMAX/2016/ENU/?guid=__files_GUID_423269A5_B395_4A90_8058_F96C0A24115F_htm
*/

namespace converter
{
    public class D3DMESH
    {
        public static string fileExtension = ".d3dmesh";

        //----------OPTIONS----------
        //'Merge' applies additional UV mapping layers to the same mesh
        //'Split' makes additional layers separate meshes instead
        //'No' just ignores them entirely.
        public static int options_UV_LAYERS = 0; //0 = Merge 1 = Split 2 = No

        //model scale
        public static float options_MODEL_SCALE = 100.0f;

        //If enabled, this will import the Level-of-Detail models for Version 33-46 games
        //(both Batman seasons, The Walking Dead: A New Frontier and the PS4 Collection, and Marvel's Guardians of the Galaxy).
        public static bool options_ENABLE_LOD = false;

        //If enabled, this will import the vertex colouring to models (if available).
        //Certain games treat vertex coloring differently, so for example if a model appears black, you can disable this option and re-import.
        public static bool options_VERTEX_COLORS = false;

        // 0 = "Texas Hold'em / Bone / CSI 3/4 / Sam and Max S1/S2 (Ep. 1/2)"
        // 1 = "Sam and Max Season 2 (Ep. 3/4)"
        // 2 = "Sam and Max Season 2 (Ep. 5 - What's New, Beelzebub?)"
        // 3 = "Strong Bad's CG4AP (Ep. 1 - Homestar Ruiner)"
        // 4 = "Strong Bad's CG4AP (Ep. 2 - Strong Badia the Free)"
        // 5 = "Strong Bad's CG4AP (Ep. 3 - Baddest of the Bands)"
        // 6 = "Strong Bad's CG4AP (Ep. 4 - Dangeresque 3)"
        // 7 = "Strong Bad's CG4AP (Ep. 5 - 8-Bit is Enough)"
        // 8 = "Wallace and Gromit (Ep. 1-3)"
        public static int options_EARLY_GAME_FIX = 0;
        //----------OPTIONS END----------

        public static void ConvertMesh_FromD3DMESH_ToObj(string meshFileName, string meshPath, string resultPath, TexNames texNames, BoneNames boneNames)
        {
            byte[] fileBytes = File.ReadAllBytes(meshPath);
            uint bytePointerLocation = 0x00;

            string meshSKLFile = meshPath.Remove(meshPath.Length - "d3dmesh".Length, "d3dmesh".Length) + "skl";

            //---------------PARSING AND INTERPERTING DATA FROM THE D3DMESH HEADER---------------
            //STARTS AT LINE 825 IN THE TelltaleGames_D3DMesh.ms script

            int HeaderMagic = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);
            Console.WriteLine("HeaderMagic: {0}", HeaderMagic);

            //temp values that will be assigned
            uint ParamCount = 0;
            uint ParamHashCheck = 0;
            byte[] raw_ParamCount = null;
            byte[] raw_ParamHashCheck = null;

            uint FileSize = 0;
            byte[] raw_FileSize = null;

            SKL sklFile = null;

            //account for different header versions (shortened from the original switch statement because of redudant code)
            if (HeaderMagic == 1296189774 || HeaderMagic == 1297371717)
            {
                //------------------------------------Headers with - MBIN (NIBM)------------------------------------
                //------------------------------------Headers with - MTRE (ERTM)------------------------------------
                ParamCount = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                Console.WriteLine("ParamCount: {0}", ParamCount);

                ParamHashCheck = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                Console.WriteLine("ParamHashCheck: {0}", ParamHashCheck);

                //RTB goes back 4 bytes from the current position?
                bytePointerLocation -= 0x04;

                Console.WriteLine("Parsing parameters in header...");
                //--------------GET PARAMETERS WITHIN HEADER--------------
                //not sure what this is for but RTB seems to attempt to parse some "parameters" within the header
                if (ParamHashCheck > 0 && ParamHashCheck < 128)
                {
                    //run a loop for the amount of parameters that are in the header
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
                    //run a loop for the amount of parameters that are in the header
                    for (int i = 0; i < ParamCount; i++)
                    {
                        //skip ahead 12 bytes? tf u doin RTB?
                        bytePointerLocation += 0x0C;
                    }
                }
            }
            else if (HeaderMagic == 1297307189 || HeaderMagic == 1297307190)
            {
                //------------------------------------Headers with - MSV5 (5VSM)------------------------------------
                //------------------------------------Headers with - MSV6 (6VSM)------------------------------------
                FileSize = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                Console.WriteLine("FileSize: {0}", FileSize);

                //RTB then seeks ahead 8 bytes from the current position
                bytePointerLocation += 0x08;

                ParamCount = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                Console.WriteLine("ParamCount: {0}", ParamCount);

                //run a loop for the amount of parameters that are in the header
                for (int i = 0; i < ParamCount; i++)
                {
                    //skip ahead 12 bytes? tf u doin RTB?
                    bytePointerLocation += 0x0C;
                }
            }
            else
            {
                if (HeaderMagic < 0 || HeaderMagic > 128)
                {
                    Console.WriteLine("Mesh header seems malformed, attempting to parse anyway.");

                    ParamCount = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                    Console.WriteLine("ParamCount: {0}", ParamCount);

                    ParamHashCheck = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
                    Console.WriteLine("ParamHashCheck: {0}", ParamHashCheck);

                    //RTB goes back 4 bytes from the current position?
                    bytePointerLocation -= 0x04;

                    Console.WriteLine("Parsing parameters in header...");
                    //--------------GET PARAMETERS WITHIN HEADER--------------
                    //not sure what this is for but RTB seems to attempt to parse some "parameters" within the header
                    if (ParamHashCheck > 0 && ParamHashCheck < 128)
                    {
                        //run a loop for the amount of parameters that are in the header
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
                        //run a loop for the amount of parameters that are in the header
                        for (int i = 0; i < ParamCount; i++)
                        {
                            //skip ahead 12 bytes? tf u doin RTB?
                            bytePointerLocation += 0x0C;
                        }
                    }
                }
                else
                {
                    //RTB sets the pointer back to the start of the file
                    bytePointerLocation = 0x00;
                }
            }

            //---------------GETTING ADDITIONAL DATA FROM THE HEADER---------------
            uint D3DNameHeaderLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            Console.WriteLine("D3DNameHeaderLength: {0}", D3DNameHeaderLength);

            uint D3DNameLength = ByteFunctions.ReadUnsignedInt(fileBytes, ref bytePointerLocation);
            Console.WriteLine("D3DNameLength: {0}", D3DNameLength);

            //RTB's offset fixer incase we parsed the incorrect value of the length of the name string
            //if the string length is greater than the length of the header
            if(D3DNameLength > D3DNameHeaderLength)
            {
                Console.WriteLine("Fixing offset, parsed 'D3DNameLength' incorrectly...", D3DNameHeaderLength);

                //RTB goes back 4 bytes
                bytePointerLocation -= 0x04;

                //RTB then assigns the string length to be the length of the header? (bro, huh?)
                D3DNameLength = D3DNameHeaderLength;
            }

            string D3DName = ByteFunctions.ReadFixedString(fileBytes, D3DNameLength, ref bytePointerLocation);
            Console.WriteLine("D3DName: {0}", D3DName);

            uint VerNum = ByteFunctions.ReadByte(fileBytes, ref bytePointerLocation);
            Console.WriteLine("VerNum: {0}", VerNum);
            //ENDS AT LINE 922 IN THE TelltaleGames_D3DMesh.ms script

            /*
            FROM RTB:
            Version 0" games use the ASCII hex code for "0" or "1" to indicate unrigged or rigged models.
            In the place where the version number would be in later titles. 
            Thankfully no other games use these two numbers!
            */
            if (VerNum == 48 || VerNum == 49)
                VerNum = 0;


            //---------------GETTING .SKL FILE (IF IT EXISTS)---------------
            //STARTS AT LINE 927 IN THE TelltaleGames_D3DMesh.ms script
            if (File.Exists(meshSKLFile))
            {
                sklFile = new SKL();

                sklFile.VerNum = VerNum;
                sklFile.D3DNameHeaderLength = D3DNameHeaderLength;

                sklFile.ParseSKLFile(meshSKLFile, boneNames);
            }
            //ENDS AT LINE 1126 IN THE TelltaleGames_D3DMesh.ms script

            //---------------GET MORE DATA FROM THE D3DMESH---------------
            //This is also the part of his script that explains why the heck its as long as it is :P
            //I've broken down and seperated each case of the switch statement into a seperate class for simplicity and clarity
            //STARTS AT LINE 1128 IN THE TelltaleGames_D3DMesh.ms script

            if (VerNum == 0 && options_EARLY_GAME_FIX < 4)
            {
                //default case in switch statement

                D3DMESH_Default.ConvertMesh_D3DMESH(fileBytes, ref bytePointerLocation, D3DName, sklFile);
            }
            else if (VerNum == 5)
            {
                //Version 5: The Walking Dead Season 1[PC]

                string testOBJ = meshPath.Remove(meshPath.Length - "d3dmesh".Length, "d3dmesh".Length) + "obj";

                D3DMESH_V5.ConvertMesh_D3DMESH(fileBytes, ref bytePointerLocation, D3DName, sklFile, testOBJ, true);
            }
            else if (VerNum == 55)
            {
                //Version 55: The Walking Dead: The Final Season, The Walking Dead: The Telltale Definitive Series

                //D3DMESH_V55.ConvertMesh_D3DMESH(fileBytes, ref bytePointerLocation, D3DName, sklFile);
            }
        }
    }
}

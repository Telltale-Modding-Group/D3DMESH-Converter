using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Assimp.Configs;
using Assimp;
using Assimp.Unmanaged;

/*
This standalone program is a translation of...

Author - Random Talking Bush
Script - Telltale All In One Model Importer script (MaxScript)
Original Link - https://forum.xentax.com/viewtopic.php?f=16&t=11687

The script imports the majority of models from most telltale games.
This was also written originally for 3DS Max (MaxScript) but I've decided to break the script down and translate it into C# to make a standalone application that will convert the files without the need to installing the software.
(In addition to that, I also want to attempt to add support for doing modifications to models as I have for my D3DTX to DDS texture project)

Currently as I'm still translating his absurdly long MaxScript... (11769 LINES!!!!!!!)
Not all of the games will be supported just yet as I'm prioritizing versions of games that I currently have installed.
ATM those are 

- Version 5: The Walking Dead Season 1 [PC]
- Version 55: The Walking Dead: The Final Season, The Walking Dead: The Telltale Definitive Series


NOTE TO Random Talking Bush (RTB): 
RTB, if you are reading this... I hope you forgive me if your pissed about this project being a thing for whatever reason...
3DS Max is not that accessible to people (even with educational license which autodesk is cracking down harder on) 
So having this as a smaller/simpler standalone application would help alot for people who just want to extract models without needing to install a complete 3d modeling package to do so.

I've also decided to embark on this project because I wanted to "de-magic-ify" your script, clean it up as much as I can, and also understand better what the heck the D3DMESH format is.
Given that its a difficult thing to understand and going through 11769 lines of code just to understand how to read it is also a monstrous pain in the bum...
and to make matters worse, your script really is the only thing on the internet that can read and understand d3dmesh files, apart from telltale devs themselves... so desperate times call for desperate measures!

With that said, I'm trying to break down, simplify, and comment as much as I can to help others understand how to read and interpert the d3dmesh file as well

However, with that said... alot of what I'm doing piggy backs off of your original script,
And sadly you didn't put that many descriptive comments on a lot of parts of your original MaxScript (I will restrain my rage for later... :P)... since you do a lot of funky stuff and I don't understand why...
If you are in town, could you please hit me up and also help me understand as to why you did certain things in the script to get things working?
*/

namespace converter
{
    /// <summary>
    /// Main program script
    /// </summary>
    public class Program
    {
        //not important, but these preassign variables help for iterating fast when testing and converting files
        public static bool usePreassignedPath = true;
        public static string preassign_d3dmeshPath = "C:/Users/david/Desktop/telltale-d3dmesh/D3DMESH";
        public static string preassign_boneNamesPath = "C:/Users/david/Desktop/telltale-d3dmesh/RTB-Original/TelltaleHashDBs/BoneNames.HashDB";
        public static string preassign_boneNamesTextPath = "C:/Users/david/Desktop/telltale-d3dmesh/RTB-Original/TelltaleHashDBs/BoneNames.txt";
        public static string preassign_texNamesPath = "C:/Users/david/Desktop/telltale-d3dmesh/RTB-Original/TelltaleHashDBs/TexNames.HashDB";
        public static string preassign_texNamesTextPath = "C:/Users/david/Desktop/telltale-d3dmesh/RTB-Original/TelltaleHashDBs/TexNames.txt";
        public static string preassign_resultPath = "C:/Users/david/Desktop/telltale-d3dmesh/OBJ";

        //shows the console output of reading the BoneNames and TexNames .HashDB files.
        public static bool showSetupConsoleOutput = false;

        public static BoneNames boneNames;
        public static TexNames texNames;

        static void Main(string[] args)
        {
            App_Convert_D3DMesh_Mode();
        }

        public static void App_Convert_D3DMesh_Mode()
        {
            //introduction
            ConsoleFunctions.SetConsoleColor(ConsoleColor.Blue, ConsoleColor.White); 
            Console.WriteLine("D3DMESH to OBJ Converter");

            //----------------SETUP - BONE NAMES----------------
            ConsoleFunctions.SetConsoleColor(ConsoleColor.Blue, ConsoleColor.White); 
            Console.WriteLine("SETUP");
            ConsoleFunctions.SetConsoleColor(ConsoleColor.DarkGray, ConsoleColor.White); 
            Console.WriteLine("Enter the path of the BoneNames.HashDB");

            //file path
            string boneNamesPath = "";
            string boneNamesTextPath = "";

            if (!usePreassignedPath)
            {
                //run a loop until the path is valid
                bool inBoneNamesPathLoop = true;
                while (inBoneNamesPathLoop)
                {
                    //get path from user
                    ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.White); 
                    boneNamesPath = Console.ReadLine();

                    if (boneNamesPath[0].Equals('"'))
                    {
                        boneNamesPath = boneNamesPath.Remove(0, 1);
                        boneNamesPath = boneNamesPath.Remove(boneNamesPath.Length - 1, 1);
                    }

                    //check if the path is valid
                    if (File.Exists(boneNamesPath) == false)
                    {
                        //notify the user and this loop will run again
                        ConsoleFunctions.SetConsoleColor(ConsoleColor.Red, ConsoleColor.White); 
                        Console.WriteLine("Incorrect path, try again.");
                    }
                    else
                    {
                        //get the path of the .txt file of the same name
                        boneNamesTextPath = boneNamesPath.Remove(boneNamesPath.Length - "HashDB".Length, "HashDB".Length) + "txt";

                        //if it's sucessful, then break out of the loop
                        inBoneNamesPathLoop = false;
                    }
                }
            }
            else
            {
                boneNamesPath = preassign_boneNamesPath;
                boneNamesTextPath = preassign_boneNamesTextPath;
            }

            boneNames = new BoneNames();
            boneNames.ParseBoneNames(boneNamesPath, boneNamesTextPath, showSetupConsoleOutput);

            //----------------SETUP - TEX NAMES----------------
            ConsoleFunctions.SetConsoleColor(ConsoleColor.Blue, ConsoleColor.White); 
            Console.WriteLine("SETUP");
            ConsoleFunctions.SetConsoleColor(ConsoleColor.DarkGray, ConsoleColor.White); 
            Console.WriteLine("Enter the path of the TexNames.HashDB");

            //file path
            string texNamesPath = "";
            string texNamesTextPath = "";

            if(!usePreassignedPath)
            {
                //run a loop until the path is valid
                bool inTexNamesPathLoop = true;
                while (inTexNamesPathLoop)
                {
                    //get path from user
                    ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.White); 
                    texNamesPath = Console.ReadLine();

                    if (texNamesPath[0].Equals('"'))
                    {
                        texNamesPath = texNamesPath.Remove(0, 1);
                        texNamesPath = texNamesPath.Remove(texNamesPath.Length - 1, 1);
                    }

                    //check if the path is valid
                    if (File.Exists(texNamesPath) == false)
                    {
                        //notify the user and this loop will run again
                        ConsoleFunctions.SetConsoleColor(ConsoleColor.Red, ConsoleColor.White); 
                        Console.WriteLine("Incorrect path, try again.");
                    }
                    else
                    {
                        //get the path of the .txt file of the same name
                        texNamesTextPath = texNamesPath.Remove(texNamesPath.Length - "HashDB".Length, "HashDB".Length) + "txt";

                        //if it's sucessful, then break out of the loop
                        inTexNamesPathLoop = false;
                    }
                }
            }
            else
            {
                texNamesPath = preassign_texNamesPath;
                texNamesTextPath = preassign_texNamesTextPath;
            }

            texNames = new TexNames();
            texNames.ParseTexNames(texNamesPath, texNamesTextPath, showSetupConsoleOutput);

            ConsoleFunctions.SetConsoleColor(ConsoleColor.Green, ConsoleColor.White); 
            Console.WriteLine("SETUP COMPLETE");
            Console.ResetColor();

            //-----------------GET D3DMESH FOLDER PATH-----------------
            ConsoleFunctions.SetConsoleColor(ConsoleColor.DarkGray, ConsoleColor.White); 
            Console.WriteLine("Enter the folder path with the D3DMesh files.");

            //d3dmesh folder path (containing the path to the d3dmesh files to be converted)
            string d3dmeshFolderPath = "";

            if(!usePreassignedPath)
            {
                //run a loop until the path is valid
                bool inD3dmeshFolderPathoop = true;
                while (inD3dmeshFolderPathoop)
                {
                    //get path from user
                    ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.White); 
                    d3dmeshFolderPath = Console.ReadLine();

                    //check if the path is valid
                    if (Directory.Exists(d3dmeshFolderPath) == false)
                    {
                        //notify the user and this loop will run again
                        ConsoleFunctions.SetConsoleColor(ConsoleColor.Red, ConsoleColor.White); 
                        Console.WriteLine("Incorrect folder path, try again.");
                    }
                    else
                    {
                        //if it's sucessful, then break out of the loop
                        inD3dmeshFolderPathoop = false;
                    }
                }
            }
            else
            {
                d3dmeshFolderPath = preassign_d3dmeshPath;
            }

            //-----------------GET RESULT FOLDER PATH-----------------
            ConsoleFunctions.SetConsoleColor(ConsoleColor.DarkGray, ConsoleColor.White); 
            Console.WriteLine("Enter the resulting path where converted OBJ meshes will be stored.");

            //result folder path (will contain the converted textures)
            string resultFolderPath = "";

            if(!usePreassignedPath)
            {
                //run a loop until the path is valid
                bool inResultPathLoop = true;
                while (inResultPathLoop)
                {
                    //get path from user
                    ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.White); 
                    resultFolderPath = Console.ReadLine();

                    //check if the path is valid
                    if (Directory.Exists(resultFolderPath) == false)
                    {
                        //notify the user and this loop will run again
                        ConsoleFunctions.SetConsoleColor(ConsoleColor.Red, ConsoleColor.White); 
                        Console.WriteLine("Incorrect Result Path, try again.");
                    }
                    else
                    {
                        //if it's sucessful, then break out of the loop
                        inResultPathLoop = false;
                    }
                }
            }
            else
            {
                resultFolderPath = preassign_resultPath;
            }

            //-----------------START CONVERSION-----------------

            //notify the user we are starting
            ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Green); 
            Console.WriteLine("Conversion Starting...");

            //we got our paths, so lets begin
            Convert_D3DMESH_Bulk(d3dmeshFolderPath, resultFolderPath);

            //once the process is finished, it will come back here and we will notify the user that we are done

            ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Green); 
            Console.WriteLine("Conversion Finished.");
            Console.ResetColor();

            //wait for user input so the console doesn't just close out instantly and we can't see what we outputted.
            Console.ReadLine();
        }

        /// <summary>
        /// Begins the conversion process. Gathers the files found in the mesh folder path, filters them, and converts each one.
        /// </summary>
        /// <param name="texPath"></param>
        /// <param name="resultPath"></param>
        public static void Convert_D3DMESH_Bulk(string meshPath, string resultPath)
        {
            ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Yellow); 
            Console.WriteLine("Collecting Files..."); //notify the user we are collecting files

            //gather the files from the mesh folder path into an array
            List<string> meshes = new List<string>(Directory.GetFiles(meshPath));

            ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Yellow); 
            Console.WriteLine("Filtering Meshes..."); //notify the user we are filtering the array

            //filter the array so we only get .d3dtx files
            meshes = IOFunctions.FilterFiles(meshes, D3DMESH.fileExtension);

            //if no d3dmesh files were found, abort the program from going on any further (we don't have any files to convert!)
            if (meshes.Count < 1)
            {
                ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Red); 
                Console.WriteLine("No .d3dmesh files were found, aborting."); //notify the user we found x amount of d3dmesh files in the array
                Console.ResetColor();
                return;
            }

            ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Green); 
            Console.WriteLine("Found {0} Meshes.", meshes.Count.ToString()); //notify the user we found x amount of d3dmesh files in the array
            Console.WriteLine("Starting...");//notify the user we are starting

            //run a loop through each of the found textures and convert each one
            foreach (string mesh in meshes)
            {
                //build the path for the resulting file
                string meshFileName = Path.GetFileName(mesh); //get the file name of the file + extension
                string meshFileNameOnly = Path.GetFileNameWithoutExtension(mesh);
                string meshResultPath = resultPath + "/" + meshFileNameOnly + ".obj"; //add the file name to the resulting folder path, this is where our converted file will be placed

                ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.White); 
                Console.WriteLine("||||||||||||||||||||||||||||||||");
                ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Blue); 
                Console.WriteLine("Converting '{0}'...", meshFileName); //notify the user are converting 'x' file.
                Console.ResetColor();

                //runs the main method for converting the texture
                D3DMESH.ConvertMesh_FromD3DMESH_ToObj(meshFileName, mesh, meshResultPath, texNames, boneNames);

                ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.Green); 
                Console.WriteLine("Finished converting '{0}'...", meshFileName); //notify the user we finished converting 'x' file.
                ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.White); 
            }
        }
    }
}

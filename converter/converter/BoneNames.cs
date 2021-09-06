using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace converter
{
    /// <summary>
    /// A class that parses the data found in RTB's BoneNames.HashDB
    /// </summary>
    public class BoneNames
    {
        //the amount of bone hash entries in the file
        public int BoneHashNum;

        //a bone hash entry
        public struct BoneHash_Struct
        {
            public int BoneHash2;
            public int BoneHash1;
            public string BoneString;
        };

        //the list of bone hash entries in the file
        public List<BoneHash_Struct> BoneHash_array = new List<BoneHash_Struct>();

        /// <summary>
        /// Parses the BoneNames.HashDB file and its data. Uses also the .txt file.
        /// </summary>
        /// <param name="filePath"></param>
        /// <param name="filePathText"></param>
        /// <param name="showConsole"></param>
        public void ParseBoneNames(string filePath, string filePathText, bool showConsole = false)
        {
            //get our temp variables
            uint bytePointerLocation = 0; //where we are in the file
            byte[] fileBytes = File.ReadAllBytes(filePath); //read the byte data of the file
            List<string> boneNames = new List<string>(File.ReadAllLines(filePathText)); //read all of the text lines in the .txt file

            //---------------BoneHashNum---------------
            if (showConsole)
                Console.WriteLine("bytePointerLocation: '{0}'", bytePointerLocation);

            BoneHashNum = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);

            if (showConsole)
            {
                ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.White); 
                Console.WriteLine("BoneHashNum: '{0}'", BoneHashNum);
            }

            //---------------Bone Hash Entries---------------
            for (int i = 0; i < BoneHashNum; i++)
            {
                BoneHash_Struct boneHashEntry = new BoneHash_Struct();

                if (showConsole)
                    Console.WriteLine("Bone Hash Entry '{0}'", i);

                //---------------BoneHash2---------------
                if (showConsole)
                    Console.WriteLine("bytePointerLocation: '{0}'", bytePointerLocation);

                boneHashEntry.BoneHash2 = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);

                if (showConsole)
                    Console.WriteLine("BoneHash2: '{0}'", boneHashEntry.BoneHash2);

                //---------------BoneHash1---------------
                if (showConsole)
                    Console.WriteLine("bytePointerLocation: '{0}'", bytePointerLocation);

                boneHashEntry.BoneHash1 = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);

                if (showConsole)
                    Console.WriteLine("BoneHash1: '{0}'", boneHashEntry.BoneHash1);

                //---------------BoneString---------------
                if (showConsole)
                    Console.WriteLine("bytePointerLocation: '{0}'", bytePointerLocation);

                boneHashEntry.BoneString = boneNames[i];
                bytePointerLocation += (uint)boneNames[i].Length + 1;

                if(showConsole)
                {
                    Console.WriteLine("BoneString: '{0}'", boneHashEntry.BoneString);
                    Console.WriteLine("BoneString Length: '{0}'", boneHashEntry.BoneString.Length);
                }

                //add the final entry
                BoneHash_array.Add(boneHashEntry);
            }
        }
    }
}

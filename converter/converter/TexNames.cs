using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace converter
{
    public class TexNames
    {
        public int TexHashNum;

        public struct TexHash_Struct
        {
            public int TexHash2;
            public int TexHash1;
            public string TexString;
        };

        public List<TexHash_Struct> TexHash_array = new List<TexHash_Struct>();

        public void ParseTexNames(string filePath, string filePathText, bool showConsole = false)
        {
            uint bytePointerLocation = 0;
            byte[] fileBytes = File.ReadAllBytes(filePath);
            List<string> texNames = new List<string>(File.ReadAllLines(filePathText));

            //---------------TexHashNum---------------
            if (showConsole)
                Console.WriteLine("bytePointerLocation: '{0}'", bytePointerLocation);

            TexHashNum = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);

            if (showConsole)
            {
                ConsoleFunctions.SetConsoleColor(ConsoleColor.Black, ConsoleColor.White); 
                Console.WriteLine("TexHashNum: '{0}'", TexHashNum);
            }

            //---------------Texture Hash Entries---------------
            for (int i = 0; i < TexHashNum; i++)
            {
                TexHash_Struct texHashEntry = new TexHash_Struct();

                if (showConsole)
                    Console.WriteLine("Texture Hash Entry '{0}'", i);

                //---------------TexHash2---------------
                if (showConsole)
                    Console.WriteLine("bytePointerLocation: '{0}'", bytePointerLocation);

                texHashEntry.TexHash2 = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);

                if (showConsole)
                    Console.WriteLine("TexHash2: '{0}'", texHashEntry.TexHash2);

                //---------------TexHash1---------------
                if (showConsole)
                    Console.WriteLine("bytePointerLocation: '{0}'", bytePointerLocation);

                texHashEntry.TexHash1 = ByteFunctions.ReadInt(fileBytes, ref bytePointerLocation);

                if (showConsole)
                    Console.WriteLine("TexHash1: '{0}'", texHashEntry.TexHash1);

                //---------------TexString---------------
                if (showConsole)
                    Console.WriteLine("bytePointerLocation: '{0}'", bytePointerLocation);

                texHashEntry.TexString = texNames[i];
                bytePointerLocation += (uint)texNames[i].Length + 1;

                if (showConsole)
                {
                    Console.WriteLine("TexString: '{0}'", texHashEntry.TexString);
                    Console.WriteLine("TexString Length: '{0}'", texHashEntry.TexString.Length);
                }

                //add the final entry
                TexHash_array.Add(texHashEntry);
            }
        }
    }
}

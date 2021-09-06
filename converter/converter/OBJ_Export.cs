using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace converter
{
    public static class OBJ_Export
    {
        public static void WriteOBJ_File(string path, List<Vertex_Data> verticies, List<UV_Data> uvs, List<Normal_Data> normals, List<Face_Data> faces)
        {
            List<string> fileLines = new List<string>();

            fileLines.Add("# Custom OBJ Exporter");
            fileLines.Add(string.Format("# Vertex Count {0}", verticies.Count));
            fileLines.Add(string.Format("# UV Count {0}", uvs.Count));
            fileLines.Add(string.Format("# Normals Count {0}", normals.Count));
            fileLines.Add(string.Format("# Faces Count {0}", faces.Count));
            fileLines.Add("");

            //write verticies
            foreach (Vertex_Data vertex in verticies)
            {
                string newLine = string.Format("v {0} {1} {2}", vertex.x, vertex.y, vertex.z);
                fileLines.Add(newLine);
            }

            //write uvs
            foreach (UV_Data uv in uvs)
            {
                string newLine = string.Format("vt {0} {1} {2}", uv.u, uv.v, uv.a);
                fileLines.Add(newLine);
            }

            //write normals
            foreach (Normal_Data normal in normals)
            {
                string newLine = string.Format("vn {0} {1} {2}", normal.x, normal.y, normal.z);
                fileLines.Add(newLine);
            }

            //fileLines.Add("");
            //fileLines.Add("s off"); //smooth shading off
            //fileLines.Add("g mesh"); //mesh group name

            //write faces
            int index = 0;
            string faceLine = "f ";

            foreach (Face_Data face in faces)
            {
                if(index > 2)
                {
                    fileLines.Add(faceLine);
                    faceLine = "f ";
                    index = 0;
                }

                faceLine += face.a + "/";
                faceLine += face.b + "/";
                faceLine += face.c + " ";

                index++;
            }



            //write the final file to the disk
            File.WriteAllLines(path, fileLines);
        }
    }
}

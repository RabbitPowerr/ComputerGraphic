using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace Visualizer{
    class Biniary{
        public static int X, Y, Z;
        public static short[] colormask;
        public Biniary() {}

        public void readBIN(string path){
            if (File.Exists(path)){
                BinaryReader reader = new BinaryReader(File.Open(path, FileMode.Open));
                X = reader.ReadInt32();
                Y = reader.ReadInt32();
                Z = reader.ReadInt32();
                int size = X * Y * Z;
                colormask = new short[size];
                for (int i = 0; i < size; ++i)
                    colormask[i] = reader.ReadInt16();
                
            }
        }
    }
}

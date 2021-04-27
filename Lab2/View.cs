using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using OpenTK;
using OpenTK.Graphics.OpenGL;
using System.Drawing;
using System.Drawing.Imaging;

namespace Visualizer{
    class View{
        public int minimum = 0;
        public int widht = 2000;
        Bitmap image;
        int VBO = 0;

        public void SetupView(int width, int height){
            GL.ShadeModel(ShadingModel.Smooth);
            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadIdentity();
            GL.Ortho(0, Biniary.X, 0, Biniary.Y, -1, 1);
            GL.Viewport(0, 0, width, height);
        }

        public void DrawQuads(int layerNumber){
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.Begin(BeginMode.Quads);
            for (int x_coord = 0; x_coord < Biniary.X - 1; x_coord++)
                for (int y_coord = 0; y_coord < Biniary.Y - 1; y_coord++){
                    short value;
                    value = Biniary.colormask[x_coord + y_coord * Biniary.X
                                        + layerNumber * Biniary.X * Biniary.Y];
                    GL.Color3(TransferFunction(value));
                    GL.Vertex2(x_coord, y_coord);
                    value = Biniary.colormask[x_coord + (y_coord + 1) * Biniary.X
                                        + layerNumber * Biniary.X * Biniary.Y];
                    GL.Color3(TransferFunction(value));
                    GL.Vertex2(x_coord, y_coord + 1);
                    value = Biniary.colormask[x_coord + 1 + (y_coord + 1) * Biniary.X
                                        + layerNumber * Biniary.X * Biniary.Y];
                    GL.Color3(TransferFunction(value));
                    GL.Vertex2(x_coord + 1, y_coord + 1);
                    value = Biniary.colormask[x_coord + 1 + y_coord * Biniary.X
                                        + layerNumber * Biniary.X * Biniary.Y];
                    GL.Color3(TransferFunction(value));
                    GL.Vertex2(x_coord + 1, y_coord);
                }
            GL.End();
        }

        int clamp(int value, int min, int max){
            return Math.Min(max, Math.Max(min, value));
        }

        Color TransferFunction(short value){
            int min = minimum;
            int max = minimum + widht;
            int newVal = clamp((value - min) * 255 / (max - min), 1, 255);
            return Color.FromArgb(255, newVal, newVal, newVal);
        }

       
        public void Load2DTexture(){
            GL.BindTexture(TextureTarget.Texture2D, VBO);
            BitmapData data = image.LockBits(
                new System.Drawing.Rectangle(0, 0, image.Width, image.Height),
                ImageLockMode.ReadOnly,
                System.Drawing.Imaging.PixelFormat.Format32bppArgb);

            GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgba,
                data.Width, data.Height, 0, OpenTK.Graphics.OpenGL.PixelFormat.Bgra,
                PixelType.UnsignedByte, data.Scan0);

            image.UnlockBits(data);

            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter,
                (int)TextureMinFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter,
                (int)TextureMagFilter.Linear);

            ErrorCode Er = GL.GetError();
            string str = Er.ToString();
        }

        public void generateTextureImage(int layerNumber){
            image = new Bitmap(Biniary.X, Biniary.Y);
            for (int i = 0; i < Biniary.X; ++i)
                for (int j = 0; j < Biniary.Y; ++j)
                {
                    int pixelNumber = i + j * Biniary.X + layerNumber * Biniary.X * Biniary.Y;
                    image.SetPixel(i, j, TransferFunction(Biniary.colormask[pixelNumber]));
                }
        }

        public void DrawTexture(){
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.Enable(EnableCap.Texture2D);
            GL.BindTexture(TextureTarget.Texture2D, VBO);
            GL.Begin(BeginMode.Quads);
            GL.Color3(Color.White);
            GL.TexCoord2(0f, 0f); 
            GL.Vertex2(0, 0);
            GL.TexCoord2(0f, 1f);
            GL.Vertex2(0, Biniary.Y);
            GL.TexCoord2(1f, 1f);
            GL.Vertex2(Biniary.X, Biniary.Y);
            GL.TexCoord2(1f, 0f);
            GL.Vertex2(Biniary.X, 0);
            GL.End();
            GL.Disable(EnableCap.Texture2D);
        }
    }
}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Visualizer
{
    public partial class Form1 : Form
    {
        Biniary bin = new Biniary();
        View view = new View();
        bool loaded = false;
        int nLayer = 0;
        int count;
        public Form1()
        {
            InitializeComponent();
        }
        private void label3_Click(object sender, EventArgs e){}

        private void открытьToolStripMenuItem_Click(object sender, EventArgs e){
            OpenFileDialog dialog = new OpenFileDialog();
            if (dialog.ShowDialog() == DialogResult.OK){
                string str = dialog.FileName;
                bin.readBIN(str);
                view.SetupView(glControl1.Width, glControl1.Height);
                trackBar1.Maximum = Biniary.Z - 1;
                loaded = true;
                glControl1.Invalidate();
            }
        }

        bool needReload = false;

      
        private void glControl1_Paint(object sender, PaintEventArgs e){
            if (loaded){
                if (radioButton1.Checked)
                    view.DrawQuads(nLayer);
                else{
                    if (needReload){
                        view.generateTextureImage(nLayer);
                        view.Load2DTexture();
                        needReload = false;
                    }
                    view.DrawTexture();
                }
                glControl1.SwapBuffers();
            }
        }

        private void trackBar1_Scroll(object sender, EventArgs e) {
            nLayer = trackBar1.Value;
            needReload = true;
        }

        void Application_Idle(object sender, EventArgs e){
            while (glControl1.IsIdle){
                displayFPS();
                glControl1.Invalidate();
            }
        }

        private void Form1_Load(object sender, EventArgs e){
            Application.Idle += Application_Idle;
        }

        
        DateTime NextFPSUpdate = DateTime.Now.AddSeconds(1);
        void displayFPS(){
            if (DateTime.Now >= NextFPSUpdate)
            {
                this.Text = String.Format("CT Visualizer (fps={0})", count);
                NextFPSUpdate = DateTime.Now.AddSeconds(1);
                count = 0;
            }
            count++;
        }

        private void trackBar3_Scroll(object sender, EventArgs e) {
            view.widht = trackBar3.Value;
            needReload = true;
        }

        private void trackBar2_Scroll(object sender, EventArgs e){
            view.minimum = trackBar2.Value;
            needReload = true;
        }

    }
}

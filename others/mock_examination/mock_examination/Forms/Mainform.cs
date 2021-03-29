using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace mock_examination
{
    public partial class Mainform : Form
    {
        public Mainform()
        {
            InitializeComponent();

            Helper.SQLiteHelper.SetConnectionString("mock_examination.db");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            (new Forms.QuestionsManagement()).ShowDialog();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            (new Forms.TraversingQuestions()).ShowDialog();
        }
    }
}

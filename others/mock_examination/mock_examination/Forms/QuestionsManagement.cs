using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace mock_examination.Forms
{
    public partial class QuestionsManagement : Form
    {
        private Dictionary<int, Structs.QuestionInfo> question_dictionary_;
        private int dgv_question_table_mouse_select_index;
        public QuestionsManagement()
        {
            InitializeComponent();

            question_dictionary_ = null;
            dgv_question_table_mouse_select_index = -1;

            show_questions();
        }

        private void show_questions()
        {
            clear_question_info();
            dgv_question_table.Rows.Clear();
            if (string.IsNullOrWhiteSpace(txt_box_search_key.Text) == true)
            {
                question_dictionary_ = Structs.QuestionInfo.LoadDictionaryFormDB(
                    Helper.SQLiteHelper.ExecuteQuery(
                        @"SELECT id, question, options, answers, level, file, is_do, is_use, others FROM question_info;"));
            }
            else
            {
                question_dictionary_ = Structs.QuestionInfo.LoadDictionaryFormDB(
                    Helper.SQLiteHelper.ExecuteQuery(
                        string.Format(
                            "SELECT id, question, options, answers, level, file, is_do, is_use, others FROM question_info WHERE id LIKE '%{0}%' OR question LIKE '%{1}%';",
                        txt_box_search_key.Text,
                        txt_box_search_key.Text)));
            }

            if (question_dictionary_.Count > 0)
            {
                foreach (var item in question_dictionary_)
                {
                    dgv_question_table.Rows.Add(
                        item.Value.ID,
                        item.Value.Question,
                        item.Value.AnswersText,
                        item.Value.IsUse,
                        item.Value.IsDoText);
                }

                dgv_question_table.ClearSelection();
                dgv_question_table.CurrentCell = dgv_question_table.Rows[0].Cells[0];
                dgv_question_table.Rows[0].Selected = true;

                show_question_info(Convert.ToInt32(dgv_question_table.Rows[0].Cells[0].Value.ToString()));
            }
        }
        private void show_question_info(int _id)
        {
            Structs.QuestionInfo info = question_dictionary_[_id];
            label_question.Text = info.Question;
            list_box_options.Items.Clear();
            foreach (var item in info.OptionDictionary)
            {
                list_box_options.Items.Add(string.Format("{0}、{1}", item.Key, item.Value));
            }
            label_answers.Text = info.AnswersText;
        }
        private void clear_question_info()
        {
            label_question.Text = string.Empty;
            list_box_options.Items.Clear();
            label_answers.Text = string.Empty;
        }
        private void bt_search_Click(object sender, EventArgs e)
        {
            show_questions();
        }
        private void dgv_question_table_CellMouseDown(object sender, DataGridViewCellMouseEventArgs e)
        {
            int mouse_x = MousePosition.X;
            int mouse_y = MousePosition.Y;
            if (e.RowIndex > -1)
            {
                int info_id = Convert.ToInt32(dgv_question_table.Rows[e.RowIndex].Cells[0].Value.ToString());
                if (e.Button == MouseButtons.Left && e.Clicks == 1)
                {
                    show_question_info(info_id);
                    dgv_question_table.ClearSelection();
                    dgv_question_table.CurrentCell = dgv_question_table.Rows[e.RowIndex].Cells[0];
                    dgv_question_table.Rows[e.RowIndex].Selected = true;
                }
                else if (e.Button == MouseButtons.Right && e.Clicks == 1)
                {
                    dgv_question_table_mouse_select_index = e.RowIndex;
                    ctx_menu_strip_dgv_qt.Show(new Point(mouse_x, mouse_y));
                }
            }
        }
        private void 删除ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (dgv_question_table_mouse_select_index != -1)
            {
                int info_id = Convert.ToInt32(dgv_question_table.Rows[dgv_question_table_mouse_select_index].Cells[0].Value.ToString());

                if (1 == Helper.SQLiteHelper.ExecuteNonQuery(question_dictionary_[info_id].MakeDeleteSQL()))
                {
                    question_dictionary_.Remove(info_id);
                    dgv_question_table.Rows.RemoveAt(dgv_question_table_mouse_select_index);
                    dgv_question_table_mouse_select_index = -1;
                }
                else
                {
                    MessageBox.Show("删除失败");
                }
            }
        }
        private void 导入试题ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog open_fd = new OpenFileDialog();
            open_fd.Filter = "Microsoft Excel files(*.xls)|*.xls;*.xlsx";
            open_fd.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.DesktopDirectory);
            open_fd.RestoreDirectory = true;
            open_fd.FilterIndex = 1;
            open_fd.AddExtension = true;
            open_fd.CheckFileExists = true;
            open_fd.CheckPathExists = true;
            open_fd.ShowHelp = true;//是否显示帮助按钮
            if (open_fd.ShowDialog() == DialogResult.OK)
            {
                int index = 0;
                Helper.SQLiteHelper.ExecuteNonQuery("DELETE FROM question_info;");
                DataTable dt = Helper.ExcelHelper.ExcelToDataTable(open_fd.FileName);
                foreach (DataRow dr in dt.Rows)
                {
                    Structs.QuestionInfo info = new Structs.QuestionInfo();
                    info.LoadFromExcel(dr);
                    if (1 == Helper.SQLiteHelper.ExecuteNonQuery(info.MakeInsertSQL()))
                    {
                        //Console.WriteLine("INFO:{0}:\t{1}", info.ID, info.Question);
                    }
                    else
                    {
                        Console.WriteLine("ERROR:{0}:\t{1}", info.ID, info.Question);
                    }
                    index++;
                    label_answers.Text = string.Format("已导入 {0}/{1}", index, dt.Rows.Count);
                    Application.DoEvents();
                }

                show_questions();
            }
        }
        private void 重置题库ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Helper.SQLiteHelper.ExecuteNonQuery("UPDATE question_info SET is_do = 0, is_use = 1, others = '';");

            show_questions();
        }
        private void 保存修改ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach (DataGridViewRow item in dgv_question_table.Rows)
            {
                int info_id = Convert.ToInt32(item.Cells[0].Value.ToString());
                if (question_dictionary_[info_id].IsUse != Convert.ToBoolean(item.Cells[3].Value))
                {
                    question_dictionary_[info_id].IsUse = Convert.ToBoolean(item.Cells[3].Value);
                    Helper.SQLiteHelper.ExecuteNonQuery(question_dictionary_[info_id].MakeUpdateSQL());
                }
            }

            MessageBox.Show("保存成功");
        }
        private void 清空题库ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Helper.SQLiteHelper.ExecuteNonQuery("DELETE FROM question_info;");

            show_questions();
        }
    }
}

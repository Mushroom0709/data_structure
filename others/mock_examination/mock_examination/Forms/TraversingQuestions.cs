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
    public partial class TraversingQuestions : Form
    {
        private Dictionary<int, Structs.QuestionInfo> question_dictionary_;
        private int dgv_question_table_select_index;
        public TraversingQuestions()
        {
            InitializeComponent();
            dgv_question_table_select_index = -1;
            load_questions();
        }

        private bool load_questions()
        {
            question_dictionary_ = Structs.QuestionInfo.LoadDictionaryFormDB(
                    Helper.SQLiteHelper.ExecuteQuery(
                        @"SELECT id, question, options, answers, level, file, is_do, is_use, others FROM question_info WHERE is_use = 1;"));

            if (question_dictionary_.Count <= 0)
                return false;

            bool is_frist = true;
            foreach (var item in question_dictionary_)
            {
                int row_index = dgv_question_table.Rows.Add(item.Value.ID, item.Value.Question, item.Value.IsDoText);
                dgv_question_table.Rows[row_index].Cells[2].Style.BackColor = item.Value.IsDoColor;

                if (item.Value.IsDo == 0 && is_frist == true)
                {
                    is_frist = false;
                    dgv_question_table_select_index = row_index;
                }
            }

            show_question();

            return true;
        }
        private void show_question()
        {
            if (dgv_question_table_select_index > -1)
            {
                dgv_question_table.ClearSelection();
                dgv_question_table.CurrentCell = dgv_question_table.Rows[dgv_question_table_select_index].Cells[0];
                dgv_question_table.Rows[dgv_question_table_select_index].Selected = true;

                int question_id = Convert.ToInt32(dgv_question_table.Rows[dgv_question_table_select_index].Cells[0].Value);

                label_question.Text = question_dictionary_[question_id].Question;
                label_answers.Text = "请先尝试做题";
                label_answers.ForeColor = Color.Black;

                dgv_options_table.Rows.Clear();

                foreach (var item in question_dictionary_[question_id].OptionDictionary)
                {
                    dgv_options_table.Rows.Add(false,item.Key, item.Value);
                }

                if (question_dictionary_[question_id].IsDo == 2)
                {
                    List<string> error_opts = Helper.Common.Json2Array(question_dictionary_[question_id].Others);

                    foreach (DataGridViewRow dgvr in dgv_options_table.Rows)
                    {
                        if (true == error_opts.Contains(dgvr.Cells[1].Value.ToString()))
                        {
                            dgvr.Cells[1].Value = true;
                        }
                    }
                    error_opts.Clear();
                    check_question(question_id, ref error_opts);
                }
            }
        }
        private bool check_question(int _question_id,ref List<string> _opts)
        {
            bool res = true;
            foreach (DataGridViewRow dgvr in dgv_options_table.Rows)
            {
                if (((bool)dgvr.Cells[0].Value) == true)
                {
                    _opts.Add(dgvr.Cells[1].Value.ToString());
                    if (true == question_dictionary_[_question_id].AnswerArray.Contains(dgvr.Cells[1].Value.ToString()))
                    {
                        dgvr.DefaultCellStyle.BackColor = Color.Green;
                    }
                    else
                    {
                        dgvr.DefaultCellStyle.BackColor = Color.Red;
                        res = false;
                    }
                }
                else
                {
                    if (true == question_dictionary_[_question_id].AnswerArray.Contains(dgvr.Cells[1].Value.ToString()))
                    {
                        dgvr.DefaultCellStyle.BackColor = Color.Red;
                        res = false;
                    }
                    else
                    {
                        dgvr.DefaultCellStyle.BackColor = Color.White;
                    }
                }
            }

            dgv_options_table.ClearSelection();

            return res;
        }
        private bool process_check_question()
        {
            bool res = true;
            List<string> error_opts = new List<string>();
            int question_id = Convert.ToInt32(dgv_question_table.Rows[dgv_question_table_select_index].Cells[0].Value);

            if (check_question(question_id, ref error_opts) == true)
            {
                label_answers.Text = string.Format("回答正确，答案:{0}", question_dictionary_[question_id].AnswersText);
                label_answers.ForeColor = Color.GreenYellow;

                question_dictionary_[question_id].IsDo = 1;
                question_dictionary_[question_id].Others = "";
            }
            else
            {
                label_answers.Text = string.Format("回答错误，正确答案:{0}", question_dictionary_[question_id].AnswersText);
                label_answers.ForeColor = Color.Red;
                res = false;

                question_dictionary_[question_id].IsDo = 2;
                question_dictionary_[question_id].Others = Helper.Common.Object2Json(error_opts);
            }

            dgv_question_table.Rows[dgv_question_table_select_index].Cells[2].Value = question_dictionary_[question_id].IsDoText;
            dgv_question_table.Rows[dgv_question_table_select_index].Cells[2].Style.BackColor = question_dictionary_[question_id].IsDoColor;
            Helper.SQLiteHelper.ExecuteNonQuery(question_dictionary_[question_id].MakeUpdateSQL());

            return res;
        }
        private void bt_check_Click(object sender, EventArgs e)
        {
            process_check_question();
        }
        private void bt_last_Click(object sender, EventArgs e)
        {
            if (dgv_question_table.Rows[dgv_question_table_select_index].Cells[2].Value.ToString() == "未做" && process_check_question() == false)
            {
                return;
            }

            if (dgv_question_table_select_index > 0)
            {
                dgv_question_table_select_index--;
                show_question();
            }
        }
        private void bt_next_Click(object sender, EventArgs e)
        {
            if (dgv_question_table.Rows[dgv_question_table_select_index].Cells[2].Value.ToString() == "未做" && process_check_question() == false)
            {
                return;
            }

            if (dgv_question_table_select_index < dgv_question_table.Rows.Count - 1)
            {
                dgv_question_table_select_index++;
                show_question();
            }
        }
        private void dgv_question_table_CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (e.RowIndex > -1 && e.Clicks == 1)
            {
                dgv_question_table_select_index = e.RowIndex;

                show_question();
            }
        }
        private void dgv_options_table_CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (e.RowIndex > -1 && e.Clicks == 1)
            {
                dgv_options_table.Rows[e.RowIndex].Cells[0].Value = !Convert.ToBoolean(dgv_options_table.Rows[e.RowIndex].Cells[0].Value);
            }
        }
    }
}

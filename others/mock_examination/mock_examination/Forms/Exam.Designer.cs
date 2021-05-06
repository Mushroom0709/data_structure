namespace mock_examination.Forms
{
    partial class Exam
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            this.label_question = new System.Windows.Forms.Label();
            this.dgv_question_table = new System.Windows.Forms.DataGridView();
            this.Column1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dgv_options_table = new System.Windows.Forms.DataGridView();
            this.dataGridViewTextBoxColumn1 = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.dataGridViewTextBoxColumn2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.bt_check = new System.Windows.Forms.Button();
            this.bt_next = new System.Windows.Forms.Button();
            this.bt_last = new System.Windows.Forms.Button();
            this.label_answers = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dgv_question_table)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgv_options_table)).BeginInit();
            this.SuspendLayout();
            // 
            // label_question
            // 
            this.label_question.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label_question.Font = new System.Drawing.Font("宋体", 18F);
            this.label_question.Location = new System.Drawing.Point(633, 12);
            this.label_question.Name = "label_question";
            this.label_question.Size = new System.Drawing.Size(579, 289);
            this.label_question.TabIndex = 15;
            this.label_question.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // dgv_question_table
            // 
            this.dgv_question_table.AllowUserToAddRows = false;
            this.dgv_question_table.AllowUserToDeleteRows = false;
            this.dgv_question_table.BackgroundColor = System.Drawing.Color.White;
            this.dgv_question_table.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgv_question_table.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Column1,
            this.Column2,
            this.Column4});
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.Color.LightSteelBlue;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.dgv_question_table.DefaultCellStyle = dataGridViewCellStyle1;
            this.dgv_question_table.GridColor = System.Drawing.Color.Black;
            this.dgv_question_table.Location = new System.Drawing.Point(12, 12);
            this.dgv_question_table.Name = "dgv_question_table";
            this.dgv_question_table.RowHeadersVisible = false;
            this.dgv_question_table.RowHeadersWidth = 62;
            this.dgv_question_table.RowTemplate.Height = 30;
            this.dgv_question_table.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dgv_question_table.Size = new System.Drawing.Size(615, 686);
            this.dgv_question_table.TabIndex = 14;
            // 
            // Column1
            // 
            this.Column1.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.Column1.FillWeight = 10F;
            this.Column1.HeaderText = "编号";
            this.Column1.MinimumWidth = 8;
            this.Column1.Name = "Column1";
            this.Column1.ReadOnly = true;
            // 
            // Column2
            // 
            this.Column2.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.Column2.FillWeight = 80F;
            this.Column2.HeaderText = "题目";
            this.Column2.MinimumWidth = 8;
            this.Column2.Name = "Column2";
            this.Column2.ReadOnly = true;
            // 
            // Column4
            // 
            this.Column4.FillWeight = 10F;
            this.Column4.HeaderText = "状态";
            this.Column4.MinimumWidth = 8;
            this.Column4.Name = "Column4";
            this.Column4.ReadOnly = true;
            this.Column4.Width = 150;
            // 
            // dgv_options_table
            // 
            this.dgv_options_table.AllowUserToAddRows = false;
            this.dgv_options_table.AllowUserToDeleteRows = false;
            this.dgv_options_table.BackgroundColor = System.Drawing.Color.White;
            this.dgv_options_table.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgv_options_table.ColumnHeadersVisible = false;
            this.dgv_options_table.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dataGridViewTextBoxColumn1,
            this.dataGridViewTextBoxColumn2,
            this.dataGridViewTextBoxColumn3});
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.Color.LightSteelBlue;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.dgv_options_table.DefaultCellStyle = dataGridViewCellStyle2;
            this.dgv_options_table.GridColor = System.Drawing.Color.Black;
            this.dgv_options_table.Location = new System.Drawing.Point(633, 304);
            this.dgv_options_table.Name = "dgv_options_table";
            this.dgv_options_table.RowHeadersVisible = false;
            this.dgv_options_table.RowHeadersWidth = 62;
            this.dgv_options_table.RowTemplate.Height = 30;
            this.dgv_options_table.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dgv_options_table.Size = new System.Drawing.Size(579, 226);
            this.dgv_options_table.TabIndex = 16;
            // 
            // dataGridViewTextBoxColumn1
            // 
            this.dataGridViewTextBoxColumn1.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dataGridViewTextBoxColumn1.FillWeight = 10F;
            this.dataGridViewTextBoxColumn1.HeaderText = "选中";
            this.dataGridViewTextBoxColumn1.MinimumWidth = 8;
            this.dataGridViewTextBoxColumn1.Name = "dataGridViewTextBoxColumn1";
            this.dataGridViewTextBoxColumn1.ReadOnly = true;
            this.dataGridViewTextBoxColumn1.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridViewTextBoxColumn1.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            // 
            // dataGridViewTextBoxColumn2
            // 
            this.dataGridViewTextBoxColumn2.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dataGridViewTextBoxColumn2.FillWeight = 10F;
            this.dataGridViewTextBoxColumn2.HeaderText = "标识";
            this.dataGridViewTextBoxColumn2.MinimumWidth = 8;
            this.dataGridViewTextBoxColumn2.Name = "dataGridViewTextBoxColumn2";
            this.dataGridViewTextBoxColumn2.ReadOnly = true;
            // 
            // dataGridViewTextBoxColumn3
            // 
            this.dataGridViewTextBoxColumn3.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dataGridViewTextBoxColumn3.FillWeight = 80F;
            this.dataGridViewTextBoxColumn3.HeaderText = "内容";
            this.dataGridViewTextBoxColumn3.MinimumWidth = 8;
            this.dataGridViewTextBoxColumn3.Name = "dataGridViewTextBoxColumn3";
            this.dataGridViewTextBoxColumn3.ReadOnly = true;
            // 
            // bt_check
            // 
            this.bt_check.Location = new System.Drawing.Point(741, 646);
            this.bt_check.Name = "bt_check";
            this.bt_check.Size = new System.Drawing.Size(363, 52);
            this.bt_check.TabIndex = 20;
            this.bt_check.Text = "检查";
            this.bt_check.UseVisualStyleBackColor = true;
            // 
            // bt_next
            // 
            this.bt_next.Location = new System.Drawing.Point(1110, 646);
            this.bt_next.Name = "bt_next";
            this.bt_next.Size = new System.Drawing.Size(102, 52);
            this.bt_next.TabIndex = 19;
            this.bt_next.Text = "下一题";
            this.bt_next.UseVisualStyleBackColor = true;
            // 
            // bt_last
            // 
            this.bt_last.Location = new System.Drawing.Point(633, 646);
            this.bt_last.Name = "bt_last";
            this.bt_last.Size = new System.Drawing.Size(102, 52);
            this.bt_last.TabIndex = 18;
            this.bt_last.Text = "上一题";
            this.bt_last.UseVisualStyleBackColor = true;
            // 
            // label_answers
            // 
            this.label_answers.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label_answers.Font = new System.Drawing.Font("宋体", 18F);
            this.label_answers.Location = new System.Drawing.Point(633, 533);
            this.label_answers.Name = "label_answers";
            this.label_answers.Size = new System.Drawing.Size(579, 110);
            this.label_answers.TabIndex = 17;
            this.label_answers.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Exam
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1690, 1131);
            this.Controls.Add(this.label_question);
            this.Controls.Add(this.dgv_question_table);
            this.Controls.Add(this.dgv_options_table);
            this.Controls.Add(this.bt_check);
            this.Controls.Add(this.bt_next);
            this.Controls.Add(this.bt_last);
            this.Controls.Add(this.label_answers);
            this.Name = "Exam";
            this.Text = "Exam";
            ((System.ComponentModel.ISupportInitialize)(this.dgv_question_table)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgv_options_table)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label label_question;
        private System.Windows.Forms.DataGridView dgv_question_table;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column1;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column2;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column4;
        private System.Windows.Forms.DataGridView dgv_options_table;
        private System.Windows.Forms.DataGridViewCheckBoxColumn dataGridViewTextBoxColumn1;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn2;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn3;
        private System.Windows.Forms.Button bt_check;
        private System.Windows.Forms.Button bt_next;
        private System.Windows.Forms.Button bt_last;
        private System.Windows.Forms.Label label_answers;
    }
}
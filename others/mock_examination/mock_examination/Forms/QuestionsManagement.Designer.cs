namespace mock_examination.Forms
{
    partial class QuestionsManagement
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
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            this.txt_box_search_key = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.bt_search = new System.Windows.Forms.Button();
            this.dgv_question_table = new System.Windows.Forms.DataGridView();
            this.Column1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column5 = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.Column3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ctx_menu_strip_dgv_qt = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.删除ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label_answers = new System.Windows.Forms.Label();
            this.list_box_options = new System.Windows.Forms.ListBox();
            this.label_question = new System.Windows.Forms.Label();
            this.menu_strip_qm = new System.Windows.Forms.MenuStrip();
            this.导入试题ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.保存修改ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.重置题库ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.清空题库ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)(this.dgv_question_table)).BeginInit();
            this.ctx_menu_strip_dgv_qt.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.menu_strip_qm.SuspendLayout();
            this.SuspendLayout();
            // 
            // txt_box_search_key
            // 
            this.txt_box_search_key.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txt_box_search_key.Location = new System.Drawing.Point(105, 41);
            this.txt_box_search_key.Name = "txt_box_search_key";
            this.txt_box_search_key.Size = new System.Drawing.Size(1440, 28);
            this.txt_box_search_key.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label1.Location = new System.Drawing.Point(12, 41);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(87, 28);
            this.label1.TabIndex = 1;
            this.label1.Text = "关键词";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // bt_search
            // 
            this.bt_search.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bt_search.Location = new System.Drawing.Point(1551, 41);
            this.bt_search.Name = "bt_search";
            this.bt_search.Size = new System.Drawing.Size(96, 28);
            this.bt_search.TabIndex = 2;
            this.bt_search.Text = "搜索";
            this.bt_search.UseVisualStyleBackColor = true;
            this.bt_search.Click += new System.EventHandler(this.bt_search_Click);
            // 
            // dgv_question_table
            // 
            this.dgv_question_table.AllowUserToAddRows = false;
            this.dgv_question_table.AllowUserToDeleteRows = false;
            this.dgv_question_table.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.dgv_question_table.BackgroundColor = System.Drawing.Color.White;
            this.dgv_question_table.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgv_question_table.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Column1,
            this.Column2,
            this.Column4,
            this.Column5,
            this.Column3});
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.Color.LightSteelBlue;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.dgv_question_table.DefaultCellStyle = dataGridViewCellStyle2;
            this.dgv_question_table.GridColor = System.Drawing.Color.Black;
            this.dgv_question_table.Location = new System.Drawing.Point(12, 75);
            this.dgv_question_table.Name = "dgv_question_table";
            this.dgv_question_table.RowHeadersVisible = false;
            this.dgv_question_table.RowHeadersWidth = 62;
            this.dgv_question_table.RowTemplate.Height = 30;
            this.dgv_question_table.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dgv_question_table.Size = new System.Drawing.Size(1635, 561);
            this.dgv_question_table.TabIndex = 6;
            this.dgv_question_table.CellMouseDown += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.dgv_question_table_CellMouseDown);
            // 
            // Column1
            // 
            this.Column1.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.Column1.FillWeight = 5F;
            this.Column1.HeaderText = "编号";
            this.Column1.MinimumWidth = 8;
            this.Column1.Name = "Column1";
            this.Column1.ReadOnly = true;
            // 
            // Column2
            // 
            this.Column2.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.Column2.FillWeight = 60F;
            this.Column2.HeaderText = "题目";
            this.Column2.MinimumWidth = 8;
            this.Column2.Name = "Column2";
            this.Column2.ReadOnly = true;
            // 
            // Column4
            // 
            this.Column4.FillWeight = 15F;
            this.Column4.HeaderText = "答案";
            this.Column4.MinimumWidth = 8;
            this.Column4.Name = "Column4";
            this.Column4.ReadOnly = true;
            this.Column4.Width = 150;
            // 
            // Column5
            // 
            this.Column5.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.Column5.FillWeight = 10F;
            this.Column5.HeaderText = "是否启用";
            this.Column5.MinimumWidth = 8;
            this.Column5.Name = "Column5";
            this.Column5.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.Column5.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            // 
            // Column3
            // 
            this.Column3.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.Column3.FillWeight = 10F;
            this.Column3.HeaderText = "刷题状态";
            this.Column3.MinimumWidth = 8;
            this.Column3.Name = "Column3";
            this.Column3.ReadOnly = true;
            // 
            // ctx_menu_strip_dgv_qt
            // 
            this.ctx_menu_strip_dgv_qt.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.ctx_menu_strip_dgv_qt.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.删除ToolStripMenuItem});
            this.ctx_menu_strip_dgv_qt.Name = "ctx_menu_strip_dgv_qt";
            this.ctx_menu_strip_dgv_qt.Size = new System.Drawing.Size(117, 34);
            // 
            // 删除ToolStripMenuItem
            // 
            this.删除ToolStripMenuItem.Name = "删除ToolStripMenuItem";
            this.删除ToolStripMenuItem.Size = new System.Drawing.Size(116, 30);
            this.删除ToolStripMenuItem.Text = "删除";
            this.删除ToolStripMenuItem.Click += new System.EventHandler(this.删除ToolStripMenuItem_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.label_answers);
            this.groupBox1.Controls.Add(this.list_box_options);
            this.groupBox1.Controls.Add(this.label_question);
            this.groupBox1.Location = new System.Drawing.Point(12, 642);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(1635, 369);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "详情";
            // 
            // label_answers
            // 
            this.label_answers.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label_answers.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label_answers.Font = new System.Drawing.Font("宋体", 18F);
            this.label_answers.Location = new System.Drawing.Point(6, 302);
            this.label_answers.Name = "label_answers";
            this.label_answers.Size = new System.Drawing.Size(1617, 64);
            this.label_answers.TabIndex = 8;
            this.label_answers.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // list_box_options
            // 
            this.list_box_options.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.list_box_options.Font = new System.Drawing.Font("宋体", 14F);
            this.list_box_options.FormattingEnabled = true;
            this.list_box_options.ItemHeight = 28;
            this.list_box_options.Location = new System.Drawing.Point(6, 99);
            this.list_box_options.Name = "list_box_options";
            this.list_box_options.Size = new System.Drawing.Size(1617, 200);
            this.list_box_options.TabIndex = 7;
            // 
            // label_question
            // 
            this.label_question.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label_question.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label_question.Font = new System.Drawing.Font("宋体", 18F);
            this.label_question.Location = new System.Drawing.Point(6, 24);
            this.label_question.Name = "label_question";
            this.label_question.Size = new System.Drawing.Size(1617, 72);
            this.label_question.TabIndex = 6;
            this.label_question.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // menu_strip_qm
            // 
            this.menu_strip_qm.GripMargin = new System.Windows.Forms.Padding(2, 2, 0, 2);
            this.menu_strip_qm.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.menu_strip_qm.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.导入试题ToolStripMenuItem,
            this.保存修改ToolStripMenuItem,
            this.重置题库ToolStripMenuItem,
            this.清空题库ToolStripMenuItem});
            this.menu_strip_qm.Location = new System.Drawing.Point(0, 0);
            this.menu_strip_qm.Name = "menu_strip_qm";
            this.menu_strip_qm.Size = new System.Drawing.Size(1659, 32);
            this.menu_strip_qm.TabIndex = 9;
            this.menu_strip_qm.Text = "menuStrip1";
            // 
            // 导入试题ToolStripMenuItem
            // 
            this.导入试题ToolStripMenuItem.Name = "导入试题ToolStripMenuItem";
            this.导入试题ToolStripMenuItem.Size = new System.Drawing.Size(98, 28);
            this.导入试题ToolStripMenuItem.Text = "导入试题";
            this.导入试题ToolStripMenuItem.Click += new System.EventHandler(this.导入试题ToolStripMenuItem_Click);
            // 
            // 保存修改ToolStripMenuItem
            // 
            this.保存修改ToolStripMenuItem.Name = "保存修改ToolStripMenuItem";
            this.保存修改ToolStripMenuItem.Size = new System.Drawing.Size(98, 28);
            this.保存修改ToolStripMenuItem.Text = "保存修改";
            this.保存修改ToolStripMenuItem.Click += new System.EventHandler(this.保存修改ToolStripMenuItem_Click);
            // 
            // 重置题库ToolStripMenuItem
            // 
            this.重置题库ToolStripMenuItem.Name = "重置题库ToolStripMenuItem";
            this.重置题库ToolStripMenuItem.Size = new System.Drawing.Size(98, 28);
            this.重置题库ToolStripMenuItem.Text = "重置题库";
            this.重置题库ToolStripMenuItem.Click += new System.EventHandler(this.重置题库ToolStripMenuItem_Click);
            // 
            // 清空题库ToolStripMenuItem
            // 
            this.清空题库ToolStripMenuItem.Name = "清空题库ToolStripMenuItem";
            this.清空题库ToolStripMenuItem.Size = new System.Drawing.Size(98, 28);
            this.清空题库ToolStripMenuItem.Text = "清空题库";
            this.清空题库ToolStripMenuItem.Click += new System.EventHandler(this.清空题库ToolStripMenuItem_Click);
            // 
            // QuestionsManagement
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1659, 1028);
            this.Controls.Add(this.menu_strip_qm);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.dgv_question_table);
            this.Controls.Add(this.bt_search);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txt_box_search_key);
            this.MainMenuStrip = this.menu_strip_qm;
            this.Name = "QuestionsManagement";
            this.Text = "题库管理";
            ((System.ComponentModel.ISupportInitialize)(this.dgv_question_table)).EndInit();
            this.ctx_menu_strip_dgv_qt.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.menu_strip_qm.ResumeLayout(false);
            this.menu_strip_qm.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txt_box_search_key;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button bt_search;
        private System.Windows.Forms.DataGridView dgv_question_table;
        private System.Windows.Forms.ContextMenuStrip ctx_menu_strip_dgv_qt;
        private System.Windows.Forms.ToolStripMenuItem 删除ToolStripMenuItem;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label_answers;
        private System.Windows.Forms.ListBox list_box_options;
        private System.Windows.Forms.Label label_question;
        private System.Windows.Forms.MenuStrip menu_strip_qm;
        private System.Windows.Forms.ToolStripMenuItem 导入试题ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 保存修改ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 重置题库ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 清空题库ToolStripMenuItem;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column1;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column2;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column4;
        private System.Windows.Forms.DataGridViewCheckBoxColumn Column5;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column3;
    }
}
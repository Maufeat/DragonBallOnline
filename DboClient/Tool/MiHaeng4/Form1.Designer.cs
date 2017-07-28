namespace MiHaeng4
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다.
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.listXLS = new System.Windows.Forms.ListView();
            this.btAddXLS = new System.Windows.Forms.Button();
            this.openXLS = new System.Windows.Forms.OpenFileDialog();
            this.btConvertNoneTagXML = new System.Windows.Forms.Button();
            this.btConvertTagXML = new System.Windows.Forms.Button();
            this.pgbCurrent = new System.Windows.Forms.ProgressBar();
            this.lbCurrent = new System.Windows.Forms.Label();
            this.openTextTable = new System.Windows.Forms.OpenFileDialog();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btTagXLS = new System.Windows.Forms.Button();
            this.btSelectAll = new System.Windows.Forms.Button();
            this.btDelete = new System.Windows.Forms.Button();
            this.btClear = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.btDataFile = new System.Windows.Forms.Button();
            this.textDataFile = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btConvertRDF = new System.Windows.Forms.Button();
            this.btSelectXML = new System.Windows.Forms.Button();
            this.listXML = new System.Windows.Forms.ListView();
            this.btRemoveXML = new System.Windows.Forms.Button();
            this.btMergeRDF = new System.Windows.Forms.Button();
            this.btClearXML = new System.Windows.Forms.Button();
            this.btMergeXML = new System.Windows.Forms.Button();
            this.lbInfoXML = new System.Windows.Forms.Label();
            this.pgbXML = new System.Windows.Forms.ProgressBar();
            this.btAddXML = new System.Windows.Forms.Button();
            this.openXML = new System.Windows.Forms.OpenFileDialog();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // listXLS
            // 
            this.listXLS.BackColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.listXLS.CheckBoxes = true;
            this.listXLS.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            this.listXLS.Location = new System.Drawing.Point(20, 30);
            this.listXLS.MultiSelect = false;
            this.listXLS.Name = "listXLS";
            this.listXLS.Size = new System.Drawing.Size(425, 125);
            this.listXLS.TabIndex = 0;
            this.listXLS.UseCompatibleStateImageBehavior = false;
            this.listXLS.View = System.Windows.Forms.View.SmallIcon;
            // 
            // btAddXLS
            // 
            this.btAddXLS.Location = new System.Drawing.Point(20, 164);
            this.btAddXLS.Name = "btAddXLS";
            this.btAddXLS.Size = new System.Drawing.Size(101, 25);
            this.btAddXLS.TabIndex = 1;
            this.btAddXLS.Text = "Add XLS";
            this.btAddXLS.UseVisualStyleBackColor = true;
            this.btAddXLS.Click += new System.EventHandler(this.btAddXLS_Click);
            // 
            // openXLS
            // 
            this.openXLS.Filter = "Excel Files|*.xls";
            this.openXLS.Multiselect = true;
            this.openXLS.RestoreDirectory = true;
            // 
            // btConvertNoneTagXML
            // 
            this.btConvertNoneTagXML.Location = new System.Drawing.Point(9, 182);
            this.btConvertNoneTagXML.Name = "btConvertNoneTagXML";
            this.btConvertNoneTagXML.Size = new System.Drawing.Size(146, 25);
            this.btConvertNoneTagXML.TabIndex = 2;
            this.btConvertNoneTagXML.Text = "Convert NoneTag XML";
            this.btConvertNoneTagXML.UseVisualStyleBackColor = true;
            this.btConvertNoneTagXML.Click += new System.EventHandler(this.btConvertNoneTagXML_Click);
            // 
            // btConvertTagXML
            // 
            this.btConvertTagXML.Location = new System.Drawing.Point(161, 182);
            this.btConvertTagXML.Name = "btConvertTagXML";
            this.btConvertTagXML.Size = new System.Drawing.Size(131, 25);
            this.btConvertTagXML.TabIndex = 3;
            this.btConvertTagXML.Text = "Convert Tag XML";
            this.btConvertTagXML.UseVisualStyleBackColor = true;
            this.btConvertTagXML.Click += new System.EventHandler(this.btConvertTagXML_Click);
            // 
            // pgbCurrent
            // 
            this.pgbCurrent.Location = new System.Drawing.Point(10, 213);
            this.pgbCurrent.Name = "pgbCurrent";
            this.pgbCurrent.Size = new System.Drawing.Size(423, 25);
            this.pgbCurrent.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.pgbCurrent.TabIndex = 4;
            // 
            // lbCurrent
            // 
            this.lbCurrent.AutoEllipsis = true;
            this.lbCurrent.CausesValidation = false;
            this.lbCurrent.ForeColor = System.Drawing.Color.Cyan;
            this.lbCurrent.Location = new System.Drawing.Point(11, 242);
            this.lbCurrent.Name = "lbCurrent";
            this.lbCurrent.Size = new System.Drawing.Size(423, 16);
            this.lbCurrent.TabIndex = 5;
            this.lbCurrent.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // openTextTable
            // 
            this.openTextTable.DefaultExt = "xls";
            this.openTextTable.FileName = "Table_Text_All_Data.xls";
            this.openTextTable.Filter = "Excel Files|*.xls";
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.Transparent;
            this.groupBox1.Controls.Add(this.btTagXLS);
            this.groupBox1.Controls.Add(this.btSelectAll);
            this.groupBox1.Controls.Add(this.btDelete);
            this.groupBox1.Controls.Add(this.btClear);
            this.groupBox1.Controls.Add(this.pgbCurrent);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.btConvertTagXML);
            this.groupBox1.Controls.Add(this.btDataFile);
            this.groupBox1.Controls.Add(this.btConvertNoneTagXML);
            this.groupBox1.Controls.Add(this.textDataFile);
            this.groupBox1.Controls.Add(this.lbCurrent);
            this.groupBox1.Font = new System.Drawing.Font("Gulim", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.groupBox1.ForeColor = System.Drawing.SystemColors.ControlText;
            this.groupBox1.Location = new System.Drawing.Point(10, 13);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(440, 323);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Convert XLS -> XML";
            // 
            // btTagXLS
            // 
            this.btTagXLS.Location = new System.Drawing.Point(298, 182);
            this.btTagXLS.Name = "btTagXLS";
            this.btTagXLS.Size = new System.Drawing.Size(135, 25);
            this.btTagXLS.TabIndex = 12;
            this.btTagXLS.Text = "Convert Tag XLS";
            this.btTagXLS.UseVisualStyleBackColor = true;
            this.btTagXLS.Click += new System.EventHandler(this.btTagXLS_Click);
            // 
            // btSelectAll
            // 
            this.btSelectAll.Location = new System.Drawing.Point(116, 150);
            this.btSelectAll.Name = "btSelectAll";
            this.btSelectAll.Size = new System.Drawing.Size(115, 25);
            this.btSelectAll.TabIndex = 11;
            this.btSelectAll.Text = "Select/Deselect All";
            this.btSelectAll.UseVisualStyleBackColor = true;
            this.btSelectAll.Click += new System.EventHandler(this.btSelectAll_Click);
            // 
            // btDelete
            // 
            this.btDelete.Location = new System.Drawing.Point(331, 151);
            this.btDelete.Name = "btDelete";
            this.btDelete.Size = new System.Drawing.Size(103, 25);
            this.btDelete.TabIndex = 10;
            this.btDelete.Text = "Remove Select";
            this.btDelete.UseVisualStyleBackColor = true;
            this.btDelete.Click += new System.EventHandler(this.btDelete_Click);
            // 
            // btClear
            // 
            this.btClear.Location = new System.Drawing.Point(236, 151);
            this.btClear.Name = "btClear";
            this.btClear.Size = new System.Drawing.Size(90, 25);
            this.btClear.TabIndex = 9;
            this.btClear.Text = "Clear All";
            this.btClear.UseVisualStyleBackColor = true;
            this.btClear.Click += new System.EventHandler(this.btClear_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Gulim", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.label1.ForeColor = System.Drawing.Color.DeepPink;
            this.label1.Location = new System.Drawing.Point(8, 269);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(161, 12);
            this.label1.TabIndex = 8;
            this.label1.Text = "Text All Data Table File";
            // 
            // btDataFile
            // 
            this.btDataFile.Location = new System.Drawing.Point(410, 283);
            this.btDataFile.Name = "btDataFile";
            this.btDataFile.Size = new System.Drawing.Size(25, 25);
            this.btDataFile.TabIndex = 7;
            this.btDataFile.Text = "...";
            this.btDataFile.UseVisualStyleBackColor = true;
            this.btDataFile.Click += new System.EventHandler(this.btDataFile_Click);
            // 
            // textDataFile
            // 
            this.textDataFile.Location = new System.Drawing.Point(10, 285);
            this.textDataFile.Name = "textDataFile";
            this.textDataFile.Size = new System.Drawing.Size(395, 21);
            this.textDataFile.TabIndex = 6;
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.Color.Transparent;
            this.groupBox2.Controls.Add(this.button2);
            this.groupBox2.Controls.Add(this.button1);
            this.groupBox2.Controls.Add(this.btConvertRDF);
            this.groupBox2.Controls.Add(this.btSelectXML);
            this.groupBox2.Controls.Add(this.listXML);
            this.groupBox2.Controls.Add(this.btRemoveXML);
            this.groupBox2.Controls.Add(this.btMergeRDF);
            this.groupBox2.Controls.Add(this.btClearXML);
            this.groupBox2.Controls.Add(this.btMergeXML);
            this.groupBox2.Controls.Add(this.lbInfoXML);
            this.groupBox2.Controls.Add(this.pgbXML);
            this.groupBox2.Controls.Add(this.btAddXML);
            this.groupBox2.Location = new System.Drawing.Point(10, 343);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(440, 282);
            this.groupBox2.TabIndex = 7;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Convert XML -> rdf";
            // 
            // btConvertRDF
            // 
            this.btConvertRDF.Location = new System.Drawing.Point(298, 184);
            this.btConvertRDF.Name = "btConvertRDF";
            this.btConvertRDF.Size = new System.Drawing.Size(135, 25);
            this.btConvertRDF.TabIndex = 20;
            this.btConvertRDF.Text = "Convert RDF";
            this.btConvertRDF.UseVisualStyleBackColor = true;
            this.btConvertRDF.Click += new System.EventHandler(this.btConvertRDF_Click);
            // 
            // btSelectXML
            // 
            this.btSelectXML.Location = new System.Drawing.Point(116, 154);
            this.btSelectXML.Name = "btSelectXML";
            this.btSelectXML.Size = new System.Drawing.Size(115, 25);
            this.btSelectXML.TabIndex = 19;
            this.btSelectXML.Text = "Select/Deselect All";
            this.btSelectXML.UseVisualStyleBackColor = true;
            this.btSelectXML.Click += new System.EventHandler(this.btSelectXML_Click);
            // 
            // listXML
            // 
            this.listXML.BackColor = System.Drawing.Color.Pink;
            this.listXML.CheckBoxes = true;
            this.listXML.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            this.listXML.Location = new System.Drawing.Point(9, 22);
            this.listXML.MultiSelect = false;
            this.listXML.Name = "listXML";
            this.listXML.Size = new System.Drawing.Size(425, 125);
            this.listXML.TabIndex = 1;
            this.listXML.UseCompatibleStateImageBehavior = false;
            this.listXML.View = System.Windows.Forms.View.SmallIcon;
            // 
            // btRemoveXML
            // 
            this.btRemoveXML.Location = new System.Drawing.Point(331, 154);
            this.btRemoveXML.Name = "btRemoveXML";
            this.btRemoveXML.Size = new System.Drawing.Size(103, 25);
            this.btRemoveXML.TabIndex = 18;
            this.btRemoveXML.Text = "Remove Select";
            this.btRemoveXML.UseVisualStyleBackColor = true;
            this.btRemoveXML.Click += new System.EventHandler(this.btRemoveXML_Click);
            // 
            // btMergeRDF
            // 
            this.btMergeRDF.Location = new System.Drawing.Point(161, 185);
            this.btMergeRDF.Name = "btMergeRDF";
            this.btMergeRDF.Size = new System.Drawing.Size(131, 25);
            this.btMergeRDF.TabIndex = 14;
            this.btMergeRDF.Text = "Merge to RDF";
            this.btMergeRDF.UseVisualStyleBackColor = true;
            this.btMergeRDF.Click += new System.EventHandler(this.btMergeRDF_Click);
            // 
            // btClearXML
            // 
            this.btClearXML.Location = new System.Drawing.Point(236, 154);
            this.btClearXML.Name = "btClearXML";
            this.btClearXML.Size = new System.Drawing.Size(90, 25);
            this.btClearXML.TabIndex = 17;
            this.btClearXML.Text = "Clear All";
            this.btClearXML.UseVisualStyleBackColor = true;
            this.btClearXML.Click += new System.EventHandler(this.btClearXML_Click);
            // 
            // btMergeXML
            // 
            this.btMergeXML.Location = new System.Drawing.Point(9, 185);
            this.btMergeXML.Name = "btMergeXML";
            this.btMergeXML.Size = new System.Drawing.Size(146, 25);
            this.btMergeXML.TabIndex = 13;
            this.btMergeXML.Text = "Merge to XML";
            this.btMergeXML.UseVisualStyleBackColor = true;
            this.btMergeXML.Click += new System.EventHandler(this.btMergeXML_Click);
            // 
            // lbInfoXML
            // 
            this.lbInfoXML.AutoEllipsis = true;
            this.lbInfoXML.CausesValidation = false;
            this.lbInfoXML.ForeColor = System.Drawing.Color.Cyan;
            this.lbInfoXML.Location = new System.Drawing.Point(10, 245);
            this.lbInfoXML.Name = "lbInfoXML";
            this.lbInfoXML.Size = new System.Drawing.Size(423, 16);
            this.lbInfoXML.TabIndex = 16;
            this.lbInfoXML.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // pgbXML
            // 
            this.pgbXML.Location = new System.Drawing.Point(6, 251);
            this.pgbXML.Name = "pgbXML";
            this.pgbXML.Size = new System.Drawing.Size(423, 25);
            this.pgbXML.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.pgbXML.TabIndex = 15;
            // 
            // btAddXML
            // 
            this.btAddXML.Location = new System.Drawing.Point(9, 154);
            this.btAddXML.Name = "btAddXML";
            this.btAddXML.Size = new System.Drawing.Size(101, 25);
            this.btAddXML.TabIndex = 12;
            this.btAddXML.Text = "Add XML";
            this.btAddXML.UseVisualStyleBackColor = true;
            this.btAddXML.Click += new System.EventHandler(this.btAddXML_Click);
            // 
            // openXML
            // 
            this.openXML.Filter = "XML Files|*.xml";
            this.openXML.Multiselect = true;
            this.openXML.RestoreDirectory = true;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(13, 216);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(142, 29);
            this.button1.TabIndex = 21;
            this.button1.Text = "Open RDF";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(161, 216);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(131, 29);
            this.button2.TabIndex = 22;
            this.button2.Text = "ConvertFromRDF";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.ClientSize = new System.Drawing.Size(457, 636);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.btAddXLS);
            this.Controls.Add(this.listXLS);
            this.Controls.Add(this.groupBox1);
            this.DoubleBuffered = true;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.Form1_Paint);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListView listXLS;
        private System.Windows.Forms.Button btAddXLS;
        private System.Windows.Forms.OpenFileDialog openXLS;
        private System.Windows.Forms.Button btConvertNoneTagXML;
        private System.Windows.Forms.Button btConvertTagXML;
        private System.Windows.Forms.ProgressBar pgbCurrent;
        private System.Windows.Forms.Label lbCurrent;
        private System.Windows.Forms.OpenFileDialog openTextTable;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btDataFile;
        private System.Windows.Forms.TextBox textDataFile;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btClear;
        private System.Windows.Forms.Button btDelete;
        private System.Windows.Forms.Button btSelectAll;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button btSelectXML;
        private System.Windows.Forms.ListView listXML;
        private System.Windows.Forms.Button btRemoveXML;
        private System.Windows.Forms.Button btMergeRDF;
        private System.Windows.Forms.Button btClearXML;
        private System.Windows.Forms.Button btMergeXML;
        private System.Windows.Forms.Label lbInfoXML;
        private System.Windows.Forms.ProgressBar pgbXML;
        private System.Windows.Forms.Button btAddXML;
        private System.Windows.Forms.Button btConvertRDF;
        private System.Windows.Forms.OpenFileDialog openXML;
        private System.Windows.Forms.Button btTagXLS;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
    }
}


namespace Dibuixos.Dibuixos.Browser
{
    partial class frmBrowser
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
            this.toolTipSamples = new System.Windows.Forms.ToolTip(this.components);
            this.treeViewSamples = new System.Windows.Forms.TreeView();
            this.contextMenuStripSamples = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.runSampleToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.viewDescriptionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.viewSourceToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.imageListSampleCategories = new System.Windows.Forms.ImageList(this.components);
            this.contextMenuStripOutput = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.copyToolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.copyToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.contextMenuStripSource = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.copyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.contextMenuStripDescription = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabSource = new System.Windows.Forms.TabPage();
            this.tabOutput = new System.Windows.Forms.TabPage();
            this.contextMenuStripSamples.SuspendLayout();
            this.contextMenuStripOutput.SuspendLayout();
            this.contextMenuStripSource.SuspendLayout();
            this.contextMenuStripDescription.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.SuspendLayout();
            // 
            // treeViewSamples
            // 
            this.treeViewSamples.ContextMenuStrip = this.contextMenuStripSamples;
            this.treeViewSamples.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeViewSamples.FullRowSelect = true;
            this.treeViewSamples.HideSelection = false;
            this.treeViewSamples.HotTracking = true;
            this.treeViewSamples.ImageIndex = 0;
            this.treeViewSamples.ImageList = this.imageListSampleCategories;
            this.treeViewSamples.Indent = 32;
            this.treeViewSamples.Location = new System.Drawing.Point(0, 0);
            this.treeViewSamples.Name = "treeViewSamples";
            this.treeViewSamples.SelectedImageIndex = 0;
            this.treeViewSamples.Size = new System.Drawing.Size(256, 411);
            this.treeViewSamples.TabIndex = 0;
            this.toolTipSamples.SetToolTip(this.treeViewSamples, "Right-click a sample for more options.");
            // 
            // contextMenuStripSamples
            // 
            this.contextMenuStripSamples.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.runSampleToolStripMenuItem,
            this.toolStripMenuItem1,
            this.viewDescriptionToolStripMenuItem,
            this.viewSourceToolStripMenuItem});
            this.contextMenuStripSamples.Name = "contextMenuStripSamples";
            this.contextMenuStripSamples.Size = new System.Drawing.Size(170, 76);
            // 
            // runSampleToolStripMenuItem
            // 
            this.runSampleToolStripMenuItem.Name = "runSampleToolStripMenuItem";
            this.runSampleToolStripMenuItem.Size = new System.Drawing.Size(169, 22);
            this.runSampleToolStripMenuItem.Text = "&Run Sample";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(166, 6);
            // 
            // viewDescriptionToolStripMenuItem
            // 
            this.viewDescriptionToolStripMenuItem.Name = "viewDescriptionToolStripMenuItem";
            this.viewDescriptionToolStripMenuItem.Size = new System.Drawing.Size(169, 22);
            this.viewDescriptionToolStripMenuItem.Text = "View Description";
            // 
            // viewSourceToolStripMenuItem
            // 
            this.viewSourceToolStripMenuItem.Name = "viewSourceToolStripMenuItem";
            this.viewSourceToolStripMenuItem.Size = new System.Drawing.Size(169, 22);
            this.viewSourceToolStripMenuItem.Text = "View Source Code";
            // 
            // imageListSampleCategories
            // 
            this.imageListSampleCategories.ColorDepth = System.Windows.Forms.ColorDepth.Depth32Bit;
            this.imageListSampleCategories.ImageSize = new System.Drawing.Size(35, 35);
            this.imageListSampleCategories.TransparentColor = System.Drawing.Color.Transparent;
            // 
            // contextMenuStripOutput
            // 
            this.contextMenuStripOutput.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.copyToolStripMenuItem2});
            this.contextMenuStripOutput.Name = "contextMenuStripOutput";
            this.contextMenuStripOutput.Size = new System.Drawing.Size(103, 26);
            // 
            // copyToolStripMenuItem2
            // 
            this.copyToolStripMenuItem2.Name = "copyToolStripMenuItem2";
            this.copyToolStripMenuItem2.Size = new System.Drawing.Size(102, 22);
            this.copyToolStripMenuItem2.Text = "&Copy";
            // 
            // copyToolStripMenuItem1
            // 
            this.copyToolStripMenuItem1.Name = "copyToolStripMenuItem1";
            this.copyToolStripMenuItem1.Size = new System.Drawing.Size(102, 22);
            this.copyToolStripMenuItem1.Text = "&Copy";
            // 
            // contextMenuStripSource
            // 
            this.contextMenuStripSource.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.copyToolStripMenuItem1});
            this.contextMenuStripSource.Name = "contextMenuStripSource";
            this.contextMenuStripSource.Size = new System.Drawing.Size(103, 26);
            // 
            // copyToolStripMenuItem
            // 
            this.copyToolStripMenuItem.Name = "copyToolStripMenuItem";
            this.copyToolStripMenuItem.Size = new System.Drawing.Size(102, 22);
            this.copyToolStripMenuItem.Text = "&Copy";
            // 
            // contextMenuStripDescription
            // 
            this.contextMenuStripDescription.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.copyToolStripMenuItem});
            this.contextMenuStripDescription.Name = "contextMenuStripDescription";
            this.contextMenuStripDescription.Size = new System.Drawing.Size(103, 26);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.treeViewSamples);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.tabControl1);
            this.splitContainer1.Size = new System.Drawing.Size(769, 411);
            this.splitContainer1.SplitterDistance = 256;
            this.splitContainer1.TabIndex = 4;
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabSource);
            this.tabControl1.Controls.Add(this.tabOutput);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(509, 411);
            this.tabControl1.TabIndex = 0;
            // 
            // tabSource
            // 
            this.tabSource.Location = new System.Drawing.Point(4, 22);
            this.tabSource.Name = "tabSource";
            this.tabSource.Padding = new System.Windows.Forms.Padding(3);
            this.tabSource.Size = new System.Drawing.Size(501, 385);
            this.tabSource.TabIndex = 0;
            this.tabSource.Text = "Source";
            this.tabSource.UseVisualStyleBackColor = true;
            // 
            // tabOutput
            // 
            this.tabOutput.Location = new System.Drawing.Point(4, 22);
            this.tabOutput.Name = "tabOutput";
            this.tabOutput.Padding = new System.Windows.Forms.Padding(3);
            this.tabOutput.Size = new System.Drawing.Size(501, 385);
            this.tabOutput.TabIndex = 1;
            this.tabOutput.Text = "Output";
            this.tabOutput.UseVisualStyleBackColor = true;
            // 
            // frmBrowser
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(769, 411);
            this.Controls.Add(this.splitContainer1);
            this.Name = "frmBrowser";
            this.Text = "Dibuixos - mathematical-drawings";
            this.contextMenuStripSamples.ResumeLayout(false);
            this.contextMenuStripOutput.ResumeLayout(false);
            this.contextMenuStripSource.ResumeLayout(false);
            this.contextMenuStripDescription.ResumeLayout(false);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.tabControl1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ToolTip toolTipSamples;
        private System.Windows.Forms.TreeView treeViewSamples;
        private System.Windows.Forms.ContextMenuStrip contextMenuStripSamples;
        private System.Windows.Forms.ToolStripMenuItem runSampleToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem viewDescriptionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem viewSourceToolStripMenuItem;
        private System.Windows.Forms.ImageList imageListSampleCategories;
        private System.Windows.Forms.ContextMenuStrip contextMenuStripOutput;
        private System.Windows.Forms.ToolStripMenuItem copyToolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem copyToolStripMenuItem1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStripSource;
        private System.Windows.Forms.ToolStripMenuItem copyToolStripMenuItem;
        private System.Windows.Forms.ContextMenuStrip contextMenuStripDescription;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabSource;
        private System.Windows.Forms.TabPage tabOutput;
    }
}
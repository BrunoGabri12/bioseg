#pragma once
#include "imageClass.h"

namespace BioSeg {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Sumário para MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Adicione o código do construtor aqui
			//
		}

	protected:
		/// <summary>
		/// Limpar os recursos que estão sendo usados.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::Label^ label2;

	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::RadioButton^ rb_pasta;
	private: System::Windows::Forms::RadioButton^ rb_img;

	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::RadioButton^ rb_fluoresceina;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::RadioButton^ rb_transp;
	private: System::Windows::Forms::RadioButton^ rb_rosa;
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
	private: System::Windows::Forms::Button^ ok_bt;
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog2;










	private:
		/// <summary>
		/// Variável de designer necessária.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necessário para suporte ao Designer - não modifique 
		/// o conteúdo deste método com o editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->rb_pasta = (gcnew System::Windows::Forms::RadioButton());
			this->rb_img = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->rb_fluoresceina = (gcnew System::Windows::Forms::RadioButton());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->rb_transp = (gcnew System::Windows::Forms::RadioButton());
			this->rb_rosa = (gcnew System::Windows::Forms::RadioButton());
			this->ok_bt = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog2 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 27.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(135, 44);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(151, 50);
			this->label1->TabIndex = 0;
			this->label1->Text = L"BioSeg";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(64, 111);
			this->label2->Name = L"label2";
			this->label2->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label2->Size = System::Drawing::Size(311, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Ferramenta para segmentação de Biofilme em próteses dentárias";
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->textBox2);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->rb_pasta);
			this->groupBox1->Controls->Add(this->rb_img);
			this->groupBox1->Location = System::Drawing::Point(2, 142);
			this->groupBox1->Margin = System::Windows::Forms::Padding(2);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(2);
			this->groupBox1->Size = System::Drawing::Size(436, 137);
			this->groupBox1->TabIndex = 11;
			this->groupBox1->TabStop = false;
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox2->Location = System::Drawing::Point(7, 103);
			this->textBox2->Margin = System::Windows::Forms::Padding(2);
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(389, 23);
			this->textBox2->TabIndex = 10;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(4, 14);
			this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(227, 17);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Selecione o que deseja processar:";
			// 
			// rb_pasta
			// 
			this->rb_pasta->AutoSize = true;
			this->rb_pasta->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rb_pasta->Location = System::Drawing::Point(8, 74);
			this->rb_pasta->Margin = System::Windows::Forms::Padding(2);
			this->rb_pasta->Name = L"rb_pasta";
			this->rb_pasta->Size = System::Drawing::Size(171, 21);
			this->rb_pasta->TabIndex = 5;
			this->rb_pasta->Text = L"Pasta (várias imagens)";
			this->rb_pasta->UseVisualStyleBackColor = true;
			this->rb_pasta->CheckedChanged += gcnew System::EventHandler(this, &MyForm::rb_pasta_CheckedChanged);
			// 
			// rb_img
			// 
			this->rb_img->AutoSize = true;
			this->rb_img->Checked = true;
			this->rb_img->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rb_img->Location = System::Drawing::Point(7, 40);
			this->rb_img->Margin = System::Windows::Forms::Padding(2);
			this->rb_img->Name = L"rb_img";
			this->rb_img->Size = System::Drawing::Size(220, 21);
			this->rb_img->TabIndex = 3;
			this->rb_img->TabStop = true;
			this->rb_img->Text = L"Imagem (apenas uma imagem)";
			this->rb_img->UseVisualStyleBackColor = true;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->rb_fluoresceina);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->rb_transp);
			this->groupBox2->Controls->Add(this->rb_rosa);
			this->groupBox2->Location = System::Drawing::Point(2, 283);
			this->groupBox2->Margin = System::Windows::Forms::Padding(2);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(2);
			this->groupBox2->Size = System::Drawing::Size(436, 93);
			this->groupBox2->TabIndex = 12;
			this->groupBox2->TabStop = false;
			// 
			// rb_fluoresceina
			// 
			this->rb_fluoresceina->AutoSize = true;
			this->rb_fluoresceina->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rb_fluoresceina->Location = System::Drawing::Point(189, 36);
			this->rb_fluoresceina->Margin = System::Windows::Forms::Padding(2);
			this->rb_fluoresceina->Name = L"rb_fluoresceina";
			this->rb_fluoresceina->Size = System::Drawing::Size(107, 21);
			this->rb_fluoresceina->TabIndex = 6;
			this->rb_fluoresceina->Text = L"Flouresceína";
			this->rb_fluoresceina->UseVisualStyleBackColor = true;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(4, 14);
			this->label4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(185, 17);
			this->label4->TabIndex = 4;
			this->label4->Text = L"Selecione o tipo de prótese:";
			// 
			// rb_transp
			// 
			this->rb_transp->AutoSize = true;
			this->rb_transp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rb_transp->Location = System::Drawing::Point(4, 59);
			this->rb_transp->Margin = System::Windows::Forms::Padding(2);
			this->rb_transp->Name = L"rb_transp";
			this->rb_transp->Size = System::Drawing::Size(112, 21);
			this->rb_transp->TabIndex = 5;
			this->rb_transp->Text = L"Transparente";
			this->rb_transp->UseVisualStyleBackColor = true;
			// 
			// rb_rosa
			// 
			this->rb_rosa->AutoSize = true;
			this->rb_rosa->Checked = true;
			this->rb_rosa->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rb_rosa->Location = System::Drawing::Point(4, 36);
			this->rb_rosa->Margin = System::Windows::Forms::Padding(2);
			this->rb_rosa->Name = L"rb_rosa";
			this->rb_rosa->Size = System::Drawing::Size(59, 21);
			this->rb_rosa->TabIndex = 3;
			this->rb_rosa->TabStop = true;
			this->rb_rosa->Text = L"Rosa";
			this->rb_rosa->UseVisualStyleBackColor = true;
			// 
			// ok_bt
			// 
			this->ok_bt->BackColor = System::Drawing::Color::ForestGreen;
			this->ok_bt->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->ok_bt->Location = System::Drawing::Point(144, 394);
			this->ok_bt->Name = L"ok_bt";
			this->ok_bt->Size = System::Drawing::Size(123, 36);
			this->ok_bt->TabIndex = 13;
			this->ok_bt->Text = L"Processar Dados";
			this->ok_bt->UseVisualStyleBackColor = false;
			this->ok_bt->Click += gcnew System::EventHandler(this, &MyForm::ok_bt_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(442, 442);
			this->Controls->Add(this->ok_bt);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"BioSeg";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


private: System::Void openFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
}
	   int runApplication(String^ path, Boolean justOneImage);
 
	   processingImg::imageClass methodOfSegmentation(processingImg::imageClass image);


private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
}

	  

private: System::Void ok_bt_Click(System::Object^ sender, System::EventArgs^ e) {

	String^ path;

	if (this->rb_pasta->Checked) {
		if (folderBrowserDialog2->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			//MessageBox::Show(folderBrowserDialog1->SelectedPath);
			path = folderBrowserDialog2->SelectedPath;
			//MessageBox::Show(Caminho);
			this->textBox2->Text = path;
			runApplication(path,true);
		}
	}
	else {
		openFileDialog1->Filter = "Image Files (JPG,PNG,GIF)|*.JPG;*.PNG;*.GIF";

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			path = openFileDialog1->FileName;
			this->textBox2->Text = path;
			runApplication(path,false);
		}
	}

}


private: System::Void rb_pasta_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}

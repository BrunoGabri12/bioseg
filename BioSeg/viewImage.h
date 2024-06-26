#pragma once
#include "viewImage.h"
#include <opencv2/opencv.hpp>
#include <opencv2/ximgproc/slic.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <msclr/marshal_cppstd.h>
#include "imgContainer.h"
#include "ManipulatorImg.h"

processingImg::imageClass imageResult; 

namespace BioSeg {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Sum�rio para viewImage
	/// </summary>
	public ref class viewImage : public System::Windows::Forms::Form
	{

	
	public:
		viewImage(int protese, int biofilme,int result, processingImg::imageClass image)
		{
			InitializeComponent();
			this->label1->Text += " " + protese.ToString() + "px";
			this->label2->Text += " " + biofilme.ToString() + "px";
			this->label3->Text += " " + result.ToString() + "%";
			imageResult = image;

			//https://answers.opencv.org/question/52599/showing-mat-image-in-picturebox/
			cv::Mat printImage = image.getImg();

			cv::cvtColor(printImage, printImage, cv::COLOR_BGR2BGRA);
			int widthPictureBox = 320;
			int heightPictureBox = 240;
			

			cv::resize(printImage, printImage,cv::Size(widthPictureBox, heightPictureBox), cv::INTER_LINEAR);
		
			HBITMAP hBit = CreateBitmap(printImage.cols, printImage.rows, 1, 32, printImage.data);
			Bitmap^ bmp = Bitmap::FromHbitmap((IntPtr)hBit);
			
			pictureBox1->Image = bmp;
 		}

	protected:
		/// <summary>
		/// Limpar os recursos que est�o sendo usados.
		/// </summary>
		~viewImage()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;


	protected:

	private:
		/// <summary>
		/// Vari�vel de designer necess�ria.
		/// </summary>
		System::ComponentModel::Container ^components;
		
#pragma region Windows Form Designer generated code
		/// <summary>
		/// M�todo necess�rio para suporte ao Designer - n�o modifique 
		/// o conte�do deste m�todo com o editor de c�digo.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(41, 29);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(320, 240);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &viewImage::pictureBox1_Click);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::Green;
			this->button1->ForeColor = System::Drawing::SystemColors::Control;
			this->button1->Location = System::Drawing::Point(143, 455);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(120, 35);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Salvar imagem";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &viewImage::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(37, 346);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(131, 20);
			this->label1->TabIndex = 2;
			this->label1->Text = L"�rea da pr�tese: ";
			this->label1->Click += gcnew System::EventHandler(this, &viewImage::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(37, 303);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(127, 20);
			this->label2->TabIndex = 3;
			this->label2->Text = L"�rea do biofilme:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(37, 389);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(188, 20);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Porcentagem de biofilme:";
			this->label3->Click += gcnew System::EventHandler(this, &viewImage::label3_Click);
			// 
			// openFileDialog1
			// 
			this->saveFileDialog1->FileName = L"saveFileDialog1";
			// 
			// viewImage
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(415, 502);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"viewImage";
			this->Text = L"viewImage";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}

private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

	saveFileDialog1->Filter = "JPEG Image|*.jpg|PNG Image|*.png|Gif Image|*.gif";


	if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {

		String^ temp = saveFileDialog1->FileName; 
		saveFileDialog1->FileName = "ImagemResultado";
		IntPtr pointer_temp = Runtime::InteropServices::Marshal::StringToHGlobalAnsi(temp);
		const char* input_location = static_cast<const char*>(pointer_temp.ToPointer());

		cv::imwrite(input_location, imageResult.getImg());
		
	}

}
};
}

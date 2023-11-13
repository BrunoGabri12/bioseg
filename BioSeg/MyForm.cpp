
#include "MyForm.h"
#include <direct.h>
#include <opencv2/opencv.hpp>
#include <opencv2/ximgproc/slic.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <msclr/marshal_cppstd.h>
#include "imgContainer.h"
#include "ManipulatorImg.h"
#include "viewImage.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

void main(array<String^>^ args) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	BioSeg::MyForm frm;
	Application::Run(% frm);
}


int BioSeg::MyForm::runApplication(String^ path) {

	std::string pathImg = msclr::interop::marshal_as<std::string>(path);

	processingImg::imageClass image; 
	processingImg::imageClass imageBackgroundSegmentation;
	processingImg::imageClass imageBiofilmeClassification;
	processingImg::imageClass imageResult;
	
	processingImg::ManipulatorImg processor; 

	image.setImg(pathImg.data());

	//imagem original com o fundo segmentado
	processor.setImg(image);
	imageBackgroundSegmentation = processor.applyImageGaussianBlur(cv::Size(5, 5), 1, 1)
		.applySplit(2)
		.applyImageAdaptativeTheresholding(255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 1051, 0)
		.applyImageMorphology(cv::MORPH_ELLIPSE, 3, cv::MORPH_ERODE, 1)
		.applyImageMorphology(cv::MORPH_ELLIPSE, 2, cv::MORPH_CLOSE, 2)
		.applyImageCut()
		.applyImageSubtract(image)
		.build();


	//retorna uma máscara da delimitação do biofilme 
	processor.setImg(imageBackgroundSegmentation);
	imageBiofilmeClassification = processor.applyGammaCorrection(2.75)
		.applySuperPixelsSegmentation(102, 10, 10, 5)
		.applyClassificationBiofilmeAndProtese()
		.build();

	//imagem original, com o fundo preto e o biofilme segmentado por vermelho
	processor.setImg(imageBackgroundSegmentation);
	imageResult = processor.paintBiofilme(imageBiofilmeClassification).build();


	processor.setImg(imageResult);
	int protese = processor.calcAreaProtese();
	int biofilme = processor.calcAreaBiofilme();
	float porcentagem = (float(biofilme) / float(protese)) *100;



	viewImage^ nextForm = gcnew viewImage(protese, biofilme,porcentagem,imageResult) ; 
	nextForm->ShowDialog();
	
	return 0;
}

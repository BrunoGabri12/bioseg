#pragma once

#include <iostream> 
#include <vector>
#include <stdexcept>
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include "dirent.h"
#include "ManipulatorImg.h"
using namespace std;


/*************THRESHOLDING************/

processingImg::ManipulatorImg processingImg::ManipulatorImg::applyImageThresholding(int min, int max, int type) {
	//aplica��o Thresholding na imagem.
	//min= valor m�nimo de thresholding max = valor m�ximo. 
	//type = tipo de thresholding
	/*Ex:
	cv.THRESH_BINARY
	cv.THRESH_BINARY_INV
	cv.THRESH_TRUNC
	cv.THRESH_TOZERO
	cv.THRESH_TOZERO_INV
	*/

	if (min == 0) {
		cv::Mat img[3];
		cv::split(this->img.getImg(), img);
	
		this->img.setImg(img[0]);
	}
	cv::threshold(this->img.getImg(), this->img.getImg(), min, max, type);

	return *this;
}


processingImg::ManipulatorImg processingImg::ManipulatorImg::applySplit(int channel) {
	/*Realiza a separa��o dos canais encontrados na imagem
	channel = {0,1,2}
	return imagem do canal especificado */
	
	cv::Mat img[3];
	cv::split(this->img.getImg(), img);
	
	this->img.setImg(img[channel]);
	
	return *this;
}

processingImg::ManipulatorImg processingImg::ManipulatorImg::applyImageAdaptativeTheresholding(int maxValue, int adaptiveMethods, int thresholdType, int blockSize, int C) {
	/*
	Aplica��o thresholding adapitative.
	maxValue: valor m�ximo do threshold == 255
	adaptiveMethods = m�todo adaptativo
		cv.ADAPTIVE_THRESH_MEAN_C
		cv.ADAPTIVE_THRESH_GAUSSIAN_C

	thresholdType = tipo de thresholding
		THRESH_BINARY // THRESH_BINARY_IN
	blockSize = tamanho do bloco utilizado para calcular o threshold
		3,5,7
	C = constante normalmente positiva
	*/
	cv::Mat img = this->img.getImg();
	cv::adaptiveThreshold(this->img.getImg(), img, maxValue, adaptiveMethods, thresholdType, blockSize, C);

	this->img.setImg(img);
	return *this;
}

processingImg::ManipulatorImg processingImg::ManipulatorImg::applyImageGaussianBlur(cv::Size ksize, double sigmaX, double sigmaY) {
	/*
	Aplica��o do m�todo GaussianBlur na imagem desejada
	Ksize valor do kernel que ir� percorrer a imagem
	sigmaX valor de desvio em X
	sigmaY valor de desvio em Y
	retorna a imagem com o blur aplicado
	*/
	cv::GaussianBlur(this->img.getImg(), this->img.getImg(), ksize, sigmaX, sigmaY);
	return *this;
}

processingImg::ManipulatorImg processingImg::ManipulatorImg::applyGammaCorrection(float gamma) {

	cv::Mat img = this->img.getImg();
	cv::Mat lookUpTable(1, 256, CV_8U);
	cv::Mat res = img.clone();
	
	uchar* p = lookUpTable.ptr();

	for (int i = 0; i < 256; ++i)
		p[i] = cv::saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);

	LUT(img, lookUpTable, res);

	this->img.setImg(res);

	return *this;
}



processingImg::ManipulatorImg processingImg::ManipulatorImg::applyImageMorphology(int elementStruc, int morph_size, int type, int iterations) {
	/*
	M�todo para aplica��o de opera��es morfol�gicas na imagem

	elementStruc =
		- MORPH_RECT
		- MORPH_CROSS
		- MORPH_ELIPSE

	morph_size = tamanho dos elementos estruturantes

	type
		- MORPH_ERODE
		- MORPH_DILATE
		- MORPH_OPEN
		- MORPH_CLOSE

	iterations = quantidade de itera��es desejadas para serem realizadas na imagem

	retorna a imagem com a opera��o morfol�gica aplicada
	*/

	cv::Mat element = cv::getStructuringElement(elementStruc,
	cv::Size(2 * morph_size + 1, 2 * morph_size + 1),
	cv::Point(morph_size, morph_size));
	cv::morphologyEx(this->img.getImg(), this->img.getImg(), type, element, cv::Point(-1, -1), iterations);

	return *this;
}


processingImg::ManipulatorImg processingImg::ManipulatorImg::applyImageContrast(double alpha, double beta) {
	/*
	 Aplica contraste na imagem

	 alpha
	 beta

	 g(i,j) = alpha * f(i,j) + beta

		exemplos de valores
			alpha 2.2
			beta 50

	retorna a imagem com o contraste e brilho modificados
	*/

	cv::Mat img = this->img.getImg();

	this->img.imShow();
	this->img.getImg().convertTo(img, -1, alpha, beta);
	return *this;
}


processingImg::ManipulatorImg processingImg::ManipulatorImg::applySuperPixelsSegmentation(int algorithm, int region_size = 10, float ruler = 0.075f, int iterate = 10) {
	/*
	aplica��o do m�todo de superpixel na imagem

	algorithm
		- SLIC
		- SLICO
		- MSLIC

	region_size = tamanho da regi�o do superpixel, valor padr�o de 10

	ruler = fator de suavidade do superpixel

	iterate = quantidade de itera��es realizadas na imagem

	retorna a imagem com os superpixels
	*/

	cv::Mat img = this->img.getImg();
	cv::Ptr<cv::ximgproc::SuperpixelSLIC> slic = cv::ximgproc::createSuperpixelSLIC(img, algorithm, region_size, ruler);
	cv::Mat1i labelImg(img.rows, img.cols);

	slic->iterate(iterate);
	slic->getLabels(labelImg);


	for (int i = 0; i < slic->getNumberOfSuperpixels(); ++i)
	{
		// Mask for each label
		cv::Mat1b superpixel_mask = labelImg == i;
		cv::Scalar BGR = mean(img, superpixel_mask);

		img.setTo(BGR, superpixel_mask);
	}


	this->setImg(img);
	return *this;
}


bool processingImg::ManipulatorImg::applyClassificationRefinedTree(cv::Scalar BGR) {

	if (BGR[0] < 20 && BGR[1] < 20 && BGR[2] < 20) {
		return false;
	}
	if (BGR[0] > 206) {
		if (BGR[0] > 246) {
			return false;
		}
		else {
			if (BGR[1] > 88) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else {
		if (BGR[1] > 36) {
			if (BGR[0] > 91) {
				if (BGR[1] > 67) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
		}
		else {
			if (BGR[0] > 66) {
				return false;
			}
			else {
				return true;
			}

		}
	}
}



//subtrai uma imageClass da outra resultando apenas no biofilme 
processingImg::ManipulatorImg processingImg::ManipulatorImg::applyClassificationBiofilmeAndProtese() {

	cv::Mat img = this->img.getImg();

	for (int i = 0; i < img.rows; i++) {

		for (int j = 0; j < img.cols; j++) {
			if (!applyClassificationRefinedTree(img.at<cv::Vec3b>(i, j))) {
				img.at<cv::Vec3b>(i, j)[0] = 0;
				img.at<cv::Vec3b>(i, j)[1] = 0;
				img.at<cv::Vec3b>(i, j)[2] = 0;
			}
			else {
				img.at<cv::Vec3b>(i, j)[0] = 255;
				img.at<cv::Vec3b>(i, j)[1] = 255;
				img.at<cv::Vec3b>(i, j)[2] = 255;
			}

		}

	}

	return *this;
}


processingImg::ManipulatorImg processingImg::ManipulatorImg::applyMetrics(imageClass pattern) {

	/*
	pattern = imagem segmentada manualmente

	verdadeiroPositivo = Regi�o de Biofilme e classificada como biofilme
	verdadeiroNegativo = Regi�o de Pr�tese e classificada como pr�tese
	falsoPositivo = Regi�o de Pr�tese presente na imagem e classificada como biofilme
	falsoNegativo = Regi�o de Biofilme na Imagem e classifica como protese

	*/

	cv::Mat img = this->img.getImg();
	cv::Mat patternImg = pattern.getImg();
	float verdadeiroPositivos = 0;
	float falsopositivos = 0;
	float falsonegativo = 0;
	float vedadeiroNegativo = 0;

	//flags para avaliar se a regi�o � vermelha ( Biofilme detectado ) ou n�o
	bool redPattern = false;
	bool redImg = false;

	for (int i = 0; i < img.rows; i++) {  //Percorre as duas imagens comparando pixel a pixel 

		for (int j = 0; j < img.cols; j++) {

			if (img.at<cv::Vec3b>(i, j)[0] < 20 && img.at<cv::Vec3b>(i, j)[1] < 20 && img.at<cv::Vec3b>(i, j)[2] < 20) continue;

			if (patternImg.at<cv::Vec3b>(i, j)[0] == 0 && patternImg.at<cv::Vec3b>(i, j)[1] == 0 && patternImg.at<cv::Vec3b>(i, j)[2] == 255) {
				redPattern = true;
			}
			else {
				redPattern = false;
			}


			if (img.at<cv::Vec3b>(i, j)[0] == 0 && img.at<cv::Vec3b>(i, j)[1] == 0 && img.at<cv::Vec3b>(i, j)[2] == 255) {
				redImg = true;

			}
			else {
				redImg = false;
			}


			//Se a regi�o do padr�o � vermelho e o da imagem tamb�m, ent�o temos uma regi�o de biofilme
			if (redPattern && redImg) {

				verdadeiroPositivos += 1;

				//Vermelho � verdadeiro positivo
				img.at<cv::Vec3b>(i, j)[0] = 0;
				img.at<cv::Vec3b>(i, j)[1] = 0;
				img.at<cv::Vec3b>(i, j)[2] = 255;
			}

			//Se o padr�o � !vermelho (protese) e a imagem � bioflme, temos ent�o um falso positvo
			else if (!redPattern && redImg) {
				falsopositivos += 1;

				//Rosa Escuro � falso positivo
				img.at<cv::Vec3b>(i, j)[0] = 128;
				img.at<cv::Vec3b>(i, j)[1] = 0;
				img.at<cv::Vec3b>(i, j)[2] = 128;
			}

			//Se o padr�o � !vermelho  (protese) e a imagem � !vermelho (protese) , temos ent�o um verdadeiro negativo
			else if (!redPattern && !redImg) {
				vedadeiroNegativo += 1;

				//Verde � verdadeiro negativp
				img.at<cv::Vec3b>(i, j)[0] = 0;
				img.at<cv::Vec3b>(i, j)[1] = 255;
				img.at<cv::Vec3b>(i, j)[2] = 0;
			}

			//Caso padr�o seja vermelho e imagem � !vermelho (regi�o de protese), temos um falso negativo 
			else if (redPattern && !redImg) {
				falsonegativo += 1;

				//Amarelho � um falso negativo 
				img.at<cv::Vec3b>(i, j)[0] = 0;
				img.at<cv::Vec3b>(i, j)[1] = 255;
				img.at<cv::Vec3b>(i, j)[2] = 255;
			}


		}


	}


	//realiza o c�lculo das m�tricas 
	//Precis�o, especificidade, sensibilidade e acur�cia 
	float precisa = (verdadeiroPositivos / (verdadeiroPositivos + falsopositivos));
	float especificidade = ((vedadeiroNegativo) / (vedadeiroNegativo + falsopositivos));
	float sensibilidade = ((verdadeiroPositivos) / (verdadeiroPositivos + falsonegativo));
	float acuracia = ((verdadeiroPositivos + vedadeiroNegativo) / (verdadeiroPositivos + vedadeiroNegativo + falsonegativo + falsopositivos));


	std::cout << verdadeiroPositivos << "," << vedadeiroNegativo << "," << falsopositivos << "," << falsonegativo << "," << precisa << "," << especificidade << "," << sensibilidade << "," << acuracia << endl;


	return *this;
}



void  processingImg::ManipulatorImg::applyRandomShort(int size) {

	//M�todo para escolher pixels aleat�rios dentro da imagem 
	// valor de size para especificar a quantidade de pixels aleat�rios deseja-se

	cv::Mat img = this->img.getImg();

	int imgCols = img.cols;
	int imgRows = img.rows;

	cv::Vec3b RGB;
	std::vector <cv::Vec3b> arrayRGB;
	int count = 0;


	//colocar os valores em um arrayList

	for (int i = 0; i < imgCols; i++) {
		for (int j = 0; j < imgRows; j++) {


			if (img.at<cv::Vec3b>(j, i)[0] <= 20 && img.at<cv::Vec3b>(j, i)[1] <= 20 && img.at<cv::Vec3b>(j, i)[2] <= 20)
				continue; //pula os valores de RGB preto

			RGB = img.at<cv::Vec3b>(j, i);
			arrayRGB.push_back(RGB); //Adiciona o RGB no array 
		}
	}



	srand((unsigned)time(NULL));

	int lineRandom = 0;  //seleciona a linha aleat�riamente de 0 a array.size()

	while (count < size) {


		if (arrayRGB.size() == 0) { // para o caso onde n�o h� biofilme na imagem
			count += 1;
			continue;
		}
		else {
			lineRandom = 0 + (rand() % arrayRGB.size());
		}



		int B = arrayRGB[lineRandom][0];
		int G = arrayRGB[lineRandom][1];
		int R = arrayRGB[lineRandom][2];


		std::cout << R << "\t " << G << "\t" << B << "\t" << "protese" << endl; //mostra os valores expressos de R,G e B 

		count += 1;


	}




}

//Subtrai uma imagem da outra 
processingImg::ManipulatorImg processingImg::ManipulatorImg::applyImageSubtract(imageClass img) {

	cv::Mat base = img.getImg();
	cv::Mat mask = this->img.getImg();
	cv::Mat result;

	base.copyTo(result, mask);



	this->setImg(result);

	return *this;
}

processingImg::ManipulatorImg processingImg::ManipulatorImg::applyImagemAdd(imageClass img) {
	cv::add(this->img.getImg(), img.getImg(), this->img.getImg());
	return *this;
}

processingImg::ManipulatorImg processingImg::ManipulatorImg::applySuperPixelContour(int algorithm, int region_size, int ruler, int iterate, bool thick_line) {
	//Contorno do superpixel 
	cv::Mat img = this->img.getImg();
	cv::Ptr<cv::ximgproc::SuperpixelSLIC> slic = cv::ximgproc::createSuperpixelSLIC(img, algorithm, region_size, ruler);

	slic->iterate(iterate);


	cv::Mat result = img.clone();

	slic->getLabelContourMask(result, TRUE);

	img.setTo(cv::Scalar(0, 0, 255), result);

	this->img.setImg(img);

	return *this;
}

processingImg::ManipulatorImg processingImg::ManipulatorImg::paintBiofilme(imageClass mask) {

	cv::Mat maskImg = mask.getImg(); 
	cv::Mat img = this->img.getImg();


	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			if (maskImg.at<cv::Vec3b>(i, j)[0] == 255 && maskImg.at<cv::Vec3b>(i, j)[1] == 255 && maskImg.at<cv::Vec3b>(i, j)[2] == 255) {
				img.at<cv::Vec3b>(i, j)[0] = 0;
				img.at<cv::Vec3b>(i, j)[1] = 0;
				img.at<cv::Vec3b>(i, j)[2] = 255;
			}
		}
	}

	return *this;

}

//subtrai uma imageClass da outra resultando apenas no biofilme 
processingImg::ManipulatorImg processingImg::ManipulatorImg::applySubtractBiofilme(imageClass img) {

	cv::Mat imgj = img.getImg();
	cv::Mat imgp = this->img.getImg();

	for (int i = 0; i < imgp.rows; i++) {

		for (int j = 0; j < imgp.cols; j++) {

			if (imgj.at<cv::Vec3b>(i, j)[0] == 0 && imgj.at<cv::Vec3b>(i, j)[1] == 0 && imgj.at<cv::Vec3b>(i, j)[2] == 255) {
				continue;
			}
			else {
				imgp.at<cv::Vec3b>(i, j) = 0;
			}

		}

	}

	return *this;
}




//subtrai a protese da imagem, resultando somente em biofilme 
processingImg::ManipulatorImg processingImg::ManipulatorImg::applySubtractProtese(imageClass img) {

	cv::Mat imgj = img.getImg();
	cv::Mat imgp = this->img.getImg();

	for (int i = 0; i < imgp.rows; i++) {

		for (int j = 0; j < imgp.cols; j++) {

			if (imgj.at<cv::Vec3b>(i, j)[0] == 0 && imgj.at<cv::Vec3b>(i, j)[1] == 255 && imgj.at<cv::Vec3b>(i, j)[2] == 0) {
				continue;
			}
			else {
				imgp.at<cv::Vec3b>(i, j) = 0;
			}

		}

	}

	return *this;
}


//recorta a �rea da regua na imagem 
processingImg::ManipulatorImg processingImg::ManipulatorImg::applyImageCut() {



	bool flag = false;
	int i, j;

	cv::Mat img = this->img.getImg();

	for (i = img.rows / 2; i < img.rows; ++i) {


		for (j = 0; j < img.cols; ++j) { //percorre uma linha inteira para 
											//verificar se existe uma linha somente com zeros 

			if (!img.at<uchar>(i, j) == 0) {
				flag = false;	//caso tenha achado uma linha vazia ativa flag 
			}

		}

		if (flag) { //se flag== false, ent�o linha em preto foi encontrada

			for (; i < img.rows; i++) {	//
				for (int t = 0; t < img.cols; t++) {
					img.at<uchar>(i, t) = 0;
				}
			}

			break;
		}

		flag = true;
	}

	return *this;
}


//calculo da �rea da imagem
void processingImg::ManipulatorImg::calcArea() {

	int larg = this->img.getImg().cols * 3;
	int alt = this->img.getImg().rows;

	std::cout << larg * alt << std::endl;



}

//calculo da �rea da protese 
int processingImg::ManipulatorImg::calcAreaProtese() {

	cv::Mat img = this->img.getImg();
	int size = 0;


	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {			
			//tudo que n�o for (0,0,0) � considerado parte da protese 
			if (!(img.at<cv::Vec3b>(i, j)[0] == 0 && img.at<cv::Vec3b>(i, j)[1] == 0 && img.at<cv::Vec3b>(i, j)[2] == 0)) {
				size++;
			}
		}
	}

	return size;
}


int processingImg::ManipulatorImg::calcAreaBiofilme() {

	cv::Mat img = this->img.getImg();
	int size = 0;

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			//tudo que for (0,0,255) --vermelho-- � biofilme
			if (img.at<cv::Vec3b>(i, j)[0] == 0 && img.at<cv::Vec3b>(i, j)[1] == 0 && img.at<cv::Vec3b>(i, j)[2] == 255) {
				size++;
			}

		}
	}

	return size;
}

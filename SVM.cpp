#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"  
#include "opencv2/ml.hpp"		  

using namespace std;
using namespace cv;
using namespace ml;

const Size winSize = Size(96, 48);
const Size winStride = Size(48, 24);
const Size blockSize = Size(32, 16);
const Size blockStride = Size(16, 8);
const Size cellSize = Size(8, 8);
const int nbins = 9;
const int dims = 28800;


vector<string> imgPath;
void GetImgPath(string filePath);

int train()
//int main()
{
	Mat trainData, trainLable;
	std::cout << "loading data......" << endl;
	FileStorage finData("..\\data\\HOGData\\trainData.xml", FileStorage::READ);
	FileStorage finLable("..\\data\\HOGData\\trainLable.xml", FileStorage::READ);
	finData["trainData"] >> trainData;
	finLable["trainLable"] >> trainLable;

	trainData.convertTo(trainData, CV_32FC1);
	trainLable.convertTo(trainLable, CV_32SC1);

	finData.release();
	finLable.release();
	std::cout << "load hog data successfully!" << endl;

	std::cout << "svm training......" << endl;
	
	CvTermCriteria criteria;
	criteria = cvTermCriteria(CV_TERMCRIT_ITER, 100, FLT_EPSILON); 

																   
	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::C_SVC); //
	svm->setKernel(SVM::LINEAR);

	//svm->setKernel(SVM::RBF); 
	//svm->setGamma(8);		 
	svm->setTermCriteria(criteria);
	svm->train(trainData, ml::ROW_SAMPLE, trainLable);
	//Ptr<TrainData> trainData = TrainData::create(train_data, ROW_SAMPLE, train_lable);
	//cout << "1" << endl;
	//svm->trainAuto(trainData);	//kFold = 10

	
	std::cout << "saving svm data......" << endl;
	svm->save("..\\data\\SVMData\\svm.xml");
	std::cout << "save svm data successfully!" << endl;

	//float gamma = svm->getGamma();
	//cout << "gamma:" << gamma << endl;

	system("pause");
	return 0;
}



//int main()
int predict()
{
	
	std::cout << "loading svm data......" << endl;
	Ptr<SVM> svm = SVM::create();
	string svmDataPath = "..\\data\\SVMData\\svm.xml";
	svm = StatModel::load<SVM>(svmDataPath);
	std::cout << "load svm data successfully!" << endl;

	
	GetImgPath("C:\\Users\\VINAY LAATA\\Documents\\Visual Studio 2015\\Projects\\opencvtest2\\data\\images\\a\\");
	GetImgPath("C:\\Users\\VINAY LAATA\\Documents\\Visual Studio 2015\\Projects\\opencvtest2\\data\\images\\b\\");
	GetImgPath("C:\\Users\\VINAY LAATA\\Documents\\Visual Studio 2015\\Projects\\opencvtest2\\data\\images\\c\\");
	GetImgPath("C:\\Users\\VINAY LAATA\\Documents\\Visual Studio 2015\\Projects\\opencvtest2\\data\\images\\d\\");
	GetImgPath("C:\\Users\\VINAY LAATA\\Documents\\Visual Studio 2015\\Projects\\opencvtest2\\data\\images\\e\\");
	GetImgPath("C:\\Users\\VINAY LAATA\\Documents\\Visual Studio 2015\\Projects\\opencvtest2\\data\\images\\f\\");
	GetImgPath("C:\\Users\\VINAY LAATA\\Documents\\Visual Studio 2015\\Projects\\opencvtest2\\data\\images\\g\\");
	GetImgPath("C:\\Users\\VINAY LAATA\\Documents\\Visual Studio 2015\\Projects\\opencvtest2\\data\\images\\h\\");
	GetImgPath("C:\\Users\\VINAY LAATA\\Documents\\Visual Studio 2015\\Projects\\opencvtest2\\data\\images\\i\\");
	GetImgPath("C:\\Users\\VINAY LAATA\\Documents\\Visual Studio 2015\\Projects\\opencvtest2\\data\\images\\j\\");
	GetImgPath("C:\\Users\\VINAY LAATA\\Documents\\Visual Studio 2015\\Projects\\opencvtest2\\data\\images\\k\\");

	std::cout << "size=  "<<imgPath.size() << endl;
	
	int k = 1;
	for (vector<string>::iterator imgIter = imgPath.begin(); imgIter != imgPath.end(); imgIter++)
	{
		std::cout << *imgIter << endl;
	}
	std::cout << "vector end" << endl;
	for (vector<string>::iterator imgIter = imgPath.begin(); imgIter != imgPath.end(); imgIter++)
	{
		//cout << *imgIter << ":";

		Mat src = imread(*imgIter, 0);
		
		if (src.empty())
		{
			std::cout << *imgIter << ":" << endl;;
			//break;
		}
		
		CvMat *hogData;
		hogData = cvCreateMat(1, dims, CV_32FC1);
		cvSetZero(hogData);

		HOGDescriptor *hog = new HOGDescriptor(winSize, blockSize, blockStride, cellSize, nbins);
		vector <float> descriptors;
		hog->compute(src, descriptors, winStride, Size(0, 0));
		int j = 0;
		for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++)
		{
			cvmSet(hogData, 0, j, *iter);
			j++;
		}
		cvSave("..\\data\\HOGData\\testData.xml", hogData);

		Mat testData;
		FileStorage finData("..\\data\\HOGData\\testData.xml", FileStorage::READ);
		finData["testData"] >> testData;
		testData.convertTo(testData, CV_32FC1);
		finData.release();
		std::cout << "ANS  " << k << endl;
		int response = (int)svm->predict(testData);
		switch (response)
		{
		case 1:
			std::cout << "Person A" << endl;
			break;
		case 2:
			std::cout << "Person B" << endl;
			break;
		case 3:
			std::cout << "Person C" << endl;
			break;
		case 4:
			std::cout << "Person D" << endl;
			break;
		case 5:
			std::cout << "Person E" << endl;
			break;
		case 6:
			std::cout << "Person F" << endl;
			break;
		case 7:
			std::cout << "Person G" << endl;
			break;
		case 8:
			std::cout << "Person H" << endl;
			break;
		case 9:
			std::cout << "Person I" << endl;
			break;
		case 10:
			std::cout << "Person J" << endl;
			break;
		case 11:
			std::cout << "Person K" << endl;
			break;
		default:
			break;
		}
		k++;
	}
	system("pause");
	return 0;
}


void GetImgPath(string filePath)
{
	string imgList = "data_list.txt";
	ifstream fin;
	fin.open(filePath + imgList);
	char name[10];
	int i = 5;
	while (i--)
	{
		fin.getline(name, 10);
		string imgName = name;
		string load = filePath + imgName;
		imgPath.push_back(load);
	}
}


int main()
{
	train();
	predict();
	return 0;
}
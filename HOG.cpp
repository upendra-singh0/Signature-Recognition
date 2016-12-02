

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp> 

using namespace std;
using namespace cv;

const int FILE_NUMBER = 5; 
const int GROUP_NUMBER = 11; 
vector<string> imgPath;


const Size winSize = Size(96, 48);
const Size winStride = Size(48, 24);
const Size blockSize = Size(32, 16);
const Size blockStride = Size(16, 8);
const Size cellSize = Size(8, 8);
const int nbins = 9;
const int dims = 28800;



void GetImgPath(string filePath);

//int hog()
int main()
{
	
	int lable = 0;
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
	HOGDescriptor *hog = new HOGDescriptor(winSize, blockSize, blockStride, cellSize, nbins);
	vector <float> descriptors;

	CvMat *trainData, *trainLable;
	trainData = cvCreateMat(FILE_NUMBER * GROUP_NUMBER, dims, CV_32FC1);
	cvSetZero(trainData);
	
	trainLable = cvCreateMat(FILE_NUMBER * GROUP_NUMBER, 1, CV_32FC1);
	cvSetZero(trainLable);


	Mat trainImg;
	int i = 0, j = 0;
	//cout << "vivek" << endl;
	for (vector<string>::iterator imgIter = imgPath.begin(); imgIter != imgPath.end(); imgIter++)
	{
		if (i < FILE_NUMBER)
			lable = 1;
		else if (i >= FILE_NUMBER && i < FILE_NUMBER * 2)
			lable = 2;
		else if (i >= FILE_NUMBER * 2 && i < FILE_NUMBER * 3)
			lable = 3;
		else if (i >= FILE_NUMBER * 3 && i < FILE_NUMBER * 4)
			lable = 4;
		else if (i >= FILE_NUMBER * 4 && i < FILE_NUMBER * 5)
			lable = 5;
		else if (i >= FILE_NUMBER * 5  && i < FILE_NUMBER * 6)
			lable = 6;
		else if (i >= FILE_NUMBER * 6 && i < FILE_NUMBER * 7)
			lable =7;
		else if (i >= FILE_NUMBER * 7 && i < FILE_NUMBER * 8)
			lable = 8;
		else if (i >= FILE_NUMBER * 8 && i < FILE_NUMBER * 9)
			lable = 9;
		else if (i >= FILE_NUMBER  * 9 && i < FILE_NUMBER * 10)
			lable = 10;
		else if (i >= FILE_NUMBER * 10 && i < FILE_NUMBER * 11)
			lable = 11;


		Mat trainImg = imread(*imgIter);
		std::cout << "vivek" << endl;
		hog->compute(trainImg, descriptors, winStride, Size(0, 0));
		std::cout << *imgIter << endl;
		std::cout << "HOG dims: " << descriptors.size() << endl;
		
		j = 0;
		for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++)
		{
			cvmSet(trainData, i, j, *iter);
			j++;
		}
		
		cvmSet(trainLable, i, 0, lable);

		i++;
	}

	std::cout << endl << "saving data......" << endl;

	cvSave("..\\data\\HOGData\\trainData.xml", trainData);
	cvSave("..\\data\\HOGData\\trainLable.xml", trainLable);
	std::cout << "save hog data successfully!" << endl;

	system("pause");

	
	cvReleaseMat(&trainData);
	cvReleaseMat(&trainLable);
	return 0;
}


void GetImgPath(string filePath)
{
	string imgList = "data_list.txt";
	ifstream fin;
	string str = filePath +imgList;
	fin.open(str);
	char name[10];
	for (int i = 1; i <= FILE_NUMBER; i++)
	{
		fin.getline(name, 10);
		string imgName = name;
		string load = filePath + imgName;
		cout << load << endl;
		imgPath.push_back(load);
	}
}
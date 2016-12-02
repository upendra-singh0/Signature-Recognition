

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

const int THRESHOLD_VALUE = 220;
const int FILE_NUMBER = 5;


vector<string> imgPath;
vector<string> dstPath;


void GetImgPath()
{
	char ch = 'a';
	while (ch < 'l')
	{
	string str = string(1,ch) + "\\";
	cout<<"str=  " << str << endl;
	string filePath = "..\\data\\threshold\\"+str;
	string savePath = "..\\data\\images\\"+str;
	string imgList = "data_list.txt";
	ifstream fin;

	fin.open("C:\\Users\\VINAY LAATA\\Documents\\Visual Studio 2015\\Projects\\opencvtest2\\data\\threshold\\"+str+"data_list.txt");
	char name[10];
	for (int i = 1; i <= FILE_NUMBER; i++)
	{
		fin.getline(name, 10);
		string imgName = name;
		cout << "imagename=  " << name << endl;
		string load = filePath+imgName;
		cout << load << endl;
		string save = savePath + imgName;
		imgPath.push_back(load);
		dstPath.push_back(save);
	}
	ch++;
}
}


Mat Threshold(Mat src)
{
	Mat dst = Mat(src.cols, src.rows, CV_8UC1);
	threshold(src, dst, THRESHOLD_VALUE, 255, CV_THRESH_BINARY);
	return dst;
}


Mat normalize(Mat src)
{
	cout << "vivek";
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	bool flag_x1 = false, flag_x2 = false, flag_y1 = false, flag_y2 = false;

	
	
	for (int i = 0; i < src.cols - 1; i++)
	{
		
		if (flag_x1 == true)
			break;
		else
			for (int j = 0; j < src.rows - 1; j++)
			{
				
				if (src.at<uchar>(j, i) == 0)
				{
					x1 = i;
					flag_x1 = true;
					break;
				}
			}
	}
	
	
	for (int i = src.cols - 1; i >= 0; i--)
	{
		
		if (flag_x2 == true)
			break;
		else
			for (int j = 0; j < src.rows - 1; j++)
			{
				
				if (src.at<uchar>(j, i) == 0)
				{
					x2 = i;
					flag_x2 = true;
					break;
				}
			}
	}

	
	for (int j = 0; j < src.rows - 1; j++)
	{
		
		if (flag_y1 == true)
			break;
		else
			for (int i = 0; i < src.cols - 1; i++)
			{
				
				if (src.at<uchar>(j, i) == 0)
				{
					y1 = j;
					flag_y1 = true;
					break;
				}
			}
	}

	
	for (int j = src.rows - 1; j >= 0; j--)
	{
		
		if (flag_y2 == true)
			break;
		else
			for (int i = 0; i < src.cols - 1; i++)
			{
				
				if (src.at<uchar>(j, i) == 0)
				{
					y2 = j;
					flag_y2 = true;
					break;
				}
			}
	}

	Rect srcRect;
	srcRect.x = x1;
	srcRect.y = y1;
	srcRect.width = x2 - x1;
	srcRect.height = y2 - y1;

	Rect dstRect;
	dstRect.x = (int)(240 - srcRect.width) / 2;
	dstRect.y = (int)(120 - srcRect.height) / 2;
	dstRect.width = x2 - x1;
	dstRect.height = y2 - y1;

	
	Mat dst = Mat(src.rows, src.cols, CV_8UC1);
	dst.setTo(Scalar(255, 255, 255));

	
	Mat srcRoi = src(srcRect);
	Mat dstRoi = dst(dstRect);
	srcRoi.copyTo(dstRoi);

	return dst;
}

int Preprocess()
{
	GetImgPath();
	for (vector<string>::iterator i = imgPath.begin(), j = dstPath.begin();
		i != imgPath.end(), j != dstPath.end(); i++, j++)
	{
		Mat src = imread(*i, 0);
		Mat thresholdImg = Threshold(src);
		cout << "vivek"<<endl;
		//namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
		//imshow("Display window", image);
		
		//Mat dst = normalize(thresholdImg);
		//imshow("Display window", thresholdImg);
		//waitKey(0);
		//destroyWindow("Display window");
		cout << *j << endl;
		imwrite(*j,thresholdImg);
	}
	return 0;
}

int main()
{
	Preprocess();

	system("pause");
	return 0;
}
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

//int data_list(string adress, char group);
//int preprocess(string adress);
int MakeDataList(string adress, char group)
{
	string str1 = "..\\data\\threshold\\";
	string str2= "\\data_list.txt";
	string str3;
	str3 = str1 +group+ str2;
	cout << str3<<endl;
	ofstream fout;
	fout.open(str3);

	if (!fout)
	{
		cout << "file open error!" << endl;
		return -1;
	}

	int num = 0;
	int sum = 5;
	//group = 'A';
	//group = 'B';

	for (int i = 1; i <= sum; i++)
	{

			fout << group<<" ("<<i<<")" <<".png" << endl;
	}
	fout.close();
	cout << "save data list successfully!" << endl;

	system("pause");
	return 0;
}

int main()
{
	MakeDataList("", 'a');
	MakeDataList("", 'b');
	MakeDataList("", 'c');
	MakeDataList("", 'd');
	MakeDataList("", 'e');
	MakeDataList("", 'f');
	MakeDataList("", 'g');
	MakeDataList("", 'h');
	MakeDataList("", 'i');
	MakeDataList("", 'j');
	MakeDataList("", 'k');
	MakeDataList("", 'l');
	//MakeDataList("", 'i');
	return 0;
}

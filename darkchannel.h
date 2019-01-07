#pragma once
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
#include<vector>
#include <algorithm>

using namespace cv;
using namespace std;

//Çó°µÍ¨µÀ
Mat darkChannel(Mat src);
uchar light(vector<uchar> inputIamgeMax);
void haze_removal(Mat image);

#include "ji.h"
#include "cJSON.h"
#include <iostream>
#include "SD.h"
//#pragma comment(lib, "DLL.lib") 
using namespace std;
void* predictor;
const char* args;

//单帧测试帧数
int frame_num = 0;
int main()
{
	JI_EVENT event;
	event.json = NULL;

	char** json = (char**)malloc(sizeof(char));

	char *license = "111sss";
	//const char* inpath = "D:\\TestVideo\\Smoke\\22.avi";
	//const char* outpath = "F:\\BaiduNetdiskDownload\\烟雾识别\\res.avi";

	//const char* inpath = "F:\\我的文档\\WeChat Files\\y760019473\\Files\\resultvideo\\test06_result.mp4";
    const char* inpath = "C:\\Users\\www73\\Desktop\\Videos\\21_0.avi";
	//const char* inpath = "H:\\vidoes\\22.avi";
    //const char* inpath = "E:\\PotPlayer\\Capture\\001.avi";
	//const char* inpath = "G:\\烟雾检测\\videos\\sWasteBasket.avi";

	const char* outpath = "F:\\BaiduNetdiskDownload\\烟雾识别\\res.avi";

	const char* img_inpath = "D:\\Code\\Visual Studio 2015\\Projects\\雾气检测\\雾气检测\\data\\1.jpg";
	const char* img_outpath = "D:\\Code\\Visual Studio 2015\\Projects\\雾气检测\\雾气检测\\data\\ressss.jpg";

	int S_init = ji_init(0, &license);
	if (S_init == 0)
	{
		printf("Init failed.");
		return -1;
	}
	ji_create_predictor();//初始化，生成背景模型

	//for (int i = 0; i < 1; i++)
	//{
	//	//参数： 没用，输入视频地址，没用，输出视频地址，结果json
	//	int ret = ji_calc_video_file(predictor, inpath, args, outpath, &event);
	//	if (event.json != NULL)
	//	{
	//		//std::cout << event.json << std::endl;
	//		delete[] event.json;
	//		event.json = NULL;
	//	}
	//}

	//参数： 没用，输入图片地址，没用，输出图片地址，结果json
	//ji_calc_file(predictor, img_inpath, args, img_outpath, json);
	//cout << *json << endl;
	//free(*json);

	//视频单帧测试
	//ji_calc_video_frame(void* predictor, JI_CV_FRAME* inframe, const char* args, JI_CV_FRAME* outframe, JI_EVENT* event)
	VideoCapture capture;
	capture.open(inpath);
	while (true)
	{
		JI_EVENT event1;
		Mat frame; 
		Rect ret;
		capture >> frame;
		if (frame.empty())
			return -1;
		JI_CV_FRAME inf, outf;
		inf.cols = frame.cols;
		inf.rows = frame.rows;
		inf.data = frame.data;
		inf.step = frame.step;
		inf.type = frame.type();
		ji_calc_video_frame(predictor, &inf, 0, &outf, &event1);
		Mat output(outf.rows, outf.cols, outf.type, outf.data, outf.step);
		//imshow("out", output);
		if (event1.json != NULL)
		{
			std::cout << event1.json << std::endl;
			delete[] event1.json;
			event1.json = NULL;
		}
		waitKey(1);
	}

	ji_destory_predictor(predictor);

	return 0;
}

//
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include <stdlib.h>
//#include <stdio.h>
//using namespace cv;
//// 全局变量定义及赋值
//int threshold_value = 0;
//int threshold_type = 3;;
//int const max_value = 255;
//int const max_type = 4;
//int const max_BINARY_value = 255;
//
//Mat src, src_gray, dst;
//char* window_name = "Threshold Demo";
//
//char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
//char* trackbar_value = "Value";
//
//// 自定义函数声明
//void Threshold_Demo(int, void*);
//
///**
//* @主函数
//*/
//int main()
//{
//	/// 读取一副图片，不改变图片本身的颜色类型（该读取方式为DOS运行模式）
//	src = imread("C:\\Users\\www73\\Desktop\\TIM截图20181206152316.png", 1);
//	/// 将图片转换成灰度图片
//	cvtColor(src, src_gray, CV_RGB2GRAY);
//	/// 创建一个窗口显示图片
//	namedWindow(window_name, CV_WINDOW_AUTOSIZE);
//	/// 创建滑动条来控制阈值
//
//
//
//	//*************************************
//	const char* inpath = "D:\\TestVideo\\Smoke\\22.avi";
//
//	Mat frame, HSVframe;
//	char * inputPath = (char *)inpath;
//	Mat img = imread(inputPath);
//	if (img.empty())
//		return -1;
//	else {
//
//	
//	int iLowH = 0;
//	int iHighH = 180;
//
//	int iLowS = 0;
//	int iHighS = 30;
//
//	int iLowV = 221;
//	int iHighV = 255;
//
//	cvtColor(frame, HSVframe, COLOR_BGR2HSV);
//	Mat *rmat, *gmat, *bmat, *temp1, temp2, temp3;
//	Mat imgThresholded;
//	inRange(HSVframe, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);//颜色特征
//	medianBlur(imgThresholded, imgThresholded, 5);
//	Mat element1 = getStructuringElement(MORPH_RECT, Size(5, 5));
//	dilate(imgThresholded, imgThresholded, element1);//膨胀
//	imshow("color", imgThresholded);
//	
//	
//	}
//
//	createTrackbar(trackbar_type,
//		window_name, &threshold_type,
//		max_type, Threshold_Demo);
//	createTrackbar(trackbar_value,
//		window_name, &threshold_value,
//		max_value, Threshold_Demo);
//
//	/// 初始化自定义的阈值函数
//	Threshold_Demo(0, 0);
//
//	/// 等待用户按键。如果是ESC健则退出等待过程。
//	while (true)
//	{
//		int c;
//		c = waitKey(20);
//		if ((char)c == 27)
//		{
//			break;
//		}
//	}
//}
//void Threshold_Demo(int, void*)
//{
//	/* 0: 二进制阈值
//	1: 反二进制阈值
//	2: 截断阈值
//	3: 0阈值
//	4: 反0阈值
//	*/
//
//	threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);
//
//	imshow(window_name, dst);
//}



#include "ji.h"
#include "cJSON.h"
#include <iostream>
#include "SD.h"
#include<opencv2/photo.hpp>


//#pragma comment(lib, "DLL.lib") 
using namespace std;
void* predictor;
const char* args;

//��֡����֡��
int frame_num = 0;
int main()
{
	JI_EVENT event;
	event.json = NULL;

	char** json = (char**)malloc(sizeof(char));

	char *license = "111sss";
	//const char* inpath = "D:\\TestVideo\\Smoke\\22.avi";
	//const char* outpath = "F:\\BaiduNetdiskDownload\\����ʶ��\\res.avi";

	
	//const char* inpath = "E:\\PotPlayer\\Capture\\C1-11.avi";
	const char* inpath = "C:\\Users\\www73\\Desktop\\Videos\\21_0.avi";
	//const char* inpath = "C:\\Users\\www73\\Desktop\\Videos\\test.avi";
	//const char* inpath = "H:\\vidoes\\22.avi";
    //const char* inpath = "E:\\PotPlayer\\Capture\\001.avi";
	
	const char* img_path1 = "C:\\Users\\www73\\Desktop\\Videos\\Pics\\dehaze.Bmp";
	//const char* img_path2 = "C:\\Users\\www73\\Desktop\\Videos\\Pics\\background.png";
	/*Mat temp = imread(img_path1);
	cvtColor(temp, temp, CV_RGB2GRAY);

	imshow("dehaze", temp);*/


	//Mat img0 = imread(img_path1, -1),imageGray, inpainted;
	//////Mat img2 = imread(img_path2, -1);
	//Mat dark = darkChannel(img0);
	//imshow("dark",dark);

	//if (img0.empty())
	//{
	//	cout << "Couldn't open the image " << img_path1<< ". Usage: inpaint <image_name>\n" << endl;
	//	return 0;
	//}

	//cvtColor(img0, imageGray, CV_RGB2GRAY, 0);
	//Mat img = img0.clone();
	//Mat inpaintMask = Mat::zeros(img.size(), CV_8U);//mask
	//threshold(imageGray, inpaintMask, 200, 255, CV_THRESH_BINARY);
	////Mat Kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	//////��Mask���ʹ�������Mask���
	////dilate(inpaintMask, inpaintMask, Kernel);

	////inpaint(img, inpaintMask, inpainted, 3, CV_INPAINT_TELEA);//CV_INPAINT_NS
	//inpaint(img, inpaintMask, inpainted, 3, CV_INPAINT_TELEA);
	//imshow("inpainted image", inpainted);


	const char* outpath = "F:\\BaiduNetdiskDownload\\����ʶ��\\res.avi";

	const char* img_inpath = "D:\\Code\\Visual Studio 2015\\Projects\\�������\\�������\\data\\1.jpg";
	const char* img_outpath = "D:\\Code\\Visual Studio 2015\\Projects\\�������\\�������\\data\\ressss.jpg";


	//gexiangyixing();

	int S_init = ji_init(0, &license);
	if (S_init == 0)
	{
		printf("Init failed.");
		return -1;
	}
	ji_create_predictor();//��ʼ�������ɱ���ģ��

	//for (int i = 0; i < 1; i++)
	//{
	//	//������ û�ã�������Ƶ��ַ��û�ã������Ƶ��ַ�����json
	//	int ret = ji_calc_video_file(predictor, inpath, args, outpath, &event);
	//	if (event.json != NULL)
	//	{
	//		//std::cout << event.json << std::endl;
	//		delete[] event.json;
	//		event.json = NULL;
	//	}
	//}

	//������ û�ã�����ͼƬ��ַ��û�ã����ͼƬ��ַ�����json
	//ji_calc_file(predictor, img_inpath, args, img_outpath, json);
	//cout << *json << endl;
	//free(*json);

	//��Ƶ��֡����
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
//// ȫ�ֱ������弰��ֵ
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
//// �Զ��庯������
//void Threshold_Demo(int, void*);
//
///**
//* @������
//*/
//int main()
//{
//	/// ��ȡһ��ͼƬ�����ı�ͼƬ�������ɫ���ͣ��ö�ȡ��ʽΪDOS����ģʽ��
//	src = imread("C:\\Users\\www73\\Desktop\\TIM��ͼ20181206152316.png", 1);
//	/// ��ͼƬת���ɻҶ�ͼƬ
//	cvtColor(src, src_gray, CV_RGB2GRAY);
//	/// ����һ��������ʾͼƬ
//	namedWindow(window_name, CV_WINDOW_AUTOSIZE);
//	/// ������������������ֵ
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
//	inRange(HSVframe, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);//��ɫ����
//	medianBlur(imgThresholded, imgThresholded, 5);
//	Mat element1 = getStructuringElement(MORPH_RECT, Size(5, 5));
//	dilate(imgThresholded, imgThresholded, element1);//����
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
//	/// ��ʼ���Զ������ֵ����
//	Threshold_Demo(0, 0);
//
//	/// �ȴ��û������������ESC�����˳��ȴ����̡�
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
//	/* 0: ��������ֵ
//	1: ����������ֵ
//	2: �ض���ֵ
//	3: 0��ֵ
//	4: ��0��ֵ
//	*/
//
//	threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);
//
//	imshow(window_name, dst);
//}

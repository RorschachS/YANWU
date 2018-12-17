#include <iostream>
#include "cJSON.h"
#include "ji.h"
#include "SD.h"

//#include <vld.h> //内存泄漏检测
using namespace std;

int ji_init(int argc, char** argv)
{
	int ret;
	ret = Smoke_init();// 验证license文件
	return ret;
}

void *ji_create_predictor()
{
	//初始化
	Smoke_create();
	return 0;
}

void ji_destory_predictor(void* predictor)
{
	Smoke_destory();
}


int ji_calc_file(void* predictor, const char* infn, const char* args, const char* outfn, char** json)
{
	//json
	cJSON * pJsonSub = NULL;
	cJSON * nameList = NULL;
	cJSON * pJsonSub1 = NULL;
	cJSON * pJsonRoot = NULL;

	Mat result;
	char * inputPath = (char *)infn;
	Mat img = imread(inputPath);
	if (img.empty())
		return -1;
	Rect res = SmokeDetect_img(img);

	int Smokeflg = 0;
	int Num_res = 0;

	if (res.area() > 0)
	{
		Smokeflg = 1;
		Num_res = 1;
		//putText(img, "Smoke", Point(5, 50), CV_FONT_HERSHEY_COMPLEX_SMALL, 1.2, Scalar(0, 0, 255), 2, 8);
		rectangle(img, res, Scalar(0, 0, 255), 2, 8, 0);
	}
	//imshow("result_window", img);
	imwrite(outfn, img);

	pJsonSub = cJSON_CreateObject();
	//cJSON_AddItemToObject(pJsonRoot, infn, nameList = cJSON_CreateArray());
	//cJSON_AddItemToArray(nameList, pJsonSub = cJSON_CreateObject());
	cJSON_AddItemToObject(pJsonSub, "numOfSmogRects", cJSON_CreateNumber(Num_res));
	cJSON_AddItemToObject(pJsonSub, "alertFlag", cJSON_CreateNumber(Smokeflg));
	cJSON_AddItemToObject(pJsonSub, "smogInfo", nameList = cJSON_CreateArray());
	cJSON_AddItemToArray(nameList, pJsonSub1 = cJSON_CreateObject());
	if (Smokeflg)
	{
		cJSON_AddItemToObject(pJsonSub1, "x", cJSON_CreateNumber(res.x));
		cJSON_AddItemToObject(pJsonSub1, "y", cJSON_CreateNumber(res.y));
		cJSON_AddItemToObject(pJsonSub1, "width", cJSON_CreateNumber(res.width));
		cJSON_AddItemToObject(pJsonSub1, "height", cJSON_CreateNumber(res.height));
	}
	//printf("%s\n", cJSON_Print(pJsonSub));
	*json = cJSON_Print(pJsonSub);
	cJSON_Delete(pJsonSub);
	return 0;
}

int ji_calc_video_file(void* predictor, const char* infn, const char* args, const char* outfn, JI_EVENT *event)
{
	if ((strcmp(infn, "") == 0) || (strcmp(outfn, "") == 0))
	{
		return -1;
	}
	char * inputPath = (char *)infn;
	VideoCapture capture(inputPath);
	if (!capture.isOpened())
		return -1;
	int rate = capture.get(CV_CAP_PROP_FPS);
	int  frameHeight = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	int  frameWidth = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	Mat img;
	VideoWriter writer;
	writer.open(outfn, CV_FOURCC('X', 'V', 'I', 'D'), rate, Size(frameWidth, frameHeight), true);

	int nframe = 0;
	//json
	cJSON * nameList = NULL;
	cJSON * nameList1 = NULL;
	cJSON * pJsonSub = NULL;
	cJSON * pJsonSub1 = NULL;

	cJSON * pJsonRoot = NULL;
	pJsonRoot = cJSON_CreateObject();
	//char *out = new char(100000);

	while (1)
	{
		int Smokeflg = 0;
		int Num_res = 0;
		int posMsec = capture.get(CV_CAP_PROP_POS_MSEC);
		int hour = posMsec / 3600000;
		int minute = (posMsec % 3600000) / 60000;
		int second = (posMsec % 60000) / 1000;
		int millisecond = posMsec % 1000;

		double t = (double)cvGetTickCount();
		if (!capture.read(img))
			break;
		Rect res;
		res = SmokeDetect(img);
		res = Rect(res.x * 2 + 200, res.y* 2, res.width * 2, res.height * 2);


		//if (res.area > 3600)
		//{
		//	//多帧存在 且 帧差小，认为烟雾存在
		//	//添加跟踪，res加入跟踪目标
		//}
		






		t = (double)cvGetTickCount() - t;
		double FPS = 1000 / (t / ((double)cvGetTickFrequency()*1000.));
		//cout << "fps:" << FPS << endl;

		if (res.area() > 0)
		{
			Smokeflg = 1;
			Num_res = 1;
			//putText(img, "Smoke", Point(5, 50), CV_FONT_HERSHEY_COMPLEX_SMALL, 1.2, Scalar(0, 0, 255), 2, 8);
			rectangle(img, res, Scalar(0, 255, 255), 2, 8, 0);
		}
		//namedWindow("img", CV_WINDOW_NORMAL);

		resize(img, img, Size(), 0.5, 0.5);
		imshow("终极img", img);
		//writer << img;

		char nf[100];
		nframe++;
		sprintf_s(nf, "%d", nframe);
		cJSON_AddItemToObject(pJsonRoot, nf, nameList = cJSON_CreateArray());//(const char*)
		cJSON_AddItemToArray(nameList, pJsonSub = cJSON_CreateObject());
		char times[100];
		sprintf_s(times, "%02d:%02d:%02d:%02d", hour, minute, second, millisecond);
		cJSON_AddItemToObject(pJsonSub, "timeStamp", cJSON_CreateString(times));
		cJSON_AddItemToObject(pJsonSub, "numOfSmogRects", cJSON_CreateNumber(Num_res));
		cJSON_AddItemToObject(pJsonSub, "alertFlag", cJSON_CreateNumber(Smokeflg));
		cJSON_AddItemToObject(pJsonSub, "smogInfo", nameList1 = cJSON_CreateArray());
		cJSON_AddItemToArray(nameList1, pJsonSub1 = cJSON_CreateObject());
		if (Smokeflg)
		{
			cJSON_AddItemToObject(pJsonSub1, "x", cJSON_CreateNumber(res.x));
			cJSON_AddItemToObject(pJsonSub1, "y", cJSON_CreateNumber(res.y));
			cJSON_AddItemToObject(pJsonSub1, "width", cJSON_CreateNumber(res.width));
			cJSON_AddItemToObject(pJsonSub1, "height", cJSON_CreateNumber(res.height));
		}
		event->code = Num_res;
		//每帧看看
		//printf("%s\n", cJSON_Print(pJsonRoot));
	}
	event->json = cJSON_Print(pJsonRoot);
	cJSON_Delete(pJsonRoot);

	img.release();
	writer.release();
	capture.release();
	return 0;
}

int ji_calc_video_frame(void* predictor, JI_CV_FRAME* inframe, const char* args, JI_CV_FRAME* outframe, JI_EVENT* event)
{
	Mat img(inframe->rows, inframe->cols, inframe->type);
	img.data = (unsigned char*)inframe->data;
	img.step = inframe->step;
	if (img.empty())
		return -1;

	event->json = NULL;
	event->code = 0;
	//json
	cJSON * nameList = NULL;
	cJSON * nameList1 = NULL;
	cJSON * pJsonSub = NULL;
	cJSON * pJsonSub1 = NULL;

	cJSON * pJsonRoot = NULL;
	pJsonRoot = cJSON_CreateObject();
	//char *out = new char(100000);

	int Smokeflg = 0;
	int Num_res = 0;

	double t = (double)cvGetTickCount();
	Rect res;
	res = SmokeDetect(img);
	res = Rect(res.x * 2 + 200, res.y * 2, res.width * 2, res.height * 2);
	t = (double)cvGetTickCount() - t;
	double FPS = 1000 / (t / ((double)cvGetTickFrequency()*1000.));
	//cout << "fps:" << FPS << endl;

	if (res.area() > 0)
	{
		Smokeflg = 1;
		Num_res = 1;
		//putText(img, "Smoke", Point(5, 50), CV_FONT_HERSHEY_COMPLEX_SMALL, 1.2, Scalar(0, 0, 255), 2, 8);
		rectangle(img, res, Scalar(0, 0, 255), 2, 8, 0);
		
	}
	
	//namedWindow("img", CV_WINDOW_NORMAL);
	//imshow("img", img);
	//writer << img;
	outframe->cols = img.cols;
	outframe->rows = img.rows;
	outframe->data = img.data;
	outframe->step = img.step;
	outframe->type = img.type();

	char nf[100];
	//extern int frame_num;
	//frame_num++;
	//sprintf_s(nf, "%d", 1);
	//cJSON_AddItemToObject(pJsonRoot, nf, nameList = cJSON_CreateArray());//(const char*)
	//cJSON_AddItemToArray(nameList, pJsonSub = cJSON_CreateObject());
	////cJSON_AddItemToObject(pJsonSub, "numOfSmogRects", cJSON_CreateNumber(Num_res));
	////cJSON_AddItemToObject(pJsonSub, "alertFlag", cJSON_CreateNumber(Smokeflg));
	////cJSON_AddItemToObject(pJsonSub, "smogInfo", nameList1 = cJSON_CreateArray());
	//cJSON_AddItemToArray(nameList1, pJsonSub1 = cJSON_CreateObject());
	if (Smokeflg)
	{
		cJSON_AddItemToObject(pJsonSub1, "x", cJSON_CreateNumber(res.x));
		cJSON_AddItemToObject(pJsonSub1, "y", cJSON_CreateNumber(res.y));
		cJSON_AddItemToObject(pJsonSub1, "width", cJSON_CreateNumber(res.width));
		cJSON_AddItemToObject(pJsonSub1, "height", cJSON_CreateNumber(res.height));
	}
	event->code = Num_res;
	//printf("%s\n", cJSON_Print(pJsonRoot));

	//delete[] event->json;
	event->json = cJSON_Print(pJsonRoot);
	cJSON_Delete(pJsonRoot);
	img.release();
	if (Smokeflg)
		return 1;
	else
		return 0;
}

int ji_calc(void* predictor, const unsigned char* buffer, int length,
	const char* args, const char* outfn, char** json) {
	return -2;
}


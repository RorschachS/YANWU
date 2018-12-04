#include "ji.h"
#include "cJSON.h"
#include <iostream>
#include "SD.h"
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

	//const char* inpath = "F:\\�ҵ��ĵ�\\WeChat Files\\y760019473\\Files\\resultvideo\\test06_result.mp4";
	const char* inpath = "C:\\Users\\www73\\Desktop\\22.avi";
	const char* outpath = "F:\\BaiduNetdiskDownload\\����ʶ��\\res.avi";

	const char* img_inpath = "D:\\Code\\Visual Studio 2015\\Projects\\�������\\�������\\data\\1.jpg";
	const char* img_outpath = "D:\\Code\\Visual Studio 2015\\Projects\\�������\\�������\\data\\ressss.jpg";

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
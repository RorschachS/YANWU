#pragma once
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/video.hpp>
#include <opencv2/core.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
using namespace std;
using namespace cv;
int Smoke_init();
void Smoke_create();
void Smoke_destory();
Rect SmokeDetect(Mat frame);
Rect SmokeDetect_img(Mat frame_src);
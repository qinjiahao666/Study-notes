#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
#include<stdlib.h>
#include<stdio.h>
#include<iostream>

#define WINDOWS_NAME "【线性混合示例】"

using namespace std;
using namespace cv;

//全局变量声明
const int g_nMaxAlphaValue = 100; //Alpha的最大值
int g_nAlphaValueSlider;  //滑动条对应的变量
double g_dAlphaValue;
double g_dBetaValue;

//声明储存图像的变量
Mat g_srcImageA;
Mat g_srcImageB;
Mat g_dstImage;

void on_Trackbar(int, void *)
{
	//求出当前的Alpha值所占的比例
	g_dAlphaValue = (double)g_nAlphaValueSlider / g_nMaxAlphaValue;

	//bete值为1减去Alpha的值
	g_dBetaValue = (1.0 - g_dAlphaValue);

	//根据当前的Alpha的值跟beta值进行线性混合
	addWeighted(g_srcImageA, g_dAlphaValue, g_srcImageB, g_dBetaValue, 0.0, g_dstImage);

	//显示效果图
	imshow(WINDOWS_NAME, g_dstImage);
}

int main()
{
	//加载图像（两张图片的大小尺寸必须相等）
	g_srcImageA = imread("D://秦嘉豪//Pictures//1_170621165119_1.jpg");
	g_srcImageB = imread("D://秦嘉豪//Pictures//1_170621165119_11.jpg");
	if (!g_srcImageA.data) {
		cout << "can not find the imageA!" << endl;
		return -1;
	}
	if (!g_srcImageB.data) {
		cout << "can not find the imageB!" << endl;
		return -1;
	}

	//设置滑动初始值
	g_nAlphaValueSlider = 70;

	//创建窗体
	namedWindow(WINDOWS_NAME, 1);

	//在窗体中创建一个滑动条
	char TrackbarName[50];
	sprintf_s(TrackbarName, "透明值 %d", g_nMaxAlphaValue);

	createTrackbar(TrackbarName, WINDOWS_NAME, &g_nAlphaValueSlider,
		g_nMaxAlphaValue, on_Trackbar);

	//结果在回调函数中显示
	on_Trackbar(g_nAlphaValueSlider, 0);

	//按任意键结束
	waitKey(0);

	return 0;
}

// mymfc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
//#include "cv.h"
//#include "highgui.h"
#include "CvvImage.h"
#include <fstream>
#include "opencv2/opencv.hpp"
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include<cstring>

using namespace cv;
using namespace std;

typedef list<CvRect> LISTRECT;

#define IMAGE_CHANNELS 3
// CmymfcApp: 
// �йش����ʵ�֣������ mymfc.cpp
//


class NumTrainData
{
public:
	NumTrainData()
	{
		memset(data, 0, sizeof(data));
		result = -1;
	}
public:
	float data[64];
	int result;
};

#define featureLen  64

class CmymfcApp : public CWinApp
{
public:
	CmymfcApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CmymfcApp theApp;
#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "InterfaceMatrix.h"

class GaussFilter :InterfaceMatrix {
public:
	GaussFilter();
	~GaussFilter();
	virtual cv::Mat ImageProcess(const cv::Mat& img);
protected:
	
	virtual void SetPixel(int x, int y, const cv::Mat& img, cv::Mat& result);
	void CreateKernel(int size,double sigma);

};
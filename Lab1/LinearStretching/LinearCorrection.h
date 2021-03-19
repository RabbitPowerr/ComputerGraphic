#pragma once
#include "GreyFilter.h"
#include"InterfaceFilter.h"
class LenearCorrection :InterfaceFilter {
public:
	LenearCorrection();
	~LenearCorrection();
	virtual cv::Mat ImageProcess(const cv::Mat& img);
protected:
	virtual void SetPixel(int x, int y, const cv::Mat& img, cv::Mat& result);
	uchar intensityMax, intensityMin;
	uchar Get_intensity(const cv::Vec3b& col);

};




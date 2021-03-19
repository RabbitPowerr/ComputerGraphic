#pragma once
#include "InterfaceFilter.h"

class GreyFilter:InterfaceFilter{
public:
	GreyFilter();
	~GreyFilter();
	virtual cv::Mat ImageProcess(const cv::Mat& img);
protected:
	virtual void SetPixel(int x, int y, const cv::Mat& img, cv::Mat& result);

};


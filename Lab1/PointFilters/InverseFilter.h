#pragma once
#include"InterfaceFilter.h"
#include <opencv2/core.hpp>

class InverseFilter:InterfaceFilter{
public:
	InverseFilter();
	~InverseFilter();
	virtual cv::Mat ImageProcess(const cv::Mat& img);
protected:
	virtual void SetPixel(int x, int y,const cv::Mat& img,cv::Mat& result);

};




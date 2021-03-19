
#pragma once
#include"InterfaceMatrix.h"
class MedianFilter :InterfaceMatrix
{
public:
	MedianFilter();
	~MedianFilter();

	cv::Mat ImageProcess(const cv::Mat& img);
protected:
	void SetPixel(int x, int y, const cv::Mat& img, cv::Mat& result);

};


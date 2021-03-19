#pragma once

#include"InterfaceMatrix.h"
class TopHat :InterfaceMatrix
{
public:
	TopHat();
	~TopHat();

	cv::Mat ImageProcess(const cv::Mat& img);
	cv::Mat ImageProcess(const cv::Mat& img, const std::vector<std::vector<double>>& tmp);

protected:
	void SetPixel(int x, int y, const cv::Mat& img, cv::Mat& result);

};


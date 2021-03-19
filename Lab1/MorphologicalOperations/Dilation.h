#pragma once

#include"InterfaceMatrix.h"
class Dilation :InterfaceMatrix
{
public:
	Dilation();
	Dilation(const uint32_t& _sz);
	Dilation(const std::vector<std::vector<double>>& tmp);
	~Dilation();
	void Set_kernel(const std::vector<std::vector<double>>& tmp);
	cv::Mat ImageProcess(const cv::Mat& img);
protected:
	void SetPixel(int x, int y, const cv::Mat& img, cv::Mat& result);
	
};


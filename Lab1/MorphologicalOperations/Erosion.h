#pragma once
#include"InterfaceMatrix.h"
class Erosion:InterfaceMatrix
{
public:
	Erosion();
	Erosion(const uint32_t& _sz);
	Erosion(const std::vector<std::vector<double>>& tmp);
	~Erosion();
	void Set_kernel(const std::vector<std::vector<double>>& tmp);

	cv::Mat ImageProcess(const cv::Mat& img);
protected:
	void SetPixel(int x, int y, const cv::Mat& img, cv::Mat& result) ;
	
};


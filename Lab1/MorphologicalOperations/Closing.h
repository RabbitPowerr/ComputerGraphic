#pragma once
#pragma onceErosion
#include"InterfaceMatrix.h"
class Closing :InterfaceMatrix
{
public:
	Closing();
	~Closing();

	cv::Mat ImageProcess(const cv::Mat& img);
	cv::Mat ImageProcess(const cv::Mat& img, const std::vector<std::vector<double>>& tmp);
protected:
	void SetPixel(int x, int y, const cv::Mat& img, cv::Mat& result);

};


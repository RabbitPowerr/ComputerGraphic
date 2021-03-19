#pragma once
#include <opencv2/core.hpp>
class InterfaceFilter{
public:
	virtual cv::Mat ImageProcess(const cv::Mat& img)=0;
protected:
	int Clamp(int value,int min,int max) {
		return (value < min) ? min : (value > max) ? max : value;
	}
	virtual void SetPixel(int x, int y, const cv::Mat& img, cv::Mat& result) = 0;
};


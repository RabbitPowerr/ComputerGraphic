#pragma once
#include "InterfaceMatrix.h"

class SharpnessFilter :InterfaceMatrix {
public:
	SharpnessFilter();
	~SharpnessFilter();
	virtual cv::Mat ImageProcess(const cv::Mat& img);
protected:

	virtual void SetPixel(int x, int y, const cv::Mat& img, cv::Mat& result);
	void CreateKernel(int size, double sigma);

};
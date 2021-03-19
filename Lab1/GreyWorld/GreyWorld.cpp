#include "GreyWorld.h"

GreyWorld::GreyWorld(){}

GreyWorld::~GreyWorld(){}

cv::Mat GreyWorld::ImageProcess(const cv::Mat& img){
	cv::Mat result;
	img.copyTo(result);
	mid.assign(3, 0);
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			for (int chl = 0; chl < 3; chl++)
				mid[chl] += img.at<cv::Vec3b>(i, j).val[chl];

	for (int chl = 0; chl < 3; chl++)
		mid[chl] /= (double)(img.cols*img.rows);
	avg = (mid[0] + mid[1] + mid[2]) / 3;
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			SetPixel(i, j, img, result);
	return result;
}

void GreyWorld::SetPixel(int i, int j, const cv::Mat& img, cv::Mat& result){
	
	auto& col = result.at<cv::Vec3b>(i,j);
	for (int chl = 0; chl < 3; chl++)
		col.val[chl] = Clamp((double)col.val[chl]*avg/mid[chl],0,255);
}

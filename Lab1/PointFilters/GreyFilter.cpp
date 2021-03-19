#include "GreyFilter.h"

GreyFilter::GreyFilter(){}

GreyFilter::~GreyFilter(){}

cv::Mat GreyFilter::ImageProcess(const cv::Mat& img){
	cv::Mat result;
	img.copyTo(result);

	for(int i=0;i<img.rows;i++)
		for (int j = 0; j < img.cols; j++) {
			SetPixel(i,j, img, result);
		}

	return result;
}

void GreyFilter::SetPixel(int x, int y, const cv::Mat& img, cv::Mat& result){
	auto& col = result.at<cv::Vec3b>(x, y);
	double intensity = 0.299 * col.val[0] + 0.587 * col.val[1] + 0.114 * col.val[2];
	col.val[0] = col.val[1] = col.val[2] = intensity;
}

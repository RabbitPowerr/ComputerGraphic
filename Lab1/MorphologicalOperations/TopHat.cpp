#include "TopHat.h"
#include "Opening.h"

TopHat::TopHat(){}

TopHat::~TopHat(){}

cv::Mat TopHat::ImageProcess(const cv::Mat& img){
	cv::Mat result,tmp;
	img.copyTo(result);
	result = Opening().ImageProcess(result);
	for (int i = 0; i<result.rows; i++)
		for (int j = 0; j<result.cols; j++)
			SetPixel(i, j, img, result);
	return result;
}

cv::Mat TopHat::ImageProcess(const cv::Mat& img, const std::vector<std::vector<double>>& tmp){
	cv::Mat result;
	img.copyTo(result);
	result = Opening().ImageProcess(result,tmp);
	for (int i = 0; i < result.rows; i++)
		for (int j = 0; j < result.cols; j++)
			SetPixel(i, j, img, result);
	return result;

}

void TopHat::SetPixel(int i, int j, const cv::Mat& img, cv::Mat& result){
	auto& col = result.at<cv::Vec3b>(i, j);
	for (int chl = 0; chl < 3; chl++)
		col.val[chl] = Clamp((int)img.at<cv::Vec3b>(i, j).val[chl] - col.val[chl], 0, 255);

}

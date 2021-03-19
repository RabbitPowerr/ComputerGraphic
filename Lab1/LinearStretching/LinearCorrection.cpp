#include "LinearCorrection.h"
#include<algorithm>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
LenearCorrection::LenearCorrection(){}

LenearCorrection::~LenearCorrection(){}

uchar LenearCorrection::Get_intensity(const cv::Vec3b& col) {
	return col.val[0] * 0.299 + 0.587 * col.val[1] + 0.144 * col.val[2];
	
}

cv::Mat LenearCorrection::ImageProcess(const cv::Mat& img){
	cv::Mat result;
	img.copyTo(result);

	intensityMax = 0, intensityMin = 255;
	for(int i=0;i<result.rows;i++)
		for (int j = 0; j < result.cols; j++) {
			auto& col = result.at<cv::Vec3b>(i, j);
			uchar currIntensity = Get_intensity(result.at<cv::Vec3b>(i, j));
			intensityMax = std::max(intensityMax, currIntensity);
			intensityMin = std::min(intensityMin, currIntensity);
		}
	for (int i = 0; i < result.rows; i++)
		for (int j = 0; j < result.cols; j++) {
			SetPixel(i, j, img, result);
		}
	return result;

}

void LenearCorrection::SetPixel(int i, int j, const cv::Mat& img, cv::Mat& result){
	auto& col = result.at<cv::Vec3b>(i,j);
	double intens = Get_intensity(result.at<cv::Vec3b>(i, j));
	double k = (double)(intens - intensityMin) *
		(255.0) / ((double)(intensityMax - intensityMin));
	col.val[0] *= k/ intens;
	col.val[1] *= k/intens;
	col.val[2] *= k/intens;
}

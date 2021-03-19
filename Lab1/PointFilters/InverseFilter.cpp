#include "InverseFilter.h"

InverseFilter::InverseFilter() {}
InverseFilter ::~InverseFilter() {}

cv::Mat InverseFilter::ImageProcess(const cv::Mat& img) {
	cv::Mat result;
	img.copyTo(result);

	for (size_t i = 0; i < img.rows; i++)
		for (size_t j = 0; j < img.cols; j++) {
			SetPixel(i, j, img, result);
		}
	return result;
}

void InverseFilter::SetPixel(int x, int y, const cv::Mat& img, cv::Mat& result) {
	auto& col = result.at<cv::Vec3b>(x, y);
	col.val[0] = 255 - col.val[0];
	col.val[2] = 255 - col.val[2];
	col.val[1] = 255 - col.val[1];
}
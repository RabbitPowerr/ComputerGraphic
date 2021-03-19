#include "SharpnessFilter.h"

SharpnessFilter::SharpnessFilter(){
	size = 3;
	kernel.assign(size, std::vector<double>(size, -0.3));
	kernel[1][1] = 3.4;
}

SharpnessFilter::~SharpnessFilter()
{
}

cv::Mat SharpnessFilter::ImageProcess(const cv::Mat& img){
	cv::Mat result;
	img.copyTo(result);

	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			SetPixel(i, j, img, result);

	return result;
}

void SharpnessFilter::SetPixel(int i, int j, const cv::Mat& img, cv::Mat& result){
	int radX = kernel.size() / 2;
	int radY = kernel[0].size() / 2;

	double resR(0), resG(0), resB(0);

	for (int dx = -radX; dx <= radX; dx++)
		for (int dy = -radY; dy <= radY; dy++) {
			int qi = Clamp(i + dx, 0, img.rows - 1);
			int qj = Clamp(j + dy, 0, img.cols - 1);
			auto col = img.at<cv::Vec3b>(qi, qj);
			resR += (double)col.val[0] * kernel[dx + radX][dy + radY];
			resG += (double)col.val[1] * kernel[dx + radX][dy + radY];
			resB += (double)col.val[2] * kernel[dx + radX][dy + radY];

		}
	auto& col = result.at<cv::Vec3b>(i, j);
	col.val[0] = Clamp(resR, 0, 255);
	col.val[1] = Clamp(resG, 0, 255);
	col.val[2] = Clamp(resB, 0, 255);
}

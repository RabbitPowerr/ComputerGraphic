#include "GaussBlur.h"
#include<opencv2/highgui.hpp>
GaussFilter::GaussFilter(){
	size = 7;
}

GaussFilter::~GaussFilter(){}

cv::Mat GaussFilter::ImageProcess(const cv::Mat& img){
	cv::Mat result;
	img.copyTo(result);

	CreateKernel(size, 2);
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			SetPixel(i, j, img, result);
	cv::imshow("qq", img);
	return result;
}

void GaussFilter::SetPixel(int i, int j, const cv::Mat& img, cv::Mat& result){
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

void GaussFilter::CreateKernel(int size, double sigma){
	int radius = size / 2;
	kernel.assign(size, std::vector<double>(size));
	float norm(0.0);
	for (int i = -radius; i <= radius; i++)
		for (int j = -radius; j <= radius; j++) {
			kernel[i + radius][j + radius] = pow(M_E, -(i * i + j * j) / (2 * sigma * sigma));
			norm += kernel[i + radius][j + radius];
		}
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) kernel[i][j] /= norm;

}


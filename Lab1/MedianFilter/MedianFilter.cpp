#include "MedianFilter.h"

MedianFilter::MedianFilter(){
	size = 7;
}

MedianFilter::~MedianFilter(){}

cv::Mat MedianFilter::ImageProcess(const cv::Mat& img){
	cv::Mat result;
	img.copyTo(result);
	for (int i = 0; i < result.rows; i++)
		for (int j = 0; j < result.cols; j++)
			SetPixel(i, j, img, result);
	return result;
}

void MedianFilter::SetPixel(int i, int j, const cv::Mat& img, cv::Mat& result){
    int radius = size / 2;
    cv::Vec3b out = (0, 0, 0);
	std::vector < std::vector<double>> tmp(3);
	for (int di = -radius; di <= radius; di++) {
		for (int dj = -radius; dj <= radius; dj++) {
			int qi = Clamp(i + di, 0, img.rows - 1);
			int qj = Clamp(j + dj, 0, img.cols - 1);
			auto col = img.at<cv::Vec3b>(qi, qj);
			for (int chl = 0; chl < 3; chl++)
				tmp[chl].push_back(col.val[chl]);
		}
    }
	for (int chl = 0; chl < 3; chl++) {
		std::sort(tmp[chl].begin(), tmp[chl].end());
		result.at<cv::Vec3b>(i, j).val[chl] =tmp[chl][(size*size)/2];
	}

}

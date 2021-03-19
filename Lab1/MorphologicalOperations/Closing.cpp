#include "Closing.h"
#include "Erosion.h"
#include "Dilation.h"

Closing::Closing(){}

Closing::~Closing(){}

cv::Mat Closing::ImageProcess(const cv::Mat& img) {
    cv::Mat result;
    img.copyTo(result);
    result = Erosion().ImageProcess(Dilation().ImageProcess(result));
    return result;
}

cv::Mat Closing::ImageProcess(const cv::Mat& img, const std::vector<std::vector<double>>& tmp){
    cv::Mat result;
    img.copyTo(result);
    result = Erosion(tmp).ImageProcess(Dilation(tmp).ImageProcess(result));
    return result;
}

void Closing::SetPixel(int x, int y, const cv::Mat& img, cv::Mat& result){}

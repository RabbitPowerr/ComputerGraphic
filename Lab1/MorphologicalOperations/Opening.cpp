#include "Opening.h"
#include "Erosion.h"
#include "Dilation.h"

Opening::Opening()
{
}


Opening::~Opening()
{
}



cv::Mat Opening::ImageProcess(const cv::Mat& img){
    cv::Mat result;
    img.copyTo(result);
    result = Dilation().ImageProcess(Erosion().ImageProcess(result));
    return result;
}

cv::Mat Opening::ImageProcess(const cv::Mat& img, const std::vector<std::vector<double>>& tmp){
    cv::Mat result;
    img.copyTo(result);
    result = Dilation(tmp).ImageProcess(Erosion(tmp).ImageProcess(result));
    return result;
}

void Opening::SetPixel(int x, int y, const cv::Mat& img, cv::Mat& result)
{
}

#include "Erosion.h"
#include "GreyFilter.h"
#include <algorithm>

Erosion::Erosion(){
    size = 9;
    kernel.assign(size, std::vector<double>(size, 0));
    for (int i = 0; i < size; i++) 
        for (int j = 0; j < size; j++)
            kernel[i][j] = abs(i-size/2)+abs(j-size/2) <= size/2;

}
Erosion::Erosion(const uint32_t& _sz) {
    size = _sz;
    kernel.assign(size, std::vector<double>(size, 0));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            kernel[i][j] = abs(i - size / 2) + abs(j - size / 2) <= size / 2;
}

Erosion::Erosion(const std::vector<std::vector<double>>& tmp){
    kernel = tmp;
    size = kernel.size();
}

Erosion::~Erosion(){}

void Erosion::Set_kernel(const std::vector<std::vector<double>>& tmp){
    kernel = tmp;
    size=kernel.size();
}

cv::Mat Erosion::ImageProcess(const cv::Mat& img){
    
    cv::Mat result;
    img.copyTo(result);
    if (size % 2 == 0) throw "Kernal size even number";
    for(int i=0;i<img.rows;i++)
        for (int j = 0; j < img.cols; j++) {
            SetPixel(i, j,img, result);
        }
    return result;
}

void Erosion::SetPixel(int i, int j, const cv::Mat& img, cv::Mat& result) {
    int radius = size/2;
    cv::Vec3b out (255, 255, 255);
    for (int di = -radius; di <= radius; di++){
        for (int dj = -radius; dj <= radius; dj++) {
            int qi = Clamp(i + di, 0, img.rows - 1);
            int qj = Clamp(j + dj, 0, img.cols - 1);
            if (kernel[di+radius][dj+radius] < 0.5) continue;
            cv::Vec3b col = img.at<cv::Vec3b>(qi, qj);
            for (int chl = 0; chl < 3; chl++)
                out.val[chl] = std::min(col.val[chl], out.val[chl]);
        }
    }
    result.at<cv::Vec3b>(i, j) = out;
}


#include "Dilation.h"
#include "GreyFilter.h"
#include <algorithm>

Dilation::Dilation() {
    size = 9;
    kernel.assign(size, std::vector<double>(size, 0));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            kernel[i][j] = abs(i - size / 2) + abs(j - size / 2) <= size / 2;

}
Dilation::Dilation(const uint32_t& _sz){
    kernel.assign(size, std::vector<double>(size, 0));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            kernel[i][j] = abs(i - size / 2) + abs(j - size / 2) <= size / 2;
}
Dilation::Dilation(const std::vector<std::vector<double>>& tmp){
    size = tmp.size();
    kernel = tmp;
}
Dilation::~Dilation() {}

void Dilation::Set_kernel(const std::vector<std::vector<double>>& tmp){
    size = tmp.size();
    kernel = tmp;  
}

cv::Mat Dilation::ImageProcess(const cv::Mat& img) {

    cv::Mat result;
    img.copyTo(result);
    if (size % 2 == 0) throw "Kernal size even number";
    result = GreyFilter().ImageProcess(result);
    for (int i = 0; i < img.rows; i++)
        for (int j = 0; j < img.cols; j++) {
            SetPixel(i, j, img, result);
        }
    return result;
}

void Dilation::SetPixel(int i, int j, const cv::Mat& img, cv::Mat& result) {
    int radius = size / 2;
    cv::Vec3b out = (0, 0, 0);
    for (int di = -radius; di <= radius; di++) {
        for (int dj = -radius; dj <= radius; dj++) {
            int qi = Clamp(i + di, 0, img.rows - 1);
            int qj = Clamp(j + dj, 0, img.cols - 1);
            if (kernel[di + radius][dj + radius] < 0.5) continue;
            cv::Vec3b col = img.at<cv::Vec3b>(qi, qj);
            for (int chl = 0; chl < 3; chl++)
                out.val[chl] = std::max(col.val[chl], out.val[chl]);
        }
    }
    result.at<cv::Vec3b>(i, j) = out;

}


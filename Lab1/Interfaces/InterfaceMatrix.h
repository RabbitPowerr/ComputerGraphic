#pragma once
#include "InterfaceFilter.h"
#include<vector>

class InterfaceMatrix :public InterfaceFilter {
protected:
	std::vector<std::vector<double>> kernel;
	uint16_t size;
	uchar Get_intensity(const cv::Vec3b& col) {
		return col.val[0] * 0.299 + 0.587 * col.val[1] + 0.144 * col.val[2];
	}
};

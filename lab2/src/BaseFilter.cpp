#include "../include/BaseFilter.h"

void BaseFilter::apply(const cv::Mat &src, cv::Mat &dst) {
    dst = cv::Mat::zeros(src.rows, src.cols, src.type());
    for (int v = 0; v < src.rows; v++) {
        for (int u = 0; u < src.cols; u++) {
            this->operate(src, dst, cv::Vec2i(u, v));
        }
    }
}
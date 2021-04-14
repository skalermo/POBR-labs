#include "../include/ConvFilter.h"

#include <utility>

uchar ConvFilter::clamp(int val) {
    if (val > 255)
        val = 255;
    else if (val < 0)
        val = 0;
    return uchar(val);
}

ConvFilter::ConvFilter(Mat kernel_) : kernel(std::move(kernel_)) {
    this->ksize = this->kernel.size();
    int divider = 0;
    for (const auto& kk: this->kernel) {
        for (const auto& k: kk) {
            divider += k;
        }
    }
    if (divider == 0)
        divider = 1;
    for (auto& kk: this->kernel) {
        for (auto& k: kk) {
            k /= divider;
        }
    }
}

void ConvFilter::operate(const cv::Mat &src, cv::Mat &dst, cv::Vec2i uv) {
    int kh, kw;
    kh = kw = this->ksize / 2;
    cv::Vec3i acc_p = {0, 0, 0};
    for (int y = -kh; y <= kh; y++) {
        for (int x = -kw; x <= kw; x++) {
            double f = this->kernel[y+kh][x+kw];
            const auto& src_p = src.at<cv::Vec3b>(uv[0]+y, uv[1]+x);
            acc_p[0] += src_p[0] * f;
            acc_p[1] += src_p[1] * f;
            acc_p[2] += src_p[2] * f;
        }
    }
    auto& dst_p = dst.at<cv::Vec3b>(uv[0], uv[1]);
    dst_p[0] = clamp(acc_p[0]);
    dst_p[1] = clamp(acc_p[1]);
    dst_p[2] = clamp(acc_p[2]);
}
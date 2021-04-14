#ifndef POBR_LAB1_BASEFILTER_H
#define POBR_LAB1_BASEFILTER_H

#include "opencv2/core.hpp"

class BaseFilter
{
public:
    // assuming filter has shape of square
    int ksize;

    ~BaseFilter() = default;
    virtual void operate(const cv::Mat& src, cv::Mat& dst, cv::Vec2i uv) = 0;
    void apply(const cv::Mat& src, cv::Mat& dst);
};

#endif //POBR_LAB1_BASEFILTER_H

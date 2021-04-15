#ifndef POBR_LAB2_CONVFILTER_H
#define POBR_LAB2_CONVFILTER_H

#include "BaseFilter.h"

class ConvFilter : public BaseFilter {
private:
    static uchar clamp(int val);
public:
    typedef std::vector<std::vector<double>> Mat;
    Mat kernel;
    explicit ConvFilter(Mat kernel);
    ~ConvFilter() = default;

    void operate(const cv::Mat &src, cv::Mat &dst, cv::Vec2i uv) override;
};

#endif //POBR_LAB2_CONVFILTER_H

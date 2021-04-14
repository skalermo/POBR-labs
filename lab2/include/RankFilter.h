#ifndef POBR_LAB2_RANKFILTER_H
#define POBR_LAB2_RANKFILTER_H

#include "BaseFilter.h"
#define MIN_FILTER 0
#define MEDIAN_FILTER 1
#define MAX_FILTER 2

class RankFilter : public BaseFilter {
public:
    int mode;
    RankFilter(int size, int mode);
    ~RankFilter() = default;
    void operate(const cv::Mat &src, cv::Mat &dst, cv::Vec2i uv) override;
};

#endif //POBR_LAB2_RANKFILTER_H

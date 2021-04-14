#include <vector>
#include "../include/RankFilter.h"


RankFilter::RankFilter(int size, int mode) {
    this->ksize = size;
    if (mode > 2 || mode < 0)
        mode = 0;
    this->mode = mode;
}

void RankFilter::operate(const cv::Mat &src, cv::Mat &dst, cv::Vec2i uv) {
    std::vector<std::vector<int>> queue(3);

    int kh, kw;
    kh = kw = this->ksize / 2;
    for (int y = -kh; y <= kh; y++) {
        for (int x = -kw; x <= kw; x++) {
            const auto& src_p = src.at<cv::Vec3b>(uv[0]+y, uv[1]+x);

            for (int i = 0; i < 3; i++) {
                auto& queue_i = queue[i];
                auto& src_p_i = src_p[i];
                auto it = std::upper_bound(queue_i.cbegin(), queue_i.cend(), src_p_i);
                queue_i.insert(it, src_p_i);
            }
        }
    }

    auto& dst_p = dst.at<cv::Vec3b>(uv[0], uv[1]);
    for (int i = 0; i < 3; i++) {
        switch (this->mode) {
            case MIN_FILTER:
                dst_p[i] = queue[i][0];
                break;
            case MEDIAN_FILTER:
            {
                auto idx = queue[i].size() / 2;
                dst_p[i] = queue[i][idx];
            }
                break;
            case MAX_FILTER:
                dst_p[i] = queue[i][queue[i].size()-1];
                break;
        }
    }
}


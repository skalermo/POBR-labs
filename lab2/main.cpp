#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <vector>
#include "ConvFilter.h"
#include "RankFilter.h"

int main() {
    cv::Mat image = cv::imread("../Lena.bmp");

    cv::Mat blurResult;
    cv::Mat edgeDetectionResult;
    std::vector<std::vector<double>> kernelBlur = {{1, 1, 1},
                                                   {1, 1, 1},
                                                   {1, 1, 1}};
    std::vector<std::vector<double>> kernelEdgeDetection = {{-1, -1, -1},
                                                            {-1,  8, -1},
                                                            {-1, -1, -1}};
    ConvFilter(kernelBlur).apply(image, blurResult);
    ConvFilter(kernelEdgeDetection).apply(image, edgeDetectionResult);

    cv::Mat minFilterResult;
    cv::Mat medianFilterResult;
    cv::Mat maxFilterResult;
    RankFilter(7, MIN_FILTER).apply(image, minFilterResult);
    RankFilter(7, MEDIAN_FILTER).apply(image, medianFilterResult);
    RankFilter(7, MAX_FILTER).apply(image, maxFilterResult);

    cv::imshow("Lena", image);
    cv::imshow("blurResult", blurResult);
    cv::imshow("edgeDetectionResult", edgeDetectionResult);
    cv::imshow("minFilterResult", minFilterResult);
    cv::imshow("medianFilterResult", medianFilterResult);
    cv::imshow("maxFilterResult", maxFilterResult);

    cv::waitKey(-1);
    return 0;
}
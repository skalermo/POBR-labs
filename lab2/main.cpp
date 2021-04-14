#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <vector>
#include "ConvFilter.h"

int main() {
    std::vector<std::vector<double>> kernelBlur = {{1, 1, 1},
                                                   {1, 1, 1},
                                                   {1, 1, 1}};
    std::vector<std::vector<double>> kernelEdgeDetection = {{-1, -1, -1},
                                                            {-1,  8, -1},
                                                            {-1, -1, -1}};
    cv::Mat image = cv::imread("../Lena.bmp");
    cv::Mat blurResult;
    cv::Mat edgeDetectionResult;
    ConvFilter(kernelBlur).apply(image, blurResult);
    ConvFilter(kernelEdgeDetection).apply(image, edgeDetectionResult);
    cv::Mat result;
    cv::hconcat(image, blurResult, result);
    cv::hconcat(result, edgeDetectionResult, result);

//    cv::imshow("Lena", image);
    cv::imshow("Result", result);
    cv::waitKey(-1);
    return 0;
}
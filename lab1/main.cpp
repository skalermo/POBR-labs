#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <iomanip>

enum Quarter {
    Right, Bottom, Left, Top
};

void changeLightnessAndContrast(cv::Vec3b &pixel, double alpha, double beta) {
    pixel[0] = cv::saturate_cast<uchar>(pixel[0] * alpha + beta);
    pixel[1] = cv::saturate_cast<uchar>(pixel[1] * alpha + beta);
    pixel[2] = cv::saturate_cast<uchar>(pixel[2] * alpha + beta);
}

void changeContrast(cv::Vec3b &pixel) {
    const double alpha = 2.0;
    const int beta = -180;
    changeLightnessAndContrast(pixel, alpha, beta);
}

void changeLightness(cv::Vec3b &pixel) {
    const double alpha = 1.0;
    const int beta = 80;
    changeLightnessAndContrast(pixel, alpha, beta);
}

void changeHue(cv::Vec3b &pixel) {
    const double grey = (pixel[0] + pixel[1] + pixel[2]) / 3.0;
    const double r = pixel[2];
    pixel[0] = cv::saturate_cast<uchar>(r - grey);
    pixel[1] = cv::saturate_cast<uchar>(r - grey);
    pixel[2] = cv::saturate_cast<uchar>(r - grey);
}

void updateLightnessHist(std::vector<int> &lightnesses, cv::Vec3b &pixel) {
    const auto lightness = (pixel[0] + pixel[1] + pixel[2]) / 3;
    lightnesses[lightness / (256 / lightnesses.capacity())]++;
}

Quarter calculateQuarter(int y, int x, int _length, int height) {
    if (x >= y && height - y < x)
        return Right;
    if (x < y && height - y < x)
        return Bottom;
    if (x < y && height - y >= x)
        return Left;
    if (x >= y && height - y >= x)
        return Top;
    return Right;
}

void report(std::vector<int> &lightnesses, int pixelCount) {
    auto start = 0;
    for (auto li: lightnesses) {
        std::cout << "Count of pixels with lightness in range " << std::setw(5)
                  << start << " - " << std::setw(3) << start + 32 - 1 << ": " << std::setw(6) << li << std::endl;
        start += 32;
    }
    std::cout << "Total pixel count: " << pixelCount << std::endl;
}

cv::Mat &perform(cv::Mat &image) {
    CV_Assert(image.depth() != sizeof(uchar));
    CV_Assert(image.channels() == 3);
    const auto intervals = 8;
    std::vector<int> lightnesses(intervals);
    for (int y = 0; y < image.rows; ++y)
        for (int x = 0; x < image.cols; ++x) {
            updateLightnessHist(lightnesses, image.at<cv::Vec3b>(y, x));
            switch (calculateQuarter(y, x, image.rows, image.cols)) {
                case Right:
                    break;
                case Bottom:
                    changeLightness(image.at<cv::Vec3b>(y, x));
                    break;
                case Left:
                    changeHue(image.at<cv::Vec3b>(y, x));
                    break;
                case Top:
                    changeContrast(image.at<cv::Vec3b>(y, x));
                    break;
            }
        }
    report(lightnesses, image.rows * image.cols);
    return image;
}

int main() {
    cv::Mat image = cv::imread("Lena.png");
    perform(image);
    cv::imshow("Lena", image);
    cv::imwrite("Lena_new.png", image);
    cv::waitKey(-1);
    return 0;
}
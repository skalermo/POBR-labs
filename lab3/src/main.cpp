#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <vector>
#include <deque>
#include <tuple>
#include <bits/stdc++.h>

long m(int p, int q, const std::vector<std::tuple<int, int>> &targetPixels) {
    long res = 0;
    for (const auto tp : targetPixels) {
        int x = std::get<0>(tp);
        int y = std::get<1>(tp);
        res = res + static_cast<long>(std::pow(x, p) * std::pow(y, q));
    }
    return res;
}

double W3(int L, int S) {
    const double pi = 2 * acos(0.0);
    double res = static_cast<double>(L) / (2 * std::sqrt(pi * S)) - 1;
    return res;
}

long double M_11(long m_00, long m_01, long m_10, long m_11) {
    long double res = m_11 - (static_cast<long double>(m_10 * m_01) / m_00);
    return res;
}

long double M_20(long m_00, long m_10, long m_20) {
    long double res = m_20 - (static_cast<long double>(m_10 * m_10) / m_00);
    return res;
}

long double M_02(long m_00, long m_01, long m_02) {
    long double res = m_02 - (static_cast<long double>(m_01 * m_01) / m_00);
    return res;
}

long double M1(long double M_02, long double M_20, long m_00) {
    long double res = (M_20 + M_02) / (m_00 * m_00);
    return res;
}

long double M7(long double M_11, long double M_02, long double M_20, long m_00) {
    long double res = (M_20 * M_02 - M_11 * M_11) / std::pow(m_00, 4);
    return res;
}

bool areEqual(const cv::Vec3b &vec1, const cv::Vec3b &vec2) {
    return vec1[0] == vec2[0]
           && vec1[1] == vec2[1]
           && vec1[2] == vec2[2];
}

bool isBorderPixel(int x, int y, const cv::Mat &image, const cv::Vec3b &targetColor) {
    return (
            !areEqual(image.at<cv::Vec3b>(x - 1, y), targetColor)
            || !areEqual(image.at<cv::Vec3b>(x + 1, y), targetColor)
            || !areEqual(image.at<cv::Vec3b>(x, y - 1), targetColor)
            || !areEqual(image.at<cv::Vec3b>(x, y + 1), targetColor)
    );
}


void processBlackWhiteAndPrint(const std::string &filename) {
    cv::Mat image = cv::imread(filename);
    cv::Vec3b targetColor{0, 0, 0};
    cv::Vec3b fillColor{0, 255, 0};

    std::vector<std::tuple<int, int>> targetPixels;
    int S = 0;
    int L = 0;
    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            if (areEqual(image.at<cv::Vec3b>(x, y), targetColor)) {
                targetPixels.emplace_back(x, y);
                S++;
                if (isBorderPixel(x, y, image, targetColor))
                    L++;
            }
        }
    }
    long m_00 = m(0, 0, targetPixels);
    long m_01 = m(0, 1, targetPixels);
    long m_10 = m(1, 0, targetPixels);
    long m_11 = m(1, 1, targetPixels);
    long m_02 = m(0, 2, targetPixels);
    long m_20 = m(2, 0, targetPixels);
    long double M_11_ = M_11(m_00, m_01, m_10, m_11);
    long double M_02_ = M_02(m_00, m_01, m_02);
    long double M_20_ = M_20(m_00, m_10, m_20);
    // file, S, L, W3, M1, M7
    double W3_ = W3(L, S);
    long double M1_ = M1(M_02_, M_20_, m_00);
    long double M7_ = M7(M_11_, M_02_, M_20_, m_00);
    std::cout << "File: " << filename << ", "
              << "S=" << S << ", "
              << "L=" << L << ", "
              << "W3=" << W3_ << ", "
              << "M1=" << M1_ << ", "
              << "M7=" << M7_ << std::endl;
}

void task1(const std::vector<std::string> &filenames) {
    for (const auto &filename : filenames) {
        processBlackWhiteAndPrint(filename);
    }
}


int main() {
    std::vector<std::string> blackWhiteFiles{
            "../black-white/elipsa.dib",
            "../black-white/elipsa1.dib",
            "../black-white/kolo.dib",
            "../black-white/prost.dib",
            "../black-white/troj.dib",
    };
    std::vector<std::string> arrowFiles{
            "../arrows/strzalki_1.dib",
            "../arrows/strzalki_2.dib",
    };

//    std::cout << "Task1" << std::endl;
//    task1(blackWhiteFiles);



    cv::waitKey(-1);
    return 0;
}


//    // floodFill process starting from found pixel
//    std::deque<std::tuple<int, int>> toFill;
//    toFill.emplace_back(x0, y0);
//    while (!toFill.empty()) {
//        std::tuple<int, int> t = toFill.front();
//        int x = std::get<0>(t);
//        int y = std::get<1>(t);
//        toFill.pop_front();
//        cv::Vec3b curPixel = image.at<cv::Vec3b>(x, y);
//        if (!(targetColor == curPixel))
//            continue;
//        image.at<cv::Vec3b>(x, y) = fillColor;
//        toFill.emplace_back(x - 1, y);
//        toFill.emplace_back(x + 1, y);
//        toFill.emplace_back(x, y - 1);
//        toFill.emplace_back(x, y + 1);

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <vector>
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
    cv::Vec3b bgColor{0, 255, 0};

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

void processArrowsAndPrint(const std::string &filename) {
    cv::Mat image = cv::imread(filename);
    cv::Vec3b bgColor{255, 255, 255};

    std::vector<int> S(5, 0);
    std::vector<int> L(5, 0);
    std::vector<int> xmax(5, 0);
    std::vector<int> xmin(5, image.cols);
    std::vector<int> ymax(5, 0);
    std::vector<int> ymin(5, image.rows);

    std::vector<std::vector<std::tuple<int, int>>> targetPixels(5);
    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            cv::Vec3b curPixel = image.at<cv::Vec3b>(x, y);
            if (!areEqual(curPixel, bgColor)) {
                // use the fact that we know exactly
                // how red pixel value matches the arrows
                int arrowNr = static_cast<int>(static_cast<double>(curPixel[2]) / 45);
                targetPixels[arrowNr].emplace_back(x, y);
                S[arrowNr]++;
                if (isBorderPixel(x, y, image, curPixel))
                    L[arrowNr]++;
                if (xmax[arrowNr] < x)
                    xmax[arrowNr] = x;
                if (xmin[arrowNr] > x)
                    xmin[arrowNr] = x;
                if (ymax[arrowNr] < y)
                    ymax[arrowNr] = y;
                if (ymin[arrowNr] > y)
                    ymin[arrowNr] = y;
            }
        }
    }
    std::cout << "File: " << filename << std::endl;
    for (int k = 0; k < 5; k++) {
        long m_00 = m(0, 0, targetPixels[k]);
        long m_01 = m(0, 1, targetPixels[k]);
        long m_10 = m(1, 0, targetPixels[k]);
        long m_11 = m(1, 1, targetPixels[k]);
        long m_02 = m(0, 2, targetPixels[k]);
        long m_20 = m(2, 0, targetPixels[k]);
        int xmid = (xmax[k] + xmin[k]) / 2;
        int ymid = (ymax[k] + ymin[k]) / 2;
        int i = static_cast<int>(m_10 / m_00);
        int j = static_cast<int>(m_01 / m_00);

        int dx = xmid - i;
        int dy = ymid - j;
        const double pi = 2 * acos(0.0);
        double angle = atan2(dx, dy) * 180 / pi;

        long double M_11_ = M_11(m_00, m_01, m_10, m_11);
        long double M_02_ = M_02(m_00, m_01, m_02);
        long double M_20_ = M_20(m_00, m_10, m_20);

        double W3_ = W3(L[k], S[k]);
        long double M1_ = M1(M_02_, M_20_, m_00);
        long double M7_ = M7(M_11_, M_02_, M_20_, m_00);
        std::cout << "Arrow R=:" << k*45 << ", "
                  << "angle=" << angle << "deg, "
                  << "S=" << S[k] << ", "
                  << "L=" << L[k] << ", "
                  << "W3=" << W3_ << ", "
                  << "M1=" << M1_ << ", "
                  << "M7=" << M7_ << std::endl;
    }
}

void task1(const std::vector<std::string> &filenames) {
    for (const auto &filename : filenames) {
        processBlackWhiteAndPrint(filename);
    }
}

void task2(const std::vector<std::string> &filenames) {
    for (const auto &filename : filenames) {
        processArrowsAndPrint(filename);
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

    std::cout << "Task1" << std::endl;
    task1(blackWhiteFiles);
    std::cout << "Task2" << std::endl;
    task2(arrowFiles);

    cv::waitKey(-1);
    return 0;
}
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

int main() {
    cv::Mat image = cv::imread("../Lena.bmp");
//    perform(image);
    cv::imshow("Lena", image);
//    cv::imwrite("Lena_new.png", image);
    cv::waitKey(-1);
    return 0;
}
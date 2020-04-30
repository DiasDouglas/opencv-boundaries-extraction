#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include<vector>

using namespace cv;
using namespace std;

Mat src, dst;
int thresh = 100, maxLevel = 5;

void threshold_trackbar_callback(int, void*) {
    Mat binary;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    threshold(src, binary, thresh, 255, THRESH_BINARY);

    findContours(binary.clone(), contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    Mat drawing = Mat::zeros(src.size(), CV_8UC3);

    int largerContourAreaIndex = 0;

    for (int i = 0; i < contours.size(); i++) {
        if (contourArea(contours[i]) > contourArea(contours[largerContourAreaIndex])) {
            largerContourAreaIndex = i;
        }
    }

    Scalar color = Scalar(255, 255, 255);
    drawContours(drawing, contours, largerContourAreaIndex, color);

    imshow("Source", binary);
    imshow("Contours", drawing);
}

void max_level_trackbar_callback(int, void*) {
    Mat binary;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    threshold(src, binary, thresh, 255, THRESH_BINARY);

    findContours(binary.clone(), contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    Mat drawing = Mat::zeros(src.size(), CV_8UC3);

    int largerContourAreaIndex = 0;

    for (int i = 0; i < contours.size(); i++) {
        if (contourArea(contours[i]) > contourArea(contours[largerContourAreaIndex])) {
            largerContourAreaIndex = i;
        }
    }

    Scalar color = Scalar(255, 255, 255);
    drawContours(drawing, contours, largerContourAreaIndex, color, 1, 8, hierarchy, maxLevel);

    imshow("Source", binary);
    imshow("Contours", drawing);
}


int main()
{
    src = imread("Lenna.png");
    cvtColor(src, src, COLOR_BGR2GRAY);

    namedWindow("Source", WINDOW_AUTOSIZE);

    createTrackbar("Threshold", "Source", &thresh, 255, threshold_trackbar_callback);
    createTrackbar("Max Level", "Source", &maxLevel, 10, max_level_trackbar_callback);

    threshold_trackbar_callback(0, 0);
    max_level_trackbar_callback(0, 0);

    waitKey();

    return 0;
}


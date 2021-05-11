#include "lesson2.h"

#include <typeinfo>
#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/videoio.hpp>
#include <string>

using namespace cv;
using namespace std;


Mat addImages(Mat img1, Mat img2, float alpha)
{
    Mat dst;
    float beta = 1- alpha;
    addWeighted(img1, alpha, img2, beta, 0.0,dst);

}


Mat translation(Mat img, float x, float y)
{
    float data[6] = {1, 0, 100, 0, 1, 50};
    Mat M(2, 3, CV_32F, data);
    Mat imgT;
    warpAffine(img, imgT, M, cv::Size(img.rows, img.cols));
    return Mat imgT;
}

Mat rotation(Mat img, float angle)
{
    Point2f pc(img.cols/2, img.rows/2);
    Mat MR = getRotationMatrix2D(pc, angle, 1);
    Mat imgR;
    warpAffine(img, imgR, MR, image.size());
    return imgR;
}

Mat affineTransformation(Mat img, float * data1, float * data2)
{
    Mat pts1(3, 2, CV_32F, data1);
    Mat pts2(3, 2, CV_32F, data2);

    Mat AT = getAffineTransform(pts1, pts2);
    Mat imgA;
    warpAffine(img, imgA, AT, img.size());
    return imgA;
}

Mat perspectiveTransformation(Mat img, float * data1, float * data2)
{
    Mat pts1(4, 2, CV_32F, data1);
    Mat pts2(4, 2, CV_32F, data2);

    Mat MP = getPerspectiveTransform(pts1, pts2);
    Mat imgP;
    warpPerspective(img, imgP, MP, Size(300, 300));
    return imgP;
}


#include "lesson3.h"

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


Mat defaultBlur(Mat img, Size s)
{
    Mat imageBlur;
    blur(img, imageBlur, s);
    return imageBlur;
}

Mat gaussianBlur(Mat img, Size s)
{
    Mat imageBlur;
    GaussianBlur(img, imageBlur, s, 0);
    return imageBlur;
}
Mat medBlur(Mat img, int k)
{
    Mat imageBlur;
    medianBlur(img, imageMBlur, k);
    return imageBlur;
}
Mat bilateralFilter(Mat img, int k, float k1, float k2)
{
    Mat imageBFilter;
    bilateralFilter(img, imageBFilter, k, k1, k2);
    return imageBFilter;
}

Mat erosion(Mat img, Size s)
{
    Mat e;
    erode(img, e, getStructuringElement(MORPH_RECT, s));
    return e;
}

Mat dilate(Mat img, Size s)
{
    Mat d;
    dilate(img, d, getStructuringElement(MORPH_RECT, s));
    return d;
}   

Mat opening(Mat img, Size s)
{
    Mat o;
    Mat element = getStructuringElement(MORPH_RECT, s, Point(1,1));

    morphologyEx(img, o, MORPH_OPEN, element, Point(-1, -1), 2);
    return o;
}

Mat closing(Mat img, Size s)
{
    Mat c;
    Mat element = getStructuringElement(MORPH_RECT, s, Point(1,1));

    morphologyEx(img, c, MORPH_CLOSE, element, Point(-1, -1), 2);
    return c;
}

Mat gradient(Mat img, Size s)
{
    Mat g;
    Mat element = getStructuringElement(MORPH_RECT, s, Point(1,1));

    morphologyEx(img, g, MORPH_GRADIENT, element, Point(-1, -1), 2);
    return c;
}

Mat tophat(Mat img, Size s)
{
    Mat t;
    Mat element = getStructuringElement(MORPH_TOPHAT, s, Point(1,1));

    morphologyEx(img, t, MORPH_TOPHAT4, element, Point(-1, -1), 2);
    return c;
}

Mat blackhat(Mat img, Size s)
{
    Mat b;
    Mat element = getStructuringElement(MORPH_BLACKHAT, s, Point(1,1));

    morphologyEx(img, b, MORPH_BLACKHAT, element, Point(0, 0), 0);
    return c;
}


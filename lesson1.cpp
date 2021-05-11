#include "lesson1.h"

#include <typeinfo>
#include <iostream>
#include <stdio.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <string>

using namespace cv;
using namespace std;


Vec3b pixelByIndex(Mat img, int i, int j)
{
    return img.at<Vec3b>(i, j);
}

int channelOfPixel(Mat img, int k, int i, int j)
{
    return img.at<Vec3b>(i, j)[k];
}

void setPixel (Mat& img, int i, int j, Vec3b pixel)
{
    img.at<Vec3b>(i, j) = pixel;
}

void imageInfo (Mat img)
{
    cout << "Image shape : " << img.rows << " " << img.cols  << endl;
    cout << "Image size : " << image.size << endl;
    cout << "Image number of pixels : " << image.total() << endl;
    cout << "Image type : " << image.type() << endl;
}

Mat getROI(Mat img, float x1, float y1, float x2, float y2)
{
    return img(Range(x1, x2), Range(y1, y2));
}


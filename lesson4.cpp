#include "lesson4.h"

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

Mat laplacian(Mat img)
{
    Mat l;
    Laplacian(img, l, CV_64F);
    return l;
}

Mat sobelx(Mat img)
{
    Mat sx;
    Sobel(img, sx, CV_64F, 1, 0, 5);
    return sx;
}

Mat sobely(Mat img)
{
    Mat sy;
    Sobel(img, sy, CV_64F, 1, 0, 5);
    return sy;
}

Mat edges(Mat img)
{
    Mat e;
    Canny(img, e, 100, 200);
    return e;
}

Mat lowerReso(Mat img)
{
    Mat lr;
    pyrDown(img, lr);
    return lr;
}

Mat higherReso(Mat img)
{
    Mat hr;
    pyrUp(img, hr);
    return hr;
}

vector<vector<Point>> contours(Mat img)
{
    vector<vector<Point>> cs;
    findContours(img, cs, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    return cs;
}

Mat imageContours(Mat img)
{
    vector<vector<Point>> cs;
    findContours(img, cs, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

    Mat contourImage(image.size(), CV_8UC3, Scalar(0, 0, 0));
    Scalar colors[3];
    colors[0] = Scalar(255, 0, 0);
    colors[1] = Scalar(0, 255, 0);
    colors[2] = Scalar(0, 0, 255);


    for (int i = 0; i < cs.size(); i++)
    {
        drawContours(contourImage, cs, i, colors[i%3]);
    }

    return contourImage;
}


void contoursInfo(Mat img)
{
    vector<vector<Point>> cs;
    findContours(img, cs, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

    vector<Moments> mu(contours.size() );
    vector<Point2f> mc(contours.size());

    for (int i = 0; i < contours.size(); i++)
    {
        mu[i] = moments(contours[i], false);
        mc[i] = Point2f(mu[i].m10/mu[i].m00, mu[i].m01/mu[i].m00);

        cout << "Countor #"  << i <<  endl;
        cout << "Countor size : " << contours[i].size() <<endl;
        cout << "Momemnts : " << mc[i] << endl;

        cout << "Area : " << mu[i].m00 << endl;
        cout << "Perimetr : " << arcLength(contours[i], true) << endl;
        cout << isContourConvex(contours[i]) << endl;

        Rect rect = boundingRect(contours[i]);

        cout << "Aspect ratio : " << float(rect.width) / rect.height << endl;
        cout << "Exctent : " << float(mu[i].m00) / (rect.width * rect.height) << endl;
        

        cout << "Equivalent Diametr : " << sqrt(4/mu[i].m00 / 3.14) << endl;

        if (sqrt(4/mu[i].m00 / 3.14) < INT_MAX && contours[i].size() >= 5)
        {
            RotatedRect box = fitEllipse(contours[i]);
            cout << "Angle of orientation : " << box.angle << endl;
        }

        cout << "----------------------------------------------" << endl;

    }
}
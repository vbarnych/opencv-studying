void template(Mat img, Mat temp)
{
    int h = temp.rows;
    int w = temp.cols;
    const int methods[6] = {TM_CCOEFF, TM_CCOEFF_NORMED, TM_CCORR, TM_CCORR_NORMED, TM_SQDIFF, TM_SQDIFF_NORMED};

    for (int i = 0; i < 6; i++)
    {
        Mat image = img.clone();
        Mat res;
        matchTemplate(image, temp, res, methods[i]);

        double minVal; double maxVal; Point minLoc; Point maxLoc;
        minMaxLoc(res, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
        Point top_left, bottom_right;
        if (i == 4 || i == 5)
        {   
            top_left = minLoc;
        }
        else
        {
            top_left = maxLoc;
        }
        
        bottom_right = Point(top_left.x + w, top_left.y + h);
        rectangle(image, top_left, bottom_right, Scalar::all(0), 2, 8, 0 );
        rectangle(res, top_left, bottom_right, Scalar::all(0), 2, 8, 0 );

        imshow(to_string(i).c_str() , image);

        waitKey(0);

    }
}

void templates(Mat img, Mat temp)
{
    int w = temp.cols;
    int h = temp.rows;
    
    Mat res;

    matchTemplate(img, temp, res, TM_CCOEFF_NORMED);
    float thresh = 0.8;
    threshold(res, res, thresh, 1.0, THRESH_BINARY);

    Mat1b resb;
    res.convertTo(resb, CV_8U, 255);

    vector<vector<Point>> contours;
    findContours(resb, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

    for (int i = 0; i < contours.size(); ++i)
    {
        Mat1b mask(res.rows, res.cols, uchar(0));
        drawContours(mask, contours, i, Scalar(255), CV_FILLED);

        Point max_point;
        double max_val;

        minMaxLoc(res, NULL, &max_val, NULL, &max_point, mask);
        rectangle(img, Rect(max_point.x, max_point.y, temp.cols, temp.rows), Scalar(0, 255, 0), 2);
    }
    
    imshow("1", img); 
}

 void houghLines(Mat & img)
{
    Mat edges;
    Canny(img, edges, 100, 200, 3);
    
    vector<Vec2f> lines; // will hold the results of the detection

    HoughLines(edges, lines, 1, CV_PI/180, 200, 0, 0 ); 
    cout << "Total number of lines : " << lines.size() << endl;

    for (int i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0];
        float theta = lines[i][1];

        float a = cos(theta);
        float b = sin(theta);
        float x0 = a*rho;
        float y0 = b*rho;
        
        float x1 = (int)(x0 + 1000*(-b));
        float y1 = (int)(y0 + 1000*a);
        float x2 = (int)(x0 - 1000*(-b));
        float y2 = (int)(y0 - 1000*a);


        line(img, Point(x1, y1), Point(x2, y2), Scalar(0, 0, 255), 2, LINE_AA);
    }
    
}

void houghLinesP(Mat & img)
{
    Mat edges;
    Canny(img, edges, 100, 200, 3);
    
    vector<Vec4i> lines;
    int maxLineLength = 100;
    int minLineLength = 10;

    HoughLinesP(edges, lines, 1, CV_PI/180, 200, maxLineLength, minLineLength);
    cout << "Total number of lines : " << lines.size() << endl;

    for (int i = 0; i < lines.size(); i++)
    {

        float x1 = lines[i][0];
        float y1 = lines[i][1];
        float x2 = lines[i][2];
        float y2 = lines[i][3]; 

        line(img, Point(x1, y1), Point(x2, y2), Scalar(0, 0, 255), 2, LINE_AA);
    }
}

void houghCircles(Mat & img)
{
    Mat image = img.clone();
    medianBlur(image, image, 5);
    vector<Vec3f> circles;
    HoughCircles(image, circles, HOUGH_GRADIENT, 1, image.rows/16, 100, 30, 1, 30);
    

    for (int i = 0; i < circles.size(); i++)
    {
        Point center = Point(circles[i][0], circles[i][1]);


        circle(imageG, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
        int radius = circles[i][2];
        circle(imageG, center, radius, Scalar(255, 0, 255), 3, LINE_AA);
    
    }
    cout << circles.size() << endl;
}

void segmentation(Mat & img)
{
    Mat element = getStructuringElement(MORPH_RECT, Size(9,9), Point(1,1));
    threshold(img, img, 0,  255, THRESH_BINARY_INV+THRESH_OTSU);

    imshow("2", img);

    Mat opening;
    morphologyEx(img, opening, MORPH_OPEN, element, Point(-1, -1), 2);

    Mat sure_bg;
    dilate(opening, sure_bg, getStructuringElement(MORPH_RECT, Size(3, 3)));

    imshow("sure_bg", sure_bg);

    Mat dist;
    distanceTransform(opening, dist, DIST_L2, 3);

    Mat sure_fg;

    double minVal; 
    double maxVal; 
    Point minLoc; 
    Point maxLoc;
    minMaxLoc( dist, &minVal, &maxVal, &minLoc, &maxLoc );

    cout << maxVal << endl;
    threshold(dist, sure_fg, 0.7*maxVal, 255, 0);    

    imshow("sure_fg", sure_fg);

    Mat markers(image.size(), CV_32S);

    int nLabels = connectedComponents(100, markers, 8);

    Mat unknown;

    //subtract(sure_bg, sure_fg, unknown);

    //cout << markers.size() << endl;*/

    /*for (int i = 0; i < markers.rows; i++) 
    {
        for (int j = 0; j < markers.cols; j++) 
        {
            markers.intPtr(i, j)[0] = markers.ucharPtr(i, j)[0] + 1;
            if (unknown.ucharPtr(i, j)[0] == 255) 
            {
                markers.intPtr(i, j)[0] = 0;
            }
        }
    }
    cvtColor(image, image, COLOR_RGBA2RGB, 0);
    watershed(image, markers);
// draw barriers
    for (int i = 0; i < markers.rows; i++) 
    {
        for (int j = 0; j < markers.cols; j++) 
        {
            if (markers.intPtr(i, j)[0] == -1) 
            {
                image.ucharPtr(i, j)[0] = 255; // R
                image.ucharPtr(i, j)[1] = 0; // G
                image.ucharPtr(i, j)[2] = 0; // B
            }
        }
    }*/
}

void findCorners(Mat & img)
{
    vector <Point2f> centers;

    findChessboardCorners(img, Size(7, 7), centers);
    cout << centers << endl;
    cout << centers.size() << endl;
    drawChessboardCorners(img, Size(7, 7), Mat(centers), true);
}
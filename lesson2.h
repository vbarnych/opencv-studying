Mat addImages(Mat img1, Mat img2, float alpha);
Mat translation(Mat img, float x, float y);
Mat rotation(Mat img, float angle);
Mat affineTransformation(Mat img, float * data1, float * data2);
Mat perspectiveTransformation(Mat img, float * data1, float * data2);


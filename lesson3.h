Mat defaultBlur(Mat img, Size s);
Mat gaussianBlur(Mat img, Size s);
Mat medBlur(Mat img, int k);
Mat bilateralFilter(Mat img, int k, float k1, float k2);
Mat erosion(Mat img, Size s);
Mat dilate(Mat img, Size s);
Mat opening(Mat img, Size s);
Mat closing(Mat img, Size s);
Mat gradient(Mat img, Size s);
Mat tophat(Mat img, Size s);
Mat blackhat(Mat img, Size s);


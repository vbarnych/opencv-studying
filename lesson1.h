Vec3b pixelByIndex(Mat img, int i, int j);
int channelOfPixel(Mat img, int k, int i, int j);
void setPixel (Mat& img, int i, int j, Vec3b pixel);
void imageInfo (Mat img);
Mat getROI(Mat img, float x1, float y1, float x2, float y2);

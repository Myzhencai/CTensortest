// // import cv2
// #include <opencv2/opencv.hpp>
// #include <opencv2/imgproc.hpp>
// #include <iostream>
// #include <math.h>
// #include <stdio.h>
// #include <iostream>
// #include <stdio.h>
// #include <stdlib.h>
// #include <cstdlib>
// #include <cassert>

// using namespace cv;
// using namespace std;


// int main(){
//     Mat im = imread( "/home/gaofei/GFT-master2/each2.jpg", IMREAD_GRAYSCALE );
// // image = cv2.imread("/home/gaofei/GFT-master2/each1.jpg", cv2.IMREAD_GRAYSCALE)
// // blur = cv2.medianBlur(image, 3) //感觉不需要进行blur
// // gray = blur
// Mat blur;
// GaussianBlur(im,blur,Size(3,3),0);
// 	// Canny(image,image,100,250);
// vector<vector<Point>> contours;
// vector<Vec4i> hierarchy;
// Mat thresh;
// threshold(blur,thresh,180,250,THRESH_BINARY);
// // imshow("1",thresh);
// // waitKey(0);
// findContours(thresh,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE,Point());

// // thresh = cv2.threshold(gray,200,255, cv2.THRESH_BINARY)[1]


// cnts = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
// cnts = cnts[0] if len(cnts) == 2 else cnts[1]

// min_area = 16
// white_dots = []
// for c in cnts:
//     area = cv2.contourArea(c)
//     if area > min_area:
//         cv2.drawContours(image, [c], -1, (255, 255, 255), 1)
//         white_dots.append(c)

// print(len(white_dots))
// cv2.imshow('thresh', thresh)
// cv2.imshow('image', image)
// cv2.imwrite('image.png', image)
// cv2.waitKey()
// return 0;
// }

#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
 
using namespace std; 
using namespace cv;  
 
int main()  
{
	Mat imageSource=imread("/home/gaofei/GFT-master2/each2.jpg",IMREAD_GRAYSCALE);
	imshow("Source Image",imageSource);
	Mat image;
	GaussianBlur(imageSource,image,Size(3,3),0);
    imshow("Gaussian Image",image);
	Canny(image,image,188,255);
    imshow("Canny Image",image);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(image,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE,Point());
    for (int c = 0; c < contours.size(); ++c)
    {
	cv::RotatedRect rotateRect = cv::minAreaRect(contours[c]);//轮廓最小外接矩形
	Point pnt = Point(rotateRect.center.x, rotateRect.center.y);//最小外接矩形的中心点坐标
	//画出最小外接矩形
	cv::Point2f rect_points[4];
	rotateRect.points(rect_points);
    }
	waitKey(0);
	return 0;
}

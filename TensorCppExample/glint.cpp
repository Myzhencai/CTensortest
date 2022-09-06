#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <cassert>
 
using namespace cv;
using namespace std;
 
Mat src_img, binary_img, dst_img;
int main()
{

	/*   
		params.minThreshold = 10;
6
	params.maxThreshold = 200;
7
	 
8
	// Filter by Area.
9
	params.filterByArea = true;
10
	params.minArea = 1500;
11
	 
12
	// Filter by Circularity
13
	params.filterByCircularity = true;
14
	params.minCircularity = 0.1;
15
	 
16
	// Filter by Convexity
17
	params.filterByConvexity = true;
18
	params.minConvexity = 0.87;
19
	 
20
	// Filter by Inertia
21
	params.filterByInertia = true;
22
	params.minInertiaRatio = 0.01;
23
	             
	*/
	// Setup SimpleBlobDetector parameters.

	SimpleBlobDetector::Params params;
	// Change thresholds
	// params.minThreshold = 180;
	// params.maxThreshold = 255;
	 
	// // Filter by Area.
	// params.filterByArea = true;
	// params.minArea = 15000;
	// // params.maxArea = 32;
	// // Filter by CircularityS
	// params.filterByCircularity = true;
	// params.minCircularity = 0.8;
	// params.minCircularity = 1;

	// // Filter by Convexity
	// params.filterByConvexity = true;
	// params.minConvexity = 0.8;

	// // Filter by Inertia
	// params.filterByInertia = true;
	// params.minInertiaRatio = 0.8;

	// // Filter by Color
	// params.filterByColor = true;
	// params.blobColor = 255;


    params.minThreshold = 180;
	params.maxThreshold = 255;
	// Filter by Area.
	params.filterByArea = true;
	params.minArea = 20;
	// Filter by Circularity
	params.filterByCircularity = true;
	params.minCircularity = 0.9;
	params.maxCircularity = 1;
	// Filter by Convexity
	params.filterByConvexity = true;
	params.minConvexity = 0.9;
	params.maxConvexity = 1;
	// Filter by Inertia
	params.filterByInertia = true;
	params.minInertiaRatio = 0.9;
	params.maxInertiaRatio = 1;
	// Filter by Color
	params.filterByColor = true;
	params.blobColor = 255;

	#if CV_MAJOR_VERSION < 3   // If you are using OpenCV 2

	  // Set up detector with params

	  SimpleBlobDetector detector(params);
	 
	  // You can use the detector this way
	  // detector.detect( im, keypoints);

	#else
	  // Set up detector with params
	  Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

	  // SimpleBlobDetector::create creates a smart pointer.

	  // So you need to use arrow ( ->) instead of dot ( . )

	  // detector->detect( im, keypoints);

	#endif





	// Read image
	Mat im = imread( "/home/gaofei/GFT-master2/each2.jpg", IMREAD_GRAYSCALE );
	// Set up the detector with default parameters.
	detector = SimpleBlobDetector::create();
	// Detect blobs.
	std::vector<KeyPoint> keypoints;
	detector->detect( im, keypoints);
	// Draw detected blobs as red circles.
	// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
	Mat im_with_keypoints;
	drawKeypoints( im, keypoints, im_with_keypoints, Scalar(0,255,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
	// Show blobs
	imshow("keypoints", im_with_keypoints );
	waitKey(0);
	// //灰度读取，在读入图像的同时进行色彩转换，这可以提高运行速度并减少内存的使用
	// if (src_img.empty())
	// {
	// 	printf("could not load the image...\n");     
	// 	return -1;
	// }
	// namedWindow("原图", CV_WINDOW_AUTOSIZE);
	// imshow("原图", src_img);
 
	// // 图像二值化
	// threshold(src_img, binary_img, 0, 255, THRESH_BINARY | THRESH_OTSU);
	// imshow("二值图像", binary_img);
 
	// // 形态学操作
	// Mat kernel = getStructuringElement(MORPH_RECT, Size(1, 1), Point(-1, -1));   // 构建形态学操作的结构元
	// morphologyEx(binary_img, dst_img, MORPH_CLOSE, kernel, Point(-1, -1));      //闭操作
	// imshow("闭操作", dst_img);
 
	// kernel = getStructuringElement(MORPH_RECT, Size(1,1), Point(-1, -1));     // 构建形态学操作的结构元
	// morphologyEx(dst_img, dst_img, MORPH_OPEN, kernel, Point(-1, -1));                 //开操作
	// imshow("开操作", dst_img);
 
	// // 寻找轮廓
	// vector<vector<Point>> contours;
	// vector<Vec4i> hireachy;
	// findContours(dst_img, contours, hireachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
 
	// Mat result_img = Mat::zeros(src_img.size(), CV_8UC3);     // 创建与原图同大小的黑色背景
	// Point circle_center;              //定义圆心坐标
	// for (auto t = 0; t < contours.size(); ++t)
	// {
	// 	// 面积过滤
	// 	double area = contourArea(contours[t]);     //计算点集所围区域的面积
	// 	if (area < 10)            //晒选出轮廓面积大于100的轮廓
	// 		continue;
	// 	// 横纵比过滤
	// 	Rect rect = boundingRect(contours[t]);            // 求点集的最小直立外包矩形
	// 	float ratio = float(rect.width) / float(rect.height);        //求出宽高比
 
	// 	if (ratio < 1.1 && ratio > 0.9)       //因为圆的外接直立矩形肯定近似于一个正方形，因此宽高比接近1.0
	// 	{ 
	// 		drawContours(result_img, contours, t, Scalar(0, 0, 255), -1, 8, Mat(), 0, Point());    //在黑色背景图上画出圆，注意其中参数-1的意义
	// 		printf("圆的面积: %f\n", area);
	// 		double arc_length = arcLength(contours[t], true);         //计算点集所围区域的周长
	// 		printf("圆的周长 : %f\n", arc_length);
	// 		int x = rect.x + rect.width / 2;
	// 		int y = rect.y + rect.height / 2;
	// 		circle_center = Point(x, y);          //得到圆心坐标
	// 		cout << "圆心坐标：" << "宽"<<circle_center.x<<" "<<"高"<< circle_center.y << endl;
	// 		circle(result_img, circle_center, 2, Scalar(0, 255, 255), 2, 8, 0);  
	// 	}
	// }
	// imshow("结果", result_img);
 
	// Mat circle_img = src_img.clone();
	// cvtColor(circle_img, circle_img, COLOR_GRAY2BGR);    //灰度图转化为彩色图
	// circle(circle_img, circle_center, 2, Scalar(0, 0, 255), 2, 8, 0);    //在原图上画出圆心
	// imshow("最终结果", circle_img);
 
	// waitKey(0);
	return 0;
}

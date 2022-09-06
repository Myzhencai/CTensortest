// #include <iostream>
// #include <stdio.h>
// #include <stdlib.h>
// #include <opencv/cv.h>
// #include <opencv2/opencv.hpp>
// #include <opencv/highgui.h>
// #include <tensorflow/core/framework/tensor_shape.h>
// #include "tensorflow/cc/ops/const_op.h"
// #include "tensorflow/core/kernels/image/image_ops.h"
// #include "tensorflow/cc/ops/standard_ops.h"
// #include "tensorflow/core/framework/graph.pb.h"
// #include "tensorflow/core/framework/tensor.h"
// #include "tensorflow/core/graph/default_device.h"
// #include "tensorflow/core/graph/graph_def_builder.h"
// #include "tensorflow/core/lib/core/errors.h"
// #include "tensorflow/core/lib/core/stringpiece.h"
// #include "tensorflow/core/lib/core/threadpool.h"
// #include "tensorflow/core/lib/io/path.h"
// #include "tensorflow/core/lib/strings/stringprintf.h"
// #include "tensorflow/core/platform/env.h"
// #include "tensorflow/core/platform/init_main.h"
// #include "tensorflow/core/platform/logging.h"
// #include "tensorflow/core/platform/types.h"
// #include "tensorflow/core/public/session.h"
// #include "tensorflow/core/util/command_line_flags.h"

// using namespace std;
// using namespace cv;
// using namespace tensorflow;


// // 定义一个函数讲OpenCV的Mat数据转化为tensor，python里面只要对cv2.read读进来的矩阵进行np.reshape之后，
// // 数据类型就成了一个tensor，即tensor与矩阵一样，然后就可以输入到网络的入口了，但是C++版本，我们网络开放的入口
// // 也需要将输入图片转化成一个tensor，所以如果用OpenCV读取图片的话，就是一个Mat，然后就要考虑怎么将Mat转化为
// // Tensor了
// void CVMat_to_Tensor(Mat img,Tensor* output_tensor,int input_rows,int input_cols)
// {
//     //imshow("input image",img);
//     //图像进行resize处理
//     resize(img,img,cv::Size(input_cols,input_rows));
//     //imshow("resized image",img);

//     //归一化
//     img.convertTo(img,CV_32FC1);  // CV_32FC3
//     //img=1-img/255;
 
//     //创建一个指向tensor的内容的指针
//     float *p = output_tensor->flat<float>().data();
 
//     //创建一个Mat，与tensor的指针绑定,改变这个Mat的值，就相当于改变tensor的值
//     cv::Mat tempMat(input_rows, input_cols, CV_32FC1, p);
//     img.convertTo(tempMat,CV_32FC1);
//  //    waitKey(0);
 
// }
 
// int main()
// {
//     /*--------------------------------配置关键信息------------------------------*/
//     //我们训练好的tf2.x的对应模型的参数
//     string model_path="/home/gaofei/GFT-master2/model6/frozen_model.pb";
//     //我们需要验证的图像位置
//     string image_path="/home/gaofei/GFT-master2/test.jpg";
//     int input_height = 240;
//     int input_width = 320;
//     string input_tensor_name="Input:0";
//     string output_tensor_name="Inference/Output:0";//后续可以将亮斑位置的事情集合到深度学习中
 
//     /*--------------------------------创建session------------------------------*/
//     Session* session;
//     Status status = NewSession(SessionOptions(), &session);//创建新会话Session
 
//     /*--------------------------------从pb文件中读取模型--------------------------------*/
//     GraphDef graphdef; //Graph Definition for current model
 
//     Status status_load = ReadBinaryProto(Env::Default(), model_path, &graphdef); //从pb文件中读取图模型;
//     if (!status_load.ok()) {
//         cout << "ERROR: Loading model failed..." << model_path << std::endl;
//         cout << status_load.ToString() << "\n";
//         return -1;
//     }
//     Status status_create = session->Create(graphdef); //将模型导入会话Session中;
//     if (!status_create.ok()) {
//         cout << "ERROR: Creating graph in session failed..." << status_create.ToString() << std::endl;
//         return -1;
//     }
//     cout << "<----Successfully created session and load graph.------->"<< endl;
 
//     /*---------------------------------载入测试图片-------------------------------------*/
//     cout<<endl<<"<------------loading test_image-------------->"<<endl;
//     Mat img;
//     //注意读取图片的模式是0
//     img = imread(image_path,0);
    
//     if(img.empty())
//     {
//         cout<<"can't open the image!!!!!!!"<<endl;
//         return -1;
//     }

//     // imshow("1", img);
//     // cvWaitKey(0);
 
//     //创建一个tensor作为输入网络的接口
//     Tensor resized_tensor(DT_FLOAT, TensorShape({1,input_height,input_width,1})); //DT_FLOAT DT_UINT8

 
//     // // //将Opencv的Mat格式的图片存入tensor
//     CVMat_to_Tensor(img,&resized_tensor,input_height,input_width);

 
//     // // /*-----------------------------------用网络进行测试-----------------------------------------*/
//     cout<<endl<<"<-------------Running the model with test_image--------------->"<<endl;
//     // 前向运行，输出结果一定是一个tensor的vector
//     vector<tensorflow::Tensor> outputs;
//     // tensorflow::Tensor outputs;
 
//     Status status_run = session->Run({{input_tensor_name, resized_tensor}}, {output_tensor_name}, {}, &outputs);
//     if (!status_run.ok()) {
//         cout << "ERROR: RUN failed..."  << std::endl;
//         cout << status_run.ToString() << "\n";
//         return -1;
//     }
//     auto test_value = outputs[0].tensor<float,4>();
//     // 对每一个输出的图像提取对应的亮斑位置    
//     int img_input_height = outputs[0].dim_size(1);
//     int img_input_width = outputs[0].dim_size(2);
//     int glint_num = outputs[0].dim_size(3);
//     for(int i=0;i<glint_num;i++){
//         Mat tmp_img(240, 320, CV_32FC1, cv::Scalar(0));
//         for(int j=0;j<img_input_height;j++){
//             for(int k=0;k<img_input_width;k++){
//                 tmp_img.ptr<float>(j)[k]=test_value(0,j,k,i);
//             }
//         }
//         tmp_img.convertTo(tmp_img,CV_8UC1);
//         Mat image;
// 	    GaussianBlur(tmp_img,image,Size(3,3),0);
//         Mat thresh;
//         threshold(image,thresh,168,250,THRESH_BINARY);
//         imshow("Gaussian Image",image);
//         imshow("Thread Image",thresh);
//         // image= mat2D3;
//         Canny(thresh,thresh,168,255);
//         imshow("Canny Image",thresh);
//         vector<vector<Point>> contours;
//         vector<Vec4i> hierarchy;
//         findContours(thresh,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE,Point());
//         for (int c = 0; c < contours.size(); ++c)
//         {
//         cv::RotatedRect rotateRect = cv::minAreaRect(contours[c]);//轮廓最小外接矩形
//         Point pnt = Point(rotateRect.center.x, rotateRect.center.y);//最小外接矩形的中心点坐标
//         cout<<"x"<<rotateRect.center.x<<endl;
//         cout<<"y"<<rotateRect.center.y<<endl;
//         }
//         waitKey(0);

//     }

// 	return 0;
// }
 

#include "TfGlint.h"

int main(){
    string model_path="/home/gaofei/GFT-master2/model6/frozen_model.pb";
    string image_path="/home/gaofei/GFT-master2/test.jpg";
    Mat testimg;
    //注意读取图片的模式是0
    testimg = imread(image_path,0);

    TfGlint testTfGlint = TfGlint(model_path,testimg);
    testTfGlint.loadmodel();
    testTfGlint.createintensor();
    testTfGlint.predict();
    return 0;
}
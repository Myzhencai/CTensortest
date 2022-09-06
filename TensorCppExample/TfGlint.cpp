#include "TfGlint.h"

TfGlint::TfGlint(string modelPath,Mat inputMat){
  model_path=modelPath;
  input_mat=inputMat;
}

TfGlint::~TfGlint(){

}

int TfGlint::loadmodel(){
  Status status = NewSession(SessionOptions(), &session);
  Status status_load = ReadBinaryProto(Env::Default(), model_path, &graphdef); //从pb文件中读取图模型;
  if (!status_load.ok()) {
      cout << "ERROR: Loading model failed..." << model_path << std::endl;
      cout << status_load.ToString() << "\n";
      return -1;
  }
  Status status_create = session->Create(graphdef); //将模型导入会话Session中;
  if (!status_create.ok()) {
      cout << "ERROR: Creating graph in session failed..." << status_create.ToString() << std::endl;
      return -1;
  }
  return 0;
}


void TfGlint::CVMat_to_Tensor(Mat img,Tensor* output_tensor,int input_rows,int input_cols)
{
    //imshow("input image",img);
    //图像进行resize处理
    resize(img,img,cv::Size(input_cols,input_rows));
    //imshow("resized image",img);

    //归一化
    img.convertTo(img,CV_32FC1);  // CV_32FC3
    //img=1-img/255;
 
    //创建一个指向tensor的内容的指针
    float *p = output_tensor->flat<float>().data();
 
    //创建一个Mat，与tensor的指针绑定,改变这个Mat的值，就相当于改变tensor的值
    cv::Mat tempMat(input_rows, input_cols, CV_32FC1, p);
    img.convertTo(tempMat,CV_32FC1);
 //    waitKey(0);
 
}
	
int TfGlint::createintensor(){
  if(input_mat.empty())
    {
        cout<<"can't open the image!!!!!!!"<<endl;
        return -1;
    }
  Tensor inputTensor(DT_FLOAT, TensorShape({1,input_height,input_width,1}));
  input_tensor=inputTensor;
  CVMat_to_Tensor(input_mat,&input_tensor,input_height,input_width);
  return 0;
}
	
int TfGlint::predict(){
  Status status_run = session->Run({{input_tensor_name, input_tensor}}, {output_tensor_name}, {}, &outputs);
    if (!status_run.ok()) {
        cout << "ERROR: RUN failed..."  << std::endl;
        cout << status_run.ToString() << "\n";
        return -1;
    }
    auto test_value = outputs[0].tensor<float,4>();
    // 对每一个输出的图像提取对应的亮斑位置    
    int img_input_height = outputs[0].dim_size(1);
    int img_input_width = outputs[0].dim_size(2);
    int glint_num = outputs[0].dim_size(3);
    cout<<"glint_num"<<glint_num<<endl;
    for(int i=0;i<glint_num;i++){
        Mat tmp_img(240, 320, CV_32FC1, cv::Scalar(0));
        for(int j=0;j<img_input_height;j++){
            for(int k=0;k<img_input_width;k++){
                //此处这么处理是为了避免图像的数值超过255先用float对应float然后在转为int
                tmp_img.ptr<float>(j)[k]=test_value(0,j,k,i);
            }
        }
        tmp_img.convertTo(tmp_img,CV_8UC1);
        Mat image;
	      GaussianBlur(tmp_img,image,Size(3,3),0);
        Mat thresh;
        threshold(image,thresh,168,250,THRESH_BINARY);
        imshow("Source Image",tmp_img);
        imshow("Gaussian Image",image);
        imshow("Thread Image",thresh);
        // image= mat2D3;
        Canny(thresh,thresh,168,255);
        imshow("Canny Image",thresh);
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(thresh,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE,Point());
        if(contours.size()==0){
          glintPoints.push_back(cv::Point2d(0.0, 0.0));
        }else{
          for (int c = 0; c < 1; ++c){ //将contours.size()换成1默认为神经网络的输出只有一个亮点可能会用问题与网络强相关
          cv::RotatedRect rotateRect = cv::minAreaRect(contours[c]);//轮廓最小外接矩形
          Point pnt = Point(rotateRect.center.x, rotateRect.center.y);//最小外接矩形的中心点坐标
          cout<<"x"<<rotateRect.center.x<<endl;
          cout<<"y"<<rotateRect.center.y<<endl;
          glintPoints.push_back(cv::Point2d(rotateRect.center.x, rotateRect.center.y));
          }
        }
        
        
        waitKey(0);
    }
  for(int i=0;i< glint_num;i++){
    cout<<"x"<<glintPoints[i].x<<"y"<<glintPoints[i].y<<endl;
  }

	return 0;

}

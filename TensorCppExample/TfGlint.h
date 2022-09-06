#ifndef TF_GLINT_H
#define TF_GLINT_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <tensorflow/core/framework/tensor_shape.h>
#include "tensorflow/cc/ops/const_op.h"
#include "tensorflow/core/kernels/image/image_ops.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/framework/graph.pb.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/graph/default_device.h"
#include "tensorflow/core/graph/graph_def_builder.h"
#include "tensorflow/core/lib/core/errors.h"
#include "tensorflow/core/lib/core/stringpiece.h"
#include "tensorflow/core/lib/core/threadpool.h"
#include "tensorflow/core/lib/io/path.h"
#include "tensorflow/core/lib/strings/stringprintf.h"
#include "tensorflow/core/platform/env.h"
#include "tensorflow/core/platform/init_main.h"
#include "tensorflow/core/platform/logging.h"
#include "tensorflow/core/platform/types.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/util/command_line_flags.h"

using namespace std;
using namespace cv;
using namespace tensorflow;


class TfGlint
{
public:
	//FrameProcessor(mc::ReaderWriterQueue<TBinocularFrame *>* in, mc::ReaderWriterQueue<TBinocularFrame *>* out);
//	FrameProcessor(concurrent_queue<std::shared_ptr<TBinocularFrame>>* in,
//					concurrent_queue<std::shared_ptr<TBinocularFrame>>* out);
	TfGlint(string modelPath,Mat inputMat);

	~TfGlint();

	/**
	Starts up the FrameProcessor
	*/
	int loadmodel();
	void CVMat_to_Tensor(Mat img,Tensor* output_tensor,int input_rows,int input_cols);
	int createintensor();
	int predict();

private:
    string model_path;
	Mat input_mat;
    int input_height = 240;
    int input_width = 320;
    string input_tensor_name="Input:0";
    string output_tensor_name="Inference/Output:0";
    Session* session;
	GraphDef graphdef;
	Tensor input_tensor;
	vector<tensorflow::Tensor> outputs;
	//需要配合更改之前是6个点一定非要有位置才能计算现在需要判定这个vector里只要有效的两个就可以开始计算结果
	std::vector<cv::Point2d> glintPoints;
};


#endif
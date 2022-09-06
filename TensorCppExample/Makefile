# compiler flags
CC=g++
CCnew=/usr/bin/c++
INC_DIRS= -I/usr/local/include/ -I/usr/local/include/opencv/ -I/home/gaofei/Tensorflow2/eigen3/ -I/home/gaofei/Tensorflow2/tensorflow-2.8.0/ -I/home/gaofei/Tensorflow2/tensorflow-2.8.0/bazel-bin/ -I/home/gaofei/Tensorflow2/abseil-cpp/
#INC_DIRS= -I../ -I/usr/local/include/eigen3 -I/usr/local/include/
#INC_DIRS= -I../ -I/usr/local/include/ -I/usr/local/include/eigen3 -Iboost_dir
#INC_DIRS= -I../ -I/usr/local/include/ -Ieigen_dir -Iboost_dir
#INCS=$(foreach d, $INC_DIR, -I$d)
CFLAGS = -c -g -std=c++1y $(INC_DIRS) -Wfatal-errors #-Wall
#RELEASE: LDFLAGS= -L/usr/local/lib/boost/ -L/usr/local/lib/ -L/usr/local/eigen3 -L/usr/local/opencv3/release/lib/
LDFLAGS=  -L/usr/local/lib/ -L/home/gaofei/Tensorflow2/tensorflow-2.8.0/bazel-bin/tensorflow/
#LDFLAGS= -L/usr/local/lib/boost/ -L/usr/local/lib/ -L/usr/local/eigen3
#LDFLAGS= -Lboost_dir/stage/lib -L/usr/local/lib/ -L/usr/local/eigen3
#LDFLAGS= -Lboost_dir/stage/lib -L/usr/local/lib/
SOURCES= main.cpp 

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tensorexample

#LIBRARIES
LIBS_opencv = -lopencv_videostab -lopencv_videoio -lopencv_video -lopencv_superres -lopencv_stitching -lopencv_shape -lopencv_photo -lopencv_objdetect -lopencv_ml -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lopencv_flann -lopencv_features2d -lopencv_core -lopencv_calib3d
LIBS_tensorflow = -ltensorflow_cc 

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(INC_DIRS) $(LIBS_opencv) $(LIBS_tensorflow) $(OBJECTS) -o $@

pkgconf: $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@  $(LIBS_tensorflow) $(LIBS_opencv) 
	
#-O3 -DNDEBUG
#	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ `pkg-config opencv gsl glfw3 eigen3 --cflags --libs`  $(LIBS_pthread) $(LIBS_boost) $(LIBS_GL)

.cpp.o:
	$(CC) $(CFLAGS) $(INC_DIRS) $< -o $@ 
#-O3 -DNDEBUG

clean:
	rm -f $(OBJECTS) $(TARGET) $(EXECUTABLE)

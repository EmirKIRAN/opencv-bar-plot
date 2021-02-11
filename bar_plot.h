#ifndef BAR_PLOT_H
#define BAR_PLOT_H
#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include<string>

#define WIDTH 1240
#define HEIGHT 840

using namespace std;
using namespace cv;

class bar_plot
{
    private:
    string* x_labels;
    float* y_labels;
    float X1,X2,y1,y2;
    Mat frame;
    string plot_name;
    int size;
    float min();
    float max();
    float std();
    float mean();
public:
    bar_plot(string plot_name);
    bar_plot& setX_values(string* x_values,int size);
    bar_plot& setY_values(float* y_values,int size);
    bar_plot& getX_values();
    bar_plot& getY_values();
    void show();
};

#endif // BAR_PLOT_H

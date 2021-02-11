#include "bar_plot.h"
#include <cmath>
#define MAX_PIECE 5

bar_plot::bar_plot(string plot_name)
{
    X1 = WIDTH/9;
    X2 = WIDTH*0.74;
    y1 = HEIGHT/5;
    y2 = HEIGHT-100;
    frame.create(HEIGHT,WIDTH,CV_8UC3);
    frame = cv::Scalar(241,240,236);
    this->plot_name = plot_name;
}
bar_plot& bar_plot::setX_values(string* x_values,int size)
{
    this->x_labels = x_values;
    this->size = size;
    return *this;
}
bar_plot& bar_plot::setY_values(float* y_values,int size)
{
    this->y_labels = y_values;
    this->size = size;
    return *this;
}
bar_plot& bar_plot::getX_values()
{
    cout << "X degerleri : " << endl << "---------------------" << endl;

    for(int i=0;i<size;i++)
        cout << x_labels[i] << "\t";
    cout << endl;
    return *this;
}
bar_plot& bar_plot::getY_values()
{
    cout << "y degerleri : " << endl << "---------------------" << endl;

    for(int i=0;i<size;i++)
        cout << y_labels[i] << "\t";
    cout << endl;
    return *this;
}
void bar_plot::show()
{
    cv::namedWindow("BAR PLOT");
    cv::line(frame,cv::Point(X1,y2),cv::Point(X2,y2),cv::Scalar(0,0,0),3);
    cv::line(frame,cv::Point(X1,y1),cv::Point(X1,y2),cv::Scalar(0,0,0),3);
    cv::putText(frame,plot_name,cv::Point(WIDTH/3+20,100),FONT_HERSHEY_COMPLEX_SMALL,1,cv::Scalar(0,0,0),1);

    int slice = (max()/MAX_PIECE)+1,cp_y=0;
    float piece_y = (y2-y1-50)/MAX_PIECE,piece_x = (X2-X1-20)/MAX_PIECE;
    for(int i=0; i<=MAX_PIECE; i++)
    {
        int value = i*slice;
        cv::putText(frame,to_string(value),cv::Point(X1-35,y2-cp_y),FONT_HERSHEY_COMPLEX_SMALL,1,cv::Scalar(0,0,0),1);
        cp_y += piece_y;
    }
    cp_y = 30;
    for(int i=0; i<size; i++)
    {
        cv::putText(frame,x_labels[i],cv::Point(X1+cp_y+20,y2+30),FONT_HERSHEY_COMPLEX_SMALL,1,cv::Scalar(0,0,0),1);
        float data_pos = (y_labels[i]/slice)*piece_y;
        cv::rectangle(frame,cv::Point(X1+(i*150)+50,y2-3),cv::Point(X1+(i*150)+100,y2-data_pos),cv::Scalar(113,204,46),-1);
        cv::circle(frame,cv::Point(X1+(i*150)+75,y2-data_pos),5,cv::Scalar(0,0,255),-1);
        if(i != size-1)
            cv::line(frame,cv::Point(X1+(i*150)+75,y2-data_pos),cv::Point(X1+((i+1)*150)+75,y2-((y_labels[i+1]/slice)*piece_y)),cv::Scalar(0,0,0),3);
        cp_y+=piece_x;
    }
    string std_value = "Std : " + to_string(std()),mean_value = "mean : " + to_string(mean()),max_value = "max : " + to_string(max()), min_value = "min : " + to_string(min());
    cv::putText(frame,min_value,cv::Point(WIDTH-250,50),FONT_HERSHEY_COMPLEX_SMALL,1,cv::Scalar(0,0,0),1);
    cv::putText(frame,max_value,cv::Point(WIDTH-250,75),FONT_HERSHEY_COMPLEX_SMALL,1,cv::Scalar(0,0,0),1);
    cv::putText(frame,std_value,cv::Point(WIDTH-250,100),FONT_HERSHEY_COMPLEX_SMALL,1,cv::Scalar(0,0,0),1);
    cv::putText(frame,mean_value,cv::Point(WIDTH-250,125),FONT_HERSHEY_COMPLEX_SMALL,1,cv::Scalar(0,0,0),1);
    cv::imshow("BAR PLOT",frame);
    cv::waitKey(0);
}
float bar_plot::min()
{
    float min_value = y_labels[0];

    for(int i=1;i<size;i++)
        if(y_labels[i] < min_value)
            min_value = y_labels[i];
    return min_value;
}
float bar_plot::max()
{
    float max_value = y_labels[0];

    for(int i=0;i<size;i++)
        if(y_labels[i] > max_value)
            max_value = y_labels[i];
    return max_value;
}
float bar_plot::std()
{
    float p = 0;
    for(int i=0;i<size;i++)
        p = p + pow(y_labels[i]-mean(),2);
    double _std = (double) (1.0/(size-1.0)) * (double)p;
    return sqrt(_std);
}
float bar_plot::mean()
{
    float sum=0;
    for(int i=0;i<size;i++)
        sum+=y_labels[i];
    return sum/size;
}

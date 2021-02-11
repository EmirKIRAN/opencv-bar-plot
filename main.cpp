#include <iostream>
#include <bar_plot.h>

using namespace std;

int main()
{
    bar_plot b("3. HAFTA SATIS GRAFIGI");
    float* f_array = new float[5];
    f_array[0] = 21.6;
    f_array[1] = 34.21;
    f_array[2] = 12.581;
    f_array[3] = 41.08;
    f_array[4] = 66.22;
    string* f_string = new string[5];
    f_string[0] = "Pzt";
    f_string[1] = "Sal";
    f_string[2] = "Car";
    f_string[3] = "Per";
    f_string[4] = "Cum";

    b.setX_values(f_string,5).setY_values(f_array,5).getX_values().getY_values().show();
    return 0;
}

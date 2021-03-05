// ConsoleApplication3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>

# define M_PI 3.14159265358979323846 


using namespace std::chrono;
using namespace std;
float f(float x)
{
    return(4/((1.0f+ x*x)* (1.0f + x * x)));
}
float IntegrateParam(float a, float b, float n)
{
    float h, S, x;
    int i;
    h = (b - a) / n;
    S = 0;

    for (i = 0; i < n - 1; i++)
    {
        //x= a + i * h;//для метода левых прямоуголников
        x = b - i * h;//для метода правых прямоугольников
        S = S + f(x);
    }
    S = h * S;
    return S;
}
float IntegrateParamNoVect(float a, float b, float n)
{
    float h, S, x;
    int i;
    h = (b - a) / n;
    S = 0;
#pragma loop(no_vector)
    for (i = 0; i < n - 1; i++)
    {
        //x = a + i * h;//для метода левых прямоуголников
        x = b - i * h;//для метода правых прямоугольников
        S = S + f(x);
    }
    S = h * S;
    return S;
}
float IntegrateParamParallel(float a, float b, float n)
{
    float h, S, x;
    int i;
    h = (b - a) / n;
    S = 0;
#pragma loop(hint_parallel(8))
    for (i = 0; i < n - 1; i++)
    {
        //x = a + i * h;//для метода левых прямоуголников
        x = b - i * h;//для метода правых прямоугольников
        S = S + f(x);
    }
    S = h * S;
    return S;
}
float IntegrateParamThread(float a, float b, float n)
{
    float h, S, x;
    int i;
    h = (b - a) / n;
    S = 0;

    for (i = 0; i < n - 1; i++)
    {
        //x = a + i * h;//для метода левых прямоуголников
        x = b - i * h;//для метода правых прямоугольников
        S = S + f(x);
    }
    S = h * S;
    cout << "Thread" << endl;
    cout << "Result " << S << endl;
    cout << "Measurement error " << 2+ M_PI - S<< endl;
    return S;
}

void main()
{
    float  res;
    float analitic_res = 2 + M_PI;
    float n = 1000000.0f;

    cout << "Right rectangle method"  << endl;
    //cout << "Left rectangle method" << endl;
    cout << "\n" << endl;

    cout << "Number of intervals " << n << endl;
    cout << "\n" << endl;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    res = IntegrateParam(-1, 1, n);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> duration = (t2 - t1);
    cout << "Consistent metod" << endl;
    cout << "Result "<< res<<endl;
    cout << "Measurement error " << analitic_res-res << endl;
    cout << "Duration is: " << duration.count() << " seconds" << endl;
    cout << "\n" << endl;


    high_resolution_clock::time_point t3 = high_resolution_clock::now();
    res = IntegrateParamNoVect(-1, 1, n);
    high_resolution_clock::time_point t4 = high_resolution_clock::now();
    duration = (t4 - t3);
    cout << "NoVector metod" << endl;
    cout << "Result " << res << endl;
    cout << "Measurement error " << analitic_res - res << endl;
    cout << "Duration is: " << duration.count() << " seconds" << endl;
    cout << "\n" << endl;

    high_resolution_clock::time_point t5 = high_resolution_clock::now();
    res = IntegrateParamNoVect(-1, 1, n);
    high_resolution_clock::time_point t6 = high_resolution_clock::now();
    duration = (t6 - t5);
    cout << "Qpar" << endl;
    cout << "Result " << res << endl;
    cout << "Measurement error " << analitic_res - res << endl;
    cout << "Duration is: " << duration.count() << " seconds" << endl;
    cout << "\n" << endl;

    high_resolution_clock::time_point t7 = high_resolution_clock::now();
    std::thread thread(IntegrateParamThread, -1, 1, n);
    high_resolution_clock::time_point t8 = high_resolution_clock::now();
    duration = (t8 - t7);
    thread.join();
    cout << "Duration is: " << duration.count() << " seconds" << endl;
    cout << "\n" << endl;

    system("PAUSE");
}




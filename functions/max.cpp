#include "../global.hpp"
#include <math.h>
#include <functional>
#include <iostream>

double max(const std::function<double(double)> &f, double tl, double tu, double accuracy = settings.graphing.reciprocal){
    int imax = 100;
    long double t1 = tl + (tu - tl)*((pow(5,0.5) - 1) / 2);
    long double t2 = tu - (tu - tl)*((pow(5,0.5) - 1) / 2);
    long double pz;    
    long double pzold = 0;
    double pt;
    long double ea;

    for (int i = 1; i <= imax; i++){
        if (f(t1) > f(t2)){
            pz = f(t1);
            pt = t1;
        }else{
            pz = f(t2);
            pt = t2;
        }

        ea = fabs((tu - tl) / pt) * 100;
        pzold = pz;

        if (ea < accuracy){
            break;
        }

        if (f(t1)>f(t2)){
            tl = t2;
            t2 = t1;
            t1= tl + fabs(tu - tl)*((pow(5,0.5) - 1) / 2);
        }  

        else if (f(t2)>f(t1)){
            tu = t1;
            t1 = t2;
            t2= tu - fabs(tu - tl)*((pow(5,0.5) - 1) / 2);
        }
    }

	return pz;
}
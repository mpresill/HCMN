#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <math.h>
#include <fstream>

using namespace std;

int main(void)
{
 double TT=0.0;
 double errTT=0.0;
 double tW=0.0;
 double errtW=0.0;
 double Other=23.717;
 double errOther=3.423;
 double DY=637.546;
 double errDY=34.990;
//////////////////////////////////////////
 //double Data=28594.000; //ele-channel
 //double errData=169.098; //ele-channel
 double Data=712.000; //mu-channel
 double errData=26.683; //mu-channel
 double D, errD, R, errR;

 D=Data-TT-tW-Other;
 errD=pow((errData*errData+errTT*errTT+errtW*errtW+errOther*errOther),0.5);
 R=D/DY;
 errR=R*pow(pow((errD/D),2)+pow((errDY/DY),2),0.5);
 cout<<"R="<<R<<"+-"<<errR<<"\n";

return 0;
}

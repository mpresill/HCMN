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
 double TTtW=146;
 double errTTtW=7;
 double Other=47;
 double errOther=13;
 double DY=917;
 double errDY=38;
//////////////////////////////////////////
 double Data=1136; 
 double errData=34; 
 double D, errD, R, errR;

 D=Data-TTtW-Other;
 errD=pow((errData*errData+errTTtW*errTTtW+errOther*errOther),0.5);
 R=D/DY;
 errR=R*pow(pow((errD/D),2)+pow((errDY/DY),2),0.5);
 cout<<"R="<<R<<"+-"<<errR<<"\n";

return 0;
}

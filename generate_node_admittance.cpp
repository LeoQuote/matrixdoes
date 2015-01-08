/*************************************************************************
	> File Name: gennerate_node_admittance.cpp
	> Author:戚志诚 
	> Mail: leo.quote@hotmail.com
	> Created Time: Thu 08 Jan 2015 04:05:25 PM CST
 ************************************************************************/

#include<iostream>
#include<complex>
using namespace std;
int main() {
    int i=0,j=0,arraySize;
    arraySize=4;
    float dataArray[4][5]= {
        {1,2,0.1,0.4,0.01528},
        {1,3,0,0.3,1.1},
        {1,4,0.12,0.5,0.01920},
        {2,4,0.08,0.40,0.01413}
    };
    //初始化Y阵
    std::complex<float> Yarray[arraySize][arraySize];
    
    
    int fromport , toport;
    float R,X,BOrK;
    std::complex<float> Y;
    for(i=0;i<4;i++) {
        fromport=dataArray[i][0]-1;
        //std::cout << fromport <<ends;
        toport=dataArray[i][1]-1;
        R=dataArray[i][2];
        X=dataArray[i][3];
        std::complex<float> Z  (R,X);

        BOrK=dataArray[i][4];
        //std::cout<< conj(Z)/norm(Z)  <<ends; 
        if (BOrK >0.85){
            //如果大于0.85,就认为是变压器, 做变压器的相关变换
            Yarray[toport][toport]+=conj(Z)/norm(Z);
            Yarray[fromport][fromport]+=Yarray[toport][toport]*(BOrK*BOrK);
            Yarray[toport][fromport]=Yarray[fromport][toport]=-Yarray[toport][toport]*BOrK;
        }
        else {
            //小于0.85,那么进行如下处理
            Y=conj(Z)/norm(Z);
            Yarray[fromport][fromport]+=Y;//+(0,BOrK);
            Yarray[toport][toport]+=Y;//+(0,BOrK);
            Yarray[fromport][toport]=Yarray[toport][fromport]=-Y;
        }
    }
    for (i=0;i<arraySize;i++) {
        for (j=0;j<arraySize;j++) {
            std::cout<< Yarray[i][j]<<ends;
            
        }
        std::cout<< "" <<endl;
    }
}

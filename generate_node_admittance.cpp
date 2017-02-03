/*************************************************************************
	> File Name: gennerate_node_admittance.cpp
	> Created Time: Thu 08 Jan 2015 04:05:25 PM CST
 ************************************************************************/

#include<iostream>
#include<complex>
using namespace std;
std::complex<float> oneOverX ( std::complex<float> X ) {
    std::complex<float> oneOverX ;
    oneOverX= conj(X)/norm(X);
    return oneOverX;
}
int main() {
    int i=0,j=0,arraySize;
    arraySize=4;
    float dataArray[4][5]= {
        {1,2,0.1,0.4,0.01528},
        {3,1,0,0.3,0.909091},
        {1,4,0.12,0.5,0.01920},
        {2,4,0.08,0.40,0.01413}
    };
    /*
    arraySize=5;
    float dataArray[5][5]= {
                {1,2,0,0.105f,1.05f},
                {2,3,0.024f,0.065f,0.016f},
                {2,4,0.03f,0.08f,0.02f},
                {3,4,0.018f,0.05f,0.013f},
                {5,4,0,0.184f,0.96f}
            
    };
    */
    //初始化Y阵
    std::complex<float> Yarray[arraySize][arraySize];
    
    
    int fromport , toport;
    float R,X,BOrK;
    std::complex<float> Y,Y2;
    for(i=0;i<arraySize;i++) {
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
            Y=conj(Z)/norm(Z);
    //        std::cout<< Y  <<endl;
            Yarray[fromport][fromport]+=Y;
            Yarray[toport][toport]+=Y/(BOrK*BOrK);
            Yarray[toport][fromport]=Yarray[fromport][toport]=-Y/BOrK;
        }
        else {
            //小于0.85,那么进行如下处理
            Y=conj(Z)/norm(Z);
            Y2=Y+(0,BOrK);
            //std::cout<< Y  <<endl;
            std::complex<float> BOrK1 (0,BOrK);
            Yarray[fromport][fromport]+=Y+BOrK1;
            Yarray[toport][toport]+=Y+BOrK1;
            Yarray[fromport][toport]=Yarray[toport][fromport]=-Y;
        }
    }
    for (i=0;i<arraySize;i++) {
        for (j=0;j<arraySize;j++) {
            //std::cout<< Yarray[i][j]<<ends;
            std::cout<<real(Yarray[i][j])<<"+"<<imag(Yarray[i][j])<<"i "<<ends;
        }
        std::cout<< ";" <<endl;
    }
//#include<conio.h>
//	printf("hehe\n");
//	以下为消元,得到上三角R阵 Rarray 
    std::complex<float> Uarray[arraySize][arraySize];
    std::complex<float> Rarray[arraySize][arraySize];
    float b[4][4]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int k;
/*    
    */
    //初始化
    for (i=0;i<arraySize;i++) {
        for (j=0;j<arraySize;j++) {
            Rarray[i][j]=Yarray[i][j];
        }
    }
        //Uarray[i][j]=Yarray[i][j];
	for (k=0;k<arraySize-1;k++){
		for (i=k+1;i<arraySize;i++) {
			for (j=k+1;j<arraySize;j++) {
			Rarray[i][j]-=Rarray[i][k]*Rarray[k][j]*oneOverX(Rarray[k][k]);
			//Yarray[i][j]=Yarray[i][j]*oneOverX(Yarray[i][i]);
			Rarray[i][j]=Rarray[i][j]*oneOverX(Rarray[i][i]);
//				printf ("%f ",b[i][j]);
			}
            Rarray[i][k]=0;
//			printf("\n");
        }
//		printf("\n");
        //Yarray[0][0]=(0,0);
        for (i=0;i<arraySize;i++) {
			for (j=0;j<arraySize;j++) {
				//b[i][j]=b[i][j]-b[i][1]*b[1][j]/b[1][1]; 
            //    std::cout<<Rarray[i][j]<<"\t"<<ends;
            std::cout<<real(Rarray[i][j])<<"+"<<imag(Rarray[i][j])<<"i "<<ends;
			}
            std::cout<<";"<<endl;
		}
        std::cout<<""<<endl;
	}
    /*
    for (k=1;k<arraySize;k++) {
        for (i=k;i<arraySize;i++){
            for (j=0;j<k;j++) {
                Uarray[i][j]=(0,0);
            }
        }
    }
    */
    std::cout << "消元完成, 结果如下"<<endl;
    for (i=0;i<arraySize;i++) {
		for (j=0;j<arraySize;j++) {
			//b[i][j]=b[i][j]-b[i][1]*b[1][j]/b[1][1]; 
            //std::cout<<real(Rarray[i][j])<<"+"<<imag(Rarray[i][j])<<"i "<<ends;
            std::cout<<Rarray[i][j]<<"\t"<<ends;
		}
        std::cout<<";"<<endl;
	}

}





//	printf("Press any key to continue...");
/*	getch(); */

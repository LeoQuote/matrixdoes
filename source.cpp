#include<stdio.h>
#include<conio.h>
int main()
{
	int a,i,j,k;
	printf("hehe\n");
	float b[4][4]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	for (k=0;k<3;k++){
		for (i=k+1;i<4;i++) {
			for (j=k;j<4;j++) {
			b[i][j]=b[i][j]-b[i][k]*b[k][j]/b[k][k];
/*				printf ("%f ",b[i][j]);*/
			}
			printf("\n");
		}
		printf("\n");
		/*´òÓ¡¾ØÕó */
		for (i=0;i<4;i++) {
			for (j=0;j<4;j++) {
	/*			b[i][j]=b[i][j]-b[i][1]*b[1][j]/b[1][1]; */
				printf ("%f ",b[i][j]);
			}
			printf("\n");
		}
	}
	printf("Press any key to continue...");
	getch();
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ARRAY_SIZE 10

int main (void){

    double judge1[ARRAY_SIZE], judge2[ARRAY_SIZE], judge3[ARRAY_SIZE];
    double s1,s2,s3;
    double m1=0,m2=0,m3=0;
    double sd1=0,sd2=0,sd3=0;
    double var1=0,var2=0,var3=0;
    int com ,i, count=0;

    while(4==scanf("%d%lg%lg%lg",&com,&s1,&s2,&s3)){
        
        judge1[count] = s1;
        judge2[count] = s2;
        judge3[count] = s3;
        count++;

    }

    for(i = 0; i < count; i ++){
        m1 += judge1[i];
        m2 += judge2[i];
        m3 += judge3[i];
    }
    m1 = m1/count;
    m2 = m2/count;
    m3 = m3/count;

    for(i =0; i< count; i++){

        var1 += (judge1[i]-m1)*(judge1[i]-m1);
        var2 += (judge2[i]-m2)*(judge2[i]-m2);
        var3 += (judge3[i]-m3)*(judge3[i]-m3);
       
    }

    var1 = var1/(count -1);
    var2 = var2/(count -1);
    var3 = var3/(count -1);

    sd1 = sqrt(var1);
    sd2 = sqrt(var2);
    sd3 = sqrt(var3);

   
    printf("judge1 : %f %f \n", m1 , sd1);
    printf("judge2 : %f %f \n", m2 , sd2);
    printf("judge3 : %f %f \n", m3 , sd3);

    
    return EXIT_SUCCESS; 
}

#include <stdlib.h>
#include <stdio.h>


int main(void){

    double s1,s2,s3,result,max=0;
    int reg,winner=0;

    while(4==scanf("%d%lg%lg%lg",&reg,&s1,&s2,&s3)){

        if(s1 < s2 && s1 <s3){
            result = (s2 + s3)/2;

        }else if (s2 < s1 && s2 < s3){
            result = (s1 + s3)/2;
         
        }else{
            result =(s1 +s2)/2;
           
        }
        if(max < result){
            max =result;
            winner =reg;
        }
        
    }
    
    printf("%d\n",winner);
    
    return EXIT_SUCCESS;
        
}

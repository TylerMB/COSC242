#include <stdio.h>
#include <stdlib.h>

int main (void){

    double s1, s2 , s3 , max=0 , result;
    int com,winner ;
    
    while (4==scanf("%d%lg%lg%lg",&com,&s1,&s2,&s3)){
        
        fflush(stdout);
        if (s1 < s2 && s1 < s3 ){
       
            result = (s2 + s3) /2;
        
                    }else if(s2 < s1 && s2 < s3){
       
                result=(s1 + s3) /2;

            }else{
       
                result = (s1 + s2)/ 2;
            }
        if (result > max){
            max = result;
            winner = com;
           
        }
    }
    printf("%d %f \n", winner, max);   
    return EXIT_FAILURE;
    }
    
        

//
//  main.c
//  axe_problem
//
//  Created by Work on 2021-02-13.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int number;
    printf("Please enter an integer: ");
    scanf("%d", &number);
    int i, j;
    int handle = 0;
    if(number==1){
        printf(" XX \n");
        handle ++;
    }
    for (i=0; i<number; i++){
        for(j=0; j<=i; j++){
            printf("X");
        }
        for(j=j; j<=number-1; j++){
            printf(" ");
        }
        if(i+2>=number){
            printf("XX");
            handle ++;
        }
        else{
            printf("  ");
        }
        for(j=number; j>i+1; j--){
            printf(" ");
        }
        for(j=j; j>=1; j--){
            printf("X");
        }
        printf("\n");
    }
    for (i=1; i<number; i++){
        for(j=number-1; j>=i; j--){
            printf("X");
        }
        for(j=j; j>=0; j--){
            printf(" ");
        }
        if(handle<10){
            printf("XX");
            handle ++;
        }
        else{
            printf("  ");
        }
        for(j=0; j<i; j++){
            printf(" ");
        }
        for(j=j; j<number; j++){
            printf("X");
        }
        printf("\n");
    }
    while(handle<10){
        for(i=0; i<number; i++){
            printf(" ");
        }
        printf("XX");
        for(i=0; i<number; i++){
            printf(" ");
        }
        printf("\n");
        handle ++;
    }
    return 0;
}

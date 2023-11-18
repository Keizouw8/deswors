#include "./functions/integral.c"
#include <stdio.h>
#include <math.h>

int main(){
    printf("%.5f", integral(0, 100000, sin));
    return 0;
}
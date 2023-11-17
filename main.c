#include "./functions/integral.c"
#include <stdio.h>
#include <math.h>

int main(){
    printf("%.10f\n", integral(0, 1, sin));
    return 0;
}
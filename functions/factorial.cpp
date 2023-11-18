double factorial(double i){
    double total = i--;
    while(i > 1){
        total *= i;
        i--;
    }
    return total;
}
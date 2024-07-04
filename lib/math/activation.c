double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double sigmoid_derivative(double x) {
    return x * (1.0 - x);
}

double relu(double x){
    if(x<=0){
        return 0;
    }else{
        return x;
    }
}
/*
    @file: cnn.cc
    @author: yash
*/
#include <iostream>
#include <fstream>
// #include <string>
#include <eigen3/Eigen/Dense>

#define KERNEL_SIZE 3
#define STRIDE 1
#define IMAGED 28 // taking the image to be square

class csv{
private:
    int rows = 0;
public:
    csv(const char* filename){
        std::ifstream file(filename);
        char c;
        while (file.get(c)){
            if(c == '\n'){
                rows++;
            }
        }
        file.close();
    }
    ~csv(){

    }
    int getrow(){
        return rows;
    }
};

class cnn{
private:
    Eigen::Matrix3f kernel;
    Eigen::Matrix<float,IMAGED,IMAGED> image;
    int rows;
public:
    cnn(){

    }
    ~cnn(){

    }
    void train(const char* filename){
        csv train(filename);
        rows = train.getrow();

    }   
};
//train

int main(){
    // std::cout << IMAGED << std::endl;
    csv train("./dataset/train.csv");
    std::cout << train.getrow() << std::endl;
    return 0;
}
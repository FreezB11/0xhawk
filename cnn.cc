/*
    @file: cnn.cc
    @author: yash
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <eigen3/Eigen/Dense>

#define KERNEL_SIZE 3
#define STRIDE 1
#define IMAGED 28 // taking the image to be square

typedef struct trainset{
    int id;
    Eigen::Matrix<float,IMAGED,IMAGED> image;
}trainset;

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

    trainset read_data(const char* filename, int n){
        trainset res;
        std::ifstream file(filename);
        if(!file.is_open()){
            throw std::runtime_error("Failed to open file");
        }
        std::string line;
        int currentline = 0;
        // skipping the first line as it is just the columen name
        std::getline(file,line);

        // we shall read now
        while (std::getline(file,line)){
            currentline++;
            if(currentline == n){
                std::istringstream linestream(line);
                std::string token;
                std::getline(linestream, token, ',');
                res.id = std::stoi(token);

                std::vector<float> px;
                while(std::getline(linestream, token, ',')){
                    px.push_back((std::stoi(token)/255.0f));
                }
                if(px.size() != IMAGED*IMAGED){
                    throw std::runtime_error("Invalid number of pixels");
                }

                Eigen::Matrix<float, IMAGED, IMAGED> img;
                for(int i = 0;  i< IMAGED;++i){
                    for(int j = 0; j < IMAGED; ++j){
                        img(i,j) = px[i*28 + j];
                    }
                }
                res.image = img;
                return res;
            }
        }
        throw std::out_of_range("requestd line number is out of bound");
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

    //test for line data
    csv test("./dataset/train.csv");
    try{
        trainset t = test.read_data("./dataset/train.csv",1);

        std::cout << "img \n" << t.image << std::endl;

    }catch (const std::exception& ex){
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    return 0;
}
#include <eigen3/Eigen/Dense>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include "../src/lib/utils.hh"
#include "../src/lib/mmath.h"

Eigen::MatrixXd sigmoid(const Eigen::MatrixXd &z) {
    return 1.0 / (1.0 + (-z).array().exp());
}

Eigen::MatrixXd sigmoid_prime(const Eigen::MatrixXd &z) {
    Eigen::MatrixXd sig = sigmoid(z);
    return sig.array() * (1 - sig.array());
}

#define IMAGED 28
// #define 

typedef struct trainset{
    Eigen::VectorXd         id;
    Eigen::VectorXd         data;
}trainset;

double compute_loss(const Eigen::VectorXd &a,const Eigen::VectorXd &y, int batch_size =1){
    return (a-y).array().pow(2).sum() / batch_size;
}

class csv{
private:
    int rows = 0;
public:
    csv(const char* filename);
    ~csv();
    trainset                read_data(const char* filename, int n);
    int                     getrow();
};

csv::csv(const char* filename){
    std::ifstream file(filename);
    char c;
    while (file.get(c)){
        if(c == '\n'){
            rows++;
        }
    }
    file.close();
}
csv::~csv(){
}

trainset csv::read_data(const char* filename, int n){
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


            Eigen::VectorXd enc = Eigen::VectorXd::Zero(10);
            int p = std::stoi(token);
            // log(
            //     "the id"
            // )
            // std::cout << p << std::endl;
            enc[p] =1;

            res.id = enc;
            // log("one hot encoding")
            // std:: cout << enc << std::endl;

            std::vector<double> px;
            while(std::getline(linestream, token, ',')){
                px.push_back((std::stoi(token) / 255.0f));///255.0f));
            }
            if(px.size() != IMAGED*IMAGED){
                throw std::runtime_error("Invalid number of pixels");
            }
            // Eigen::VectorXd img;
            // for(int i = 0;  i< IMAGED*IMAGED;++i){
            //     img[i] = px[i];
            // }
            Eigen::VectorXd img = Eigen::Map<Eigen::VectorXd>(px.data(), px.size());
            res.data = img;
            return res;
        }
    }
    throw std::out_of_range("requestd line number is out of bound");
}

int csv::getrow(){
    return rows;
}


Eigen::MatrixXd W1,W2,W3,b1,b2,b3;
Eigen::MatrixXd A1,Z1,
                A2,Z2,
                A3,Z3;

void forward(const Eigen::MatrixXd &X, int batch_size=1){
        Z1 = W1.transpose() * X + b1;//.replicate(1, batch_size);
        A1 = sigmoid(Z1);
        Z2 = W2.transpose() * A1 + b2;//.replicate(1, batch_size);
        A2 = sigmoid(Z2);
        Z3 = W3.transpose() * A2 + b3;//.replicate(1, batch_size);
        A3 = sigmoid(Z3);
}
double loss(const Eigen::MatrixXd &y,int batch_size =1){
    return (A3 - y).array().pow(2).sum()/batch_size;
}

void back_propagation(const Eigen::MatrixXd &X, const Eigen::MatrixXd &Y,int batch_size =1 ){
    Eigen::MatrixXd dz3 = (A3 - Y).array() * sigmoid_prime(Z3).array();
    Eigen::MatrixXd dw3 = dz3 * A2.transpose() / batch_size;
    Eigen::MatrixXd db3 = dz3.rowwise().sum() / batch_size;
    Eigen::MatrixXd dz2 = (W3*dz3).array() * sigmoid_prime(Z2).array();
    Eigen::MatrixXd dw2 = dz2 * A1.transpose() / batch_size;
    Eigen::MatrixXd db2 = dz2.rowwise().sum() / batch_size;
    Eigen::MatrixXd dz1 = (W2 * dz2).array() * sigmoid_prime(Z1).array();
    Eigen::MatrixXd dw1 = dz1 * X.transpose() / batch_size;
    Eigen::MatrixXd db1 = dz1.rowwise().sum() / batch_size;

    double lr = 0.01f;

    W1 -= lr * dw1.transpose();
    b1 -= lr * db1;
    W2 -= lr * dw2.transpose();
    b2 -= lr * db2;
    W3 -= lr * dw3.transpose();
    b3 -= lr * db3;
}


int main(){

    csv test("../dataset/train.csv");
    // trainset p = test.read_data("../dataset/train.csv",4);
    // Eigen::MatrixXd W1,W2,W3,b1,b2,b3;
    W1 = Eigen::MatrixXd::Random(784,50);
    W2 = Eigen::MatrixXd::Random(50,50);
    W3 = Eigen::MatrixXd::Random(50,10);
    b1 = Eigen::MatrixXd::Random(50,1);
    b2 = Eigen::MatrixXd::Random(50,1);
    b3 = Eigen::MatrixXd::Random(10,1);

    // Eigen::MatrixXd A1(50), Z1(50),
    //                 A2(50), Z2(50),
    //                 A3(10), Z3(10);
            
    

    // std::cout << p.data << std::endl;
    // std::cout << p.id << std::endl;
    // std::cout << test.getrow() << std::endl;

    std::ofstream dataFile("loss.txt");
    

    int q = 20000;
    for(int i = 1; i<q;i++){
        trainset p = test.read_data("../dataset/train.csv",i);
        forward(p.data);
        dataFile << i << " " << loss(p.id) << std::endl;
        back_propagation(p.data, p.id);
    }

    dataFile.close();

    trainset t = test.read_data("../dataset/train.csv",8);
    // log("testing")
    forward(t.data);
    A3 = softmax(A3);

    // std::cout << A3.transpose() << std::endl;
    log("Model trained with "<< q << " samples\n")
    log("Actual value of the number")
    std::cout << t.id.transpose() << std::endl;
    log("Predicted number by Network")
    std::cout << A3.transpose() << std::endl;

    // std::cout << loss(p.id) << std::endl;
    // std::cout << A3 << std::endl;
    // std::cout << "chechk\n";

    
    // std::cout << "output is here\n";
    // std::cout << A3 << std::endl;    

    return 0;
}
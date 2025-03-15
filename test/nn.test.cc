#include "../src/nn.hh"
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <fstream>

#define IMAGED 28

// typedef struct trainset{
//     Eigen::VectorXd         id;
//     Eigen::VectorXd         data;
// }trainset;

// class csv{
// private:
//     int rows = 0;
// public:
//     csv(const char* filename);
//     ~csv();
//     trainset                read_data(const char* filename, int n);
//     int                     getrow();
// };

// csv::csv(const char* filename){
//     std::ifstream file(filename);
//     char c;
//     while (file.get(c)){
//         if(c == '\n'){
//             rows++;
//         }
//     }
//     file.close();
// }
// csv::~csv(){
// }

// trainset csv::read_data(const char* filename, int n){
//     trainset res;
//     std::ifstream file(filename);
//     if(!file.is_open()){
//         throw std::runtime_error("Failed to open file");
//     }
//     std::string line;
//     int currentline = 0;
//     // skipping the first line as it is just the columen name
//     std::getline(file,line);
//     // we shall read now
//     while (std::getline(file,line)){
//         currentline++;
//         if(currentline == n){
//             std::istringstream linestream(line);
//             std::string token;
//             std::getline(linestream, token, ',');


//             Eigen::VectorXd enc = Eigen::VectorXd::Zero(10);
//             int p = std::stoi(token);
//             // log(
//             //     "the id"
//             // )
//             // std::cout << p << std::endl;
//             enc[p] =1;

//             res.id = enc;
//             // log("one hot encoding")
//             // std:: cout << enc << std::endl;

//             std::vector<double> px;
//             while(std::getline(linestream, token, ',')){
//                 px.push_back((std::stoi(token) / 255.0f));///255.0f));
//             }
//             if(px.size() != IMAGED*IMAGED){
//                 std::cerr << "expected " << IMAGED*IMAGED << " pixels, but got " << px.size() << std::endl;
//                 throw std::runtime_error("Invalid number of pixels");
//             }
//             // Eigen::VectorXd img;
//             // for(int i = 0;  i< IMAGED*IMAGED;++i){
//             //     img[i] = px[i];
//             // }
//             Eigen::VectorXd img = Eigen::Map<Eigen::VectorXd>(px.data(), px.size());
//             res.data = img;
//             return res;
//         }
//     }
//     throw std::out_of_range("requestd line number is out of bound");
// }

// int csv::getrow(){
//     return rows;
// }

int main() {
    std::vector<int> layers = {784, 30, 10};
    NeuralNetwork nn(layers);

    csv test("./dataset/train.csv",28);


    trainset p = test.read_data("./dataset/train.csv",4);
    std::cout << "here\n";

    // Eigen::MatrixXd input(784, 1);
    // input.setRandom();

    // Eigen::MatrixXd target(10, 1);
    // target.setRandom();

    nn.train(p.data, p.id, 0.1, 1000);

    Eigen::MatrixXd output = nn.feedforward(p.data);
    std::cout << output << std::endl;

    return 0;
}
#include <hawk/cnn.hh>
#include <fstream>

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
            res.id = std::stoi(token);
            std::vector<float> px;
            while(std::getline(linestream, token, ',')){
                px.push_back((std::stoi(token)/255.0f));
            }
            if(px.size() != IMAGED*IMAGED){
                throw std::runtime_error("Invalid number of pixels");
            }
            Eigen::Matrix<double, IMAGED, IMAGED> img;
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

int csv::getrow(){
    return rows;
}



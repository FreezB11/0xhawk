#include <hawk/knn.h>
#include <queue>

namespace HAWK {
namespace KNN {

KNN::KNN(int k) : k(k) {}

void KNN::setK(int k) {
    this->k = k;
}

void KNN::fit(const Eigen::MatrixXd& X, const Eigen::VectorXi& y) {
    X_train = X;
    y_train = y;
}

double KNN::euclideanDistance(const Eigen::VectorXd& a, const Eigen::VectorXd& b) const {
    return (a - b).norm();
}

std::vector<std::pair<double, int>> KNN::getNeighbors(const Eigen::VectorXd& test_point) const {
    std::vector<std::pair<double, int>> distances;
    
    for (int i = 0; i < X_train.rows(); ++i) {
        double dist = euclideanDistance(X_train.row(i), test_point);
        distances.emplace_back(dist, y_train(i));
    }
    
    // Sort distances and keep only the k smallest
    std::sort(distances.begin(), distances.end(), 
        [](const std::pair<double, int>& a, const std::pair<double, int>& b) {
            return a.first < b.first;
        });
    
    if (distances.size() > static_cast<size_t>(k)) {
        distances.resize(k);
    }
    
    return distances;
}

int KNN::predictSingle(const Eigen::VectorXd& test_point) const {
    auto neighbors = getNeighbors(test_point);
    std::unordered_map<int, int> classVotes;
    
    for (const auto& neighbor : neighbors) {
        classVotes[neighbor.second]++;
    }
    
    // Find the class with maximum votes
    int predictedClass = -1;
    int maxVotes = 0;
    for (const auto& vote : classVotes) {
        if (vote.second > maxVotes) {
            maxVotes = vote.second;
            predictedClass = vote.first;
        }
    }
    
    return predictedClass;
}

Eigen::VectorXi KNN::predict(const Eigen::MatrixXd& X) {
    Eigen::VectorXi predictions(X.rows());
    
    for (int i = 0; i < X.rows(); ++i) {
        predictions(i) = predictSingle(X.row(i));
    }
    
    return predictions;
}

} // namespace KNN
} // namespace HAWK
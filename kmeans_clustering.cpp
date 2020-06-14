// Clustering using k-means

#include <vector>
#include <random>
#include <unordered_set>
#include <cmath>
#include <iostream>


using std::vector;
using std::unordered_set;

struct Point {
  
  float x {0};
  float y {0};

  void operator+=(const Point& p) {
    this->x += p.x;
    this->y += p.y;   
  }

};

double ComputeDistance (const Point& p1, const Point& p2) {

  return std::pow(std::pow(p1.x-p2.x, 2) + std::pow(p1.y-p2.y, 2), 0.5);

}

vector<Point> KMeansClustering(const vector<Point>& points, const int k) {

  vector<Point> cluster_means;

  constexpr float tolerance = 0.001;

  if (points.size() < k) {
    return cluster_means;
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(0, points.size()-1);

  unordered_set<int> indices;

  for(int i = 0; i < k; ++i) {
    auto idx = distr(gen);
    while(indices.find(idx) != indices.end()) {
      idx = distr(gen);
    }
    indices.insert(idx);
    cluster_means.push_back(points[idx]);
  }

  auto FindClosestMean = [&](const Point& p) {
    
    int idx = 0;
    int min_dist = std::numeric_limits<int>::max();
    
    for(int i = 0; i < cluster_means.size(); ++i) {

      auto dist = ComputeDistance(cluster_means[i], p);
      
      if (dist < min_dist){
        min_dist = dist;
        idx = i;
      }
    }
    
    return idx;
  
  };

  int iterations = 0;
  
  while(true) {

    iterations += 1;

    vector<Point> new_cluster_means(k, Point());
    vector<int> cluster_size(k, 0);

    for(auto& point : points) {

      auto idx = FindClosestMean(point);
      new_cluster_means[idx] += point;
      cluster_size[idx] += 1;

    }

    double diff = 0.0;

    for(int i = 0; i < new_cluster_means.size(); ++i) {

      new_cluster_means[i].x /= cluster_size[i];
      new_cluster_means[i].y /= cluster_size[i]; 

      diff += ComputeDistance(new_cluster_means[i], cluster_means[i]);

    }

    diff /= k;

    if (diff < tolerance) {
      std::cout << "Cluster means converged in: " << iterations << " iterations" << std::endl;
      break;
    }

    cluster_means.clear();
    cluster_means = new_cluster_means;
  
  }

  return cluster_means;
}

int main() {

  vector<Point> points;

  std::random_device rd;
  std::mt19937 gen(rd());
  
  //Three clusters around (4,4), (10,10) and (-4,-4)  - 100 points each cluster
  std::normal_distribution<> n_distr_1(4, 0.5);
  std::normal_distribution<> n_distr_2(10, 0.5);
  std::normal_distribution<> n_distr_3(-4, 0.5);

  for(int i = 0; i < 100; ++i) {

    Point p;

    p.x = n_distr_1(gen);
    p.y = n_distr_1(gen);
    points.push_back(p);

    p.x = n_distr_2(gen);
    p.y = n_distr_2(gen);
    points.push_back(p);

    p.x = n_distr_3(gen);
    p.y = n_distr_3(gen);
    points.push_back(p);

  }

  auto cluster_means = KMeansClustering(points, 3);

  for(const auto& c_mean : cluster_means) {

    std::cout << "(" << c_mean.x << "," << c_mean.y << ")" << std::endl;

  }
}
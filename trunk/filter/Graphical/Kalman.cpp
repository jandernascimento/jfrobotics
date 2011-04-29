#include "Kalman.hpp"

Kalman::Kalman(float init_mean, float init_std, float init_q, float init_r) {
  mean = init_mean;
  std = init_std;
  q = init_q;
  r = init_r;
}

void Kalman::prediction(int a) {
  old_mean = mean;
  old_std = std;
  mean = old_mean + a;
  std = old_std + q;
}

void Kalman::estimation(int o) {
  k = std / (std + r); 
  
  mean = mean + k * (o - mean);
  std = (1 - k) * std;
}


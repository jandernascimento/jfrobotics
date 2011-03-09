#include "Kalman.hpp"

Kalman::Kalman(float init_mean, float init_std, float init_q, float init_r) {

mean=init_mean;
std=init_std;
q=init_q;
r=init_r;

}

void Kalman::prediction(int a) {
}

void Kalman::estimation(int o) {
}


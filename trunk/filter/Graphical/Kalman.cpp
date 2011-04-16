#include "Kalman.hpp"

Kalman::Kalman(float init_mean, float init_std, float init_q, float init_r) {

mean=init_mean;
std=init_std;
q=init_q;
r=init_r;

}

void Kalman::prediction(int a) {

mean=1*mean+1*a;
std=1*std*1+q;

}

void Kalman::estimation(int o) {

k=(1*std*1)/(1*std*1+r);

mean=mean+k*(o-1*mean);
std=(1-k*1)*std;

}


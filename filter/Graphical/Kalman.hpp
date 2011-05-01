class Kalman{
    public:
		float mean;
		float std;
		float q;
		float r;
		float k;

		Kalman(float init_mean, float init_std, float init_q, float init_r);

		void prediction(int a);
		void estimation(int o);
};

#include <iostream>
/*Libraries needed*/
#include "DataReader.hpp"
#include "Kalman.hpp"

int main(int argc, char* argv[]){

    std::string setName(argv[1]);
    DataReader dataObj(setName);
  
	 dataObj.readData();//read the next laser data
 	 dataObj.printLaserData();//print the current laser data on the terminal window

	 // Initialization of Kalman Filter
	 float init_x;
	 float init_std;
	 float init_q;
	 float init_r;
	 Kalman x(init_x, init_std, init_q, init_r);
    std::cout << " mean(I) = " << x.mean << " std(I) = " << x.std << std::endl << std::endl;
    /*Displaying the dataset (each sliding window; each frame)*/
    while(dataObj.readData() == NOERROR) {
 	 	dataObj.printLaserData();//print the current laser data on the terminal window

		// prediction phase
		float a = 16;
		std::cout << "action = " << a << std::endl;
		x.prediction(a);
		std::cout << "mean(P) = " << x.mean << " std(P) = " << x.std << std::endl;

		// estimation phase
		float o;
		std::cout << "observation = " << o << std::endl;
		x.estimation(o);
		std::cout << "mean(E) = " << x.mean << " std(E) = " << x.std << std::endl << std::endl;
		
    }
    
    return 0;
}

#include <iostream>
/*Libraries needed*/
#include "cv.h"
#include "DataReader.hpp"
#include "Kalman.hpp"

int main(int argc, char* argv[]){
 
    std::string setName(argv[1]);
    DataReader dataObj1(setName);
    int key;

	 float a = 16;

    /*Window initialization*/
    dataObj1.initWindow();
    dataObj1.clearImage();
    
	 dataObj1.readData();//read the next laser data
    dataObj1.displayLaserData();//display the current laser data on the graphical window
  	 dataObj1.printLaserData();//display the current laser data on the graphical window

	 // Initialization of Kalman Filter
	 float init_x=0;
	 float init_std=0;
	 float init_q=1;
	 float init_r=5;
	 Kalman x(init_x, init_std, init_q, init_r);
    std::cout << "mean(I) = " << x.mean << " std(I) = " << x.std << std::endl << std::endl;

    /*Displaying the dataset (each sliding window; each
     frame)*/
    while(dataObj1.readData() == NOERROR) {
    	dataObj1.displayLaserData();//display the current laser data on the graphical window
    	dataObj1.printLaserData();//print the current laser data

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

		/*delay*/
		key=cvWaitKey(0);
    }
    
    return 0;
}

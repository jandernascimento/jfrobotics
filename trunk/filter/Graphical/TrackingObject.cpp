#include <iostream>
/*Libraries needed*/
#include "DataReader.hpp"
#include "Kalman.hpp"

int main(int argc, char* argv[]){

   std::string setName(argv[1]);
   DataReader dataObj(setName);
   int key;
    
	float a = 3;

   /*Window initialization*/
   dataObj.initWindow();
   dataObj.clearImage();

 	// read the first data to determine the background
	dataObj.readData();//read the next laser data
   dataObj.initBackground();//define the background
 	dataObj.displayLaserData();//display the current laser data on the graphical window
   
	// Initialization of Kalman Filter
	// read the second data
	dataObj.readData();//read the next laser data
 	//dataObj.printLaserData();//print the current laser data on the terminal window
	dataObj.displayLaserData();//display the current laser data on the graphical window

	//detection of motion
	int threshold = 15;
	dataObj.detectMotion(threshold);
	dataObj.printMotion();
	dataObj.displayMotion();
  	dataObj.formObject();

	float init_y = 16;
	float init_std = 10;
	float init_q = 4;
	float init_r = 1;
	Kalman y(init_y, init_std, init_q, init_r);
   std::cout << "mean(I) = " << y.mean << " std(I) = " << y.std << std::endl << std::endl;

   int data_num = 1;

   /*Displaying the dataset (each sliding window; each
     frame)*/
	while(dataObj.readData() == NOERROR) {
    
    std::cout << "data_num = " << data_num++ << std::endl;

    //dataObj.printLaserData();//display the current laser data on the
    //graphical window
    dataObj.displayLaserData();//display the current laser data on the
    //graphical window

		float o = dataObj.detectMotion(threshold);
		dataObj.printMotion();
    dataObj.displayMotion();
		dataObj.formObject();

		// prediction phase
		std::cout << "action = " << a << std::endl;
		y.prediction(a);
		std::cout << "mean(P) = " << y.mean << " std(P) = " << y.std << std::endl;

		// estimation phase
		std::cout << "observation = " << o << std::endl;
		y.estimation(o);
		std::cout << "mean(E) = " << y.mean << " std(E) = " << y.std << std::endl << std::endl;

		/*delay*/
		key=cvWaitKey(0);
	}
    
     return 0;

}

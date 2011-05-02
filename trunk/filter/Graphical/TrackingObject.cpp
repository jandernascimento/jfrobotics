#include <iostream>
/*Libraries needed*/
#include "DataReader.hpp"
#include "Kalman.hpp"

int main(int argc, char* argv[]){

   std::string setName(argv[1]);
   DataReader dataObj(setName);
   int key;
    
	float a;
	float pos1;
	float pos2;

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
 	dataObj.printLaserData();//print the current laser data on the terminal window
	dataObj.displayLaserData();//display the current laser data on the graphical window

	//detection of motion
	int threshold=5;
	dataObj.detectMotion(threshold);
	//dataObj.printMotion();
	dataObj.displayMotion();
  	pos1=dataObj.formObject();

	float init_y = 0.0;
	float init_std = 0.01;
	float init_q = 1;
	float init_r = 5;
	Kalman y(init_y, init_std, init_q, init_r);
   std::cout << "mean(I) = " << y.mean << " std(I) = " << y.std << std::endl << std::endl;

   /*Displaying the dataset (each sliding window; each
     frame)*/
	while(dataObj.readData() == NOERROR) {
		//dataObj.printLaserData();//display the current laser data on the graphical window
		dataObj.displayLaserData();//display the current laser data on the graphical window

		dataObj.detectMotion(threshold);
		//dataObj.printMotion();
  		dataObj.displayMotion();
		dataObj.formObject();

		// prediction phase
		pos2=dataObj.formObject();
		a=fabs(pos2-pos1);
                pos1=pos2;
		std::cout << "action = " << a << std::endl;
		y.prediction(a);
		std::cout << "mean(P) = " << y.mean << " std(P) = " << y.std << std::endl;

		// estimation phase
		//float o = dataObj.dataLaserR[BN / 2];
		float o = dataObj.getYCentroid();
		std::cout << "observation = " << o << std::endl;
		y.estimation(o);
		std::cout << "mean(E) = " << y.mean << " std(E) = " << y.std << std::endl << std::endl;

                 std::cout << "Impossible to track" <<pos2 << std::endl;

                if(pos2==270){
                   dataObj.drawRectangle(10, 10, 20, 20, cvScalar(2));
                }
	
		/*delay*/
                key=cvWaitKey(30);
	}
    
     return 0;

}

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

/*Beams number*/
#define BN 725
/*Number of frames in the DataSet*/
#define FRAMESNUMBER 12
/*Error macros for data reading*/
#define NOERROR 1
#define ENDDATASET 2
#define ERROR 0

class DataReader{
    private:
		int fileIndex;
		/*Directory name of current data set*/
		std::string dataSetName;
    public:
		/*These matrices allocate the length values retrieved from laser 
		sensor (cm)/radians/X coordinates/Y coordinates respectively, for a 
		sliding window of size SW.*/
		float dataLaser[BN]; //angle in degree
		float dataLaserR[BN]; //range in centimeters
		float dataLaserX[BN]; //position on X-axis
		float dataLaserY[BN]; //position on Y-axis

		float background[BN]; // used to store the background
		int detection[BN]; // used to store the beam where a motion has been detected
		int xmin, xmax, ymin, ymax;
		int x, y;
       
		/*Contructor function needs the dataset directory name*/
		DataReader(std::string fileName);
		~DataReader();
        
		/*Each time this function is called, the next sliding window 
		is stored in the four matrices. It returns NOERROR if no error ocurred; 
		ENDDATASET when the file index reachs the end of the data set; 
		and ERROR in other case.*/
		int readData();
        
		/*Print the set points stored in dataLaser at time t from
		current sliding window.*/
		int printLaserData();
		int printLaserData(int beam);

		/*Translates and rotates the coordinates x and y to be friendly displayed in
		the opencv coordinate system.*/
		void transformCoordinates(float x,float y, float *nx, float *ny);
        
		//detection of moving objects
		int initBackground();
		int detectMotion(int threshold);
		int printMotion();
		int formObject();
        
};

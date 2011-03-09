#include "DataReader.hpp"

DataReader::DataReader(std::string setName){
    /*Index file initialization*/
    fileIndex = 1;
    dataSetName = setName;
}

int DataReader::readData(){
    std::ifstream inFile;
    char tempChar[255];
    std::string fileNameTemp(""), lineTemp("");
    
    /*If we reach the end of the data set*/
    if (fileIndex == FRAMESNUMBER)
        return ENDDATASET;
    
    /*We read the next frame */
    std::ostringstream convert("");
    convert << fileIndex;
    if (fileIndex < 10)
    	fileNameTemp = dataSetName + std::string("data_000") + convert.str() + std::string(".csv");
    else if (fileIndex < 100)
    	fileNameTemp = dataSetName + std::string("data_00") + convert.str() + std::string(".csv");
    else
    	fileNameTemp = dataSetName + std::string("data_0") + convert.str() + std::string(".csv");
          
    inFile.open(fileNameTemp.c_str(), std::ifstream::in);
    if (!inFile.good()){
    	std::cout << "ERROR: Input file doesn't exist." << std::endl;
      return ERROR;
    } else {            
    	for (int j=0 ; j<BN ; j++){
    		inFile.getline(tempChar,255);
         lineTemp = std::string(tempChar);
         replace( lineTemp.begin(), lineTemp.end(), ',', ' ' ); 
         std::istringstream tempStream(lineTemp);
			tempStream >> dataLaser[j]  >> dataLaserR[j] >> dataLaser[j] >> dataLaserX[j] >> dataLaserY[j];
         /*to cm*/
         dataLaserR[j] /= 10;
    		dataLaserX[j] = dataLaserR[j] * cos(dataLaser[j]);
         dataLaserY[j] = dataLaserR[j] * sin(dataLaser[j]);
			
			// to degree
			dataLaser[j] *= 180;
			dataLaser[j] /= 3.14159;
		}
	}
	inFile.close();       
   fileIndex ++;//= SW;
    
    return NOERROR;
}

int DataReader::printLaserData(){

	std::cout << "printLaserData" << std::endl;
	for (int i=0;i < BN; i++)
		std::cout << "beam " << i << ", r="
		<< dataLaserR[i] << "cms, theta=" 
		<< dataLaser[i] << "degres, X=" 
		<< dataLaserX[i] << "cms, Y=" 
		<< dataLaserY[i] << "cms" << std::endl;
	std::cout << std::endl;

}

int DataReader::printLaserData(int beam){

	std::cout << "printLaserData" << std::endl;
	std::cout << "beam " << beam << ", r="
		<< dataLaserR[beam] << "cms, theta=" 
		<< dataLaser[beam] << "degres, X=" 
		<< dataLaserX[beam] << "cms, Y=" 
		<< dataLaserY[beam] << "cms" << std::endl << std::endl;

}

void DataReader::transformCoordinates(float x, float y, float *nx, float *ny){
    /*To (translate/rotate) the points. Parameters and equation used.*/
    int tx = 100, ty = 270, th = 0;
    /*cos(theta)  -sin (theta)  tx             | x
      sin (theta)  cos(theta)   ty             | y
      0                  0      1              | 1
     */
    *nx = (float) (cos(th)*x - sin(th)*y) + tx;
    *ny = (float) (sin(th)*x + cos(th)*y) + ty;

}

DataReader::~DataReader(){
}

int DataReader::initBackground(){
}

int DataReader::detectMotion(int threshold) {
}

int DataReader::printMotion() {

	std::cout << "printMotion" << std::endl;
	for(int i=0; i < BN; i++)
		if (detection[i])
			std::cout << "beam " << i << ", r="
			<< dataLaserR[i] << "cms, theta=" 
			<< dataLaser[i] << "degres, X=" 
			<< dataLaserX[i] << "cms, Y=" 
  			<< dataLaserY[i] << "cms" << std::endl;
	std::cout << std::endl;

	return NOERROR;

}

int DataReader::formObject() {
}

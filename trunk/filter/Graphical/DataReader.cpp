#include "DataReader.hpp"

DataReader::DataReader(std::string setName){
    /*Index file initialization*/
    fileIndex = 1;
    dataSetName = setName;
}

int DataReader::initWindow(){
    /*Initialazing the window and main image.*/
    cvNamedWindow("myWindow", CV_WINDOW_AUTOSIZE);
    image = cvCreateImage(cvSize(630,630),IPL_DEPTH_32F,3);
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

int DataReader::displayLaserData(){
    float nxl,nyl,rxl,ryl;
    
    /*Clearing image / Drawing the reference point*/
    clearImage();
    
    transformCoordinates(0,0,&nxl,&nyl);
    transformCoordinates(40,0,&rxl,&ryl);
    cvLine(image, cvPoint(nxl,nyl), cvPoint(rxl,ryl), CV_RGB(217,217,217),1,4);

    transformCoordinates(0,0, &nxl,&nyl);
    transformCoordinates(0,40, &rxl,&ryl);
    cvLine(image, cvPoint(nxl,nyl), cvPoint(rxl,ryl), CV_RGB(217,217,217),1,4);

    transformCoordinates(0,0,&nxl,&nyl);
    cvCircle(image,cvPoint(nxl,nyl),5,CV_RGB(0,255,0));    
    //transformCoordinates(-20,-10, &nxl,&nyl);
    //transformCoordinates(0,10, &rxl,&ryl);
    //cvRectangle(image,cvPoint(nxl,nyl), cvPoint(rxl,ryl), CV_RGB(217,217,217),2);

    CvFont f;
    cvInitFont(&f,CV_FONT_HERSHEY_SIMPLEX,0.5,0.5,1,1,1);
    transformCoordinates(490,10, &nxl,&nyl);
    transformCoordinates(3,300, &rxl,&ryl);
    cvPutText(image,"+x",cvPoint(nxl,nyl),&f,CV_RGB(217,217,217));
    cvPutText(image,"+y",cvPoint(rxl,ryl),&f,CV_RGB(217,217,217));

    
    for (int i=0;i < BN; i++){
        /*Before display every point, we have to transform its coordinates*/
        transformCoordinates(dataLaserX[i],dataLaserY[i],&nxl,&nyl);
        cvRectangle(image, cvPoint(nxl,nyl), cvPoint(nxl,nyl), CV_RGB(255,255,255), 1);
    }
    cvShowImage("myWindow", image);
    return NOERROR;
}

int DataReader::printLaserData(){

	for (int j=0;j<BN;j++)
		std::cout << "beam " << j << ", "
			<< dataLaserR[j] << " degre, " 
			<< dataLaser[j] << "cms, X=" 
			<< dataLaserX[j] << ", Y=" 
		  	<< dataLaserY[j] << std::endl;
}
int DataReader::printLaserData(int beam){

	std::cout << "beam " << beam << ", "
		<< dataLaserR[beam] << " degre, " 
		<< dataLaser[beam] << "cms, X=" 
		<< dataLaserX[beam] << ", Y=" 
	  	<< dataLaserY[beam] << std::endl;
}

void DataReader::drawRectangle(float xl, float yl, float xr, float yr, CvScalar color){ 
    cvRectangle(image, cvPoint(xl,yl), cvPoint(xr,yr), color, 1);
    cvShowImage("myWindow", image);
}

void DataReader::drawPoint(float x, float y, CvScalar color){
    cvRectangle(image, cvPoint(x,y), cvPoint(x,y), color, 1);
    cvShowImage("myWindow", image);
}

void DataReader::clearImage(){
    cvSet(image, cvScalar(0,0,0));
    cvShowImage("myWindow", image);
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

void DataReader::saveCurrentImage(){
	std::string fileNameTemp("");
   std::ostringstream convert("");
 	
	convert << fileIndex;
	if (fileIndex < 10)
		fileNameTemp = dataSetName + std::string("data_000") + convert.str() + std::string(".jpg");
	else if (fileIndex < 100)
		fileNameTemp = dataSetName + std::string("data_00") + convert.str() + std::string(".jpg");
	else
		fileNameTemp = dataSetName + std::string("data_0") + convert.str() + std::string(".jpg");
 
   cvSaveImage(fileNameTemp.c_str(),image);
}

DataReader::~DataReader(){
    cvReleaseImage(&image);
}

int DataReader::initBackground(){

	for(int i=0; i < BN; i++)
		background[i]=dataLaserR[i];


}

int DataReader::detectMotion(int threshold) {
	

	xmin=99999999999999;
	ymin=99999999999999;

	xmax=-1;
	ymax=-1;



	for(int i=0; i < BN; i++){
	
		float x1,y1,x2,y2;
		float diff=background[i]-dataLaserR[i];
		if(diff>0 && diff>threshold){
			detection[i]=1;
		
			if(
				(dataLaserX[i]==0 || dataLaserY[i]==0)
				||(dataLaserX[i]==217 && dataLaserY[i]==0)
			) 
				continue;			
	
			if(dataLaserX[i]<=xmin){ 
				xmin=dataLaserX[i];
			}
			
			if(dataLaserX[i]>=xmax){
				 xmax=dataLaserX[i];
			}
			
			if(dataLaserY[i]<=ymin){ 
				ymin=dataLaserY[i];
			}
			
			if(dataLaserY[i]>=ymax){
				 ymax=dataLaserY[i];
			}

	
		}else 
			detection[i]=0;
	}


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
int DataReader::displayMotion() {

	for(int i=0; i < BN; i++)
		if (detection[i]) {
		   float x1,y1,x2,y2;
    
    		   transformCoordinates(0,0,&x1,&y1);
		   transformCoordinates(dataLaserX[i],dataLaserY[i],&x2,&y2);
		   cvLine(image, cvPoint(x1,y1), cvPoint(x2,y2), CV_RGB(217,217,217),1,4);


		}

 
        
	
	cvShowImage("myWindow", image);
	return NOERROR;

}

int DataReader::formObject() {

	float x1,y1,x2,y2;

	printf("----> PRIMITIVE p1(%f,%f) p2(%f,%f)\n",xmin,ymin,xmax,ymax);
    	transformCoordinates(xmin,ymin,&x1,&y1);
    	transformCoordinates(xmax,ymax,&x2,&y2);

	printf("----> COOD p1(%f,%f) p2(%f,%f)\n",x1,y1,x2,y2);

	drawRectangle(x1,y1, x2, y2, cvScalar(2));


}

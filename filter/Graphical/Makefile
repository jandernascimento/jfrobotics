CC=g++
# Path of needed libraries
INCLUDE=/usr/include/opencv
#INCLUDE=/usr/local/include/opencv
LIB=/usr/local/lib/
#LIB=/usr/lib/

all: Localization TrackingObject

Kalman.o: Kalman.hpp Kalman.cpp
	$(CC) -c Kalman.cpp -I$(INCLUDE)

DataReader.o: DataReader.hpp DataReader.cpp
	$(CC) -c DataReader.cpp -I$(INCLUDE)

Localization.o: Localization.cpp DataReader.hpp Kalman.hpp
	$(CC) -c Localization.cpp -I$(INCLUDE)

Localization: Localization.o DataReader.o Kalman.o
	$(CC) -o Localization Localization.o DataReader.o Kalman.o -lcv -lcxcore -lhighgui -L$(LIB)

TrackingObject.o: TrackingObject.cpp DataReader.hpp Kalman.hpp
	$(CC) -c TrackingObject.cpp -I$(INCLUDE)

TrackingObject: TrackingObject.o DataReader.o
	$(CC) -o TrackingObject TrackingObject.o DataReader.o Kalman.o -lcv -lcxcore -lhighgui -L$(LIB)

clean:
	rm *.o
	rm Localization
	rm TrackingObject


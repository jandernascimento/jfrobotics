CC=g++

all: Localization TrackingObject

Kalman.o: Kalman.hpp Kalman.cpp
	$(CC) -c Kalman.cpp

DataReader.o: DataReader.hpp DataReader.cpp
	$(CC) -c DataReader.cpp

Localization.o: Localization.cpp DataReader.hpp Kalman.hpp
	$(CC) -c Localization.cpp

Localization: Localization.o DataReader.o Kalman.o
	$(CC) -o Localization Localization.o DataReader.o Kalman.o

TrackingObject.o: TrackingObject.cpp DataReader.hpp Kalman.hpp
	$(CC) -c TrackingObject.cpp

TrackingObject: TrackingObject.o DataReader.o
	$(CC) -o TrackingObject TrackingObject.o DataReader.o Kalman.o

clean:
	rm *.o
	rm Localization
	rm TrackingObject


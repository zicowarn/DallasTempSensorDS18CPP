//============================================================================
// Name        : DallasTempSensorDS18CPP.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "error/DallasTempSensorDS18CPPErrors.h"
#include "features/DallasTempSensorDS18CPPFeatures.h"

using namespace std;



int testFunc2(){
	MY_THROW(TestException, "f2 throw");
	return 0;
}

void testFunc1(){
	try{
		testFunc2();
	}
	catch (TestException& e)
	{
		cout<< e.what() <<endl;
	}
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	DallasTempSensorDS18Sensor mSensor(DallasTempSensorDS18Sensor::THERM_SENSOR_DS18B20, "");
	mSensor.say();
	cout<< mSensor.BASE_DIRECTORY<<endl;
}

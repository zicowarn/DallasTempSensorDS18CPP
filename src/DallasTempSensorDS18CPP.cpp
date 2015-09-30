/*
 * @Title: DallasTempSensorDS18CPP.cpp
 * @Description: TODO
 * @author: mrwang
 * @Created on: 28.09.2015 23:22:40
 * @Last modified by: mrwang
 * @Last modified on: 29.09.2015 23:22:40
 * @Version: V1.0
 * @Compiler: GCC
 * @Language: C/C++
 * @License: The MIT License (MIT)
 * @Copyright: 2015 mrwang
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
	DallasTempSensorDS18Sensor mSensor(DallasTempSensorDS18Sensor::THERM_SENSOR_DS18B20, "000006c4fdb1");
	int types[2]={DallasTempSensorDS18Sensor::THERM_SENSOR_DS1822, DallasTempSensorDS18Sensor::THERM_SENSOR_DS18B20};
	std::map<std::string, int> sensors = mSensor.get_available_sensors(types);
	std::cout << "mymap contains:\n";
	for (std::map<std::string, int>::const_iterator it=sensors.begin(); it!=sensors.end(); ++it){
		std::cout << it->first << " => " << it->second << '\n';
	}


}

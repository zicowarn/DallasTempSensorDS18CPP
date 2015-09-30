# DallasTempSensorDS18CPP
===============================================================================

This c++ project provide a rein C++ API and represents a temperature sensor of type w1-thermosensor 

### File structure of this project:
---
>>> in folder src/error
  >>>> - DallasTempSensorDS18CPPErrors.cpp
  >>>> - DallasTempSensorDS18CPPErrors.h
>>>  
>>> in folder src/features
  >>>> - DallasTempSensorDS18CPPFeatures.cpp
  >>>> - DallasTempSensorDS18CPPFeatures.h
>>>
>>> in folder src
  >>>> - DallasTempSensorDS18CPP.cpp  # for test the features
>>> 


### Dependent head files:
----
```c++
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <exception>
#include <cxxabi.h>
#include <execinfo.h>
#include <sstream>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <algorithm>
#include <string>
#include <sys/stat.h>
```

## Usage:
----
```c++
std::cout << "!!! Welcome to DallasTempSensorDS18CPP !!!" << std::endl;
/* You be allowed to create a instance of class DallasTempSensorDS18CPP,
if you do not know type and id of sensors*/
DallasTempSensorDS18Sensor mSensor(NULL, "");

/* You be allowed to create a instance of class DallasTempSensorDS18CPP also like this, if you just do not know id of sensors*/
DallasTempSensorDS18Sensor mSensor(DallasTempSensorDS18Sensor::THERM_SENSOR_DS18B20, "");

/* You be allowed to create a instance of class DallasTempSensorDS18CPP also like this, if you exactly know id of sensors*/
DallasTempSensorDS18Sensor mSensor(DallasTempSensorDS18Sensor::THERM_SENSOR_DS18B20,"000006c4fdb1");

int units[3] = { DallasTempSensorDS18Sensor::DEGREES_C,DallasTempSensorDS18Sensor::DEGREES_F };

/* You be allowed to get the values from the digital thermosensor. and
 * if you specify more than one temperature unit, you can get the converted
 * values of the specified units
*/
std::vector<float> values = mSensor.get_temperatures(units);
std::cout << "vector contains: " << std::endl;
for (unsigned it = 0; it < values.size(); it++) {
	/* C
	 * F
	 */
	std::cout << " Values => " << values[it] << std::endl;
}

/* You be allowed to get the values from the digital thermosensor. and
 * if you even do not specify any temperature unit, you can get all
 * converted values of all available units
 */
std::vector<float> values2 = mSensor.get_temperatures();
std::cout << "vector contains2 : " << std::endl;
for (unsigned it = 0; it < values2.size(); it++) {
	/* C
	 * F
	 * Kelvin
	 */
	std::cout << " Values => " << values2[it] << std::endl;
}

/* You be allowed to get the values from the digital thermosensor. and
 * if you just specify only one temperature unit, you can get the 
 * converted values of the specified unit 
 */
float values3 = mSensor.get_temperature(DallasTempSensorDS18Sensor::DEGREES_C);
std::cout << " Value in DEGREES_C  => " << values3 << std::endl;
values3 = mSensor.get_temperature(DallasTempSensorDS18Sensor::DEGREES_F);
std::cout << " Value in DEGREES_F  => " << values3 << std::endl;
values3 = mSensor.get_temperature(DallasTempSensorDS18Sensor::KELVIN);
std::cout << " Value in KELVIN  => " << values3 << std::endl;
```


### Version
---
V1.5.0

### Installation
---
```sh
$ git clone [git-repo-url] DallasTempSensorDS18CPP
```


### Todos
---
 - Add Code Comments
 - Test code

### License
----
The MIT License (MIT)

Copyright (c) 2015 Zhichao Wang

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

**Free Software, Hell Yeah!**

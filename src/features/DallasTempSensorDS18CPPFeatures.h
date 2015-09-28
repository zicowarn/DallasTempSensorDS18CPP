/*
 * DallasTempSensorDS18CPPFeatures.h
 *
 *  Created on: 28.09.2015
 *      Author: mrwang
 */

#ifndef DALLASTEMPSENSORDS18CPPFEATURES_H_
#define DALLASTEMPSENSORDS18CPPFEATURES_H_

#include <map>

std::map<std::string,int> create_resolv_type_str();

std::map<int, std::string> create_type_names();


class DallasTempSensorDS18Sensor{
public:

	DallasTempSensorDS18Sensor(int sensor_type, std::string sensor_id);
	virtual ~DallasTempSensorDS18Sensor();
	void say();

	const static int THERM_SENSOR_DS18S20 = 0x10;
	const static int THERM_SENSOR_DS1822 = 0x22;
	const static int THERM_SENSOR_DS18B20 = 0x28;
	const static int DEGREES_C = 0x01;
	const static int DEGREES_F = 0x02;
	const static int KELVIN = 0x03;
	static std::string BASE_DIRECTORY;
	static std::string SLAVE_FILE;


protected:

	const static int RETRY_ATTEMPS = 10;
	static float RETRY_DELAY_SECONDS;
	static std::map<std::string,int> RESOLVE_TYPE_STR;
	static std::map<int, std::string> TYPE_NAMES;

private:
	int _type;
	std::string _id;

};


#endif /* DALLASTEMPSENSORDS18CPPFEATURES_H_ */

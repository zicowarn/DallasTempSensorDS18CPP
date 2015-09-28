/*
 * DallasTempSensorDS18CPPFeatures.cpp
 *
 *  Created on: 28.09.2015
 *      Author: mrwang
 */

#include <iostream>
#include "DallasTempSensorDS18CPPFeatures.h"

std::map<std::string, int> create_resolv_type_str() {
	std::map<std::string, int> m;
	m["10"] = DallasTempSensorDS18Sensor::THERM_SENSOR_DS18S20;
	m["22"] = DallasTempSensorDS18Sensor::THERM_SENSOR_DS1822;
	m["28"] = DallasTempSensorDS18Sensor::THERM_SENSOR_DS18B20;
	return m;
}

std::map<int, std::string> create_type_names() {
	std::map<int, std::string> m;
	m[0x10] = "DS18S20";
	m[0x22] = "DS1822";
	m[0x28] = "DS18B20";
	return m;
}

std::map<std::string, int> DallasTempSensorDS18Sensor::RESOLVE_TYPE_STR = create_resolv_type_str();
std::map<int, std::string> DallasTempSensorDS18Sensor::TYPE_NAMES = create_type_names();
float DallasTempSensorDS18Sensor::RETRY_DELAY_SECONDS =  1.0 / float(DallasTempSensorDS18Sensor::RETRY_ATTEMPS);
std::string DallasTempSensorDS18Sensor::BASE_DIRECTORY = "./sys/bus/w1/devices";
std::string DallasTempSensorDS18Sensor::SLAVE_FILE = "w1_slave";


DallasTempSensorDS18Sensor::DallasTempSensorDS18Sensor(int sensor_type, std::string sensor_id){
	this->_type = sensor_type;
	this->_id = sensor_id;
	std::cout<<"create new instance"<<std::endl;
}

DallasTempSensorDS18Sensor::~DallasTempSensorDS18Sensor(){
	std::cout<<"delete new instance"<<std::endl;
}

void DallasTempSensorDS18Sensor::say(){
	std::cout<<"hello"<<std::endl;
}


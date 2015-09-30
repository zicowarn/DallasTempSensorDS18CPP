/*
 * @Title: DallasTempSensorDS18CPPFeatures.cpp
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
#include <sstream>
#include <dirent.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <string>
#include <sys/stat.h>
#include "DallasTempSensorDS18CPPFeatures.h"
#include "../error/DallasTempSensorDS18CPPErrors.h"


/********************************/
/*      Helper functions        */
/********************************/

/**
 *
 * @return
 */
std::map<std::string, int> create_resolv_type_str() {
	std::map<std::string, int> m;
	m["10"] = DallasTempSensorDS18Sensor::THERM_SENSOR_DS18S20;
	m["22"] = DallasTempSensorDS18Sensor::THERM_SENSOR_DS1822;
	m["28"] = DallasTempSensorDS18Sensor::THERM_SENSOR_DS18B20;
	return m;
}


/**
 *
 * @return
 */
std::map<int, std::string> create_type_names() {
	std::map<int, std::string> m;
	m[0x10] = "DS18S20";
	m[0x22] = "DS1822";
	m[0x28] = "DS18B20";
	return m;
}

/**
 *
 * @param directory
 * @return
 */
std::vector<std::string> listdir(std::string directory) {
	std::vector<std::string> rts;
	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(directory.c_str())) == NULL) {
		//std::cout << "Error(" << 0 << ") opening " << directory << std::endl;
		MY_THROW(DictionaryNotCorrectError,
				"dictionary is can not open " + directory);
	}
	while ((dirp = readdir(dp)) != NULL) {
		if (std::string(dirp->d_name).size() > 2) {
			rts.push_back(std::string(dirp->d_name));
			//std::cout<< "Get file name "<<std::string(dirp->d_name)<<std::endl;
		}

	}
	closedir(dp);
	if (rts.size() == 0) {
		MY_THROW(DictionaryNotCorrectError,
				"dictionary is may be not correct " + directory);
	}
	return rts;
}

/**
 *
 * @param suffix
 * @param types
 * @return
 */
bool is_sensor(std::string suffix, int types[]) {
	if (suffix.empty() && !types) {
		return false;
	} else if (!types) {
		int types[3] = { 0x11, 0x22, 0x28 };
		std::string result;
		for (unsigned a = 0; a < (sizeof(types) / sizeof(*types)); a++) {
			std::stringstream stream;
			stream << std::hex << types[a];
			result = stream.str();
			if (suffix.find(result) == 0) {
				return true;
			}
		}
	} else {
		std::string result;
		for (unsigned a = 0; a < (sizeof(types) / sizeof(*types)); a++) {
			std::stringstream stream;
			stream << std::hex << types[a];
			result = stream.str();
			if (suffix.find(result) == 0) {
				return true;
			}
		}
	}
	return false;
}


/********************************/
/* Class variable configuration */
/********************************/


/**
 *
 */
std::map<std::string, int> DallasTempSensorDS18Sensor::RESOLVE_TYPE_STR =
		create_resolv_type_str();

/**
 *
 */
std::map<int, std::string> DallasTempSensorDS18Sensor::TYPE_NAMES =
		create_type_names();

/**
 *
 */
float DallasTempSensorDS18Sensor::RETRY_DELAY_SECONDS = 1.0
		/ float(DallasTempSensorDS18Sensor::RETRY_ATTEMPS);

/**
 *
 */
std::string DallasTempSensorDS18Sensor::BASE_DIRECTORY = "./sys/bus/w1/devices";

/**
 *
 */
std::string DallasTempSensorDS18Sensor::SLAVE_FILE = "w1_slave";


/********************************/
/*     Class public functions   */
/********************************/

/**
 *
 * @param sensor_type
 * @param sensor_id
 */
DallasTempSensorDS18Sensor::DallasTempSensorDS18Sensor(int sensor_type,
		std::string sensor_id) {
	this->_type = sensor_type;
	this->_id = sensor_id;
	std::cout << "create new instance" << std::endl;
	this->_sensorpath = DallasTempSensorDS18Sensor::BASE_DIRECTORY + "/"
			+ this->slave_prefix() + this->_id + "/"
			+ DallasTempSensorDS18Sensor::SLAVE_FILE;
	int units[] = {0x01, 0x02};
	std::vector<float> values = this->get_temperatures(units);
	for(std::vector<float>::size_type i = 0; i != values.size(); i++){
		std::cout<<"values: "<<i<<" tel: "<<values[i]<<std::endl;
	}

}

/**
 *
 */
DallasTempSensorDS18Sensor::~DallasTempSensorDS18Sensor() {
	std::cout << "delete new instance" << std::endl;
}


/********************************/
/*     Class const functions    */
/********************************/

/**
 *
 * @return
 */
std::string DallasTempSensorDS18Sensor::id() const{
	return this->_id;
}


/**
 *
 * @return
 */
int DallasTempSensorDS18Sensor::type() const{
	return this->_type;
}

/**
 *
 * @return
 */
std::string DallasTempSensorDS18Sensor::type_name() const{
	std::map<int, std::string>::const_iterator it =
	DallasTempSensorDS18Sensor::TYPE_NAMES.find(this->_type);
	return it->second;
}

/**
 *
 * @param unit
 * @return
 */
float DallasTempSensorDS18Sensor::get_temperature(int unit){
	int temp_value = this->raw_sensor_value();
	if (unit == 0x01) return UNIT_FACTORS_C(temp_value);
	else if (unit == 0x02) return UNIT_FACTORS_F(temp_value);
	else if (unit == 0x02) return UNIT_FACTORS_K(temp_value);
	else MY_THROW(UnsupportUnitError, " ");
}

/**
 *
 * @return
 */
std::vector<float> DallasTempSensorDS18Sensor::get_temperatures(){
	std::vector<float> rts;
	int values[] = {0x01, 0x02, 0x03};
	std::vector<int> units(&values[0], &values[0]+3);
	int temp_value = this->raw_sensor_value();
	for(std::vector<int>::size_type i = 0; i != units.size(); i++) {
		if (units[i] == 0x01) rts.push_back(UNIT_FACTORS_C(temp_value));
		else if (units[i] == 0x02) rts.push_back(UNIT_FACTORS_F(temp_value));
		else rts.push_back(UNIT_FACTORS_K(temp_value));
	}
	return rts;
}

std::vector<float> DallasTempSensorDS18Sensor::get_temperatures(int in_units[]){
	std::vector<float> rts;
	int values[] = {0x01, 0x02, 0x03};
	std::vector<int> units(&values[0], &values[0]+3);
	int temp_value = this->raw_sensor_value();
	for (unsigned i = 0; i< (sizeof(in_units) / sizeof(*in_units)); i++){
		if ( std::find(units.begin(), units.end(), in_units[i])!=units.end()){
			if (units[i] == 0x01) rts.push_back(UNIT_FACTORS_C(temp_value));
				else if (units[i] == 0x02) rts.push_back(UNIT_FACTORS_F(temp_value));
				else if (units[i] == 0x03) rts.push_back(UNIT_FACTORS_K(temp_value));
				else MY_THROW(UnsupportUnitError, " ");
		}
		else{
			MY_THROW(UnsupportUnitError, " ");
		}
	}
	return rts;
}



/********************************/
/*     Class private functions  */
/********************************/


/**
 *
 * @param types
 * @return
 */
std::map<std::string, int> DallasTempSensorDS18Sensor::get_available_sensors(
		int types[]) {
	std::map<std::string, int> m;
	if (!types) {
		std::vector<std::string> filelist = listdir(
				DallasTempSensorDS18Sensor::BASE_DIRECTORY);
		for (std::vector<int>::size_type i = 0; i != filelist.size(); i++) {
			if (is_sensor(filelist[i], NULL)) {
				std::map<std::string, int>::const_iterator it =
						DallasTempSensorDS18Sensor::RESOLVE_TYPE_STR.find(
								filelist[i].substr(0, 2));
				m.insert(
						std::pair<std::string, int>(filelist[i].substr(3),
								it->second));
			}
		}
	} else {
		std::vector<std::string> filelist = listdir(
				DallasTempSensorDS18Sensor::BASE_DIRECTORY);
		for (std::vector<int>::size_type i = 0; i != filelist.size(); i++) {
			if (is_sensor(filelist[i], types)) {
				std::map<std::string, int>::const_iterator it =
						DallasTempSensorDS18Sensor::RESOLVE_TYPE_STR.find(
								filelist[i].substr(0, 2));
				m.insert(
						std::pair<std::string, int>(filelist[i].substr(3),
								it->second));
			}
		}
	}
	return m;
}

/**
 *
 * @return
 */
int DallasTempSensorDS18Sensor::raw_sensor_value() {
	std::vector<std::string> records;
	std::vector<std::string> targets;
	std::ifstream slave_file((this->_sensorpath).c_str());
	std::string line;
	while (std::getline(slave_file, line))
	{
		records.push_back(line);
	}
	slave_file.close();
	if (!records[0].find("YES")){
		MY_THROW(SensorNotReadyError, "Sensor is not yet ready to read temperature");
	}
	std::istringstream target_str(records[1]);
	std::string split_str;
	char split_char = '=';
	while (std::getline(target_str, split_str, split_char)){
		targets.push_back(split_str);
	}
	return atoi(targets[1].c_str());
}

/**
 *
 * @return
 */
std::string DallasTempSensorDS18Sensor::slave_prefix() {
	std::stringstream stream;
	stream << std::hex << this->_type;
	std::string result(stream.str());
	result += "-";
	return result;
}

/**
 *
 * @return
 */
bool DallasTempSensorDS18Sensor::exists(){
	struct stat sb;
	if (stat(this->_sensorpath.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
	{
	    return true;
	}
	else{
		return false;
	}
}

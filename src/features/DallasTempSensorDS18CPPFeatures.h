/*
 * @Title: DallasTempSensorDS18CPPFeatures.h
 * @Description: TODO
 * @author: mrwang
 * @Created on: 29.09.2015 23:22:40
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

#include <map>
#include <vector>
#include <string>

#ifndef DALLASTEMPSENSORDS18CPPFEATURES_H_
#define DALLASTEMPSENSORDS18CPPFEATURES_H_

#define UNIT_FACTORS_C(s) float(s*0.001)
#define UNIT_FACTORS_F(s) float(s*0.001*1.8 +32.0)
#define UNIT_FACTORS_K(s) float(s*0.001 + 273.15)

/**
 *
 * @return
 */
std::map<std::string,int> create_resolv_type_str();

/**
 *
 * @return
 */
std::map<int, std::string> create_type_names();

/**
 *
 * @param directory
 * @return
 */
std::vector<std::string> listdir(std::string directory);

/**
 *
 * @param suffix
 * @param types
 * @return
 */
bool is_sensor(std::string suffix, int types[]);

/**
 *
 */
class DallasTempSensorDS18Sensor{
public:

	/**
	 *
	 * @param sensor_type
	 * @param sensor_id
	 */
	DallasTempSensorDS18Sensor(int sensor_type, std::string sensor_id);

	/**
	 *
	 */
	virtual ~DallasTempSensorDS18Sensor();

	/**
	 *
	 * @param types
	 * @return
	 */
	static std::map<std::string, int> get_available_sensors(int types[]);

	/**
	 *
	 * @return
	 */
	virtual std::string id() const;

	/**
	 *
	 * @return
	 */
	virtual int type() const;

	/**
	 *
	 * @return
	 */
	virtual std::string type_name() const;

	/**
	 *
	 * @param unit
	 * @return
	 */
	float get_temperature(int unit);

	/**
	 *
	 * @return
	 */
	std::vector<float> get_temperatures();

	/**
	 *
	 * @param units
	 * @return
	 */
	std::vector<float> get_temperatures(int in_units[]);

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


	void _load_kernel_modules();
	/**
	 *
	 * @return
	 */
	int raw_sensor_value();

	/**
	 *
	 * @return
	 */
	std::string slave_prefix();

	/**
	 *
	 * @return
	 */
	bool exists();

	int _type;
	std::string _id;
	std::string _sensorpath;

};


#endif /* DALLASTEMPSENSORDS18CPPFEATURES_H_ */

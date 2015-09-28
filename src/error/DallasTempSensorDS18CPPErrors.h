/*
 * DallasTempSensorDS18CPPErrors.h
 *
 *  Created on: 28.09.2015
 *      Author: mrwang
 */

#ifndef DALLASTEMPSENSORDS18CPPERRORS_H_
#define DALLASTEMPSENSORDS18CPPERRORS_H_

#include <exception>
#include <string>

#define MY_THROW(ExClass, args...) do{ ExClass e(args); e.Init(__FILE__, __PRETTY_FUNCTION__, __LINE__); throw e; } while(false)

#define MY_DEFINE_EXCEPTION(ExClass, Base) ExClass(const std::string& msg="") throw(): Base(msg) {} ~ExClass() throw (){}/*override*/std::string GetClassName() const { return #ExClass;}



class DallasTempSensorDS18ErrorBase: public std::exception {
public:

	DallasTempSensorDS18ErrorBase(const std::string& msg = "") throw ();

	virtual ~DallasTempSensorDS18ErrorBase() throw ();

	void Init(const char* file, const char* func, int line);

	virtual std::string GetClassName() const;

	virtual std::string GetMessage() const;

	const char* what() const throw ();

	const std::string& ToString() const;

	std::string GetStackTrace() const;

protected:

	std::string mMesg;

	const char* mFile;

	const char* mFunc;

	int mLine;

private:
	enum {
		MAX_STACK_TRACE_SIZE = 50
	};

	void* mStackTrace[MAX_STACK_TRACE_SIZE];

	size_t mStackTraceSize;

	mutable std::string mWhat;

};


class TestException:public DallasTempSensorDS18ErrorBase
{
public:
	MY_DEFINE_EXCEPTION(TestException, DallasTempSensorDS18ErrorBase);
};


class DictionaryNotCorrectError:public DallasTempSensorDS18ErrorBase
{
public:
	MY_DEFINE_EXCEPTION(DictionaryNotCorrectError, DallasTempSensorDS18ErrorBase);
};

class KernelModuleLoadError:public DallasTempSensorDS18ErrorBase
{
public:
	MY_DEFINE_EXCEPTION(KernelModuleLoadError, DallasTempSensorDS18ErrorBase);
};

class NoSensorFoundError:public DallasTempSensorDS18ErrorBase
{
public:
	MY_DEFINE_EXCEPTION(NoSensorFoundError, DallasTempSensorDS18ErrorBase);
};

class SensorNotReadyError:public DallasTempSensorDS18ErrorBase
{
public:
	MY_DEFINE_EXCEPTION(SensorNotReadyError, DallasTempSensorDS18ErrorBase);
};

class UnsupportUnitError:public DallasTempSensorDS18ErrorBase
{
public:
	MY_DEFINE_EXCEPTION(UnsupportUnitError, DallasTempSensorDS18ErrorBase);
};

#endif /* DALLASTEMPSENSORDS18CPPERRORS_H_ */

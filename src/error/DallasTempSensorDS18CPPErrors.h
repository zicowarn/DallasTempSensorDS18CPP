/*
 * @Title: DallasTempSensorDS18CPPErrors.h
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


#ifndef DALLASTEMPSENSORDS18CPPERRORS_H_
#define DALLASTEMPSENSORDS18CPPERRORS_H_

#include <exception>
#include <string>

#define MY_THROW(ExClass, args...) do{ ExClass e(args); e.Init(__FILE__, __PRETTY_FUNCTION__, __LINE__); throw e; } while(false)

#define MY_DEFINE_EXCEPTION(ExClass, Base) ExClass(const std::string& msg="") throw(): Base(msg) {} ~ExClass() throw (){}/*override*/std::string GetClassName() const { return #ExClass;}


/**
 *
 */
class DallasTempSensorDS18ErrorBase: public std::exception {
public:

	/**
	 *
	 * @param msg
	 */
	DallasTempSensorDS18ErrorBase(const std::string& msg = "") throw ();

	/**
	 *
	 */
	virtual ~DallasTempSensorDS18ErrorBase() throw ();

	/**
	 *
	 * @param file
	 * @param func
	 * @param line
	 */
	void Init(const char* file, const char* func, int line);

	/**
	 *
	 * @return
	 */
	virtual std::string GetClassName() const;

	/**
	 *
	 * @return
	 */
	virtual std::string GetMessage() const;

	/**
	 *
	 * @return
	 */
	const char* what() const throw ();

	/**
	 *
	 * @return
	 */
	const std::string& ToString() const;

	/**
	 *
	 * @return
	 */
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

/**
 *
 */
class TestException:public DallasTempSensorDS18ErrorBase
{
public:
	MY_DEFINE_EXCEPTION(TestException, DallasTempSensorDS18ErrorBase);
};

/**
 *
 */
class DictionaryNotCorrectError:public DallasTempSensorDS18ErrorBase
{
public:
	MY_DEFINE_EXCEPTION(DictionaryNotCorrectError, DallasTempSensorDS18ErrorBase);
};

/**
 *
 */
class KernelModuleLoadError:public DallasTempSensorDS18ErrorBase
{
public:
	MY_DEFINE_EXCEPTION(KernelModuleLoadError, DallasTempSensorDS18ErrorBase);
};


/**
 *
 */
class NoSensorFoundError:public DallasTempSensorDS18ErrorBase
{
public:
	MY_DEFINE_EXCEPTION(NoSensorFoundError, DallasTempSensorDS18ErrorBase);
};

/**
 *
 */
class SensorNotReadyError:public DallasTempSensorDS18ErrorBase
{
public:
	MY_DEFINE_EXCEPTION(SensorNotReadyError, DallasTempSensorDS18ErrorBase);
};

/**
 *
 */
class UnsupportUnitError:public DallasTempSensorDS18ErrorBase
{
public:
	MY_DEFINE_EXCEPTION(UnsupportUnitError, DallasTempSensorDS18ErrorBase);
};

#endif /* DALLASTEMPSENSORDS18CPPERRORS_H_ */

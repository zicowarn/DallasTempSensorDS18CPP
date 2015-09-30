/*
 * @Title: DallasTempSensorDS18CPPErrors.cpp
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

#include <stdlib.h>
#include <cxxabi.h>
#include <execinfo.h>
#include <iostream>
#include <sstream>
#include "DallasTempSensorDS18CPPErrors.h"

using namespace std;

/**
 *
 * @param msg
 */
DallasTempSensorDS18ErrorBase::DallasTempSensorDS18ErrorBase(
		const std::string& msg) throw () :
		mMesg(msg), mFile("<unknow file>"), mFunc("<unknow func>"), mLine(-1), mStackTraceSize(
				0) {
}

/**
 *
 */
DallasTempSensorDS18ErrorBase::~DallasTempSensorDS18ErrorBase() throw () {
}

/**
 *
 * @param file
 * @param func
 * @param line
 */
void DallasTempSensorDS18ErrorBase::Init(const char* file, const char* func,
		int line) {
	mFile = file;
	mFunc = func;
	mLine = line;
	mStackTraceSize = backtrace(mStackTrace, MAX_STACK_TRACE_SIZE);

}

/**
 *
 * @return
 */
std::string DallasTempSensorDS18ErrorBase::GetClassName() const {
	return "DallasTempSensorDS18ErrorBase";
}

/**
 *
 * @return
 */
const char* DallasTempSensorDS18ErrorBase::what() const throw () {
	return ToString().c_str();
}

/**
 *
 * @return
 */
const std::string& DallasTempSensorDS18ErrorBase::ToString() const {
	if (mWhat.empty()) {
		stringstream sstr("");
		if (mLine > 0) {
			sstr << mFile << " at (" << mLine << ")";
		}
		sstr << ": " << GetClassName();
		if (!GetMessage().empty()) {
			sstr << ": " << GetMessage();
		}
		sstr << "\nStack Trace:\n";
		sstr << GetStackTrace();
		mWhat = sstr.str();
	}
	return mWhat;
}

/**
 *
 * @return
 */
std::string DallasTempSensorDS18ErrorBase::GetMessage() const {
	return mMesg;
}


/**
 *
 * @return
 */
std::string DallasTempSensorDS18ErrorBase::GetStackTrace() const {
	if (mStackTraceSize == 0)
		return "<No stack trace>\n";
	char** strings = backtrace_symbols(mStackTrace, 10);
	if (strings == NULL) // Since this is for debug only thus
						 // non-critical, don't throw an exception.
		return "<Unknown error: backtrace_symbols returned NULL>\n";

	std::string result;
	for (size_t i = 0; i < mStackTraceSize; ++i) {
		std::string mangledName = strings[i];
		std::string::size_type begin = mangledName.find('(');
		std::string::size_type end = mangledName.find('+', begin);
		if (begin == std::string::npos || end == std::string::npos) {
			result += mangledName;
			result += '\n';
			continue;
		}
		++begin;
		int status;
		char* s = abi::__cxa_demangle(
				mangledName.substr(begin, end - begin).c_str(), NULL, 0,
				&status);
		if (status != 0) {
			result += mangledName;
			result += '\n';
			continue;
		}
		std::string demangledName(s);
		free(s);
		// Ignore ExceptionBase::Init so the top frame is the
		// user's frame where this exception is thrown.
		//
		// Can't just ignore frame#0 because the compiler might
		// inline ExceptionBase::Init.
		result += mangledName.substr(0, begin);
		result += demangledName;
		result += mangledName.substr(end);
		result += '\n';
	}
	free(strings);
	return result;
}



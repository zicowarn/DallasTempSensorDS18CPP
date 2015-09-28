/*
 * DallasTempSensorDS18CPPErrors.cpp
 *
 *  Created on: 28.09.2015
 *      Author: mrwang
 */

#include <stdlib.h>
#include <cxxabi.h>
#include <execinfo.h>
#include <iostream>
#include <sstream>
#include "DallasTempSensorDS18CPPErrors.h"

using namespace std;

DallasTempSensorDS18ErrorBase::DallasTempSensorDS18ErrorBase(
		const std::string& msg) throw () :
		mMesg(msg), mFile("<unknow file>"), mFunc("<unknow func>"), mLine(-1), mStackTraceSize(
				0) {
}

DallasTempSensorDS18ErrorBase::~DallasTempSensorDS18ErrorBase() throw () {
}

void DallasTempSensorDS18ErrorBase::Init(const char* file, const char* func,
		int line) {
	mFile = file;
	mFunc = func;
	mLine = line;
	mStackTraceSize = backtrace(mStackTrace, MAX_STACK_TRACE_SIZE);

}

std::string DallasTempSensorDS18ErrorBase::GetClassName() const {
	return "DallasTempSensorDS18ErrorBase";
}

const char* DallasTempSensorDS18ErrorBase::what() const throw () {
	return ToString().c_str();
}

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

std::string DallasTempSensorDS18ErrorBase::GetMessage() const {
	return mMesg;
}

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



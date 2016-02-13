#include "PyJs.h"

PyJs::PyJs()
	:exceptions_callback(nullptr),
	PythonFrontEnd()
{
}

PyJs::PyJs(const exceptions_callback_func& _error_callback)
	: exceptions_callback(_error_callback),
	PythonFrontEnd(exceptions_callback)
{
}

PyJs::PyJs(const source_code_string& _SourceCode)
	: PythonSourceCode(_SourceCode),
	exceptions_callback(nullptr),
	PythonFrontEnd(PythonSourceCode)
{
	complie_impl();
}

PyJs::PyJs(const source_code_string& _SourceCode, exceptions_callback_func& _error_callback)
	: PythonSourceCode(_SourceCode),
	exceptions_callback(_error_callback),
	PythonFrontEnd(PythonSourceCode, exceptions_callback)
{
	complie_impl();
}

PyJs::~PyJs()
{
}

bool PyJs::exceptions()
{
	return exceptions_flag;
}

std::wstring PyJs::getExceptionsMsg()
{
	return PythonExceptionsMessage;
}

void PyJs::complie(const source_code_string& _SourceCode)
{
	PythonSourceCode = _SourceCode;
	complie_impl();
}

void PyJs::complie_impl()
{
	exceptions_flag = false;
	//TODO
}
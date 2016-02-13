#include "PyFrontend.h"

namespace PyJsFrontEnd
{
	PyFrontEnd::PyFrontEnd()
		:code(nullptr),
		exceptions_callback(nullptr),
		PythonLexer(code, exceptions_callback)
	{
	}

	PyFrontEnd::PyFrontEnd(const source_code_string& _code)
		:code(&_code),
		exceptions_callback(nullptr),
		PythonLexer(code, exceptions_callback)
	{
	}

	PyFrontEnd::PyFrontEnd(const exceptions_callback_func& _exceptions_callback)
		:code(nullptr),
		exceptions_callback(_exceptions_callback),
		PythonLexer(code, exceptions_callback)
	{
	}

	PyFrontEnd::PyFrontEnd(const source_code_string& _code
		, const exceptions_callback_func& _exceptions_callback)
		:code(&_code),
		exceptions_callback(_exceptions_callback),
		PythonLexer(code, exceptions_callback)
	{
	}

	void PyFrontEnd::complie(const source_code_string& _source_code)
	{
		code = &_source_code;
		complie_impl();
	}

	const source_code_string& PyFrontEnd::getSourceCode() const
	{
		return *code;
	}

	void PyFrontEnd::complie_impl() const
	{

	}
}
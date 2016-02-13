#ifndef __PY_JS__

#define __PY_JS__

#include <string>
#include <functional>
#include "Frontend/PyFrontend.h"

class PyJs
{
private:
	typedef PyJsFrontEnd::exceptions_callback_func exceptions_callback_func;
	typedef PyJsFrontEnd::source_code_string source_code_string;

public:
	typedef PyJsFrontEnd::exceptions::pyExceptions Python_exceptions;
	typedef PyJsFrontEnd::exceptions::exceptions_message exceptions_message;

public:
	PyJs(const PyJs&) = delete;
	PyJs(const PyJs&&) = delete;
	const PyJs& operator =(const PyJs&) = delete;
	const PyJs& operator =(const PyJs&&) = delete;

	explicit PyJs();
	explicit PyJs(const exceptions_callback_func& exceptions_callback);
	explicit PyJs(const source_code_string& _SourceCode);
	explicit PyJs(const source_code_string& _SourceCode, exceptions_callback_func& exceptions_callback);
	~PyJs();

	bool exceptions();
	std::wstring getExceptionsMsg();

	void complie(const source_code_string& _SourceCode);

private:
	void complie_impl();

private:
	exceptions_callback_func const& exceptions_callback;

	exceptions_callback_func const default_exceptions_callback = [&](const Python_exceptions& Exceptions)
	{
		exceptions_flag = true;
		PythonExceptionsMessage = Exceptions.getExceptionsMessage();
		if (exceptions_callback)
			exceptions_callback(Exceptions);
	};

	source_code_string PythonSourceCode;

	PyJsFrontEnd::PyFrontEnd PythonFrontEnd;

	exceptions_message  PythonExceptionsMessage;
	bool exceptions_flag;

};

#endif


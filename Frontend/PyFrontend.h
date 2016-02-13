#ifndef __PY_FRONTEND__

#define __PY_FRONTEND__

#include "PyCommonDef.h"
#include "PyExceptions.h"
#include "PyLexer.h"
#include "PyParser.h"

namespace PyJsFrontEnd
{
	class PyFrontEnd
	{
	public:
		PyFrontEnd(const PyFrontEnd&) = delete;
		PyFrontEnd& operator = (const PyFrontEnd&) = delete;
		PyFrontEnd& operator = (const PyFrontEnd&&) = delete;

		PyFrontEnd();
		PyFrontEnd(const source_code_string& _code);
		PyFrontEnd(const exceptions_callback_func& _exceptions_callback);
		PyFrontEnd(const source_code_string& _code
			, const exceptions_callback_func& _exceptions_callback);

		void complie(const source_code_string& _source_code);
		const source_code_string& getSourceCode() const;

	private:
		void complie_impl() const;

	private:
		const source_code_string* code;
		const exceptions_callback_func& exceptions_callback;

		lexer::pyLexer PythonLexer;
		parser::parser PythonPaser;
	};

}

#endif
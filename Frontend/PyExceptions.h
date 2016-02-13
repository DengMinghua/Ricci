#ifndef __PY_ERROR__

#define __PY_ERROR__

#include <functional>
#include "PyCommonDef.h"

namespace PyJsFrontEnd
{
	namespace exceptions
	{
		typedef ::PyJsFrontEnd::exceptions_message exceptions_message;

		class pyExceptions
		{
		public:
			struct exceptions_pos
			{
				size_t line, column, character;
			};

			typedef size_t exceptions_type;

			enum class exceptions_index :exceptions_type
			{
				UNDEFINED,				//0
				SYNTAX_ERROR,			//1
				INDENTATIONERROR,		//2
				TABERROR,				//3
			};

			pyExceptions(const exceptions_index _index = exceptions_index::UNDEFINED,
				const source_code_fregment& _code = EMPTY_WSTR,
				const exceptions_pos& _exceptions_pos = { 0,0,0 })
				:_exceptions_index(_index),
				_relative_code(_code),
				_pos(_exceptions_pos)
			{
			}

			pyExceptions(const exceptions_index _index,
				const source_code_fregment&& _code,
				const exceptions_pos& _exceptions_pos = { 0,0,0 })
				:_exceptions_index(_index),
				_relative_code(std::move(_code)),
				_pos(_exceptions_pos)
			{
			}

			const exceptions_message getExceptionsMessage() const
			{
				exceptions_message _msg;
				_msg.append(L"Line: ");
				_msg += std::to_wstring(_pos.line);
				_msg.append(L"  Column: ");
				_msg += std::to_wstring(_pos.column);
				_msg.append(L"  Character: ");
				_msg += std::to_wstring(_pos.character);
				_msg.append(L"\n");
				_msg.append(_relative_code);
				_msg.append(L"\n");
				for (size_t i = 0; i < _pos.character - 1; i++)
				{
					_msg.append(L" ");
				}
				_msg.append(L"^\n");
				_msg.append(getExceptionsTypeInfo());
				_msg.append(L"\n");
				return _msg;
			}

			inline
				const exceptions_index getExceptionsIndex() const
			{
				return _exceptions_index;
			}

			inline
				const source_code_fregment& getRelativeCode() const
			{
				return _relative_code;
			}

			inline
				const exceptions_pos& getExceptionsPosition() const
			{
				return _pos;
			}

		private:
			virtual const exceptions_message getExceptionsTypeInfo() const = 0;

			const exceptions_index _exceptions_index;
			const source_code_fregment _relative_code;
			const exceptions_pos _pos;
		};

		class pySyntaxError
			:public pyExceptions
		{
		public:
			typedef exceptions_type error_type;
			typedef exceptions_pos error_pos;

			enum class syntax_error_index :error_type
			{
				DEFAULT,										//0 invalid syntax
				UNMATCHED_JAVASCRIPT_MARK,						//1 unmatched inline JavaScript code mark
				UNEXPECTED_CHARACTER_AFTER_LINE_CONTINUATION,	//2 unexpected character after line continuation character
				EOF_IN_MULTI_LINE_STATEMENT,					//3 EOF in multi - line statement
				INVALID_TOKEN,									//4 invalid token
				EOL_WHILE_SCANNING_STRING_LITERAL,				//5 EOL while scanning string literal
																//  More...
			};

			pySyntaxError(const source_code_fregment& _code = EMPTY_WSTR,
				const error_pos& _error_pos = { 0,0,0 })
				:pyExceptions(exceptions_index::SYNTAX_ERROR, _code, _error_pos),
				_syntax_error_index(syntax_error_index::DEFAULT)
			{
			}

			pySyntaxError(const source_code_fregment&& _code,
				const error_pos& _error_pos = { 0,0,0 })
				:pyExceptions(exceptions_index::SYNTAX_ERROR, std::move(_code), _error_pos),
				_syntax_error_index(syntax_error_index::DEFAULT)
			{
			}

			pySyntaxError(const syntax_error_index _index,
				const source_code_fregment& _code = EMPTY_WSTR,
				const error_pos& _error_pos = { 0,0,0 })
				:pyExceptions(exceptions_index::SYNTAX_ERROR, _code, _error_pos),
				_syntax_error_index(_index)
			{
			}

			pySyntaxError(const syntax_error_index _index,
				const source_code_fregment&& _code,
				const error_pos& _error_pos = { 0,0,0 })
				:pyExceptions(exceptions_index::SYNTAX_ERROR, std::move(_code), _error_pos),
				_syntax_error_index(_index)
			{
			}

			inline
				const syntax_error_index getSyntaxErrorType() const
			{
				return _syntax_error_index;
			}

		private:
			const exceptions_message getExceptionsTypeInfo() const
			{
				switch (_syntax_error_index)
				{
				case syntax_error_index::DEFAULT:
					return L"SyntaxError: invalid syntax";
				case syntax_error_index::UNMATCHED_JAVASCRIPT_MARK:
					return L"SyntaxError: unmatched inline JavaScript code mark";
				case syntax_error_index::UNEXPECTED_CHARACTER_AFTER_LINE_CONTINUATION:
					return L"SyntaxError: unexpected character after line continuation character";
				case syntax_error_index::EOF_IN_MULTI_LINE_STATEMENT:
					return L"SyntaxError: EOF in multi - line statement";
				case syntax_error_index::INVALID_TOKEN:
					return L"SyntaxError: invalid token";
				case syntax_error_index::EOL_WHILE_SCANNING_STRING_LITERAL:
					return L"SyntaxError: EOL while scanning string literal";
				default:
					return L"SyntaxError: invalid syntax";
				}
			}

			const syntax_error_index _syntax_error_index;
		};

		class pyIndentationError
			:public pyExceptions
		{
		public:
			typedef exceptions_type error_type;
			typedef exceptions_pos error_pos;

			enum class indentation_error_index :error_type
			{
				UNDEFINED,				//0
				UNMATCH,				//1
				EXPECTED_BLOCK,			//2
				UNEXPECTED,				//3
			};

			pyIndentationError(const indentation_error_index _index,
				const source_code_fregment& _code = EMPTY_WSTR,
				const error_pos& _error_pos = { 0,0,0 })
				:pyExceptions(exceptions_index::INDENTATIONERROR, _code, _error_pos),
				_indentation_error_index(_index)
			{
			}

			pyIndentationError(const indentation_error_index _index,
				const source_code_fregment&& _code,
				const error_pos& _error_pos = { 0,0,0 })
				:pyExceptions(exceptions_index::INDENTATIONERROR, std::move(_code), _error_pos),
				_indentation_error_index(_index)
			{
			}

			inline
				const indentation_error_index getIndentationErrorType() const
			{
				return _indentation_error_index;
			}

		private:
			const exceptions_message getExceptionsTypeInfo() const
			{
				switch (_indentation_error_index)
				{
				case indentation_error_index::UNDEFINED:
					break;
				case indentation_error_index::UNMATCH:
					return L"IndentationError: unindent does not match any outer indentation level";
				case indentation_error_index::EXPECTED_BLOCK:
					return L"IndentationError: expected an indented block";
				case indentation_error_index::UNEXPECTED:
					return L"IndentationError: unexpected indent";
				default:
					break;
				}
				return L"IndentationError: unknow error occurred";
			}

			const indentation_error_index _indentation_error_index;
		};

		class pyTabError
			:public pyExceptions
		{
		public:
			typedef exceptions_pos error_pos;

			pyTabError(const source_code_fregment& _code = EMPTY_WSTR,
				const error_pos& _error_pos = { 0,0,0 })
				:pyExceptions(exceptions_index::TABERROR, _code, _error_pos)
			{
			}

			pyTabError(const source_code_fregment&& _code,
				const error_pos& _error_pos = { 0,0,0 })
				:pyExceptions(exceptions_index::TABERROR, std::move(_code), _error_pos)
			{
			}

		private:
			const exceptions_message getExceptionsTypeInfo() const
			{
				return L"TabError: inconsistent use of tabs and spaces in indentation";
			}
		};
	}

	typedef std::function<void(const exceptions::pyExceptions&)> exceptions_callback_func;

}

#endif
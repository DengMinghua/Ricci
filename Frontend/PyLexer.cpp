#include <unordered_map>
#include "PyLexer.h"

#ifdef _MSC_VER // for MSVC
#pragma warning(push)
#pragma warning(disable:4592)	//surpress the warning 4592
#endif

namespace PyJsFrontEnd
{
	namespace lexer
	{
		using namespace token;
		using namespace exceptions;

		typedef std::unordered_map<names_string, keywords_index> keyword_table_type;
		static const keyword_table_type keyword_table({
			{ L"False",		keywords_index::FALSE },
			{ L"None",		keywords_index::NONE },
			{ L"True",		keywords_index::TRUE },
			{ L"and",		keywords_index::AND },
			{ L"as",		keywords_index::AS },
			{ L"assert",	keywords_index::ASSERT },
			{ L"break",		keywords_index::BREAK },
			{ L"class",		keywords_index::CLASS },
			{ L"continue",	keywords_index::CONTINUE },
			{ L"def",		keywords_index::DEF },
			{ L"del",		keywords_index::DEL },
			{ L"elif",		keywords_index::ELIF },
			{ L"else",		keywords_index::ELSE },
			{ L"except",	keywords_index::EXCEPT },
			{ L"finally",	keywords_index::FINALLY },
			{ L"for",		keywords_index::FOR },
			{ L"from",		keywords_index::FROM },
			{ L"global",	keywords_index::GLOBAL },
			{ L"if",		keywords_index::IF },
			{ L"import",	keywords_index::IMPORT },
			{ L"in",		keywords_index::IN },
			{ L"is",		keywords_index::IS },
			{ L"lambda",	keywords_index::LAMBDA },
			{ L"nonlocal",	keywords_index::NONLOCAL },
			{ L"not",		keywords_index::NOT },
			{ L"or",		keywords_index::OR },
			{ L"pass",		keywords_index::PASS },
			{ L"raise",		keywords_index::RAISE },
			{ L"return",	keywords_index::RETURN },
			{ L"try",		keywords_index::TRY },
			{ L"while",		keywords_index::WHILE },
			{ L"with",		keywords_index::WITH },
			{ L"yield",		keywords_index::YIELD },
		});

		typedef std::unordered_map<names_string, operators_index> operators_table_type;
		static const operators_table_type operators_table({
			{ L"+",		operators_index::ADD },
			{ L"-",		operators_index::SUB },
			{ L"*",		operators_index::MUL },
			{ L"**",	operators_index::POW },
			{ L"/",		operators_index::DIV },
			{ L"//",	operators_index::FLOORDIV },
			{ L"%",		operators_index::MOD },
			{ L"<<",	operators_index::LSHIFT },
			{ L">>",	operators_index::RSHIFT },
			{ L"&",		operators_index::AND },
			{ L"|",		operators_index::OR },
			{ L"^",		operators_index::XOR },
			{ L"~",		operators_index::INVERT },
			{ L"<",		operators_index::LT },
			{ L">",		operators_index::GT },
			{ L"<=",	operators_index::LE },
			{ L">=",	operators_index::GE },
			{ L"==",	operators_index::EQ },
			{ L"!=",	operators_index::NE },
		});

		typedef std::unordered_map<names_string, delimiters_index> delimiters_table_type;
		static const delimiters_table_type delimiters_table({
			{ L"(",		delimiters_index::LP },
			{ L")",		delimiters_index::RP },
			{ L"[",		delimiters_index::LB },
			{ L"]",		delimiters_index::RB },
			{ L"{",		delimiters_index::LCB },
			{ L"}",		delimiters_index::RCB },
			{ L",",		delimiters_index::COMMA },
			{ L":",		delimiters_index::COLON },
			{ L".",		delimiters_index::PERIOD },
			{ L";",		delimiters_index::SEMICOLON },
			{ L"@",		delimiters_index::AT },
			{ L"=",		delimiters_index::EQU },
			{ L"+=",	delimiters_index::INCREMENT },
			{ L"-=",	delimiters_index::DECREMENT },
			{ L"*=",	delimiters_index::SQUARING },
			{ L"/=",	delimiters_index::DIVIDE_ },
			{ L"//=",	delimiters_index::FLOORDIV_ },
			{ L"@=",	delimiters_index::AT_ },
			{ L"&=",	delimiters_index::MOD_ },
			{ L"|=",	delimiters_index::OR_ },
			{ L"^=",	delimiters_index::XOR },
			{ L">>=",	delimiters_index::RSHIFT_ },
			{ L"<<=",	delimiters_index::LSHIFT_ },
			{ L"**=",	delimiters_index::POW_ },
		});

		template<class _Ty>
		inline
			_Ty getIndexFromTable(const names_string& _keyword, const std::unordered_map<names_string, _Ty>& _table)
		{
			auto _iter = _table.find(_keyword);
			if (_iter != _table.end())
				return _iter->second;
			else
				return _Ty::UNDEFINED;
		}

		inline
			keywords_index getKeywordIndex(const names_string& _keyword)
		{
			return getIndexFromTable(_keyword, keyword_table);
		}

		inline
			operators_index getOperatorsIndex(const names_string& _operators)
		{
			return getIndexFromTable(_operators, operators_table);
		}

		inline
			delimiters_index getDelimitersIndex(const names_string& _delimiters)
		{
			return getIndexFromTable(_delimiters, delimiters_table);
		}

		inline
			bool validIdentifiersCharacter(wchar_t _ch)
		{
			return (_ch == L'_' || isalphaX(_ch) || isdigitX(_ch));
		}

		inline
			bool isIndentationCharacter(wchar_t _ch)
		{
			return (_ch == L' ' || _ch == L'\t');
		}

		inline
			source_code_string::size_type getLineBeginIndex(const source_code_string& _code,
				source_code_string::size_type _pos = 0)
		{
			auto _index(_pos);
			while (_index > 0 && _code[_index] != L'\n')
			{
				_index--;
			}
			return _index > 0 ? _index + 1 : 0;
		}

		inline
			source_code_string::size_type getLineEndIndex(const source_code_string& _code,
				source_code_string::size_type  _pos = 0)
		{
			auto _index(_pos);
			auto _code_length(_code.length());
			while (_index < _code_length &&
				(_code[_index] != L'\n' && !(_code[_index] == L'\r' && _index + 1 < _code_length && _code[_index] == L'\n')))
			{
				_index++;
			}
			return --_index;
		}

		//Implement of pyLexer_impl

		pyLexer_impl::pyLexer_impl(const exceptions_callback_func& _exceptionsCallback)
			:exceptionsCallback(_exceptionsCallback),
			haltFlag(false),
			index({ 0,1,1,1 }),
			remainingDedent(0)
		{
			IndentationStack.reserve(4);
		}

		pyLexer_impl::pyLexer_impl(const source_code_string* const _code,
			const exceptions_callback_func& _exceptionsCallback)
			:PythonCode(_code),
			exceptionsCallback(_exceptionsCallback),
			haltFlag(false),
			index({ 0,1,1,1 }),
			remainingDedent(0)
		{
			IndentationStack.reserve(4);
			IndentationStack.push_back(0);
		}

		pyLexer_impl::~pyLexer_impl()
		{
		}

		pyToken::pToken pyLexer_impl::getNextToken_impl()
		{
			return getNextToken_x();
		}

		void pyLexer_impl::initSet_impl(const source_code_string* const _code)
		{
			haltFlag = false;
			index = { 0,1,1,1 };
			remainingDedent = 0;
			IndentationStack.clear();
			IndentationStack.push_back(0);
			DelimitersStack.clear();
			PythonCode = _code;
		}

		void pyLexer_impl::skipBlank()
		{
			const source_code_string& _code = *PythonCode;
			auto _pos = index.pos;
			decltype(_pos) _Count(0);

			while (_pos + _Count < _code.length() &&
				(
					_code[_pos + _Count] == L' ' ||
					_code[_pos + _Count] == L'\t' ||
					_code[_pos + _Count] == L'\f' ||
					_code[_pos + _Count] == L'\v'
					))
			{
				_Count++;
			}
			shiftPos(_Count);
		}

		void pyLexer_impl::shiftPos(const size_t _Off)
		{
			const auto& code(*PythonCode);
			for (size_t i = 0; i < _Off; i++)
			{
				auto _pos = index.pos + i;
				if (code[_pos] == L'\n')
				{
					index.line++;
					index.column = 1;
					index.character = 1;
				}
				else
				{
					index.character++;
					index.column += code[_pos] == L'\t' ? TAB_STOP : 1;
				}
			}
			index.pos += _Off;
		}

		void pyLexer_impl::shiftPosToNextLine()
		{
			const auto& code(*PythonCode);
			auto _new_pos = getLineEndIndex(code, index.pos) + 1;
			if (_new_pos < code.length() && code[_new_pos] == L'\n')
				_new_pos++;
			if (_new_pos < code.length())
			{
				index.pos = _new_pos;
				index.line++;
				index.column = 1;
				index.character = 1;
			}
			else
			{
				shiftPos(_new_pos - index.pos);
			}
		}

		pyToken::token_pos pyLexer_impl::currentPos()
		{
			return{ index.line ,index.column ,index.character };
		}

		wchar_t pyLexer_impl::escapeOctIndex(const source_code_fregment& _num_str)
		{
			return convertOctStringTo<wchar_t>(_num_str);
		}

		wchar_t pyLexer_impl::escapeHexIndex(const source_code_fregment& _num_str)
		{
			return convertHexStringTo<wchar_t>(_num_str);
		}

		wchar_t pyLexer_impl::escapeCharacter()
		{
			const source_code_string& _code = *PythonCode;
			auto _code_length(_code.length());
			auto _pos = index.pos;
			if (_code[_pos] == L'\\' && _pos + 1 < _code_length)
			{
				switch (_code[_pos + 1])
				{

#define ESCAPE_CASE(_ch,_ret) case _ch: shiftPos(2); return _ret

					ESCAPE_CASE(L'\n', L'\x0');
					ESCAPE_CASE(L'\\', L'\\');
					ESCAPE_CASE(L'\'', L'\'');
					ESCAPE_CASE(L'\"', L'\"');
					ESCAPE_CASE(L'a', L'\a');
					ESCAPE_CASE(L'b', L'\b');
					ESCAPE_CASE(L'f', L'\f');
					ESCAPE_CASE(L'n', L'\n');
					ESCAPE_CASE(L'r', L'\r');
					ESCAPE_CASE(L't', L'\t');
					ESCAPE_CASE(L'v', L'\v');

				case L'x':
				{
					auto _temp(_code.substr(index.pos, 3));
					if (validHexNumber(_temp))
					{
						shiftPos(3);
						return escapeHexIndex(_temp);
					}
					else
					{
						raise_exceptions<pySyntaxError>();
						return 0;
					}
				}
				case L'u':
				{
					auto _temp(_code.substr(index.pos, 4));
					if (validHexNumber(_temp))
					{
						shiftPos(5);
						return escapeHexIndex(_temp);
					}
					else
					{
						raise_exceptions<pySyntaxError>();
						return 0;
					}
				}

				default:
					if (_code[_pos + 1] >= L'0' && _code[_pos + 1] <= L'7')
					{
						size_t _len = 1;
						shiftPos(2);
						if (_pos + 2 < _code.length() && _code[_pos + 2] >= L'0' && _code[_pos + 2] <= L'7')
						{
							shiftPos(1);
							_len++;
						}
						if (_pos + 3 < _code.length() && _code[_pos + 3] >= L'0' && _code[_pos + 3] <= L'7')
						{
							shiftPos(1);
							_len++;
						}
						auto _temp(_code.substr(index.pos, _len));
						return escapeOctIndex(_temp);
					}
					else
					{
						shiftPos(1);
						return L'\\';	//Unrecognized escape character
					}

#undef ESCAPE_CASE
				}
			}
			return static_cast<wchar_t>(0);
		}

		pyToken::pToken pyLexer_impl::typesStringLiteralsToken(const string_type_index _type)
		{
			const source_code_string& _code = *PythonCode;
			literals_string _temp;
			auto _init_pos = index.pos;
			auto _cur_pos = _init_pos;
			bool _implicitLineJoining = false;
			auto tokenPos = currentPos();

			if ((_cur_pos + 2 < _code.length()) &&
				(_code[_cur_pos] == _code[_cur_pos + 1] && _code[_cur_pos] == _code[_cur_pos + 2]))
			{
				shiftPos(3);
				_cur_pos += 3;
				_implicitLineJoining = true;
			}
			else
			{
				shiftPos(1);
				_cur_pos += 1;
			}

			while (_cur_pos < _code.length())
			{
				if ((!_implicitLineJoining) && _code[_cur_pos] == _code[_init_pos])
				{
					shiftPos(1);
					break;
				}	//end mark of string ' or " 
				else if ((_implicitLineJoining) &&
					(_cur_pos + 2 < _code.length() &&
						(
							_code[_cur_pos] == _code[_init_pos] &&
							_code[_cur_pos + 1] == _code[_init_pos] &&
							_code[_cur_pos + 2] == _code[_init_pos])
						))
				{
					shiftPos(3);
					break;
				}	//end mark of string ''' or """

				if (_code[_cur_pos] == L'\\' &&
					(_type != string_type_index::RAW || _type != string_type_index::RAW_BYTE))
				{
					auto _esc_ch = escapeCharacter();
					if (haltFlag)
						return nullptr;
					if (_esc_ch)
						_temp.push_back(_esc_ch);
					continue;
				}
				else if (_code[_cur_pos] == L'\\' &&
					(_type == string_type_index::RAW || _type == string_type_index::RAW_BYTE))
				{
					_temp.push_back(L'\\');
					_temp.push_back(_code[_cur_pos + 1]);
					shiftPos(2);
					continue;
				}

				if (_code[_cur_pos] == L'\n' && !_implicitLineJoining)
				{
					raise_exceptions<pySyntaxError>(pySyntaxError::syntax_error_index::EOL_WHILE_SCANNING_STRING_LITERAL);
					return nullptr;
				}

				_temp.push_back(_code[_cur_pos]);
				shiftPos(1);
				_cur_pos = index.pos;
			}

			switch (_type)
			{
			case string_type_index::DEFAULT_BYTE:case string_type_index::RAW_BYTE:
				return pyToken::pToken(new token::literals(
					std::move(_temp),
					literals::literals_type::STRING,
					tokenPos));
			case string_type_index::DEFAULT:case string_type_index::RAW:
				return pyToken::pToken(new token::literals(
					std::move(_temp),
					literals::literals_type::STRING,
					tokenPos));
			default:
				return nullptr;
			}
		}

		pyToken::pToken pyLexer_impl::stringLiteralsToken()
		{
			const source_code_string& _code = *PythonCode;
			auto _pos = index.pos;

			if (_code[_pos] == L'\'' || _code[_pos] == L'\"')
			{
				return typesStringLiteralsToken(string_type_index::DEFAULT);
			}
			else if (_pos + 1 < _code.length() &&
				(_code[_pos + 1] == L'\'' || _code[_pos + 1] == L'\"'))
			{
				switch (tolower(_code[_pos + 1]))
				{
				case L'r':	//raw string
					shiftPos(1);
					return typesStringLiteralsToken(string_type_index::RAW);
				case L'b':	//byte string
					shiftPos(1);
					return typesStringLiteralsToken(string_type_index::DEFAULT_BYTE);
				case L'u':	//unicode string
					shiftPos(1);
					return typesStringLiteralsToken(string_type_index::DEFAULT);
				default:
					raise_exceptions<pySyntaxError>();
					return nullptr;
				}
			}
			else if (_pos + 2 < _code.length() &&
				(_code[_pos + 2] == L'\'' || _code[_pos + 2] == L'\"'))
			{
				if ((tolower(_code[_pos + 1]) == L'b' && tolower(_code[_pos + 2]) == L'r') ||
					(tolower(_code[_pos + 1]) == L'r' && tolower(_code[_pos + 2]) == L'b'))
					//raw byte string
				{
					shiftPos(2);
					return typesStringLiteralsToken(string_type_index::RAW_BYTE);
				}
			}
			return nullptr;
		}

		pyToken::pToken pyLexer_impl::numericLiteralsToken()
		{
			const source_code_string& _code = *PythonCode;
			auto _pos = index.pos;
			decltype(_pos) _Count(0);
			literals_string _temp;
			literals::literals_type _type(literals::literals_type::UNDEFINED);

			if (_pos + 1 < _code.length() &&
				(_code[_pos] == L'0'))
			{
				switch (_code[_pos + 1])
				{

#define NUMERIC_LITERALS(_Type,_Cond) \
			do{ _Count += 2; \
				_type = _Type; \
				while (_pos + _Count < _code.length() && \
						_Cond(_code[_pos + _Count]))\
				{ _temp.push_back(_code[_pos + _Count]); _Count++; }\
				if (_Count == 0 || \
					(_pos + _Count < _code.length() && (isalphaX(_code[_pos + _Count]) || _code[_pos + _Count] == '_'))) \
				{ goto error; } \
				goto number_got; \
			}while (0)

				case L'b':
					NUMERIC_LITERALS(literals::literals_type::BININTEGER, isbindigitX);
				case L'o':
					NUMERIC_LITERALS(literals::literals_type::OCTINTEGER, isoctdigitX);
				case L'x':
					NUMERIC_LITERALS(literals::literals_type::HEXINTEGER, ishexdigitX);
				default:
					_temp.push_back(L'0');
					_Count++;
					break;
				}

#undef NUMERIC_LITERALS

			}
			//detect the type of numeric literals(prefix)

			while (_pos + _Count < _code.length())
			{
				auto _Off = _pos + _Count;
				if (isdigitX(_code[_Off]))
				{
					_temp.push_back(_code[_Off]);
					_Count++;
					continue;
				}
				else if (_type == literals::literals_type::UNDEFINED &&
					_code[_Off] == L'.')
				{
					_type = literals::literals_type::FLOAT;
					_temp.push_back(_code[_Off]);
					_Count++;
					continue;
				}
				else if (isalphaX(_code[_Off]) || _code[_Off]=='_')
				{
					goto error;
				}
				break;
			}

			if (_type == literals::literals_type::UNDEFINED)
			{
				_type = literals::literals_type::DECIMALINTEGER;
			}
			else if (_type == literals::literals_type::FLOAT &&
				_pos + _Count < _code.length() &&
				tolower(_code[_pos + _Count]) == L'e')
			{
				_temp.push_back(_code[_pos + _Count]);
				_Count++;
				if (_pos + _Count < _code.length() &&
					(_code[_pos + _Count] == L'+' || _code[_pos + _Count] == L'-'))
				{
					_temp.push_back(_code[_pos + _Count]);
					_Count++;
				}
				decltype(_Count) _Count_exp = 0;
				auto _Off = _pos + _Count;
				while (_Off + _Count_exp < _code.length() &&
					isdigitX(_code[_Off + _Count_exp]))
				{
					_temp.push_back(_code[_Off + _Count_exp]);
					_Count_exp++;
				}
				if (_Count_exp > 0)
					_Count += _Count_exp;
				else
					goto error;
			}
			//exponent part of float

		number_got:;

			if (tolower(_code[_pos + _Count]) == L'j')
			{
				switch (_type)
				{
				case literals::literals_type::BININTEGER:
					_temp.push_back(L'b');
					_type = literals::literals_type::IMAGINARY_INTPART;
					break;
				case literals::literals_type::OCTINTEGER:
					_temp.push_back(L'o');
					_type = literals::literals_type::IMAGINARY_INTPART;
					break;
				case literals::literals_type::DECIMALINTEGER:
					_temp.push_back(L'd');
					_type = literals::literals_type::IMAGINARY_INTPART;
					break;
				case literals::literals_type::HEXINTEGER:
					_temp.push_back(L'x');
					_type = literals::literals_type::IMAGINARY_INTPART;
					break;
				case literals::literals_type::FLOAT:
					_type = literals::literals_type::IMAGINARY_FLOATNUMBER;
					break;
				default:
					break;
				}
				_Count++;
			}
			//detect the type of numeric literals(suffix)

			auto tokenPos = currentPos();
			shiftPos(_Count);
			return pyToken::pToken(new token::literals(
				std::move(_temp),
				_type,
				tokenPos));

		error:;
			raise_exceptions<pySyntaxError>(pySyntaxError::syntax_error_index::INVALID_TOKEN);
			return nullptr;
		}

		pyToken::pToken pyLexer_impl::literalsToken()
		{
			const source_code_string& _code = *PythonCode;
			auto _pos = index.pos;

			if (isdigitX(_code[_pos]))
			{
				return numericLiteralsToken();
			}
			else
			{
				return stringLiteralsToken();
			}
		}

		pyToken::pToken pyLexer_impl::identifiersAndKeywordsToken()
		{
			const source_code_string& _code = *PythonCode;
			auto _pos = index.pos;
			decltype(_pos) _Count(0);
			while (_pos + _Count < _code.length() &&
				validIdentifiersCharacter(_code[_pos + _Count]))
			{
				_Count++;
			}
			if (_Count > 0)
			{
				auto tokenPos = currentPos();
				shiftPos(_Count);
				names_string name(_code.substr(_pos, _Count));
				auto _key_word_index = getKeywordIndex(name);
				if (_key_word_index != keywords_index::UNDEFINED)
				{
					return pyToken::pToken(new keywords(_key_word_index, tokenPos));
				}
				else
				{
					return pyToken::pToken(new identifiers(std::move(name), tokenPos));
				}
			}
			return nullptr;
		}

		pyToken::pToken pyLexer_impl::indentationToken()
		{
			const source_code_string& _code = *PythonCode;
			auto _pos = index.pos;
			decltype(_pos) _Count(0);
#ifdef ENABLE_MIX_TAB_SPACE_ERROR
			bool spaceIndentation = (_code[_pos] == ' ');
			bool tabIndentation = !spaceIndentation;
#endif
			size_t indentation_level(0);

			if (remainingDedent > 0)
			{
				remainingDedent--;
				return pyToken::pToken(new indent(currentPos()));
			}

			while (_pos + _Count < _code.length() &&
				isIndentationCharacter(_code[_pos + _Count]))
			{
				if (_code[_pos + _Count] == '\t')
				{
#ifndef ENABLE_MIX_TAB_SPACE_ERROR
					indentation_level += indentation_level == 0 ?
						TAB_STOP :
						TAB_STOP - indentation_level%TAB_STOP;
#else
					indentation_level += TAB_STOP;
					if (!tabIndentation)
					{
						raise_exceptions<pyTabError>();
						return nullptr;
					}
#endif
				}
				else
				{
					indentation_level++;
				}
				_Count++;
			}
			auto tokenPos = currentPos();
			shiftPos(_Count);
			auto _top_level = IndentationStack.back();
			if (indentation_level == _top_level)
			{
				return pyToken::pToken(new condent(tokenPos));
			}
			else if (indentation_level < _top_level)
			{
				while (indentation_level < IndentationStack.back())
				{
					IndentationStack.pop_back();
					remainingDedent++;
				}
				if (indentation_level != IndentationStack.back())
				{
					raise_exceptions<pyIndentationError>(pyIndentationError::indentation_error_index::UNMATCH);
					return nullptr;
				}
				else
				{
					remainingDedent--;
					return pyToken::pToken(new dedent(tokenPos));
				}
			}
			IndentationStack.push_back(indentation_level);
			return pyToken::pToken(new indent(tokenPos));
		}

		inline
			bool matchjavascriptInlineMark(const source_code_string& _code, size_t _pos)
		{
			static const wchar_t* mark = L"/*JavaScript*/";
			for (size_t i = 0; i < 14 && _pos + i < _code.length(); i++)
			{
				if (_code[_pos + i] != mark[i])
					return false;
			}
			return true;
		}

		pyToken::pToken pyLexer_impl::javascriptInlineToken()
		{
			const source_code_string& _code = *PythonCode;
			auto _pos = index.pos;

			JavaScript_code_string _temp;

			_temp.reserve(64);
			if (matchjavascriptInlineMark(_code, _pos))
			{
				auto tokenPos = currentPos();
				_pos += 14;
				while (_pos + 13 < _code.length() &&
					!matchjavascriptInlineMark(_code, _pos))
				{
					_temp.push_back(_code[_pos]);
					_pos++;
				}
				if (_pos + 14 >= _code.length())
				{
					shiftPos(_code.length() - index.pos - 1);
					raise_exceptions<pySyntaxError>(pySyntaxError::syntax_error_index::UNMATCHED_JAVASCRIPT_MARK);
					return nullptr;
				}
				_pos += _pos + 14;
				shiftPos(_pos - index.pos);
				return pyToken::pToken(new javascript_inline_code(std::move(_temp), tokenPos));
			}
			return nullptr;
		}

		pyToken::pToken pyLexer_impl::operatorsToken()
		{
			const source_code_string& _code = *PythonCode;
			auto _pos = index.pos;

			for (size_t i = 2; i > 0; i--)
			{
				if (_pos + i - 1 < _code.length())
				{
					auto _operatorsIndex = getOperatorsIndex(_code.substr(_pos, i));
					if (_operatorsIndex != operators_index::UNDEFINED)
					{
						auto tokenPos = currentPos();
						shiftPos(i);
						return pyToken::pToken(new token::operators(_operatorsIndex, tokenPos));
					}
				}
			}
			return nullptr;
		}

		pyToken::pToken pyLexer_impl::delimitersToken()
		{
			const source_code_string& _code = *PythonCode;
			auto _pos = index.pos;

			for (size_t i = 3; i > 0; i--)
			{
				if (_pos + i - 1 < _code.length())
				{
					auto _delimitersIndex = getDelimitersIndex(_code.substr(_pos, i));
					if (_delimitersIndex != delimiters_index::UNDEFINED)
					{
						if (_delimitersIndex == delimiters_index::LP ||
							_delimitersIndex == delimiters_index::LB ||
							_delimitersIndex == delimiters_index::LCB)
						{
							DelimitersStack.push_back(_delimitersIndex);
						}
						else if ((_delimitersIndex == delimiters_index::RP && DelimitersStack.back() == delimiters_index::LP) ||
							(_delimitersIndex == delimiters_index::RB && DelimitersStack.back() == delimiters_index::LB) ||
							(_delimitersIndex == delimiters_index::RCB && DelimitersStack.back() == delimiters_index::LCB))
						{
							DelimitersStack.pop_back();
						}
						auto tokenPos = currentPos();
						shiftPos(i);
						return pyToken::pToken(new token::delimiters(_delimitersIndex, tokenPos));
					}
				}
			}
			return nullptr;
		}

		pyToken::pToken pyLexer_impl::getNextToken_x()
		{
			const source_code_string& _code = *PythonCode;
			auto _pos = index.pos;

			if (_pos < _code.length())
			{
				if (remainingDedent > 0)
				{
					remainingDedent--;
					return pyToken::pToken(new dedent(currentPos()));
				}
				if (index.character == 1 && DelimitersStack.empty())	//scan the begin of a new line
				{
					auto _indent_token = indentationToken();
					if (_indent_token)
					{
						_pos = index.pos;
						if ((_pos < _code.length() && _code[_pos] != L'#') &&
							_pos != getLineEndIndex(_code, _pos))
						{
							if (_indent_token->getTag() != pyToken::tag::CONDENT)
								return _indent_token;
						}
						else if (_pos < _code.length() && _code[_pos] == L'#')
						{
							if (_indent_token->getTag() == pyToken::tag::INDENT)
								IndentationStack.pop_back();
							shiftPosToNextLine();
							return getNextToken_x();
						}
					}
					else
					{
						return nullptr;	//error halt
					}
				}

				skipBlank();
				_pos = index.pos;

				if (_pos + 1 < _code.length() &&
					_code[_pos] == L'/' && _pos + 13 < _code.length() && _code[_pos + 1] == L'*')
				{
					return javascriptInlineToken();
				}

				if (_code[_pos] == L'\\')
				{
					if (_pos + 1 < _code.length())
					{
						if (_code[_pos + 1] == L'\n' ||
							(_pos + 2 < _code.length() && (_code[_pos + 1] == L'\r' && _code[_pos + 2] == L'\n')))
						{
							shiftPosToNextLine();
							skipBlank();
							return getNextToken_x();
						}
						else
						{
							raise_exceptions<pySyntaxError>(pySyntaxError::syntax_error_index::UNEXPECTED_CHARACTER_AFTER_LINE_CONTINUATION);
							return nullptr;
						}
					}
					else
					{
						raise_exceptions<pySyntaxError>(pySyntaxError::syntax_error_index::EOF_IN_MULTI_LINE_STATEMENT);
						return nullptr;
					}
				}
				//Explicit line joining

				if (_code[_pos] == L'\n')
				{
					if (DelimitersStack.empty())
					{
						auto tokenPos = currentPos();
						shiftPos(1);
						return pyToken::pToken(new newline(tokenPos));
					}
					else
					{
						shiftPosToNextLine();
						skipBlank();
						return getNextToken_x();
					}
				}
				//Implicit line joining

				if (_code[_pos] == L'#')
				{
					shiftPosToNextLine();
					return getNextToken_x();
				}
				//comment

				pyToken::pToken _ret;
				if (_code[_pos] == L'\'' || _code[_pos] == L'\"')
				{
					return stringLiteralsToken();
				}
				else if (isdigitX(_code[_pos]) || isalphaX(_code[_pos]))
				{
					_ret = literalsToken();
					if (_ret)
						return _ret;
					if (!haltFlag)
					{
						_ret = identifiersAndKeywordsToken();
						if (_ret)
							return _ret;
					}
					else
					{
						return nullptr;
					}
				}
				else
				{
					_ret = delimitersToken();
					if (_ret)
						return _ret;
					_ret = operatorsToken();
					if (_ret)
						return _ret;
				}

				raise_exceptions<pySyntaxError>();	//unknown symbol ($ ? `)
				return nullptr;
			}
			else
			{
				return pyToken::pToken(new termination(currentPos()));
			}
		}

		void pyLexer_impl::exceptions(const pyExceptions& Msg)
		{
			haltFlag = true;
			if (exceptionsCallback)
				exceptionsCallback(Msg);
		}

		//Implement of pyLexer

		pyLexer::pyLexer(const exceptions_callback_func& _exceptionsCallback)
			:pyLexer_impl(_exceptionsCallback)
		{
		}

		pyLexer::pyLexer(const source_code_string* const _code,
			const exceptions_callback_func& _exceptionsCallback)
			: pyLexer_impl(_code, _exceptionsCallback)
		{
		}

		pyLexer::~pyLexer()
		{
		}

		bool pyLexer::end() const
		{
			return getPos() >= PythonCode->length();
		}

		size_t pyLexer::getPos() const
		{
			return index.pos;
		}

		bool pyLexer::exceptions() const
		{
			return haltFlag;
		}

		void pyLexer::initSet(const source_code_string* const _code)
		{
			initSet_impl(_code);
		}

		pyToken::pToken pyLexer::getNextToken()
		{
			return getNextToken_impl();
		}
	}
}

#ifdef _MSC_VER // for MSVC
#pragma warning(pop)
#endif
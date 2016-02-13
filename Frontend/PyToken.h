#ifndef __PY_TOKEN__

#define __PY_TOKEN__

#include <string>
#include "PyCommonDef.h"
#include "../CommonLib/memory.h"
#include "../CommonLib/number.h"

namespace PyJsFrontEnd
{
	using namespace PyJsComLib;

	namespace lexer
	{
		namespace token
		{

			class pyToken
				:public irc_ptr_default_base		//enable intrusive reference counting pointer
			{
			public:
				typedef size_t tag_value_type;

				struct token_pos
				{
					size_t line, column, character;
				};

				enum class tag :tag_value_type
				{
					UNDEFINED,				//0
					NEWLINE,				//1
					INDENT,					//2
					CONDENT,				//3
					DEDENT,					//4
					IDENTIFIERS,			//5
					KEYWORDS,				//6
					LITERALS,				//7
					OPERATORS,				//8
					DELIMITERS,				//9
					TERMINATION,			//10
					JAVASCRIPT_CODE			//11
				};

				typedef tag tag_type;
				typedef irc_ptr<pyToken> pToken;
				typedef pyToken* pToken_trivial;

				pyToken()
					:_tag(tag::UNDEFINED),
					_pos({ 0,0,0 })
				{
				}

				explicit pyToken(const tag_type& _t,
					const token_pos& _p)
					:_tag(_t),
					_pos(_p)
				{
				}

				inline
					tag_type getTag() const
				{
					return _tag;
				}

				inline
					const token_pos& getPos() const
				{
					return _pos;
				}

			private:
				const tag_type _tag;
				const token_pos _pos;
			};

			class newline
				:public pyToken
			{
			public:
				newline(const token_pos& _p)
					:pyToken(tag::NEWLINE, _p)
				{
				}
			};

			class indent
				:public pyToken
			{
			public:
				indent(const token_pos& _p)
					:pyToken(tag::INDENT, _p)
				{
				}
			};

			class condent
				:public pyToken
			{
			public:
				condent(const token_pos& _p)
					:pyToken(tag::CONDENT, _p)
				{
				}
			};

			class dedent
				:public pyToken
			{
			public:
				dedent(const token_pos& _p)
					:pyToken(tag::DEDENT, _p)
				{
				}
			};

			class termination
				:public pyToken
			{
			public:
				termination(const token_pos& _p)
					:pyToken(tag::TERMINATION, _p)
				{
				}
			};

			class pyNameToken
				:public pyToken
			{
			public:

				pyNameToken(const tag_type& _tag, const names_string& _name_, const token_pos& _p)
					:pyToken(_tag, _p),
					_name(_name_)
				{
				}

				pyNameToken(const tag_type& _tag, names_string&& _name_, const token_pos& _p)
					:pyToken(_tag, _p),
					_name(std::move(_name_))
				{
				}

				inline
					const names_string& getName() const
				{
					return _name;
				}

			protected:
				const names_string _name;
			};

			class pyIndexToken
				:public pyToken
			{
			public:
				typedef size_t index_type;

				pyIndexToken(const tag_type& _tag, const index_type _index, const token_pos& _p)
					:pyToken(_tag, _p),
					index(_index)
				{
				}

			protected:
				inline
					index_type getRawIndex() const
				{
					return index;
				}

			private:
				const index_type index;
			};

			class identifiers
				:public pyNameToken
			{
			public:
				explicit identifiers(const names_string& _value, const token_pos& _p)
					:pyNameToken(tag::IDENTIFIERS, _value, _p)
				{
				}

				explicit identifiers(names_string&& _value, const token_pos& _p)
					:pyNameToken(tag::IDENTIFIERS, std::move(_value), _p)
				{
				}
			};

			class keywords
				:public pyIndexToken
			{
			public:
				explicit keywords(const keywords_index _index = keywords_index::UNDEFINED)
					:pyIndexToken(tag::KEYWORDS, to_underlying(_index), { 0,0,0 })
				{
				}

				explicit keywords(const keywords_index _index, const token_pos& _p)
					:pyIndexToken(tag::KEYWORDS, to_underlying(_index), _p)
				{
				}

				inline
					keywords_index getIndex() const
				{
					return static_cast<keywords_index>(getRawIndex());
				}
			};

			class literals
				:public pyNameToken
			{
			public:
				typedef tag_value_type literals_type_value;

				enum class literals_type : literals_type_value
				{
					UNDEFINED,				//0
					STRING,					//1
					BYTES_STRING,			//2
											//String
					BININTEGER,				//3
					OCTINTEGER,				//4
					DECIMALINTEGER,			//5
					HEXINTEGER,				//6
											//Integer
					FLOAT,					//7
											//Float
					IMAGINARY_FLOATNUMBER,	//8
					IMAGINARY_INTPART		//9
											//Imaginary
				};

				typedef Python_integer literals_integer;
				typedef Python_float literals_float;
				typedef Python_imaginary literals_imaginary;
				typedef source_code_fregment literals_string;

				explicit literals(const names_string& _value, const token_pos& _p)
					:pyNameToken(tag::LITERALS, _value, _p),
					_literals_type(literals_type::UNDEFINED)
				{
				}

				explicit literals(const names_string&& _value, const token_pos& _p)
					:pyNameToken(tag::LITERALS, std::move(_value), _p),
					_literals_type(literals_type::UNDEFINED)
				{
				}

				explicit literals(const names_string& _value,
					const literals_type _type,
					const token_pos& _p)
					:pyNameToken(tag::LITERALS, _value, _p),
					_literals_type(_type),
					_value(constructLiteralsValue(pyNameToken::_name, _literals_type))
				{
				}

				explicit literals(names_string&& _value,
					const literals_type _type,
					const token_pos& _p)
					:pyNameToken(tag::LITERALS, std::move(_value), _p),
					_literals_type(_type),
					_value(constructLiteralsValue(pyNameToken::_name, _literals_type))
				{
				}

				inline
					const literals_type getLiteralsType() const
				{
					return _literals_type;
				}

				inline
					const Any& getLiteralsValue() const
				{
					return _value;
				}

			private:
				static
					const Any constructLiteralsValue(const names_string& _value,
						const literals_type _type)
				{
					switch (_type)
					{
					case literals_type::STRING: case literals_type::BYTES_STRING:
						return Any(std::ref(_value));
					case literals_type::BININTEGER:
						return Any(convertBinStringTo<BigNum>(_value));
					case literals_type::OCTINTEGER:
						return Any(convertOctStringTo<BigNum>(_value));
					case literals_type::DECIMALINTEGER:
						return Any(convertDecStringTo<BigNum>(_value));
					case literals_type::HEXINTEGER:
						return Any(convertHexStringTo<BigNum>(_value));
					case literals_type::FLOAT:
						return Any(static_cast<Python_float>(std::stod(_value)));
					case literals_type::IMAGINARY_FLOATNUMBER:
					{
						return Any(Python_imaginary(Python_literals_real_number_type::FLOAT,
							static_cast<Python_float>(std::stod(_value))));
					}
					case literals_type::IMAGINARY_INTPART:
					{
						auto _mark = _value.back();
						auto __value = const_cast<names_string&>(_value);
						__value.pop_back();
						switch (_mark)
						{
						case L'd':
							return Any(Python_imaginary(Python_literals_real_number_type::DECIMAL,
								convertDecStringTo<BigNum>(_value)));
						case L'h':
							return Any(Python_imaginary(Python_literals_real_number_type::HEX,
								convertHexStringTo<BigNum>(_value)));
						case L'b':
							return Any(Python_imaginary(Python_literals_real_number_type::BINARY,
								convertBinStringTo<BigNum>(_value)));
						case L'o':
							return Any(Python_imaginary(Python_literals_real_number_type::OCTAL,
								convertOctStringTo<BigNum>(_value)));
						}
						break;
					}
					default:
						break;
					}
					return Any();
				}

				const literals_type _literals_type;
				Any _value;
			};

			class operators
				:public pyIndexToken
			{
			public:
				explicit operators(const operators_index _index = operators_index::UNDEFINED)
					:pyIndexToken(tag::OPERATORS, to_underlying(_index), { 0,0,0 })
				{
				}

				explicit operators(const operators_index _index, const token_pos& _p)
					:pyIndexToken(tag::OPERATORS, to_underlying(_index), _p)
				{
				}

				inline
					operators_index getIndex() const
				{
					return static_cast<operators_index>(getRawIndex());
				}
			};

			class delimiters
				:public pyIndexToken
			{
			public:
				explicit delimiters(const delimiters_index _index = delimiters_index::UNDEFINED)
					:pyIndexToken(tag::DELIMITERS, to_underlying(_index), { 0,0,0 })
				{
				}

				explicit delimiters(const delimiters_index _index, const token_pos& _p)
					:pyIndexToken(tag::DELIMITERS, to_underlying(_index), _p)
				{
				}

				inline
					delimiters_index getIndex() const
				{
					return static_cast<delimiters_index>(getRawIndex());
				}
			};

			class javascript_inline_code
				:public pyToken
			{
			public:
				explicit javascript_inline_code(const JavaScript_code_string& _code,
					const token_pos& _p)
					:pyToken(tag::JAVASCRIPT_CODE, _p),
					_JavaScript_code(_code)
				{
				}

				explicit javascript_inline_code(const JavaScript_code_string&& _code,
					const token_pos& _p)
					:pyToken(tag::JAVASCRIPT_CODE, _p),
					_JavaScript_code(std::move(_code))
				{
				}

				inline
					const JavaScript_code_string& getJavaScriptCode() const
				{
					return _JavaScript_code;
				}

			private:
				const JavaScript_code_string _JavaScript_code;
			};
		}
	}
}

#endif
#include <iostream>
#include <unordered_map>

#include "../PyJs.h"

void PyLexer_Test()
{
	using namespace PyJsComLib;
	using namespace PyJsFrontEnd;
	using namespace lexer;
	using namespace lexer::token;

#define _reverse(_x,_y) {(_y), (_x)}
	typedef std::unordered_map<keywords_index, names_string> keyword_table_type;
	static const keyword_table_type keyword_table_r({
		_reverse(L"False",		keywords_index::FALSE),
		_reverse(L"None",		keywords_index::NONE),
		_reverse(L"True",		keywords_index::TRUE),
		_reverse(L"and",		keywords_index::AND),
		_reverse(L"as",			keywords_index::AS),
		_reverse(L"assert",		keywords_index::ASSERT),
		_reverse(L"break",		keywords_index::BREAK),
		_reverse(L"class",		keywords_index::CLASS),
		_reverse(L"continue",	keywords_index::CONTINUE),
		_reverse(L"def",		keywords_index::DEF),
		_reverse(L"del",		keywords_index::DEL),
		_reverse(L"elif",		keywords_index::ELIF),
		_reverse(L"else",		keywords_index::ELSE),
		_reverse(L"except",		keywords_index::EXCEPT),
		_reverse(L"finally",	keywords_index::FINALLY),
		_reverse(L"for",		keywords_index::FOR),
		_reverse(L"from",		keywords_index::FROM),
		_reverse(L"global",		keywords_index::GLOBAL),
		_reverse(L"if",			keywords_index::IF),
		_reverse(L"import",		keywords_index::IMPORT),
		_reverse(L"in",			keywords_index::IN),
		_reverse(L"is",			keywords_index::IS),
		_reverse(L"lambda",		keywords_index::LAMBDA),
		_reverse(L"nonlocal",	keywords_index::NONLOCAL),
		_reverse(L"not",		keywords_index::NOT),
		_reverse(L"or",			keywords_index::OR),
		_reverse(L"pass",		keywords_index::PASS),
		_reverse(L"raise",		keywords_index::RAISE),
		_reverse(L"return",		keywords_index::RETURN),
		_reverse(L"try",		keywords_index::TRY),
		_reverse(L"while",		keywords_index::WHILE),
		_reverse(L"with",		keywords_index::WITH),
		_reverse(L"yield",		keywords_index::YIELD),
	});
	typedef std::unordered_map<operators_index, names_string> operators_table_type;
	static const operators_table_type operators_table_r({
		_reverse(L"+",		operators_index::ADD),
		_reverse(L"-",		operators_index::SUB),
		_reverse(L"*",		operators_index::MUL),
		_reverse(L"**",		operators_index::POW),
		_reverse(L"/",		operators_index::DIV),
		_reverse(L"//",		operators_index::FLOORDIV),
		_reverse(L"%",		operators_index::MOD),
		_reverse(L"<<",		operators_index::LSHIFT),
		_reverse(L">>",		operators_index::RSHIFT),
		_reverse(L"&",		operators_index::AND),
		_reverse(L"|",		operators_index::OR),
		_reverse(L"^",		operators_index::XOR),
		_reverse(L"~",		operators_index::INVERT),
		_reverse(L"<",		operators_index::LT),
		_reverse(L">",		operators_index::GT),
		_reverse(L"<=",		operators_index::LE),
		_reverse(L">=",		operators_index::GE),
		_reverse(L"==",		operators_index::EQ),
		_reverse(L"!=",		operators_index::NE),
	});

	typedef std::unordered_map<delimiters_index, names_string> delimiters_table_type;
	static const delimiters_table_type delimiters_table_r({
		_reverse(L"(",		delimiters_index::LP),
		_reverse(L")",		delimiters_index::RP),
		_reverse(L"[",		delimiters_index::LB),
		_reverse(L"]",		delimiters_index::RB),
		_reverse(L"{",		delimiters_index::LCB),
		_reverse(L"}",		delimiters_index::RCB),
		_reverse(L",",		delimiters_index::COMMA),
		_reverse(L":",		delimiters_index::COLON),
		_reverse(L".",		delimiters_index::PERIOD),
		_reverse(L";",		delimiters_index::SEMICOLON),
		_reverse(L"@",		delimiters_index::AT),
		_reverse(L"=",		delimiters_index::EQU),
		_reverse(L"+=",		delimiters_index::INCREMENT),
		_reverse(L"-=",		delimiters_index::DECREMENT),
		_reverse(L"*=",		delimiters_index::SQUARING),
		_reverse(L"/=",		delimiters_index::DIVIDE_),
		_reverse(L"//=",	delimiters_index::FLOORDIV_),
		_reverse(L"@=",		delimiters_index::AT_),
		_reverse(L"&=",		delimiters_index::MOD_),
		_reverse(L"|=",		delimiters_index::OR_),
		_reverse(L"^=",		delimiters_index::XOR),
		_reverse(L">>=",	delimiters_index::RSHIFT_),
		_reverse(L"<<=",	delimiters_index::LSHIFT_),
		_reverse(L"**=",	delimiters_index::POW_),
	});

	std::wstring code = L"\
def perm(l):\n\
        # Compute the list of all permutations of l\n\
    if len(l) <= 1:\n\
                  return[l]\n\
    r = []\n\
    for i in range(len(l)) :\n\
             s = l[:i] + l[i + 1:]\n\
             p = perm(s)\n\
             for x in p :\n\
              r.append(l[i:i + 1] + x)\n\
    return r";

	std::wcout << code << std::endl;
	std::wcout << std::endl;

	pyLexer lexer_test(&code, [&](const ::PyJsFrontEnd::exceptions::pyExceptions& _exceptions) {
		std::wcout << std::endl;
		std::wcout << _exceptions.getExceptionsMessage() << std::endl;
	});
	auto token = lexer_test.getNextToken();
	size_t indent(0);
	bool innl(false);	//in new line indention

	auto nl = [&]()		//new line
	{
		if (innl)
		{
			for (size_t i = 0; i < indent; i++)
			{
				std::cout << ' ';
			}
			innl = false;
		}
	};

	while (token)
	{
		switch (token->getTag())
		{
		case ::PyJsFrontEnd::lexer::token::pyToken::tag::UNDEFINED:
			std::cout << std::endl;
			break;
		case ::PyJsFrontEnd::lexer::token::pyToken::tag::NEWLINE:
			innl = true;
			std::cout << ';' << std::endl;
			break;
		case ::PyJsFrontEnd::lexer::token::pyToken::tag::INDENT:
			nl();
			indent += 4;
			std::cout << "{\n";
			innl = true;
			break;
		case ::PyJsFrontEnd::lexer::token::pyToken::tag::CONDENT:
			break;
		case ::PyJsFrontEnd::lexer::token::pyToken::tag::DEDENT:
			indent -= 4;
			nl();
			std::cout << "}\n";
			innl = true;
			break;
		case ::PyJsFrontEnd::lexer::token::pyToken::tag::IDENTIFIERS:
			nl();
			std::cout << "ID(";
			std::wcout << raw_pointer_cast<::PyJsFrontEnd::lexer::token::identifiers>(token)->getName();
			std::cout << ") ";
			break;
		case ::PyJsFrontEnd::lexer::token::pyToken::tag::KEYWORDS:
			nl();
			std::cout << "KW(\"";
			std::wcout << keyword_table_r.at(raw_pointer_cast<::PyJsFrontEnd::lexer::token::keywords>(token)->getIndex()) << "\")";
			std::cout << " ";
			break;
		case ::PyJsFrontEnd::lexer::token::pyToken::tag::LITERALS:
		{
			nl();
			std::cout << "CONST(\"";
			auto ptr = raw_pointer_cast<::PyJsFrontEnd::lexer::token::literals>(token);
			switch (ptr->getLiteralsType())
			{
			case ::PyJsFrontEnd::lexer::token::literals::literals_type::STRING:
			case ::PyJsFrontEnd::lexer::token::literals::literals_type::BYTES_STRING:
				std::wcout << ptr->getLiteralsValue().value<const std::wstring&>();
				break;
			case ::PyJsFrontEnd::lexer::token::literals::literals_type::BININTEGER:
			case ::PyJsFrontEnd::lexer::token::literals::literals_type::OCTINTEGER:
			case ::PyJsFrontEnd::lexer::token::literals::literals_type::DECIMALINTEGER:
			case ::PyJsFrontEnd::lexer::token::literals::literals_type::HEXINTEGER:
				std::cout << ptr->getLiteralsValue().value<BigNum>().to_string();
				break;
			case ::PyJsFrontEnd::lexer::token::literals::literals_type::FLOAT:
				std::cout << ptr->getLiteralsValue().value<double>();
				break;
			case ::PyJsFrontEnd::lexer::token::literals::literals_type::IMAGINARY_FLOATNUMBER:
				std::cout << ptr->getLiteralsValue().value<Python_imaginary>().coeff._float_ << 'j';
				break;
			case ::PyJsFrontEnd::lexer::token::literals::literals_type::IMAGINARY_INTPART:
				std::cout << ptr->getLiteralsValue().value<Python_imaginary>().coeff._int_.to_string() << 'j';
				break;
			}
			std::cout << "\") ";
			break;
		}
		case ::PyJsFrontEnd::lexer::token::pyToken::tag::OPERATORS:
			nl();
			std::cout << "OP(\"";
			std::wcout << operators_table_r.at(raw_pointer_cast<::PyJsFrontEnd::lexer::token::operators>(token)->getIndex()) << "\")";
			std::cout << " ";
			break;
		case ::PyJsFrontEnd::lexer::token::pyToken::tag::DELIMITERS:
			nl();
			std::cout << "SYMB(\"";
			std::wcout << delimiters_table_r.at(raw_pointer_cast<::PyJsFrontEnd::lexer::token::delimiters>(token)->getIndex()) << "\")";
			std::cout << " ";
			break;
		case ::PyJsFrontEnd::lexer::token::pyToken::tag::TERMINATION:
			std::cout << ';' << std::endl;
			for (int i = indent; i >= 0; i -= 4)
			{
				for (int j = 0; j < i; j++)
					std::cout << " ";
				std::cout << "}\n";
			}
			std::cout << "END_OF_CODE" << std::endl;
			goto end;
		case ::PyJsFrontEnd::lexer::token::pyToken::tag::JAVASCRIPT_CODE:
			nl();
			std::cout << "JAVASCRIPT_CODE: {";
			std::wcout << raw_pointer_cast<::PyJsFrontEnd::lexer::token::javascript_inline_code>(token)->getJavaScriptCode() << L"} ";
			break;
		default:
			break;
		}
		token = lexer_test.getNextToken();
	}
end:;
	std::cin.get();
	return ;
}
#ifndef __PY_COMMON_DEF__

#define __PY_COMMON_DEF__

#include "../CommonLib/number.h"

#define EMPTY_WSTR L""
#define UNDEFINED_INDEX 0

#define TAB_STOP 8
#define ENABLE_MIX_TAB_SPACE_ERROR

namespace PyJsFrontEnd
{
	using namespace PyJsComLib;

	typedef size_t index_type;

	typedef std::wstring source_code_string;
	typedef std::wstring JavaScript_code_string;
	typedef std::wstring exceptions_message;

	typedef source_code_string source_code_fregment;
	typedef source_code_fregment names_string;
	typedef source_code_fregment literals_string;

	enum class Python_literals_real_number_type :index_type
	{
		DECIMAL,		//0
		HEX,			//1
		BINARY,			//2
		OCTAL,			//3
		FLOAT,			//4
	};

	typedef BigNum Python_integer;
	typedef double Python_float;
	struct Python_imaginary
	{
		Python_literals_real_number_type coeff_type;
		struct _coeff
		{
			Python_integer _int_;
			Python_float _float_;

			_coeff(const Python_integer& _int)
				:_int_(_int), _float_(0.0f)
			{
			}

			_coeff(Python_integer&& _int)
				:_int_(std::move(_int)), _float_(0.0f)
			{
			}

			_coeff(Python_float _float)
				:_float_(_float)
			{
			}
		}coeff;

		Python_imaginary(const Python_literals_real_number_type _type,
			Python_integer& _int)
			:coeff_type(_type), coeff(_int)
		{
		}

		Python_imaginary(const Python_literals_real_number_type _type,
			Python_integer&& _int)
			:coeff_type(_type), coeff(std::move(_int))
		{
		}

		Python_imaginary(const Python_literals_real_number_type _type,
			Python_float _float)
			:coeff_type(_type), coeff(_float)
		{
		}
	};

	template <class _Ty,
		typename _ELE>
		inline
		bool in(_Ty&& set, _ELE&& element)
	{
		return set.find(element) != set.end();
	}

	namespace lexer
	{

		namespace token
		{

			enum class keywords_index :index_type
			{
				UNDEFINED,	//0
				FALSE,		//1
				NONE,		//2
				TRUE,		//3
				AND,		//4
				AS,			//5
				ASSERT,		//6
				BREAK,		//7
				CLASS,		//8
				CONTINUE,	//9
				DEF,		//10
				DEL,		//11
				ELIF,		//12
				ELSE,		//13
				EXCEPT,		//14
				FINALLY,	//15
				FOR,		//16
				FROM,		//17
				GLOBAL,		//18
				IF,			//19
				IMPORT,		//20
				IN,			//21
				IS,			//22
				LAMBDA,		//23
				NONLOCAL,	//24
				NOT,		//25
				OR,			//26
				PASS,		//27
				RAISE,		//28
				RETURN,		//29
				TRY,		//30
				WHILE,		//31
				WITH,		//32
				YIELD,		//33
			};

			enum class operators_index :index_type
			{
				UNDEFINED,	//0
				ADD,		//1  +
				SUB,		//2  -
				MUL,		//3  *
				POW,		//4  **
				DIV,		//5  /
				FLOORDIV,	//6  //
				MOD,		//7  %
				LSHIFT,		//8  <<
				RSHIFT,		//9  >>
				AND,		//10 &
				OR,			//11 |
				XOR,		//12 ^
				INVERT,		//13 ~
				LT,			//14 <
				GT,			//15 >
				LE,			//16 <=
				GE,			//17 >=
				EQ,			//18 ==
				NE,			//19 !=
			};

			enum class delimiters_index :index_type
			{
				UNDEFINED,	//0
				LP,			//1  (
				RP,			//2  )
				LB,			//3  [
				RB,			//4  ]
				LCB,		//5	 {
				RCB,		//6  }
				COMMA,		//7  ,
				COLON,		//8  :
				PERIOD,		//9  .
				SEMICOLON,	//10 ;
				AT,			//11 @
				EQU,		//12 =
				INCREMENT,	//13 +=
				DECREMENT,	//14 -=
				SQUARING,	//15 *=
				DIVIDE_,	//16 /=
				FLOORDIV_,	//17 //=
				AT_,		//18 @=
				MOD_,		//19 &=
				OR_,		//20 |=
				XOR,		//21 ^=
				RSHIFT_,	//22 >>=
				LSHIFT_,	//23 <<=
				POW_,		//24 **=
			};
		}

		enum class string_type_index :index_type
		{
			UNDEFINED,		//0
			DEFAULT,		//1
			RAW,			//2
			DEFAULT_BYTE,	//1
			RAW_BYTE,		//2
		};

	}

}

#endif

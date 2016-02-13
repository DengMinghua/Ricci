#ifndef __PY_LEXER__

#define __PY_LEXER__

#include <vector>
#include "PyCommonDef.h"
#include "PyToken.h"
#include "PyExceptions.h"

namespace PyJsFrontEnd
{
	namespace lexer
	{
		using token::pyToken;
		using namespace exceptions;

		class pyLexer_impl
		{
		public:
			pyLexer_impl(const exceptions_callback_func& _exceptionsCallback);
			pyLexer_impl(const source_code_string* const _code,
				const exceptions_callback_func& _exceptionsCallback);
			~pyLexer_impl();

			pyToken::pToken getNextToken_impl();
			void initSet_impl(const source_code_string* const _code);

		private:
			void skipBlank();
			void shiftPos(const size_t _Off);
			void shiftPosToNextLine();
			pyToken::token_pos currentPos();

			static wchar_t escapeOctIndex(const source_code_fregment& _num_str);
			static wchar_t escapeHexIndex(const source_code_fregment& _num_str);
			wchar_t escapeCharacter();

			pyToken::pToken typesStringLiteralsToken(const string_type_index _type);
			pyToken::pToken stringLiteralsToken();
			pyToken::pToken numericLiteralsToken();
			pyToken::pToken literalsToken();
			pyToken::pToken identifiersAndKeywordsToken();
			pyToken::pToken indentationToken();
			pyToken::pToken operatorsToken();
			pyToken::pToken delimitersToken();
			pyToken::pToken javascriptInlineToken();
			pyToken::pToken getNextToken_x();

			void exceptions(const pyExceptions& Msg);

			template<class _Err,
			class... _Types,
			class = typename std::enable_if<std::is_convertible<_Err, pyExceptions>::value,
				void>::type>
				inline
				void raise_exceptions(_Types&&... _Args)
			{
				auto _begin_index = getLineBeginIndex(*PythonCode, index.pos);
				auto _end_index = getLineEndIndex(*PythonCode, index.pos);
				exceptions(_Err(std::forward<_Types>(_Args)...,
					PythonCode->substr(_begin_index, _end_index - _begin_index + 1),
					{
						index.line,
						index.column,
					index.character
					}));
			}

		protected:
			struct _index
			{
				size_t pos;
				size_t line, column, character;
			} index;

			bool haltFlag;  //error exit
			exceptions_callback_func exceptionsCallback;

			const source_code_string* PythonCode;
			std::vector<size_t> IndentationStack;
			size_t remainingDedent;
			std::vector<token::delimiters_index> DelimitersStack;	//for Implicit line joining
		};

		class pyLexer
			:protected pyLexer_impl
		{
		public:
			pyLexer(const exceptions_callback_func& _exceptionsCallback);
			pyLexer(const source_code_string* const _code,
				const exceptions_callback_func& _exceptionsCallback);

			~pyLexer();

			pyLexer(const pyLexer&) = delete;
			pyLexer& operator = (const pyLexer&) = delete;
			pyLexer& operator = (const pyLexer&&) = delete;

			bool end() const;
			size_t getPos() const;
			bool exceptions() const;

			void initSet(const source_code_string* const _code);
			pyToken::pToken getNextToken();
		};
	}
}

#endif
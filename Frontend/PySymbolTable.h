#ifndef __PY_SYMBOL__

#define __PY_SYMBOL__

#include "PyCommonDef.h"
#include <vector>
#include <tuple>

namespace PyJsFrontEnd
{
	template<class... _Types>
	class pySymbolTableBase
	{
	public:
		typedef std::tuple<typename std::decay<_Types>::type...> _Bargs;
		typedef std::vector<_Bargs> table_type;
		typedef typename table_type::size_type index_type;

		pySymbolTableBase()
		{
		}

		~pySymbolTableBase()
		{
		}

		template<class... _Types>
		inline
			void setElement(index_type _index, _Types&&... _Args)
		{
			table[_index] = _Bargs(std::forward<_Types>(_Args)...)
		}

		template<class... _Types>
		inline
			index_type pushElement(_Types&&... _Args)
		{
			table.emplace_back(std::forward<_Types>(_Args)...);
			return size() - 1;
		}

		void popElement()
		{
			table.pop_back();
		}

		inline
			const _Bargs& getElement(const index_type _index) const
		{
			return table[_index];
		}

		inline
			index_type size() const
		{
			return table.size();
		}
	private:
		std::vector<_Bargs> table;
	};

	class object_type_info
	{
		//TODO
	};

	class identifiers_table
		:public pySymbolTableBase<names_string>	//TODO
	{
	public:
		identifiers_table()
		{
			this->pushElement(L"");	//0 reserved for undefined
		}

		~identifiers_table()
		{

		}

	private:
	};

	class literals_type_info
	{
	public:
		enum class type :size_t
		{
			UNDEFINED,			//0
			STRING,				//1
			BYTES_LITERALS,		//2
			INTEGER,			//3
			FLOAT,				//4
			IMAGINARY,			//5
		};
	};

	class literals_table
		:public pySymbolTableBase<names_string, literals_type_info::type>	//TODO
	{
	public:
		using type = literals_type_info::type;

		literals_table()
		{
			this->pushElement(L"", type::UNDEFINED);	//0 reserved for undefined
		}

		~literals_table()
		{

		}

	private:
	};

	class keywords_table
	{
		
	};

	class operators_table
	{
		
	};

	class delimiters_table
	{
		
	};

}

#endif
#ifndef __PYJS_COM_LIB_NUMBERS__

#define __PYJS_COM_LIB_NUMBERS__

#include <string>
#include <vector>
#include <limits>
#include <cstdint>

namespace PyJsComLib
{

	constexpr
		size_t round_to_decbase_impl(size_t x,
			size_t value)
	{
		return x * 10 <= value ?
			round_to_decbase_impl(x * 10, value) :
			x;
	}

	constexpr
		size_t round_to_decbase(size_t value)
	{
		return value < 10 ? 1 : round_to_decbase_impl(1, value / 10) * 10;
	}

	constexpr
		size_t log_binbase_impl(size_t x,
			size_t n,
			size_t value)
	{
		return x * 2 <= value ?
			log_binbase_impl(x * 2, n + 1, value) :
			n;
	}

	constexpr
		size_t log_binbase(size_t value)
	{
		return value < 2 ? 0 : log_binbase_impl(1, 0, value / 2) + 1;
	}

	constexpr
		size_t log_octbase_impl(size_t x,
			size_t n,
			size_t value)
	{
		return x * 8 <= value ?
			log_octbase_impl(x * 8, n + 1, value) :
			n;
	}

	constexpr
		size_t log_octbase(size_t value)
	{
		return value < 8 ? 0 : log_octbase_impl(1, 0, value / 8) + 1;
	}

	constexpr
		size_t log_decbase_impl(size_t x,
			size_t n,
			size_t value)
	{
		return x * 10 <= value ?
			log_decbase_impl(x * 10, n + 1, value) :
			n;
	}

	constexpr
		size_t log_decbase(size_t value)
	{
		return value < 10 ? 0 : log_decbase_impl(1, 0, value / 10) + 1;
	}

	constexpr
		size_t log_hexbase_impl(size_t x,
			size_t n,
			size_t value)
	{
		return x * 16 <= value ?
			log_hexbase_impl(x * 16, n + 1, value) :
			n;
	}

	constexpr
		size_t log_hexbase(size_t value)
	{
		return value < 16 ? 0 : log_hexbase_impl(1, 0, value / 16) + 1;
	}

	inline
		size_t log_decbase_rt(const size_t value)
	{
		size_t count = 0;
		for (size_t i = 1; i <= value / 10; i++)
		{
			count++;
			i *= 10;
		}
		return count;
	}

	constexpr
		size_t cpow_impl(size_t _n, size_t _x, size_t _y)
	{
		return _y>0 ?
			cpow_impl(_n * _x, _x, _y - 1) :
			_n;
	}

	constexpr
		size_t cpow(size_t _x, size_t _y)
	{
		return _y < 1 ? 1 : cpow_impl(1, _x, _y);
	}

	inline
		size_t ipow(size_t _x, size_t _y)
	{
		size_t _n(1);
		while (_y > 0)
		{
			_n *= _x;
			_y--;
		}
		return _n;
	}

	template<typename _Ty>
	inline
		_Ty max(_Ty _x, _Ty _y)
	{
		return _x > _y ? _x : _y;
	}

	template<typename _Ty>
	inline
		_Ty min(_Ty _x, _Ty _y)
	{
		return _x < _y ? _x : _y;
	}

	constexpr auto ele_num_sup = round_to_decbase(std::numeric_limits<uint32_t>::max());
	constexpr auto ele_num_sup_len = log_decbase(ele_num_sup);

	class BigNum
	{
	public:
		typedef uint32_t ele_type;

		//TODO
		//inline BigNum operator-(const ele_type) const throw();
		//inline BigNum operator-(const BigNum &) const throw();
		//inline BigNum operator/(const ele_type) const throw();
		//inline BigNum operator/(const BigNum &) const throw();
		//inline BigNum operator-=(const ele_type) throw();
		//inline BigNum operator-=(const BigNum &) throw();
		//inline BigNum operator/=(const ele_type) throw();
		//inline BigNum operator/=(const BigNum &) throw();

		//inline bool operator>(const BigNum &) const;
		//inline bool operator>(const ele_type t) const;
		//inline bool operator<(const BigNum &) const;
		//inline bool operator<(const ele_type t) const;
		//inline bool operator>=(const BigNum &) const;
		//inline bool operator>=(const ele_type t) const;
		//inline bool operator<=(const BigNum &) const;
		//inline bool operator<=(const ele_type t) const;
		//inline bool operator==(const BigNum &) const;
		//inline bool operator==(const ele_type t) const;
		//inline bool operator!=(const BigNum &) const;
		//inline bool operator!=(const ele_type t) const;

		BigNum()
		{
			num.push_back(0);
		}

		explicit
			BigNum(const ele_type _x)
		{
			num.push_back(_x);
		}

		explicit
			BigNum(const std::string& _str)
		{
			size_t count(ele_num_sup_len);
			ele_type base(1);
			for (size_t i = _str.length() - 1; ; i--)
			{
				count++;
				base *= 10;
				if (count > ele_num_sup_len)
				{
					num.push_back(0);
					count = 1;
					base = 1;
				}
				if ('0' <= _str[i] && _str[i] <= '9')
				{
					num.back() = num.back() + base*(_str[i] - '0');
				}
				else
				{
					num.clear();
					num.push_back(0);
					num.shrink_to_fit();
					return;
				}
				if (i == 0)
					break;
			}
		}

		explicit
			BigNum(const std::wstring& _str)
		{
			size_t count(9);
			for (size_t i = _str.length() - 1; ; i--)
			{
				count++;
				if (count > ele_num_sup_len)
				{
					num.push_back(0);
					count = 0;
				}
				if (L'0' <= _str[i] && _str[i] <= L'9')
				{
					num.back() = num.back() * 10 + (_str[i] - L'0');
				}
				else
				{
					num.clear();
					num.push_back(0);
					num.shrink_to_fit();
					return;
				}
				if (i == 0)
					break;
			}
		}

		
		BigNum(const BigNum& _other)
			:num(_other.num)
		{
		}

		BigNum(BigNum&& _other)
			: num(std::move(_other.num))
		{
		}

		inline
			BigNum& operator=(const BigNum::ele_type _x) throw()
		{
			num.clear();
			num.push_back(_x);
			num.shrink_to_fit();
			return *this;
		}

		inline
			BigNum& operator=(const BigNum& _other) throw()
		{
			num = _other.num;
			num.shrink_to_fit();
			return *this;
		}

		inline
			BigNum& operator=(BigNum&& _other) throw()
		{
			num = std::move(_other.num);
			num.shrink_to_fit();
			return *this;
		}

		inline
			BigNum operator+(const ele_type _x) const throw()
		{
			BigNum _ret(*this);
			_ret.inc(0, _x);
			return _ret;
		}

		inline
			BigNum operator+(const BigNum& _other) const throw()
		{
			BigNum _ret;
			size_t _min = min(size(), _other.size());
			for (size_t i = 0; i < _min; i++)
			{
				_ret.inc(i, num[i] + _other.num[i]);
			}
			return _ret;
		}

		inline
			BigNum operator*(const ele_type _x) const throw()
		{
			BigNum _ret;
			_ret.num.reserve(size());
			for (size_t i = 0; i < size(); i++)
			{
				_ret.inc(i, static_cast<dele_type>(num[i])* static_cast<dele_type>(_x));
			}
			return _ret;
		}

		inline
			BigNum operator*(const BigNum &_other) const throw()
		{
			BigNum _ret;
			size_t _index;
			_ret.num.reserve(size() + _other.size());
			for (size_t i = 0; i < size(); i++)
			{
				for (size_t j = 0; j < _other.size(); j++)
				{
					_index = i + j;
					_ret.inc(_index, static_cast<dele_type>(num[i]) * static_cast<dele_type>(_other.num[j]));
				}
			}
			return _ret;
		}

		inline
			BigNum& operator+=(const ele_type _x) throw()
		{
			inc(0, _x);
			return *this;
		}

		inline
			BigNum& operator+=(const BigNum & _other) throw()
		{
			size_t len = _other.size();
			for (size_t i = 0; i < len; i++)
			{
				inc(i, _other.num[i]);
			}
			return *this;
		}

		inline
			BigNum& operator*=(const ele_type _x) throw()
		{
			BigNum _temp(std::move(*this));
			num.clear();
			num.reserve(_temp.size() + 1);
			for (size_t i = 0; i < _temp.size(); i++)
			{
				inc(i, static_cast<dele_type>(_temp.num[i])* static_cast<dele_type>(_x));
			}
			return *this;
		}

		inline
			BigNum& operator*=(const BigNum& _other) throw()
		{
			size_t len = size();
			BigNum _temp(std::move(*this));
			size_t _index;
			num.clear();
			num.reserve(_temp.size() + _other.size());
			for (size_t i = 0; i < len; i++)
			{
				for (size_t j = 0; j < _other.size(); j++)
				{
					_index = i + j;
					inc(_index, static_cast<dele_type>(_temp.num[i]) * static_cast<dele_type>(_other.num[j]));
				}
			}
			return *this;
		}

		inline
			operator bool() const
		{
			for (auto i : num)
			{
				if (i > 0)
					return true;
			}
			return false;
		}

		inline
			operator ele_type() const
		{
			if (size() > 0)
				return num[0];
			else
				return 0;
		}

		inline
			void swap(BigNum& _other)
		{
			std::swap(num, _other.num);
		}

		std::string to_string() const
		{
			std::string _str;
			if (size() > 0)
				_str.append(std::to_string(num[size() - 1]));
			for (size_t i = size() - 1; i > 0; i--)
			{
				_str.append(ele_num_sup_len - log_decbase_rt(num[i - 1]) - 1, '0');
				_str.append(std::to_string(num[i - 1]));
			}
			if (_str.empty())
				_str = "0";
			return _str;
		}

		std::wstring to_wstring() const
		{
			std::wstring _wstr;
			if (size()>0)
				_wstr.append(std::to_wstring(num[size() - 1]));
			for (size_t i = size() - 1; i > 0; i--)
			{
				_wstr.append(ele_num_sup_len - log_decbase_rt(num[i - 1]) - 1, '0');
				_wstr.append(std::to_wstring(num[i - 1]));
			}
			if (_wstr.empty())
				_wstr = L"0";
			return _wstr;
		}

	private:
		typedef uint64_t dele_type;

		void inc(size_t _index, dele_type _num)
		{
			while (_num > 0)
			{
				while (_index >= size())
					num.push_back(0);
				num[_index] += static_cast<ele_type>(_num % ele_num_sup);
				if (num[_index] >= ele_num_sup)
				{
					if (_index + 1 < size())
						num[_index + 1] += static_cast<ele_type>(num[_index] / ele_num_sup);
					else
						num.push_back(static_cast<ele_type>(num[_index] / ele_num_sup));
					num[_index] %= ele_num_sup;
				}
				_num /= ele_num_sup;
				_index++;
			}
		}

		std::size_t size() const
		{
			return num.size();
		}

		std::vector<ele_type> num;
	};

	inline
		std::string to_string(const BigNum& num)
	{
		return num.to_string();
	}

	inline
		std::wstring to_wstring(const BigNum& num)
	{
		return num.to_wstring();
	}

	template <typename T>
	inline
		T convertBinStringTo(const std::wstring& str)
	{
		T _temp(0);
		for (auto i : str)
		{
			if (i <= L'1'&&i >= L'0')
			{
				_temp = _temp * 2 + (i - '0');
			}
		}
		return std::move(_temp);
	}

	template <>
	inline
		BigNum convertBinStringTo<BigNum>(const std::wstring& str)
	{
		BigNum _num;
		BigNum::ele_type _temp = 0;
		size_t count = 0;
		for (auto i : str)
		{
			count++;
			if (count >= log_binbase(ele_num_sup))
			{
				count = 0;
				_num = _num*static_cast<BigNum::ele_type>((cpow(2, log_binbase(ele_num_sup)))) + _temp;
				_temp = 0;
			}
			if (i <= L'1'&&i >= L'0')
			{
				_temp = _temp * 2 + (i - '0');
			}
		}
		_num = _num*static_cast<BigNum::ele_type>(ipow(2, count + 1)) + _temp;
		return std::move(_num);
	}

	inline
		bool validBinNumber(const std::wstring& str)
	{
		for (auto i : str)
		{
			if (!((i <= L'1' && i >= L'0')))
				return false;
		}
		return true;
	}

	template <typename T>
	inline
		T convertDecStringTo(const std::wstring& str)
	{
		T _temp(0);
		for (auto i : str)
		{
			if (i <= L'9'&&i >= L'0')
			{
				_temp = _temp * 10 + (i - '0');
			}
		}
		return std::move(_temp);
	}

	inline
		bool validDecNumber(const std::wstring& str)
	{
		for (auto i : str)
		{
			if (!((i <= L'9' && i >= L'0')))
				return false;
		}
		return true;
	}

	template <>
	inline
		BigNum convertDecStringTo<BigNum>(const std::wstring& str)
	{
		return BigNum(str);
	}

	template <typename T>
	inline
		T convertOctStringTo(const std::wstring& str)
	{
		T _temp(0);
		for (auto i : str)
		{
			if (i <= L'7'&&i >= L'0')
			{
				_temp = _temp * 8 + (i - L'0');
			}
		}
		return std::move(_temp);
	}

	template <>
	inline
		BigNum convertOctStringTo<BigNum>(const std::wstring& str)
	{
		BigNum _num;
		BigNum::ele_type _temp = 0;
		size_t count = 0;
		for (auto i : str)
		{
			count++;
			if (count >= log_octbase(ele_num_sup))
			{
				count = 0;
				_num = _num*static_cast<BigNum::ele_type>(cpow(8, log_octbase(ele_num_sup))) + _temp;
				_temp = 0;
			}
			if (i <= L'7'&&i >= L'0')
			{
				_temp = _temp * 8 + (i - L'0');
			}
		}
		_num = _num*static_cast<BigNum::ele_type>(ipow(8, count + 1)) + _temp;
		return std::move(_num);
	}

	inline
		bool validOctNumber(const std::wstring& str)
	{
		for (auto i : str)
		{
			if (!((i <= L'7' && i >= L'0')))
				return false;
		}
		return true;
	}

	template <typename T>
	inline
		T convertHexStringTo(const std::wstring& str)
	{
		T _temp(0);
		for (auto i : str)
		{
			if (i <= L'9' && i >= L'0')
			{
				_temp = _temp * 16 + (i - L'0');
			}
			else if (tolower(i) >= L'a' && tolower(i) <= L'f')
			{
				_temp = _temp * 16 + (static_cast<T>(tolower(i)) - L'a' + 10);
			}
		}
		return std::move(_temp);
	}

	template <>
	inline
		BigNum convertHexStringTo<BigNum>(const std::wstring& str)
	{
		BigNum _num;
		BigNum::ele_type _temp = 0;
		size_t count = 0;
		for (auto i : str)
		{
			count++;
			if (count >= log_hexbase(ele_num_sup))
			{
				count = 0;
				_num = _num*static_cast<BigNum::ele_type>(cpow(16, log_hexbase(ele_num_sup))) + _temp;
				_temp = 0;
			}
			if (i <= L'9' && i >= L'0')
			{
				_temp = _temp * 16 + (i - L'0');
			}
			else if (tolower(i) >= L'a' && tolower(i) <= L'f')
			{
				_temp = _temp * 16 + (tolower(i) - L'a' + 10);
			}
		}
		_num = _num*static_cast<BigNum::ele_type>(ipow(16, count + 1)) + _temp;
		return std::move(_num);
	}

	inline
		bool validHexNumber(const std::wstring& str)
	{
		for (auto i : str)
		{
			if (!((i <= L'9' && i >= L'0') || (tolower(i) >= L'a' && tolower(i) <= L'f')))
				return false;
		}
		return true;
	}

	inline
		bool isalphaX(int _char) throw()
	{
		return ((_char >= 0x41) && (_char <= 0x5A)) || ((_char >= 0x61) && (_char <= 0x7A));
	}

	inline
		bool isdigitX(int _char) throw()
	{
		return ((_char >= 0x30) && (_char <= 0x39));
	}

	inline
		bool ishexdigitX(int _char) throw()
	{
		return ((_char >= 0x30) && (_char <= 0x39) || (tolower(_char) >= 0x61 && tolower(_char) <= 0x66));
	}

	inline
		bool isoctdigitX(int _char) throw()
	{
		return ((_char >= 0x30) && (_char <= 0x37));
	}

	inline
		bool isbindigitX(int _char) throw()
	{
		return ((_char >= 0x30) && (_char <= 0x31));
	}
}

#endif
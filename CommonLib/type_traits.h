#ifndef __PYJS_COM_LIB_TYPE_TRAITS__

#define __PYJS_COM_LIB_TYPE_TRAITS__

namespace PyJsComLib
{

	template<bool _VALUE>
	struct _BOOL
	{
		const static bool value = false;
	};

	template<>
	struct _BOOL < true >
	{
		const static bool value = true;
	};

	template<bool _COND, class _expr1, class _expr2>
	struct _IF
	{
		typedef _expr2 value;
	};

	template<class _expr1, class _expr2>
	struct _IF<true, _expr1, _expr2>
	{
		typedef _expr1 value;
	};


	template<class _Ty>
	struct convert_rv_reference_to_lv_referenc
	{
		typedef _Ty type;
	};

	template<class _Ty>
	struct convert_rv_reference_to_lv_referenc<_Ty&&>
	{
		typedef _Ty& type;
	};

	template<class _Ty>
	struct get_embedded_type
	{
	private:
		template <typename U>
		static typename U::type __test_embedded_type(typename U::type*);
		template <typename U>
		static typename U __test_embedded_type(...);
	public:
		typedef decltype(__test_embedded_type<std::decay<_Ty>::type>(nullptr)) type;
	};

	template<class _Ty>
	struct is_reference_wrapper
	{
	private:
		template<class U>
		struct __is_reference_wrapper
		{
			static const bool value = false;
		};

		template<class U>
		struct __is_reference_wrapper<std::reference_wrapper<U>>
		{
			static const bool value = true;
		};

		template<class U>
		struct __is_reference_wrapper<std::reference_wrapper<U> const>
		{
			static const bool value = true;
		};

	public:
		static const bool value = typename __is_reference_wrapper<std::decay<_Ty>::type>::value;
	};

	template <typename _Ty,
	class _rTy = typename std::underlying_type<_Ty>::type>
		inline
		_rTy to_underlying(_Ty e)
	{
		return static_cast<_rTy>(e);
	}

#define __HAS_MEMBER_FUNC(_struct_name,_func_name,_func_ret_type,_func_args_type)	\
	template<class _Ty>	\
	struct has_##_struct_name##_member_func	\
	{	\
		static void _func_name();	\
		struct __test : _Ty	\
		{	\
		private:	\
			static _BOOL<true> __test_member_func(_func_ret_type(_Ty::*)_func_args_type);	\
			static _BOOL<true> __test_member_func(_func_ret_type(_Ty::*)_func_args_type const);	\
			static _BOOL<false> __test_member_func(...);	\
		public:	\
			static const bool value = (decltype(__test_member_func(&_func_name))::value);	\
		};	\
		static const bool value = __test::value;	\
	};

}

#endif
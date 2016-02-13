#ifndef __PYJS_COM_LIB_MEMORY__

#define __PYJS_COM_LIB_MEMORY__

#include <memory>
#include "type_traits.h"

namespace PyJsComLib
{

	class irc_ptr_default_base	//default base for irc pointer object
	{
	protected:

		irc_ptr_default_base()
			:ref_conut(0)
		{
		}

		virtual ~irc_ptr_default_base() = default;

		inline
			void addReference() throw()
		{
			ref_conut++;
		}

		inline
			void decReference() throw()
		{
			ref_conut--;
		}

		inline
			size_t getReferenceCount() const throw()
		{
			return ref_conut;
		}

		inline
			bool zeroReference() const throw()
		{
			return ref_conut == 0;
		}

	protected:
		size_t ref_conut;
		template<class _Ty0>
		friend class irc_ptr;
	};

	template<class _Ty>
	class irc_ptr	//Intrusive reference counting pointer
	{
	private:
		__HAS_MEMBER_FUNC(addRef, addReference, void, ());
		__HAS_MEMBER_FUNC(decRef, decReference, void, ());
		__HAS_MEMBER_FUNC(zeroRef, zeroReference, bool, ());

		template <class _Ty0>
		struct irc_func_check
		{
			static const bool value = has_addRef_member_func<_Ty0>::value &&
				has_decRef_member_func<_Ty0>::value &&
				has_zeroRef_member_func<_Ty0>::value;
		};

		template <class _Ty0>
		class rebind_irc_base
			:protected irc_ptr_default_base
		{
		public:
			typedef rebind_irc_base<_Ty0> _Myt;

			rebind_irc_base() throw()
				:_ptr(nullptr)
			{
			}

			rebind_irc_base(_Ty0* const _new_ptr) throw()
				:_ptr(_new_ptr)
			{
			}

			~rebind_irc_base()
			{
				delete(_ptr);
			}

			_Ty0* _ptr;
			template<class _Ty_x>
			friend class irc_ptr;
		};

		template <class _Ty0>
		struct is_rebind
		{
			static const bool value = !irc_func_check<_Ty0>::value;
		};

		template <class _Ty0>
		struct rebind
		{
			typedef typename _IF<is_rebind<_Ty0>::value, rebind_irc_base<_Ty0>, _Ty0>::value type;
		};

		typedef typename rebind<_Ty>::type _vTy;

		inline
			rebind_irc_base<_Ty>* init_ptr(_Ty* value, rebind_irc_base<_Ty>*)
		{
			return new rebind_irc_base<_Ty>(value);
		}

		inline
			_Ty* init_ptr(_Ty* _value, _Ty*)
		{
			return _value;
		}

		template <class U>
		inline
			U cast_ptr(rebind_irc_base<_Ty>* _value) const
		{
			return static_cast<U>(_value->_ptr);
		}

		template <class U>
		inline
			U cast_ptr(_Ty* _value) const
		{
			return static_cast<U>(_value);
		}

	public:
		typedef irc_ptr<_Ty> _Myt;

		irc_ptr() throw()
			:_ptr(nullptr)
		{
		}

		irc_ptr(std::nullptr_t) throw()
			:_ptr(nullptr)
		{
		}

		explicit irc_ptr(_Ty* _new_ptr) throw()
			:_ptr(init_ptr(_new_ptr, _ptr))
		{
			if (_ptr)
				_ptr->addReference();
		}

		irc_ptr(const _Myt& _other) throw()
			:_ptr(_other._ptr)
		{
			if (_ptr)
				_ptr->addReference();
		}

		irc_ptr(_Myt&& _other) throw()
			:_ptr(_other._ptr)
		{
			_other._ptr = nullptr;
		}

		template<class _Ty2>
		irc_ptr(const irc_ptr<_Ty2>& _other) throw()
			:_ptr(static_cast<_Ty*>(_other._ptr))
		{
			if (_ptr)
				_ptr->addReference();
		}

		template<class _Ty2,
		class = typename std::enable_if<std::is_convertible<_Ty2*, _Ty*>::value,
			void>::type>
			irc_ptr(irc_ptr<_Ty2>&& _other) throw()
			:_ptr(static_cast<_Ty*>(_other._ptr))
		{
			_other._ptr = nullptr;
		}

		~irc_ptr() throw()
		{
			release();
		}

		inline
			const _Myt& operator =(const _Myt& _other) throw()
		{
			if (_ptr)
			{
				_ptr->decReference();
				if (_ptr->zeroReference())
					delete(_ptr);
			}
			_ptr = _other._ptr;
			if (_ptr)
				_ptr->addReference();
			return *this;
		}

		inline
			const _Myt& operator =(_Myt&& _other) throw()
		{
			if (_ptr)
			{
				_ptr->decReference();
				if (_ptr->zeroReference())
					delete(_ptr);
			}
			_ptr = _other._ptr;
			_other._ptr = nullptr;
			return *this;
		}

		template<class _Ty2,
		class = typename std::enable_if<std::is_convertible<_Ty2*, _Ty*>::value,
			void>::type>
			inline
			const _Myt& operator =(const irc_ptr<_Ty2>& _other) throw()
		{
			if (_ptr)
			{
				_ptr->decReference();
				if (_ptr->zeroReference())
					delete(_ptr);
			}
			_ptr = _other._ptr;
			if (_ptr)
				_ptr->addReference();
			return *this;
		}

		template<class _Ty2,
		class = typename std::enable_if<std::is_convertible<_Ty2*, _Ty*>::value,
			void>::type>
			inline
			const _Myt& operator =(irc_ptr<_Ty2>&& _other) throw()
		{
			if (_ptr)
			{
				_ptr->decReference();
				if (_ptr->zeroReference())
					delete(_ptr);
			}
			_ptr = _other._ptr;
			_other._ptr = nullptr;
			return *this;
		}

		inline
			explicit operator bool() const throw()
		{
			return (cast_ptr<_Ty*>(_ptr) != 0);
		}

		template<class _Ty2>
		inline
			bool operator ==(const irc_ptr<_Ty2>& _other) const throw()
		{
			return cast_ptr<_Ty*>(_ptr) == cast_ptr<_Ty2*>(_other._ptr);
		}

		template<class _Ty2>
		inline
			bool operator !=(const irc_ptr<_Ty2>& _other) const throw()
		{
			return cast_ptr<_Ty*>(_ptr) != cast_ptr<_Ty2*>(_other._ptr);
		}

		inline
			_Ty& operator*() throw()
		{
			return *(cast_ptr<_Ty*>(_ptr));
		}

		inline
			_Ty& operator*() const throw()
		{
			return *(cast_ptr<_Ty*>(_ptr));
		}

		inline
			_Ty* operator->() throw()
		{
			return cast_ptr<_Ty*>(_ptr);
		}

		inline
			_Ty* operator->() const throw()
		{
			return cast_ptr<_Ty*>(_ptr);
		}

		inline
			_Ty* get() throw()
		{
			return cast_ptr<_Ty*>(_ptr);
		}

		inline
			_Ty* get() const throw()
		{
			return cast_ptr<_Ty*>(_ptr);
		}

		inline
			void swap(_Myt& _other) throw()
		{
			std::swap(_ptr, _other._ptr);
		}

		inline
			void reset() throw()
		{
			release();
		}

		inline
			void reset(_Ty* _new_ptr) throw()
		{
			if (_ptr)
			{
				_ptr->decReference();
				if (_ptr->zeroReference())
					delete(_ptr);
			}
			_ptr = _new_ptr;
			if (_ptr)
				_ptr->addReference();
		}

		inline
			void release() throw()
		{
			if (!_ptr)
				return;
			else
			{
				_ptr->decReference();
				if (_ptr->zeroReference())
					delete(_ptr);
				_ptr = nullptr;
			}
		}

	private:
		_vTy* _ptr;
		template<class _Ty0>
		friend class irc_ptr;
	};

	template<class _Ty1,
	class _Ty2>
		inline
		_Ty1* raw_pointer_cast(const irc_ptr<_Ty2>& _irc_ptr) throw()
	{
		return static_cast<_Ty1*>(_irc_ptr.get());
	}

	template<class _Ty1,
	class _Ty2>
		inline
		_Ty1* raw_pointer_cast(const std::shared_ptr<_Ty2>& _shared_ptr) throw()
	{
		return static_cast<_Ty1*>(_shared_ptr.get());
	}

	template<class _Ty1,
	class _Ty2>
		inline
		irc_ptr<_Ty1> irc_pointer_cast(const irc_ptr<_Ty2>& _irc_ptr) throw()
	{
		return irc_ptr<_Ty1>(static_cast<_Ty1*>(_irc_ptr.get()));
	}

	template<class _Ty>
	inline
		void swap(irc_ptr<_Ty>& x, irc_ptr<_Ty>& y)
	{
		x.swap(y);
	}

	class Any
	{
	public:
		template<class T>
		using StorageType = typename _IF<
			is_reference_wrapper<typename std::decay<T>::type>::value,
			typename get_embedded_type<T>::type&,
			typename std::decay<T>::type
		>::value;

		template<class T>
		using InterpretType = typename _IF<
			is_reference_wrapper<typename std::decay<T>::type>::value,
			typename get_embedded_type<T>::type&,
			typename convert_rv_reference_to_lv_referenc<T>::type
		>::value;

		template<class U,
		class = typename std::enable_if<
			!std::is_same<StorageType<U>, Any>::value, void
		>::type>
			Any(U&& _value)
			: _ptr(new Container<StorageType<U>>(std::forward<U>(_value)))
		{
		}

		Any()
			: _ptr(nullptr)
		{
		}

		Any(const Any& _that)
			: _ptr(_that.clone())
		{
		}

		Any(Any&& _that)
			: _ptr(_that._ptr)
		{
			_that._ptr = nullptr;
		}

		template<class U>
		inline
			bool is() const
		{
			typedef InterpretType<U> T;

			if (!_ptr)
				return false;

			auto derived = dynamic_cast<Container<T>*> (ptr);

			return !(derived == nullptr);
		}

		template<class U>
		inline
			InterpretType<U>& as() const
		{
			typedef InterpretType<U> T;

			if (!_ptr)
				throw std::bad_cast();

			auto container = dynamic_cast<Container<T>*> (_ptr);

			if (!container)
				throw std::bad_cast();

			return container->value;
		}

		template<class U>
		inline
			InterpretType<U>& value() const
		{
			return as<InterpretType<U>>();
		}

		template<class U>
		inline
			operator U() const
		{
			return as<InterpretType<U>>();
		}

		Any& operator=(const Any& a)
		{
			if (_ptr == a._ptr)
				return *this;
			auto old_ptr = _ptr;
			_ptr = a.clone();
			if (old_ptr)
				delete old_ptr;
			return *this;
		}

		Any& operator=(Any&& a)
		{
			if (_ptr == a._ptr)
				return *this;
			std::swap(_ptr, a._ptr);
			return *this;
		}

		~Any()
		{
			if (_ptr)
				delete _ptr;
		}

	private:
		class ContainerBase
		{
		public:
			virtual ~ContainerBase() {}
			virtual ContainerBase* clone() const = 0;
		};

		template<typename T>
		class Container
			:public ContainerBase
		{
		public:
			template<typename U>
			Container(U&& value)
				:value(std::forward<U>(value))
			{
			}

			inline
				ContainerBase* clone() const
			{
				return new Container<T>(value);
			}

			T value;
		};

		inline
			ContainerBase* clone() const
		{
			if (_ptr)
				return _ptr->clone();
			else
				return nullptr;
		}

		ContainerBase* _ptr;
	};

}

#endif
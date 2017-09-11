#ifndef uvector_h__
#define uvector_h__

#include <cstdint>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include "IntegerTraits.h"

namespace MicroUI {
#pragma pack(push, 1)
	template<typename T, size_t Capacity>
	class uvector {
	public:
		using value_type = T;
		using size_type = typename integer_traits<Capacity>::type;
		using pointer = T*;
		using iterator = pointer;

		uvector() :_size(0) {

		}

		uvector(std::initializer_list<T> values) :_size(0) {
			auto cnt = (size_type)(std::min)((size_t)values.size(), Capacity);
			auto val = values.begin();
			for (size_type i = 0; i < cnt; ++i) {
				push_pack(*val);
				++val;
			}
		}

		bool push_pack(const value_type& val) {
			if (_size >= Capacity) {
				return false;
			}
			construct(&_buffer[_size++], val);
			return true;
		}

		size_type capacity() const noexcept {
			return Capacity;
		}
		size_type max_size() const noexcept {
			return Capacity;
		}

		bool empty() const noexcept {
			return _size == 0;
		}

		value_type* data() noexcept {
			return &_buffer[0];
		}
		const value_type* data() const noexcept {
			return &_buffer[0];
		}


		void pop_back() {
			if (_size > 0) {
				resize(_size - 1);
			}
		}

		/*template <class... Args>
		iterator emplace(const_iterator position, Args&&... args)
		{
			
		}*/

		void resize(size_type n) {
			if (n < _size) {
				while (_size > n) {
					destroy(&_buffer[_size - 1]);
					--_size;
				}
			} else {
				resize(n, T());
			}
		}

		void fast_erase(iterator item) {
			size_type index = std::addressof(*item) - &_buffer[0];
			if (index >= _size) {
				return;
			}
			destroy(&_buffer[index]);

			if (index != (_size - 1)) {
				construct(&_buffer[index], _buffer[_size - 1]);
			}
			--_size;
		}

		T& operator [](size_type id) {
			return _buffer[id];
		}

		void clear() noexcept {
			for (size_type i = 0; i < _size; ++i) {
				destroy(&_buffer[i]);
			}
			_size = 0;
		}

		void resize(size_type n, const T& val) {
			n = (std::min)(n, (size_type)Capacity);
			if (n > _size) {
				while (_size < n) {
					construct(&_buffer[_size++], val);
					++_size;
				}
			} else if (n < _size) {
				while (_size > n) {
					destroy(&_buffer[_size - 1]);
					--_size;
				}
			}
		}
		size_type size() const noexcept {
			return _size;
		}

		iterator begin() {
			return &_buffer[0];
		}
		iterator end() {
			return &_buffer[_size];
		}
	private:
		template<class T, class... _Types>
		void construct(T* ptr, _Types&&... _Args) {
			::new ((void*)ptr) T(std::forward<_Types>(_Args)...);
		}


		template<class _Uty>
		void destroy(_Uty *_Ptr) {
			_Ptr->~_Uty();
		}

		T _buffer[Capacity];
		size_type _size;
	};
#pragma pack(pop)
}
#endif // uvector_h__

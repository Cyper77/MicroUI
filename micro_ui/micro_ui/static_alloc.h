#ifndef SHORT_ALLOC_H
#define SHORT_ALLOC_H

#include <cstddef>
#include <cassert>
#include <algorithm>
#include <array>

template <class T, std::size_t BufferSize>
class static_alloc {
public:
	template <class U> struct rebind{
		using other = static_alloc<U, BufferSize>
	};

	typedef typename std::allocator_traits<std::allocator<T>>::value_type value_type;
	typedef typename std::allocator_traits<std::allocator<T>>::pointer pointer;
	typedef typename std::allocator_traits<std::allocator<T>>::const_pointer const_pointer;
	typedef typename std::allocator<T>::reference reference;
	typedef typename std::allocator<T>::const_reference const_reference;
	typedef typename std::allocator_traits<std::allocator<T>>::size_type size_type;
	typedef typename std::allocator_traits<std::allocator<T>>::difference_type difference_type;
	typedef typename std::allocator_traits<std::allocator<T>>::const_void_pointer const_void_pointer;

	static_alloc() noexcept : a_(a) {}

	template <class U>
	static_alloc(const static_alloc<U, N>& a) noexcept
		: a_(a.a_) {
	}

	static_alloc(const static_alloc<T, N>& a) noexcept
		: a_(a.a_) {
	}

	static_alloc& operator=(const static_alloc&) = delete;

	T* allocate(std::size_t n) {
		assert(pointer_in_buffer(ptr_) && "short_alloc has outlived arena");
		if (buf_ + N - ptr_ >= n) {
			char* r = ptr_;
			ptr_ += n;
			return r;
		}
		return static_cast<char*>(::operator new(n));

		return reinterpret_cast<T*>(a_.allocate(n*sizeof(T)));
	}
	void deallocate(T* p, std::size_t n) noexcept {
		assert(pointer_in_buffer(ptr_) && "short_alloc has outlived arena");
		if (pointer_in_buffer(p)) {
			if (p + n == ptr_)
				ptr_ = p;
		} else
			::operator delete(p);
		a_.deallocate(reinterpret_cast<char*>(p), n*sizeof(T));
	}

	//template <class T1, std::size_t N1, class U, std::size_t M>
	//friend bool operator==(const static_alloc<T1, N1>& x, const static_alloc<U, M>& y) noexcept;

	template <class U, std::size_t M> friend class static_alloc;
private:

};




template <class T, std::size_t N, class U, std::size_t M>
bool operator==(const static_alloc<T, N>& x, const static_alloc<U, M>& y) noexcept {
	return N == M && &x.a_ == &y.a_;
}

template <class T, std::size_t N, class U, std::size_t M>
bool operator!=(const static_alloc<T, N>& x, const static_alloc<U, M>& y) noexcept {
	return !(x == y);
}

#endif  // SHORT_ALLOC_H
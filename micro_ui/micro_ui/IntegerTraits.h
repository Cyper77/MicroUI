#ifndef integer_traits_h__
#define integer_traits_h__

#if defined(__cplusplus)

#include <cstdint>

template<bool condition, typename left_t, typename right_t>
struct conditional_typedef {
	typedef left_t type;
};

template<typename left_t, typename right_t>
struct conditional_typedef<false, left_t, right_t> {
	typedef right_t type;
};

template<uint64_t value>
struct integer_traits {
	static const bool is_8_bits = (value <= 0xff);
	static const bool is_16_bits = (value > 0xff) && (value <= 0xffff);
	static const bool is_32_bits = (value > 0xffff) && (value <= 0xffffffff);
	static const bool is_64_bits = (value > 0xffffffff);

	typedef typename conditional_typedef < is_8_bits, uint8_t, 
		typename conditional_typedef < is_16_bits, uint16_t, 
		typename conditional_typedef < is_32_bits, uint32_t, uint64_t >::type > ::type > ::type type;
};
#endif

#endif // integer_traits_h__

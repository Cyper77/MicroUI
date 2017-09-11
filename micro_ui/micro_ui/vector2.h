#ifndef vector2_h__
#define vector2_h__

#include "vector_base.h"

namespace MicroUI {
	template<typename T>
	class vector2 : public vector_base<T, 2> {
	public:
		T x;
		T y;

		vector2() :x(0), y(0) {

		}

		vector2(T _x, T _y) :x(_x), y(_y) {

		}

		vector2 operator +(vector2 right) {
			return vector2(x + right.x, y + right.y);
		}

		vector2 operator -(vector2 right) {
			return vector2(x - right.x, y - right.y);
		}
	};
}
#endif // vector2_h__

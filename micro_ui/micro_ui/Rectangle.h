#ifndef rect_h__
#define rect_h__

#include "vector2.h"

namespace MicroUI
{
	template<typename T>
	class Rectangle {
	public:
		using element_t = T;
		T x;
		T y;
		T width;
		T height;

		Rectangle() :x(0), y(0), width(0), height(0) {

		}

		Rectangle(T _x, T _y, T _width, T _height) :x(_x), y(_y), width(_width), height(_height) {

		}

		Rectangle(vector2<T> position, vector2<T> size) :x(position.x), y(position.y), width(size.x), height(size.y) {

		}

		T right() const {
			return x + width;
		}

		T bottom() const {
			return y + height;
		}

		bool contains(Rectangle rect) const {
			return (rect.x >= x) && (rect.y >= y) && (rect.right() <= right()) && (rect.bottom() <= bottom());
		}

		bool contains(vector2<T> point) const {
			return (point.x >= x) && (point.y >= y) && (point.x < right()) && (point.y < bottom());
		}
	};
}


#endif // rect_h__

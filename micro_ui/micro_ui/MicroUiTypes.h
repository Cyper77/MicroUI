#ifndef micro_ui_types_h__
#define micro_ui_types_h__

#include "rectangle.h"
#include "color.h"
#include "vector2.h"
#include <cstdint>

namespace MicroUI {
	using coord_1d = int16_t;
	using Rect = Rectangle<coord_1d>;
	using Point = vector2<coord_1d>;
	using Size = vector2<coord_1d>;
	using Color = Color16;


}
#endif // micro_ui_types_h__

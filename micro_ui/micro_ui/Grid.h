#ifndef ui_grid_h__
#define ui_grid_h__

#include "ElementBase.h"

namespace MicroUI
{
	class Grid : public ElementBase {
	public:
		virtual bool renderColor(Point local_pos, Color16& color) override {
			if((((local_pos.x % 20) == 0) || ((local_pos.y % 20) == 0)) && ((local_pos.x %2 == 0) && (local_pos.y % 2 == 0))) {
				color = Color24::gray().asColor16();
			} else {
				return false;
				//color = background_color;
			}
			return true;
		}
	};
}
#endif // ui_grid_h__

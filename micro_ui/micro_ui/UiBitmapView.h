#ifndef ui_const_bitmap_h__
#define ui_const_bitmap_h__

#include "ElementBase.h"

namespace MicroUI {
	class UiBitmapView : public ElementBase {
	public:
		void setBitmap(const Color16* pixels, Size bitmap_size)
		{
			_pixels = pixels;
			_bitmap_size = bitmap_size;
		}

		virtual bool renderColor(Point local_pos, Color16& color) override {
			if((local_pos.x >= _bitmap_size.x) || (local_pos.y >= _bitmap_size.y) || local_pos.x < 0 || local_pos.y < 0) {
				return false;
			}
			color = _pixels[local_pos.y * _bitmap_size.x + local_pos.x];
			return true;
		}

	private:
		Size _bitmap_size;
		const Color16* _pixels;
	};
}
#endif // ui_const_bitmap_h__

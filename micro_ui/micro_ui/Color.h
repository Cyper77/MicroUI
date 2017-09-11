#ifndef color_h__
#define color_h__

#include <cstdint>

namespace MicroUI {

	struct Color16 {
		union {
			uint16_t value;
			struct {
				uint16_t r : 5;
				uint16_t g : 6;
				uint16_t b : 5;
			};
		};

		Color16 swab_rb() const
		{
			Color16 result;
			result.r = b;
			result.b = r;
			result.g = g;
			return result;
		}
	};

	struct Color24 {
		uint8_t r;
		uint8_t g;
		uint8_t b;

		Color24()
			:r(0), g(0), b(0) {
		}

		Color24(uint8_t _r, uint8_t _g, uint8_t _b)
			:r(_r), g(_g), b(_b) {
		}

		static Color24 red() {
			return Color24(0xff, 0, 0);
		}

		static Color24 green() {
			return Color24(0, 0xff, 0);
		}

		static Color24 blue() {
			return Color24(0, 0, 0xff);
		}

		static Color24 yellow() {
			return Color24(0xff, 0xff, 0);
		}

		static Color24 white() {
			return Color24(0xff, 0xff, 0xff);
		}

		static Color24 black() {
			return Color24(0, 0, 0);
		}


		static Color24 gray() {
			return Color24(0x80, 0x80, 0x80);
		}

		Color16 asColor16() {
			Color16 result;
			result.r = r >> 3;
			result.g = g >> 2;
			result.b = b >> 3;
			return result;
		}
	};

	struct Color32{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		Color32():r(0), g(0), b(0), a(0){
			
		}

		Color32(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) :r(_r), g(_g), b(_b), a(_a) {

		}

		Color32(Color16 src)
		{
			r = src.r << 3;
			g = src.g << 2;
			b = src.b << 3;
			a = 0xff;
		}
	};
}

#endif // color_h__

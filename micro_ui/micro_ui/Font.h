#ifndef ui_font_h__
#define ui_font_h__

#include <cstdint>

namespace MicroUI {
	class Font {
	public:
		Font(const uint8_t* buffer, uint8_t char_count, uint8_t char_width)
			:_buffer(buffer), _char_count(char_count), _char_width(char_width) {

		}

		bool get_pixel(char c, uint8_t x, uint8_t y)
		{
			auto buffer = get_char_buffer(c);
			return (buffer[x] & (1 << y)) != 0;
		}

		const uint8_t* get_char_buffer(char c) {
			if (c < ' ') {
				c = 0;
			} else {
				c -= ' ';
			}
			return &_buffer[c * _char_width];
		}
		uint8_t char_count() const {
			return _char_count;
		}
		uint8_t char_width() const {
			return _char_width;
		}
		static constexpr uint8_t char_height() {
			return 8;
		}
	private:
		const uint8_t* _buffer;
		uint8_t _char_count;
		uint8_t _char_width;
	};
}
#endif // ui_font_h__

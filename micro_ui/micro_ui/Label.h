#ifndef ui_label_h__
#define ui_label_h__

#include "ElementBase.h"
#include "Font.h"
#include <string.h>

namespace MicroUI {
	class Label : public ElementBase {
	public:
		Font* font;
		uint8_t font_size;
		Color16 font_color;

		Label() :_text(nullptr), font(nullptr), font_size(1), font_color(Color24::white().asColor16()){

		}

		bool renderColor(Point local_pos, Color16& color) override {
			if ((font == nullptr) || (_text == nullptr) || (local_pos.y >= (Font::char_height() * font_size)) || (local_pos.y < 0)) {
				return false;
			}

			auto char_id = (local_pos.x / font_size) / font->char_width();
			auto char_local_x = (local_pos.x / font_size) % font->char_width();

			if(char_id >= _text_len){
				return false;
			}

			if(font->get_pixel(_text[char_id], char_local_x, local_pos.y / font_size))
			{
				color = font_color;
				return true;
			}
			return false;
		}
		void setText(const char* text){
			_text = text;
			if(_text != nullptr){
				_text_len = strlen(_text);
			}
		}
	private:
		uint8_t _text_len = 0;
		const char* _text;
	};
}
#endif // ui_label_h__

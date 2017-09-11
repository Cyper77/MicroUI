#ifndef display_h__
#define display_h__

#include "window.h"
#include <windows.h>
#include "MicroUiTypes.h"
#include <vector>
#include <functional>

namespace MicroUI {
	class display {
	public:
		using fill_function_t = std::function<Color16(Rect rect, Point point)>;

		display(Size size) :_full_rect(0, 0, size.x, size.y), _edit_rect_position(0) {
			_window.Init(L"micro_display");
			_window.SetSize(size.x, size.y);
			_device_context = ::GetDC(_window.GetHwnd());
		}

		void update() {
			_window.ProcessMessages();
		}
		bool begin_rect(Rect rect) {
			if ((_edit_rect_position != 0) || (!_full_rect.contains(rect))) {
				return false;
			}
			_edit_rect = rect;
			_edit_rect_buffer.resize(rect.width * rect.height);
			return true;
		}

		void append_pixel(Color16 color) {
			_edit_rect_buffer[_edit_rect_position++] = Color32(color.swab_rb());
		}

		void fill_rect(fill_function_t fill_func) {
			_edit_rect_position = 0;
			for (coord_1d y = 0; y < _edit_rect.height; ++y)
			{
				for (coord_1d x = 0; x < _edit_rect.width; ++x) {
					_edit_rect_buffer[_edit_rect_position++] = fill_func(_edit_rect, Point(x, y)).swab_rb();
				}
			}
		}

		void fill_rect(Rect rect, fill_function_t fill_func) {
			if (begin_rect(rect)) {
				fill_rect(fill_func);
				end_rect();
			}
		}

		void end_rect() {
			if (_edit_rect_position != 0) {
				blit_edit_rect();
				_edit_rect_position = 0;
			}
		}
	private:
		void blit_edit_rect() {
			if (_edit_rect_position == 0) {
				return;
			}
			BITMAPINFO bitmap_info = {};
			BITMAPINFOHEADER header = {};
			header.biSize = sizeof(BITMAPINFOHEADER);
			header.biWidth = _edit_rect.width;
			header.biHeight = -_edit_rect.height;
			header.biPlanes = 1;
			header.biBitCount = 32;
			header.biCompression = 0;
			header.biSizeImage = _edit_rect.width * _edit_rect.height * 4;
			bitmap_info.bmiHeader = header;
			SetDIBitsToDevice(_device_context, _edit_rect.x, _edit_rect.y, _edit_rect.width, _edit_rect.height, 0, 0, 0, _edit_rect.height, &_edit_rect_buffer[0], &bitmap_info, 0);
		}

		Rect _full_rect;
		Rect _edit_rect;
		uint32_t _edit_rect_position;
		std::vector<Color32> _edit_rect_buffer;
		std::vector<Color32> _back_buffer;
		window _window;
		HDC _device_context;
	};
}
#endif // display_h__

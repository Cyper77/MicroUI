#include "window.h"
#include "display.h"
#include "Panel.h"
#include "Viewport.h"
#include "uvector.h"
#include <iostream>
#include <vector>
#include <amp.h>
#include "Element.h"
#include <chrono>
#include "Font.h"
#include <type_traits>
#include "homespun_font.h"
#include <cstdio>
#include "Label.h"
#include "Grid.h"
#include "UiBitmapView.h"
#include "BmpToImg.h"

using namespace MicroUI;

struct render_context {
	Color16 color_buffer;
};

void render_ui(ElementBase* element, Point point, Color16& result) {
	if (element == nullptr) {
		return;
	}

	auto lsp = element->to_local_space(point);
	auto lsr = element->local_rect();

	if (lsr.contains(lsp)) {

		Color16 col;
		if(element->renderColor(lsp, col))
		{
			result = col;
		}

		auto children = element->getChildrenCount();
		for (decltype(children) i = 0; i < children; ++i) {
			auto child = element->get_child(i);
			render_ui(child, point, result);
		}
	}
}

int main() {
	display disp(Size(320, 240));

	disp.fill_rect(Rect(0, 0, 320, 240), [](Rect rect, Point point) {return Color24::gray().asColor16(); });
	disp.fill_rect(Rect(10, 10, 100, 100), [](Rect rect, Point point) {return Color24::red().asColor16(); });

	Element<Viewport, 10> ui_core;
	ui_core.size = Size(320, 240);
	ui_core.background_color = Color24::black().asColor16();

	Element<Panel, 2> progress_bg;
	progress_bg.set_parent(&ui_core);
	progress_bg.background_color = Color24::green().asColor16();
	progress_bg.size = Size(100, 20);
	progress_bg.local_position = Point(10, 10);

	Element<Panel, 2> progress_line;
	progress_line.set_parent(&progress_bg);
	progress_line.background_color = Color24::red().asColor16();
	progress_line.size = Size(58, 18);
	progress_line.local_position = Point(1, 1);

	Font fnt(&font[0][0], std::extent<decltype(font), 0>::value, std::extent<decltype(font), 1>::value);

	Element<Label, 1> label;
	label.set_parent(&ui_core);
	label.setText("Test 1!");
	label.local_position = Point(10, 80);
	label.size = Size(100, 30);
	label.font = &fnt;
	label.font_size = 1;
	label.font_color = Color24::red().asColor16();

	Element<Label, 1> label2;
	label2.set_parent(&ui_core);
	label2.setText("Test 2!");
	label2.local_position = Point(10, 120);
	label2.size = Size(100, 30);
	label2.font = &fnt;
	label2.font_size = 2;
	label2.font_color = Color24::green().asColor16();

	Element<Label, 1> label3;
	label3.set_parent(&ui_core);
	label3.setText("Test 4!");
	label3.local_position = Point(10, 160);
	label3.size = Size(200, 30);
	label3.font = &fnt;
	label3.font_size = 4;
	label3.font_color = Color24::blue().asColor16();

	Element<Grid, 1> grid;
	grid.set_parent(&ui_core);
	grid.local_position = Point(160, 120);
	grid.size = Size(160, 120);

	auto img = BmpToImg::load("Img32x32.bmp");
	Element<UiBitmapView, 1> bitmap;
	bitmap.setBitmap(&img.pixels[0], Size(img.width, img.height));
	bitmap.set_parent(&ui_core);
	bitmap.local_position = Point(160, 0);
	bitmap.size = Size(img.width, img.height);

	auto img2 = BmpToImg::load("Img32x32.bmp");
	Element<UiBitmapView, 1> bitmap2;
	bitmap2.setBitmap(&img2.pixels[0], Size(img.width, img.height));
	bitmap2.set_parent(&ui_core);
	bitmap2.local_position = Point(192, 32);
	bitmap2.size = Size(img.width, img.height);

	auto prev_time = std::chrono::high_resolution_clock::now();
	
	uint32_t frame_id = 0;

	while (true) {
		/*bitmap2.local_position.x += 1;
		if (bitmap2.local_position.x > 224) {
			bitmap2.local_position.x = 192;
		}*/
		disp.fill_rect(Rect(0, 0, ui_core.size.x, ui_core.size.y),
			[&ui_core](Rect rect, Point point) {
			Color16 color;
			render_ui(&ui_core, point, color);
			return color;
		});

		disp.update();
		Sleep(0);
		frame_id++;

		auto now_time = std::chrono::high_resolution_clock::now();
		auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(now_time - prev_time);
		if(delta.count() >= 1000)
		{
			auto fps = frame_id * 1000 / delta.count();
			std::cout << "FPS: " << fps << std::endl;
			prev_time = now_time;
			frame_id = 0;
		}
	}


	return 0;
}


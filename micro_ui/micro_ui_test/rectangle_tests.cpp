#include <windows.h>
#include "CppUnitTest.h"
#include "../micro_ui/MicroUiTypes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace micro_ui_test {

TEST_CLASS(rectangle_tests) {
public:
	TEST_METHOD(test_rect_methods) {
		MicroUI::Rect rect_a(0, 10, 20, 30);

		Assert::IsTrue((MicroUI::Rect::element_t)0 == rect_a.x, L"X is not correct");
		Assert::IsTrue((MicroUI::Rect::element_t)10 == rect_a.y, L"Y is not correct");
		Assert::IsTrue((MicroUI::Rect::element_t)20 == rect_a.width, L"Width is not correct");
		Assert::IsTrue((MicroUI::Rect::element_t)30 == rect_a.height, L"Height is not correct");

		MicroUI::Rect rect_b(0, 10, 20, 30);

		Assert::IsTrue(rect_a.contains(rect_b), L"rect contains failed");
		Assert::IsFalse(rect_a.contains(MicroUI::Rect(0, 0, 0, 0)), L"rect contains failed");
		Assert::IsFalse(rect_a.contains(MicroUI::Rect(0, 10, 20, 40)), L"rect contains failed");
	}

};

}
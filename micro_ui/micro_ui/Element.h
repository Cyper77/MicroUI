#ifndef ui_element_h__
#define ui_element_h__

#include "MicroUiTypes.h"
#include "UiTransformProvider.h"

namespace MicroUI
{
	template<typename T, size_t MaxChildren>
	using Element = UiTransformProvider<T, MaxChildren>;
}
#endif // ui_element_h__

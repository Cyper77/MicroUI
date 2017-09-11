#ifndef ui_transform_provider_h__
#define ui_transform_provider_h__

#include "ElementBase.h"
#include <type_traits>
#include "uvector.h"

namespace MicroUI
{
	template<typename Base, uint32_t MaxChildren>
	class UiTransformProvider : public Base
	{
	public:
		using children_container = uvector<ElementBase*, MaxChildren>;

		uint32_t getChildrenCount() override {
			return _children.size();
		}
		ElementBase* get_child(uint32_t id) override {
			return _children[id];
		}
		uint32_t get_max_children() override {
			return MaxChildren;
		}

		bool get_child_id(ElementBase* child, size_t& id) override {
			for (children_container::size_type i = 0; i < _children.size(); ++i) {
				if (_children[i] == child) {
					id = (size_t)i;
					return true;
				}
			}
			return false;
		}


	private:
		children_container _children;
		bool add_child(ElementBase* child) override {
			if (child == nullptr || child == this) {
				return false;
			}
			return _children.push_pack((ElementBase*)child);
		}
		bool remove_child(ElementBase* child) override {

			auto val = std::find(_children.begin(), _children.end(), child);
			if(val == _children.end())
			{
				return false;
			}

			_children.fast_erase(val);
			return true;
		}
		
	};
}
#endif // ui_transform_provider_h__

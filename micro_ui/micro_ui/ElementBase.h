#ifndef ui_element_base_h__
#define ui_element_base_h__

#include "MicroUiTypes.h"

namespace MicroUI{
	class ElementBase {
	public:
		Size size;
		Color background_color;

		Rect local_rect() const {
			return Rect(Point(0,0), size);
		}

		Point local_position;

		virtual Point position() const {
			if (_parent != nullptr) {
				return _parent->position() + local_position;
			} else {
				return local_position;
			}
		}

		virtual bool renderColor(Point local_pos, Color16& color)
		{
			color = background_color;
			return true;
		}

		virtual uint32_t getChildrenCount() = 0;
		virtual ElementBase* get_child(uint32_t id) = 0;
		virtual uint32_t get_max_children() = 0;
		ElementBase* get_parent() {
			return _parent;
		}
		virtual void set_parent(ElementBase* parent) {
			auto prev_parent = get_parent();
			if (prev_parent == parent) {
				return;
			}

			if (prev_parent != nullptr) {
				prev_parent->remove_child(this);
			}

			_parent = parent;

			if (_parent != nullptr) {
				_parent->add_child(this);
			}
		}

		Point to_local_space(Point world_point) {
			return world_point - position();
		}

		Point to_world_space(Point local_point) {
			return local_point + position();
		}
		virtual bool get_child_id(ElementBase* child, size_t& id) = 0;
	protected:
		ElementBase* _parent;
		virtual bool add_child(ElementBase* child) = 0;
		virtual bool remove_child(ElementBase* child) = 0;
	};
}


#endif // ui_element_base_h__

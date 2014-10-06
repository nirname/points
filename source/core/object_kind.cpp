#include "object_kind.hpp"

ObjectKind::ObjectKind() {
	shape = NULL;
	color = NULL;
}

void ObjectKind::draw_shape() {
	if(shape != NULL) {
		shape->display();
	}
}

void ObjectKind::use_color() {
	if(color != NULL) {
		color->use();
	}
}

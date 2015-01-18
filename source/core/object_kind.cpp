#include "object_kind.hpp"

#include "drawing.hpp"

ObjectKind::ObjectKind() {
	shape = NULL;
	color = NULL;
	mask.insert(Point(1, 1));
}

void ObjectKind::draw_shape() {
	if(shape != NULL) {
		shape->display();
	} else {
		default_shape.display();
	}
}

void ObjectKind::use_color() {
	if(color != NULL) {
		color->use();
	} else {
		default_color.use();
	}
}

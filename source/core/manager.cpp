#include "manager.hpp"

#include "point.hpp"
#include <string>

Manager<std::string, Point> points;

void manager(){
	points.insert("A", new Point(1, 2));
}

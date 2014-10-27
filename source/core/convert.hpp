#pragma once

#include <string>
#include <ostream>

#include "yaml.hpp"
#include "color.hpp"
#include "drawing.hpp"

namespace YAML {

	template<>
	struct convert<Color> {

		static Node encode(const Color & color) {
			Node node;
			node.push_back(color.red);
			node.push_back(color.green);
			node.push_back(color.blue);
			return node;
		}

		static bool decode(const Node & node, Color & color) {
			//try {
				Color buffer;
				if(node.IsSequence()) {
					buffer.red = node[0].as<unsigned int>();
					buffer.green = node[1].as<unsigned int>();
					buffer.blue = node[2].as<unsigned int>();
					color = buffer;
				} else if (node.IsMap()) {
					if(node["red"]) { buffer.red = node["red"].as<unsigned int>(); }
					if(node["green"]) { buffer.green = node["green"].as<unsigned int>(); }
					if(node["blue"]) { buffer.blue = node["blue"].as<unsigned int>(); }
					color = buffer;
				} else if (node.IsScalar()) {
					std::string color_name = node.as<std::string>();
					if ( color_name == "black" ) { color.set( BLACK ); }
					else if ( color_name == "white" ) { color.set( WHITE ); }
					else if ( color_name == "gray" ) { color.set( GRAY ); }
					else if ( color_name == "blue" ) { color.set( BLUE ); }
					else if ( color_name == "yellow" ) { color.set( YELLOW ); }
					else if ( color_name == "green" ) { color.set( GREEN ); }
					else if ( color_name == "red" ) { color.set( RED ); }
					else if ( color_name == "violet" ) { color.set( VIOLET ); }
					else if ( color_name == "azure" ) { color.set( AZURE ); }
					else if ( color_name == "orange" ) { color.set( ORANGE ); }
					else if ( color_name == "soft_blue" ) { color.set( SOFT_BLUE ); }
					else if ( color_name == "soft_yellow" ) { color.set( SOFT_YELLOW ); }
					else if ( color_name == "soft_green" ) { color.set( SOFT_GREEN ); }
					else if ( color_name == "soft_red" ) { color.set( SOFT_RED ); }
					else if ( color_name == "soft_violet" ) { color.set( SOFT_VIOLET ); }
					else if ( color_name == "light_gray" ) { color.set( LIGHT_GRAY ); }
					else if ( color_name == "dark_violet" ) { color.set( DARK_VIOLET ); }
					else if ( color_name == "dark_gray" ) { color.set( DARK_GRAY ); }
				} else {
					return false;
				}
			//} catch(...) {}
			return true;
		}

	}; // convert<Color>


	template<>
	struct convert<DrawingFunction> {
		static Node encode(const DrawingFunction & shape_function) {
			Node node;
			return node;
		}

		static bool decode(const Node & node, DrawingFunction & shape_function) {
			if(!node.IsScalar()) {
				return false;
			}
			std::string value = node.as<std::string>();
			if(value == std::string("square")) {
				shape_function = square;
			} else if (value == std::string("point")) {
				shape_function = point;
			} else if (value == std::string("circle")) {
				shape_function = circle;
			} else {
				return false;
			}
			return true;
		}

	};

	/*template<>
	struct convert<SCREENSAVER_KIND> {
		static Node encode(const SCREENSAVER_KIND & screensaver_kind) {
			Node node;
			if(screensaver_kind == RANDOM_SCREENSAVER) {
				node = Node(to_string(screensaver_kind));
			} else
			//if(simple enum with only one bit) {
			//}
			else {
			}

			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}
	}; // convert<SCREENSAVER_KIND>
	*/

	/*template<>
	struct convert<bool> {
		static Node encode(const bool & parameter) {
			Node node;
			if(parameter == true) {
				node = std::string();
			}
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node & node, bool & parameter) {
			if(!node.IsScalar()) {
				return false;
			}
			std::string value = node.as<std::string>();
			if(value == std::string("on")) {
				parameter = true;
			} else if(value == std::string("off")) {
				parameter = false;
			} else {
				return false;
			}
			return true;
		}
	};*/

} // namespace YAML

/*template<typename T> void operator >> (const YAML::Node & option, T & parameter) {
	try {
		if(option.IsScalar()) {
			parameter = option.as<T>();
		}
	} catch(YAML::TypedBadConversion<T> & exception) {
	}
}*/

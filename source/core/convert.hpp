#pragma once

#include <string>
#include <ostream>

#include "yaml.hpp"
#include "color.hpp"
#include "shape.hpp"
#include "screen.hpp"

#include "emitter.hpp"

namespace YAML {

	template<>
	struct convert<Node> {

		static Node encode(const Node & source) {
			Node result = source;
			return result;
		}

		static bool decode(const Node & source, Node & result) {
			result = source;
			return true;
		}
	};

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
	struct convert<AspectRatio> {

		static Node encode(const AspectRatio & aspect_ratio) {
			Node node;
			node.push_back(aspect_ratio.width);
			node.push_back(aspect_ratio.height);
			return node;
		}

		static bool decode(const Node & node, AspectRatio & aspect_ratio) {
			AspectRatio buffer;
			if(node.IsSequence()) {
				buffer.width = node[0].as<unsigned int>();
				buffer.height = node[1].as<unsigned int>();
			} else if (node.IsMap()) {
				if(node["width"]) { buffer.width = node["width"].as<unsigned int>(); }
				if(node["height"]) { buffer.height = node["height"].as<unsigned int>(); }
			} else {
				return false;
			}
			aspect_ratio = buffer;
			return true;
		}

	}; // convert<AspectRatio>

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

	template<>
	struct convert<Shape *> {

		static Node encode(const Shape * & shape) {
			Node node;
			/*node.push_back(color.red);
			node.push_back(color.green);
			node.push_back(color.blue);*/
			return node;
		}

		static bool decode(const Node & node, Shape * & shape) {
			std::string shape_name;

			if(node.IsScalar()) {
				std::cout << "scalar" << std::endl;
				shape_name = node.as<std::string>();
				if(shape_name == "block") {
					shape = new ::Block;
				} else if(shape_name == "circle") {
					shape = new ::Circle;
				} else if(shape_name == "star") {
					shape = new ::Star;
				} else if(shape_name == "david") {
					shape = new ::David;
				} else if(shape_name == "diamond") {
					shape = new ::Diamond;
				} else if(shape_name == "triangle") {
					shape = new ::Triangle;
				} else {
					shape = new ::Block;
				}
			} else if(node.IsSequence() && node.size() >= 1) {
				std::cout << "sequence" << std::endl;
				shape_name = node[0].as<std::string>();
				if(shape_name == "ngon") {
					if(node.size() != 3) {
						std::cout << "Wrong number of arguments for ngon (should be 3)" << std::endl;
						return false;
					}
					int angles = node[1].as<int>();
					int step_over = node[2].as<int>();
					shape = new ::NGon(angles, step_over);
				}
			} else {
				return false;
			}

			return true;
		}
	};


} // namespace YAML

/*template<typename T> void operator >> (const YAML::Node & option, T & parameter) {
	try {
		if(option.IsScalar()) {
			parameter = option.as<T>();
		}
	} catch(YAML::TypedBadConversion<T> & exception) {
	}
}*/

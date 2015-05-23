#pragma once

#include "yaml.hpp"
#include "shape.hpp"

namespace YAML {

	template<>
	struct convert<Shape> {

		static Node encode(const Shape & shape) {
			Node node;
			return node;
		}

		static bool decode(const Node & node, Shape & shape) {
			std::cout << "Shape: " << std::ends;
			std::string shape_name;

			shape.clear();

			//if(shape.basic_shape == NULL) {
				try {
					if(node.IsScalar()) {
						std::cout << "(simple) ";
						shape_name = node.as<std::string>();
						if(shape_name == "block") {
							shape.basic_shape = new ::Block;
						} else if(shape_name == "circle") {
							shape.basic_shape = new ::Circle;
						} else if(shape_name == "star") {
							shape.basic_shape = new ::Star;
						} else if(shape_name == "david") {
							shape.basic_shape = new ::David;
						} else if(shape_name == "diamond") {
							shape.basic_shape = new ::Diamond;
						} else if(shape_name == "triangle") {
							shape.basic_shape = new ::Triangle;
						} else {
							std::cout << "unknown shape name "
								<< "`" << shape_name << "', "
								<< "default is used" << std::endl;
							shape.basic_shape = new ::Block;
						}
						std::cout << "`" << shape_name << "'" << std::endl;
					} else if(node.IsSequence() && node.size() >= 1) {
						std::cout << "(complex) ";
						shape_name = node[0].as<std::string>();
						if(shape_name == "ngon") {
							if(node.size() != 3) {
								std::cout << "wrong number of arguments for ngon (should be 2)" << std::endl;
								return false;
							}
							int angles = node[1].as<int>();
							int step_over = node[2].as<int>();
							shape.basic_shape = new ::NGon(angles, step_over);
							std::cout << "`" << shape_name << "'" << std::endl;
						} else {
							std::cout << "only ngon has arguments" << std::endl;
							return false;
						}
					} else {
						return false;
					}
				} catch(YAML::TypedBadConversion<std::string> & exception) {
					std::cout << "wrong shape name; ";
				} catch(YAML::TypedBadConversion<int> & exception) {
					std::cout << "wrong shape options; ";
				}
			//}

			if(shape.basic_shape != NULL && shape.basic_shape->base != 0) {
				std::cout << "ok" << std::endl;
				return false;
			} else {
				shape.basic_shape = new ::Block;
				std::cout << "shape wasn't created, default shape is used" << std::endl;
				return true;
			}

		}

	};

}

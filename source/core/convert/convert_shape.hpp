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

			if(shape.basic_shape != NULL) {
				delete shape.basic_shape;
				shape.basic_shape = NULL;
			}

			if(shape.basic_shape == NULL) {
				std::string shape_name;
				try {
					if(node.IsScalar()) {
						std::cout << "scalar" << std::endl;
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
							std::cout << "Unknown shape name "
								<< "`" << shape_name << "', "
								<< "default is used" << std::endl;
							shape.basic_shape = new ::Block;
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
							shape.basic_shape = new ::NGon(angles, step_over);
						} else {
							std::cout << "Only ngon has arguments" << std::endl;
							return false;
						}
					} else {
						return false;
					}
				} catch(YAML::TypedBadConversion<std::string> & exception) {
					std::cout << "Wrong shape name" << std::endl;
					return false;
				}
			}

			if(shape.basic_shape != NULL && shape.basic_shape->base != 0) {
				std::cout << "ok" << std::endl;
				return false;
			} else {
				std::cout << "shape wasn't created" << std::endl;
				return true;
			}

		}

	};

	/*template<>
	struct convert<BasicShape *> {

		static Node encode(const BasicShape * & shape) {
			Node node;
			return node;
		}

		static bool decode(const Node & node, BasicShape * & shape) {
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
				} else {
					std::cout << "Only ngon has arguments" << std::endl;
					return false;
				}
			} else {
				return false;
			}

			return true;
		}
	};*/

}

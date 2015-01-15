#pragma once

#include "shape.hpp"

namespace YAML {

	template<>
	struct convert<BasicShape *> {

		static Node encode(const BasicShape * & shape) {
			Node node;
			/*node.push_back(color.red);
			node.push_back(color.green);
			node.push_back(color.blue);*/
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
	};

}

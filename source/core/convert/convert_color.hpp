#pragma once

#include "color.hpp"

namespace YAML {

	template<>
	struct convert<Color> {

		static Node encode(const Color & color) {
			Node node;
			if(color == pallete::black)             node = "black";
			else if(color == pallete::dark_gray)    node = "dark-gray";
			else if(color == pallete::gray)         node = "gray";
			else if(color == pallete::light_gray)   node = "light-gray";
			else if(color == pallete::white)        node = "white";

			else if(color == pallete::red)          node = "red";
			else if(color == pallete::red_orange)   node = "red-orange";
			else if(color == pallete::yellow)       node = "yellow";
			else if(color == pallete::yellow_green) node = "yellow-green";
			else if(color == pallete::green)        node = "green";
			else if(color == pallete::sea_green)    node = "sea-green";
			else if(color == pallete::blue_green)   node = "blue-green";
			else if(color == pallete::cyan)         node = "cyan";
			else if(color == pallete::soft_blue)    node = "soft-blue";
			else if(color == pallete::sky_blue)     node = "sky-blue";
			else if(color == pallete::blue)         node = "blue";
			else if(color == pallete::purple)       node = "purple";
			else if(color == pallete::violet)       node = "violet";
			else if(color == pallete::red_violet)   node = "red-violet";
			else {
				node.push_back(color.red);
				node.push_back(color.green);
				node.push_back(color.blue);
			}
			return node;
		}

		static bool decode(const Node & node, Color & color) {
			try {
				if(node.IsSequence()) {
					color.rgb(
						node[0].as<int>(),
						node[1].as<int>(),
						node[2].as<int>()
					);
				} else if (node.IsMap()) {
					if(node["red"] && node["green"] && node["blue"]) {
						color.rgb(
							node["red"].as<int>(),
							node["green"].as<int>(),
							node["blue"].as<int>()
						);
					} else {
						return false;
					}
				} else if (node.IsScalar()) {
					std::string color_name = node.as<std::string>();
					if(color_name == "black")           color.hsv(BLACK);
					else if(color_name == "dark-gray")  color.hsv(DARK_GRAY);
					else if(color_name == "gray")       color.hsv(GRAY);
					else if(color_name == "light-gray") color.hsv(LIGHT_GRAY);
					else if(color_name == "white")      color.hsv(WHITE);

					else if(color_name == "red")          color.hsv(RED);
					else if(color_name == "red-orange")   color.hsv(RED_ORANGE);
					else if(color_name == "orange")       color.hsv(ORANGE);
					else if(color_name == "yellow-green") color.hsv(YELLOW);
					else if(color_name == "green")        color.hsv(GREEN);
					else if(color_name == "sea-green")    color.hsv(SEA_GREEN);
					else if(color_name == "blue-green")   color.hsv(BLUE_GREEN);
					else if(color_name == "cyan")         color.hsv(CYAN);
					else if(color_name == "sky-blue")     color.hsv(SKY_BLUE);
					else if(color_name == "soft-blue")    color.hsv(SOFT_BLUE);
					else if(color_name == "blue")         color.hsv(BLUE);
					else if(color_name == "purple")       color.hsv(PURPLE);
					else if(color_name == "violet")       color.hsv(VIOLET);
					else if(color_name == "red-violet")   color.hsv(RED_VIOLET);
					else return false;
				} else {
					return false;
				}
			} catch(YAML::TypedBadConversion<std::string()> & exception) {
				return false;
			}
			return true;
		}

	};

}

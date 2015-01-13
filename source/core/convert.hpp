#pragma once

#include <string>
#include <ostream>

#include "yaml.hpp"
#include "library.hpp"
#include "emitter.hpp"

#include "color.hpp"
#include "shape.hpp"
#include "aspect_ratio.hpp"
#include "size.hpp"
#include "manager.hpp"
#include "field.hpp"

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
						node[0].as<unsigned int>(),
						node[1].as<unsigned int>(),
						node[2].as<unsigned int>()
					);
				} else if (node.IsMap()) {
					if(node["red"] && node["green"] && node["blue"]) {
						color.rgb(
							node["red"].as<unsigned int>(),
							node["green"].as<unsigned int>(),
							node["blue"].as<unsigned int>()
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
			} catch(...) {}
			return true;
		}

	}; // convert<Color>

}

namespace YAML {

	template<>
	struct convert<AspectRatio> {

		static Node encode(const AspectRatio & aspect_ratio) {
			Node node;
			node.push_back(aspect_ratio.width);
			node.push_back(aspect_ratio.height);
			return node;
		}

		static bool decode(const Node & node, AspectRatio & aspect_ratio) {
			try {
				if(node.IsSequence() && node[0] && node[1]) {
					aspect_ratio = AspectRatio(node[0].as<unsigned int>(), node[1].as<unsigned int>());
				} else if (node.IsMap() && node["width"] && node["height"]) {
					aspect_ratio = AspectRatio(
						node["width"].as<unsigned int>(),
						node["height"].as<unsigned int>()
					);
				} else {
					return false;
				}
			} catch(...) {}
			return true;
		}

	}; // convert<AspectRatio>

	template<>
	struct convert<SCREENSAVER_KIND> {
		static Node encode(const SCREENSAVER_KIND & screensaver_kind) {
			Node node;
			if(screensaver_kind == RANDOM_SCREENSAVER || screensaver_kind == NO_SCREENSAVER) {
				node = to_string(screensaver_kind);
			} else {
				for(SCREENSAVER_KIND s = LIFE_SCREENSAVER; s <= TIMER_SCREENSAVER; s++) {
					if(screensaver_kind & s) {
						node.push_back(to_string(s));
					}
				}
			}
			return node;
		}

		static bool decode(const Node & node, SCREENSAVER_KIND & screensaver_kind) {
			screensaver_kind = NO_SCREENSAVER;
			std::string screensaver_name;
			if(node.IsScalar()) {
				screensaver_name = node.as<std::string>();
				if(screensaver_name == "random") {
					screensaver_kind = RANDOM_SCREENSAVER;
				} else {
					for(SCREENSAVER_KIND s = LIFE_SCREENSAVER; s <= TIMER_SCREENSAVER; s++) {
						if(screensaver_name == to_string(s)) {
							screensaver_kind = SCREENSAVER_KIND(screensaver_kind | s);
						}
					}
				}
			} else if (node.IsSequence()) {
				for(unsigned int i = 0; i < node.size(); i++) {
					screensaver_name = node[0].as<std::string>();
					for(SCREENSAVER_KIND s = LIFE_SCREENSAVER; s <= TIMER_SCREENSAVER; s++) {
						if(screensaver_name == to_string(s)) {
							screensaver_kind = SCREENSAVER_KIND(screensaver_kind | s);
						}
					}
				}
			} else {
				return false;
			}
			return true;
		}

	}; // convert<SCREENSAVER_KIND>

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

namespace YAML {

	template<>
	struct convert<Size> {

		static Node encode(const Size & size) {
			Node node;
			node.push_back(size.width);
			node.push_back(size.height);
			return node;
		}

		static bool decode(const Node & node, Size & size) {
			if(node.IsSequence() && node[0] && node[1]) {
				size = Size(node[0].as<unsigned int>(), node[1].as<unsigned int>());
			} else if (node.IsMap() && node["width"] && node["height"]) {
				size = Size(node[0].as<unsigned int>(), node[1].as<unsigned int>());
			} else {
				return false;
			}
			return true;
		}

	};

}

namespace YAML {

	template<>
	struct convert<Field> {
		static Node encode(const Field & field) {
			Node node;
			return node;
		}

		static bool decode(const Node & node, Field & field) {
			return false;
		}
	};

}

namespace YAML {

	template<>
	struct convert<View> {
		static Node encode(const View & view) {
			Node node;
			return node;
		}

		static bool decode(const Node & node, View & view) {
			return false;
		}
	};

}

namespace YAML {

	template<>
	struct convert<ObjectKind> {
		static Node encode(const ObjectKind & object_kind) {
			Node node;
			return node;
		}

		static bool decode(const Node & node, ObjectKind & object_kind) {
			return false;
		}
	};

}

namespace YAML {

	template<>
	struct convert<Object> {
		static Node encode(const Object & object) {
			Node node;
			return node;
		}

		static bool decode(const Node & node, Object & object) {
			return false;
		}
	};

}

namespace YAML {

	template<class Key, class Entity>
	struct convert< Manager<Key, Entity> > {

		static Node encode(const Manager<Key, Entity> & manager) {
			Node node;
			return node;
		}

		static bool decode(const Node & node, Manager<Key, Entity> & manager) {
			if(node.IsMap()) {
				Key key;
				for(YAML::const_iterator iterator = node.begin(); iterator != node.end(); ++iterator) {
					try {
						key = iterator->first.as<Key>();
					}
					catch(YAML::TypedBadConversion<std::string()> & exception) {
						std::cout << "wrong key" << std::endl;
						return false;
						//std::cout << "Can't upload entity" << std::endl;
					}
					Entity * entity = NULL;
					if((entity = manager.add(key)) != NULL) {
						try {
							*entity = iterator->second.as<Entity>();
						}
						catch(YAML::TypedBadConversion<std::string()> & exception) {
							std::cout << "wrong value" << std::endl;
							manager.remove(key);
							return false;
						}
					}

						/*if(has(_name)) {
							return NULL;
						} else {
							TypePointer instance = NULL;
							try {
								instance = build();
							} catch (...) {
								std::cout << "Can not allocate memory for new entity" << std::endl;
								return NULL;
							}
							try {
								options >> *instance;
							} catch(const EXCEPTION & exception) {
								std::cout << exception << std::endl;
								delete instance;
								return NULL;
							} catch(...) {
								std::cout << "An a error occured while creating entity" << std::endl;
								delete instance;
								return NULL;
							}
							set(_name, instance);
							return instance;
						}*/

						/*Entity * entity = new Entity;
						*entity = iterator->second.as<Entity>;
						manager.insert(iterator->first.as<std::string>(), );*/

				}
			} else {
				//std::cout << " should be a map" << std::endl;
			}
			return false;
		}

	};

}

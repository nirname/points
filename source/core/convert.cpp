#include "yaml.hpp"

namespace YAML {

	/*template<>
	struct convert<bool> {
		//static Node encode(bool rhs) {
		//	return rhs ? Node("true") : Node("false");
		//}

		static bool decode(const Node& node, bool& rhs) {
			if(!node.IsScalar()) {
				return false;
			}
			std::string value = node.as<std::string>();
			if(value == std::string("true")) {
				parameter = true;
			} else if(value == std::string("false")) {
				parameter = false;
			} else {
				return false;
			}
			return true;
		}
	};*/


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

}

template<typename T> void operator >> (const YAML::Node & option, T & parameter) {
	try {
		if(option.IsScalar()) {
			parameter = option.as<T>();
		}
	} catch(YAML::TypedBadConversion<T> & exception) {
	}
}

template<> void operator >> (const YAML::Node & option, bool & parameter) {
	if(option.IsScalar()) {
		std::string value = option.as<std::string>();
		if(value == std::string("on")) {
			parameter = true;
		} else {
			parameter = false;
		}
	}
}

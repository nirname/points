#pragma once

void operator >> (std::string & value, bool & parameter) {
	if(value == std::string("on")) {
		parameter = true;
	} else if(value == std::string("off")) {
		parameter = false;
	}
}


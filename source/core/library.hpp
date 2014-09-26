#pragma once

#include <string>
#include <sstream>

template <typename T> std::string to_string (T value);

template<typename Type> Type & operator++(Type & _link, int);

/// Converts everything that has 'std::ostream operator <<' defined to string
///
template<typename T> std::string to_string (T value) {
	std::stringstream stream;
	stream << value;
	return stream.str();
}

/// Allows iterating over enum
///
template<typename Type> Type & operator++(Type & _link, int) {
	const int i = static_cast<int>(_link);
	_link = static_cast<Type>(i + 1);
	return _link;
}

//std::string application_path();

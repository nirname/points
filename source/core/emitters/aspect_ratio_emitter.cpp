#include "aspect_ratio_emitter.hpp"

std::ostream & operator << (std::ostream & _ostream, const AspectRatio & aspect_ratio) {
	_ostream << "aspect_ratio("
		<< aspect_ratio.width << ", "
		<< aspect_ratio.height
	<< ")";
	return _ostream;
}

#pragma once

#include <ostream>

#include "screensaver.hpp"
#include "color.hpp"

std::ostream & operator << (std::ostream & _ostream, const SCREENSAVER_KIND & screensaver_kind);
std::ostream & operator << (std::ostream & _ostream, const Color & color);

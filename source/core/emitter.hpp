#pragma once

#include <ostream>

#include "screensaver.hpp"
#include "color.hpp"
#include "game.hpp"
#include "application.hpp"
#include "screen.hpp"
#include "size.hpp"

std::ostream & operator << (std::ostream & _ostream, const SCREENSAVER_KIND & screensaver_kind);
std::ostream & operator << (std::ostream & _ostream, const APPLICATION_MODE & application_mode);
std::ostream & operator << (std::ostream & _ostream, const GAME_KIND & game_kind);
std::ostream & operator << (std::ostream & _ostream, const Color & color);
std::ostream & operator << (std::ostream & _ostream, const AspectRatio & aspect_ratio);
std::ostream & operator << (std::ostream & _ostream, const Size & size);

#pragma once

#include <ostream>

#include "screensaver.hpp"
#include "color.hpp"
#include "game.hpp"
#include "application.hpp"

std::ostream & operator << (std::ostream & _ostream, const SCREENSAVER_KIND & screensaver_kind);
std::ostream & operator << (std::ostream & _ostream, const APPLICATION_MODE & application_mode);
std::ostream & operator << (std::ostream & _ostream, const GAME_KIND & game_kind);
std::ostream & operator << (std::ostream & _ostream, const Color & color);

#pragma once

#define EMPTY_SIZE 0.6f
#define FIGURE_SIZE 0.8f

const float FIGURE_OFFSET = (1.0 - FIGURE_SIZE) / 2.0;
//const float FIGURE_BORDER = FIGURE_SIZE + FIGURE_OFFSET;

const float DEG2RAD = 3.14159 / 180;
int graphics::sleep = 50;

#include "graphics/functions.h"

#include "graphics/screen_format.h"
#include "graphics/screen.h"

#include "graphics/color.h"
#include "graphics/drawing.h"
#include "graphics/animation.h"
#include "graphics/shape.h"



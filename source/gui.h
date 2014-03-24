#pragma once

struct MenuItem;
struct Menu;
struct Interface;

typedef std::pair<std::string, Menu> MenuWithTitle;

typedef std::list<MenuItem> MenuItems;
typedef std::map<std::string, Menu> Menus;

void quit();
void display_option(int position, MenuItem * _menu_item);

#include "gui/_menu_item.h"
#include "gui/_menu.h"
#include "gui/_interface.h"

#include "gui/menu_item.h"
#include "gui/menu.h"
#include "gui/interface.h"

#include "gui/functions.h"

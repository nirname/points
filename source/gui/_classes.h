#pragma once

struct MenuItem;
typedef void (* MenuItemHandler)(unsigned char, int, MenuItem *);
typedef std::list<MenuItem> MenuItems;

struct Menu;
typedef std::map<std::string, Menu> Menus;
typedef std::pair<std::string, Menu> MenuWithTitle;

struct Interface;

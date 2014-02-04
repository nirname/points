#pragma once

namespace test {

	class MenuManager {

		class Menu;
		class MenuItem;

		typedef Menu *  MenuPointer;
		typedef MenuItem * MenuItemPointer;
		typedef std::list<MenuItemPointer> MenuItems;

		class Menu {

			private:

				std::string title;
				MenuItems items;
				MenuItems::iterator current_item;

			public:

				Menu(std::string _title = "") : title(_title) {
					current_item = items.begin();
				}

		};

		class MenuItem {
			std::string title;
		};

	};

}

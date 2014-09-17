
namespace engine {

	void screensaver_autoload(int);
	void menu_autoload(int);
	void auto_exit(int);

	void reset_last_activity_time();
	int menu_time_left();

	struct Application {

		APPLICATION_MODE mode;

		Application() {
			mode == LOADING_MODE;
		}

		void set(APPLICATION_MODE _mode);

		void start();
		void quit();

		void handle(unsigned char, int);

		void     loading_process(unsigned char, int);
		void    foreword_process(unsigned char, int);
		void        menu_process(unsigned char, int);
		void screensaver_process(unsigned char, int);
		void   countdown_process(unsigned char, int);
		void    gameplay_process(unsigned char, int);
		void information_process(unsigned char, int);
		void   afterword_process(unsigned char, int);
		
		//void start_game();
		//void show_menu();
		

	};

}

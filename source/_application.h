
namespace engine {

	struct Application {

		APPLICATION_MODE mode;

		Application() {
			mode == LOADING_MODE;
		}

		void set(APPLICATION_MODE _mode);
		void reset_last_activity_time();

		void handle(unsigned char, int);

		void loading_process(unsigned char);
		void foreword_process(unsigned char);
		void menu_process(unsigned char, int);
		void screensaver_process(unsigned char);
		void countdown_process(unsigned char);
		void gameplay_process(unsigned char);
		void information_process(unsigned char);
		void afterword_process(unsigned char);

	};

}

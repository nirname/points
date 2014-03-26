
namespace engine {

	struct Application {

		APPLICATION_MODE mode;

		Application() {
			mode == LOADING_MODE;
		}

		void set(APPLICATION_MODE _mode);

		void handle(unsigned char, int);

		void     loading_process(unsigned char, int);
		void    foreword_process(unsigned char, int);
		void        menu_process(unsigned char, int);
		void screensaver_process(unsigned char, int);
		void   countdown_process(unsigned char, int);
		void    gameplay_process(unsigned char, int);
		void information_process(unsigned char, int);
		void   afterword_process(unsigned char, int);

	};

}
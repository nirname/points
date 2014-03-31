#pragma once

graphics::Screen screen(SCREEN_FORMAT_16x9);
engine::Game game;
engine::Application application;
Interface interface(&application, load_interface, display_interface);
Screensaver screensaver;

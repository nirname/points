#pragma once

#define ESCAPE_KEY 27
#define ENTER_KEY 13
#define TAB_KEY 9

#define CTRL_Q_KEY 17

void keyboard(unsigned char key, int x, int y);

void special(int special_key, int x, int y);

void mouse(int button, int state, int width, int height);

void glEnter2D(void) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
}

void glLeave2D(void) {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
}

void glWrite(float x, float y, int *font, char text[256], int kls) {
    int i;
    glRasterPos2f(x, y);
    for (i=0; i<kls; i++)
        glutBitmapCharacter(font, (int)text[i]);
}

//---

glEnter2D();
glColor3f(1,1,0);
glWrite(20, 20, (int*)GLUT_BITMAP_8_BY_13, (char*)"qwerty", 6);
glLeave2D();

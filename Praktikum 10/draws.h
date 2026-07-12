#ifndef DRAWS_H
#define DRAWS_H

#include <GL/freeglut.h>

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 240;

struct Vec3 {
    float x;
    float y;
    float z;

    Vec3(float xValue, float yValue, float zValue)
        : x(xValue), y(yValue), z(zValue) {}
};

inline void initView() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-450.0, 450.0, -120.0, 120.0);
    glMatrixMode(GL_MODELVIEW);
}

inline void reshapeView(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-450.0, 450.0, -120.0, 120.0);
    glMatrixMode(GL_MODELVIEW);
}

inline void drawText(Vec3 position, Vec3 normalColor, Vec3 highlightColor, const char* text, float scale, int startIdx, int length) {
    const float charWidth = 18.0f * scale;

    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glScalef(scale, scale, 1.0f);

    for (int i = 0; text[i] != '\0'; ++i) {
        if (i >= startIdx && i < startIdx + length) {
            glColor3f(highlightColor.x, highlightColor.y, highlightColor.z);
        } else {
            glColor3f(normalColor.x, normalColor.y, normalColor.z);
        }

        glRasterPos2f(i * charWidth / scale, 0.0f);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }

    glPopMatrix();
}

#endif

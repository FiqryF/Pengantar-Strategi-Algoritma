#include <windows.h>

#include <iostream>
#include <string>

#include <GL/freeglut.h>

#include "draws.h"

using namespace std;

char markText[1024];
string ptext;
string pattern;
int startIdx;

void drawResult() {
    glPushMatrix();

    sprintf(markText, "%s", ptext.c_str());
    Vec3 position(-350.0f, 0.0f, 0.0f);
    Vec3 color1(1.0f, 1.0f, 1.0f);
    Vec3 color2(1.0f, 0.0f, 1.0f);

    if (startIdx >= 0) {
        drawText(position, color1, color2, markText, 2.0f, startIdx, pattern.length());
    } else {
        drawText(position, color1, color1, markText, 2.0f, 0, pattern.length());
    }

    glPopMatrix();
}

void displayGraph() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawResult();

    glutSwapBuffers();
}

int* computeFail(string pattern) {
    int* fail = new int[pattern.length()];
    fail[0] = 0;
    int m = pattern.length();
    int j = 0;
    int i = 1;

    while (i < m) {
        if (pattern.at(j) == pattern.at(i)) {
            fail[i] = j + 1;
            i++;
            j++;
        } else if (j > 0) {
            j = fail[j - 1];
        } else {
            fail[i] = 0;
            i++;
        }
    }

    return fail;
}

int KMPMatch(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();
    int* fail = computeFail(pattern);
    int i = 0;
    int j = 0;

    while (i < n) {
        if (pattern.at(j) == text.at(i)) {
            if (j == m - 1) {
                delete[] fail;
                return i - m + 1;
            }
            i++;
            j++;
        } else if (j > 0) {
            j = fail[j - 1];
        } else {
            i++;
        }
    }

    delete[] fail;
    return -1;
}

int main(int argc, char** argv) {
    ptext = "abacaabacabacababa";
    pattern = "acabaca";

    cout << "cari: [" << pattern << "] di dalam teks: [" << ptext << "]\n";

    startIdx = KMPMatch(ptext, pattern);

    if (startIdx == -1) {
        cout << "pola tidak ditemukan pada teks\n";
    } else {
        cout << "pola ditemukan pada posisi-" << startIdx << "\n";
    }

    if (argc > 1 && string(argv[1]) == "--nogui") {
        return 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Praktikum 10 - String Matching KMP");
    initView();
    glutDisplayFunc(displayGraph);
    glutReshapeFunc(reshapeView);
    glutMainLoop();

    return 0;
}

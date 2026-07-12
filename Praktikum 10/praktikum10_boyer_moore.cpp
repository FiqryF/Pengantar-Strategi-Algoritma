#include <windows.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

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

vector<int> buildLastOccurrence(const string& pattern) {
    vector<int> last(256, -1);

    for (int i = 0; i < static_cast<int>(pattern.length()); ++i) {
        last[static_cast<unsigned char>(pattern.at(i))] = i;
    }

    return last;
}

int BoyerMooreMatch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    if (m == 0) {
        return 0;
    }

    vector<int> last = buildLastOccurrence(pattern);
    int i = m - 1;
    int j = m - 1;

    while (i < n) {
        if (text.at(i) == pattern.at(j)) {
            if (j == 0) {
                return i;
            }

            i--;
            j--;
        } else {
            int lo = last[static_cast<unsigned char>(text.at(i))];
            i = i + m - min(j, 1 + lo);
            j = m - 1;
        }
    }

    return -1;
}

int main(int argc, char** argv) {
    ptext = "abacaabacabacababa";
    pattern = "acabaca";

    cout << "cari: [" << pattern << "] di dalam teks: [" << ptext << "]\n";

    startIdx = BoyerMooreMatch(ptext, pattern);

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
    glutCreateWindow("Praktikum 10 - Boyer-Moore");
    initView();
    glutDisplayFunc(displayGraph);
    glutReshapeFunc(reshapeView);
    glutMainLoop();

    return 0;
}

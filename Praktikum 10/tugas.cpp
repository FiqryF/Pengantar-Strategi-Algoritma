#include <windows.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <GL/freeglut.h>

#include "draws.h"

using namespace std;

char markText[1024];
string textValue;
string patternValue;
int startIdx;
vector<int> lastOccurrenceTable;

vector<int> buildLastOccurrenceTable(const string& pattern) {
    vector<int> table(256, -1);

    for (int i = 0; i < static_cast<int>(pattern.length()); ++i) {
        table[static_cast<unsigned char>(pattern[i])] = i;
    }

    return table;
}

int BoyerMooreMatch(const string& text, const string& pattern) {
    int n = static_cast<int>(text.length());
    int m = static_cast<int>(pattern.length());

    if (m == 0) {
        return 0;
    }

    lastOccurrenceTable = buildLastOccurrenceTable(pattern);

    int i = m - 1;
    int j = m - 1;

    while (i < n) {
        if (text[i] == pattern[j]) {
            if (j == 0) {
                return i;
            }

            i--;
            j--;
        } else {
            int last = lastOccurrenceTable[static_cast<unsigned char>(text[i])];
            i = i + m - min(j, 1 + last);
            j = m - 1;
        }
    }

    return -1;
}

void printLastOccurrenceTable() {
    cout << "Last occurrence table untuk pattern:" << endl;
    vector<bool> printed(256, false);

    for (int i = 0; i < static_cast<int>(patternValue.length()); ++i) {
        char c = patternValue[i];
        if (printed[static_cast<unsigned char>(c)]) {
            continue;
        }

        printed[static_cast<unsigned char>(c)] = true;
        cout << c << " = " << lastOccurrenceTable[static_cast<unsigned char>(c)] << endl;
    }
}

void drawResult() {
    glPushMatrix();

    sprintf(markText, "%s", textValue.c_str());
    Vec3 position(-350.0f, 0.0f, 0.0f);
    Vec3 normalColor(1.0f, 1.0f, 1.0f);
    Vec3 highlightColor(0.0f, 1.0f, 1.0f);

    if (startIdx >= 0) {
        drawText(position, normalColor, highlightColor, markText, 2.0f, startIdx, patternValue.length());
    } else {
        drawText(position, normalColor, normalColor, markText, 2.0f, 0, patternValue.length());
    }

    glPopMatrix();
}

void displayGraph() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawResult();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    textValue = "abacaabacabacababa";
    patternValue = "acabaca";

    cout << "Post-Test Praktikum 10" << endl;
    cout << "Representasi: last occurrence table / bad character table" << endl;
    cout << "cari: [" << patternValue << "] di dalam teks: [" << textValue << "]" << endl;

    startIdx = BoyerMooreMatch(textValue, patternValue);
    printLastOccurrenceTable();

    if (startIdx == -1) {
        cout << "pola tidak ditemukan pada teks" << endl;
    } else {
        cout << "pola ditemukan pada posisi-" << startIdx << endl;
    }

    if (argc > 1 && string(argv[1]) == "--nogui") {
        return 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Post-Test Praktikum 10 - Boyer-Moore");
    initView();
    glutDisplayFunc(displayGraph);
    glutReshapeFunc(reshapeView);
    glutMainLoop();

    return 0;
}

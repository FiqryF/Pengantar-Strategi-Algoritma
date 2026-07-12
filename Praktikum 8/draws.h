#ifndef DRAWS_H
#define DRAWS_H

#include <cmath>
#include <cstdio>

#include <GL/freeglut.h>

#include "graph.h"

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 760;

struct Vec3 {
    float r;
    float g;
    float b;

    Vec3(float red, float green, float blue)
        : r(red), g(green), b(blue) {}
};

inline void applyColor(const Vec3& color) {
    glColor3f(color.r, color.g, color.b);
}

inline void initView() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

inline void reshapeView(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

inline void drawText(float x, float y, const char* text, const Vec3& color) {
    applyColor(color);
    glRasterPos2f(x, y);

    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

inline void drawCircle(NodePosition center, float radius, const Vec3& color) {
    applyColor(color);

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 64; ++i) {
        float theta = 2.0f * 3.1415926f * static_cast<float>(i) / 64.0f;
        glVertex2f(center.x + radius * cosf(theta), center.y + radius * sinf(theta));
    }
    glEnd();
}

inline void drawLine(NodePosition start, NodePosition end, const Vec3& color, float width) {
    glLineWidth(width);
    applyColor(color);

    glBegin(GL_LINES);
    glVertex2f(start.x, start.y);
    glVertex2f(end.x, end.y);
    glEnd();
}

inline void drawNodes(const Graph& graph) {
    for (int i = 0; i < graph.getNumNodes(); ++i) {
        NodePosition position = graph.getNodePosition(i);
        drawCircle(position, 0.075f, Vec3(0.0f, 1.0f, 0.0f));

        char label[16];
        std::snprintf(label, sizeof(label), "%d", i);
        drawText(position.x - 0.018f, position.y - 0.025f, label, Vec3(0.0f, 1.0f, 0.0f));
    }
}

inline void drawEdges(const Graph& graph) {
    const std::vector<std::vector<int> >& adjacency = graph.getAdjNodes();
    const std::vector<std::vector<int> >& distance = graph.getNodeDistance();

    for (int source = 0; source < graph.getNumNodes(); ++source) {
        for (int i = 0; i < static_cast<int>(adjacency[source].size()); ++i) {
            int target = adjacency[source][i];
            if (!graph.getIsDirected() && source > target) {
                continue;
            }

            NodePosition a = graph.getNodePosition(source);
            NodePosition b = graph.getNodePosition(target);
            drawLine(a, b, Vec3(0.75f, 0.75f, 0.75f), 2.0f);

            char label[16];
            std::snprintf(label, sizeof(label), "%d", distance[source][target]);
            drawText((a.x + b.x) / 2.0f + 0.02f, (a.y + b.y) / 2.0f + 0.02f, label, Vec3(1.0f, 1.0f, 1.0f));
        }
    }
}

#endif

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

inline void drawArrow(NodePosition start, NodePosition end, const Vec3& color, float width) {
    float radius = 0.07f;
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    float length = sqrtf(dx * dx + dy * dy);

    if (length <= 0.0f) {
        return;
    }

    float ux = dx / length;
    float uy = dy / length;

    NodePosition adjustedStart{start.x + ux * radius, start.y + uy * radius};
    NodePosition adjustedEnd{end.x - ux * radius, end.y - uy * radius};

    drawLine(adjustedStart, adjustedEnd, color, width);

    float arrowSize = 0.045f;
    float leftX = adjustedEnd.x - ux * arrowSize - uy * arrowSize * 0.7f;
    float leftY = adjustedEnd.y - uy * arrowSize + ux * arrowSize * 0.7f;
    float rightX = adjustedEnd.x - ux * arrowSize + uy * arrowSize * 0.7f;
    float rightY = adjustedEnd.y - uy * arrowSize - ux * arrowSize * 0.7f;

    glBegin(GL_TRIANGLES);
    applyColor(color);
    glVertex2f(adjustedEnd.x, adjustedEnd.y);
    glVertex2f(leftX, leftY);
    glVertex2f(rightX, rightY);
    glEnd();
}

inline void drawNodes(const Graph& graph) {
    for (int i = 0; i < graph.getNumNodes(); ++i) {
        NodePosition position = graph.getNodePosition(i);
        drawCircle(position, 0.07f, Vec3(0.0f, 1.0f, 0.0f));

        char label[16];
        std::snprintf(label, sizeof(label), "%d", i);
        drawText(position.x - 0.018f, position.y - 0.025f, label, Vec3(0.0f, 1.0f, 0.0f));
    }
}

inline void drawEdges(const Graph& graph) {
    const std::vector<std::vector<int> >& adjacency = graph.getAdjNodes();

    for (int source = 0; source < graph.getNumNodes(); ++source) {
        for (int i = 0; i < static_cast<int>(adjacency[source].size()); ++i) {
            int target = adjacency[source][i];
            drawArrow(
                graph.getNodePosition(source),
                graph.getNodePosition(target),
                Vec3(0.85f, 0.85f, 0.85f),
                2.0f
            );
        }
    }
}

#endif

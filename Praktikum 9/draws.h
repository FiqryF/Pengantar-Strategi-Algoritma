#ifndef DRAWS_H
#define DRAWS_H

#include <cstdio>
#include <string>

#include <GL/freeglut.h>

#include "graph.h"

struct Vec3 {
    float r;
    float g;
    float b;
    float a;

    Vec3(float red, float green, float blue, float alpha)
        : r(red), g(green), b(blue), a(alpha) {}
};

inline void applyColor(const Vec3& color) {
    glColor4f(color.r, color.g, color.b, color.a);
}

inline void drawText(float x, float y, const char* text, const Vec3& color, void* font = GLUT_BITMAP_HELVETICA_18) {
    applyColor(color);
    glRasterPos2f(x, y);

    for (const char* character = text; *character != '\0'; ++character) {
        glutBitmapCharacter(font, *character);
    }
}

inline void drawText(NodePosition position, const char* text, const Vec3& color, float, float) {
    drawText(position.x, position.y, text, color);
}

inline void drawLine(NodePosition start, NodePosition end, const Vec3& color, float width) {
    glLineWidth(width);
    applyColor(color);

    glBegin(GL_LINES);
    glVertex2f(start.x, start.y);
    glVertex2f(end.x, end.y);
    glEnd();
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

inline void drawFilledCircle(NodePosition center, float radius, const Vec3& color) {
    applyColor(color);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(center.x, center.y);
    for (int i = 0; i <= 64; ++i) {
        float theta = 2.0f * 3.1415926f * static_cast<float>(i) / 64.0f;
        glVertex2f(center.x + radius * cosf(theta), center.y + radius * sinf(theta));
    }
    glEnd();
}

inline void drawEdges(const Graph& graph) {
    Vec3 edgeColor(0.88f, 0.88f, 0.88f, 1.0f);
    Vec3 weightColor(1.0f, 1.0f, 1.0f, 1.0f);

    const std::vector<std::vector<int> >& adjacency = graph.getAdjNodes();

    for (int source = 0; source < graph.getNumNodes(); ++source) {
        for (int i = 0; i < static_cast<int>(adjacency[source].size()); ++i) {
            int target = adjacency[source][i];
            if (!graph.getIsDirected() && source > target) {
                continue;
            }

            NodePosition a = graph.getNodePosition(source);
            NodePosition b = graph.getNodePosition(target);
            drawLine(a, b, edgeColor, 2.0f);

            float midX = (a.x + b.x) / 2.0f;
            float midY = (a.y + b.y) / 2.0f;
            char label[16];
            std::snprintf(label, sizeof(label), "%.0f", graph.getNodeDistanceTo(source, target));
            drawText(midX + 0.03f, midY + 0.03f, label, weightColor, GLUT_BITMAP_HELVETICA_18);
        }
    }
}

inline void drawNodes(const Graph& graph) {
    for (int index = 0; index < graph.getNumNodes(); ++index) {
        NodePosition position = graph.getNodePosition(index);

        drawFilledCircle(position, 0.055f, Vec3(0.0f, 0.0f, 0.0f, 1.0f));
        drawCircle(position, 0.06f, Vec3(0.0f, 1.0f, 0.0f, 1.0f));

        char label[16];
        std::snprintf(label, sizeof(label), "%d", index);
        drawText(position.x - 0.018f, position.y - 0.025f, label, Vec3(0.0f, 1.0f, 0.0f, 1.0f), GLUT_BITMAP_HELVETICA_18);
    }
}

#endif

#include <windows.h>

#include <cmath>
#include <string>
#include <vector>

#include <GL/freeglut.h>

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 720;

struct Vec2 {
    float x;
    float y;
};

struct Node {
    int id;
    string shortName;
    string fullName;
    Vec2 position;
};

struct Edge {
    int from;
    int to;
    int weight;
};

vector<Node> nodes;
vector<Edge> edges;
vector<int> optimalRoute;

void setColor(float r, float g, float b) {
    glColor3f(r, g, b);
}

void drawText(float x, float y, const string& text, float r = 0.0f, float g = 0.0f, float b = 0.0f) {
    setColor(r, g, b);
    glRasterPos2f(x, y);

    for (int i = 0; i < static_cast<int>(text.length()); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

void drawCircle(Vec2 center, float radius, float r, float g, float b) {
    setColor(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(center.x, center.y);
    for (int i = 0; i <= 72; ++i) {
        float theta = 2.0f * 3.1415926f * static_cast<float>(i) / 72.0f;
        glVertex2f(center.x + radius * cosf(theta), center.y + radius * sinf(theta));
    }
    glEnd();

    setColor(0.0f, 0.0f, 0.45f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 72; ++i) {
        float theta = 2.0f * 3.1415926f * static_cast<float>(i) / 72.0f;
        glVertex2f(center.x + radius * cosf(theta), center.y + radius * sinf(theta));
    }
    glEnd();
}

void drawLine(Vec2 a, Vec2 b, float width, float r, float g, float blue) {
    glLineWidth(width);
    setColor(r, g, blue);
    glBegin(GL_LINES);
    glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
    glEnd();
}

void drawArrow(Vec2 a, Vec2 b, float width, float r, float g, float blue) {
    drawLine(a, b, width, r, g, blue);

    float dx = b.x - a.x;
    float dy = b.y - a.y;
    float length = sqrtf(dx * dx + dy * dy);

    if (length <= 0.0f) {
        return;
    }

    float ux = dx / length;
    float uy = dy / length;

    float arrowSize = 0.045f;
    Vec2 tip{b.x - ux * 0.075f, b.y - uy * 0.075f};
    Vec2 left{
        tip.x - ux * arrowSize - uy * arrowSize * 0.65f,
        tip.y - uy * arrowSize + ux * arrowSize * 0.65f
    };
    Vec2 right{
        tip.x - ux * arrowSize + uy * arrowSize * 0.65f,
        tip.y - uy * arrowSize - ux * arrowSize * 0.65f
    };

    setColor(r, g, blue);
    glBegin(GL_TRIANGLES);
    glVertex2f(tip.x, tip.y);
    glVertex2f(left.x, left.y);
    glVertex2f(right.x, right.y);
    glEnd();
}

Node getNodeById(int id) {
    for (int i = 0; i < static_cast<int>(nodes.size()); ++i) {
        if (nodes[i].id == id) {
            return nodes[i];
        }
    }

    return nodes[0];
}

void drawCompleteGraph() {
    for (int i = 0; i < static_cast<int>(edges.size()); ++i) {
        Node from = getNodeById(edges[i].from);
        Node to = getNodeById(edges[i].to);

        drawLine(from.position, to.position, 1.6f, 0.68f, 0.68f, 0.68f);

        float midX = (from.position.x + to.position.x) / 2.0f;
        float midY = (from.position.y + to.position.y) / 2.0f;

        string label = to_string(edges[i].weight) + " km";
        drawText(midX + 0.018f, midY + 0.018f, label, 0.20f, 0.20f, 0.20f);
    }
}

void drawOptimalRoute() {
    for (int i = 1; i < static_cast<int>(optimalRoute.size()); ++i) {
        Node from = getNodeById(optimalRoute[i - 1]);
        Node to = getNodeById(optimalRoute[i]);

        Vec2 a = from.position;
        Vec2 b = to.position;

        float dx = b.x - a.x;
        float dy = b.y - a.y;
        float length = sqrtf(dx * dx + dy * dy);
        if (length > 0.0f) {
            float radius = 0.075f;
            float ux = dx / length;
            float uy = dy / length;
            a.x += ux * radius;
            a.y += uy * radius;
            b.x -= ux * radius;
            b.y -= uy * radius;
        }

        drawArrow(a, b, 5.0f, 0.88f, 0.05f, 0.05f);
    }
}

void drawNodes() {
    for (int i = 0; i < static_cast<int>(nodes.size()); ++i) {
        drawCircle(nodes[i].position, 0.075f, 0.08f, 0.34f, 0.95f);

        string idLabel = to_string(nodes[i].id);
        drawText(nodes[i].position.x - 0.013f, nodes[i].position.y - 0.020f, idLabel, 1.0f, 1.0f, 1.0f);

        float labelX = nodes[i].position.x - 0.12f;
        float labelY = nodes[i].position.y - 0.13f;

        if (nodes[i].id == 0) {
            labelX = nodes[i].position.x - 0.17f;
            labelY = nodes[i].position.y - 0.14f;
        } else if (nodes[i].id == 1) {
            labelX = nodes[i].position.x - 0.20f;
            labelY = nodes[i].position.y + 0.12f;
        } else if (nodes[i].id == 2) {
            labelX = nodes[i].position.x - 0.12f;
            labelY = nodes[i].position.y - 0.14f;
        } else if (nodes[i].id == 3) {
            labelX = nodes[i].position.x - 0.15f;
            labelY = nodes[i].position.y + 0.12f;
        }

        drawText(labelX, labelY, nodes[i].shortName, 0.0f, 0.0f, 0.0f);
    }
}

void drawInfoPanel() {
    drawText(-0.88f, -0.63f, "Skenario Distribusi:", 0.0f, 0.0f, 0.0f);
    drawText(-0.88f, -0.70f, "Satu kendaraan berangkat dari gudang, mengunjungi seluruh cabang,", 0.0f, 0.0f, 0.0f);
    drawText(-0.88f, -0.77f, "lalu kembali ke gudang dengan jarak tempuh paling kecil.", 0.0f, 0.0f, 0.0f);

    drawText(-0.88f, -0.87f, "Metode: Branch and Bound untuk Travelling Salesman Problem (TSP)", 0.0f, 0.0f, 0.0f);
    drawText(-0.88f, -0.94f, "Rute terpilih: Gudang -> Bandung Timur -> Sumedang -> Cimahi -> Gudang", 0.0f, 0.0f, 0.0f);
    drawText(0.48f, -0.87f, "Total jarak = 80 km", 0.80f, 0.0f, 0.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawText(-0.55f, 0.91f, "Ilustrasi Studi Kasus Logistik - Branch and Bound TSP", 0.0f, 0.0f, 0.0f);
    drawText(-0.43f, 0.84f, "Optimasi urutan kunjungan cabang distribusi barang", 0.0f, 0.0f, 0.0f);

    drawCompleteGraph();
    drawOptimalRoute();
    drawNodes();
    drawInfoPanel();

    glutSwapBuffers();
}

void initView() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void buildData() {
    nodes.push_back(Node{0, "Gudang Pusat", "Gudang Pusat", Vec2{-0.78f, 0.12f}});
    nodes.push_back(Node{1, "Bandung Timur", "Cabang Bandung Timur", Vec2{0.70f, 0.48f}});
    nodes.push_back(Node{2, "Cimahi", "Cabang Cimahi", Vec2{0.70f, -0.28f}});
    nodes.push_back(Node{3, "Sumedang", "Cabang Sumedang", Vec2{0.02f, 0.66f}});

    edges.push_back(Edge{0, 1, 25});
    edges.push_back(Edge{0, 2, 15});
    edges.push_back(Edge{0, 3, 20});
    edges.push_back(Edge{1, 2, 35});
    edges.push_back(Edge{1, 3, 10});
    edges.push_back(Edge{2, 3, 30});

    optimalRoute.push_back(0);
    optimalRoute.push_back(1);
    optimalRoute.push_back(3);
    optimalRoute.push_back(2);
    optimalRoute.push_back(0);
}

int main(int argc, char** argv) {
    buildData();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Studi Kasus Logistik - Branch and Bound TSP");
    initView();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}

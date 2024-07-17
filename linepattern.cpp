#include <GL/glut.h>
#include <cmath>

void init() {
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    glPointSize(2);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void displaypoint(float x, float y) {
    glBegin(GL_POINTS);
    glColor3f(1, 1, 1);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}

void Simpleline(float x1, float y1, float x2, float y2) {
    float step;
    float dx = x2 - x1;
    float dy = y2 - y1;

    if (fabs(dx) > fabs(dy)) {
        step = fabs(dx);
    } else {
        step = fabs(dy);
    }

    float xin = dx / step;
    float yin = dy / step;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= step; i++) {
        displaypoint(x, y);
        x = x + xin;
        y = y + yin;
    }
}

void dottedline(float x1, float y1, float x2, float y2) {
    float step;
    float dx = x2 - x1;
    float dy = y2 - y1;

    if (fabs(dx) > fabs(dy)) {
        step = fabs(dx);
    } else {
        step = fabs(dy);
    }

    float xin = dx / step;
    float yin = dy / step;

    float x = x1;
    float y = y1;

    displaypoint(x, y);

    for (int i = 0; i <= step; i++) {
        x = x + xin;
        y = y + yin;
        if (i % 5 == 0) {
            displaypoint(x, y);
        }
    }
}

void dashedline(float x1, float y1, float x2, float y2) {
    float step;
    float dx = x2 - x1;
    float dy = y2 - y1;

    if (fabs(dx) > fabs(dy)) {
        step = fabs(dx);
    } else {
        step = fabs(dy);
    }

    float xin = dx / step;
    float yin = dy / step;

    float x = x1;
    float y = y1;

    for (int k = 0; k <= step; k++) {
        x = x + xin;
        y = y + yin;
        int m = k % 20;
        if (m % 9 != 0 && m % 10 != 0 && m % 11 != 0 && m % 12 != 0 && m % 16 != 0 && m % 17 != 0 && m % 18 != 0 && m % 19 != 0) {
            displaypoint(x, y);
        }
    }
}

// Additional algorithm for dashed line
void alternateDashedLine(float x1, float y1, float x2, float y2) {
    float step;
    float dx = x2 - x1;
    float dy = y2 - y1;

    if (fabs(dx) > fabs(dy)) {
        step = fabs(dx);
    } else {
        step = fabs(dy);
    }

    float xin = dx / step;
    float yin = dy / step;

    float x = x1;
    float y = y1;

    bool draw = true; // Flag to toggle drawing
    for (int k = 0; k <= step; k++) {
        x = x + xin;
        y = y + yin;

        // Draw only if draw flag is true
        if (draw) {
            displaypoint(x, y);
        }

        // Toggle draw flag every 10 steps
        if (k % 10 == 0) {
            draw = !draw;
        }
    }
}

void render() {
    dashedline(100, 100, 300, 100);
    dottedline(100, 200, 300, 200);
    Simpleline(100, 300, 300, 300);
    alternateDashedLine(100, 400, 300, 400); // Adding the alternate dashed line
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Line Pattern");
    init();
    glutDisplayFunc(render);
    glutMainLoop();
    return 0;
}


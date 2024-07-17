#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void setpixel(float x, float y) {
    glBegin(GL_POINTS);
    glColor3f(0, 0, 0);
    glVertex2f(x, y);
    glEnd();
}

void initialize() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 600, 0, 600);
}

void DDA(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float step = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xinc = dx / step;
    float yinc = dy / step;
    float x = x1;
    float y = y1;
    int i;
    for (i = 0; i <= step; i++) {
        setpixel(x, y);
        x += xinc;
        y += yinc;
    }
}

void bresenham(int xc, int yc, int r) {
    int d = 3 - 2 * r;
    int x = 0;
    int y = r;
    while (x <= y) {
        setpixel(xc + x, yc + y);
        setpixel(xc - x, yc + y);
        setpixel(xc + x, yc - y);
        setpixel(xc - x, yc - y);
        setpixel(xc + y, yc + x);
        setpixel(xc - y, yc + x);
        setpixel(xc + y, yc - x);
        setpixel(xc - y, yc - x);
        if (d < 0)
            d += 4 * x + 6;
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the first figure
    DDA(100, 100, 100, 200);
    DDA(100, 200, 130, 250);
    DDA(130, 250, 180, 250);
    DDA(180, 250, 180, 350);
    DDA(180, 350, 230, 350);
    DDA(230, 350, 230, 100);
    DDA(230, 100, 100, 100);

    // Draw the second figure
    DDA(235, 100, 235, 350);
    DDA(235, 350, 400, 350);
    DDA(400, 350, 400, 100);
    DDA(400, 100, 235, 100);

    // Draw circles
    bresenham(150, 50, 50);
    bresenham(150, 50, 20);
    bresenham(300, 50, 50);
    bresenham(300, 50, 20);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("OpenGL - FIGURE");
    initialize();
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}


#include<GL/glut.h>
#include<iostream>

using namespace std;
int cx, cy, p, q, r = 250;

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void bresenhamCircle(int xc, int yc, int r) {

    int d = 3 - 2 * r;
    int x = 0;
    int y = r;

    while (x <= y) {
        setPixel(xc + x, yc + y);
        setPixel(xc + y, yc + x);
        setPixel(xc - x, yc - y);
        setPixel(xc - y, yc - x);

        setPixel(xc - x, yc + y);
        setPixel(xc + y, yc - x);
        setPixel(xc - y, yc + x);
        setPixel(xc + x, yc - y);

        if (d < 0) {
            d = d + 4 * (x)+6;
        }
        else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}
void draw() {
    bresenhamCircle(250, 250, 200);
    bresenhamCircle(250, 250, 100);

    bresenhamCircle(250, 350, 100);
    bresenhamCircle(250, 150, 100);

    bresenhamCircle(150, 250, 100);
    bresenhamCircle(350, 250, 100);

    bresenhamCircle(178, 318, 100);
    bresenhamCircle(178, 182, 100);

    bresenhamCircle(322, 182, 100);
    bresenhamCircle(322, 318, 100);
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int args, char** argv) {

    glutInit(&args, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("CIrcle Pattern");
    init();
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}


// #include <GL/glut.h>
// #include <bits/stdc++.h>
// #include <iostream>
// using namespace std;

// int cx, cy, radius;

// void displayPoint(int x, int y)
// {
//     glBegin(GL_POINTS);
//     glVertex2i(x, y);
//     glEnd();
// }

// void simpleLine(int x1, int y1, int x2, int y2)
// {
//     float x, y, dx, dy, step, Xin, Yin;
//     dx = x2 - x1;
//     dy = y2 - y1;

//     if(abs(dx) > abs(dy))
//         step = abs(dx);
//     else
//         step = abs(dy);

//     Xin = dx/step;
//     Yin = dy/step;
//     x = x1;
//     y = y1;
//     displayPoint(x, y);
//     for(int i = 0; i < step; i++)
//     {
//         x += Xin;
//         y += Yin;
//         displayPoint(x, y);
//     }
//     glFlush();
// }

// void drawCirclePoints(int cx , int cy, int x, int y)
// {
//     glColor3f(0, 0, 0);
//     glBegin(GL_POINTS);

//     glVertex2i(cx + x, cy + y);
//     glVertex2i(cx - x, cy + y);
//     glVertex2i(cx + x, cy - y);
//     glVertex2i(cx - x, cy - y);

//     glVertex2i(cx + y, cy + x);
//     glVertex2i(cx - y, cy + x);
//     glVertex2i(cx + y, cy - x);
//     glVertex2i(cx - y, cy - x);

//     glEnd();
//     glFlush();
// }

// void drawCircle()
// {
//     int x = 0;
//     int y = radius;
//     int d = 3 - 2*radius;

//     drawCirclePoints(cx, cy, x, y);
//     while(y >= x)
//     {
//         x++;
//         if(d > 0)
//         {
//             y--;
//             d += 4 * (x - y) + 10;
//         }
//         else
//         {
//             d += 4*x + 6;
//         }
//         drawCirclePoints(cx, cy, x, y);
//     }
// }

// void keyboard(unsigned char key, int x, int y)
// {
//     cout << "The radius of the circle is : "<<key<<endl;
//     cout << "The center of the circle is : "<<"( "<<cx<<", "<<cy<<" )"<<endl;
//     radius = (key - '0') * 25;
//     drawCircle();

// }

// void mouseListener(int button, int state, int x, int y)
// {
//     cout << "The mouse co-ordinates are : "<<"( "<<x<<", "<<y<<" )"<<endl;
//     cout << "Enter the radius of the circle : "<<endl;
//     cx = x;
//     cy = y;
//     glutKeyboardFunc(keyboard);

// }

// void initialize(void)
// {
//     glClearColor(1.0, 1.0, 1.0, 1.0);
//     glClear(GL_COLOR_BUFFER_BIT);
//     gluOrtho2D(0, 800, 800, 0);
// }

// void primitives(void)
// {
//     glColor3f(0, 0, 0);
//     simpleLine(0, 400, 800, 400);
//     simpleLine(400, 0, 400, 800);
//     glutMouseFunc(mouseListener);
// }

// int main(int argc, char **argv)
// {
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//     glutInitWindowPosition(0, 0);
//     glutInitWindowSize(800, 800);
//     glutCreateWindow("Necklace");

//     initialize();

//     glutDisplayFunc(primitives);

//     glutMainLoop();
//     return 0;
// }
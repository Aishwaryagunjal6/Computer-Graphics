#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

double xmin = 50, ymin = 50, xmax = 100, ymax = 100;
double xvmin = 150, yvmin = 150, xvmax = 400, yvmax = 400;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

int ComputeoutCode(int x, int y)
{
	int code = 0;
	if (y > ymax)
	{
		code |= TOP;
	}
	else if (y < ymin)
	{
		code |= BOTTOM;
	}
	if (x > xmax)
	{
		code |= RIGHT;
	}
	else if (x < xmin)
	{
		code |= LEFT;
	}
	return code;
}

void clip(int x0, int y0, int x1, int y1)
{
	int outcode0, outcode1, outcodeout;
	bool accept = false, done = false;
	outcode0 = ComputeoutCode(x0, y0);
	outcode1 = ComputeoutCode(x1, y1);

	do
	{
		if (!(outcode0 | outcode1))
		{
			accept = true;
			done = true;
		}
		else if (outcode0 & outcode1)
		{
			done = true;
		}

		else
		{
			int x, y;
			outcodeout = outcode0 ? outcode0 : outcode1;
			if (outcodeout & TOP)
			{
				y = ymax;
				x = x1 + (ymax - y1) * ((x1 - x0) / (y1 - y0));
			}
			else if (outcodeout & BOTTOM)
			{
				y = ymin;
				x = x0 + (ymin - y0) * ((x1 - x0) / (y1 - y0));
			}
			else if (outcodeout & RIGHT)
			{
				x = xmax;
				y = y1 + (xmax - x1) * ((y1 - y0) / (x1 - x0));
			}
			else
			{
				x = xmin;
				y = y0 + (xmax - x0) * ((y1 - y0) / (x1 - x0));
			}
			if (outcodeout == outcode0)
			{
				x0 = x;
				y0 = y;
				outcode0 = ComputeoutCode(x0, y0);
			}
			else
			{
				x1 = x;
				y1 = y;
				outcode1 = ComputeoutCode(x1, y1);
			}
		}

	} while (!done);

	if (accept)
	{
		double sx = 5;
		double sy = 5;
		double vx0 = xvmin + (x0 - xmin) * sx;
		double vy0 = yvmin + (y0 - ymin) * sy;
		double vx1 = xvmin + (x1 - xmin) * sx;
		double vy1 = yvmin + (y1 - ymin) * sy;

		glBegin(GL_LINE_LOOP);
		glColor3f(1, 0, 0);
		glVertex2d(xvmin, yvmin);
		glVertex2d(xvmax, yvmin);
		glVertex2d(xvmax, yvmax);
		glVertex2d(xvmin, yvmax);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0, 1, 1);
		glVertex2d(xmin, ymin);
		glVertex2d(xmax, ymin);
		glVertex2d(xmax, ymax);
		glVertex2d(xmin, ymax);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(1, 1, 0);
		glVertex2d(vx0, vy0);
		glVertex2d(vx1, vy1);
		glEnd();
	}
}

void display()
{
	double x0 = 50, y0 = 50, x1 = 110, y1 = 110;
	double x2 = 30, y2 = 50, x3 = 120, y3 = 20;
	double x4 = 60, y4 = 40, x5 = 112, y5 = 125;

	glBegin(GL_LINES);
	glColor3f(1, 0, 1);
	glVertex2d(x0, y0);
	glVertex2d(x1, y1);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 0, 1);
	glVertex2d(x2, y2);
	glVertex2d(x3, y3);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 0, 1);
	glVertex2d(x4, y4);
	glVertex2d(x5, y5);
	glEnd();

	clip(x0, y0, x1, y1);
	clip(x2, y2, x3, y3);
	clip(x4, x4, x5, x5);
	glFlush();
}

void init()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0, 600, 0, 600);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(100, 0);
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL - FIGURE");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

int length, xi, yi, choice;
double angle, ET[3][3], ETResult[3][3];
void drawET(double ET[3][3])
{
    int i;
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < 3; i++)
    {
        glVertex2i(ET[i][0], ET[i][1]);
    }
    glEnd();
}

void Display()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(-320, 320, -240, 240);
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2d(-320, 0);
    glVertex2d(320, 0);
    glVertex2d(0, -240);
    glVertex2d(0, 240);
    glEnd();
    glColor3f(1, 0, 0);
    drawET(ET);
    glFlush();
}
void mult3X3(double ET[3][3], double temp[3][3])
{
    double sum;
    int i, j, k;
    for (i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            sum = 0;
            for (int k = 0; k < 3; k++)
            {
                sum = sum + ET[i][k] * temp[k][j];
            }
            ETResult[i][j] = sum;
        }
    }
}
void translationET()
{
    double tx, ty, temp[3][3];
    printf("\nTranslating Equilateral triangle");
    printf("\nEnter Tx: ");
    scanf("%lf", &tx);
    printf("\nEnter Ty: ");
    scanf("%lf", &ty);
    temp[3][3] = { 0 };
    temp[0][0] = 1;
    temp[1][1] = 1;
    temp[2][2] = 1;
    temp[2][0] = tx;
    temp[2][1] = ty;
    mult3X3(ET, temp);
    glColor3f(0.0, 1.0, 0.0);
    drawET(ETResult);
}
void rotationET()
{
    double rx, ry, angle, temp[3][3];
    printf("\n**ROTATION**\n");
    // printf("\nArbitrary Point (x,y) : ");
    // scanf("%lf %lf", &rx, &ry);
    printf("\nAngle (in degrees) : ");
    scanf("%lf", &angle);
    angle = angle * (M_PI / 180);
    temp[3][3] = { 0 };
    temp[0][0] = cos(angle);
    temp[0][1] = sin(angle);
    temp[1][0] = -sin(angle);
    temp[1][1] = cos(angle);
    temp[2][0] = 0;
    temp[2][1] = 0;
    temp[0][2] = 0;
    temp[1][2] = 0;
    temp[2][2] = 1;
    mult3X3(ET, temp);
    glColor3f(0.0, 1.0, 0.0);
    drawET(ETResult);
}
//----------Reflection-------------//
void reflectX() // creation of reflection to X axix matrix
{
    double temp[3][3];
    temp[0][0] = 1;
    temp[0][1] = 0;
    temp[0][2] = 0;
    temp[1][0] = 0;
    temp[1][1] = -1;
    temp[1][2] = 0;
    temp[2][0] = 0;
    temp[2][1] = 0;
    temp[2][2] = 1;
    mult3X3(ET, temp);
    glColor3f(0.0, 1.0, 0.0);
    drawET(ETResult);
}
void reflectY() // creation of reflection to X axix matrix
{
    double temp[3][3];
    temp[0][0] = -1;
    temp[0][1] = 0;
    temp[0][2] = 0;
    temp[1][0] = 0;
    temp[1][1] = 1;
    temp[1][2] = 0;
    temp[2][0] = 0;
    temp[2][1] = 0;
    temp[2][2] = 1;
    mult3X3(ET, temp);
    glColor3f(0.0, 1.0, 0.0);
    drawET(ETResult);
}
void reflectXY() // creation of reflection to X axix matrix
{
    double temp[3][3];
    temp[0][0] = -1;
    temp[0][1] = 0;
    temp[0][2] = 0;
    temp[1][0] = 0;
    temp[1][1] = -1;
    temp[1][2] = 0;
    temp[2][0] = 0;
    temp[2][1] = 0;
    temp[2][2] = 1;
    mult3X3(ET, temp);
    glColor3f(0.0, 1.0, 0.0);
    drawET(ETResult);
}

//----------Scaling-------------//
void scaleET()
{
    double sx, sy, temp[3][3];
    printf("\nScaling Equilateral triangle");
    printf("\nSx: ");
    scanf("%lf", &sx);
    printf("\nSy: ");
    scanf("%lf", &sy);
    temp[3][3] = { 0 };
    temp[0][0] = sx;
    temp[1][1] = sy;
    temp[2][2] = 1;
    mult3X3(ET, temp);
    glColor3f(1.0, 1.0, 0.0);
    drawET(ETResult);
}

void ShearXET()
{
    double shx, temp[3][3];
    printf("\nShearing Equilateral triangle");
    printf("\nShx: ");
    scanf("%lf", &shx);
    temp[3][3] = { 0 };
    temp[0][0] = 1;
    temp[1][1] = 1;
    temp[2][2] = 1;
    temp[1][0] = shx;
    mult3X3(ET, temp);
    glColor3f(1.0, 1.0, 0.0);
    drawET(ETResult);
}

void ShearYET()
{
    double shy, temp[3][3];

    printf("\nShearing Equilateral triangle");

    printf("\nShy: ");

    scanf("%lf", &shy);

    temp[3][3] = { 0 };

    temp[0][0] = 1;

    temp[1][1] = 1;

    temp[2][2] = 1;

    temp[0][1] = shy;

    mult3X3(ET, temp);

    glColor3f(1.0, 1.0, 0.0);

    drawET(ETResult);
}


//----------MENU--------------//
void Menu(int item)
{
    switch (item)
    {
    case 1:
        translationET();
        break;
    case 2:
        rotationET();
        break;
    case 3:
        reflectX();
        break;
    case 4:
        reflectY();
        break;
    case 5:
        reflectXY();
        break;

    case 6:
        scaleET();
        break;
        
    case 7:
        ShearXET();
        break;
        
    case 8:
        ShearYET();
        break;
                
    case 9:
        exit(0);
        break;
    }
}
int main(int argc, char** argv)
{
    int i, j;
    // printf("\nEnter X co-ordinate of a Base point: ");
    // scanf("%d", &xi);
    // printf("\nEnter Y co-ordinate of the Base point:");
    // scanf("%d", &yi);
    // printf("\nEnter length of sides: ");
    // scanf("%d", &length);
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            ET[i][j] = 1;
        }
    }
    ET[0][0] = 0;
    ET[0][1] = 0;
    ET[1][0] = 100;
    ET[1][1] = 0;
    ET[2][0] = 50;
    ET[2][1] = 75;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("2D-TRANSFORMATIONS");
    glutDisplayFunc(Display);
    glutCreateMenu(Menu);
    glutAddMenuEntry("1.Translation", 1);
    glutAddMenuEntry("2.Rotation", 2);
    glutAddMenuEntry("3.ReflectX", 3);
    glutAddMenuEntry("4.ReflectY", 4);
    glutAddMenuEntry("5.ReflectXY", 5);
    glutAddMenuEntry("6.Scaling", 6);
    glutAddMenuEntry("7.ShearingX", 7);
    glutAddMenuEntry("8.ShearingY", 8);
    glutAddMenuEntry("9.EXIT", 9);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}

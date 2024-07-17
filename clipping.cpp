#include <stdio.h>
#include <GL/glut.h>

double xmin = 50, ymin = 50, xmax = 100, ymax = 100;       // Window boundaries
double xvmin = 150, yvmin = 150, xvmax = 400, yvmax = 400; // Viewport boundaries

// bit codes for the right, left, top, & bottom   (tbrl)
const int RIGHT = 2;
const int LEFT = 1;
const int TOP = 8;
const int BOTTOM = 4;

// used to compute bit codes of a point
int ComputeOutCode(double x, double y)
{
    int code=0;
    if(y<ymin)
      code|=BOTTOM;
    else if(y>ymax)
      code|=TOP;
    if(x<xmin)
      code|=LEFT;
    else if(x>xmax)
      code|=RIGHT;
    return code;
}

void clip(double x0, double y0, double x1, double y1){
   int outCode0, outCode1, outCodeOut;
   bool accept=false, done=false;
   
   outCode0=ComputeOutCode(x0, y0);
   outCode1=ComputeOutCode(x1, y1);
   
   do{
      if(!(outCode0|outCode1)){
        accept=true;
        done=true;
      }
      else if(outCode0 & outCode1){
        done=true;
      }
      else{
        double x, y;
        outCodeOut=outCode0?outCode0:outCode1;
        if(outCodeOut & TOP){
           x=x1+(ymax-y1)*(x1-x0)/(y1-y0);    
           y=ymax;
        }
        else if(outCodeOut & BOTTOM){
           x=x0+(ymin-y0)*(x1-x0)/(y1-y0);
           y=ymin;
        }
        else if(outCodeOut & RIGHT){
           x=xmax;
           y=y0+(xmax-x0)*(y1-y0)/(x1-x0);
       }
       else{
           x=xmin;
           y=y0+(xmin-x0)*(y1-y0)/(x1-x0);
       }
       
       if(outCodeOut==outCode0){
          x0=x;
          y0=y;
          outCode0=ComputeOutCode(x0 , y0);
       }
       else{
          x1=x;
          y1=y;
          outCode1=ComputeOutCode(x1 , y1);   
       }
      }
     }while(!done);
     
     if(accept){
        double sx=5;
        double sy=5;
        double vx0= xvmin+(x0-xmin)*sx;
        double vy0= yvmin+(y0-ymin)*sy;
        double vx1=xvmin+(x1-xmin)*sx;
        double vy1=yvmin+(y1-ymin)*sy;
        
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(xvmin , yvmin);
        glVertex2f(xvmax, yvmin);
        glVertex2f(xvmax, yvmax);
        glVertex2f(xvmin, yvmax);
        
        glEnd();
        
        glColor3f(0.0, 1.0, 1.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(xmin, ymin);
        glVertex2f(xmax, ymin);
        glVertex2f(xmax, ymax);
        glVertex2f(xmin, ymax);
        
        glEnd();
        
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_LINES);
        glVertex2d(vx0, vy0);
        glVertex2d(vx1, vy1);
        glEnd();
      }
} 

void display(){
   double x0=30 , y0=20 , x1=80 , y1=120 ;       
   double x2=80 , y2=20 , x3=100 , y3=80 ;   
   double x4=10 , y4=80 , x5=40 , y5=80 ;   
   double x6=40 , y6=80 , x7=80 , y7=120 ;   
   double x8=130 , y8=50 , x9=60 , y9=120 ;
   
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0 , 1.0 , 0.0);
   glLineWidth(2);
        glBegin(GL_LINES);
        glVertex2d(x0, y0);
        glVertex2d(x1, y1);
        glEnd();
        glBegin(GL_LINES);
        glVertex2d(x2, y2);
        glVertex2d(x3, y3);
        glEnd();
        glBegin(GL_LINES);
        glVertex2d(x4, y4);
        glVertex2d(x5, y5);
        glEnd();
        glBegin(GL_LINES);
        glVertex2d(x6, y6);
        glVertex2d(x7, y7);
        glEnd();
        glBegin(GL_LINES);
        glVertex2d(x8, y8);
        glVertex2d(x9, y9);
        glEnd();    
  
        clip(x0, y0, x1, y1);
        clip(x2, y2, x3, y3);
        clip(x4, y4, x5, y5);
        clip(x6, y6, x7, y7);
        clip(x8, y8, x9, y9);
        glFlush();
}

void initialize(void){
   glClearColor(0.0, 0.0,0.0,0.0);
   glClear(GL_COLOR_BUFFER_BIT);
   gluOrtho2D(-600, 600, -600, 600);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(100, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("OpenGL - FIGURE");
    initialize();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}         
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
            


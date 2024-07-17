#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

void setpixel(float x, float y){
   	glBegin(GL_POINTS);
   	glColor3f(0,0,0);
   	glVertex2f(x,y);
   	glEnd();
}

void init(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,600,0,600);
}

struct pixel{
	float r,g,b;
};

pixel fclr;
pixel bclr;
pixel o;
pixel n;

void DDA(float x1, float y1, float x2, float y2){
	   float dx=x2-x1;
	   float dy=y2-y1;
	   float step=abs(dx)>abs(dy) ? abs(dx) : abs(dy);
	   float x=x1;
	   float y=y1;
	   float xinc= dx/step;
	   float yinc= dy/step;
	   
	   for(int i=0; i<=step; i++){
	   	setpixel(x,y);
	   	x+=xinc;
	   	y+=yinc;
	   }
}

void BSA(float x1, float y1, float x2, float y2){
	float dx=x2-x1;
	float dy=y2-y1;
	float x=x1;
	float y=y1;
	float xin =1, yin=1;
	
	if(dx<0){
		dx=-dx;
	}
	if(dy<0){
		dy=-dy;
	}
	if(x1>x2){
		xin=-1;
	}
	if(y1>y2){
		yin=-1;
	}
	setpixel(x,y);
	
	if(dx>dy){
		float p= 2*dy-dx;
		for(int i = 0;i < dx;i++){
		  if(p>0){
			p+=2*(dy-dx);
			y+=yin;
		  }
		  else{
			p+=2*dy;
		  }
		  x+=xin;
		  setpixel(x,y);
		}
	}
	else{
		float p= 2*dx-dy;
		for(int i = 0;i < dy;i++){
		  if(p>0){
			p+=2*(dx-dy);
			x+=xin;
		  }
		  else{
			p+=2*dx;
		  }
		  y+=yin;
		  setpixel(x,y);
		}  
	}
	
}

void boundaryfill(float x, float y){
    pixel c;
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, &c);
    if((c.r!=fclr.r || c.g!=fclr.g || c.b!=fclr.b) && (c.r!=bclr.r || c.g!=bclr.g || c.b!=bclr.b)){
          glBegin(GL_POINTS);
          glColor3f(fclr.r , fclr.g, fclr.b);
          glVertex2f(x,y);
          glEnd();
          glFlush();
          boundaryfill(x-1 , y);
          boundaryfill(x+1 , y);
          boundaryfill(x, y+1);
          boundaryfill(x, y-1);
     }
}

void floodfill(float x, float y, pixel o, pixel n){
    pixel c;
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, &c);
    if(c.r== o.r && c.g==o.g && c.b==o.b){
          glBegin(GL_POINTS);
          glColor3f(n.r , n.g, n.b);
          glVertex2f(x,y);
          glEnd();
          glFlush();
          floodfill(x-1 , y, o, n);
          floodfill(x+1 , y, o, n);
          floodfill(x, y+1, o, n);
          floodfill(x, y-1, o, n);
     }
}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	/*DDA(200,200,500,200);
        DDA(500,200,500,400);
        DDA(500,400,200,400);
        DDA(200,400,200,200);
    
        DDA(200,200,270,250);
        DDA(270,250,350,200);
        DDA(350,200,400,300);
        DDA(400,300,500,200);
    
        DDA(150,150,325,150);
        DDA(325,150,300,90);
        DDA(300,90,400,90);
        DDA(400,90,375,150);
        DDA(375,150,550,150);
        DDA(550,150,550,450);
        DDA(550,450,150,450);
        DDA(150,450,150,150);*/
        
        //inside rectangle
        BSA(200,200,500,200);
        BSA(500,200,500,400);
        BSA(500,400,200,400);
        BSA(200,400,200,200);
    	
    	
    	//mountains
        BSA(200,200,270,250);
        BSA(270,250,350,200);
        BSA(350,200,400,300);
        BSA(400,300,500,200);
    	
    	
    	//outside rectangle
        BSA(150,150,325,150);
        BSA(325,150,300,90);
        BSA(300,90,400,90);
        BSA(400,90,375,150);
        BSA(375,150,550,150);
        BSA(550,150,550,450);
        BSA(550,450,150,450);
        BSA(150,450,150,150);
        
        glFlush();
  
 }
 
 void color(){       
        
        //Boundaryfill
        bclr.r=0;
        bclr.g=0;
        bclr.b=0;
        fclr.r=1;
        fclr.g=0;
        fclr.b=0;
        boundaryfill(175, 175);
        
        fclr.r=0;
        fclr.g=1;
        fclr.b=1;
        boundaryfill(250, 235);  //mountain 1
        boundaryfill(400, 255);  //mountain 2
        
        
        //floodfill
        o.r=1;
        o.g=1;
        o.b=1;
        n.r=1;
        n.g=0;
        n.b=0;
        floodfill(175, 175, o, n);
        
        n.r=0;
        n.g=1;
        n.b=0;
        floodfill(175, 175, o, n);//mountain 1
        floodfill(175, 175, o, n);//mountain 2
        
	glFlush();
	
}

int ch=1;
void mymouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // If left click
    {
        switch (ch)
        {
        case 1:
            ch = 2;
            draw();
            break;
        case 2: 
            color();
            ch = 1;
            break;
        }
    }
}



void initfun(){
   glFlush();
}	

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(600,600);
	glutCreateWindow("screen");
	init();
	glutDisplayFunc(initfun);
        glutMouseFunc(mymouse); 
	glutMainLoop();
	return 0;
	
}   
	   

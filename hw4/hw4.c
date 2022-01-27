/*
 * Eliza Mimi To Homework4
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
//#ifdef USEGLEW
//#include <GL/glew.h>
//#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define PI 3.1415927
#ifndef RES
#define RES 1
#endif
#define LEN 8192

/*
 
 
 1. 'WASD' keys To move in first person!
 2. 'F key to get into first person!
 3. 'M' is the mode key to change mode
 4. 0 key is to reset the angel !
 5. Esc to exit
 6. Right Up Left Down keys to move not in first person!


 
 */


int th = 50.0;
int ph = 50.0;
int mode = 0;       //  Projection Mode!!
int fov = 50;       // Perspective!
int fp = 0;            // This is the First Person variable
double asp = 1;
double dim = 1.5; // The dim of where my fp is going to start

#define Cos(x) (cos((x)*3.14159265/180))
#define Sin(x) (sin((x)*3.14159265/180))

int rotation = 0.0;
// This is where the eye coordination of the on the x y z will be !!
double Ex = 0.0;
double Ey = 0.0;
double Ez = 2.5; // this will be align with my boats
// THE CAMERA FROM WHAT I LEARNED
double Cx = 0.0;
double Cz = 0.0;



void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;   // Text pointer
   //  Create text to be display
   va_list args;
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display text string
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

//MY PROJECTION

static void Project()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if (fp) {
        gluPerspective(fov, asp, dim / 4, dim * 4);
    }
    else {
        if (mode)
            gluPerspective(fov, asp, dim / 4, 4 * dim);
        else
            glOrtho(-asp * dim, +asp * dim, -dim, +dim, -dim, +dim); //ORTHAGONAL
    }
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void Fatal(const char* format , ...)
{
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}

void ErrCheck(char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}



static void triangle(double x,double y,double z,double dx,double dy,double dz, double th)
{
   //  Save transformation
    glPushMatrix();
    
    glRotated(th,0,1,0);
    glRotated(180,1,0,0);
    glTranslated(x,y,z);
    
    glScaled(dx,dy,dz);
    

    //Front red
    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex3f(-1,-1, 1);
    glVertex3f(+1,-1, 1);
    glVertex3f(+1,+1, 1);
    
    glEnd();
    
    //Back
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    glVertex3f(-1,-1, -1);
    glVertex3f(+1,-1, -1);
    glVertex3f(+1,+1, -1);
    
    glEnd();
    
    
    //Square Side
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
    glVertex3f(1,-1, -1);
    glVertex3f(1,-1, 1);
    glVertex3f(1,1, 1);
    glVertex3f(1,1, -1);
    
    glEnd();
    
    //Hypo
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
    glVertex3f(1,1, 1);
    glVertex3f(1,1, -1);
    glVertex3f(-1,-1, -1);
    glVertex3f(-1,-1, 1);
    
    glEnd();
    
  
   //  Undo transformations
   glPopMatrix();
}

/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */

static void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Cube
   glBegin(GL_QUADS);
   //  Front
   glColor3f(1,1,1);
   glVertex3f(-1,-1, 1);
   glVertex3f(+1,-1, 1);
   glVertex3f(+1,+1, 1);
   glVertex3f(-1,+1, 1);
   //  Back
   glColor3f(1,1,1);
   glVertex3f(+1,-1,-1);
   glVertex3f(-1,-1,-1);
   glVertex3f(-1,+1,-1);
   glVertex3f(+1,+1,-1);
   //  Right
   glColor3f(1,1,1);
   glVertex3f(+1,-1,+1);
   glVertex3f(+1,-1,-1);
   glVertex3f(+1,+1,-1);
   glVertex3f(+1,+1,+1);
   //  Left
   glColor3f(1,1,1);
   glVertex3f(-1,-1,-1);
   glVertex3f(-1,-1,+1);
   glVertex3f(-1,+1,+1);
   glVertex3f(-1,+1,-1);
   //  Top
   glColor3f(1,1,1);
   glVertex3f(-1,+1,+1);
   glVertex3f(+1,+1,+1);
   glVertex3f(+1,+1,-1);
   glVertex3f(-1,+1,-1);
   //  Bottom
   glColor3f(1,1,1);
   glVertex3f(-1,-1,-1);
   glVertex3f(+1,-1,-1);
   glVertex3f(+1,-1,+1);
   glVertex3f(-1,-1,+1);
   //  End
   glEnd();
   //  Undo transformations
   glPopMatrix();
}



static void containers(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Cube
   glBegin(GL_QUADS);
   //  Front
   glColor3f(1,0,0);
   glVertex3f(-1,-1, 1);
   glVertex3f(+1,-1, 1);
   glVertex3f(+1,+1, 1);
   glVertex3f(-1,+1, 1);
   //  Back
   glColor3f(1,0,0);
   glVertex3f(+1,-1,-1);
   glVertex3f(-1,-1,-1);
   glVertex3f(-1,+1,-1);
   glVertex3f(+1,+1,-1);
   //  Right
   glColor3f(1,0,0);
   glVertex3f(+1,-1,+1);
   glVertex3f(+1,-1,-1);
   glVertex3f(+1,+1,-1);
   glVertex3f(+1,+1,+1);
   //  Left
   glColor3f(1,0,0);
   glVertex3f(-1,-1,-1);
   glVertex3f(-1,-1,+1);
   glVertex3f(-1,+1,+1);
   glVertex3f(-1,+1,-1);
   //  Top
   glColor3f(1,0,0);
   glVertex3f(-1,+1,+1);
   glVertex3f(+1,+1,+1);
   glVertex3f(+1,+1,-1);
   glVertex3f(-1,+1,-1);
   //  Bottom
   glColor3f(1,0,0);
   glVertex3f(-1,-1,-1);
   glVertex3f(+1,-1,-1);
   glVertex3f(+1,-1,+1);
   glVertex3f(-1,-1,+1);
   //  End
   glEnd();
   //  Undo transformations
   glPopMatrix();
}

static void stick(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Cube
   glBegin(GL_QUADS);
   //  Front
   glColor3f(.5,.35,.05);
   glVertex3f(-1,-1, 1);
   glVertex3f(+1,-1, 1);
   glVertex3f(+1,+1, 1);
   glVertex3f(-1,+1, 1);
   //  Back
    glColor3f(.5,.35,.05);
   glVertex3f(+1,-1,-1);
   glVertex3f(-1,-1,-1);
   glVertex3f(-1,+1,-1);
   glVertex3f(+1,+1,-1);
   //  Right
    glColor3f(.5,.35,.05);
   glVertex3f(+1,-1,+1);
   glVertex3f(+1,-1,-1);
   glVertex3f(+1,+1,-1);
   glVertex3f(+1,+1,+1);
   //  Left
    glColor3f(.5,.35,.05);
   glVertex3f(-1,-1,-1);
   glVertex3f(-1,-1,+1);
   glVertex3f(-1,+1,+1);
   glVertex3f(-1,+1,-1);
   //  Top
    glColor3f(.5,.35,.05);
   glVertex3f(-1,+1,+1);
   glVertex3f(+1,+1,+1);
   glVertex3f(+1,+1,-1);
   glVertex3f(-1,+1,-1);
   //  Bottom
    glColor3f(.5,.35,.05);
   glVertex3f(-1,-1,-1);
   glVertex3f(+1,-1,-1);
   glVertex3f(+1,-1,+1);
   glVertex3f(-1,-1,+1);
   //  End
   glEnd();
   //  Undo transformations
   glPopMatrix();
}



static void flag(double x,double y,double z,double dx,double dy,double dz, double th, int color)
{
   //  Save transformation
    glPushMatrix();
    glRotated(th,0,1,0);
    glRotated(0,1,0,0);
    glTranslated(x,y,z);
    glScaled(dx,dy,dz);
    glBegin(GL_POLYGON);
    if (color == 1)
        glColor3f(0,0,1);
    if (color == 2)
        glColor3f(1,0,0);
    if (color == 3)
        glColor3f(0,1,0);
    glVertex3f(-1,-1, 1);
    glVertex3f(+1,-1, 1);
    glVertex3f(+1,+1, 1);
    glEnd();
   glPopMatrix();
}




void drawboat(double x, double y, double z, double width, double height, double depth, int color){
    
    
    glPushMatrix();
    
    glTranslated(x,y,z);
    glScaled(width,height,depth);
    
    flag(-1,3.6,0,1,.4,0,180,color); // FLAG OF BOAT
    stick(0, 3.4,0, .08,.6,.05,0); // STICK OF BOAT
    containers(0, 1.3,0, 3,.4,1,0); // CONTAINER SHIP 1
    containers(0, 1.3,0, 3,.4,1,0); // CONTAINER SHIP 2
    containers(0, 2,0, 2,.4,1,0); // CONTAINER SHIP 3
    cube(0,0,0, 2,1,1,0);// multiply by 2 to stretch the width out
    cube(0,2.6,0, 1,.2,1,0);
    triangle(-3,0,0,1,1,1,0);// scaled it to match width with cube
    triangle(-3,0,0,1,1,1,180);// rotate 180 for
    glFlush();
    glEnd();

    glPopMatrix();
    
}


/*
 * DISPLAY
 */
void display()
{
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    //glRotatef(th,0.0,1.0,0.0);
    //glRotatef(ph,1.0,0.0,0.0);

    if (fp) { //If first person ...
        Cx = +2 * dim*Sin(rotation);
        Cz = -2 * dim*Cos(rotation);
        gluLookAt(Ex, Ey, Ez, Cx + Ex, Ey, Cz + Ez, 0, 1, 0);
    }
    else {
        if (mode) { //PERSPECTIVE
            double per_x = -2 * dim*Sin(th)*Cos(ph);
            double per_y = +2 * dim*Sin(ph);
            double per_z = +2 * dim*Cos(th)*Cos(ph);
            gluLookAt(per_x, per_y, per_z, 0, 0, 0, 0, Cos(ph), 0);
        }
        else { //ORTHAGONAL
            glRotatef(ph, 1, 0, 0);
            glRotatef(th, 0, 1, 0);
        }
    }
    
    drawboat(-.8,0,0, .07,.07,.08,1); //big blue
    drawboat(.5,0,0,.05,.1,.13,2);// red
    drawboat(-.1,0,-.5, .1,.04,.1,3);//green
    drawboat(.9,0,-.5, .03,.04,.03,1);//mini blue
    
    glWindowPos2i(5,30);
    Print("F key for FP and WASD to move and M for mode!");
    
    // X Y Z AXIS !
       /* glColor3f(1.0,0.0,0.0); // X IS RED
           glBegin(GL_LINES);
           // X- Axis
           glVertex3f(-1.0, 0.0f, 0.0f);
           glVertex3f(1.0, 0.0f, 0.0f);
            glEnd();
           glFlush();
           // Y-Axis
           glColor3f(0.0,1.0,0.0); // Y IS GREEN
           glBegin(GL_LINES);
           glVertex3f(0.0, -2.0f, 0.0f);
           glVertex3f(0.0, 2.0f, 0.0f);
           glEnd();
           glFlush();
           // Z-Axis
           glColor3f(0.0,0.0,1.0); // Z IS BLUE
           glBegin(GL_LINES);
           glVertex3f(0.0, 0.0f ,-2.0f );
           glVertex3f(0.0, 0.0f ,2.0f );
           glEnd();
           glFlush();*/
    
    glFlush();
    glutSwapBuffers();
    

}

//Special keys!!

void special(int key,int x,int y)
{
   //  Right arrow key
    if(!fp){
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
    }
    Project();
   glutPostRedisplay();
}


void key(unsigned char ch, int x, int y)
{
    //  Exit on ESC
    if (ch == 27)
        exit(0);
    //  FP
    else if (ch == 'f') {
        fp = 1 - fp;
    }
    if (fp) {
        double dt = 0.05;
        //FOWARD
        if (ch == 'w') {
            Ex += Cx * dt;
            Ez += Cz * dt;
        }
        //LEFT
        else if (ch == 'a') {
            rotation -= 3;
        }
        //BACKWARDS
        else if (ch == 's') {
            Ex -= Cx * dt;
            Ez -= Cz * dt;
        }
        //RIGHT
        else if (ch == 'd') {
            rotation += 3;
        }
        //KEEP ANGEL 360 DEGREES
        rotation %= 360;
    }
    else {
        //RESET ANGEL
        if (ch == '0')
            th = ph = 45;
        //SWITCH MODE
        else if (ch == 'm')
            mode = 1 - mode;
    }
    
    Project();
    glutPostRedisplay();
}


/*
 * This function is called by GLUT when the window is resized
 */
void reshape(int width,int height)
{
   /*glViewport(0,0, RES*width,RES*height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   double asp = (height>0) ? (double)width/height : 1;
   glOrtho(-asp,+asp, -1.0,+1.0, -1.0,+1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();*/
    //CONDENCED USING PROJECTION VVV
        asp = (height > 0) ? (double)width / height : 1;
        glViewport(0, 0, width, height);
        Project();
}


int main(int argc,char* argv[])
{
    //  Initialize GLUT
    glutInit(&argc,argv);
    glutInitWindowSize(500, 500);
    //  Request double buffered true color window with Z-buffer
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    //  Create window
    glutCreateWindow("Eliza Mimi To");
 #ifdef USEGLEW
    //  Initialize GLEW
    if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
 #endif
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutKeyboardFunc(key);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}

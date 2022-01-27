
/*
 * Eliza Mimi To FINAL PROJECT
 
 WELCOME TO A LIFE STYLE FROM A BOAT!! Everyone has a van life story, but no one talks about a Boat life, so I wanted to start my own!

 Key Buildings

 1. WASD moves around in first person !
 2. F - switch to first person
 3. t- TURNS OFF AND ON TV
 4. l- TURNS OFF AND OFF LIGHT
 5. [] - up down light movement
 6. 0 key is to reset the angel !
 7. Esc to exit
 8. Right left up down arrow- move view
 9. P - projection mode switching

 
 */

#include "CSCIx229.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415927

int th = 150.0;      //  Azimuth of view angle
int ph = 30.0;      //  Elevation of view angle
int move = 1;       //  Move light
int light = 1;      // Lighting
double asp = 1;     // Aspect ratio
double dim = 1000.0; // Size of world
int m = 1; // projection

//LIGHT VALUES
int one = 1;       // Unit value
int distance = 1000;    // Light distance
int smooth = 1;        // Smooth/Flat shading
int local = 0;        // Local Viewer Model
int ambient = 30;    // Ambient intensity (%)
int diffuse = 100;  // Diffuse intensity (%)
int specular = 0;    // Specular intensity (%)
int zh = 90;        // Light azimuth
float ylight = 500;    // Elevation of light
int emission = 0;    // Emission intensity (%)
int shininess = 0;  // Shininess (power of two)
float shiny = 1;    // Shininess (value)
int inc = 10;

//LIGHTS, WALLS, FP
int mode = 0;
int fp = 0;            // First person
int tv_on = 0;        // Turn the tv on

unsigned int texture[22];  // Texture names
#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

// Rotation variable for first person
int rotation = 0.0;
// Eye coordinates
double Ex = 100.0;
double Ey = 50.0;
double Ez = 300.0;
// Camera coordinates
double Cx = 0.0;
double Cz = 0.0;


static void boat(){ //BASE OF MY WORLD
    
    //TEXTURES
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture[7]);
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    //TOP
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 0); glVertex3f(-600, 0, -600);
    glTexCoord2f(1, 0); glVertex3f(600, 0, -600);
    glTexCoord2f(1, 1); glVertex3f(600, 0, 600);
    glTexCoord2f(0, 1); glVertex3f(-600, 0, 600);
    //BOTTOM
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0, 0); glVertex3f(-600, -400, -600);
    glTexCoord2f(1, 0); glVertex3f(600, -400, -600);
    glTexCoord2f(1, 1); glVertex3f(600, -400, 600);
    glTexCoord2f(0, 1); glVertex3f(-600, -400, 600);
    glColor3f(1.0, 1.0, 1.0);
    //LEFT
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 0); glVertex3f(-600, -400, 600);
    glTexCoord2f(1, 0); glVertex3f(-600, 0, 600);
    glTexCoord2f(1, 1); glVertex3f(-600, 0, -600);
    glTexCoord2f(0, 1); glVertex3f(-600, -400, -600);
    //RIGHT
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 0); glVertex3f(600, -400, 600);
    glTexCoord2f(1, 0); glVertex3f(600, 0, 600);
    glTexCoord2f(1, 1); glVertex3f(600, 0, -600);
    glTexCoord2f(0, 1); glVertex3f(600, -400, -600);
    glColor3f(1.0, 1.0, 1.0);
    //FRONT
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0, 0); glVertex3f(-600, -400, 600);
    glTexCoord2f(1, 0); glVertex3f(600, -400, 600);
    glTexCoord2f(1, 1); glVertex3f(600, 0, 600);
    glTexCoord2f(0, 1); glVertex3f(-600, 0, 600);
    glColor3f(1.0, 1.0, 1.0);
    //BACK
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0, 0); glVertex3f(-600, -400, -600);
    glTexCoord2f(1, 0); glVertex3f(600, -400, -600);
    glTexCoord2f(1, 1); glVertex3f(600, 0, -600);
    glTexCoord2f(0, 1); glVertex3f(-600, 0, -600);
    glColor3f(1.0, 1.0, 1.0);
    glColor3f(1, 1, 1);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
}

static void water() { //floor from my boat!!
    
    //TEXTURES
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture[11]);
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    //USED TOP OF A CUBE TO MAKE MY WATER BASE
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 0); glVertex3f(-3000, -400, -3000);
    glTexCoord2f(1, 0); glVertex3f(3000, -400, -3000);
    glTexCoord2f(1, 1); glVertex3f(3000, -400, 3000);
    glTexCoord2f(0, 1); glVertex3f(-3000, -400, 3000);
    glColor3f(1, 1, 1);

    glEnd();
    glDisable(GL_TEXTURE_2D);
    
}

static void sky() { //MADE A BIGGER CUBE FOR MY WOLRD FOR THE SKY
    
    
    //Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture[4]);

    glBegin(GL_QUADS);
//BIG VERTEXXESSS
    glColor3f(1, 1, 1);
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 0); glVertex3f(-3000, -3000, -3000);
    glTexCoord2f(1, 0); glVertex3f(3000, -3000, -3000);
    glTexCoord2f(1, 1); glVertex3f(3000, -3000, 3000);
    glTexCoord2f(0, 1); glVertex3f(-3000, -3000, 3000);
    glColor3f(1, 1, 1);
    glNormal3f(0, -1, 0);
    glTexCoord2f(0, 0); glVertex3f(-3000, 3000, -3000);
    glTexCoord2f(1, 0); glVertex3f(3000, 3000, -3000);
    glTexCoord2f(1, 1); glVertex3f(3000, 3000, 3000);
    glTexCoord2f(0, 1); glVertex3f(-3000, 3000, 3000);
    glColor3f(1, 1, 1);
    glNormal3f(0, 0, -1);
    glTexCoord2f(0, 0); glVertex3f(-3000, -3000, 3000);
    glTexCoord2f(1, 0); glVertex3f(3000, -3000, 3000);
    glTexCoord2f(1, 1); glVertex3f(3000, 3000, 3000);
    glTexCoord2f(0, 1); glVertex3f(-3000, 3000, 3000);
    glColor3f(1, 1, 1);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(-3000, -3000, -3000);
    glTexCoord2f(1, 0); glVertex3f(3000, -3000, -3000);
    glTexCoord2f(1, 1); glVertex3f(3000, 3000, -3000);
    glTexCoord2f(0, 1); glVertex3f(-3000, 3000, -3000);
    glColor3f(1, 1, 1);
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(3000, 3000, 3000);
    glTexCoord2f(1, 0); glVertex3f(3000, -3000, 3000);
    glTexCoord2f(1, 1); glVertex3f(3000, -3000, -3000);
    glTexCoord2f(0, 1); glVertex3f(3000, 3000, -3000);
    glColor3f(1, 1, 1);
    glNormal3f(1, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(-3000, 3000, 3000);
    glTexCoord2f(1, 0); glVertex3f(-3000, -3000, 3000);
    glTexCoord2f(1, 1); glVertex3f(-3000, -3000, -3000);
    glTexCoord2f(0, 1); glVertex3f(-3000, 3000, -3000);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}


static void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
    //MY CUBRIODS USED
    float white[] = { 1,1,1,1 };
    float black[] = { 0,0,0,1 };
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
    
    glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
        glColor3f(1, 1, 1);
        glBindTexture(GL_TEXTURE_2D, texture[10]);
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Cube
   glBegin(GL_QUADS);
    //FRONT
    glColor3f(1,1,1);
    glNormal3f( 0, 0, 1);
    
    glTexCoord2f(0,0); glVertex3f(-50,-700, 50);
    glTexCoord2f(1,0); glVertex3f(+50,-700, 50);
    glTexCoord2f(1,1); glVertex3f(+50,+700, 50);
    glTexCoord2f(0,1); glVertex3f(-50,+700, 50);
   // BACK
    glColor3f(1,1,1);
    glNormal3f( 0, 0,-1);
        
    glTexCoord2f(0,0); glVertex3f(+50,-700,-50);
    glTexCoord2f(1,0); glVertex3f(-50,-700,-50);
    glTexCoord2f(1,1); glVertex3f(-50,+700,-50);
    glTexCoord2f(0,1); glVertex3f(+50,+700,-50);
   //  RIGHT
    glColor3f(1,1,1);
    glNormal3f(+1, 0, 0);
    
    glTexCoord2f(0,0); glVertex3f(+50,-700,+50);
    glTexCoord2f(1,0); glVertex3f(+50,-700,-50);
    glTexCoord2f(1,1); glVertex3f(+50,+700,-50);
    glTexCoord2f(0,1); glVertex3f(+50,+700,+50);
   //  LEFT
    glColor3f(1,1,1);
    glNormal3f(-1, 0, 0);
    
    glTexCoord2f(0,0); glVertex3f(-50,-700,-50);
    glTexCoord2f(1,0); glVertex3f(-50,-700,+50);
    glTexCoord2f(1,1); glVertex3f(-50,+700,+50);
    glTexCoord2f(0,1); glVertex3f(-50,+700,-50);
   // TOP
    glColor3f(1,1,1);
    glNormal3f( 0,+1, 0);
    glTexCoord2f(0,0); glVertex3f(-50,+700,+50);
    glTexCoord2f(1,0); glVertex3f(+50,+700,+50);
    glTexCoord2f(1,1); glVertex3f(+50,+700,-50);
    glTexCoord2f(0,1); glVertex3f(-50,+700,-50);
   //  BOTTOM
    glColor3f(1,1,1);
    glNormal3f( 0,-one, 0);
    glTexCoord2f(0,0); glVertex3f(-50,-700,-50);
    glTexCoord2f(1,0); glVertex3f(+50,-700,-50);
    glTexCoord2f(1,1); glVertex3f(+50,-700,+50);
    glTexCoord2f(0,1); glVertex3f(-50,-700,+50);
    glEnd();
    glPopMatrix();
}


static void bar(){ //THR BAR TO MY FLAG
    
    //TEXTURES
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture[7]);
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    //TOP
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 0); glVertex3f(-10, 0, -10);
    glTexCoord2f(1, 0); glVertex3f(10, 0, -10);
    glTexCoord2f(1, 1); glVertex3f(10, 0, 10);
    glTexCoord2f(0, 1); glVertex3f(-10, 0, 10);
    //BOTTOM
    glNormal3f(0, -1, 0);
    glTexCoord2f(0, 0); glVertex3f(-10, 700, -10);
    glTexCoord2f(1, 0); glVertex3f(10, 700, -10);
    glTexCoord2f(1, 1); glVertex3f(10, 700, 10);
    glTexCoord2f(0, 1); glVertex3f(-10, 700, 10);
    glColor3f(1, 1, 1);
    //LEFT
    glNormal3f(1, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(-10, 700, 10);
    glTexCoord2f(1, 0); glVertex3f(-10, 0, 10);
    glTexCoord2f(1, 1); glVertex3f(-10, 0, -10);
    glTexCoord2f(0, 1); glVertex3f(-10, 700, -10);
    //RIGHT
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(10, 700, 10);
    glTexCoord2f(1, 0); glVertex3f(10, 0, 10);
    glTexCoord2f(1, 1); glVertex3f(10, 0, -10);
    glTexCoord2f(0, 1); glVertex3f(10, 700, -10);
    glColor3f(1.0, 1.0, 1.0);
    //FRONT
    glNormal3f(0, 0, -1);
    glTexCoord2f(0, 0); glVertex3f(-10, 700, 10);
    glTexCoord2f(1, 0); glVertex3f(10, 700, 10);
    glTexCoord2f(1, 1); glVertex3f(10, 0, 10);
    glTexCoord2f(0, 1); glVertex3f(-10, 0, 10);
    glColor3f(1, 1, 1);
    //BACK
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(-10, 700, -10);
    glTexCoord2f(1, 0); glVertex3f(10, 700, -10);
    glTexCoord2f(1, 1); glVertex3f(10, 0, -10);
    glTexCoord2f(0, 1); glVertex3f(-10, 0, -10);
    glColor3f(1, 1, 1);
    glColor3f(1, 1, 1);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

// POINTS COORDINATES FOR MY OBJECTS.
static void func(double x, double y, double z) { //MY NORMALS,VERTEX THAT WOULD BE IN THE OBJECT FUNC
    
    glBegin(GL_QUADS);
    glNormal3d(0, 0, 1);
    glTexCoord2d(0, 0);
    glVertex3d(-x, y, z);
    glTexCoord2d(0, y * 2 / 100);
    glVertex3d(-x, -y, z);
    glTexCoord2d(x * 2 / 100, y * 2 / 100);
    glVertex3d(x, -y, z);
    glTexCoord2d(x * 2 / 100, 0);
    glVertex3d(x, y, z);
    glNormal3d(1, 0, 0);
    glTexCoord2d(0, 0);
    glVertex3d(x, y, z);
    glTexCoord2d(0, y * 2 / 100);
    glVertex3d(x, -y, z);
    glTexCoord2d(z * 2 / 100, y * 2 / 100);
    glVertex3d(x, -y, -z);
    glTexCoord2d(z * 2 / 100, 0);
    glVertex3d(x, y, -z);
    glNormal3d(0, 0, -1);
    glTexCoord2d(x * 2 / 100, 0);
    glVertex3d(x, y, -z);
    glTexCoord2d(x * 2 / 100, y * 2 / 100);
    glVertex3d(x, -y, -z);
    glTexCoord2d(0, y * 2 / 100);
    glVertex3d(-x, -y, -z);
    glTexCoord2d(0, 0);
    glVertex3d(-x, y, -z);
    glNormal3d(-1, 0, 0);
    glTexCoord2d(0, y * 2 / 100);
    glVertex3d(-x, y, -z);
    glTexCoord2d(0, 0);
    glVertex3d(-x, -y, -z);
    glTexCoord2d(z * 2 / 100, 0);
    glVertex3d(-x, -y, z);
    glTexCoord2d(z * 2 / 100, y * 2 / 100);
    glVertex3d(-x, y, z);
    glNormal3d(0, 1, 0);
    glTexCoord2d(0, 0);
    glVertex3d(-x, y, z);
    glTexCoord2d(x * 2 / 100, 0);
    glVertex3d(x, y, z);
    glTexCoord2d(x * 2 / 100, z * 2 / 100);
    glVertex3d(x, y, -z);
    glTexCoord2d(0, z * 2 / 100);
    glVertex3d(-x, y, -z);
    glNormal3d(0, -1, 0);
    glTexCoord2d(0, z * 2 / 100);
    glVertex3d(-x, -y, -z);
    glTexCoord2d(x * 2 / 100, z * 2 / 100);
    glVertex3d(x, -y, -z);
    glTexCoord2d(x * 2 / 100, 0);
    glVertex3d(x, -y, z);
    glTexCoord2d(0, 0);
    glVertex3d(-x, -y, z);
    glEnd();
}

static void func3(float x, float y, float z, float cant) {
    glBegin(GL_QUADS);

    glNormal3d(0, 0, 1);
    glTexCoord2f(cant, cant);
    glVertex3f(-1 * x, 0 * y, -1 * z);
    glTexCoord2f(0.0f, cant);
    glVertex3f(-1 * x, 0 * y, 1 * z);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1 * x, 0 * y, 1 * z);
    glTexCoord2f(cant, 0.0f);
    glVertex3f(1 * x, 0 * y, -1 * z);

    glEnd();
}

void func4(double h){
    GLUquadric *q = gluNewQuadric();
    gluQuadricTexture(q, GL_TRUE);
    glTranslated(0, -h, 0);
    glRotated(90, -1, 0, 0);
    gluCylinder(q, 5, 8, 2 * h, 20, 20);
    glRotated(-90, -1, 0, 0);
    glTranslated(0, h, 0);
    gluDeleteQuadric(q);
}


static void futon(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) { //THIS IS MY FUTON COUCH
    double h = 43;
    double l = 38;
    double c = 12;
    double a = 5;

    glTranslated(x, y, z);
    glRotated(th, rx, ry, rz);
    glScaled(dx, dy, dz);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);

    glColor3d(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture[8]);
    glTranslated(-l - 2, 0, 0);
    glTranslated(2 * l + 4, 0, 0);
    glTranslated(-l - 2, 0, 0);
    glRotated(a, -1, 0, 0);
    double m = 5.0;
    glTranslated(0, -1, -5);
    func(l, 2, h - m);
    glBindTexture(GL_TEXTURE_2D, texture[8]);
    glTranslated(0, c, 3);
    func(l - 1, c, h - m - 4);
    glBindTexture(GL_TEXTURE_2D, 0);
    glTranslated(0, -c, -3);
    glTranslated(0, h - m, -(h - m) + 2);
    glRotated(90, -1, 0, 0);
    glBindTexture(GL_TEXTURE_2D, texture[14]);
    func(l, 2, h - m);
    glBindTexture(GL_TEXTURE_2D, texture[8]);
    glTranslated(0, -c, 3);
    func(l - 1, c, h - m - 4);
    glBindTexture(GL_TEXTURE_2D, 0);

}

static void tvstand(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) { //TV STAND OBJECT
    
    glTranslated(x, y, z);
    glRotated(th, rx, ry, rz);
    glScaled(dx, dy, dz);
    glPushMatrix();
    glTranslated(0, -2.8, 0);
    func3(35, 0, 49, 1);
    glPopMatrix();
    
    // 4 LEGS
    glPushMatrix();
    glTranslated(28, 0, 42);
    glRotated(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.5, 2.1, 56, 20, 20);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(-20, 0, 42);
    glRotated(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.5, 2.1, 56, 20, 20);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(28, 0, -0.6 * 70);
    glRotated(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.5, 2.1, 56, 20, 20);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(-28, 0, -42);
    glRotated(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.5, 2.1, 56, 20, 20);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0, -28, 0);
    func3(31.5, 1.4, 45.5, 1);
    glPopMatrix();
}


//TV OBJECT
static void tv(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) { //TV WITH TEX
    
    float white[] = { 1,1,1,1 };
    float black[] = { 0,0,0,1 };
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

    glTranslated(x, y, z);
    glRotated(th, rx, ry, rz);
    glScaled(dx, dy, dz);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
    glColor3f(1, 1, 1);
    
    
    //ON AND OFF TEXTURE
    
    if (tv_on) {
        glBindTexture(GL_TEXTURE_2D, texture[2]); //TURNING ON AND OFF THE TV
    }
    else {
        glBindTexture(GL_TEXTURE_2D, texture[5]);
    }
    

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    
    
    glTexCoord2f(0, 0); glVertex3f(-52, 6, -57);
    glTexCoord2f(1, 0); glVertex3f(52, 6, -57);
    glTexCoord2f(1, 1); glVertex3f(52, 100, -57);
    glTexCoord2f(0, 1); glVertex3f(-52, 100, -57);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
    glColor3f(1, 1, 1);
    
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(-52, 6, -52);
    glTexCoord2f(1, 0); glVertex3f(52, 6, -52);
    glTexCoord2f(1, 1); glVertex3f(52, 100, -52);
    glTexCoord2f(0, 1); glVertex3f(-52, 100, -52);
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(-52, 6, -57);
    glTexCoord2f(1, 0); glVertex3f(-52, 100, -57);
    glTexCoord2f(1, 1); glVertex3f(-52, 100, -52);
    glTexCoord2f(0, 1); glVertex3f(-52, 6, -52);
    glNormal3f(1, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(52, 6, -57);
    glTexCoord2f(1, 0); glVertex3f(52, 100, -57);
    glTexCoord2f(1, 1); glVertex3f(52, 100, -52);
    glTexCoord2f(0, 1); glVertex3f(52, 6, -52);
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 0); glVertex3f(-52, 100, -57);
    glTexCoord2f(1, 0); glVertex3f(-52, 100, -52);
    glTexCoord2f(1, 1); glVertex3f(52, 100, -52);
    glTexCoord2f(0, 1); glVertex3f(52, 100, -57);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

static void translate(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) { //ANOTHER HELPER FUNCTION
    // Translations
    glTranslated(x, y, z);
    glRotated(th, rx, ry, rz);
    glScaled(dx, dy, dz);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
    glColor3f(1, 1, 1);
    glColor3d(1, 1, 1);
    glPushMatrix();
    glTranslated(-41, 0, -91);
    glPopMatrix();
    glPushMatrix();
    glTranslated(41, 0, -91);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-41, 0, 91);
    glPopMatrix();
    glPushMatrix();
    glTranslated(41, 0, 91);
    glPopMatrix();
    glTranslated(0, 30, 0);
    glColor3d(1, 1, 1);
    glDisable(GL_TEXTURE_2D);

}

//BED OBJECT
static void bed(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) {

    // Translations
    glTranslated(x, y, z);
    glRotated(th, rx, ry, rz);
    glScaled(dx, dy, dz);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glColor3d(1, 1, 1);
    double h = 15;
    glPushMatrix();
    glTranslated(-40, 0, -90);
    func4(h);
    glPopMatrix();
    glPushMatrix();
    glTranslated(40, 0, -90);
    func4(h);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-40, 0, 90);
    func4(h);
    glPopMatrix();
    glPushMatrix();
    glTranslated(40, 0, 90);
    func4(h);
    glPopMatrix();
    glTranslated(0, h, 0);
    glColor3d(1, 1, 1);
    func(50, h / 10, 100);
    glDisable(GL_TEXTURE_2D);
}

//BLANKET OBJECT
static void blanket(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) {
    //  Set specular color to white
    float white[] = { 1,1,1,1 };
    float black[] = { 0,0,0,1 };
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

    glTranslated(x, y, z);
    glRotated(th, rx, ry, rz);
    glScaled(dx, dy, dz);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture[12]);

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);

    int l = 20;int d = 20;int w = 30;int z1 = 35;int z2 = 60;
    
    glNormal3f(0, 0, -1);
    glTexCoord2f(0, 0); glVertex3f(-l, d, -z2);
    glTexCoord2f(5, 0); glVertex3f(l, d, -z2);
    glTexCoord2f(5, 1); glVertex3f(l, w, -z2);
    glTexCoord2f(0, 1); glVertex3f(-l, w, -z2);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(-l, d, -z1);
    glTexCoord2f(5, 0); glVertex3f(l, d, -z1);
    glTexCoord2f(5, 1); glVertex3f(l, w, -z1);
    glTexCoord2f(0, 1); glVertex3f(-l, w, -z1);
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(-l, d, -z2);
    glTexCoord2f(1, 0); glVertex3f(-l, w, -z2);
    glTexCoord2f(1, 1); glVertex3f(-l, w, -z1);
    glTexCoord2f(0, 1); glVertex3f(-l, d, -z1);
    glNormal3f(1, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(l, d, -z2);
    glTexCoord2f(1, 0); glVertex3f(l, w, -z2);
    glTexCoord2f(1, 1); glVertex3f(l, w, -z1);
    glTexCoord2f(0, 1); glVertex3f(l, d, -z1);
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 0); glVertex3f(-l, w, -z2);
    glTexCoord2f(1, 0); glVertex3f(-l, w, -z1);
    glTexCoord2f(1, 1); glVertex3f(l, w, -z1);
    glTexCoord2f(0, 1); glVertex3f(l, w, -z2);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

//PILLOW OBJECT
static void pillow(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) {
    //  Set specular color to white
    float white[] = { 1,1,1,1 };
    float black[] = { 0,0,0,1 };
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

    glTranslated(x, y, z);
    glRotated(th, rx, ry, rz);
    glScaled(dx, dy, dz);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);

    int l = 20;int d = 20;int w = 30;int z1 = 35;int z2 = 60;
    
    glNormal3f(0, 0, -1);
    glTexCoord2f(0, 0); glVertex3f(-l, d, -z2);
    glTexCoord2f(5, 0); glVertex3f(l, d, -z2);
    glTexCoord2f(5, 1); glVertex3f(l, w, -z2);
    glTexCoord2f(0, 1); glVertex3f(-l, w, -z2);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(-l, d, -z1);
    glTexCoord2f(5, 0); glVertex3f(l, d, -z1);
    glTexCoord2f(5, 1); glVertex3f(l, w, -z1);
    glTexCoord2f(0, 1); glVertex3f(-l, w, -z1);
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(-l, d, -z2);
    glTexCoord2f(1, 0); glVertex3f(-l, w, -z2);
    glTexCoord2f(1, 1); glVertex3f(-l, w, -z1);
    glTexCoord2f(0, 1); glVertex3f(-l, d, -z1);
    glNormal3f(1, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(l, d, -z2);
    glTexCoord2f(1, 0); glVertex3f(l, w, -z2);
    glTexCoord2f(1, 1); glVertex3f(l, w, -z1);
    glTexCoord2f(0, 1); glVertex3f(l, d, -z1);
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 0); glVertex3f(-l, w, -z2);
    glTexCoord2f(1, 0); glVertex3f(-l, w, -z1);
    glTexCoord2f(1, 1); glVertex3f(l, w, -z1);
    glTexCoord2f(0, 1); glVertex3f(l, w, -z2);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

//My objects got off center so this is just another help function to center it again
static void center(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) {
    
    glTranslated(x, y, z);
    glRotated(th, rx, ry, rz);
    glScaled(dx, dy, dz);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
    glColor3d(1, 1, 1);
    glTranslated(-27, 0, 0);
    glTranslated(54, 0, 0);
    glTranslated(-27, 0, 0);
    glRotated(5, -1, 0, 0);
    glTranslated(0, -1,0);
    glTranslated(0, 10, 3);
    glBindTexture(GL_TEXTURE_2D, 0);
    glTranslated(0, -10, -3);
    glTranslated(0, 27, -25);
    glRotated(90, -1, 0, 0);
    glTranslated(0, -10, 3);
    glBindTexture(GL_TEXTURE_2D, 0);

}


static void yeti(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
    
    //  Set specular color to white
    float white[] = { 1,1,1,1 };
    float black[] = { 0,0,0,1 };
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
    
    glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
        glColor3f(1, 1, 1);
        glBindTexture(GL_TEXTURE_2D, texture[5]);
   glPushMatrix();
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   glBegin(GL_QUADS);
    //FRONT
    glColor3f(1,1,1);
    glNormal3f( 0, 0, 1);
    glTexCoord2f(0,0); glVertex3f(-50,-700, 50);
    glTexCoord2f(1,0); glVertex3f(+50,-700, 50);
    glTexCoord2f(1,1); glVertex3f(+50,+700, 50);
    glTexCoord2f(0,1); glVertex3f(-50,+700, 50);
   // BACK
    glColor3f(1,1,1);
    glNormal3f( 0, 0,-1);
        
    glTexCoord2f(0,0); glVertex3f(+50,-700,-50);
    glTexCoord2f(1,0); glVertex3f(-50,-700,-50);
    glTexCoord2f(1,1); glVertex3f(-50,+700,-50);
    glTexCoord2f(0,1); glVertex3f(+50,+700,-50);
   //  RIGHT
    glColor3f(1,1,1);
    glNormal3f(+1, 0, 0);
    glTexCoord2f(0,0); glVertex3f(+50,-700,+50);
    glTexCoord2f(1,0); glVertex3f(+50,-700,-50);
    glTexCoord2f(1,1); glVertex3f(+50,+700,-50);
    glTexCoord2f(0,1); glVertex3f(+50,+700,+50);
   //  LEFT
    glColor3f(1,1,1);
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0,0); glVertex3f(-50,-700,-50);
    glTexCoord2f(1,0); glVertex3f(-50,-700,+50);
    glTexCoord2f(1,1); glVertex3f(-50,+700,+50);
    glTexCoord2f(0,1); glVertex3f(-50,+700,-50);
   // TOP
    glColor3f(1,1,1);
    glNormal3f( 0,+1, 0);
    glTexCoord2f(0,0); glVertex3f(-50,+700,+50);
    glTexCoord2f(1,0); glVertex3f(+50,+700,+50);
    glTexCoord2f(1,1); glVertex3f(+50,+700,-50);
    glTexCoord2f(0,1); glVertex3f(-50,+700,-50);
   //  BOTTOM
    glColor3f(1,1,1);
    glNormal3f( 0,-one, 0);
    glTexCoord2f(0,0); glVertex3f(-50,-700,-50);
    glTexCoord2f(1,0); glVertex3f(+50,-700,-50);
    glTexCoord2f(1,1); glVertex3f(+50,-700,+50);
    glTexCoord2f(0,1); glVertex3f(-50,-700,+50);
    glEnd();
    glPopMatrix();
}


static void matt(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
    //  Set specular color to white
    float white[] = { 1,1,1,1 };
    float black[] = { 0,0,0,1 };
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
    
    glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
        glColor3f(1, 1, 1);
        glBindTexture(GL_TEXTURE_2D, texture[15]);

   glPushMatrix();
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glNormal3f( 0,+1, 0);
    glTexCoord2f(0,0); glVertex3f(-50,+700,+50);
    glTexCoord2f(1,0); glVertex3f(+50,+700,+50);
    glTexCoord2f(1,1); glVertex3f(+50,+700,-50);
    glTexCoord2f(0,1); glVertex3f(-50,+700,-50);
    glEnd();
    glPopMatrix();
}

static void oldmatt(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
    //  Set specular color to white
    float white[] = { 1,1,1,1 };
    float black[] = { 0,0,0,1 };
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
    
    glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
        glColor3f(1, 1, 1);
        glBindTexture(GL_TEXTURE_2D, texture[20]);

   glPushMatrix();
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glNormal3f( 0,+1, 0);
    glTexCoord2f(0,0); glVertex3f(-50,+700,+50);
    glTexCoord2f(1,0); glVertex3f(+50,+700,+50);
    glTexCoord2f(1,1); glVertex3f(+50,+700,-50);
    glTexCoord2f(0,1); glVertex3f(-50,+700,-50);
    glEnd();
    glPopMatrix();
}


static void Vertex(double th, double ph)
{ //Used vertex ex13 as reference in class!
    double x = Sin(th)*Cos(ph);
    double y = Cos(th)*Cos(ph);
    double z = Sin(ph);
    glNormal3d(x, y, z);
    glVertex3d(x, y, z);
}

//BALL FROM CLASS
static void ball(double x,double y,double z,double r)
{

   glPushMatrix();
   
   glTranslated(x,y,z);
   glScaled(r,r,r);
   float yellow[]   = {1.0,1.0,0.0,1.0};
   float Emission[] = {0.0,0.0,0.01*emission,1.0};
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (int ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   glPopMatrix();
}


static void bear(double x,double y,double z,double r)
{ //SPHERE WITH TEXTURE

    glPushMatrix();

    glTranslated(x,y,z);
    glScaled(r,r,r);
    glRotatef(90,1,0,0);
    glBindTexture(GL_TEXTURE_2D, texture[18]);
    //CREATING MY NEW QUAD
    GLUquadric *quadric= gluNewQuadric();
    gluQuadricDrawStyle(quadric,GLU_FILL);
    gluQuadricNormals(quadric,GLU_SMOOTH);
    gluQuadricTexture(quadric, GL_TRUE);
    //NORMAL AND TEXTURES
    gluSphere(quadric,1,10,10);
    gluDeleteQuadric(quadric);
    glPopMatrix();
    
}


static void bounty(double x,double y,double z,double r)
{ //SAME FROM BEAR SPHERE

    glPushMatrix();

    glTranslated(x,y,z);
    glScaled(r,r,r);
    glRotatef(90,1,0,0);
    glBindTexture(GL_TEXTURE_2D, texture[19]);
    GLUquadric *quadric= gluNewQuadric();
    gluQuadricDrawStyle(quadric,GLU_FILL);
    gluQuadricNormals(quadric,GLU_SMOOTH);
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric,1,10,10);
    gluDeleteQuadric(quadric);
    glPopMatrix();
    
}

//REFERENCEE!!!
// I USED http://www.songho.ca/opengl/gl_cylinder.html AS REFERENCE FOR MY CYNLINDER!!!!
void logs(double x,double y,double z,double dx, double dy, double dz, double th, int ty , int tz , int mx, int my, int mz){ //CYLINDERRR
    
    double r = 0.3;
    int h = 1;
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(dx,dy,dz);
    //TEXTURES ENABLE
    if (ty==1){
       glRotated(th,0,0,1);
       glRotated(th,1,0,0);
       }
       else{
         glRotated(th,0,0,1);
       }
    
       if(mx==1){
           glEnable(GL_TEXTURE_2D);
           glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
           glBindTexture(GL_TEXTURE_2D,texture[2]); // I was going to use another texture with
           //another cylinder but decided to srick with a wood theme 
       }
       else{
           glEnable(GL_TEXTURE_2D);
           glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
           glBindTexture(GL_TEXTURE_2D,texture[17]);
        }

    double i;
    //GLTEXTURE
    //TOP OF MY CYLINDER
      glColor3f(1,1,1);
      glNormal3d(0,1,0);
      glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5,0.5);
      glVertex3d(0.0, h, 0.0);
        
    for(i = 0 ; i <= tz; i+= 10) {
    glTexCoord2f(0.5 * Cos(i)+0.6, -0.5 * Sin(i)+0.5);
        if(my != 0){
            glVertex3d(r * Cos(i-40), h, r * Sin(i-40));
        }
        
        else{glVertex3d(r * Cos(i), h, r * Sin(i));
        }
     }
  glEnd();
    
  if(mx==1){
    glDisable(GL_TEXTURE_2D);
    glNormal3d(0,-1,0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3d(0,-h, 0);
      
    for(i = 0; i <= tz; i+=10) {
        glVertex3d(r * Cos(i), -h, r * Sin(i));
    }
    glEnd();
    double j;
    glBegin(GL_QUAD_STRIP);
    for (j = 0; j <= tz; j+=.125) {
      double x = r * Cos(j);
      double y = h;
      double z = r * Sin(j);

      glNormal3d(Cos(j), 0, Sin(j));
      glVertex3d(x, y, z);
    }
    glEnd();
}
    //BOTTOM OF MY CYNLINDER
  else{
    glColor3f(1,1,1);
    glNormal3d(0,-1,0);
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5,0.5);
    glVertex3d(0.0, -h, 0.0);
    for(i = 0.0; i <= tz; i+=10) {
    glTexCoord2f(0.5*Cos(i)+0.5, 0.5*Sin(i)+0.5);
    glVertex3d(r * Cos(i), -h, r * Sin(i));
    }
      
    glEnd();
    double j;
    glBegin(GL_QUAD_STRIP);
    for (j = 0; j <= tz; j+=.125) {
      const float tc = (j / (float) 360);
      double x = r * Cos(j);
      double y = h;
      double z = r * Sin(j);
      glColor3f(1,1,1);
        
      glNormal3d(Cos(j), 0, Sin(j));
      glTexCoord2f(-tc, 0.0); glVertex3d(x, -y, z);
      glTexCoord2f(-tc, 1.0); glVertex3d(x, y, z);
    }
    glEnd();
  }
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}


//REUSED CODE FROM MY OLD HOMEWORK
static void flag(double x,double y,double z,double dx,double dy,double dz, double th)
{
    
    float white[] = { 1,1,1,1 };
    float black[] = { 0,0,0,1 };
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture[13]);

   //  Save transformation
    glPushMatrix();
    glRotated(th,0,1,0);
    glRotated(0,1,0,0);
    glTranslated(x,y,z);
    glScaled(dx,dy,dz);
    glBegin(GL_POLYGON);
    glTexCoord2f(0,0); glVertex3f(-600,-400, 600);
    glTexCoord2f(1,0);glVertex3f(+600,-400, 600);
    glTexCoord2f(1,1);glVertex3f(+600,+400, 600);
    glEnd();
   glPopMatrix();
}

//DISPLAY
void display()
{
    
    //REUSED FROM HW 5
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
   
    if (fp) {
        Cx = +2 * dim*Sin(rotation);
        Cz = -2 * dim*Cos(rotation);
        gluLookAt(Ex, Ey, Ez, Cx + Ex, Ey, Cz + Ez, 0, 1, 0);
    }
    else {
        if (m) {
            double Ex = -2 * dim*Sin(th)*Cos(ph);
            double Ey = +2 * dim        *Sin(ph);
            double Ez = +2 * dim*Cos(th)*Cos(ph);
            gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, Cos(ph), 0);
        }
        else {
            glRotatef(ph, 1, 0, 0);
            glRotatef(th, 0, 1, 0);
        }
    }
    glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

    if (light)
    {
        float Ambient[] = { 0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0 };
        float Diffuse[] = { 0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0 };
        float Specular[] = { 0.01*specular,0.01*specular,0.01*specular,1.0 };

        float Position[] = { distance*Cos(zh),ylight,distance*Sin(zh),1.0 };
        glColor3f(1, 1, 1);
        ball(Position[0], Position[1], Position[2], 10);
        glEnable(GL_NORMALIZE);
        glEnable(GL_LIGHTING);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
        glLightfv(GL_LIGHT0, GL_POSITION, Position);
    }
    else
        glDisable(GL_LIGHTING);

    boat();
    water();
    flag(-190,530,0,.3,.4,0,180);
    cube(525,35,375,.9,.07,2,0);
    yeti(525,80,375,1,.02,2.1,0);
    matt(-320,-48,300, 5,.07,5,0);
    
    oldmatt(-380,-48,-450, 2,.07,2,0);
    
    bear(200.0,50.0,500.0,50);
    bear(200.0,130.0,500.0,40);
    bear(240.0,160.0,500.0,20);
    bear(160,160.0,500.0,20);
    bear(165,25,530.0,20);//left leg
    bear(170,80,520,20); //left arm
    bear(230,80,530,20); //right arm
    bear(230,25,530,20);
    
    
    bounty(1600,-380,1500.0,50);
    bounty(1400,-380,1500.0,50);
    bounty(1200,-380,1500.0,50);
    bounty(1000,-380,1500.0,50);
    bounty(800,-380,1500.0,50);
    bounty(600,-380,1500.0,50);
    bounty(400,-380,1500.0,50);
    bounty(200,-380,1500.0,50);
    bounty(0,-380,1500.0,50);
    bounty(-200,-380,1500.0,50);
    bounty(-400,-380,1500.0,50);
    bounty(-600,-380,1500.0,50);
    bounty(-800,-380,1500.0,50);
    bounty(-1000,-380,1500.0,50);
    
    
    bounty(1600,-380,-1300.0,50);
    bounty(1400,-380,-1300.0,50);
    bounty(1200,-380,-1300.0,50);
    bounty(1000,-380,-1300.0,50);
    bounty(800,-380,-1300.0,50);
    bounty(600,-380,-1300.0,50);
    bounty(400,-380,-1300.0,50);
    bounty(200,-380,-1300.0,50);
    bounty(0,-380,-1300.0,50);
    bounty(-200,-380,-1300.0,50);
    bounty(-400,-380,-1300.0,50);
    bounty(-600,-380,-1300.0,50);
    bounty(-800,-380,-1300.0,50);
    bounty(-1000,-380,-1300.0,50);
    //PERIMETER
    logs(550,50,100,55,55,55,0,0,1000,0,0,2);
    logs(550,50,150,55,55,55,0,0,1000,0,0,2);
    logs(550,50,200,55,55,55,0,0,1000,0,0,2);
    logs(550,50,250,55,55,55,0,0,1000,0,0,2);
    logs(550,50,50,55,55,55,0,0,1000,0,0,2);
    logs(550,50,0,55,55,55,0,0,1000,0,0,2);
    logs(550,50,-50,55,55,55,0,0,1000,0,0,2);
    logs(550,50,-100,55,55,55,0,0,1000,0,0,2);
    logs(550,50,-150,55,55,55,0,0,1000,0,0,2);
    logs(550,50,-200,55,55,55,0,0,1000,0,0,2);
    logs(550,50,-250,55,55,55,0,0,1000,0,0,2);
    logs(550,50,-300,55,55,55,0,0,1000,0,0,2);
    logs(550,50,-350,55,55,55,0,0,1000,0,0,2);
    logs(550,50,-400,55,55,55,0,0,1000,0,0,2);
    logs(550,50,-450,55,55,55,0,0,1000,0,0,2);
    logs(550,50,-500,55,55,55,0,0,1000,0,0,2);
    logs(550,50,-550,55,55,55,0,0,1000,0,0,2);
    logs(-550,50,-50,55,55,55,0,0,1000,0,0,2);
    logs(-550,50,100,55,55,55,0,0,1000,0,0,2);
    logs(-550,50,150,55,55,55,0,0,1000,0,0,2);
    logs(-550,50,200,55,55,55,0,0,1000,0,0,2);
    logs(-550,50,250,55,55,55,0,0,1000,0,0,2);
    logs(-550,50,50,55,55,55,0,0,1000,0,0,2);
    logs(-550,50,0,55,55,55,0,0,1000,0,0,2);
    logs(-550,50,-100,55,55,55,0,0,1000,0,0,2);
    logs(-550,50,-150,55,55,55,0,0,1000,0,0,2);
    logs(-550,50,-200,55,55,55,0,0,1000,0,0,2);
    logs(-550,50,-250,55,55,55,0,0,1000,0,0,2);
    logs(-550,50,-300,55,55,55,0,0,1000,0,0,2);
    logs(-550,50,-350,55,55,55,0,0,1000,0,0,2);
    logs(-550,50,-400,55,55,55,0,0,1000,0,0,2);
    logs(-550,50,-450,55,55,55,0,0,1000,0,0,2);
    logs(-550,50,-500,55,55,55,0,0,1000,0,0,2);
    logs(-550,50,-550,55,55,55,0,0,1000,0,0,2);
    
    logs(-200,50,-570,55,55,55,0,0,1000,0,0,2);
    logs(-150,50,-570,55,55,55,0,0,1000,0,0,2);
    logs(-100,50,-570,55,55,55,0,0,1000,0,0,2);
    logs(-50,50,-570,55,55,55,0,0,1000,0,0,2);
    logs(0,50,-570,55,55,55,0,0,1000,0,0,2);
    logs(50,50,-570,55,55,55,0,0,1000,0,0,2);
    logs(100,50,-570,55,55,55,0,0,1000,0,0,2);
    logs(150,50,-570,55,55,55,0,0,1000,0,0,2);
    logs(200,50,-570,55,55,55,0,0,1000,0,0,2);
    logs(250,50,-570,55,55,55,0,0,1000,0,0,2);
    logs(300,50,-570,55,55,55,0,0,1000,0,0,2);
    logs(350,50,-570,55,55,55,0,0,1000,0,0,2);
    logs(400,50,-570,55,55,55,0,0,1000,0,0,2);
    logs(450,50,-570,55,55,55,0,0,1000,0,0,2);
    logs(500,50,-570,55,55,55,0,0,1000,0,0,2);
    // PERIMETER
    
    
    logs(-300,18,-570,55,55,55,-90,0,1000,0,0,2);
    logs(-450,18,-570,55,55,55,-90,0,1000,0,0,2);
    logs(-300,50,-570,55,55,55,-90,0,1000,0,0,2);
    logs(-450,50,-570,55,55,55,-90,0,1000,0,0,2);
    logs(-325,80,-570,55,55,55,-90,0,1000,0,0,2);
    logs(-425,80,-570,55,55,55,-90,0,1000,0,0,2);
    logs(-380,110,-570,55,55,55,-90,0,1000,0,0,2);
    
    //(<bear>,^vup,top bear,flat or thick,
    sky();
    bar();
    futon(-340, -3, 100, 3, 1, 1, 0, 0, 0, 0);
    center(80, -20, -27.5, 0.5, 1, 1, 95, 1, 0, 0);
    tvstand(-150, -300, -35, 2, 1, 0.75, 95, 1, 0, 0);
    tv(0, -3.5, 40, 0.75 , 1, 0.75, 0, 0, 0, 0);
    translate(135, -18, -580, 0.4, 1, 0.5, 0, 0, 0, 0);
    bed(-370, -35, 550, 1.5, 1.4, 1.5, 0, 0, 0, 0);
    bed(470, 0, -1500, 3, 1.7, 2.5, 0, 0, 0, 0);
    blanket(1, -13, 375, 2.3, .7, 8, 0, 0, 0, 0);
    pillow(14, 10, 0, .25, 1, 1, 0, 0, 0, 0);
    
    
    ErrCheck("display");
    glFlush();
    glutSwapBuffers();
}


void idle()
{
    double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    zh = fmod(90 * t, 360.0);
    glutPostRedisplay();
}


void special(int key, int x, int y)
{
    if (!fp) {
        if (key == GLUT_KEY_RIGHT)
            th += 5;
        else if (key == GLUT_KEY_LEFT)
            th -= 5;
        else if (key == GLUT_KEY_UP)
            ph += 5;
        else if (key == GLUT_KEY_DOWN)
            ph -= 5;
        else if (key == GLUT_KEY_PAGE_DOWN)
            dim += 5;
        else if (key == GLUT_KEY_PAGE_UP && dim > 1)
            dim -= 5;
        th %= 360;
        ph %= 360;
    }
    //  Update projection
    Project(45, asp, dim, fp, m);
    glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch, int x, int y)
{
    //  Exit on ESC
    if (ch == 27)
        exit(0);
    //  Toggle first person
    else if (ch == 'f') {
        fp = 1 - fp;
    }
    else if (ch == 't') //TUYRN ON AND OFF TV
        tv_on = 1 - tv_on;
    else if (ch == 'l') //LIGHT TURN ON AND OFF
        light = 1 - light;
    //else if (ch == 'o') //TURN ON AND OFF WALLS
        //wall = 1 - wall;
    else if (ch == 'm') //MOVE LIGHT
        move = 1 - move;
    else if (ch == '[') //MOVE UP DOEN LIGHT
        ylight -= 10;
    else if (ch == ']')
        ylight += 10;
    
    if (fp) { //WASD MOVING LIKE ANY ONLINE GAMES
        double dt = 0.05;
        if (ch == 'w') {
            Ex += Cx * dt;
            Ez += Cz * dt;
        }
        else if (ch == 'a') {
            rotation -= 3;
        }
        else if (ch == 's') {
            Ex -= Cx * dt;
            Ez -= Cz * dt;
        }
        else if (ch == 'd') {
            rotation += 3;
        }
        rotation %= 360;
    }
    else {
        if (ch == '0')
            th = ph = 45;
        //Switch display mode
        else if (ch == 'p')
            m = 1 - m;
    }

    shiny = shininess < 0 ? 0 : pow(2.0, shininess);
    Project(45, asp, dim, fp, m);
    glutIdleFunc(move ? idle : NULL);
    glutPostRedisplay();
}

/*
 * This function is called by GLUT when the window is resized
 */
void reshape(int width, int height)
{
    asp = (height > 0) ? (double)width / height : 1;
    glViewport(0, 0, width, height);
    Project(45, asp, dim, fp, m);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc, char* argv[])
{

    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("On A Boat: Eliza Mimi To");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    texture[0] = LoadTexBMP("pillow.bmp");
    texture[1] = LoadTexBMP("tv.bmp");
    texture[2] = LoadTexBMP("icarly.bmp");
    texture[3] = LoadTexBMP("table.bmp");
    texture[4] = LoadTexBMP("sky.bmp");
    texture[5] = LoadTexBMP("tv_screen.bmp");
    texture[7] = LoadTexBMP("floor.bmp");
    texture[8] = LoadTexBMP("futon.bmp");
    texture[9] = LoadTexBMP("otherfloor.bmp");
    texture[10] = LoadTexBMP("yeti.bmp");
    texture[11] = LoadTexBMP("water.bmp");
    texture[12] = LoadTexBMP("blanket.bmp");
    texture[13] = LoadTexBMP("flag.bmp");
    texture[14] = LoadTexBMP("grey.bmp");
    texture[15] = LoadTexBMP("matt.bmp");
    texture[16] = LoadTexBMP("bear.bmp");
    texture[17] = LoadTexBMP("planks.bmp");
    texture[18] = LoadTexBMP("lv.bmp");
    texture[19] = LoadTexBMP("red.bmp");
    texture[20] = LoadTexBMP("oldwood.bmp");

    ErrCheck("init");
    glutMainLoop();
    return 0;
}

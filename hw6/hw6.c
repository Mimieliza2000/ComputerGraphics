/*
 * Eliza Mimi To Homework6 Texture and lighting
 
 OBHECTS FROM PREVIOUS HOEMWORK
 ex15 HELPED A LOT WITH MOST OF THIS
 */
#include "CSCIx229.h"

/*
 
 
 1. 'WASD' keys To move in first person!
 
 */

int th = 50.0;      //  Azimuth of view angle
int ph = 50.0;      //  Elevation of view angle
//int mode = 1;       //  Projection mode
int move = 1;       //  Move light
int fov = 55;       //  Field of view (for perspective)
int light = 1;      //  Lighting
double asp = 1;     //  Aspect ratio
double dim = 3.0;//  Size of world


//LIGHT VALUES
int one = 1;        // Unit value
int distance = 5;    // Light distance
int smooth = 1;        // Smooth/Flat shading
int local = 0;        // Local Viewer Model
int ambient = 30;    // Ambient intensity (%)
int diffuse = 100;  // Diffuse intensity (%)
int specular = 0;    // Specular intensity (%)
int zh = 90;        // Light azimuth
float ylight = 0;    // Elevation of light
int emission = 0;    // Emission intensity (%)
int shininess = 0;  // Shininess (power of two)
float shiny = 1;    // Shininess (value)
int inc = 10;
//Texture values
int mode = 0;    //  Texture mode
unsigned int texture[2];  //  Texture names


//Start of my boat
static void triangle(double x,double y,double z,double dx,double dy,double dz, double th)
{
    
    //  Set specular color to white
    float white[] = { 1,1,1,1 };
    float black[] = { 0,0,0,1 };
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
        
    
    //Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    
   //  Save transformation
    glPushMatrix();
    glRotated(th,0,1,0);
    glRotated(180,1,0,0);
    glTranslated(x,y,z);
    glScaled(dx,dy,dz);
    

    //Front red
    glBegin(GL_POLYGON);
    glNormal3f( 0, 0, 1);
    glColor3f(1,1,1);
    
    glTexCoord2f(0, 0); glVertex3f(-1,-1, 1);
    glTexCoord2f(1, 0);glVertex3f(+1,-1, 1);
    glTexCoord2f(1, 1);glVertex3f(+1,+1, 1);
    
    glEnd();
    
    //Back
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    glNormal3f( 0, 0,-1);
    
    
    glTexCoord2f(0, 0);glVertex3f(-1,-1, -1);
    glTexCoord2f(1, 0);glVertex3f(+1,-1, -1);
    glTexCoord2f(1, 1);glVertex3f(+1,+1, -1);
    
    glEnd();
    
    
    //Square Side
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    
    
    glTexCoord2f(0,0);glVertex3f(1,-1, -1);
    glTexCoord2f(1,0);glVertex3f(1,-1, 1);
    glTexCoord2f(1,1);glVertex3f(1,1, 1);
    glTexCoord2f(0,1);glVertex3f(1,1, -1);
    
    glEnd();
    
    //Hypo
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
    
    glTexCoord2f(0,0);glVertex3f(1,1, 1);
    glTexCoord2f(1,0);glVertex3f(1,1, -1);
    glTexCoord2f(1,1);glVertex3f(-1,-1, -1);
    glTexCoord2f(0,1);glVertex3f(-1,-1, 1);
    
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
    
    //  Set specular color to white
        float white[] = { 1,1,1,1 };
        float black[] = { 0,0,0,1 };
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
    
    glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
        glColor3f(1, 1, 1);
        glBindTexture(GL_TEXTURE_2D, texture[0]);

    
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
    glNormal3f( 0, 0, 1);
    
    glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
    glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
    glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
    glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
   //  Back
    glColor3f(1,1,1);
    glNormal3f( 0, 0,-1);
    
    glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
   //  Right
    glColor3f(1,1,1);
    glNormal3f(+1, 0, 0);
    
    glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
   //  Left
    glColor3f(1,1,1);
    glNormal3f(-1, 0, 0);
    
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   //  Top
    glColor3f(1,1,1);
    glNormal3f( 0,+1, 0);
    glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   //  Bottom
    glColor3f(1,1,1);
    glNormal3f( 0,-one, 0);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
    glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
   //  End
    glEnd();
   //  Undo transformations
    //glDisable(GL_LIGHTING);
    glPopMatrix();
}



static void containers(double x,double y,double z,
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
        glBindTexture(GL_TEXTURE_2D, texture[1]);

    
    
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
   glNormal3f( 0, 0, 1);
    
    glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
    glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
    glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
    glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
   //  Back
   glColor3f(1,1,1);
    glNormal3f( 0, 0,-1);
    
    glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
   //  Right
   glColor3f(1,1,1);
    glNormal3f(+1, 0, 0);
    
    glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
   //  Left
   glColor3f(1,1,1);
    glNormal3f(-1, 0, 0);
    
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   //  Top
   glColor3f(1,1,1);
    glNormal3f( 0,+1, 0);
    glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   //  Bottom
   glColor3f(1,1,1);
    glNormal3f( 0,-one, 0);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
    glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
   //  End
   glEnd();
   //  Undo transformations
   glPopMatrix();
}

static void stick(double x,double y,double z,
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
        glBindTexture(GL_TEXTURE_2D, texture[1]);

    
    
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
    glNormal3f( 0, 0, 1);
    
    glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
    glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
    glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
    glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
   //  Back
    glColor3f(1,1,1);
    glNormal3f( 0, 0,-1);
    
    glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
   //  Right
    glColor3f(1,1,1);
    glNormal3f(+1, 0, 0);
    
    glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
   //  Left
    glColor3f(1,1,1);
    glNormal3f(-1, 0, 0);
    
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   //  Top
    glColor3f(1,1,1);
    glNormal3f( 0,+1, 0);
    glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   //  Bottom
    glColor3f(1,1,1);
    glNormal3f( 0,-one, 0);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
    glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
   //  End
    glEnd();
   //  Undo transformations
    glPopMatrix();
}



static void flag(double x,double y,double z,double dx,double dy,double dz, double th, int color)
{
    //  Set specular color to white
    float white[] = { 1,1,1,1 };
    float black[] = { 0,0,0,1 };
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
   //  Save transformation
    glPushMatrix();
    glRotated(th,0,1,0);
    glRotated(0,1,0,0);
    glTranslated(x,y,z);
    glScaled(dx,dy,dz);
    
    
    
    glBegin(GL_POLYGON);
    glNormal3f( 0, 0, 1);
    
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
    containers(0,2.6,0, 1,.2,1,0);
    triangle(-3,0,0,1,1,1,0);// scaled it to match width with cube
    triangle(-3,0,0,1,1,1,180);// rotate 180 for
    
    glFlush();
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

static void ball(double x,double y,double z,double r)
{

    int th, ph;
        float yellow[] = { 1.0,1.0,0.0,1.0 };
        float Emission[] = { 0.0,0.0,0.01*emission,1.0 };
        glPushMatrix();

        glTranslated(x, y, z);
        glScaled(r, r, r);
    
    
        //  White ball
        glColor3f(1, 1, 1);
        glMaterialf(GL_FRONT, GL_SHININESS, shiny);
        glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
        glMaterialfv(GL_FRONT, GL_EMISSION, Emission);
    
    
        //  Bands of latitude
        for (ph = -90; ph < 90; ph += inc)
        {
            glBegin(GL_QUAD_STRIP);
            for (th = 0; th <= 360; th += 2 * inc)
            {
                Vertex(th, ph);
                Vertex(th, ph + inc);
            }
            glEnd();
        }
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

    double Ex = -2 * dim*Sin(th)*Cos(ph);
    double Ey = +2 * dim        *Sin(ph);
    double Ez = +2 * dim*Cos(th)*Cos(ph);
    gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, Cos(ph), 0);
    glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);
    
    if (light) //USED ex13 AS REFERNECE !!
        {
            //  Translate intensity to color vectors
            float Ambient[] = { 0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0 };
            float Diffuse[] = { 0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0 };
            float Specular[] = { 0.01*specular,0.01*specular,0.01*specular,1.0 };
            float Position[] = { distance*Cos(zh),ylight,distance*Sin(zh),1.0 };
    
            glColor3f(1, 1, 1);
            ball(Position[0], Position[1], Position[2], 0.1);
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
    else{
        glDisable(GL_LIGHTING);
        
    }
    
    //MY DRAW BOATS
    drawboat(-.8,0,0, .07,.07,.08,1); //big blue
    drawboat(.5,0,0,.05,.1,.13,2);// red
    drawboat(-.1,0,-.5, .1,.04,.1,3);//green
    drawboat(.9,0,-.5, .03,.04,.03,1);//mini blue

    
    glDisable(GL_TEXTURE_2D);
    glWindowPos2i(5,30);
    Print("L-light M-Toggle light, [ ]- elevation , JK-Abiemt ");
    glWindowPos2i(5,10);
    Print("DF- Deffuse, YU- Speclar level, ZX-Shiny");
    
    // X Y Z AXIS !
       glColor3f(1.0,0.0,0.0); // X IS RED
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
           glFlush();
    
    glFlush();
    glutSwapBuffers();
}

void idle()
{
    double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    zh = fmod(90 * t, 360.0);
    glutPostRedisplay();
}

//Special keys!!


//Special keys!!

void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(45,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

void key(unsigned char ch, int x, int y)
{
    //  Exit on ESC
    if (ch == 27)
        exit(0);
   // RESET
    else if (ch == '0')
        th = ph = 0;
    // TOGGEL
    else if (ch == 'l')
        light = 1 - light;
    
    //  LIGHT MOVEMENT
    else if (ch == 'm')
        move = 1 - move;
    //  LIGHT ELEVATION
    else if (ch == '[')
        ylight -= 0.1;
    else if (ch == ']')
        ylight += 0.1;
    
    
    //  AMBIENT LEVEL
    else if (ch == 'j' && ambient > 0)
        ambient -= 5;
    else if (ch == 'k' && ambient < 100)
        ambient += 5;
    
    
    //  DEFFUSE LEVEL
    else if (ch == 'd' && diffuse > 0)
        diffuse -= 5;
    else if (ch == 'f' && diffuse < 100)
        diffuse += 5;
    
    
    //  SPECTACLUR LEVEL
    else if (ch == 'y' && specular > 0)
        specular -= 5;
    else if (ch == 'u' && specular < 100)
        specular += 5;
    
    
    //  EMMISION LEVEL
    else if (ch == 'a' && emission > 0)
        emission -= 5;
    else if (ch == 'q' && emission < 100)
        emission += 5;
    
    
    //  SHINNIE LEVEL
    else if (ch == 'z' && shininess > -1)
        shininess -= 1;
    else if (ch == 'x' && shininess < 7)
        shininess += 1;
    //  TRANSLATE SHINY
    shiny = shininess < 0 ? 0 : pow(2.0, shininess);
    // REPROJECT
    Project(45, asp, dim);
    glutIdleFunc(move ? idle : NULL);
    glutPostRedisplay();
}

/*
 * This function is called by GLUT when the window is resized
 */
void reshape(int width, int height)
{
    //ex15 template!!
    asp = (height > 0) ? (double)width / height : 1;
    glViewport(0, 0, width, height);
    Project(45, asp, dim);
}



int main(int argc, char* argv[])
{
   
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("Assignment 6: Eliza Mimi To");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    texture[0] = LoadTexBMP("lightwood.bmp");
    texture[1] = LoadTexBMP("shipment.bmp");
    ErrCheck("init");
    glutMainLoop();
    return 0;
}

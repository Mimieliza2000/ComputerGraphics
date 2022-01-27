
/*
 *  Set projection
 */
#include "CSCIx229.h"

void Project(double fov,double asp,double dim,double fp,double m)
{
   
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (fp) { //First person
        gluPerspective(fov,asp,dim/16,16*dim);
    }
    else {
        if (m)
            gluPerspective(fov,asp,dim/16,16*dim); //same used for first person
        //  Orthogonal projection
        else
            glOrtho(-asp * dim, +asp * dim, -dim, +dim, -dim, +dim);
    }
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

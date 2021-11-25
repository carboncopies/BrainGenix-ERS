//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing a function to draw a grid when the editor is enabled.
    Additonal Notes: None
    Date Created: 2021-1-25
*/

#include <Grid.h>


// Define Grid Function
void DrawGrid(float UnitSize, int GridSize, float GridPosX, float GridPosY, float GridPosZ) {

    // 

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1.0, 0.0, 0.0);
    int xsize=0,ysize=0;
    for(int j=0;j<10;j++)
    {

        xsize=0;
        for(int i=0;i<10;i++)
        {
             glBegin(GL_POLYGON);
               glVertex3f(-50.0+xsize, -50.0+ysize, 0.0);
               glVertex3f(-40.0+xsize, -50.0+ysize, 0.0);
               glVertex3f(-40.0+xsize, -40.0+ysize, 0.0);
               glVertex3f(-50.0+xsize, -40.0+ysize, 0.0);
            glEnd();
         xsize+=10.0;
     }
     ysize+=10.0;
     }




}
//
//  main.c
//  180_pro1
//
//  Created by daisy_island on 10/25/14.
//  Copyright (c) 2014 daisy_island. All rights reserved.
//

#ifdef __APPLE__      //unix
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32     //windows
#include <windows.h>
#endif
#include <GL/gl.h> // linux
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

float angle=0.0; // angle of rotation for the camera direction
float lx=0.0f,lz=-1.0f,ly=0.0f;// actual vector representing the camera's direction
float x=0.0f,z=5.0f;// XZ position of the camera
float size=1;
float pi = 3.141592653;

void drawBackground(){
    glPushMatrix();
    
    glColor3f(1, 1, 1);
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-10, 10, -10);
    glVertex3f(15, 10, -10);
    glVertex3f(-10, -2, -10);
    glVertex3f(15, -2, -10);
    glVertex3f(-10, -2, 5);
    glVertex3f(15, -2, 5);
    glEnd();
    
    glPopMatrix();
}

void drawBoundaries(){
    glPushMatrix();
    glScalef(.1, .1, .1);
    /* Outter */
    
    glColor3f(0, 0, 0);
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-5, 5, 7);
    glVertex3f(-7, 7, 7);
    glVertex3f(5, 5, 7);
    glVertex3f(7, 7, 7);
    glVertex3f(5, -5, 7);
    glVertex3f(7, -7, 7);
    glVertex3f(-5, -5, 7);
    glVertex3f(-7, -7, 7);
    glVertex3f(-5, 5, 7);
    glVertex3f(-7, 7, 7);
    glEnd();
    
    glColor3f(0, 1, 1);
    /* Inner volumes */
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-5, 5, 5);
    glVertex3f(-5, 5, 7);
    glVertex3f(5, 5, 5);
    glVertex3f(5, 5, 7);
    glVertex3f(5, -5, 5);
    glVertex3f(5, -5, 7);
    glVertex3f(-5, -5, 5);
    glVertex3f(-5, -5, 7);
    glVertex3f(-5, 5, 5);
    glVertex3f(-5, 5, 7);
    glEnd();
    
    glColor3f(1, 0, 1);
    glBegin(GL_POLYGON);
    glVertex3f(-5, 5, 5);
    glVertex3f(5, 5, 5);
    glVertex3f(5, -5, 5);
    glVertex3f(-5, -5, 5);
    glEnd();
    glPopMatrix();
}

void drawCircle(float radius){
    
    glPushMatrix();
    glTranslatef(0,0,size/2);
    glBegin(GL_POLYGON);
    
    glColor3d(0, 0,1);
    for (int i=0; i < 360; i++)
    {
        float degInRad = i*pi/180;
        glVertex3f(cos(degInRad)*radius,sin(degInRad)*radius,0);
    }
    
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3d(1, 1, 0);
    
    for (int i=0; i<360; i++)
    {
        float degInRad = i*pi/180;
        glVertex3f(cos(degInRad)*radius,sin(degInRad)*radius,size/8);
    }
    
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    glColor3d(1, 0, 0);
    /* Draw the first five pieces.*/
    for (int i=0; i<360; i++)
    {
        float degInRad = i*pi/180;
        glVertex3f(cos(degInRad)*radius,sin(degInRad)*radius,0);
        glVertex3f(cos(degInRad)*radius,sin(degInRad)*radius,size/8);
    }
    /*Draw the last piece. */
    glEnd();
    
    glPopMatrix();
}

void drawSolidT(float size){
    glPushMatrix();
    
    glScalef(size, size, size);
    glTranslatef(0,-.8, 1);
    
    glBegin(GL_TRIANGLE_STRIP);
    
    glColor3d(0, 0, 1);
    glVertex3f(-1,0,0);
    glVertex3f(1,0,0);
    glVertex3f(0,2,0);
    
    glVertex3f(-1,0,1.1);
    glVertex3f(1,0,1.1);
    glVertex3f(0,2,1.1);
    
    glEnd();
    
    //Faces.
    glBegin(GL_QUAD_STRIP);
    
    //left
    glColor3d(1, 0, 1);
    glVertex3f(-1,0,0);
    glVertex3f(-1,0,1.1);
    glVertex3f(0,2,0);
    glVertex3f(0,2,1.1);
    
    //right
    glColor3d(0, 1, 0);
    glVertex3f(0,2,1.1);
    glVertex3f(0,2,0);
    glVertex3f(1,0,1.1);
    glVertex3f(1,0,0);
    
    //bottom
    glVertex3f(1,0,0);
    glVertex3f(1,0,1.1);
    glVertex3f(-1,0,1.1);
    glVertex3f(-1,0,0);
    
    glEnd();
    
    glEnd();
    glPopMatrix();
}
void drawPentagon(float radius, float xPos, float yPos){
    
    glPushMatrix();
    glTranslatef(0,0,.7);
    glBegin(GL_POLYGON);
    
    glColor3d(0, 0, 1);
    for (int i=0; i<6 ; i++) {
        glVertex3f(xPos+radius*cos(60*i*pi/180),
                   yPos+radius*sin(60*i*pi/180),
                   0);
    }
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3d(1, 0, 0);
    for (int i=0; i<6 ; i++) {
        glVertex3f(xPos+radius*cos(60*i*pi/180),
                   yPos+radius*sin(60*i*pi/180),
                   size/8);
    }
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    glColor3d(0, 1, 0);
    /* Draw the first five pieces.*/
    for (int i=0; i<6 ; i++) {
        
        glVertex3f(xPos+radius*cos(60*i*pi/180),
                   yPos+radius*sin(60*i*pi/180),
                   0);
        glVertex3f(xPos+radius*cos(60*i*pi/180),
                   yPos+radius*sin(60*i*pi/180),
                   size/8);
    }
    /*Draw the last piece. */
    glVertex3f(xPos+radius*cos(60*5*pi/180),
               yPos+radius*sin(60*5*pi/180),
               size/8);
    glVertex3f(xPos+radius*cos(60*5*pi/180),
               yPos+radius*sin(60*5*pi/180),
               0);
    glVertex3f(xPos+radius*cos(60*6*pi/180),
               yPos+radius*sin(60*6*pi/180),
               size/8);
    glVertex3f(xPos+radius*cos(60*6*pi/180),
               yPos+radius*sin(60*6*pi/180),
               0);
    glEnd();
    
    
    glPopMatrix();
    
}

void drawZero(float size, float xPos, float yPos, float zPos){
    glPushMatrix();
    glTranslatef(xPos,yPos, zPos);
    glScalef(1, 2, 0);
    glScalef(size, size, size);
    
    /*Draw layers.*/
    for (int j=0; j<2; j++) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i<361; i++) {
            glVertex3f(0+1.5*cos(i*pi/180),
                       1.5*sin(i*pi/180),
                       j);
            glVertex3f(0+3*cos(i*pi/180),
                       3*sin(i*pi/180),
                       j);
        }
        glEnd();
    }
    
    /* Volumes */
    glBegin(GL_QUAD_STRIP);
    glColor3d(1, 0, 0);
    
    for(int i=0; i<360; i++){
        glVertex3f(3*cos(i*pi/180),
                   3*sin(i*pi/180),
                   1);
        glVertex3f(3*cos(i*pi/180),
                   3*sin(i*pi/180),
                   0);
    }
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    for(int i=0; i<360; i++){
        glVertex3f(1.5*cos(i*pi/180),
                   1.5*sin(i*pi/180),
                   1);
        
        glVertex3f(1.5*cos(i*pi/180),
                   1.5*sin(i*pi/180),
                   0);
    }
    glEnd();
    
    
    glPopMatrix();
    
}

void drawOne(float size, float xPos, float yPos, float zPos){
    glPushMatrix();
    glTranslatef(xPos,yPos, zPos);
    glScalef(size, size, size);
    
    for (int j=0; j<2; j++) {
        glBegin(GL_POLYGON);
        glVertex3f(-1, 4, j);
        glVertex3f(-3, 2, j);
        glVertex3f(-2, 1, j);
        glVertex3f(1, 4, j);
        glEnd();
        
        glBegin(GL_POLYGON);
        glVertex3f(-1, 4, j);
        glVertex3f(1, 4, j);
        glVertex3f(1, -4, j);
        glVertex3f(-1, -4, j);
        glEnd();
    }
    
    /*Give volumes.*/
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-3, 2, 1);
    glVertex3f(-3, 2, 0);
    glVertex3f(-1, 4, 1);
    glVertex3f(-1, 4, 0);
    glVertex3f(1, 4, 1);
    glVertex3f(1, 4, 0);
    glVertex3f(1, -4, 1);
    glVertex3f(1, -4, 0);
    glVertex3f(-1, -4, 1);
    glVertex3f(-1, -4, 0);
    glVertex3f(-1, 2, 1);
    glVertex3f(-1, 2, 0);
    glVertex3f(-2, 1, 1);
    glVertex3f(-2, 1, 0);
    glVertex3f(-3, 2, 1);
    glVertex3f(-3, 2, 0);
    glEnd();
    
    glPopMatrix();
}

void drawTwo(float size, float xPos, float yPos, float zPos){
    glPushMatrix();
    glTranslatef(xPos,yPos, zPos);
    glScalef(size, size, size);
    
    /* Upper Part */
    //faces
    for (int j = 0 ; j<2; j++) {
        glBegin(GL_POLYGON);
        
        glVertex3f(-4, -7, j);
        glVertex3f(-4, -5, j);
        glVertex3f(4, -5, j);
        glVertex3f(4, -7, j);
        glEnd();
        
        glBegin(GL_POLYGON);
        glVertex3f(-2, -5, j);
        glVertex3f(-4, -5, j);
        glVertex3f(2*cos(250*pi/180),
                   2*sin(250*pi/180),
                   j);
        //glVertex3f(0, -2, j);
        glVertex3f(4*cos(260*pi/180),
                   4*sin(260*pi/180),
                   j);
        // glVertex3f(0, -4, j);
        glEnd();
    }
    //volumes
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-2, -5, 1);
    glVertex3f(-2, -5, 0);
    glVertex3f(4, -5, 1);
    glVertex3f(4, -5, 0);
    glVertex3f(4, -7, 1);
    glVertex3f(4, -7, 0);
    glVertex3f(-4, -7, 1);
    glVertex3f(-4, -7, 0);
    glVertex3f(-4, -5, 1);
    glVertex3f(-4, -5, 0);
    glVertex3f(2*cos(250*pi/180),
               2*sin(250*pi/180),
               1);
    glVertex3f(2*cos(250*pi/180),
               2*sin(250*pi/180),
               0);
    //    glVertex3f(0, -2, 1);
    //    glVertex3f(0, -2, 0);
    
    glVertex3f(4*cos(260*pi/180),
               4*sin(260*pi/180),
               1);
    glVertex3f(4*cos(260*pi/180),
               4*sin(260*pi/180),
               0);
    //    glVertex3f(0, -4, 1);
    //    glVertex3f(0, -4, 0);
    
    glVertex3f(-2, -5, 1);
    glVertex3f(-2, -5, 0);
    
    glEnd();
    
    /* Upper part */
    glRotatef(180, 0, 1, 0);
    //faces
    for (int j = 0 ; j<2; j++) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i<290; i++) {
            glVertex3f(2*cos(i*pi/180),
                       -0.3+2*sin(i*pi/180),
                       j);
            glVertex3f(4*cos(i*pi/180),
                       -0.3+4*sin(i*pi/180),
                       j);
            //            glVertex3f(4*cos((i+1)*pi/180),
            //                       -0.3+4*sin((i+1)*pi/180),
            //                       j);
        }
        glEnd();
    }
    
    /* Upper volumes */
    glBegin(GL_TRIANGLE_STRIP);
    
    glVertex3f(2*cos(0*pi/180), -.3+2*sin(0*pi/180), 1);
    glVertex3f(2*cos(0*pi/180), -.3+2*sin(0*pi/180), 0);
    
    for(int i=0; i<290; i++){
        glVertex3f(4*cos(i*pi/180),
                   -.3+4*sin(i*pi/180),
                   1);
        glVertex3f(4*cos(i*pi/180),
                   -.3+4*sin(i*pi/180),
                   0);
    }
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    for(int i=0; i<290; i++){
        glVertex3f(2*cos(i*pi/180),
                   -.3+2*sin(i*pi/180),
                   1);
        
        glVertex3f(2*cos(i*pi/180),
                   -.3+2*sin(i*pi/180),
                   0);
    }
    glVertex3f(4*cos(290*pi/180), -.3+4*sin(290*pi/180), 1);
    glVertex3f(4*cos(290*pi/180), -.3+4*sin(290*pi/180), 0);
    glEnd();
    
    
    
    glPopMatrix();
    
}

void drawThree(float size, float xPos, float yPos, float zPos){
    glPushMatrix();
    glTranslatef(xPos,yPos, zPos);
    glScalef(size, size, size);
    //glTranslatef(0,0, 8);
    glRotatef(180, 0, 1, 0);
    
    /*Draw two three layers.*/
    for (int j=0; j<2; j++) {
        
        /* Upper Faces */
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i<290; i++) {
            glVertex3f(0+1.25*cos(i*pi/180),
                       3+1.25*sin(i*pi/180),
                       j);
            glVertex3f(0+3*cos(i*pi/180),
                       3+3*sin(i*pi/180),
                       j);
        }
        glEnd();
        
        /* Lower Faces*/
        glBegin(GL_TRIANGLE_STRIP);
        for(int i=70; i<360; i++){
            glVertex3f(0+1.25*cos(i*pi/180),
                       -2.5+1.25*sin(i*pi/180),
                       j);
            glVertex3f(0+3*cos(i*pi/180),
                       -2.5+3*sin((i)*pi/180),
                       j);
        }
        glEnd();
    }
    
    /* Upper Volume */
    glBegin(GL_QUAD_STRIP);
    glColor3d(1, 0, 0);
    
    glVertex3f(1.25*cos(0*pi/180), 3+1.25*sin(0*pi/180), 1);
    glVertex3f(1.25*cos(0*pi/180), 3+1.25*sin(0*pi/180), 0);
    
    for(int i=0; i<290; i++){
        glVertex3f(3*cos(i*pi/180),
                   3+3*sin(i*pi/180),
                   1);
        glVertex3f(3*cos(i*pi/180),
                   3+3*sin(i*pi/180),
                   0);
    }
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    for(int i=0; i<290; i++){
        glVertex3f(1.25*cos(i*pi/180),
                   3+1.25*sin(i*pi/180),
                   1);
        
        glVertex3f(1.25*cos(i*pi/180),
                   3+1.25*sin(i*pi/180),
                   0);
    }
    glVertex3f(3*cos(290*pi/180), 3+3*sin(290*pi/180), 1);
    glVertex3f(3*cos(290*pi/180), 3+3*sin(290*pi/180), 0);
    glEnd();
    
    /* Lower Volume */
    glBegin(GL_QUAD_STRIP);
    glColor3d(1, 0, 0);
    
    glVertex3f(1.25*cos(70*pi/180), -2.5+1.25*sin(70*pi/180), 1);
    glVertex3f(1.25*cos(70*pi/180), -2.5+1.25*sin(70*pi/180), 0);
    
    for(int i=70; i<360; i++){
        glVertex3f(3*cos(i*pi/180),
                   -2.5+3*sin(i*pi/180),
                   1);
        glVertex3f(3*cos(i*pi/180),
                   -2.5+3*sin(i*pi/180),
                   0);
    }
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    for(int i=70; i<360; i++){
        glVertex3f(1.25*cos(i*pi/180),
                   -2.5+1.25*sin(i*pi/180),
                   1);
        
        glVertex3f(1.25*cos(i*pi/180),
                   -2.5+1.25*sin(i*pi/180),
                   0);
    }
    glVertex3f(3*cos(360*pi/180), -2.5+3*sin(360*pi/180), 1);
    glVertex3f(3*cos(360*pi/180), -2.5+3*sin(360*pi/180), 0);
    glEnd();
    
    glPopMatrix();
}

void drawFour(float size, float xPos, float yPos, float zPos){
    
    glPushMatrix();
    glTranslatef(xPos,yPos, zPos);
    glScalef(size, size, size);
    
    /* Draw the surfaces. */
    for (int j=0; j<2; j++) {
        glBegin(GL_POLYGON);
        glVertex3f(-1, 6, j);
        glVertex3f(-4, 0, j);
        glVertex3f(-2, 0, j);
        glVertex3f(1, 6, j);
        glEnd();
        
        glBegin(GL_POLYGON);
        glVertex3f(0, 6, j);
        glVertex3f(2, 6, j);
        glVertex3f(2, -4, j);
        glVertex3f(0, -4, j);
        glEnd();
        
        glBegin(GL_POLYGON);
        glVertex3f(-4, -2, j);
        glVertex3f(-4, 0, j);
        glVertex3f(3, 0, j);
        glVertex3f(3, -2, j);
        glEnd();
    }
    
    /*Give volumes.*/
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-1, 6, 1);
    glVertex3f(-1, 6, 0);
    glVertex3f(2, 6, 1);
    glVertex3f(2, 6, 0);
    glVertex3f(2, 0, 1);
    glVertex3f(2, 0, 0);
    glVertex3f(3, 0, 1);
    glVertex3f(3, 0, 0);
    glVertex3f(3, -2, 1);
    glVertex3f(3, -2, 0);
    glVertex3f(2, -2, 1);
    glVertex3f(2, -2, 0);
    glVertex3f(2, -4, 1);
    glVertex3f(2, -4, 0);
    glVertex3f(0, -4, 1);
    glVertex3f(0, -4, 0);
    glVertex3f(0, -2, 1);
    glVertex3f(0, -2, 0);
    glVertex3f(-4, -2, 1);
    glVertex3f(-4, -2, 0);
    glVertex3f(-4, 0, 1);
    glVertex3f(-4, 0, 0);
    glVertex3f(-1, 6, 1);
    glVertex3f(-1, 6, 0);
    glEnd();
    
    /*Inner volume. */
    glBegin(GL_QUAD_STRIP);
    glVertex3f(0, 4, 1);
    glVertex3f(0, 4, 0);
    glVertex3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(-2, 0, 1);
    glVertex3f(-2, 0, 0);
    glEnd();
    glPopMatrix();
    
}

void drawFive(float size, float xPos, float yPos, float zPos){
    glPushMatrix();
    glTranslatef(xPos,yPos, zPos);
    glScalef(size, size, size);
    
    /* Upper */
    for (int i = 0;  i<2; i++) {
        
        glBegin(GL_POLYGON);
        glVertex3f(-3, 7, i);
        glVertex3f(3, 7, i);
        glVertex3f(3, 5, i);
        glVertex3f(-3, 5, i);
        glEnd();
        
        glBegin(GL_POLYGON);
        glVertex3f(-3, 5, i);
        glVertex3f(-3, 1.2, i);
        glVertex3f(-1, 2.5, i);
        glVertex3f(-1, 5, i);
        glEnd();
        
    }
    /* Upper Volumes */
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-3, 1.2, 1);
    glVertex3f(-3, 1.2, 0);
    glVertex3f(-3, 7, 1);
    glVertex3f(-3, 7, 0);
    glVertex3f(3, 7, 1);
    glVertex3f(3, 7, 0);
    glVertex3f(3, 5, 1);
    glVertex3f(3, 5, 0);
    glVertex3f(-1, 5, 1);
    glVertex3f(-1, 5, 0);
    glVertex3f(-1, 2.5, 1);
    glVertex3f(-1, 2.5, 0);
    glEnd();
    
    /* Lower Part*/
    glRotated(180, 0, 1, 0);
    
    for (int i = 0 ; i <2 ; i++) {
        glBegin(GL_TRIANGLE_STRIP);
        
        for (int j = 31; j<320; j++) {
            glVertex3f(0+2*cos(j*pi/180),
                       -1+2*sin(j*pi/180),
                       i);
            glVertex3f(0+4*cos(j*pi/180),
                       -1+4*sin(j*pi/180),
                       i);
        }
        glEnd();
    }
    
    //volumes
    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(1, 0, 0);
    
    glVertex3f(2*cos(31*pi/180), -1+2*sin(31*pi/180), 1);
    glVertex3f(2*cos(31*pi/180), -1+2*sin(31*pi/180), 0);
    
    for(int i=31; i<320; i++){
        glVertex3f(4*cos(i*pi/180),
                   -1+4*sin(i*pi/180),
                   1);
        glVertex3f(4*cos(i*pi/180),
                   -1+4*sin(i*pi/180),
                   0);
    }
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    for(int i=31; i<320; i++){
        glVertex3f(2*cos(i*pi/180),
                   -1+2*sin(i*pi/180),
                   1);
        
        glVertex3f(2*cos(i*pi/180),
                   -1+2*sin(i*pi/180),
                   0);
    }
    glVertex3f(4*cos(320*pi/180), -1+4*sin(320*pi/180), 1);
    glVertex3f(4*cos(320*pi/180), -1+4*sin(320*pi/180), 0);
    glEnd();
    
    glPopMatrix();
}

void drawSix(float size, float xPos, float yPos, float zPos){
    glPushMatrix();
    glTranslatef(xPos,yPos, zPos);
    glScalef(size, size, size);
    
    
    
    /* Draw the circle */
    // Draw layers
    for (int j=0; j<2; j++) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i<360; i++) {
            glVertex3f(0+1.5*cos(i*pi/180),
                       1.5*sin(i*pi/180),
                       j);
            glVertex3f(0+3*cos(i*pi/180),
                       3*sin(i*pi/180),
                       j);
        }
        glEnd();
    }
    
    /* Volumes */
    glBegin(GL_QUAD_STRIP);
    glColor3d(1, 0, 0);
    
    for(int i=0; i<360; i++){
        glVertex3f(3*cos(i*pi/180),
                   3*sin(i*pi/180),
                   1);
        glVertex3f(3*cos(i*pi/180),
                   3*sin(i*pi/180),
                   0);
    }
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    for(int i=0; i<360; i++){
        glVertex3f(1.5*cos(i*pi/180),
                   1.5*sin(i*pi/180),
                   1);
        
        glVertex3f(1.5*cos(i*pi/180),
                   1.5*sin(i*pi/180),
                   0);
    }
    glEnd();
    
    glPopMatrix();
}


void drawSeven(float size, float xPos, float yPos, float zPos){
    glPushMatrix();
    glTranslatef(xPos,yPos, zPos);
    glScalef(size, size, size);
    
    /* Faces. */
    for (int j = 0;  j < 2 ; j ++) {
        glBegin(GL_POLYGON);
        
        glVertex3f(-3, 3, j);
        glVertex3f(-4, 5, j);
        glVertex3f(4, 5, j);
        glVertex3f(1, 3, j);
        
        glEnd();
        glBegin(GL_POLYGON);
        
        glVertex3f(-3, -5, j);
        glVertex3f(1, 3, j);
        glVertex3f(4, 5, j);
        glVertex3f(0, -5, j);
        
        glEnd();
    }
    /* Volumes. */
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-3, 3, 1);
    glVertex3f(-3, 3, 0);
    glVertex3f(-4, 5, 1);
    glVertex3f(-4, 5, 0);
    glVertex3f(4, 5, 1);
    glVertex3f(4, 5, 0);
    glVertex3f(0, -5, 1);
    glVertex3f(0, -5, 0);
    glVertex3f(-3, -5, 1);
    glVertex3f(-3, -5, 0);
    glVertex3f(1, 3, 1);
    glVertex3f(1, 3, 0);
    glVertex3f(-3, 3, 1);
    glVertex3f(-3, 3, 0);
    glEnd();
    glPopMatrix();
    
}

void drawEight(float size, float xPos, float yPos, float zPos){
    glPushMatrix();
    glTranslatef(xPos,yPos, zPos);
    glScalef(size, size, size);
    //glTranslatef(0,0, 8);
    glRotatef(180, 0, 1, 0);
    
    /*Draw two three layers.*/
    for (int j=0; j<2; j++) {
        
        /* Upper Faces */
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i<360; i++) {
            glVertex3f(0+1.25*cos(i*pi/180),
                       3+1.25*sin(i*pi/180),
                       j);
            glVertex3f(0+3*cos(i*pi/180),
                       3+3*sin(i*pi/180),
                       j);
        }
        glEnd();
        
        /* Lower Faces*/
        glBegin(GL_TRIANGLE_STRIP);
        for(int i=0; i<360; i++){
            glVertex3f(0+1.25*cos(i*pi/180),
                       -2.5+1.25*sin(i*pi/180),
                       j);
            glVertex3f(0+3*cos(i*pi/180),
                       -2.5+3*sin((i)*pi/180),
                       j);
        }
        glEnd();
    }
    
    /* Upper Volume */
    glBegin(GL_QUAD_STRIP);
    glColor3d(1, 0, 0);
    
    for(int i=0; i<360; i++){
        glVertex3f(3*cos(i*pi/180),
                   3+3*sin(i*pi/180),
                   1);
        glVertex3f(3*cos(i*pi/180),
                   3+3*sin(i*pi/180),
                   0);
    }
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    for(int i=0; i<360; i++){
        glVertex3f(1.25*cos(i*pi/180),
                   3+1.25*sin(i*pi/180),
                   1);
        
        glVertex3f(1.25*cos(i*pi/180),
                   3+1.25*sin(i*pi/180),
                   0);
    }
    glEnd();
    
    /* Lower Volume */
    glBegin(GL_QUAD_STRIP);
    glColor3d(1, 0, 0);
    
    
    for(int i=0; i<360; i++){
        glVertex3f(3*cos(i*pi/180),
                   -2.5+3*sin(i*pi/180),
                   1);
        glVertex3f(3*cos(i*pi/180),
                   -2.5+3*sin(i*pi/180),
                   0);
    }
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    for(int i=0; i<360; i++){
        glVertex3f(1.25*cos(i*pi/180),
                   -2.5+1.25*sin(i*pi/180),
                   1);
        
        glVertex3f(1.25*cos(i*pi/180),
                   -2.5+1.25*sin(i*pi/180),
                   0);
    }
    
    glEnd();
    
    glPopMatrix();
}

void drawNumbers(float size, float xPos, float yPos, float zPos){
    glPushMatrix();
    
    
    
    glPopMatrix();
}

void drawCube(float xPos, float yPos, float zPos)
{
    glPushMatrix();
    
    glTranslatef(xPos, yPos, zPos);
    glColor3d(1, 1, 1);
    
    drawBoundaries();
    drawSolidT(.3);
    
    //bottom face
    glRotated(90, 1, 0, 0);
    drawBoundaries();
    
    
    //back
    glRotated(90, 1, 0, 0);
    drawBoundaries();
    drawPentagon(0.3, 0, 0);
    
    //Upper
    glRotated(90, 1, 0, 0);
    drawBoundaries();
    
    //Right
    glRotated(90, 0, 1, 0);
    drawBoundaries();
    
    //Left
    glRotated(180, 0, 1, 0);
    drawBoundaries();
    drawPentagon(0.3, 0, 0);
    
    glutWireCube(2);
    
    glPopMatrix();
}

void init(void)
{
    glEnable(GL_DEPTH_TEST); /* enables the depth test to allow different objects show up in order. */
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void display(void)
{
    /* clear the matrix */
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // set camera view
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Set the camera
    gluLookAt(	x, 1.0f, z,
              x+lx, 1+ly,  z+lz,
              0.0f, 1.0f,  0.0f);
    
    /* modeling transformation */
     drawBackground();
    
    /*Draw five cubes at different point.*/
    for (int i=0; i<5; i++) {
        if (i<3) {
            drawCube(i*1.5, 0, -2.5*(i+1));
        }else{
            drawCube(i*1.5, 0, 2.5*(i-5));
        }
    }
   
    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode (GL_MODELVIEW);
}


void keyboard(unsigned char key, int x, int y)
{float fraction = 1.0f;
    switch (key) {
        case 27:
        case 'q':
            exit(0);
            break;
        case 188:
        case 'w':
            x += lx * fraction;
            z += lz * fraction;
            break;
            
        case 83:
        case 's':
            x -= lx * fraction;
            z -= lz * fraction;
            break;
            
    }
}

void processSpecialKeys(int key, int xx, int yy) {
    
    switch (key) {
        case GLUT_KEY_LEFT :
            angle -= 0.05f;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_RIGHT :
            angle += 0.05f;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_UP :
            angle += 0.05f;
            ly= tan(angle);
            break;
        case GLUT_KEY_DOWN :
            angle -= 0.05f;
            ly= tan(angle);
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE| GLUT_RGB |GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    
    glutIdleFunc(display);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(processSpecialKeys);
    glutPostRedisplay(); //repaint the screen.
    
    glutMainLoop();
    return 0;
}


//
//  main.cpp
//
//
//  Created by Yuhua Mai on 8/30/13.
//  Copyright (c) 2013 Yuhua Mai. All rights reserved.
//

#include <iostream>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <glut.h>
#endif


float win_width = 512;
float win_height = 512;

float timer;

float x_angle, y_angle, z_angle;
bool x_rotate, y_rotate, z_rotate;

int i=1;
double PI = 3.1415926;

// angle of rotation for the camera direction
float angle;
float velAngle;

int red, green, blue;

float cubeSide;
bool enlarge;

void init( void ){
    
    timer = 0;
    
    x_angle = 0;
    y_angle = 0;
    z_angle = 0;
    
    x_rotate = false;
    y_rotate = false;
    z_rotate = false;
    
    angle = 0.0;
    velAngle = 0.0;
    
    red = 1; green = 0; blue = 0;
    
    cubeSide = 0.25;
    enlarge = true;
    
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
    
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
	
}

void idle( void ){
    timer += 0.01;
    
	if (x_rotate) {
		x_angle += 0.01;
	}
    if (y_rotate) {
		y_angle += 0.01;
	}
    if (z_rotate) {
		z_angle += 0.01;
	}
    
    angle += velAngle;
    
    if (cubeSide >= 0.45) {
        enlarge = false;
    } else if(cubeSide <= 0.05){
        enlarge = true;
    }
    
    if (enlarge && cubeSide <= 0.45) {
        cubeSide += 0.0001;
    }
    
    if (!enlarge && cubeSide >= 0.05) {
        cubeSide -= 0.0001;
    }
    
    
    glutPostRedisplay();
}

void line(void){
    glRotatef(x_angle, 1, 0, 0);
    glRotatef(y_angle, 0, 1, 0);
    glRotatef(z_angle, 0, 0, 1);
    
    glBegin(GL_LINES);
    
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);
    
    glEnd();
    
}

void cube(double side){
    glPushMatrix();
    
	glRotatef(x_angle, 1, 0, 0);
    glRotatef(y_angle, 0, 1, 0);
    glRotatef(z_angle, 0, 0, 1);
    
    //draw the cube here
    glBegin(GL_QUADS);
    
    //front back
    glColor3f(0, 0, 1);
    glVertex3f(-side, -side, side);
    glColor3f(1, 0, 1);
    glVertex3f(side, -side, side);
    glColor3f(1, 1, 1);
    glVertex3f(side, side, side);
    glColor3f(0, 1, 1);
    glVertex3f(-side, side, side);
    
    glColor3f(1, 0, 0);
    glVertex3f(side, -side, -side);
    glColor3f(0, 0, 0);
    glVertex3f(-side, -side, -side);
    glColor3f(0, 1, 0);
    glVertex3f(-side, side, -side);
    glColor3f(1, 1, 0);
    glVertex3f(side, side, -side);
    
    //right left
    glColor3f(1, 0, 1);
    glVertex3f(side, -side, side);
    glColor3f(1, 0, 0);
    glVertex3f(side, -side, -side);
    glColor3f(1, 1, 0);
    glVertex3f(side, side, -side);
    glColor3f(1, 1, 1);
    glVertex3f(side, side, side);
    
    glColor3f(0, 0, 0);
    glVertex3f(-side, -side, -side);
    glColor3f(0, 0, 1);
    glVertex3f(-side, -side, side);
    glColor3f(0, 1, 1);
    glVertex3f(-side, side, side);
    glColor3f(0, 1, 0);
    glVertex3f(-side, side, -side);
    
    //top down
    glColor3f(0, 1, 1);
    glVertex3f(-side, side, side);
    glColor3f(1, 1, 1);
    glVertex3f(side, side, side);
    glColor3f(1, 1, 0);
    glVertex3f(side, side, -side);
    glColor3f(0, 1, 0);
    glVertex3f(-side, side, -side);
    
    glColor3f(0, 0, 1);
    glVertex3f(-side, -side, side);
    glColor3f(0, 0, 0);
    glVertex3f(-side, -side, -side);
    glColor3f(1, 0, 0);
    glVertex3f(side, -side, -side);
    glColor3f(1, 0, 1);
    glVertex3f(side, -side, side);
    
    glEnd();
    glPopMatrix();
    
}

void sphere(void){
    glPushMatrix();
    
    glRotatef(x_angle, 1, 0, 0);
    glRotatef(timer, 0, 1, 0);
    glRotatef(z_angle, 0, 0, 1);
    
    glColor3f(1, 1, 1);
    glTranslatef(1, 0.0, 0);
    glutWireSphere(0.25, 10, 10);
    
    glPopMatrix();
}

void cone(void){
    glPushMatrix();
    
    glRotatef(x_angle, 1, 0, 0);
    glRotatef(y_angle, 0, 1, 0);
    glRotatef(timer, 0, 0, 1);
    
    glTranslatef(0, 1, 0);
    
    glColor3f(red, green, blue);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(0.5, 1, 100, 100);
    
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1-red, green, 1-blue);
    glVertex2f(0.0f, 0.0f);       // Center of circle
    int numSegments = 100;
    GLfloat angle;
    for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
        angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
        glVertex2f(sin(angle) * 0.5, cos(angle) * 0.5);
    }
    glEnd();
    
    glPopMatrix();
}

void triangle(void){
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    
    glRotatef(x_angle, 1, 0, 0);
    glRotatef(y_angle, 0, 1, 0);
    glRotatef(z_angle, 0, 0, 1);
    
    //Face 1
    
    glColor3f(0, 1, 0);     glVertex3f(-1, 1, 0);
    glColor3f(1, 0, 0);     glVertex3f(-1, 0, 0);
    glColor3f(0, 0, 1);     glVertex3f(0, 0, 0);
    
    glColor3f(0, 1, 0);     glVertex3f(0, 0, 0);
    glColor3f(1, 0, 0);     glVertex3f(-1, 0, 0);
    glColor3f(0, 0, 1);     glVertex3f(-1, 1, 0);
    
    //Face 2
    
    glColor3f(1, 0, 0);     glVertex3f(1, 1, 0);
    glColor3f(0, 0, 1);     glVertex3f(0, 0, 0);
    glColor3f(0, 1, 0);     glVertex3f(1, 0, 0);
    
    glColor3f(1, 0, 0);     glVertex3f(1, 0, 0);
    glColor3f(0, 0, 1);     glVertex3f(0, 0, 0);
    glColor3f(0, 1, 0);     glVertex3f(1, 1, 0);
    
    //Face 3
    
    glColor3f(0, 0, 1);     glVertex3f(0, 0, 0);
    glColor3f(0, 1, 0);     glVertex3f(-0.5, -1, 0);
    glColor3f(1, 0, 0);     glVertex3f(0.5, -1, 0);
    
    glColor3f(0, 0, 1);     glVertex3f(0.5, -1, 0);
    glColor3f(0, 1, 0);     glVertex3f(-0.5, -1, 0);
    glColor3f(1, 0, 0);     glVertex3f(0, 0, 0);
    
    glEnd();
    glPopMatrix();
    
}

void torus(void){
    glPushMatrix();
    
    glColor3f(0, 1, 1);
    
    glRotatef(timer, 1, 0, 0);
    glRotatef(timer, 0, 1, 0);
    glRotatef(timer, 0, 0, 1);
    
    glutWireTorus(0.2, 3, 30, 30);
    
    glPopMatrix();
}


void display(void)
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    gluPerspective(45.f, win_width/win_height, .1f, 500.f);
    //    glOrtho(-2, 2, -2, 2, 0.1, 500);
    
    
    glMatrixMode(GL_MODELVIEW);
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_LINE, GL_FILL);
    
    glPushMatrix();
    
    gluLookAt(1, 2, 3+angle,
              0, 0, 0,
              0, 1, 0);
    
    line();
    cube(cubeSide);
    sphere();
    cone();
    triangle();
    torus();
    
    glPopMatrix();
    
    glFlush();
    glutSwapBuffers();
}

void reshape( int w, int h )
{
    win_width = w;
    win_height = h;
    glViewport( 0, 0, w, h );
    
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y ) {
    
    switch(key) {
        case 27: // Escape key
            exit(0);break;
            
            // rotate objects
		case 'x':
			x_rotate = ! x_rotate; break;
        case 'y':
			y_rotate = ! y_rotate; break;
        case 'z':
			z_rotate = ! z_rotate; break;
            
            // change cone's color
        case 'c':
            red = !red; green = !green; blue = !blue; break;
            
            // camera angle turn left, right or stop
        case 'a' :
			velAngle = -0.001; break;
		case 'd' :
			velAngle = 0.001; break;
		case 's' :
            velAngle = 0.0; break;
    }
}

int main(int argc, char * argv[])
{
    std::cout << "Hello, World!\n";
    
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize( win_width, win_height );
	
    glutCreateWindow( "3D Cube" );
    
    init();
	
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );
    glutIdleFunc( idle );
    glutMainLoop();
    
    return 0;
}
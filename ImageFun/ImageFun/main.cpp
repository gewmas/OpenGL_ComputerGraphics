//
//  main.cpp
//  ImageFun
//
//  Created by Tabitha Peck on 9/2/13.
//  Copyright (c) 2013 Tabitha Peck. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "ImageIO.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <glut.h>
#endif


float win_width = 512;
float win_height = 512;

ImageIO* current_image;

void init( void ){
    
    glClearColor(1.0, 0.0, 0.0, 0.0);
	
}

void idle( void ){
    
    glutPostRedisplay();
}

void drawImage( void ){
    
    if(current_image != NULL){
        
        glClear(GL_COLOR_BUFFER_BIT);
        glRasterPos2i(0, 0);
        
        glDrawPixels(current_image->getWidth(), current_image->getHeight(), GL_RGB,
                     GL_FLOAT, current_image->getImageDisplayArray());
    }
    
}

void display( void )
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0, win_width, 0, win_height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    drawImage();
    
    glFlush();
}

void reshape( int w, int h )
{
    win_width = w;
    win_height = h;
    glViewport( 0, 0, win_width, win_height );
    
    glutPostRedisplay();
}

void keyboard( unsigned char key, int x, int y ) {
    switch(key) {
        case 27: // Escape key
            exit(0);
            break;
    }
}

void showImageToScreen(ImageIO *the_image, int argc, char *argv[]){
    current_image = the_image;
    
    win_height = the_image->getHeight();
    win_width = the_image->getWidth();
    
    glutInit( &argc, argv );
    
    glutInitDisplayMode( GLUT_RGB );
    glutInitWindowSize( win_width, win_height );
	
    glutCreateWindow( "Image" );
    
    init();
	
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );
    glutIdleFunc( idle );
    
    glutMainLoop();

}

void testStep2(ImageIO *image, int argc, char * argv[]){
    showImageToScreen(image, argc, argv);
}

void testStep3(ImageIO *image, int argc, char * argv[]){
    image->writeImage("/Users/Michael/Desktop/CS344/ImageFun/ImageFun/three.ppm");
    
    ImageIO* the_image = new ImageIO("/Users/Michael/Desktop/CS344/ImageFun/ImageFun/three.ppm");    
    showImageToScreen(the_image, argc, argv);
    delete the_image;
}

void testStep4(ImageIO *image, int argc, char * argv[]){
    ImageIO *current_image = image->removeRed();
    showImageToScreen(current_image, argc, argv);
    delete current_image;
}

void testStep5(ImageIO *image, int argc, char * argv[]){
    ImageIO *current_image = image->grayScale();
    showImageToScreen(current_image, argc, argv);
    delete current_image;
}

void testStep6RemoveGreen(ImageIO *image, int argc, char * argv[]){
    ImageIO *current_image = image->removeGreen();
    showImageToScreen(current_image, argc, argv);
    delete current_image;
}

void testStep6RemoveBlue(ImageIO *image, int argc, char * argv[]){
    ImageIO *current_image = image->removeBlue();
    showImageToScreen(current_image, argc, argv);
    delete current_image;
}

void testStep6Scale(ImageIO *image, int argc, char * argv[]){
    ImageIO *current_image = image->scale(1.8, 0.8);
    showImageToScreen(current_image, argc, argv);
    delete current_image;
}

void testStep6Composite(ImageIO *image1, ImageIO *image2, int argc, char * argv[]){
    ImageIO *current_image = image1->composite(image2);
    showImageToScreen(current_image, argc, argv);
    delete current_image;
}

int main(int argc, char * argv[])
{
    ImageIO* image1 = new ImageIO("/Users/Michael/Desktop/CS344/ImageFun/ImageFun/monstercollege.ppm");
    ImageIO* image2 = new ImageIO("/Users/Michael/Desktop/CS344/ImageFun/ImageFun/girl.ppm");
    
//    testStep2(image1, argc, argv);
//    testStep3(image1, argc, argv);
//    testStep4(image1, argc, argv);
//    testStep5(image1, argc, argv);
//    testStep6RemoveGreen(image1, argc, argv);
//    testStep6RemoveBlue(image1, argc, argv);
//    testStep6Scale(image1, argc, argv);
//    testStep6Composite(image1, image2, argc, argv);
    
    delete image1;
    delete image2;
    
    return 0;
}
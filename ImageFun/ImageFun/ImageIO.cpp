//
//  ImageIO.cpp
//  Resolution
//
//  Created by Tabitha Peck on 7/23/13.
//  Copyright (c) 2013 Tabitha Peck. All rights reserved.
//  based on code from stack overflow: http://stackoverflow.com/questions/2693631/read-ppm-file-and-store-it-in-an-array-coded-with-c
/*
 For specific introduction, please read README.
 
 ImageIO* removeGreen();    remove green color from the image
 ImageIO* removeBlue();     remove blue color from the image
 
 ImageIO* composite();      composite two images together
 ImageIO* scale(int ratio); scale the image - zoom in or zoom out
 */

#include "ImageIO.h"
//#include <stdio.h>
#include <stdlib.h>

#include <GLUT/glut.h>

#include <assert.h>

ImageIO::ImageIO(int w, int h, int m){
    width = w;
    height = h;
    max = m;
    image = new float**[height];
    for(int i = 0; i < height; i++){
        image[i] = new float*[width];
        for(int j = 0; j < width; j++){
            image[i][j] = new float[3];
            image[i][j][0] = 0;
            image[i][j][1] = 0;
            image[i][j][2] = 0;
        }
    }
    imageDisplayArray = NULL;
}

ImageIO::ImageIO(const char* file_name){
    
    FILE* file;
    char buff[16];
    float r, g, b;
    
    file = fopen(file_name, "r"); // open file for reading
    
    if(!file){
        fprintf(stderr, "Unable to open file %s", file_name);
        exit(1);
    }
    
    fscanf(file, "%s%*[^\n]%*c", magic_number); //read magic number and white space
    
    if(magic_number[0] != 'P' || magic_number[1] != '3'){
        printf("Incorrect file type");
        exit(1);
    }
    
    //check for comments
    fscanf(file, "%s", buff);
    while (strncmp(buff, "#", 1) == 0) {
        fscanf(file, "%s%*[^\n]%*c", buff);
    }
    
    if (fscanf(file, "%d %d %d", &width, &height, &max) != 3) {
        fprintf(stderr, "Invalid image size (error loading '%s')\n", file_name);
        exit(1);
    }
    
    image = new float **[height];
    for (int i = 0; i < height; i++) {
        image[i] = new float *[width];
        for (int j = 0; j < width; j++) {
            image[i][j] = new float[3];
            if (fscanf(file, "%f %f %f", &r, &g, &b) != 3) {
                fprintf(stderr, "Invalid pixel reading\n");
                exit(1);
            }
            image[i][j][0] = r/255;
            image[i][j][1] = g/255;
            image[i][j][2] = b/255;
        }
        
    }
    
    fclose(file);
    imageDisplayArray = NULL;
}

ImageIO::~ImageIO(void){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            delete [] image[i][j];
        }
        delete [] image[i];
    }
    delete [] image;
    
    delete [] imageDisplayArray;
}

int ImageIO::getWidth(){
    return width;
}

int ImageIO::getHeight(){
    return height;
}

float*** ImageIO::getImage(){
    return image;
}

//Step 2
float* ImageIO::getImageDisplayArray() {
    if(imageDisplayArray != NULL)
        return imageDisplayArray;
        
    imageDisplayArray = new float[width * height * 3];

    // your code goes here
    int imageDisplayArrayIndex = 0;
    int maxImageDisplayArrayIndex = width * height * 3;
    
    for(int i = height-1; i >= 0; i--){
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 3; k++) {
                assert(imageDisplayArrayIndex < maxImageDisplayArrayIndex);
                imageDisplayArray[imageDisplayArrayIndex++] = image[i][j][k];
            }
        }
    }
    // your code ends here
    
    return imageDisplayArray;
}

//Step 3
void ImageIO::writeImage(const char* file_name){
    FILE* file;
    file = fopen(file_name, "w");
    if(!file){
        fprintf(stderr, "Unable to open file %s", file_name);
        exit(1);
    }
    
    // your code goes here
    fprintf(file, "P3\n");
    fprintf(file, "# Some Description Here\n");
    
    /*
     Can only create one line with #
     fprintf(file, "# CREATOR: GIMP PNM Filter Version 1.1\n");
     fprintf(file, "# CREATOR: GIMP PNM Filter Version 1.1\n");
     fprintf(file, "# CREATOR: GIMP PNM Filter Version 1.1\n");
     */
    
    fprintf(file, "%d %d\n", width, height);
    fprintf(file, "%d\n", max);
    
    for(int i = 0; i < height; i++){
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 3; k++) {
                fprintf(file, "%d\n", int(image[i][j][k]*255));
            }
        }
    }
    // your code ends here
    
    fclose(file);
    
}

//Step 4
void ImageIO::removeColor(int index, ImageIO *currentImage){
    float ***oldImage = getImage();
    float ***image = currentImage->getImage();
    
    for(int i = 0; i < height; i++){
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 3; k++) {
                if (k != index) {
                    image[i][j][k] = oldImage[i][j][k];
                }
            }
        }
    }
}

ImageIO* ImageIO::removeRed(){
    ImageIO* red = new ImageIO(width, height, max);
    
    // your code goes here
    removeColor(0, red);
    // your code ends here
    
    return red;
}


//Step 5
ImageIO* ImageIO::grayScale(){
    ImageIO* gray = new ImageIO(width, height, max);
    
    // your code goes here
    float ***oldImage = getImage();
    float ***grayImage = gray->getImage();
    
    for(int i = 0; i < height; i++){
        for (int j = 0; j < width; j++) {
            float Y = 0.2126*oldImage[i][j][0] + 0.7251*oldImage[i][j][1] + 0.0722*oldImage[i][j][2];
            for (int k = 0; k < 2; k++) {
                grayImage[i][j][k] = Y;
            }
        }
    }
    
    // your code ends here
    
    return gray;
}

//Step 6
ImageIO* ImageIO::removeGreen(){
    ImageIO* green = new ImageIO(width, height, max);
    
    // your code goes here
    removeColor(1, green);
    // your code ends here
    
    return green;
}

ImageIO* ImageIO::removeBlue(){
    ImageIO* blue = new ImageIO(width, height, max);
    
    // your code goes here
    removeColor(2, blue);
    // your code ends here
    
    return blue;
}

ImageIO* ImageIO::scale(float ratioX, float ratioY){
    int newWidth = width*ratioX;
    int newHeight = height*ratioY;
    
    ImageIO* scaleImage = new ImageIO(newWidth, newHeight, max);
    
    float ***oldImage = getImage();
    float ***newImage = scaleImage->getImage();
    
    for(int i = 0; i < newHeight; i++){
        for (int j = 0; j < newWidth; j++) {
            for (int k = 0; k < 3; k++) {
                int indexI = (int)(i / ratioY);
                int indexJ = (int)(j / ratioX);
                newImage[i][j][k] = oldImage[indexI][indexJ][k];
            }
        }
    }
    
    return scaleImage;
}

ImageIO* ImageIO::composite(ImageIO *anotherImage){
    int width1 = getWidth();
    int height1 = getHeight();
    int width2 = anotherImage->getWidth();
    int height2 = anotherImage->getHeight();
    
    float ***image1 = getImage();
    float ***image2 = anotherImage->getImage();
    
    //bigger image is image1
    if(width1 < width2 && height1 < height2){
        float ***temp = image2;
        image2 = image1;
        image1 = temp;
        
        int tempWidth = width1;
        int tempHeight = height1;
        width1 = width2;
        height1 = height2;
        width2 = tempWidth;
        height2 = tempHeight;
    }else if(width1 < width2 && height1 > height2){
        ImageIO *tempImageIO = anotherImage->scale(width1/width2, 1);
        delete anotherImage;
        image2 = tempImageIO->getImage();
        
        width2 = width1;
    }else if(width1 > width2 && height1 < height2){
        ImageIO *tempImageIO = anotherImage->scale(1, height1/height2);
        delete anotherImage;
        image2 = tempImageIO->getImage();
        
        height2 = height1;
    }
    
    ImageIO* compositeImage = new ImageIO(width1, height, max);
    float ***newImage = compositeImage->getImage();
    
    for(int i = 0; i < height1; i++){
        for (int j = 0; j < width1; j++) {
            for (int k = 0; k < 3; k++) {
                if (i < height2 && j < width2) {
                    newImage[i][j][k] = image1[i][j][k] + image2[i][j][k];
                }else{
                    newImage[i][j][k] = image1[i][j][k];
                }
            }
        }
    }
    
    return compositeImage;
}








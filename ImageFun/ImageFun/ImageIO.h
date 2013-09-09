//
//  ImageIO.h
//  Resolution
//
//  Created by Tabitha Peck on 7/23/13.
//  Copyright (c) 2013 Tabitha Peck. All rights reserved.
//

#ifndef __Resolution__ImageIO__
#define __Resolution__ImageIO__

#include <iostream>
//#include "Filter.h"

#include <GLUT/glut.h>

using namespace std;

class ImageIO{
public:
    ImageIO(int w, int h, int max);
    ImageIO(const char* file_name);
    ~ImageIO(void);
    int getWidth();
    int getHeight();
    float*** getImage();
    
    float* getImageDisplayArray();
    void writeImage(const char* file_name);
    
    ImageIO* removeRed();

    ImageIO* grayScale();
    
    ImageIO* removeGreen();
    ImageIO* removeBlue();
    ImageIO* composite(ImageIO *anotherImage);
    ImageIO* scale(float ratioX, float ratioY);
    
private:
    char magic_number[2];
    int width;
    int height;
    int max;
    float*** image;
    float* imageDisplayArray;
    
    void removeColor(int index, ImageIO *currentImage);
    

};

#endif /* defined(__Resolution__ImageIO__) */

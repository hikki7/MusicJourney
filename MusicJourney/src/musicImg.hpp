//
//  musicImg.hpp
//  MusicJourney
//
//  Created by 引田祐樹 on 2019/01/07.
//

#pragma once
#ifndef musicImg_hpp
#define musicImg_hpp

#include <stdio.h>
#include "ofMain.h"


using namespace glm;

class musicImg {
    
public:
    musicImg(vec3 start,ofImage _img,float *radius);
    ~musicImg();
    void update();
    void display();
    void scatterImg();
    void collectImg();
    
    vector<vector<vec3>> target;

private:
    ofImage img;
    int imgW,imgH;
    ofPixels pixels;
    vector<vector<vec3>> location;
    vector<vector<ofColor>>imgColor;
    vector<vector<vec3>> fakeTarget;
    
    float r;
};

#endif /* musicImg_hpp */

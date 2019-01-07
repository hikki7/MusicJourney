//
//  cameraControl.hpp
//  MusicJourney
//
//  Created by 引田祐樹 on 2019/01/07.
//

#pragma once
#ifndef cameraControl_hpp
#define cameraControl_hpp

#include <stdio.h>
#include "ofMain.h"

using namespace glm;

class cameraControl {
    
public:
    cameraControl();
    ~cameraControl();
    void update();
    void display();
    void addForce(vec3 _force);
    void seek(vec3 _target);
    
    bool arrival;
    bool near;
    
private:
    vec3 location;
    vec3 velocity;
    vec3 acceleration;
    float r;
    float maxForce;
    float maxSpeed;
    
    float d;
    float bd;
    
};

#endif /* cameraControl_hpp */
